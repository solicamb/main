/*Copyright (c) 2019 Sagnik Middya and James Meech

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Authored by Sagnik Middya and James Meech
*/


#include <TinyGPS++.h> 
#include <SPI.h>
#include <MFRC522.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "SdFat.h"
#include <Sensor.h>
#include "SPI_anything.h"

#define RST_PIN         PA8          // Reset pin for RFID board
#define SS_PIN          PB12         // Chip select for RFID board
const uint8_t chipSelect = PA4;         // Chip select for SD
#define sensor_ss_pin   PA1

//---------------------------All function instances required-------------------------------
TinyGPSPlus gps;
SdFat sd;
SdFile file;
SPIClass SPI_2(2); //SPI2 for RFID
SPIClass SPI_3(3);

Adafruit_PCD8544 display = Adafruit_PCD8544(PB9, PB8, PB7, PB5, PB6);  //in latest version: PA12 goes to PB7,PA11 goes to pb6

Sensor sensor(sensor_ss_pin);

//--------------------------All variable definitions below -------------------------------------

char fileName[9] = "data.csv";

//MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
unsigned long value;

//SoliCamb logo bitmap
const unsigned char solicamb_logo [] PROGMEM = {
0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0xfe, 0x00, 0x7f, 
  0xff, 0x80, 0xff, 0xf1, 0xff, 0x0f, 0xff, 0x80, 0xff, 0xe7, 0xff, 0xf3, 0xff, 0x80, 0xff, 0x9f, 
  0xff, 0xfd, 0xff, 0x80, 0xff, 0x7f, 0xcf, 0xfe, 0xff, 0x80, 0xfe, 0xff, 0xc7, 0xff, 0x7f, 0x80, 
  0xfd, 0xff, 0xc7, 0xff, 0xbf, 0x80, 0xfb, 0xff, 0xc3, 0xff, 0xdf, 0x80, 0xf7, 0xff, 0xc3, 0xff, 
  0xdf, 0x80, 0xf7, 0xdf, 0xc3, 0xff, 0xef, 0x80, 0xef, 0xe3, 0xc3, 0x83, 0xf7, 0x80, 0xef, 0xe0, 
  0xc2, 0x03, 0xf7, 0x80, 0xef, 0xe0, 0x64, 0x07, 0xf7, 0x80, 0xdf, 0xf0, 0x24, 0x0f, 0xfb, 0x80, 
  0xdf, 0xf8, 0x38, 0x1f, 0xfb, 0x80, 0xdf, 0xfc, 0x18, 0x3f, 0xfb, 0x80, 0xdf, 0xff, 0xe7, 0xff, 
  0xfb, 0x80, 0xdf, 0xff, 0xe7, 0xff, 0xfb, 0x80, 0xdf, 0xff, 0xe7, 0xff, 0xfb, 0x80, 0xdf, 0xff, 
  0xe7, 0xff, 0xfb, 0x80, 0xc0, 0x00, 0x20, 0x00, 0x03, 0x80, 0xc0, 0x07, 0xe7, 0xc0, 0x03, 0x80, 
  0xc0, 0x06, 0x01, 0x40, 0x03, 0x80, 0xc0, 0x06, 0xec, 0x40, 0x03, 0x80, 0xe0, 0x04, 0xef, 0x40, 
  0x07, 0x80, 0xe0, 0x7d, 0xef, 0x40, 0x07, 0x80, 0xf0, 0x41, 0xef, 0x40, 0x0f, 0x80, 0xf0, 0x4d, 
  0x8f, 0x40, 0x0f, 0x80, 0xf8, 0x79, 0xbb, 0x78, 0x1f, 0x80, 0xfc, 0x03, 0x33, 0x0c, 0x3f, 0x80, 
  0xfe, 0x03, 0x5f, 0x8c, 0x7f, 0x80, 0xff, 0x01, 0xdf, 0xf8, 0xff, 0x80, 0xff, 0x80, 0x19, 0x91, 
  0xff, 0x80, 0xff, 0xc0, 0x1d, 0x83, 0xff, 0x80, 0xff, 0xf0, 0x07, 0x0f, 0xff, 0x80, 0xff, 0xfc, 
  0x00, 0x3f, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 
  0xe3, 0x37, 0x63, 0x3b, 0x63, 0x80, 0xde, 0x97, 0x6e, 0x13, 0x2d, 0x80, 0xcc, 0xd7, 0x4e, 0xd0, 
  0x21, 0x80, 0xf4, 0xd7, 0x4e, 0x14, 0xad, 0x80, 0xf2, 0x97, 0x6e, 0xd4, 0xad, 0x80, 0xc6, 0x31, 
  0x62, 0xd7, 0xa3, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80,  
};

int contrast=50;

int menuitem = 1;
int page = 1;

volatile boolean cancel = false;
volatile boolean down = false;
volatile boolean middle = false;

int downButtonState = 1;
int cancelButtonState = 1;  
int selectButtonState = 1;          
int lastDownButtonState = 1;
int lastSelectButtonState = 1;
int lastCancelButtonState = 1;

int rfid_flag=0;
int color_flag=0;
int moisture_flag=0;

float nitrate = 0;
float pH = 0;
uint8_t wetness_top = 0;
uint8_t wetness_mid = 0;
uint8_t wetness_bot = 0;
uint8_t moisture_score_top = 0;
uint8_t moisture_score_mid = 0;
char sensorID;
int serialnumber = 0;
char colorID = 0;
int color_serial = 0;
char moistureID = 0;
int moisture_serial = 0;
#define deviceID 4

uint8_t SPIreceived = 0;
//----------------------------------------------------------------------------

void setup()
{
  pinMode(chipSelect, OUTPUT);
  pinMode(SS_PIN, OUTPUT);
  pinMode(PC14, INPUT_PULLDOWN);
  pinMode(PC13, INPUT_PULLDOWN);
  pinMode(PC15, INPUT_PULLDOWN);
  pinMode(PB9, OUTPUT);
  pinMode(sensor_ss_pin, OUTPUT);
  digitalWrite(sensor_ss_pin, HIGH);
  digitalWrite(PB1, HIGH);
  digitalWrite(PA13, LOW);   // for switching off screen LED

  // connect at 115200 so we can read the GPS fast enough and echo without dropping chars
  // also spit it out
  Serial.begin(115200);
  Serial2.begin(9600);
   Serial.println("right after serial begin");
  delay(1000);
  SPI.begin();
  SPI_2.begin();
  Serial.println("before logo display"); 
  

  //---------Start display and show logo-----------------------
  display.begin();      
  Serial.println("just after display begin");
  display.setContrast(57);
  display.clearDisplay();
  display.display(); 
  
  //display the logo
  display.setRotation(2);
  display.drawBitmap(20, 0,  solicamb_logo, 42, 48, BLACK);
  display.display();
  delay(2500);
  display.clearDisplay();

  Serial.println("just after logo display");

  //---------Sd card initiation------------------------------------
  display.setTextSize(1);
  display.setTextColor(BLACK, WHITE);
  display.setCursor(0, 0);
  display.print("SD card initiation");
    
  if (!sd.begin(chipSelect, SPI_HALF_SPEED)) {
    sd.initErrorHalt();
  }

  if (!sd.exists(fileName)){
  file.open(fileName, O_WRITE | O_CREAT);
  writeHeader();
  delay(1000);
   if (!file.sync() || file.getWriteError()) {
    Serial.println("Synching write error");
  }
  file.close();
  file.flush();
  //-----------------------------------------------------------------------

  
}
drawMenu();
}
//uint32_t timer = millis();

void loop() { 
  //---------------------Showing main menu and navigating---------------------
  //drawMenu();

  int prev_flag_count = color_flag + moisture_flag + rfid_flag;
  
  downButtonState = digitalRead(PC14);
  selectButtonState = digitalRead(PC13);
  cancelButtonState =   digitalRead(PC15);

  checkIfDownButtonIsPressed();
  checkIfCancelButtonIsPressed();
  checkIfSelectButtonIsPressed();

  if (cancel)
  {
    if (page == 1){
      cancel = false;
    }
    else
    {
       cancel = false;
       page = 1;
       drawMenu();      
    }
  }
         
  if (down && page == 1) {
    down = false;
    menuitem++;
    drawMenu();
    if (menuitem==4) 
    {
      menuitem=1;
      drawMenu();
    }      
  }else if (down && (page == 2 || page == 3 || page == 5 || page == 6)) {
    down = false;
    contrast++;
    setContrast();
  }else if (down && page == 4 ) {
    down = false;
    menuitem++;
    drawMenu();
    if (menuitem==3) 
    {
      menuitem=1;
      drawMenu();
    }
    }

  //drawMenu();

  if (middle) {
    middle = false;

    if(page == 1 && menuitem ==3)
    {
      SPI_3=SPI;
      SPI=SPI_2;
      sensorID = sensor.whatsensor();
      serialnumber = sensor.whatserial();
      if (sensorID == 'c')
      {
        page = 4;
        menuitem=1;
        drawMenu();
      }
      else
      {
        display.clearDisplay();
        display.setCursor(15, 0);
        display.print("check connection");
        display.setTextColor(BLACK, WHITE);
        display.display();
        delay(2000);
        page = 1;
        drawMenu();
      }
      SPI=SPI_3;
    }
    
    else if (page == 1 && menuitem==2) 
    {
      page=3;
      drawMenu();
      value=getrfidtag();
      Serial.println(value, HEX);
      page=1;
      drawMenu();
     }
    
    else if (page == 1 && menuitem==1) {
      SPI_3=SPI;
      SPI=SPI_2;
      sensorID = sensor.whatsensor();
      serialnumber = sensor.whatserial();
      if (sensorID == 'm')
      {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("Moisture probe found. Serial Number:");
        display.print(serialnumber);
        display.setTextColor(BLACK, WHITE);
        display.display();
        delay(2000);
        page = 7;
        drawMenu();
      }
      else
      {
        display.clearDisplay();
        display.setCursor(0, 15);
        display.print("Check connection");
        display.setTextColor(BLACK, WHITE);
        display.display();
        delay(2000);
        page = 1;
        drawMenu();
      }
      SPI=SPI_3;
     }
     
    else if (page == 4){
      page = 5;
      drawMenu();
    }
    else if (page == 5){
      sensing();
      page = 1;
      menuitem = 1;
      drawMenu();      
    }
    else if (page == 7){
      sensing(); 
      page = 1;
      drawMenu(); 
    }
    
}

/*
int flag_count = color_flag + moisture_flag + rfid_flag;
  

 if (flag_count != prev_flag_count)
 {
      
      display.clearDisplay();
      display.setCursor(0, 10);
      display.print("Want other measurements?");
      display.setTextColor(BLACK, WHITE);
      display.display();
      while ((middle || cancel) == false)
      {
        selectButtonState = digitalRead(PC13);
        cancelButtonState =   digitalRead(PC15);
        checkIfCancelButtonIsPressed();6
        checkIfSelectButtonIsPressed();
      }
      if (middle == true)
      {
        middle = false;
        page = 1;
        menuitem = 1;
        drawMenu();
      }
      else if (cancel == true)
      {
        cancel = false;
        color_flag = 1;
        moisture_flag = 1;
        rfid_flag = 1;
         
      }
     display.clearDisplay();
         display.setCursor(0, 10);
         display.print("Data logging suceesful");
         display.setTextColor(BLACK, WHITE);
         display.display(); 
      delay(2000);
      page = 1;
      drawMenu();
 }  
 */

  //----------------------Getting GPS is compulsory---------------------------
  
int cntr = 0;
 while (cntr <= 50 && Serial2.available() > 0 && (color_flag == 1 || moisture_flag == 1 || rfid_flag == 1)){
    
    cntr ++;
    
    if (gps.encode(Serial2.read())){
      
      if (gps.location.isValid() && gps.date.isValid()){

        
         Serial.println("GPS data recorded successfully");
         
                     
      }
      else 
      {
        display.clearDisplay();
         display.setCursor(0, 10);
         display.print("GPS not set");
         display.setTextColor(BLACK, WHITE);
         display.display();
      }
      
      
    }

    else
    {
      display.clearDisplay();
         display.setCursor(0, 10);
         display.print("GPS not set");
         display.setTextColor(BLACK, WHITE);
         display.display();
    }

    if (cntr = 50)
    {
      display.clearDisplay();
         display.setCursor(0, 10);
         display.print("Logging Data");
         display.setTextColor(BLACK, WHITE);
         display.display();
              
         startlog();
         delay(1000);
             
         color_flag = 0;
         moisture_flag = 0;
         rfid_flag = 0;
         nitrate = 0;
         wetness_top = 0;
         wetness_mid = 0;
         wetness_bot = 0;
         moisture_score_top = 0;
         moisture_score_mid = 0;
         sensorID = 0;
        serialnumber = 0;
        colorID = 0;
        color_serial = 0;
        moistureID=0;
        moisture_serial=0;
         page = 1;
         drawMenu();
    }
    
    
  }

   
 }


//----------------Checking what button is pressed---------------------------

void checkIfDownButtonIsPressed()
  {
    if (downButtonState != lastDownButtonState) 
  {
    if (downButtonState == 1) 
    {
      down=true;
    }
    delay(200);
  }
   lastDownButtonState = downButtonState;
  }

void checkIfCancelButtonIsPressed()
{
  if (cancelButtonState != lastCancelButtonState) 
  {
    if (cancelButtonState == 1) {
      cancel=true;
    }
    delay(200);
  }
   lastCancelButtonState = cancelButtonState;
}

void checkIfSelectButtonIsPressed()
{
   if (selectButtonState != lastSelectButtonState) 
  {
    if (selectButtonState == 1) {
      middle=true;
    }
    delay(200);
  }
   lastSelectButtonState = selectButtonState;
}

//-----------------------Function for showing menu-------------------
void drawMenu()
  {
//---------page 1:the main menu page---------------------------------    
  if (page==1) 
  {    
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(10, 0);
    display.print("SOLICAMB");
    display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(0, 15);
   
    if (menuitem==1) 
    { 
      display.setTextColor(WHITE, BLACK);
    }
    else 
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.setTextSize(1);
    display.print("Water Ret.");
    display.setCursor(0, 25);
   
    if (menuitem==2) 
    {
      display.setTextColor(WHITE, BLACK);
    }
    else 
    {
      display.setTextColor(BLACK, WHITE);
    }    
    display.print("RFID");
    
    display.display();
    
    if (menuitem==3) 
    { 
      display.setTextColor(WHITE, BLACK);
    }
    else 
    {
      display.setTextColor(BLACK, WHITE);
    }  
    display.setCursor(0, 35);
    display.print("Color sensor");
    display.display();
  }
    
//---------------page 2: for water retention---------------------------------- 
  else if (page==2) 
  {
    
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(5, 0);
    display.println("WATER RET.");
    display.setCursor(0, 15);
    display.print("Take reading");
    display.drawFastHLine(0,10,83,BLACK);
    //display.setCursor(5, 15);
    //display.print("GO");
    display.setTextSize(2);
    display.setCursor(5, 25);
    //display.print(contrast);
 
    display.setTextSize(2);
    display.display();
  }

//----------------page 3: for RFID scanning instruction----------------------------
  else if (page==3) 
  {
    
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(18, 0);
    display.println("RFID");
    display.setCursor(0, 15);
    display.print("Scan card");
    display.drawFastHLine(0,10,83,BLACK);
    display.setTextSize(2);
    display.setCursor(5, 25);
    display.display();
  }

//------------------page4: choosing between Nitrate and PH sensing-----------------------------
  else if (page==4)
  {
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(5, 0);
    display.print("Color Sensor");
    display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(0, 15);
   
    if (menuitem==1) 
    { 
      display.setTextColor(WHITE, BLACK);
    }
    else 
    {
      display.setTextColor(BLACK, WHITE);
    }
    display.setTextSize(1);
    display.print("Nitrates");
    display.setCursor(0, 25);
   
    if (menuitem==2) 
    {
      display.setTextColor(WHITE, BLACK);
    }
    else 
    {
      display.setTextColor(BLACK, WHITE);
    }    
    display.print("PH");
    
    display.display();
    }
//-------------------page 5: Color sensing Instruction---------------------------------------- 
  else if (page==5)
  {
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(5, 0);
    display.println("Color sensing");
    display.setCursor(0, 15);
    display.print("Insert Strip");
    display.drawFastHLine(0,10,83,BLACK);
    display.setCursor(5, 25);
    display.print("Press SELECT");
    display.display();
    }

//------------------page 6: Color sensing wait time----------------------------------
  else if (page==6)
  {
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(5, 0);
    display.println("Color sensing");
    display.setCursor(0, 15);
    display.print("Sensing");
    display.setCursor(10, 25);
    display.print("WAIT");
    display.drawFastHLine(0,10,83,BLACK);
    display.setTextSize(2);
    display.setCursor(5, 25);
    display.display();
    }

//------------------page 7: moisture probe instrsuction----------------------------------
   else if (page==7)
  {
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(5, 0);
    display.println("Moisture Ret.");
    display.setCursor(0, 15);
    display.print("Insert probe");
    display.setCursor(5, 30);
    display.print("Press SELECT");
    display.drawFastHLine(0,10,83,BLACK);
    display.display();
    }

//------------------page 8: moisture probe irrigation instrsuction----------------------------------
   else if (page==8)
  {
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(5, 0);
    display.println("Moisture Ret.");
    display.setCursor(0, 15);
    display.print("Irrigate probe");
    display.setCursor(0, 25);
    display.print("Measurement in progress");
    display.drawFastHLine(0,10,83,BLACK);
    display.display();
    }
   
  }

  void resetDefaults()
  {
    contrast = 50;
    setContrast();
    
  }

  void setContrast()
  {
    display.setContrast(57);
    display.display();
  }

  //------------------------------------------------------------------------

  //---------------------Common sensing function for both sensors--------------------------------
void sensing(){
  SPI_3=SPI;
  SPI=SPI_2;
  
  if (sensorID == 'c')
  {
    page = 6;
    drawMenu();
    delay(1000);
    
    if (menuitem == 1)
    {
    sensor.startsensing(0x01);      //0x01 = nitrates; 0x02 = PH
    SPI_readAnything(SPIreceived);

    while (SPIreceived != 2)       //waits untill slave sends 2 to indicate that it will send the nitrate value next
     {
      SPI_readAnything(SPIreceived);
      delay(10);
     }
    delay(500); 
    SPI_readAnything(nitrate);
    digitalWrite(sensor_ss_pin, HIGH);
    colorID = sensorID; color_serial = serialnumber;
    Serial.println(nitrate);
    
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(5, 0);
    display.println("Color sensing");
    display.setCursor(0, 15);
    display.print("Nitrate content:");
    display.setCursor(0, 25);
    display.print(nitrate);
    display.print(" ppm");
    display.display();
    delay(5000);       
    }
    
    if (menuitem == 2)
    {
    sensor.startsensing(0x02);      //0x01 = nitrates; 0x02 = PH
    SPI_readAnything(SPIreceived);

    while (SPIreceived != 2)       //waits untill slave sends 2 to indicate that it will send the pH value next
     {
      SPI_readAnything(SPIreceived);
      delay(10);
     }
    delay(500); 
    SPI_readAnything(pH);
    digitalWrite(sensor_ss_pin, HIGH);
    colorID = sensorID; color_serial = serialnumber;
    
    display.setTextSize(1);
    display.clearDisplay();
    display.setTextColor(BLACK, WHITE);
    display.setCursor(5, 0);
    display.println("Color sensing");
    display.setCursor(0, 15);
    display.print("pH value:");
    display.setCursor(0, 25);
    display.print(pH);       
    display.display();
    delay(5000);
    }
    
    color_flag = 1;
    }
 
  if (sensorID == 'm')
  {
      sensor.startsensing(0xF1); // 0xF recognised by the slave
      delay(1000);
    
      display.setTextSize(1);
      display.clearDisplay();
      display.setTextColor(BLACK, WHITE);
      display.setCursor(5, 0);
      display.println("Moisture Ret.");
      display.drawFastHLine(0,10,83,BLACK);
      SPI_readAnything(SPIreceived);    

     while (SPIreceived != 3)       //slave sends 3 before sending 'soil wetness_top" value
     {
      SPI_readAnything(SPIreceived);
      delay(1);
     }
     
     if (SPIreceived == 3)        // slave sends 3 before sending 'soil wetness_top" value 
     {
      SPI_readAnything(wetness_top);     //reads wetness_top value
      delay(100);
      SPI_readAnything(SPIreceived);
      delay(100);
      SPI_readAnything(wetness_mid);     //reads wetness_top value
      delay(100);
      SPI_readAnything(SPIreceived);
      delay(100);
      SPI_readAnything(wetness_bot);     //reads wetness_top value
      display.setTextSize(1);
      display.setCursor(0, 15);
      display.print("Top soil:");
      display.display();
      
      if (wetness_top == 3)
        display.print("wet");
      else if (wetness_top == 2)
        display.print("moist");  
      else if (wetness_top == 1)
        display.print("dry");
      display.display();

      display.setCursor(0, 25);
      display.print("Mid soil:");
      display.display();
      
      if (wetness_mid == 3)
        display.print("wet");
      else if (wetness_mid == 2)
        display.print("moist");  
      else if (wetness_mid == 1)
        display.print("dry");
      display.display();

      display.setCursor(0, 35);
      display.print("Bot soil:");
      display.display();
      
      if (wetness_bot == 3)
        display.print("wet");
      else if (wetness_bot == 2)
        display.print("moist");  
      else if (wetness_bot == 1)
        display.print("dry");  
      display.display();
      delay(5000);
      
      page = 8;
      drawMenu();
      delay(1000);
     }
    
     while (SPIreceived != 4)       //waits untill slave sends 4 to indicate that it will send the water velocity parameter next
     {
      SPI_readAnything(SPIreceived);
      delay(1);
     }
     delay(500);
     SPI_readAnything(moisture_score_top);
     delay (10);
     
     while (SPIreceived != 5)       //waits untill slave sends 4 to indicate that it will send the water velocity parameter next
     {
      SPI_readAnything(SPIreceived);
      delay(1);
     }

      SPI_readAnything(moisture_score_mid);
      display.setTextSize(1);
      display.clearDisplay();
      display.setTextColor(BLACK, WHITE);
      display.setCursor(5, 0);
      display.println("Moisture Ret.");
      display.drawFastHLine(0,10,83,BLACK);
      display.setCursor(0, 15);
      display.print("Scores");
      display.setCursor(0, 25);
      display.print("Top soil: ");
      display.print(moisture_score_top);
      display.setCursor(0, 35);
      display.print("Mid soil: ");
      display.print(moisture_score_mid);
      display.display();
      delay(5000);
           
     
    }
    
    digitalWrite(sensor_ss_pin, HIGH);
    moistureID = sensorID; moisture_serial = serialnumber;
    moisture_flag = 1;
    
  
  SPI=SPI_3;


}
  
long getrfidtag() {
  //This was originally in the setup function:

  
  digitalWrite(SS_PIN, LOW);
  
  digitalWrite(chipSelect, HIGH);
  delay(50);
  SPI_3=SPI;
  SPI=SPI_2;
  MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();  // Show details of PCD - MFRC522 Card Reader details
  


  //This was originally in the loop function:
  
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  while ( ! mfrc522.PICC_IsNewCardPresent()) {
    
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    
  }

  // Dump debug info about the card; PICC_HaltA() is automatically called
  value=mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  Serial.println(value, HEX);
  SPI.end();
  SPI=SPI_3;
  //digitalWrite(PC13, HIGH);
  rfid_flag=1;
  delay(1000);
  //digitalWrite(PC13, LOW);
  digitalWrite(SS_PIN, HIGH);
  return value;

 
}


//--------------------to configure the SD card writing-------------------------------
void startlog(){


  digitalWrite(chipSelect, LOW);
  delay(1000);
  
  if (!sd.begin(chipSelect, SPI_HALF_SPEED)) {
    sd.initErrorHalt();
  }

  if (!file.open(fileName, O_WRITE | O_APPEND | O_CREAT)) {
    Serial.println("Error trying file.open");
  }
  else{

  logData();
   if (!file.sync() || file.getWriteError()) {
    Serial.println("Synching write error");
  }
  
  file.close();
  file.flush();
  }
}

//----------------------exclusive function to write the column headers-------------------
//----------called rom the setup function if no pre existing fuile is not found----------

void writeHeader() {

  file.print(F("Hour")); 
  file.write(","); 
  file.print(F("Minute")); 
  file.write(",");
  file.print(F("Second")); 
  file.write(",");
  file.print(F("Day")); 
  file.write(",");
  file.print(F("Month")); 
  file.write(",");
  file.print(F("Year")); 
  file.write(",");
  file.print(F("Lattitude")); 
  file.write(","); 
  file.print(F("Longitude")); 
  file.write(",");
  file.print(F("RFID TAG"));
  file.write(",");
  file.print(F("Nitrate"));
  file.write(",");
  file.print(F("Top soil wetness"));
  file.write(",");
  file.print(F("Mid soil wetness"));
  file.write(",");
  file.print(F("Lower soil wetness"));
  file.write(",");
  file.print(F("Top soil score"));
  file.write(",");
  file.print(F("Mid soil score"));
  file.write(",");
  file.print(F("Device ID")); 


  file.println();
}
//---------------------Logging the individual readings-----------------------------------

void logData() {
  
  
    file.print(String(gps.time.hour()));
    file.write(",");
    file.print(String(gps.time.minute()));
    file.write(",");
    file.print(String(gps.time.second()));
    file.write(",");
    file.print(String(gps.date.day()));
    file.write(",");
    file.print(String(gps.date.month()));
    file.write(",");
    file.print(String(gps.date.year()));
    file.write(",");
    file.print(String(gps.location.rawLat().negative ? "-" : "+"));
    file.print(String(gps.location.lat(), 6));
    file.write(",");
    file.print(String(gps.location.rawLng().negative ? "-" : "+"));
    file.print(String(gps.location.lng(), 6));
    file.write(",");
    file.print(value, HEX);
    file.write(",");
    file.print(nitrate);
    file.write(",");
    file.print(wetness_top);
    file.write(",");
    file.print(wetness_mid);
    file.write(",");
    file.print(wetness_bot);
    file.write(",");
    file.print(moisture_score_top);
    file.write(",");
    file.print(moisture_score_mid);
    file.write(",");
    file.print(deviceID);
    file.print(colorID);
    file.print(color_serial);
    file.print(moistureID);
    file.print(moisture_serial);
    file.println();
     
}

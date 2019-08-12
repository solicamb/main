
# File Communicative.cpp

[**File List**](files.md) **>** [**Communicative.cpp**](_communicative_8cpp.md)

[Go to the documentation of this file.](_communicative_8cpp.md) 


````cpp

#include <Arduino.h>
#include "Communicative.h"
#include "SPI_InstructionSet.h"
#include <SPI.h>

const int REQUEST_DELAY_MICROS = 100;

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

Communicative::Communicative(const int CS)
{

  ChipSelect = CS;
  SPISetup();

}

void Communicative::SPISetup(){

  // digitalWrite(ChipSelect, HIGH);  // ensure SS stays high for now

  // // Put SCK, MOSI, SS pins into output mode
  // // also put SCK, MOSI into LOW state, and SS into HIGH state.
  // // Then put SPI hardware into Master mode and turn SPI on
  // SPI.begin ();

  // // Slow down the master a bit
  // SPI.setClockDivider(SPI_CLOCK_DIV8);

  SPI.begin(); //Initialize the SPI_1 port.
  SPI.setBitOrder(MSBFIRST); // Set the SPI_1 bit order
  SPI.setDataMode(SPI_MODE0); //Set the  SPI_2 data mode 0
  SPI.setClockDivider(SPI_CLOCK_DIV16);      // Slow speed (72 / 16 = 4.5 MHz SPI_1 speed)
  pinMode(ChipSelect, OUTPUT);
}

Communicative::~Communicative(void){
  SPI.end();
}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

bool Communicative::isPeripheralConnected(void){

  if (areYouAlive() == 0x06){
    return true;
  }else{
    return false;
  }

}


sCmd Communicative::RequestReply(const mCmd Request){

  digitalWrite(ChipSelect, LOW);  // enable Slave Select 

  sCmd Reply;
  
  //Initial Handshake  
   transferAndPause ('?');  // add command
   byte a = transferAndPause (0x00);

  if (a == 0x06){

    //Send Request
      SPI_write(Request);
      delay(REQUEST_DELAY_MICROS);

    //Recieve Reply
      SPI_read(Reply);

  }else{
    //Throw error due to failed handshake
  }


  // disable Slave Select
    digitalWrite(ChipSelect, HIGH);


  return Reply;

}


Identity Communicative::RequestIdentity(const mCmd Request){
  
  digitalWrite(ChipSelect, LOW);  // enable Slave Select 
  Identity Reply;
  
  //Initial Handshake  
   transferAndPause ('?');  // add command
   byte a = transferAndPause (0x00);

  if (a == 0x06){

    //Send Request
      SPI_write(Request);
      delay(REQUEST_DELAY_MICROS);

    //Recieve Reply
      SPI_read(Reply);

  }else{
    //Throw error due to failed handshake
  }


  // disable Slave Select
    digitalWrite(ChipSelect, HIGH);


  return Reply;


}

Data Communicative::RequestData(const mCmd Request){

  digitalWrite(ChipSelect, LOW);  // enable Slave Select 
  Data Reply;
  
  //Initial Handshake  
   transferAndPause ('?');  // add command
   byte a = transferAndPause (0x00);

  if (a == 0x06){

    //Send Request
      SPI_write(Request);
      delay(REQUEST_DELAY_MICROS);

    //Recieve Reply
      SPI_read(Reply);

  }else{
    //Throw error due to failed handshake
  }


  // disable Slave Select
    digitalWrite(ChipSelect, HIGH);


  return Reply;


}

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library

byte Communicative::transferAndPause(const byte what){

//  delay(100);
  byte a = SPI.transfer (what);
 delayMicroseconds (100);
    
  return a;
}

template <typename T> unsigned int Communicative::SPI_write (const T& value){
  
  const byte * p = (const byte*) &value;
  unsigned int i;
  for (i = 0; i < sizeof value; i++)
        transferAndPause(*p++);
  return i;
} 
    
template <typename T> unsigned int Communicative::SPI_read(T& value){

  byte * p = (byte*) &value;
  unsigned int i;
  for (i = 0; i < sizeof value; i++)
        *p++ = transferAndPause (0);
  return i;

}

byte Communicative::areYouAlive(){

   mCmd Request = {(mInstruct)IsThereData, (int)0,(float)0.0 };
   sCmd Reply;

  digitalWrite(ChipSelect, LOW);  // enable Slave Select 
  //digitalWrite(SS, LOW);
  
  //Initial Handshake  
   transferAndPause ('?');  // add command
   byte a = transferAndPause (0x00);

//    Serial.print("Recieved: ");
//    Serial.println(a);

  if (a == 0x06){

    //Send Request
      SPI_write(Request);
      delay(REQUEST_DELAY_MICROS);

    //Recieve Reply
      SPI_read(Reply);

  }else{
    //Throw error due to failed handshake
  }


  // disable Slave Select
    digitalWrite(ChipSelect, HIGH);
    //digitalWrite(SS, HIGH);

  return a;


} 
````


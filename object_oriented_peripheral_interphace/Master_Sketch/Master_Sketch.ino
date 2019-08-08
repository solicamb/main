  #include <SPI.h>
//#include "SPI_Anything.h"
#include "Communicative.h"
#include "Sensor.h"
#define SPI1_NSS_PIN PA4 

//Sensor MySensor(SPI1_NSS_PIN);

//###########################################################################################################

void setup (void)
{
  Serial.begin (115200);
  Serial.println ();
  Serial.println("Setup complete");
//
//  SPI.begin(); //Initialize the SPI_1 port.
//  SPI.setBitOrder(MSBFIRST); // Set the SPI_1 bit order
//  SPI.setDataMode(SPI_MODE0); //Set the  SPI_2 data mode 0
//  SPI.setClockDivider(SPI_CLOCK_DIV16);      // Slow speed (72 / 16 = 4.5 MHz SPI_1 speed)
//  pinMode(SPI1_NSS_PIN, OUTPUT);
  
//  digitalWrite(SS, HIGH);  // ensure SS stays high for now
//
//  // Put SCK, MOSI, SS pins into output mode
//  // also put SCK, MOSI into LOW state, and SS into HIGH state.
//  // Then put SPI hardware into Master mode and turn SPI on
//  SPI.begin ();
//
//  // Slow down the master a bit
//  SPI.setClockDivider(SPI_CLOCK_DIV8);
  
}  // end of setup

void loop (void)
{

   ///////////////////////////////////////////////////////
  
//  digitalWrite(SS, LOW);  // enable Slave Select 
//  
//  //Initial Handshake  
//    transferAndWait ('?');  // add command
//   byte a = transferAndWait (0x00);
//
//  //Send Request
//    mCmd Request = {(mInstruct)NextCommandPlease, (int)10,(float)1.5 };
//    SPI_writeAnything(Request);
//    delay(100);
//
// //Recieve Reply
//    sCmd Reply;
//    SPI_readAnything(Reply);
//
//
//     // disable Slave Select
//    digitalWrite(SS, HIGH);
  //////////////////////////////////////////////////////
//
//  Communicative RawSensor;
//
//  delay(100);
//
//  mCmd Request = {(mInstruct)NextCommandPlease, (int)10,(float)1.5 };
//  sCmd RawReply = RawSensor.RequestReply(Request);
//
//    Serial.println ("Reply From Slave");
////  Serial.println (a);
//  Serial.println(RawReply.Instruction);
//  Serial.println((String)RawReply.sParam);  
//  Serial.println(RawReply.iParam);
//  Serial.println(RawReply.fParam);

/////////////////////////////////////////////////////////
Sensor MySensor(SPI1_NSS_PIN);

Serial.println("Checking Sensot...");
if (MySensor.areYouConnected()){
  Serial.println("Sensor is connected");
}else{
  Serial.println("NOT CONNECTED");
}

//Test Instructor
Serial.print("Num Instructions: ");
Serial.println(MySensor.howManyInstructions());
MySensor.loadNextCommand();
char command[SLAVE_COMMMAND_STRING_LENGTH];
MySensor.getCurrentCommandString(command);
Serial.println("\n\nComand String");
Serial.println((String)command);

Serial.print("Sensor asks: Please wait for: ");
Serial.println(MySensor.howLongShouldIWait());


//Test Identifiable
Serial.println("\n Checking Sensor Identity");
MySensor.updateIdentity();
char sName[IDENTITY_SENSOR_NAME_LENGTH];
MySensor.getSensorName(sName);
Serial.print("Sensor Name:   ");
Serial.println((String)sName);

//Test Data Source
Serial.println("\n Checking Data");
if (MySensor.isThereData()){
  Serial.println("Sensor reports data present");
}else{
  Serial.println("NO DATA");
}

MySensor.loadData();
float DataVect[DATA_ROW_LENGTH];
MySensor.getDataVector(First,DataVect);
int vectLen = MySensor.getVectorLength(First);
Serial.print("Vector length: ");
Serial.println(vectLen);
char Heading[ROW_HEADING_LENGTH];
MySensor.getVectorHeading(First,Heading);
Serial.print((String)Heading);
char Units[ROW_UNIT_LENGTH];
MySensor.getVectorUnits(First,Units);
for (int i = 0; i<vectLen; i++){
  Serial.print(DataVect[i]);
  Serial.print((String)Units);
  Serial.print(",");
}
Serial.println();
MySensor.getDataVector(Second,DataVect);
vectLen = MySensor.getVectorLength(Second);
Serial.print("Vector length: ");
Serial.println(vectLen);
MySensor.getVectorHeading(Second,Heading);
Serial.print((String)Heading);
 Units[ROW_UNIT_LENGTH];
MySensor.getVectorUnits(Second,Units);
for (int i = 0; i<vectLen; i++){
  Serial.print(DataVect[i]);
  Serial.print((String)Units);
  Serial.print(",");
}

Serial.println();
MySensor.getDataVector(Third,DataVect);
vectLen = MySensor.getVectorLength(Third);
Serial.print("Vector length: ");
Serial.println(vectLen);
MySensor.getVectorHeading(Third,Heading);
Serial.print((String)Heading);
 Units[ROW_UNIT_LENGTH];
MySensor.getVectorUnits(Third,Units);
for (int i = 0; i<vectLen; i++){
  Serial.print(DataVect[i]);
  Serial.print(Units);
  Serial.print(",");
}

Serial.println();

//Test Instructable
if(MySensor.issueCommand(PauseMeasurementForiParam,100)){
  Serial.println("Pause Command ACK");
}else{
  Serial.println("PAUSE COMMAND FAILED");
}


if(MySensor.issueCommand(RestartMeasurementProcedure)){
  Serial.println("Restart Command ACK");
}else{
  Serial.println("RESTART COMMAND FAILED");
}

if(MySensor.issueCommand(ResetDevice)){
  Serial.println("Reset Command ACK");
}else{
  Serial.println("RESET COMMAND FAILED");
}


//Test Error




Serial.println("*******************************************");
  
  delay (2000);  // 1 second delay 
}  // end of loop

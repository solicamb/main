  #include <SPI.h>
//#include "SPI_Anything.h"
#include "Communicative.h"
#include "Sensor.h"

Sensor MySensor(13);

//###########################################################################################################

void setup (void)
{
  Serial.begin (115200);
  Serial.println ();
  
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
//Serial.println("Instantiating Sensor");
//Sensor MySensor(SS);

Serial.println("Checking Sensot...");
if (MySensor.areYouConnected()){
  Serial.println("Sensor is connected");
}else{
  Serial.println("NOT CONNECTED");
}

//sCmd Reply = MySensor.loadNextCommand();
//char command[SLAVE_COMMMAND_STRING_LENGTH];
//MySensor.getCurrentCommandString(command);
//
//Serial.println("\n\nComand String");
//Serial.println((String)command);
//

//
//Serial.println("\n Checking Data");
//if (MySensor.isThereData()){
//  Serial.println("Sensor reports data present");
//}else{
//  Serial.println("NO DATA");
//}


MySensor.loadData();
float DataVect[DATA_ROW_LENGTH];
MySensor.getDataVector(First,DataVect);
int vectLen = MySensor.getVectorLength(First);
Serial.print("Vector length: ");
Serial.println(vectLen);
Serial.print("First Data vector: ");
for (int i = 0; i<vectLen; i++){
  Serial.print(DataVect[i]);
  Serial.print(",");
}


//Serial.println("\n Checking Sensor Identity");
//MySensor.updateIdentity();
//char sName[IDENTITY_SENSOR_NAME_LENGTH];
//MySensor.getSensorName(sName);
//Serial.print("Sensor Name:   ");
//Serial.println((String)sName);
Serial.println("*******************************************");
  
  delay (2000);  // 1 second delay 
}  // end of loop

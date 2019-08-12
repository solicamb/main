#include <SPI.h>
#include "Sensor.h"
#define SPI1_NSS_PIN PA4 

void setup (void)
{
  Serial.begin (115200);
  Serial.println ();
  
}  // end of setup

void loop (void)
{

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


#include <Arduino.h>
#include "Communicative.h"
#include "SPI_InstructionSet.h"
#include <SPI.h>

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

Communicative::Communicative(const int CS)
{

  if (CommsModule.isPeripheralConnected()){
    updateIdentity();
  }

  ThisSensor.sensorChipSelect = CS;

}


// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

bool Communicative::hasIdentityChanged(void){

  Identity connectedID;
  mCmd Request = {(mInstruct)WhoAreYou, (int)0,(float)0.0};

  connectedID = CommsModule.RequestIdentity(Request);

  if (connectedID.sensorID == ThisSensor.sensorID){
    return false;
  }else{
    return true;
  }

}

void Communicative::updateIdentity(void){

  Identity connectedID;
  mCmd Request = {(mInstruct)WhoAreYou, (int)0,(float)0.0};

  connectedID = CommsModule.RequestIdentity(Request);

  ThisSensor.sensorID = connectedID.sensorID;

  for (int i =0; i<ThisSensor.namelength; i++){
    ThisSensor.SensorName[i] = connectedID.SensorName[i];
  }
  

}

void setChipSelect(const int ChipSelect){
  CommsModule.setChipSelect(ChipSelect);
}
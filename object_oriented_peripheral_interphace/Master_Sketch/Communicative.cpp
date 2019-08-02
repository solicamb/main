/*
  Test.h - Test library for Wiring - implementation
  Copyright (c) 2006 John Doe.  All right reserved.
*/

// include core Wiring API
//#include "WProgram.h"

// include this library's description file
//#include "Test.h"

// include description files for other libraries used (if any)
//#include "HardwareSerial.h"

#include <Arduino.h>
#include "Communicative.h"
#include "SPI_InstructionSet.h"
#include <SPI.h>

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

Communicative::Communicative(void)
{

  ThisSensor.sensorChipSelect = SS;
  SPISetup();

}

Communicative::Communicative(int ChipSelect){

  ThisSensor.sensorChipSelect = ChipSelect;
  SPISetup();

}

void Communicative::SPISetup(void){

  digitalWrite(ThisSensor.sensorChipSelect, HIGH);  // ensure SS stays high for now

  // Put SCK, MOSI, SS pins into output mode
  // also put SCK, MOSI into LOW state, and SS into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin ();

  // Slow down the master a bit
  SPI.setClockDivider(SPI_CLOCK_DIV8);
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

bool Communicative::hasPerihperalChanged(void){

  Identity connectedID;
  mCmd Request = {(mInstruct)WhoAreYou, (int)0,(float)0.0};

  connectedID = RequestIdentity(Request);

  if (connectedID.sensorID == ThisSensor.sensorID){
    return false;
  }else{
    return true;
  }

}

void Communicative::updatePeripheralInfo(void){

  Identity connectedID;
  mCmd Request = {(mInstruct)WhoAreYou, (int)0,(float)0.0};

  connectedID = RequestIdentity(Request);

  ThisSensor.sensorID = connectedID.sensorID;

  for (int i =0; i<ThisSensor.namelength; i++){
    ThisSensor.SensorName[i] = connectedID.SensorName[i];
  }
  

}


sCmd Communicative::RequestReply(const mCmd Request){

  digitalWrite(ThisSensor.sensorChipSelect, LOW);  // enable Slave Select 

  sCmd Reply;
  
  //Initial Handshake  
   transferAndPause ('?');  // add command
   byte a = transferAndPause (0x00);

  if (a == 0x06){

    //Send Request
      SPI_write(Request);
      delay(100);

    //Recieve Reply
      SPI_read(Reply);

  }else{
    //Throw error due to failed handshake
  }


  // disable Slave Select
    digitalWrite(ThisSensor.sensorChipSelect, HIGH);


  return Reply;

}


Identity Communicative::RequestIdentity(const mCmd Request){
  
  digitalWrite(ThisSensor.sensorChipSelect, LOW);  // enable Slave Select 
  Identity Reply;
  
  //Initial Handshake  
   transferAndPause ('?');  // add command
   byte a = transferAndPause (0x00);

  if (a == 0x06){

    //Send Request
      SPI_write(Request);
      delay(100);

    //Recieve Reply
      SPI_read(Reply);

  }else{
    //Throw error due to failed handshake
  }


  // disable Slave Select
    digitalWrite(ThisSensor.sensorChipSelect, HIGH);


  return Reply;


}

Data Communicative::RequestData(const mCmd Request){

  digitalWrite(ThisSensor.sensorChipSelect, LOW);  // enable Slave Select 
  Data Reply;
  
  //Initial Handshake  
   transferAndPause ('?');  // add command
   byte a = transferAndPause (0x00);

  if (a == 0x06){

    //Send Request
      SPI_write(Request);
      delay(100);

    //Recieve Reply
      SPI_read(Reply);

  }else{
    //Throw error due to failed handshake
  }


  // disable Slave Select
    digitalWrite(ThisSensor.sensorChipSelect, HIGH);


  return Reply;


}

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library

byte Communicative::transferAndPause(const byte what){
  
  byte a = SPI.transfer (what);
  delayMicroseconds (20);
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

byte Communicative::areYouAlive(void){

   mCmd Request = {(mInstruct)IsThereData, (int)0,(float)0.0 };
   sCmd Reply;

  digitalWrite(ThisSensor.sensorChipSelect, LOW);  // enable Slave Select 
  //digitalWrite(SS, LOW);
  
  //Initial Handshake  
   transferAndPause ('?');  // add command
   byte a = transferAndPause (0x00);

  if (a == 0x06){

    //Send Request
      SPI_write(Request);
      delay(100);

    //Recieve Reply
      SPI_read(Reply);

  }else{
    //Throw error due to failed handshake
  }


  // disable Slave Select
    digitalWrite(ThisSensor.sensorChipSelect, HIGH);
    //digitalWrite(SS, HIGH);

  return a;


} 
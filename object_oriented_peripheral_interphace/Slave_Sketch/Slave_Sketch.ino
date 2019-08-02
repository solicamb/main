#include <SPI.h>
#include "SPI_Anything_Slave.h"

const Identity ThisSensorID = {50,"Test Sensor",1,10};

void setup (void)
{
   Serial.begin (115200);
  Serial.println ();
  
  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);

  // turn on SPI in slave mode
  SPCR |= _BV(SPE);

  // turn on interrupts
  SPCR |= _BV(SPIE);

}  // end of setup


// SPI interrupt routine
ISR (SPI_STC_vect)
{

  //Inital Handshake to confirm connection
    byte Ping = SPDR;
    if (Ping == '?'){
      SPI.transfer(0x06); //If the intial byte is the 'Are you alive?' byte (defined as '?') then reply with an 'ACK'==0x06
    

    //Retrieve the request from Master
      mCmd Request;
      SPI_readAnything(Request); 
  
    //Send Reply to request
      Serial.println();
      Serial.println(Request.Instruction);

//      if (Request.Instruction == WhoAreYou){
//        Serial.println("Enter Who");
//            SPI_writeAnything(ThisSensorID);
//          Serial.println("Who Are you");
//      }
//
//      if (Request.Instruction == IsThereData){
//        Serial.println("Enter Is");
//          sCmd Reply = {Yes,"This is a test message",Request.iParam +1, Request.fParam*2.0};
//          SPI_writeAnything(Reply);
//          Serial.println("Is there data");
//      }


      switch (Request.Instruction){
        case WhoAreYou:
          //Serial.println("Enter Who");
          SPI_writeAnything(ThisSensorID);
          //Serial.println("Who Are you");
          break;
         case IsThereData:
          //Serial.println("Enter Is");
          sCmd Reply = {Yes,"This is a test message",Request.iParam +1, Request.fParam*2.0};
          SPI_writeAnything(Reply);
          //Serial.println("Is there data");
          break;
      }
      
  
    }

}  // end of interrupt service routine (ISR) SPI_STC_vect

void loop (void)
{
  
}  // end of loop

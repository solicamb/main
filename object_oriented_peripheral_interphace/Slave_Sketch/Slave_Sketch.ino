#include <SPI.h>
#include "SPI_Anything_Slave.h"

const Identity ThisSensorID = {50,"Test Sensor",1,10};
Data MeasurementData;

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

  ////////////////////////////////////////////////////
  MeasurementData.NumColumns = 0;
  MeasurementData.NumRows = 0;

  for (int i = 0; i<NUMBER_OF_DATA_ROWS; i++){
    MeasurementData.RowHeadings[0][i] = '\n';
    MeasurementData.rowUnits[0][i] = '\n';

    for (int j = 0 ; j<DATA_ROW_LENGTH; j++){
      MeasurementData.DataPoints[i][j] = 0.0;
    }
  }

 //////////////////////////////////////////////////////

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
//      Serial.println();
//      Serial.println(Request.Instruction);

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
          SPI_writeAnything(ThisSensorID);
          break;
         case IsThereData:
          sCmd Reply = {Yes,"This is a test message",Request.iParam +1, Request.fParam*2.0};
          SPI_writeAnything(Reply);
          break;
         case PauseMeasurementForiParam:
          sCmd Reply1 = {ACK,"",0,0.0};
          SPI_writeAnything(Reply1);
          break;
         case RestartMeasurementProcedure:
          sCmd Reply2 = {ACK,"",0,0.0};
          SPI_writeAnything(Reply2);
          break;
         case ResetDevice:
          sCmd Reply3 = {ACK,"",0,0.0};
          SPI_writeAnything(Reply3);
          break;
         case HowManyInstructions:
          sCmd Reply4 = {ReferToInt,"",0,0.0};
          SPI_writeAnything(Reply4);
          break;
         case NextCommandPlease:
          sCmd Reply5 = {ReferToString,"",0,0.0};
          SPI_writeAnything(Reply5);
          break;
         case SendDataPlease:
          SPI_writeAnything(MeasurementData);
          break;
         case HowLongShouldIWait:
          sCmd Reply6 = {ReferToInt,"",0,0.0};
          SPI_writeAnything(Reply6);
          break;
         case BeginMeasurement:
          sCmd Reply7 = {ACK,"",0,0.0};
          SPI_writeAnything(Reply7);
          break;
         case SitRep:
          sCmd Reply8 = {ACK,"",0,0.0};
          SPI_writeAnything(Reply8);
          break;   
      }
      
  
    }

}  // end of interrupt service routine (ISR) SPI_STC_vect

void loop (void)
{
  
}  // end of loop

#include <SPI.h>
#include "SPI_Anything_Slave.h"

const Identity ThisSensorID = {50,"Test Sensor",1,10};
volatile Data MeasurementData;

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
        volatile mCmd Request;
        SPI_readAnything(Request); 
        volatile sCmd Reply;
    
      //Send Reply to request
  
         if (Request.Instruction == NextCommandPlease){
              Reply = (sCmd){ReferToString,"This is an example command",1,1.0};
              SPI_writeAnything(Reply);
        }else if (Request.Instruction == WhoAreYou){
              SPI_writeAnything(ThisSensorID);
        }else if (Request.Instruction == IsThereData){
            Reply = (sCmd){Yes,"This is a test message",Request.iParam +1, Request.fParam*2.0};
            SPI_writeAnything(Reply);
        }else if (Request.Instruction == PauseMeasurementForiParam){
            Reply = (sCmd){ACK,"",0,0.0};
            SPI_writeAnything(Reply);
        }else if (Request.Instruction == RestartMeasurementProcedure){
            Reply = (sCmd){ACK,"",0,0.0};
            SPI_writeAnything(Reply);
        }else if (Request.Instruction == ResetDevice){
            Reply = (sCmd){ACK,"",0,0.0};
            SPI_writeAnything(Reply);
        }else if (Request.Instruction == HowManyInstructions){
            Reply = (sCmd){ReferToInt,"",0,0.0};
            SPI_writeAnything(Reply);
        }else if (Request.Instruction == SendDataPlease){
  //          SPI_writeAnything(MeasurementData);
        }else if (Request.Instruction == HowLongShouldIWait){
            Reply = (sCmd){ReferToInt,"",0,0.0};
            SPI_writeAnything(Reply);
        }else if (Request.Instruction == BeginMeasurement){
            Reply = (sCmd){ACK,"",0,0.0};
            SPI_writeAnything(Reply);
        }else if (Request.Instruction == SitRep){
            Reply = (sCmd){ACK,"",0,0.0};
            SPI_writeAnything(Reply);
        }else {
          Reply = (sCmd){NAK,"COMMAND NOT RECOGNISED",-1, -1.0};
          SPI_writeAnything(Reply);
        }
      
      
  
    }

}  // end of interrupt service routine (ISR) SPI_STC_vect

void loop (void)
{
  int a = 1;
}  // end of loop

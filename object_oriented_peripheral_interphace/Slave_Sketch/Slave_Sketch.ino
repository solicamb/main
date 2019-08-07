#include <SPI.h>
#include "SPI_Anything_Slave.h"
//#include "Master.h"

const Identity ThisSensorID = {"Test Sensor",1,10};
volatile Data MeasurementData;

//volatile Master SensorMaster(50, 
//                    "Test Sensor",  
//                    (char[][SLAVE_COMMMAND_STRING_LENGTH]){"This is the first instruction",
//                    "This is the Second instruction",
//                    "This is the third instruction"}, 
//                    3, 
//                    (sInstruct[]){DisplayInstructionAndWait,
//                    DisplayInstructionAndWait,
//                    DisplayInstructionAndWait},
//                    (int[]){1000,
//                    1000,
//                    1000},
//                    (float[]){0.0,
//                    0.0,
//                    0.0}
//                    );
    

void setup (void)
{
  Serial.begin (115200);
  Serial.println ();

SPI.beginTransactionSlave(SPISettings(18000000, MSBFIRST, SPI_MODE0, DATA_SIZE_8BIT)); //STM32

//////////////////////////////////////////////////
  
//  // have to send on master in, *slave out*
//  pinMode(MISO, OUTPUT);
//
//  // turn on SPI in slave mode
//  SPCR |= _BV(SPE);
//
//  // turn on interrupts
//  SPCR |= _BV(SPIE);

  ////////////////////////////////////////////////////
  //MeasurementData.NumColumns = 0;
  MeasurementData.NumRows = 0;

  for (int i = 0; i<NUMBER_OF_DATA_ROWS; i++){
    MeasurementData.RowHeadings[0][i] = '\n';
    MeasurementData.rowUnits[0][i] = '\n';
    MeasurementData.NumColumns[i] = 5;

    for (int j = 0 ; j<5; j++){
      MeasurementData.DataPoints[i][j] = 5.5;
    }
  }

 //////////////////////////////////////////////////////

}  // end of setup


// SPI interrupt routine
ISR (SPI_STC_vect)
{

//    if (SensorMaster.Handshake()){
//      mCmd Request = SensorMaster.loadRequest();
//  
//      //Send Reply to request
//  
//         if (Request.Instruction == NextCommandPlease){
////              SensorMaster.sendReply((sInstruct)ReferToString,1,1.0,"This is an example command");
//
//              if (!SensorMaster.sendNextUserInstruction()){
//                SensorMaster.restartUserInstructionCycle();
//                SensorMaster.sendReply((sInstruct)ReferToString,"Measurement Cycle completed, restarting...");
//              }
//              
//        }else if (Request.Instruction == WhoAreYou){
//              SensorMaster.sendIdentity();
//        }else if (Request.Instruction == IsThereData){
//            SensorMaster.sendReply((sCmd){Yes,"This is a test message",Request.iParam +1, Request.fParam*2.0});
//        }else if (Request.Instruction == PauseMeasurementForiParam){
//           SensorMaster.sendReply((sInstruct)ACK);
//        }else if (Request.Instruction == RestartMeasurementProcedure){
//            SensorMaster.sendReply(ACK);
//        }else if (Request.Instruction == ResetDevice){
//            SensorMaster.sendReply(ACK);
//        }else if (Request.Instruction == HowManyInstructions){
//            SensorMaster.sendTotalNumOfInstructions();
//        }else if (Request.Instruction == SendDataPlease){
//            SensorMaster.sendData();
//        }else if (Request.Instruction == HowLongShouldIWait){
//            SensorMaster.sendReply(ReferToInt,0);
//        }else if (Request.Instruction == BeginMeasurement){
//            SensorMaster.sendReply(ACK);
//        }else if (Request.Instruction == SitRep){
//            SensorMaster.sendReply(ACK);
//        }else {
//          SensorMaster.sendReply((sCmd){NAK,"COMMAND NOT RECOGNISED",-1, -1.0});
//        }
//    }

  //Inital Handshake to confirm connection
    byte Ping = SPDR;
    if (Ping == '?'){
      SPI.transfer(0x06); //If the intial byte is the 'Are you alive?' byte (defined as '?') then reply with an 'ACK'==0x06

      //Retrieve the request from Master
        volatile mCmd Request;
        SPI_readAnything(Request); 
        volatile sCmd Reply;

      if (Request.Instruction == SendDataPlease){
            SPI_writeAnything(MeasurementData);
        }

        if (Request.Instruction == IsThereData){
            Reply = (sCmd){Yes,"This is a test message",Request.iParam +1, Request.fParam*2.0};
            SPI_writeAnything(Reply);
        }
    
      //Send Reply to request
  
//         if (Request.Instruction == NextCommandPlease){
//              Reply = (sCmd){ReferToString,"This is an example command",1,1.0};
//              SPI_writeAnything(Reply);
//        }else if (Request.Instruction == WhoAreYou){
//              SPI_writeAnything(ThisSensorID);
//        }else if (Request.Instruction == IsThereData){
//            Reply = (sCmd){Yes,"This is a test message",Request.iParam +1, Request.fParam*2.0};
//            SPI_writeAnything(Reply);
//        }else if (Request.Instruction == PauseMeasurementForiParam){
//            Reply = (sCmd){ACK,"",0,0.0};
//            SPI_writeAnything(Reply);
//        }else if (Request.Instruction == RestartMeasurementProcedure){
//            Reply = (sCmd){ACK,"",0,0.0};
//            SPI_writeAnything(Reply);
//        }else if (Request.Instruction == ResetDevice){
//            Reply = (sCmd){ACK,"",0,0.0};
//            SPI_writeAnything(Reply);
//        }else if (Request.Instruction == HowManyInstructions){
//            Reply = (sCmd){ReferToInt,"",0,0.0};
//            SPI_writeAnything(Reply);
//        }else if (Request.Instruction == SendDataPlease){
//          //  SPI_writeAnything(MeasurementData);
//        }else if (Request.Instruction == HowLongShouldIWait){
//            Reply = (sCmd){ReferToInt,"",0,0.0};
//            SPI_writeAnything(Reply);
//        }else if (Request.Instruction == BeginMeasurement){
//            Reply = (sCmd){ACK,"",0,0.0};
//            SPI_writeAnything(Reply);
//        }else if (Request.Instruction == SitRep){
//            Reply = (sCmd){ACK,"",0,0.0};
//            SPI_writeAnything(Reply);
//        }else {
//          Reply = (sCmd){NAK,"COMMAND NOT RECOGNISED",-1, -1.0};
//          SPI_writeAnything(Reply);
//        }
//      
//      
  
    }

}  // end of interrupt service routine (ISR) SPI_STC_vect

void loop (void)
{
//    float a = 1;
//  float b = 2;
//  float c = 3;
//  for (int i = 0; i < 2; i++){
//    SensorMaster.PushMeasurementVector(First,(10*a+i)/10);
//    SensorMaster.PushMeasurementVector(First,(10*b+i)/10);
//    SensorMaster.PushMeasurementVector(First,(10*c+i)/10);
//  }
}  // end of loop

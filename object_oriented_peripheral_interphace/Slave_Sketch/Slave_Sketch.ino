#include <SPI.h>
#include "SPI_Anything_Slave.h"
#include "Master.h"
#include <cstdint>

const Identity ThisSensorID = {"Test Sensor",1,10};
volatile Data MeasurementData;

//volatile Master SensorMasterGlobal;
//volatile Master SensorMaster;

volatile Master SensorMaster(50, 
                    "Test SLAVE Sensor",  
                    (char[][SLAVE_COMMMAND_STRING_LENGTH]){"This is the first instruction",
                    "This is the Second instruction",
                    "This is the third instruction"}, 
                    3, 
                    (sInstruct[]){DisplayInstructionAndWait,
                    DisplayInstructionAndWait,
                    DisplayInstructionAndWait},
                    (int[]){1000,
                    1000,
                    1000},
                    (float[]){0.0,
                    0.0,
                    0.0}
                    );

void SPI_IRQ(void){

///////////////////////////////////////////////////////////////////////////////////////////
    ////Master SensorMaster(SensorMasterGlobal);
//    
//    if (SensorMaster.Handshake()){
//      mCmd Request = SensorMaster.loadRequest();
//  
//      //Send Reply to request
//  
//         if (Request.Instruction == NextCommandPlease){
//              volatile char cmmd[] = "This is an example command";
//              SensorMaster.sendReply((sInstruct)ReferToString,1,1.0,cmmd);
//         }
//         if (!SensorMaster.sendNextUserInstruction()){
//                SensorMaster.restartUserInstructionCycle();
//                SensorMaster.sendReply((sInstruct)ReferToString,"Measurement Cycle completed, restarting...");
//        }else if (Request.Instruction == WhoAreYou){
//              SensorMaster.sendIdentity();
//        }else if (Request.Instruction == IsThereData){
//            SensorMaster.sendReply((sCmd){Yes,"This is a test message",Request.iParam +1, Request.fParam*2.0});}
////        }else if (Request.Instruction == PauseMeasurementForiParam){
////           SensorMaster.sendReply((sInstruct)ACK);
////        }else if (Request.Instruction == RestartMeasurementProcedure){
////            SensorMaster.sendReply(ACK);
////        }else if (Request.Instruction == ResetDevice){
////            SensorMaster.sendReply(ACK);
////        }else if (Request.Instruction == HowManyInstructions){
////            SensorMaster.sendTotalNumOfInstructions();
////        }else if (Request.Instruction == SendDataPlease){
////            SensorMaster.sendData();}
////        }else if (Request.Instruction == HowLongShouldIWait){
////            SensorMaster.sendReply(ReferToInt,0);
////        }else if (Request.Instruction == BeginMeasurement){
////            SensorMaster.sendReply(ACK);
////        }else if (Request.Instruction == SitRep){
////            SensorMaster.sendReply(ACK);
////        }else {
////          SensorMaster.sendReply((sCmd){NAK,"COMMAND NOT RECOGNISED",-1, -1.0});
////        }
//
//    }//End Transmission
////
////    SensorMasterGlobal = SensorMaster;

//////////////////////////////////////////////////////////////////////////////////////////////
    // Blocking call to read SPI message
//  uint8_t msg = SPI.read();
//    
//    if ((char)msg == '?'){
//      SPI.transfer(0x06); //If the intial byte is the 'Are you alive?' byte (defined as '?') then reply with an 'ACK'==0x06
      if (SensorMaster.Handshake()){ //**************
      //Retrieve the request from Master
//        mCmd Request;
//        SPI_readAnything(Request); 
        sCmd Reply;

          mCmd Request = SensorMaster.loadRequest();//*********

          
         if (Request.Instruction == NextCommandPlease){
          if (!SensorMaster.sendNextUserInstruction()){
            SensorMaster.restartUserInstructionCycle();
            volatile char cmmd[] = "Measurement Cycle completed, restarting...";
            SensorMaster.sendReply((sInstruct)ReferToString,cmmd);
          }
        }else 
        if (Request.Instruction == WhoAreYou){
              SensorMaster.sendIdentity();//SPI_writeAnything(ThisSensorID);
        }else if (Request.Instruction == IsThereData){
            if (SensorMaster.isThereData()){
              SensorMaster.sendReply((sInstruct)Yes);
            }else{
              SensorMaster.sendReply((sInstruct)No);
            }
        }else if (Request.Instruction == PauseMeasurementForiParam){
            SensorMaster.sendReply(ACK);
        }else if (Request.Instruction == RestartMeasurementProcedure){
            SensorMaster.sendReply(ACK);
        }else if (Request.Instruction == ResetDevice){
            SensorMaster.sendReply(ACK);
        }else if (Request.Instruction == HowManyInstructions){
            SensorMaster.sendTotalNumOfInstructions();
        }else if (Request.Instruction == SendDataPlease){
            SensorMaster.sendData();
        }else if (Request.Instruction == HowLongShouldIWait){
            SensorMaster.sendReply(ReferToInt,(int)100);
        }else if (Request.Instruction == BeginMeasurement){
            SensorMaster.sendReply(ACK);
        }else if (Request.Instruction == SitRep){
            SensorMaster.sendReply(ACK);
        }else {
          volatile char err[] = "COMMAND NOT RECOGNISED";
          SensorMaster.sendReply((sInstruct)NAK,cmmd);
        }

    }//End of transaction

//////////////////////////////////////////////////////////////////////////////////////
}

void setupSPI(void)
{
  // The clock value is not used
  // SPI1 is selected by default
  // MOSI, MISO, SCK and NSS PINs are set by the library
  SPI.beginTransactionSlave(SPISettings(18000000, MSBFIRST, SPI_MODE0, DATA_SIZE_8BIT));

}

void setup (void)
{
  Serial.begin (115200);
  Serial.println ();

  delay(100);

  //Initialise Master
//
//    char UserInstructions[][SLAVE_COMMMAND_STRING_LENGTH]={"This is the first instruction",
//                      "This is the Second instruction",
//                      "This is the third instruction"};
//  
//    sInstruct SlaveInstructions[]={DisplayInstructionAndWait,
//                      DisplayInstructionAndWait,
//                      DisplayInstructionAndWait};
//  
//    int iParams[]={1000,1000,1000};
//    float fParams[]={0.0,0.0,0.0};
//    
////    SensorMasterGlobal = (Master){50, 
////                      "Test Sensor",  
////                      UserInstructions, 
////                      3, 
////                      SlaveInstructions,
////                      iParams,
////                      fParams
////                      };
//
//   SensorMaster = (Master){50, 
//                      "Test Sensor",  
//                      UserInstructions, 
//                      3, 
//                      SlaveInstructions,
//                      iParams,
//                      fParams
//                      };

  //Setup SPI
      setupSPI();
     attachInterrupt(PA4 , SPI_IRQ, FALLING);
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
////  MeasurementData.NumColumns = 0;
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
//ISR (SPI_STC_vect)
//{

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
//    byte Ping = SPDR;
//    if (Ping == '?'){
//      SPI.transfer(0x06); //If the intial byte is the 'Are you alive?' byte (defined as '?') then reply with an 'ACK'==0x06
//
//      //Retrieve the request from Master
//        volatile mCmd Request;
//        SPI_readAnything(Request); 
//        volatile sCmd Reply;
//
//      if (Request.Instruction == SendDataPlease){
//            SPI_writeAnything(MeasurementData);
//        }
//
//        if (Request.Instruction == IsThereData){
//            Reply = (sCmd){Yes,"This is a test message",Request.iParam +1, Request.fParam*2.0};
//            SPI_writeAnything(Reply);
//        }
    
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
  
 //   }

//}  // end of interrupt service routine (ISR) SPI_STC_vect

void loop (void)
{
 // Serial.println("here");
//  delay(1000);
  volatile char Heading1[] = "Moisture";
  SensorMaster.setMeasurementVectorHeading(First,Heading1);
  volatile char Unit1[] = "WU";
  SensorMaster.setMeasurementVectorUnits(First,Unit1);

  volatile char Heading2[] = "pH";
  SensorMaster.setMeasurementVectorHeading(Second,Heading2);
  volatile char Unit2[] = "None";
  SensorMaster.setMeasurementVectorUnits(Second,Unit2);

  volatile char Heading3[] = "Nitrates";
  SensorMaster.setMeasurementVectorHeading(Third,Heading3);
  volatile char Unit3[] = "ppm";
  SensorMaster.setMeasurementVectorUnits(Third,Unit3);

  float a = 1;
  float b = 2;
  float c = 3;
  for (int i = 0; i < 2; i++){
    SensorMaster.PushMeasurementVector(First,(10*a+i)/10);
    SensorMaster.PushMeasurementVector(Second,(10*b+i)/10);
    SensorMaster.PushMeasurementVector(Third,(10*c+i)/10);
  }

 delay(15000);

 for (int i = 2; i < 4; i++){
    SensorMaster.PushMeasurementVector(First,(10*a+i)/10);
    SensorMaster.PushMeasurementVector(Second,(10*b+i)/10);
    SensorMaster.PushMeasurementVector(Third,(10*c+i)/10);
  }

  delay(15000);

  SensorMaster.ClearMeasurementVector(First);
  SensorMaster.PopMeasurementVector(Second);

  while(1){}
}  // end of loop

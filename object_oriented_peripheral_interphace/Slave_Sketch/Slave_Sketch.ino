#include <SPI.h>
#include "Master.h"
#include <cstdint>

//volatile Master SensorMaster(50, 
//                    "Test SLAVE Sensor",  
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
//volatile Master SensorMaster;

//void SPI_IRQ(void){
//  
//      if (SensorMaster.Handshake()){
//        
//      //Retrieve the request from Master
//          mCmd Request = SensorMaster.loadRequest();
//
//      //Switch to appropriate repsonse
//          
//         if (Request.Instruction == NextCommandPlease){
//          if (!SensorMaster.sendNextUserInstruction()){
//            SensorMaster.restartUserInstructionCycle();
//            volatile char cmmd[] = "Measurement Cycle completed, restarting...";
//            SensorMaster.sendReply((sInstruct)ReferToString,cmmd);
//          }
//        }else if (Request.Instruction == WhoAreYou){
//              SensorMaster.sendIdentity();//SPI_writeAnything(ThisSensorID);
//        }else if (Request.Instruction == IsThereData){
//            if (SensorMaster.isThereData()){
//              SensorMaster.sendReply((sInstruct)Yes);
//            }else{
//              SensorMaster.sendReply((sInstruct)No);
//            }
//        }else if (Request.Instruction == PauseMeasurementForiParam){
//            SensorMaster.sendReply(ACK);
//        }else if (Request.Instruction == RestartMeasurementProcedure){
//            SensorMaster.sendReply(ACK);
//        }else if (Request.Instruction == ResetDevice){
//            SensorMaster.sendReply(ACK);
//        }else if (Request.Instruction == HowManyInstructions){
//            SensorMaster.sendTotalNumOfInstructions();
//        }else if (Request.Instruction == SendDataPlease){
//            SensorMaster.sendData();
//        }else if (Request.Instruction == HowLongShouldIWait){
//            SensorMaster.sendReply(ReferToInt,(int)100);
//        }else if (Request.Instruction == BeginMeasurement){
//            SensorMaster.sendReply(ACK);
//        }else if (Request.Instruction == SitRep){
//            SensorMaster.sendReply(ACK);
//        }else {
//          volatile char err[] = "COMMAND NOT RECOGNISED";
//          SensorMaster.sendReply((sInstruct)NAK,err);
//        }
//
//    }//End of transaction
//
////////////////////////////////////////////////////////////////////////////////////////
//}

void RequestHandler(mCmd& Request){
  
  //Switch to appropriate repsonse
          
         if (Request.Instruction == NextCommandPlease){
          if (!SensorMaster.sendNextUserInstruction()){
            SensorMaster.restartUserInstructionCycle();
            volatile char cmmd[] = "Measurement Cycle completed, restarting...";
            SensorMaster.sendReply((sInstruct)ReferToString,cmmd);
          }
        }else if (Request.Instruction == WhoAreYou){
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
          SensorMaster.sendReply((sInstruct)NAK,err);
        }

}

void setup (void)
{
  Serial.begin (115200);
  Serial.println ();

  delay(100);
  volatile char Name[] = "Test SLAVE Sensor";
  volatile char InstructsToUser[][SLAVE_COMMMAND_STRING_LENGTH] = {"This is the first instruction",
                                                                  "This is the Second instruction",
                                                                  "This is the third instruction"} ;
  volatile sInstruct InstructsToMaster[] = {DisplayInstructionAndWait,
                                            DisplayInstructionAndWait,
                                            DisplayInstructionAndWait};
  volatile int IntegerParameters[] = {1000,
                                    1000,
                                    1000};

  volatile float FloatParameters[] = {0.0,
                                    0.0,
                                    0.0};
  SensorMaster.SETUP(50, 
                    Name,  
                    InstructsToUser, 
                    3, 
                    InstructsToMaster,
                    IntegerParameters,
                    FloatParameters
                    );

  //Setup SPI
  SensorMaster.SPISetup();
//  attachInterrupt(PA4 , SPI_IRQ, FALLING);

}  // end of setup


void loop (void)
{
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

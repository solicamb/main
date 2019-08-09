#include <SPI.h>
#include "Master.h"
#include <cstdint>

void RequestHandler(mCmd& Request){
  
  //Switch to appropriate repsonse
          
        if (Request.Instruction == NextCommandPlease){
          if (!SensorMaster.sendNextUserInstruction()){
            //SensorMaster.restartUserInstructionCycle();
            volatile char cmmd[] = "Measurement Cycle completed";
            SensorMaster.sendReply((sInstruct)DisplayInstructionAndWait,cmmd);
          }
        }else if (Request.Instruction == WhoAreYou){
              SensorMaster.sendIdentity();
        }else if (Request.Instruction == IsThereData){

            if (SensorMaster.getCurrentInstructionNumber() == 3) { //If we're on the "reading test stip" instruction

	            if (SensorMaster.isThereData()){
	              SensorMaster.sendReply((sInstruct)Yes);
	            }else{
	              SensorMaster.sendReply((sInstruct)No);
	            }

            }else SensorMaster.sendReply((sInstruct)No);

        }else if (Request.Instruction == PauseMeasurementForiParam){
            SensorMaster.sendReply(ACK);  //Not used in this script
        }else if (Request.Instruction == RestartMeasurementProcedure){
        	SensorMaster.restartUserInstructionCycle();
            SensorMaster.sendReply(ACK); //not use in this script
        }else if (Request.Instruction == ResetDevice){
            SensorMaster.sendReply(NAK); //Not implemented in this script
        }else if (Request.Instruction == HowManyInstructions){
            SensorMaster.sendTotalNumOfInstructions();
        }else if (Request.Instruction == SendDataPlease){
            SensorMaster.sendData();
        }else if (Request.Instruction == HowLongShouldIWait){
            SensorMaster.sendReply(ReferToInt,(int)100); //Not used in this script
        }else if (Request.Instruction == BeginMeasurement){
        	SensorMaster.beginMeasurement();
        }else if (Request.Instruction == SitRep){
            SensorMaster.sendReply(NAK); //Not used in thie script
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
  int SnesorID = 42;
  volatile char Name[] = "Colour Sensor";
  volatile char InstructsToUser[][SLAVE_COMMMAND_STRING_LENGTH] = {"(1)Prepare Soil solution and let settle",
                                                                  "(2)Dip strip and insert into sensor",
                                                                  "(3)Reading test strip..."} ;
  volatile sInstruct InstructsToMaster[] = {DisplayInstructionAndWaitForUser,
                                            DisplayInstructionAndWaitForUser,
                                            DisplayInstructionAndWait};
  int NumberOfInstructions = 3;

  volatile int IntegerParameters[] = {0,
                                      0,
                                      5000};

  volatile float FloatParameters[] = {0.0,
                                    0.0,
                                    0.0};
  SensorMaster.SETUP(SnesorID, 
                    Name,  
                    InstructsToUser, 
                    NumberOfInstructions, 
                    InstructsToMaster,
                    IntegerParameters,
                    FloatParameters
                    );


}  // end of setup


void loop (void)
{

	//This measurement procedure is interrupt based and so relies on the ISR to change/advance system state


	//Wait for user to intiate measurement procedure
		while(!SensorMaster.shallIStart()){}

	//Wait until the measurement instruction is reached
		while(SensorMaster.getCurrentInstructionNumber() < 2){}

	//User has now confirmed that test strip is in place and the Master has been instructe to delay for 2000ms
			//Take measurement
				//Replace with appropriate measurement procedure

			//Process Data
				//Output of processing imagined here to be a Nitrate concentration and a standard deviation, for example
				float Nitrates = 442; //Simulated output
				float StandardDev = 21; //Simulated output

			//Store data
				//Set headings and units
					volatile char Heading1[] = "Nitrates ";
					SensorMaster.setMeasurementVectorHeading(First,Heading1);
					volatile char Unit1[] = " ppm";
					SensorMaster.setMeasurementVectorUnits(First,Unit1);

					volatile char Heading2[] = "SD ";
					SensorMaster.setMeasurementVectorHeading(Second,Heading2);
					volatile char Unit2[] = " +-ppm";
					SensorMaster.setMeasurementVectorUnits(Second,Unit2);

				//clear measurement vectors (optional) and push new values

					SensorMaster.ClearMeasurementVector(First);
					SensorMaster.ClearMeasurementVector(Second);

					SensorMaster.PushMeasurementVector(First,Nitrates);	
    				SensorMaster.PushMeasurementVector(Second,StandardDev);

    //Wait for master to re-init
      while(1){}

}  // end of loop

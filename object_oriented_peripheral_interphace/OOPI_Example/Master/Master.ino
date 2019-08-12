#include <SPI.h>
#include "Sensor.h"
#define SPI1_NSS_PIN PA4 

void setup (void)
{
  Serial.begin (115200);
  Serial.println ();
  
}  // end of setup

void loop (void) //Serial.prints have been used where screen.dispays schould be and button pushes replaced with comments
{

/*

	This loop follows the following procedure which is independent of sensor type/functioning:

---->Create a sensor object
|			|
|			v
|	Wait until the Sensor is connected
|			|
|			v
|	Ask the sensor for its identity/name
|			|
|			v
|	Wait for the user to start the measurement cycle
|			|
|			v
|	Enter the intruction loop ---> Make sure sensor is still connected
|         									^			|	
|					          				|			v
|									          |			Force reset of measurement procedure on sensor
|		          							|			|
|			          						|			v
|					          				|			Ask the sensor what to do (i.e. what instruction to display to the user and wait for user respons)
|			          						|			|
|          									|			v
|         									|			Make sure sensor is still connected
|         									|			|
|					          				|			v
|					          				|			Ask sensor if there is data to be stored, load the data and store it.
|		          							|			|
|			          						|			v
|				          					|			loop until all instructions are exected
|			          						|			|
|	          								|___________^___________
|						          			            						|
|	          										            				|
|				          								            			v
|									          					            End of Measurement.
|_______________________________________Wait for user to attach new sensor/repeat measurement
							
*/												

//Instantiate Sensor object
	Sensor MySensor(SPI1_NSS_PIN);

//Wait until Sensor is connected
  Serial.println("Please connect a sensor to begin"); //Display this on screen
	while(!MySensor.areYouConnected()){
    delay(100);
	}

 Serial.println("Sensor Connected");
 delay(1000);

//Ensure Sensor measurement procedure reset 
  MySensor.issueCommand(RestartMeasurementProcedure);

//Sensor has been connected, check identity
	MySensor.updateIdentity(); //load identity from sensor
	char sName[IDENTITY_SENSOR_NAME_LENGTH];
	MySensor.getSensorName(sName); //get string name
  Serial.print("Sensor Name: ");
	Serial.print((String)sName); 
	Serial.println(" found!");
  delay(1000);
  
//Wait until user is ready to proceed
	Serial.println("Would you like to start measurement?");
	//while loop waiting for button press to confirm
		delay(2000); Serial.println("BUTTON PRESS SIMLUATED"); //<- Remove and replace with button press

	if (!MySensor.issueCommand(BeginMeasurement)){ //If sensor doesn't acknowledge the begin measurement command, restart loop
		Serial.println("Sensor not responding, check connection");
		return;
	}

//Start instruction loop
	int NumInstructions = MySensor.howManyInstructions();

	for (int i = 0; i<NumInstructions; i++){ //Loop through the measurement cycle
    
		//Ensure sensor is still connected and that Identity hasn't changed
			if(!MySensor.areYouConnected()){
				Serial.println("Sensor Disconnected");
				delay(1000);
				return;
			}

		//Get next instruction
			MySensor.loadNextCommand(); //fetch nect command from sensor and react appropriately

			if (MySensor.getCurrentCommandInstruction() == DisplayInstructionAndWait){

				//Get and print instruction to user
					char command[SLAVE_COMMMAND_STRING_LENGTH];
					MySensor.getCurrentCommandString(command);
					Serial.println((String)command);

				//Get delay time and wait
					delay(MySensor.getCurrentCommandInt());

			}else if (MySensor.getCurrentCommandInstruction() == DisplayInstructionAndWaitForUser){

				//Get and print instruction to user
					char command[SLAVE_COMMMAND_STRING_LENGTH];
					MySensor.getCurrentCommandString(command);
					Serial.println((String)command);

				//Wait for user to push button
					//While loop waiting for user to confirm
					  delay(2000); //dummy delay <- remove
						Serial.println("BUTTON PRESS SIMULATED\n");

			}else if (MySensor.getCurrentCommandInstruction() == DontDisplayAndWait){

				//Get delay time and wait
					delay(MySensor.getCurrentCommandInt());

			}else if (MySensor.getCurrentCommandInstruction() == DontDisplayAndContinue){

				//Sensor asks for a nop

			}

		//Ensure sensor is still connected and that Identity hasn't changed (Repeated here since the sensor may have asked for a large delay...)
			if(!MySensor.areYouConnected()){
				Serial.println("Sensor Disconnected");
				delay(1000);
				return;
			}

		//Check for Data
			if (MySensor.isThereData()){

				//load data
					MySensor.loadData();

				//get data dimensions
					//Data given as three arrays ('vectors'), but sensors may output single values or streams
					int vectLen[3];
					vectLen[First]= MySensor.getVectorLength(First);
					vectLen[Second] = MySensor.getVectorLength(Second);
					vectLen[Third] = MySensor.getVectorLength(Third);

				//Get single values or arrays based on dimensions
					float DataVect[DATA_ROW_LENGTH];
					MySensor.getDataVector(First,DataVect);

					for (int i = First; i < (Third+1); i++){
            
						if (vectLen[i] == 0) continue; //if data isn't there, don't try and store it

						//Get vector heading and units
							char Heading[ROW_HEADING_LENGTH];
							MySensor.getVectorHeading((MeasurementVectors)i,Heading);

							char Units[ROW_UNIT_LENGTH];
							MySensor.getVectorUnits((MeasurementVectors)i,Units);

						if (vectLen[i] == 1){ //If single value

							float DataValue = DataVect[0];

							//Write Data value, heading and units to SD card
								//Simulated here as Serial.prints
								//Sensor Identities also contain a serial number (sensorID)...
								Serial.print((String)Heading); Serial.print(DataValue); Serial.println((String)Units); delay(800);

						}else{

							//Write Data value, heading and units to SD card
								//Simulated here as Serial.prints
								Serial.print((String)Heading);
								for (int j = 0; j<vectLen[i]; j++){

									 Serial.print(DataVect[j]); Serial.println((String)Units);
								
								}
						} 

					} //end of data loop

			} // end of data if

	} //end of instruction loop

  
	Serial.println("\n\nMeasurement Procedure Compete********************");
  delay(3000);

}  // end of loop()

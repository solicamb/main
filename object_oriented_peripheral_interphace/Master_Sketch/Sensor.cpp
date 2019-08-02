#include <Arduino.h>
#include "DataSource.h"
#include "Instructor.h"
#include "SPI_InstructionSet.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

Sensor::Sensor(void) : Instructable(){

}

Sensor::Sensor(int ChipSelect): Instructable(ChipSelect){

}



// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries


int Sensor::BeginMeasurement(void){

	return issueCommand(BeginMeasurement);

}

int Sensor::PauseMeasurementForMillis(int PauseTime){

	return issueCommand(PauseMeasurementForiParam, PauseTime);

}

int Sensor::RestartMeasurement(void){

	return issueCommand(RestartMeasurementProcedure);

}


// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library
#include <Arduino.h>
#include "DataSource.h"
#include "Instructor.h"
#include "Instructable.h"
#include "Identifiable.h"
#include "Sensor.h"
#include "SPI_InstructionSet.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances



// Sensor::Sensor(const int ChipSelect): Instructable(ChipSelect), Instructor(ChipSelect), DataSource(ChipSelect), Identifiable(ChipSelect){

// }
Sensor::Sensor(const int ChipSelect): Instructable(ChipSelect){

}




// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries


int Sensor::StartMeasurement(void){

	bool Ans = issueCommand(BeginMeasurement);

	return Ans;

}

int Sensor::PauseMeasurementForMillis(int PauseTime){

	return issueCommand(PauseMeasurementForiParam, PauseTime);

}

int Sensor::RestartMeasurement(void){

	return issueCommand(RestartMeasurementProcedure);

}


// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library
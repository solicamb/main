#include <Arduino.h>
#include "Communicative.h"
#include "Instructable.h"
#include "SPI_InstructionSet.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances


Instructable::Instructable(const int ChipSelect): CommsModule(ChipSelect){

}



// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

int Instructable::issueCommand(mInstruct Command){
	mCmd Request = {Command,0,0.0};

	sCmd Reply = CommsModule.RequestReply(Request);

	if (Reply.Instruction == ACK){
		return 0;
	}else{
		return 1;
	}
}

int Instructable::issueCommand(mInstruct Command, int intParam){
	mCmd Request = {Command,intParam,0.0};

	sCmd Reply = CommsModule.RequestReply(Request);

	if (Reply.Instruction == ACK){
		return 0;
	}else{
		return 1;
	}
}

int Instructable::issueCommand(mInstruct Command, float floatParam){
	mCmd Request = {Command,0,floatParam};

	sCmd Reply = CommsModule.RequestReply(Request);

	if (Reply.Instruction == ACK){
		return 0;
	}else{
		return 1;
	}
}

int Instructable::issueCommand(mInstruct Command, int intParam, float floatParam){
	mCmd Request = {Command,intParam,floatParam};

	sCmd Reply = CommsModule.RequestReply(Request);

	if (Reply.Instruction == ACK){
		return 0;
	}else{
		return 1;
	}
}

bool Instructable::areYouConnected(void){
	return CommsModule.isPeripheralConnected();
}


// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library
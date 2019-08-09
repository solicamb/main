#include <Arduino.h>
#include "Instructable.h"
#include "Instructor.h"
#include "SPI_InstructionSet.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances


Instructor::Instructor(const int ChipSelect): CommsModule(ChipSelect){
	CurrentCommand.Instruction = NAK;
	CurrentCommand.sParam[0] = '\n';
	CurrentCommand.iParam = 0;
	CurrentCommand.fParam = 0.0;
}



// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries


int Instructor::howManyInstructions(void){
	mCmd Request = {(mInstruct)HowManyInstructions,0,0.0};
	sCmd Reply = CommsModule.RequestReply(Request);
	return Reply.iParam;
}


int Instructor::howLongShouldIWait(void){
	mCmd Request = {(mInstruct)HowLongShouldIWait,0,0.0};
	sCmd Reply = CommsModule.RequestReply(Request);
	return Reply.iParam;
}

void Instructor::loadNextCommand(void){
	 mCmd Request = {(mInstruct)NextCommandPlease,0,0.0};
	// sCmd Reply = CommsModule.RequestReply(Request);
	// CurrentCommand = Reply;
	//return CurrentCommand;
	//mCmd Request = {(mInstruct)IsThereData,0,0.0};
	sCmd Reply = CommsModule.RequestReply(Request);
	CurrentCommand = Reply;
}

void Instructor::getCurrentCommandString(char Instruction[SLAVE_COMMMAND_STRING_LENGTH]){
	for (int i = 0; i < SLAVE_COMMMAND_STRING_LENGTH; i++){
		Instruction[i] = CurrentCommand.sParam[i];
		if (CurrentCommand.sParam[i] == '\n') break;
	}
}

int Instructor::getCurrentCommandInt(void){
	return CurrentCommand.iParam;
}

float Instructor::getCurrentCommandFloat(void){
	return CurrentCommand.fParam;
}

sInstruct Instructor::getCurrentCommandInstruction(void){
	return CurrentCommand.Instruction;
}

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library
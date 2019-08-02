#include <Arduino.h>
#include "Instructable.h"
#include "Instructor.h"
#include "SPI_InstructionSet.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

Instructor::Instructor(void) : Communicative(){
	CurrentCommand.Instruction = NAK;
	CurrentCommand.sParam[0] = '\n';
	CurrentCommand.iParam = 0;
	CurrentCommand.fParam = 0.0;
}

Instructor::Instructor(int ChipSelect): Communicative(ChipSelect){
	CurrentCommand.Instruction = NAK;
	CurrentCommand.sParam[0] = '\n';
	CurrentCommand.iParam = 0;
	CurrentCommand.fParam = 0.0;
}



// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries


int Instructor::howManyInstructions(void){
	mCmd Request = {(mInstruct)HowManyInstructions,0,0.0};
	sCmd Reply = RequestReply(Request);
	return Reply.iParam;
}


int Instructor::howLongShouldIWait(void){
	mCmd Request = {(mInstruct)HowLongShouldIWait,0,0.0};
	sCmd Reply = RequestReply(Request);
	return Reply.iParam;
}

sCmd Instructor::loadNextCommand(void){
	mCmd Request = {(mInstruct)NextCommandPlease,0,0.0};
	CurrentCommand = RequestReply(Request);
	return CurrentCommand;
}

void Instructor::getCurrentCommandString(char[128] Instruction){
	for (int i = 0; i < 128; i++){
		Instruction[i] = CurrentCommand.sParam[i];
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
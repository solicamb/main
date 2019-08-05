#include <Arduino.h>
#include "Instructable.h"
#include "DataSource.h"
#include "SPI_InstructionSet.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances


DataSource::DataSource(const int ChipSelect): CommsModule(ChipSelect){

	CurrentData.NumColumns = 0;
	CurrentData.NumRows = 0;

	for (int i = 0; i<NUMBER_OF_DATA_ROWS; i++){
		CurrentData.RowHeadings[0][i] = '\n';
		CurrentData.rowUnits[0][i] = '\n';

		for (int j = 0 ; j<DATA_ROW_LENGTH; j++){
			CurrentData.DataPoints[i][j] = 0.0;
		}
	}

}



// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

bool DataSource::isThereData(void){
	mCmd Request = {(mInstruct)IsThereData,0,0.0};
	sCmd Reply = CommsModule.RequestReply(Request);

	if (Reply.Instruction == Yes){
		return true;
	}else{
		return false;
	}
}

Data DataSource::loadData(void){
	mCmd Request = {(mInstruct)SendDataPlease,0,0.0};
	CurrentData = CommsModule.RequestData(Request);
	return CurrentData;
}

int DataSource::getNumberOfDataColumns(void){
	return CurrentData.NumColumns;
}

int DataSource::getNumberOfDataRows(void){
	return CurrentData.NumRows;
}

void DataSource::getRowHeadings(char Headings[NUMBER_OF_DATA_ROWS][ROW_HEADING_LENGTH]){

	for (int i = 0; i<NUMBER_OF_DATA_ROWS; i++){
		
		for(int j=0; j< ROW_HEADING_LENGTH; j++){

			Headings[i][j] = CurrentData.RowHeadings[i][j];

		}
	}
}

void DataSource::getRowUnits(char Units[NUMBER_OF_DATA_ROWS][ROW_UNIT_LENGTH]){

	for (int i = 0; i<NUMBER_OF_DATA_ROWS; i++){
		
		for(int j=0; j< ROW_UNIT_LENGTH; j++){

			Units[i][j] = CurrentData.rowUnits[i][j];

		}
	}
}

void DataSource::getDataArray(float DataVals[NUMBER_OF_DATA_ROWS][DATA_ROW_LENGTH]){

	for (int i = 0; i<NUMBER_OF_DATA_ROWS; i++){
		
		for(int j=0; j< DATA_ROW_LENGTH; j++){

			DataVals[i][j] = CurrentData.DataPoints[i][j];

		}
	}

}

float DataSource::getValueOne(void){
	return CurrentData.DataPoints[0][0];
}

float DataSource::getValueTwo(void){
	return CurrentData.DataPoints[1][0];
}

float DataSource::getValueThree(void){
	return CurrentData.DataPoints[2][0];
}


// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library
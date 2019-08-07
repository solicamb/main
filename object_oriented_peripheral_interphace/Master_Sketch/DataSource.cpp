#include <Arduino.h>
#include "Instructable.h"
#include "DataSource.h"
#include "SPI_InstructionSet.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances


DataSource::DataSource(const int ChipSelect): CommsModule(ChipSelect){

	//CurrentData.NumColumns = 0;
	CurrentData.NumRows = 0;

	for (int i = 0; i<NUMBER_OF_DATA_ROWS; i++){
		CurrentData.RowHeadings[i][0] = '\n';
		CurrentData.rowUnits[i][0] = '\n';
		CurrentData.NumColumns[i] = 0;

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

int DataSource::getNumberOfDataColumns(const MeasurementVectors VectorNumber){
	return CurrentData.NumColumns[VectorNumber];
}

int DataSource::getNumberOfDataRows(void){
	return CurrentData.NumRows;
}

void DataSource::getRowHeadings(char Headings[NUMBER_OF_DATA_ROWS][ROW_HEADING_LENGTH]){

	for (int i = 0; i<NUMBER_OF_DATA_ROWS; i++){
		
		for(int j=0; j< ROW_HEADING_LENGTH; j++){

			Headings[i][j] = CurrentData.RowHeadings[i][j];

			if ('\n' ==  CurrentData.RowHeadings[i][j]) break;

		}
	}
}

void DataSource::getRowUnits(char Units[NUMBER_OF_DATA_ROWS][ROW_UNIT_LENGTH]){

	for (int i = 0; i<NUMBER_OF_DATA_ROWS; i++){
		
		for(int j=0; j< ROW_UNIT_LENGTH; j++){

			Units[i][j] = CurrentData.rowUnits[i][j];

			if ('\n' == CurrentData.rowUnits[i][j]) break;

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

void DataSource::getDataVector(const MeasurementVectors VectorNumber, float DataVect[DATA_ROW_LENGTH]){

	switch (VectorNumber){

		case First:
			for (int i = 0; i < CurrentData.NumColumns[First]; i++){
				DataVect[i] = CurrentData.DataPoints[First][i];
			}
			break;

		case Second:
			for (int i = 0; i < CurrentData.NumColumns[Second]; i++){
				DataVect[i] = CurrentData.DataPoints[Second][i];
			}
			break;

		case Third:
			for (int i = 0; i < CurrentData.NumColumns[Third]; i++){
				DataVect[i] = CurrentData.DataPoints[Third][i];
			}
			break;
	}

}

int DataSource::getVectorLength(const MeasurementVectors VectorNumber){
	return CurrentData.NumColumns[VectorNumber];
}

 void DataSource::getVectorHeading(const MeasurementVectors VectorNumber, char Heading[ROW_HEADING_LENGTH]){

 	switch (VectorNumber){

 		case First:
 			for (int i = 0; i < ROW_HEADING_LENGTH; i++){
 				Heading[i] = CurrentData.RowHeadings[First][i];
 				if ('\n' == CurrentData.RowHeadings[First][i]) break;
 			}

 		case Second:
			for (int i = 0; i < ROW_HEADING_LENGTH; i++){
				Heading[i] = CurrentData.RowHeadings[Second][i];
				if ('\n' == CurrentData.RowHeadings[Second][i]) break;
 			}

 		case Third:
 			for (int i = 0; i < ROW_HEADING_LENGTH; i++){
				Heading[i] = CurrentData.RowHeadings[Third][i];
				if ('\n' == CurrentData.RowHeadings[Third][i]) break;
 			}
 	}

 }

 void DataSource::getVectorUnits(const MeasurementVectors VectorNumber, char Units[ROW_UNIT_LENGTH]){

 	switch (VectorNumber){

 		case First:
 			for (int i = 0; i < ROW_UNIT_LENGTH; i++){
 				Units[i] = CurrentData.rowUnits[First][i];
 				if ('\n' == CurrentData.rowUnits[First][i]) break;
 			}

 		case Second:
			for (int i = 0; i < ROW_UNIT_LENGTH; i++){
				Units[i] = CurrentData.rowUnits[Second][i];
				if ('\n' == CurrentData.rowUnits[Second][i]) break;
 			}

 		case Third:
 			for (int i = 0; i < ROW_UNIT_LENGTH; i++){
				Units[i] = CurrentData.rowUnits[Third][i];
				if ('\n' == CurrentData.rowUnits[Third][i]) break;
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
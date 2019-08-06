
#include <Arduino.h>
#include "Master.h"
#include "SPI_InstructionSet.h"
#include <SPI.h>

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

  Master(const int SensorIDNumber, const char SensorName[], const int SensorNameLength, const char InstructionSet[][SLAVE_COMMMAND_STRING_LENGTH], const int NumberOfInstructions, const sInstruct MasterInstructionSet[]){

  //Initialise Identity
    ThisSensorID.SensorID = SensorIDNumber;
    ThisSensorID.namelength = SensorNameLength;
    ThisSensorID.sensorChipSelect = 0;

    for (int i =0; i< SensorNameLength; i++){
      ThisSensorID.SensorName[i] = SensorName[i];
    }

  //Initialise User Instruction Set
    UserInstructionSet.NumOfInstructions = NumberOfInstructions;
    UserInstructionSet.InstructionCounter = 0;

    for (int i = 0; i<NumberOfInstructions; i++){

      UserInstructionSet.MasterInstructionSet[i] = MasterInstructionSet[i];

      for (int j = 0; j<SLAVE_COMMMAND_STRING_LENGTH;j++){
        UserInstructionSet.InstructionSet[i][j] = InstructionSet[i][j];
        if (InstructionSet[i][j] == '\n') break;
      }
    }

  //Initialise Data
    //MeasurementData.NumColumns = 0;
    MeasurementData.NumRows = 0;

    for (int i = 0; i<NUMBER_OF_DATA_ROWS; i++){
      MeasurementData.RowHeadings[i][0] = '\n';
      MeasurementData.rowUnits[i][0] = '\n';
      MeasurementData.NumColumns[i] = 0;

      for (int j = 0 ; j<DATA_ROW_LENGTH; j++){
        MeasurementData.DataPoints[i][j] = 0.0;
      }
    }

  //Setup Slave SPI
    SPISetup();

}

void Master::SPISetup(){

   // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);

  // turn on SPI in slave mode
  SPCR |= _BV(SPE);

  // turn on interrupts
  SPCR |= _BV(SPIE);
}

Master::~Master(void){
  //SPI.end();
}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries
  //Communications Interface
      bool Master::Handshake(void){
        byte Ping = SPDR;
        if (Ping == '?'){
          SPI.transfer(0x06);
          return true;
        }else{
          return false;
        }
      }

      mCmd Master::loadRequest(void){
        SPI_readAnything(CurrentRequest);
        return CurrentRequest;
      }

      mInstruct Master::getCurrentInstruction(void){
        return CurrentRequest.Instruction;
      }

      int getCurrentInstructionIntParameter(void){
        return CurrentRequest.iParam;
      }

      float getCurrentInstructionFloatParameter(void){
        return CurrentRequest.fParam;
      }

      void Master::sendReply(const sCmd Reply){
        SPI_write(Reply);
      }

      void Master::sendReply(const sInstruct Instruction, const char InstructionString[SLAVE_COMMMAND_STRING_LENGTH]){
        sCmd Reply = {Instruction,"",0,0.0};

        for (int i = 0; i<SLAVE_COMMMAND_STRING_LENGTH; i++){
          Reply.sParam[i] = InstructionString[i];
          if (InstructionString[i] == '\n') break;
        }
      
        SPI_write(Reply);

      }

      void Master::sendReply(const sInstruct Instruction, const int iParam){
      
        SPI_write((sCmd){Instruction,"",iParam,0.0});
      
      }

      void Master::sendReply(const sInstruct Instruction, const float fParam){

        SPI_write((sCmd){Instruction,"",0,fParam});

      }

      void Master::sendReply(const sInstruct Instruction, const int iParam, const int fParam){

        SPI_write((sCmd){Instruction,"",iParam,fParam});

      }

      void Master::sendReply(const sInstruct Instruction, const int iParam, const char InstructionString[SLAVE_COMMMAND_STRING_LENGTH]){

        sCmd Reply = {Instruction,"",iParam,0.0};

        for (int i = 0; i<SLAVE_COMMMAND_STRING_LENGTH; i++){
          Reply.sParam[i] = InstructionString[i];
          if (InstructionString[i] == '\n') break;
        }

        SPI_write(Reply);

      }
      
      void Master::sendReply(const sInstruct Instruction, const float fParam, const char InstructionString[SLAVE_COMMMAND_STRING_LENGTH]){

        sCmd Reply = {Instruction,"",0,fParam};

        for (int i = 0; i<SLAVE_COMMMAND_STRING_LENGTH; i++){
          Reply.sParam[i] = InstructionString[i];
          if (InstructionString[i] == '\n') break;
        }

        SPI_write(Reply);

      }

      void Master::sendReply(const sInstruct Instruction, const int iParam, const float fParam, const char InstructionString[SLAVE_COMMMAND_STRING_LENGTH]){


      sCmd Reply = {Instruction,"",iParam,fParam};

        for (int i = 0; i<SLAVE_COMMMAND_STRING_LENGTH; i++){
          Reply.sParam[i] = InstructionString[i];
          if (InstructionString[i] == '\n') break;
        }

        SPI_write(Reply);

      }


      void Master::sendData(void){
        SPI_write(MeasurementData);
      }

      void Master::sendIdentity(void){
        SPI_write(ThisSensorID);
      }

    //Data handling interface
      bool Master::PushMeasurementVector(const MeasurementVectors VectorNumber, const float Measurement){

        switch (VectorNumber){

          case First:
            if (MeasurementData.NumColumns[First] == DATA_ROW_LENGTH) return false;
            MeasurementData.DataPoints[First][MeasurementData.NumColumns] = Measurement;
            MeasurementData.NumColumns[First]++;
            break;

          case Second:
            if (MeasurementData.NumColumns[Second] == DATA_ROW_LENGTH) return false;
            MeasurementData.DataPoints[Second][MeasurementData.NumColumns] = Measurement;
            MeasurementData.NumColumns[Second]++;
            break;

          case Third:
            if (MeasurementData.NumColumns[Third] == DATA_ROW_LENGTH) return false;
            MeasurementData.DataPoints[Third][MeasurementData.NumColumns] = Measurement;
            MeasurementData.NumColumns[Third]++;
            break;

        }

        return true;

      }

      bool Master::PopMeasurementVector(const MeasurementVectors VectorNumber){

        switch (VectorNumber){

          case First:
            if (MeasurementData.NumColumns[First] == 0) return false;
            MeasurementData.NumColumns[First]--;
            break;

          case Second:
            if (MeasurementData.NumColumns[Second] == 0) return false;
            MeasurementData.NumColumns[Second]--;
            break;

          case Third:
            if (MeasurementData.NumColumns[Third] == 0) return false;
            MeasurementData.NumColumns[Third]--;
            break;

        }

        return true;

      }

      void Master::ClearMeasurementVector(const MeasurementVectors VectorNumber){

        switch (VectorNumber){

          case First:
            MeasurementData.NumColumns[First] = 0;
            break;

          case Second:
            MeasurementData.NumColumns[Second] = 0;
            break;

          case Third:
            MeasurementData.NumColumns[Third] = 0;
            break;

        }

      }

      void Master::setMeasurementVectorHeading(const MeasurementVectors VectorNumber, const char Heading[ROW_HEADING_LENGTH]){

        switch (VectorNumber){

          case First:
            for (int i =0; i<ROW_HEADING_LENGTH; i++){
              MeasurementData.RowHeadings[First][i] = Heading[i];
              if (Heading[i] == '\n') break;
            }
            break;

          case Second:
            for (int i =0; i<ROW_HEADING_LENGTH; i++){
              MeasurementData.RowHeadings[Second][i] = Heading[i];
              if (Heading[i] == '\n') break;
            }
            break;

          case Third:
            for (int i =0; i<ROW_HEADING_LENGTH; i++){
              MeasurementData.RowHeadings[Third][i] = Heading[i];
              if (Heading[i] == '\n') break;
            }
            break;

        }

      }

      void Master::setMeasurementVectorUnits(const MeasurementVectors VectorNumber, const char Units[ROW_UNIT_LENGTH]){

        switch (VectorNumber){

          case First:
            for (int i =0; i<ROW_UNIT_LENGTH; i++){
              MeasurementData.rowUnits[First][i] = Units[i];
              if (Units[i] == '\n') break;
            }
            break;

          case Second:
            for (int i =0; i<ROW_UNIT_LENGTH; i++){
              MeasurementData.rowUnits[Second][i] = Units[i];
              if (Units[i] == '\n') break;
            }
            break;

          case Third:
            for (int i =0; i<ROW_UNIT_LENGTH; i++){
              MeasurementData.rowUnits[Third][i] = Units[i];
              if (Units[i] == '\n') break;
            }
            break;

      }

      bool Master::isThereData(void){

        if ((MeasurementData.NumColumns[First] > 0) || (MeasurementData.NumColumns[Second] > 0) ||(MeasurementData.NumColumns[Third] > 0)){
          return true;
        } else{
          return false;
        }
      }

    //User Instruction Interface
      void Master::sendTotalNumOfInstructions(void){
        sendReply((sInstruct)ReferToInt,UserInstructionSet.NumOfInstructions);
      }

      int Master::getCurrentInstructionNumber(void){
        return UserInstructionSet.InstructionCounter;
      }

      void Master::sendNextUserInstruction(void){
        UserInstructionSet.InstructionCounter++;
        int Counter = UserInstructionSet.InstructionCounter;
        sendReply(UserInstructionSet.MasterInstructionSet[Counter],UserInstructionSet.InstructionSet[Counter]);
      }

      void Master::resendCurrentUserInstruction(void){
        int Counter = UserInstructionSet.InstructionCounter;
        sendReply(UserInstructionSet.MasterInstructionSet[Counter],UserInstructionSet.InstructionSet[Counter]);
      }

      void Master::restartUserInstructionCycle(void){
        UserInstructionSet.InstructionCounter = 0;
      }


// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library

template <typename T> unsigned int Master::SPI_write (const T& value){
  const byte * p = (const byte*) &value;
    unsigned int i;
    for (i = 0; i < sizeof value; i++)
          SPI.transfer(*p++);
    return i;
}


template <typename T> unsigned int Master::SPI_read(T& value){
  byte * p = (byte*) &value;
    unsigned int i;
    for (i = 0; i < sizeof value; i++)
          *p++ = SPI.transfer (0);
    return i;
}



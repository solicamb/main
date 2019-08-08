
#include <Arduino.h>
#include "Master.h"
#include "SPI_InstructionSet.h"
#include <SPI.h>
#include "SPI_Anything_Slave.h"

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

  Master::Master(){
  //   CurrentRequest = (mCmd){SitRep,0,0.0};

  //   //Initialise Identity
  //   ThisSensorID.sensorID = 0;
  //   ThisSensorID.sensorChipSelect = 0;

  //   for (int i =0; i< IDENTITY_SENSOR_NAME_LENGTH; i++){
  //     ThisSensorID.SensorName[i] = '\n';
  //   }

  // //Initialise User Instruction Set
  //   UserInstructionSet.NumOfInstructions = 0;
  //   UserInstructionSet.InstructionCounter = 0;

  //   for (int i = 0; i<MAX_USER_INSTRUCTION_NUMBER; i++){

  //     UserInstructionSet.MasterInstructionSet[i] = NAK;
  //     UserInstructionSet.iParams[i] = 0;
  //     UserInstructionSet.fParams[i] = 0.0;

  //     for (int j = 0; j<SLAVE_COMMMAND_STRING_LENGTH;j++){
  //       UserInstructionSet.InstructionSet[i][j] = '\n';
  //     }
  //   }

  // //Initialise Data
  //   //MeasurementData.NumColumns = 0;
  //   MeasurementData.NumRows = 0;

  //   for (int i = 0; i<NUMBER_OF_DATA_ROWS; i++){
  //     MeasurementData.RowHeadings[i][0] = '\n';
  //     MeasurementData.rowUnits[i][0] = '\n';
  //     MeasurementData.NumColumns[i] = 0;

  //     for (int j = 0 ; j<DATA_ROW_LENGTH; j++){
  //       MeasurementData.DataPoints[i][j] = 0.0;
  //     }
  //   }

  //Setup Slave SPI
    //SPISetup();
  }

  Master::Master(const int SensorIDNumber, const char SensorName[], const char InstructionSet[][SLAVE_COMMMAND_STRING_LENGTH], const int NumberOfInstructions, const sInstruct MasterInstructionSet[], const int intParams[], const float floatParams[]){

  //Initialise Identity
    ThisSensorID.sensorID = SensorIDNumber;
    ThisSensorID.sensorChipSelect = 0;

    for (int i =0; i< IDENTITY_SENSOR_NAME_LENGTH; i++){
      ThisSensorID.SensorName[i] = SensorName[i];
      if ('\n' == SensorName[i]) break;
    }

  //Initialise User Instruction Set
    UserInstructionSet.NumOfInstructions = NumberOfInstructions;
    UserInstructionSet.InstructionCounter = 0;

    for (int i = 0; i<NumberOfInstructions; i++){

      UserInstructionSet.MasterInstructionSet[i] = MasterInstructionSet[i];
      UserInstructionSet.iParams[i] = intParams[i];
      UserInstructionSet.fParams[i] = floatParams[i];

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
    //SPISetup();

}

 void Master::SETUP(const int SensorIDNumber, volatile char SensorName[], volatile char InstructionSet[][SLAVE_COMMMAND_STRING_LENGTH], const int NumberOfInstructions, volatile sInstruct MasterInstructionSet[], volatile int intParams[], volatile float floatParams[]) volatile{
    //Initialise Identity
    ThisSensorID.sensorID = SensorIDNumber;
    ThisSensorID.sensorChipSelect = 0;

    for (int i =0; i< IDENTITY_SENSOR_NAME_LENGTH; i++){
      ThisSensorID.SensorName[i] = SensorName[i];
      if ('\n' == SensorName[i]) break;
    }

  //Initialise User Instruction Set
    UserInstructionSet.NumOfInstructions = NumberOfInstructions;
    UserInstructionSet.InstructionCounter = 0;

    for (int i = 0; i<NumberOfInstructions; i++){

      UserInstructionSet.MasterInstructionSet[i] = MasterInstructionSet[i];
      UserInstructionSet.iParams[i] = intParams[i];
      UserInstructionSet.fParams[i] = floatParams[i];

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

  //Setup SPI and interrup

    SPISetup();
    
 }


void Master::SPISetup() volatile{

  //  // have to send on master in, *slave out*
  // pinMode(MISO, OUTPUT);

  // // turn on SPI in slave mode
  // SPCR |= _BV(SPE);

  // // turn on interrupts
  // SPCR |= _BV(SPIE);

   SPI.beginTransactionSlave(SPISettings(18000000, MSBFIRST, SPI_MODE0, DATA_SIZE_8BIT));
   attachInterrupt(PA4 , SPI_IRQ, FALLING);

}

Master::~Master(void){
  //SPI.end();
}

Master::Master(volatile const Master& rhs){
  Serial.println("Copy");
  Serial.println(millis());
  this->CurrentRequest = rhs.CurrentRequest;
  this->ThisSensorID = rhs.ThisSensorID;
  this->MeasurementData = rhs.MeasurementData;
  this->UserInstructionSet = rhs.UserInstructionSet;;
}


// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries
  //Communications Interface
      bool Master::Handshake(void) volatile{
        // byte Ping = SPDR;
        uint8_t Ping = SPI.read();
        if (Ping == '?'){
          SPI.transfer(0x06);
          return true;
        }else{
          return false;
        }
      }

      mCmd Master::loadRequest(void) volatile{
        SPI_read(CurrentRequest);
        return CurrentRequest;
      }

      mInstruct Master::getCurrentInstruction(void) volatile{
        return CurrentRequest.Instruction;
      }

      int Master::getCurrentInstructionIntParameter(void) volatile{
        return CurrentRequest.iParam;
      }

      float Master::getCurrentInstructionFloatParameter(void) volatile{
        return CurrentRequest.fParam;
      }

      void Master::sendReply(const sCmd Reply) volatile{
        // SPI_write(Reply);
        SPI_writeAnything(Reply);
      }

      void Master::sendReply(const sInstruct Instruction) volatile{
        sCmd Reply = {Instruction,"",0,0.0};
      
        SPI_write(Reply);
      }

      void Master::sendReply(const sInstruct Instruction, volatile char InstructionString[SLAVE_COMMMAND_STRING_LENGTH]) volatile{
        sCmd Reply = {Instruction,"",0,0.0};

        for (int i = 0; i<SLAVE_COMMMAND_STRING_LENGTH; i++){
          Reply.sParam[i] = InstructionString[i];
          if (InstructionString[i] == '\n') break;
        }
      
        SPI_write(Reply);

      }

      void Master::sendReply(const sInstruct Instruction, const int iParam) volatile{
      
        SPI_write((sCmd){Instruction,"",iParam,0.0});
      
      }

      void Master::sendReply(const sInstruct Instruction, const float fParam) volatile{

        SPI_write((sCmd){Instruction,"",0,fParam});

      }

      void Master::sendReply(const sInstruct Instruction, const int iParam, const int fParam) volatile{

        SPI_write((sCmd){Instruction,"",iParam,fParam});

      }

      void Master::sendReply( sInstruct Instruction,  int iParam, volatile char InstructionString[SLAVE_COMMMAND_STRING_LENGTH]) volatile{

        sCmd Reply = {Instruction,"",iParam,0.0};

        for (int i = 0; i<SLAVE_COMMMAND_STRING_LENGTH; i++){
          Reply.sParam[i] = InstructionString[i];
          if (InstructionString[i] == '\n') break;
        }

        SPI_write(Reply);

      }
      
      void Master::sendReply( sInstruct Instruction,  float fParam, volatile char InstructionString[SLAVE_COMMMAND_STRING_LENGTH]) volatile{

        sCmd Reply = {Instruction,"",0,fParam};

        for (int i = 0; i<SLAVE_COMMMAND_STRING_LENGTH; i++){
          Reply.sParam[i] = InstructionString[i];
          if (InstructionString[i] == '\n') break;
        }

        SPI_write(Reply);

      }

      void Master::sendReply( sInstruct Instruction, int iParam, float fParam, volatile char InstructionString[SLAVE_COMMMAND_STRING_LENGTH]) volatile{


      sCmd Reply = {Instruction,"",iParam,fParam};

        for (int i = 0; i<SLAVE_COMMMAND_STRING_LENGTH; i++){
          Reply.sParam[i] = InstructionString[i];
          if (InstructionString[i] == '\n') break;
        }

        SPI_write(Reply);

      }


      void Master::sendData(void) volatile{
          SPI_write(MeasurementData);
      }

      void Master::sendIdentity(void) volatile{
        SPI_write(ThisSensorID);
      }

    //Data handling interface
      bool Master::PushMeasurementVector(const MeasurementVectors VectorNumber, const float Measurement) volatile{

        switch (VectorNumber){

          case First:
            if (MeasurementData.NumColumns[First] == DATA_ROW_LENGTH) return false;
            MeasurementData.DataPoints[First][MeasurementData.NumColumns[First]] = Measurement;
            MeasurementData.NumColumns[First]++;
            break;

          case Second:
            if (MeasurementData.NumColumns[Second] == DATA_ROW_LENGTH) return false;
            MeasurementData.DataPoints[Second][MeasurementData.NumColumns[Second]] = Measurement;
            MeasurementData.NumColumns[Second]++;
            break;

          case Third:
            if (MeasurementData.NumColumns[Third] == DATA_ROW_LENGTH) return false;
            MeasurementData.DataPoints[Third][MeasurementData.NumColumns[Third]] = Measurement;
            MeasurementData.NumColumns[Third]++;
            break;

        }

        return true;

      }

      bool Master::PopMeasurementVector( MeasurementVectors VectorNumber)volatile{

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

      void Master::ClearMeasurementVector( MeasurementVectors VectorNumber)volatile{

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

      void Master::setMeasurementVectorHeading( MeasurementVectors VectorNumber, volatile char Heading[ROW_HEADING_LENGTH])volatile{

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

      void Master::setMeasurementVectorUnits(MeasurementVectors VectorNumber, volatile char Units[ROW_UNIT_LENGTH])volatile{

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

    }

      bool Master::isThereData(void) volatile{

        if ((MeasurementData.NumColumns[First] > 0) || (MeasurementData.NumColumns[Second] > 0) ||(MeasurementData.NumColumns[Third] > 0)){
          return true;
        } else{
          return false;
        }
      }

    //User Instruction Interface
      void Master::sendTotalNumOfInstructions(void) volatile{
        sendReply((sInstruct)ReferToInt,UserInstructionSet.NumOfInstructions);
      }

      int Master::getCurrentInstructionNumber(void) volatile{
        return UserInstructionSet.InstructionCounter;
      }

      bool Master::sendNextUserInstruction(void) volatile{

        if (UserInstructionSet.InstructionCounter == UserInstructionSet.NumOfInstructions){
          return false;
        }

        int Counter = UserInstructionSet.InstructionCounter;
        sendReply(UserInstructionSet.MasterInstructionSet[Counter], UserInstructionSet.iParams[Counter], UserInstructionSet.fParams[Counter], UserInstructionSet.InstructionSet[Counter]);
      
        UserInstructionSet.InstructionCounter++;

        return true;
      }

      void Master::resendCurrentUserInstruction(void) volatile{
        int Counter = UserInstructionSet.InstructionCounter;
        sendReply(UserInstructionSet.MasterInstructionSet[Counter], UserInstructionSet.iParams[Counter], UserInstructionSet.fParams[Counter], UserInstructionSet.InstructionSet[Counter]);
       }

      void Master::restartUserInstructionCycle(void) volatile{
        UserInstructionSet.InstructionCounter = 0;
      }


// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library

template <typename T> unsigned int Master::SPI_write (const T& value) volatile{
  const byte * p = (const byte*) &value;
    unsigned int i;
    for (i = 0; i < sizeof value; i++)
          SPI.transfer(*p++);
    return i;
}


template <typename T> unsigned int Master::SPI_read(T& value) volatile{
  byte * p = (byte*) &value;
    unsigned int i;
    for (i = 0; i < sizeof value; i++)
          *p++ = SPI.transfer (0);
    return i;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

volatile Master SensorMaster;

void SPI_IRQ(void){
  
      if (SensorMaster.Handshake()){
        
      //Retrieve the request from Master
          mCmd Request = SensorMaster.loadRequest();

      //Call Request Handler
          RequestHandler(Request);
    }//End of transaction

//////////////////////////////////////////////////////////////////////////////////////
}
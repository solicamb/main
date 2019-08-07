
// ensure this library description is only included once
#ifndef Master_h
#define Master_h

// include types & constants of Wiring core API
#include <Arduino.h>
#include "SPI_InstructionSet.h"

const int MAX_USER_INSTRUCTION_NUMBER = 5;

typedef struct UserInstructions{
  int NumOfInstructions;
  int InstructionCounter;
  char InstructionSet[MAX_USER_INSTRUCTION_NUMBER][SLAVE_COMMMAND_STRING_LENGTH];
  sInstruct MasterInstructionSet[MAX_USER_INSTRUCTION_NUMBER];
  int iParams[MAX_USER_INSTRUCTION_NUMBER];
  float fParams[MAX_USER_INSTRUCTION_NUMBER];
};

// library interface description
class Master
{
  // user-accessible "public" interface
  public:
    Master(const int SensorIDNumber, const char SensorName[], const char InstructionSet[][SLAVE_COMMMAND_STRING_LENGTH], const int NumberOfInstructions, const sInstruct MasterInstructionSet[], const int intParams[], const float floatParams[]);
    ~Master(void);

    //Communications Interface
      bool Handshake(void);
      mCmd loadRequest(void);
      mInstruct getCurrentInstruction(void);
      int getCurrentInstructionIntParameter(void);
      float getCurrentInstructionFloatParameter(void);

      void sendReply(const sCmd Reply);
      void sendReply(const sInstruct Instruction);
      void sendReply(const sInstruct Instruction, const char InstructionString[SLAVE_COMMMAND_STRING_LENGTH]);
      void sendReply(const sInstruct Instruction, const int iParam);
      void sendReply(const sInstruct Instruction, const float fParam);
      void sendReply(const sInstruct Instruction, const int iParam, const int fParam);
      void sendReply(const sInstruct Instruction, const int iParam, const char InstructionString[SLAVE_COMMMAND_STRING_LENGTH]);
      void sendReply(const sInstruct Instruction, const float fParam, const char InstructionString[SLAVE_COMMMAND_STRING_LENGTH]);
      void sendReply(const sInstruct Instruction, const int iParam, const float fParam, const char InstructionString[SLAVE_COMMMAND_STRING_LENGTH]);

      void sendData(void);
      void sendIdentity(void);

    //Data handling interface
      bool PushMeasurementVector(const MeasurementVectors VectorNumber, const float Measurement);
      bool PopMeasurementVector(const MeasurementVectors VectorNumber);
      void ClearMeasurementVector(const MeasurementVectors VectorNumber);
      void setMeasurementVectorHeading(const MeasurementVectors VectorNumber, const char Heading[ROW_HEADING_LENGTH]);
      void setMeasurementVectorUnits(const MeasurementVectors VectorNumber, const char Units[ROW_UNIT_LENGTH]);
      bool isThereData(void);

    //User Instruction Interface
      void sendTotalNumOfInstructions(void);
      int getCurrentInstructionNumber(void);
      bool sendNextUserInstruction(void);
      void resendCurrentUserInstruction(void);
      void restartUserInstructionCycle(void);


  // library-accessible "private" interface
  private:
    void SPISetup(void);
    template <typename T> unsigned int SPI_write (const T& value);
    template <typename T> unsigned int SPI_read(T& value);

    mCmd CurrentRequest;
  
    Identity ThisSensorID;
    Data MeasurementData;
    UserInstructions UserInstructionSet;
};

#endif

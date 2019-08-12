
# File Master.h

[**File List**](files.md) **>** [**Master.h**](_master_8h.md)

[Go to the documentation of this file.](_master_8h.md) 


````cpp

// ensure this library description is only included once
#ifndef Master_h 
#define Master_h

// include types & constants of Wiring core API
#include <Arduino.h>
#include "SPI_InstructionSet.h"
#define SPI1_NSS_PIN PA4 

const int MAX_USER_INSTRUCTION_NUMBER = 5;

typedef struct UserInstructions{
  int NumOfInstructions;
  int InstructionCounter;
  char InstructionSet[MAX_USER_INSTRUCTION_NUMBER][SLAVE_COMMMAND_STRING_LENGTH];
  sInstruct MasterInstructionSet[MAX_USER_INSTRUCTION_NUMBER];
  int iParams[MAX_USER_INSTRUCTION_NUMBER];
  float fParams[MAX_USER_INSTRUCTION_NUMBER];

  UserInstructions& operator = (const volatile UserInstructions& rhs) volatile{
    this->NumOfInstructions = rhs.NumOfInstructions;
    this->InstructionCounter = rhs.InstructionCounter;

    for (int i =0; i<MAX_USER_INSTRUCTION_NUMBER;i++){
      this->iParams[i] = rhs.iParams[i];
      this->fParams[i] = rhs.fParams[i];
      this->MasterInstructionSet[i] = rhs.MasterInstructionSet[i];

      for (int j=0;j<SLAVE_COMMMAND_STRING_LENGTH;j++){
        this->InstructionSet[i][j] = rhs.InstructionSet[i][j];
      }
    }
  }

  volatile UserInstructions& operator = (const  UserInstructions& rhs) volatile{
    this->NumOfInstructions = rhs.NumOfInstructions;
    this->InstructionCounter = rhs.InstructionCounter;

    for (int i =0; i<MAX_USER_INSTRUCTION_NUMBER;i++){
      this->iParams[i] = rhs.iParams[i];
      this->fParams[i] = rhs.fParams[i];
      this->MasterInstructionSet[i] = rhs.MasterInstructionSet[i];

      for (int j=0;j<SLAVE_COMMMAND_STRING_LENGTH;j++){
        this->InstructionSet[i][j] = rhs.InstructionSet[i][j];
      }
    }
  }
};

// library interface description

class Master
{
  // user-accessible "public" interface
  public:
    Master(const int SensorIDNumber, const char SensorName[], const char InstructionSet[][SLAVE_COMMMAND_STRING_LENGTH], const int NumberOfInstructions, const sInstruct MasterInstructionSet[], const int intParams[], const float floatParams[]);
    Master(void);
    ~Master(void);
    Master(volatile const Master&);
    volatile Master& operator = (const  Master& rhs) volatile{
      this->CurrentRequest = rhs.CurrentRequest;
      this->ThisSensorID = rhs.ThisSensorID;
      this->MeasurementData = rhs.MeasurementData;
      this->UserInstructionSet = rhs.UserInstructionSet;
    }

    volatile Master& operator = (volatile const  Master& rhs) volatile{
      this->CurrentRequest = rhs.CurrentRequest;
      this->ThisSensorID = rhs.ThisSensorID;
      this->MeasurementData = rhs.MeasurementData;
      this->UserInstructionSet = rhs.UserInstructionSet;
    }


    void SETUP(const int SensorIDNumber, volatile char SensorName[], volatile char InstructionSet[][SLAVE_COMMMAND_STRING_LENGTH], const int NumberOfInstructions, volatile sInstruct MasterInstructionSet[], volatile int intParams[], volatile float floatParams[]) volatile;
    void SPISetup(void) volatile;

    //Communications Interface

      bool Handshake(void) volatile;

      mCmd loadRequest(void) volatile;
      mInstruct getCurrentInstruction(void) volatile;\
      int getCurrentInstructionIntParameter(void) volatile;
      float getCurrentInstructionFloatParameter(void) volatile;

      void sendReply(const sCmd Reply) volatile;

      void sendReply(const sInstruct Instruction) volatile;

      void sendReply(const sInstruct Instruction, volatile char InstructionString[SLAVE_COMMMAND_STRING_LENGTH]) volatile;

      void sendReply(const sInstruct Instruction, const int iParam) volatile;

      void sendReply(const sInstruct Instruction, const float fParam) volatile;

      void sendReply(const sInstruct Instruction, const int iParam, const int fParam) volatile;

      void sendReply(sInstruct Instruction, int iParam, volatile char InstructionString[SLAVE_COMMMAND_STRING_LENGTH]) volatile;

      void sendReply(sInstruct Instruction, float fParam, volatile char InstructionString[SLAVE_COMMMAND_STRING_LENGTH]) volatile;

      void sendReply( sInstruct Instruction, int iParam, float fParam, volatile char InstructionString[SLAVE_COMMMAND_STRING_LENGTH]) volatile;


      void sendData(void) volatile;

      void sendIdentity(void) volatile;

    //Data handling interface

      bool PushMeasurementVector(const MeasurementVectors VectorNumber, const float Measurement) volatile;

      bool PopMeasurementVector( MeasurementVectors VectorNumber) volatile;

      void ClearMeasurementVector(MeasurementVectors VectorNumber) volatile;

      void setMeasurementVectorHeading(MeasurementVectors VectorNumber, volatile char Heading[ROW_HEADING_LENGTH]) volatile;

      void setMeasurementVectorUnits(MeasurementVectors VectorNumber, volatile char Units[ROW_UNIT_LENGTH]) volatile;

      bool isThereData(void) volatile;

    //User Instruction Interface
      void sendTotalNumOfInstructions(void) volatile;
      int getCurrentInstructionNumber(void) volatile;

      bool sendNextUserInstruction(void) volatile;

      void resendCurrentUserInstruction(void) volatile;

      void restartUserInstructionCycle(void) volatile;

      void beginMeasurement(void) volatile;

      bool shallIStart(void) volatile;


  // library-accessible "private" interface
  private:
    template <typename T> unsigned int SPI_write (const T& value) volatile;
    template <typename T> unsigned int SPI_read(T& value) volatile;

    bool beginMeasurementYet;

    mCmd CurrentRequest;
  
    Identity ThisSensorID;
    Data MeasurementData;
    UserInstructions UserInstructionSet;
};

void SPI_IRQ(void);

void RequestHandler(mCmd& Request);

volatile extern Master SensorMaster;

#endif
````


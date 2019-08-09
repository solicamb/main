#ifndef SPIINSTRUCTIONSET_H
#define SPIINSTRUCTIONSET_H

typedef enum sInstruct{
  DisplayInstructionAndWait,
  DisplayInstructionAndWaitForUser,
  DontDisplayAndWait,
  DontDisplayAndContinue,
  ACK,
  Yes,
  No,
  NAK,
  ReferToInt,
  ReferToFloat,
  ReferToString
}; 

typedef enum mInstruct{
  PauseMeasurementForiParam,
  RestartMeasurementProcedure,
  ResetDevice,
  HowManyInstructions,
  NextCommandPlease,
  IsThereData,
  SendDataPlease,
  WhoAreYou,
  HowLongShouldIWait,
  BeginMeasurement,
  SitRep
};

const int SLAVE_COMMMAND_STRING_LENGTH = 40;

typedef struct sCmd{
  sInstruct Instruction; 
  char sParam[SLAVE_COMMMAND_STRING_LENGTH];
  int iParam;
  float fParam;

  sCmd& operator = (const volatile sCmd& rhs) volatile{
    this->Instruction = rhs.Instruction;
    this->iParam = rhs.iParam;
    this->fParam = rhs.fParam;

    for (int i = 0; i<SLAVE_COMMMAND_STRING_LENGTH;i++){
      this->sParam[i] = rhs.sParam[i];
    }

  }

  volatile sCmd& operator = (const sCmd& rhs) volatile{
    this->Instruction = rhs.Instruction;
    this->iParam = rhs.iParam;
    this->fParam = rhs.fParam;

    for (int i = 0; i<SLAVE_COMMMAND_STRING_LENGTH;i++){
      this->sParam[i] = rhs.sParam[i];
    }

  }
};

typedef struct mCmd{
  mInstruct Instruction;
  int iParam;
  float fParam;

  // mCmd(const mCmd& rhs){
  //   this->Instruction = rhs.Instruction;
  //   this->iParam = rhs.iParam;
  //   this->fParam = rhs.fParam;
  // }

  mCmd(mInstruct Instruct,int i, float f){
    this->Instruction = Instruct;
    this->iParam = i;
    this->fParam = f;
  }

  mCmd(){
    this->Instruction = SitRep;
    this->iParam = 0;
    this->fParam=0.0;
  }

  mCmd(volatile mCmd& rhs){
    this->Instruction = rhs.Instruction;
    this->iParam = rhs.iParam;
    this->fParam = rhs.fParam;
  }

  mCmd& operator = (const volatile mCmd& rhs) volatile{
    this->Instruction = rhs.Instruction;
    this->iParam = rhs.iParam;
    this->fParam = rhs.fParam;
  }

  volatile mCmd& operator = (const mCmd& rhs) volatile{
    this->Instruction = rhs.Instruction;
    this->iParam = rhs.iParam;
    this->fParam = rhs.fParam;
  }
};

const int IDENTITY_SENSOR_NAME_LENGTH = 25;

typedef struct Identity{
  char SensorName[IDENTITY_SENSOR_NAME_LENGTH];
  int sensorID;
  int sensorChipSelect;

  Identity& operator = (const volatile Identity& rhs) volatile
    {
      for (int i =0; i<IDENTITY_SENSOR_NAME_LENGTH; i++){
        this->SensorName[i] = rhs.SensorName[i];
      }

      this->sensorID = rhs.sensorID;

      this->sensorChipSelect = rhs.sensorChipSelect;
    }

    volatile Identity& operator = (const Identity& rhs) volatile
    {
      for (int i =0; i<IDENTITY_SENSOR_NAME_LENGTH; i++){
        this->SensorName[i] = rhs.SensorName[i];
      }

      this->sensorID = rhs.sensorID;

      this->sensorChipSelect = rhs.sensorChipSelect;
    }
};

const int NUMBER_OF_DATA_ROWS = 3;
const int ROW_HEADING_LENGTH = 10;
const int ROW_UNIT_LENGTH = 5;
const int DATA_ROW_LENGTH = 64;

typedef struct Data{
  int NumColumns[NUMBER_OF_DATA_ROWS];
  int NumRows;
  char RowHeadings[NUMBER_OF_DATA_ROWS][ROW_HEADING_LENGTH];
  char rowUnits[NUMBER_OF_DATA_ROWS][ROW_UNIT_LENGTH];
  float DataPoints[NUMBER_OF_DATA_ROWS][DATA_ROW_LENGTH];

  Data& operator = (const volatile Data& rhs) volatile
    {
      this->NumRows = rhs.NumRows;

      for (int i = 0; i<NUMBER_OF_DATA_ROWS; i++){
        this->NumColumns[i] = rhs.NumColumns[i];

        for(int j = 0; j<ROW_HEADING_LENGTH; j++){
          this->RowHeadings[i][j] = rhs.RowHeadings[i][j];
        }


        for(int j = 0; j<ROW_UNIT_LENGTH; j++){
          this->rowUnits[i][j] = rhs.rowUnits[i][j];
        }
        

        for(int j = 0; j<DATA_ROW_LENGTH; j++){
          this->DataPoints[i][j] = rhs.DataPoints[i][j];
        }  

      }
    }

    volatile Data& operator = (const Data& rhs) volatile
    {
      this->NumRows = rhs.NumRows;

      for (int i = 0; i<NUMBER_OF_DATA_ROWS; i++){
        this->NumColumns[i] = rhs.NumColumns[i];

        for(int j = 0; j<ROW_HEADING_LENGTH; j++){
          this->RowHeadings[i][j] = rhs.RowHeadings[i][j];
        }


        for(int j = 0; j<ROW_UNIT_LENGTH; j++){
          this->rowUnits[i][j] = rhs.rowUnits[i][j];
        }
        

        for(int j = 0; j<DATA_ROW_LENGTH; j++){
          this->DataPoints[i][j] = rhs.DataPoints[i][j];
        }  

      }
    }
};

typedef enum MeasurementVectors{
    First,
    Second,
    Third
};

#endif

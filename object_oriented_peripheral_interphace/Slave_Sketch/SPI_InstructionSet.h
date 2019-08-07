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
};

typedef struct mCmd{
  mInstruct Instruction;
  int iParam;
  float fParam;
};

const int IDENTITY_SENSOR_NAME_LENGTH = 25;

typedef struct Identity{
  char SensorName[IDENTITY_SENSOR_NAME_LENGTH];
  int sensorID;
  int sensorChipSelect;
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
};

typedef enum MeasurementVectors{
    First,
    Second,
    Third
};

#endif

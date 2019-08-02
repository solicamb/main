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

typedef struct sCmd{
  sInstruct Instruction; 
  char sParam[128];
  int iParam;
  float fParam;
};

typedef struct mCmd{
  mInstruct Instruction;
  int iParam;
  float fParam;
};

typedef struct Identity{
  int namelength;
  char SensorName[50];
  int sensorID;
  int sensorChipSelect;
};

const int NUMBER_OF_DATA_ROWS = 3;
const int ROW_HEADING_LENGTH = 20;
const int ROW_UNIT_LENGTH = 5;
const int DATA_ROW_LENGTH = 128;

typedef struct Data{
  uint8_t NumColumns;
  uint8_t NumRows;
  char RowHeadings[NUMBER_OF_DATA_ROWS][ROW_HEADING_LENGTH];
  char rowUnits[NUMBER_OF_DATA_ROWS][ROW_UNIT_LENGTH];
  float DataPoints[NUMBER_OF_DATA_ROWS][DATA_ROW_LENGTH];
};

#endif
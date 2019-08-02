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
  int namelength = 50;
  char SensorName[50];
  int sensorID;
  int sensorChipSelect;
};

typedef struct Data{
  uint8_t NumColumns;
  uint8_t NumRows;
  char RowHeadings[20][3];
  char rowUnits[3][5];
  float DataPoints[3][128];
};

#endif

// ensure this library description is only included once
#ifndef DataSource_h
#define DataSource_h

// include types & constants of Wiring core API
#include <Arduino.h>
#include "SPI_InstructionSet.h"
#include "Instructable.h"

// library interface description
class DataSource
{
  // user-accessible "public" interface
  public:

    DataSource(const int ChipSelect = SS);

    bool isThereData(void);
    Data loadData(void);

    int getNumberOfDataColumns(const MeasurementVectors VectorNumber);
    int getNumberOfDataRows(void);

    //For handling data as square array
      void getRowHeadings(char[NUMBER_OF_DATA_ROWS][ROW_HEADING_LENGTH]);
      void getRowUnits(char[NUMBER_OF_DATA_ROWS][ROW_UNIT_LENGTH]);
      void getDataArray(float[NUMBER_OF_DATA_ROWS][DATA_ROW_LENGTH]);

    //For handling data as collection of 'vectors'
      void getDataVector(const MeasurementVectors VectorNumber, float[DATA_ROW_LENGTH]);
      int getVectorLength(const MeasurementVectors VectorNumber);
      void getVectorHeading(const MeasurementVectors VectorNumber, char[ROW_HEADING_LENGTH]);
      void getVectorUnits(const MeasurementVectors VectorNumber, char[ROW_UNIT_LENGTH]);

    float getValueOne(void);
    float getValueTwo(void);
    float getValueThree(void);


  // library-accessible "private" interface
  private:
    Data CurrentData;
    Communicative CommsModule;

  };

#endif


// ensure this library description is only included once
#ifndef DataSource_h
#define DataSource_h

// include types & constants of Wiring core API
#include <Arduino.h>
#include "SPI_InstructionSet.h"
#include "Instructable.h"

// library interface description
class DataSource: virtual public Instructable
{
  // user-accessible "public" interface
  public:

    DataSource(void);
    DataSource(int ChipSelect);

    bool isThereData(void);
    Data loadData(void);

    int getNumberOfDataColumns(void);
    int getNumberOfDataRows(void);
    void getRowHeadings(char[NUMBER_OF_DATA_ROWS][ROW_HEADING_LENGTH]);
    void getRowUnits(char[NUMBER_OF_DATA_ROWS][ROW_UNIT_LENGTH]);
    void getDataArray(float[NUMBER_OF_DATA_ROWS][DATA_ROW_LENGTH]);
    float getValueOne(void);
    float getValueTwo(void);
    float getValueThree(void);


  // library-accessible "private" interface
  private:
    Data CurrentData;

#endif


// ensure this library description is only included once
#ifndef DataSource_h
#define DataSource_h

// include types & constants of Wiring core API
#include <Arduino.h>
#include "SPI_InstructionSet.h"
#include "Instructor.h"
#include "DataSource.h"

// library interface description
class Sensor: public Instructor, DataSource
{
  // user-accessible "public" interface
  public:

    Sensor(void);
    Sensor(int ChipSelect);

    int BeginMeasurement(void);
    int PauseMeasurementForMillis(int);
    int RestartMeasurement(void);

  // library-accessible "private" interface
  private:

#endif

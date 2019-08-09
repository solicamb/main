
// ensure this library description is only included once
#ifndef Sensor_h
#define Sensor_h

// include types & constants of Wiring core API
#include <Arduino.h>
#include "SPI_InstructionSet.h"
#include "Instructor.h"
#include "DataSource.h"
#include "Instructable.h"
#include "Identifiable.h"

// library interface description

 class Sensor: public Instructable, public Instructor, public DataSource, public Identifiable
{
  // user-accessible "public" interface
  public:

    Sensor(const int ChipSelect);

    int StartMeasurement(void);
    int PauseMeasurementForMillis(int);
    int RestartMeasurement(void);

  // library-accessible "private" interface
  private:

};

#endif

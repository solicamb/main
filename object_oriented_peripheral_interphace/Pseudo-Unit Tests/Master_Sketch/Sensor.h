
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
  

  // library interface description
//!  A class which models a Sensor/peripheral.
/*!
  This class models a sensor peripheral as an entity which has a queriable Identity, is a source of Data, can be issued commands and can issue a
  series of instructions in turn. In particular, a sensor is considered to perform a measurement procedure consisting of a series of steps;
  at each step, the sensor will issue instructions to the master to be acted upon and/or displayed to the user. The sensor may also require
  feedback from the user such as confirmation of the completion of an instruction, before proceeding to the next instruction in the 
  measurement procedure. While the sensor dictates the flow of the measurement procedure, a master reserves the right to initiate the 
  procedure, pause the procedure and restart the procedure.
 */
 class Sensor: public Instructable, public Instructor, public DataSource, public Identifiable
{
  // user-accessible "public" interface
  public:

    //! Constructor
    /*!
      \param ChipSelect is the Slave Select pin of the SPI peripheral in question.
    */
    Sensor(const int ChipSelect);

    //! Instruct the sensor to initiate the measurement procedure.
    /*!
      Informs the sensor to start the measurement procedure and proceed to the first instruction step.
      \return True if the sensor acknowledges the request.
    */
    int StartMeasurement(void);
    //! Instruct the sensor to pause the measurement procedure for a brief period.
    /*!
      Instructs the sensor to temporarily pause the measurement procedure for a period defined in milliseconds.
      \param int is the number of milliseconds for which the sensor is to pause.
      \return True if the sensor acknowledges the request.
    */
    int PauseMeasurementForMillis(int);
    //! Instruct the sensor to restart the measurement procedure.
    /*!
      Instructs the sensor to restart the measurement procedure. The sensor will wait revert to its initial state, waiting for 
      a StartMeasurement() command before proceeding to the first instruction in the procedure.
      \return True if the sensor acknowledges the request.
    */
    int RestartMeasurement(void);

  // library-accessible "private" interface
  private:

};

#endif

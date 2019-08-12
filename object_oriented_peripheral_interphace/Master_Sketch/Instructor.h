
// ensure this library description is only included once
#ifndef Instructor_h
#define Instructor_h

// include types & constants of Wiring core API
#include <Arduino.h>
#include "SPI_InstructionSet.h"
#include "Instructable.h"
// library interface description
//!  A class which models a Sensor/peripheral as entity which can issue instructions to the master.
/*!
  This class models a peripheral as an entity which can issue commands to the master. The premise is that a sensor peripheral
  will conduct a measurement by cycling through a number of steps. At each step the sensor may wish for the Master to perform certain
  actions, such as display a message to the user, pause for a certain period of time or wait until the user has acknowledged an instruction
  by button press. In general, the master is expected to iterate through the instruction set, loading an instruction each iteration and
  repsonding appropriately.
  i.e. follow the procedure: howManyInstructions()->start loop->loadNextCommand()->React to command->repeat until all instructions have been processed. 
*/
class Instructor
{
  // user-accessible "public" interface
  public:

    //! Constructor
    /*!
      \param ChipSelect is the Slave Select pin of the SPI peripheral in question.
    */
    Instructor(const int ChipSelect);

    //! Asks the Sensor how many instructions there are in a measurement cycle.
    /*!
      In general, the master is expected to iterate through the instrcution set.
      \return The number of instructions in a measurement cycle.
    */
    int howManyInstructions(void);
    //! Asks the sensor how long the master should pause for. Deprecated.
    /*!
      \return The duration, in milliseconds, the master should pause for.
    */
    int howLongShouldIWait(void);
    //! Fetches the next instruction issued by the sensor in its instruction cycle.
    /*!
      Fetches the next instruction from the Sensor and loads it into local memory. Instructions are issued in the sCmd type and
      are therefore consititute an element of the sInstruct instruction set, qualified by a character array (string), integer and float.
    */
    void loadNextCommand(void);
    //! Returns the character array which qualifies the instruction currently loaded into local memory as issued by the Sensor.
    /*!
      The character array (string) issued by the Sensor is generally intended to be displayed to the user, to update the user
      on the progress of the measurement procedure or instruct the user on the next step in the measurement procedure, such as
      inserting the probe into the measurement environment.
      \param char is the character array into which the instruction string is loaded.
    */
    void getCurrentCommandString(char[SLAVE_COMMMAND_STRING_LENGTH]);
    //! Returns the integer which qualifies the instruction currently loaded into local memory as issued by the Sensor.
    /*!
      The integer which qualifies the instruction issued by the sensor is generally used to either augment the information displayed 
      to the user to instruct the master as to how it should carry out the request of the slave, such as how long to pasue for.
      \return The integer which qualifies the instruction.
    */
    int getCurrentCommandInt(void);
    //! Returns the float which qualifies the instruction currently loaded into local memory as issued by the Sensor.
    /*!
      The float which qualifies the instruction issued by the sensor is generally used to either augment the information displayed 
      to the user to instruct the master as to how it should carry out the request of the slave.
    */
    float getCurrentCommandFloat(void);
    //! Returns the sinstruct object which defines the instruction currently loaded into local memory as issued by the Sensor.
    /*!
      Elements of the sInstruct type define all the potential instructions which can be issued by a Slave.
      \return The instruction issued by the slave.
    */
    sInstruct getCurrentCommandInstruction(void);

  // library-accessible "private" interface
  private:
    sCmd CurrentCommand;
    Communicative CommsModule;
};

#endif

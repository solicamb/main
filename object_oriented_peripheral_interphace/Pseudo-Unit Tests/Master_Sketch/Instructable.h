
// ensure this library description is only included once
#ifndef Instructable_h
#define Instructable_h

// include types & constants of Wiring core API
#include <Arduino.h>
#include "SPI_InstructionSet.h"
#include "Communicative.h"
// library interface description
//!  A class which models a Sensor/peripheral as entity which can recieve commands.
/*!
  This class models a peripheral as an entity which can be issued commands. The commands issued are elements of the set
  defined by the mInstruct type. Each instruction can be accompanied by and integer and/or float as required to act as
  parameters to qualify the command. For example, if the peripheral is commanded to pause for an interval, the integer
  parameter is used by the peripheral to determine the length of time for which to pause.
*/
class Instructable
{
  // user-accessible "public" interface
  public:

    //Instructable(void);
     //! A constructor
    /*!
      \param The Slave Select pin of the SPI peripheral in question.
    */
    Instructable(const int ChipSelect);

    //! Issues a command to the peripheral.
    /*!
      Sends a command which is an element of the mInstruct type.
      \param mInstruct is the command issued to the peripheral.
      \return True if the peripheral acknowledges the command.
    */
    bool issueCommand(mInstruct);
    //! Issues a command to the peripheral.
    /*!
      Sends a command which is an element of the mInstruct type qualified by an integer parameter (generally used to
      instruct on wait time or similar).
      \param mInstruct is the command issued to the peripheral and int is the integer qualifier.
      \return True if the peripheral acknowledges the command.
    */
    bool issueCommand(mInstruct, int);
    //! Issues a command to the peripheral.
    /*!
      Sends a command which is an element of the mInstruct type qualified by a float parameter.
      \param mInstruct is the command issued to the peripheral and float is the floating point qualifier.
      \return True if the peripheral acknowledges the command.
    */
    bool issueCommand(mInstruct, float);
    //! Issues a command to the peripheral.
    /*!
      Sends a command which is an element of the mInstruct type qualified by an integer parameter (generally used to
      instruct on wait time or similar) and a floating point parameter.
      \param mInstruct is the command issued to the peripheral, int is the integer qualifier and float is the floating point qualifier.
      \return True if the peripheral acknowledges the command.
    */
    bool issueCommand(mInstruct, int, float);

    //! Checks to see whether the peripheral is connected.
    /*!
      Initiates handshake and nop transaction with the sensor to ensure that it is connected and responding appropriately.
      \return True if the peripheral is connected and communicating effectively.
    */
    bool areYouConnected(void);

  // library-accessible "private" interface
  private:
    Communicative CommsModule;

};

#endif

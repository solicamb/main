
// ensure this library description is only included once
#ifndef Identifiable_h
#define Identifiable_h

// include types & constants of Wiring core API
#include <Arduino.h>
#include "SPI_InstructionSet.h"
#include "Communicative.h"
// library interface description
//!  A class which models a Sensor/peripheral as an identifiable entity
/*!
  This class models a peripheral as an identifiable entity with ID number and string name. The class allows for 
  the identity to be loaded from the peripheral and interrogated.  
*/
class Identifiable
{
  // user-accessible "public" interface
  public:

    //Instructable(void);
    //! A constructor
    /*!
      Constructor for class which loads the identity of any connected SPI peripheral into local memory.
      \param The Slave Select pin of the SPI peripheral in question.
      \sa updateIdentity.
    */
    Identifiable(const int ChipSelect);

    //! Checks to seee whether the Identity in local memory is different to the Identity advertised by peripheral.
    /*!
      \return True if the stored Identity is different than the Identity advertised by the peripheral.
      \sa Identity
    */
    bool hasIdentityChanged(void);
    //! Loads the Identity advertised by the peripheral into local memory.
    void updateIdentity(void);
    //! Gets the identity number of the attached peripheral.
    /*!
      Reports the identity number of the peripheral currently stored in local memory.
      \return The sensor ID number.
    */
    int getIDNumber(void);
    //! Gets the sensor name of the attached peripheral.
    /*!
      Reports the sensor name of the peripheral currently stored in local memory.
      \param name is the character array into which the sensor name is loaded.
    */
    void getSensorName(char name[IDENTITY_SENSOR_NAME_LENGTH]);

  // library-accessible "private" interface
  private:
    Communicative CommsModule;
    Identity ThisSensor;

};

#endif

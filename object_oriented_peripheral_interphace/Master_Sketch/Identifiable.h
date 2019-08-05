
// ensure this library description is only included once
#ifndef Identifiable_h
#define Identifiable_h

// include types & constants of Wiring core API
#include <Arduino.h>
#include "SPI_InstructionSet.h"
#include "Communicative.h"
// library interface description
class Identifiable
{
  // user-accessible "public" interface
  public:

    //Instructable(void);
    Identifiable(const int ChipSelect = SS);

    bool hasIdentityChanged(void);
    void updateIdentity(void);

  // library-accessible "private" interface
  private:
    Communicative CommsModule;
    Identity ThisSensor;

};

#endif

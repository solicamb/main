
// ensure this library description is only included once
#ifndef Communicative_h
#define Communicative_h

// include types & constants of Wiring core API
#include <Arduino.h>
#include "SPI_InstructionSet.h"
// library interface description
class Communicative
{
  // user-accessible "public" interface
  public:
    Communicative(const int CS = SS);
    ~Communicative(void);
    bool isPeripheralConnected(void);
    void setChipSelect(const int CS);

  //protected:  
    sCmd RequestReply(const mCmd);
    Identity RequestIdentity(const mCmd);
    Data RequestData(const mCmd);


  // library-accessible "private" interface
  private:
    void SPISetup(const int ChipSelect = SS);
    byte transferAndPause(const byte);
    template <typename T> unsigned int SPI_write (const T& value);
    template <typename T> unsigned int SPI_read(T& value);
    byte areYouAlive(const int ChipSelect = SS);

    int ChipSelect;
   // Identity ThisSensor;
};

#endif

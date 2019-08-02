
// ensure this library description is only included once
#ifndef Instructor_h
#define Instructor_h

// include types & constants of Wiring core API
#include <Arduino.h>
#include "SPI_InstructionSet.h"
#include "Instructable.h"
// library interface description
class Instructor: virtual public Instructable
{
  // user-accessible "public" interface
  public:

    Instructor(void);
    Instructor(int ChipSelect);

    int howManyInstructions(void);
    int howLongShouldIWait(void);
    sCmd loadNextCommand(void);
    void getCurrentCommandString(char[128]);
    int getCurrentCommandInt(void);
    float getCurrentCommandFloat(void);
    sInstruct getCurrentCommandInstruction(void);

  // library-accessible "private" interface
  private:
    sCmd CurrentCommand;
};

#endif

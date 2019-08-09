
// ensure this library description is only included once
#ifndef Instructor_h
#define Instructor_h

// include types & constants of Wiring core API
#include <Arduino.h>
#include "SPI_InstructionSet.h"
#include "Instructable.h"
// library interface description
class Instructor
{
  // user-accessible "public" interface
  public:

    Instructor(const int ChipSelect);

    int howManyInstructions(void);
    int howLongShouldIWait(void);
    void loadNextCommand(void);
    void getCurrentCommandString(char[SLAVE_COMMMAND_STRING_LENGTH]);
    int getCurrentCommandInt(void);
    float getCurrentCommandFloat(void);
    sInstruct getCurrentCommandInstruction(void);

  // library-accessible "private" interface
  private:
    sCmd CurrentCommand;
    Communicative CommsModule;
};

#endif

#include <SPI.h>
#include <Arduino.h>

template <typename T> unsigned int SPI_writeAnything (const T& value)
  {
    const byte * p = (const byte*) &value;
    unsigned int i;
    for (i = 0; i < sizeof value; i++)
          transferAndWait(*p++);
    return i;
  }  // end of SPI_writeAnything

template <typename T> unsigned int SPI_readAnything(T& value)
  {
    byte * p = (byte*) &value;
    unsigned int i;
    for (i = 0; i < sizeof value; i++)
          *p++ = transferAndWait (0);
    return i;
  }  // end of SPI_readAnything
  
  
template <typename T> unsigned int SPI_readAnything_ISR(T& value)
  {
    byte * p = (byte*) &value;
    unsigned int i;
    *p++ = SPDR;  // get first byte
    for (i = 1; i < sizeof value; i++)
          *p++ = transferAndWait (0);
    return i;
  }  // end of SPI_readAnything_ISR  

typedef enum sInstruct{
  DisplayInstructionAndWait,
  DisplayInstructionAndWaitForUser,
  DontDisplayAndWait,
  DontDisplayAndContinue,
  ACK,
  Yes,
  No,
  NAK,
  ReferToInt,
  ReferToFloat,
  ReferToString
};

typedef enum mInstruct{
  PauseMeasurementForiParam,
  RestartMeasurementProcedure,
  ResetDevice,
  HowManyInstructions,
  NextCommandPlease,
  IsThereData,
  SendDataPlease,
  WhoAreYou,
  HowLongShouldIWait,
  BeginMeasurement
};

typedef struct sCmd{
  sInstruct Instruction; 
  char sParam[128];
  int iParam;
  float fParam;
};

typedef struct mCmd{
  mInstruct Instruction;
  int iParam;
  float fParam;
};

//############################################################################################################

void setup (void)
{
  Serial.begin (115200);
  Serial.println ();
  
  digitalWrite(SS, HIGH);  // ensure SS stays high for now

  // Put SCK, MOSI, SS pins into output mode
  // also put SCK, MOSI into LOW state, and SS into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin ();

  // Slow down the master a bit
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  
}  // end of setup

byte transferAndWait (const byte what)
{
  byte a = SPI.transfer (what);
  delayMicroseconds (20);
  return a;
} // end of transferAndWait

void loop (void)
{

  byte a;
  // enable Slave Select
  digitalWrite(SS, LOW);    

  transferAndWait ('?');  // add command
  a = transferAndWait (0x00);

  ///////////////////////////////////////////////////////
  mCmd Request = {(mInstruct)IsThereData, (int)10,(float)1.5 };
  SPI_writeAnything(Request);

  delay(100);
  sCmd Reply;
  SPI_readAnything(Reply);
 
  ///////////////////////////////////////////////////////


  // disable Slave Select
  digitalWrite(SS, HIGH);

  Serial.println ("Reply From Slave");
  Serial.println (a);
  Serial.println(Reply.Instruction);
  Serial.println((String)Reply.sParam);  
  Serial.println(Reply.iParam);
  Serial.println(Reply.fParam);
  
  delay (1000);  // 1 second delay 
}  // end of loop

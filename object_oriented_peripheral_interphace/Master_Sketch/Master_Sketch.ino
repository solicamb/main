#include <SPI.h>
#include "SPI_Anything.h"

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

void loop (void)
{

   ///////////////////////////////////////////////////////
  
  digitalWrite(SS, LOW);  // enable Slave Select 
  
  //Initial Handshake  
    transferAndWait ('?');  // add command
   byte a = transferAndWait (0x00);

  //Send Request
    mCmd Request = {(mInstruct)IsThereData, (int)10,(float)1.5 };
    SPI_writeAnything(Request);
    delay(100);

 //Recieve Reply
    sCmd Reply;
    SPI_readAnything(Reply);


     // disable Slave Select
    digitalWrite(SS, HIGH);
  //////////////////////////////////////////////////////

  delay(100);
  
 ///////////////////////////////////////////////////////
  
 digitalWrite(SS, LOW);  // enable Slave Select 
  
  //Initial Handshake  
    transferAndWait ('?');  // add command
     a = transferAndWait (0x00);

  //Send Request
    mCmd Request2 = {(mInstruct)WhoAreYou, (int)2,(float)6.2 };
    SPI_writeAnything(Request2);
    delay(100);

 //Recieve Reply
      Identity Repli;
      SPI_readAnything(Repli);

     // disable Slave Select
    digitalWrite(SS, HIGH);
  //////////////////////////////////////////////////////
  


  Serial.println ("Reply From Slave");
  Serial.println (a);
  Serial.println(Reply.Instruction);
  Serial.println((String)Reply.sParam);  
  Serial.println(Reply.iParam);
  Serial.println(Reply.fParam);
  Serial.println("And");
  Serial.println((String)Repli.SensorName);
  Serial.println(Repli.sensorID);
  Serial.println(Repli.sensorChipSelect);
  
  delay (1000);  // 1 second delay 
}  // end of loop

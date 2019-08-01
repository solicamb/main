#include <SPI.h>

volatile byte command = 0;

void setup (void)
{

  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);

  // turn on SPI in slave mode
  SPCR |= _BV(SPE);

  // turn on interrupts
  SPCR |= _BV(SPIE);

}  // end of setup


// SPI interrupt routine
ISR (SPI_STC_vect)
{
  byte c = SPDR;

  if (c == '?'){
    SPI.transfer(0x06);
  }


}  // end of interrupt service routine (ISR) SPI_STC_vect

void loop (void)
{
  
}  // end of loop

// SPI full-duplex slave example
// STM32 acts as a SPI slave and reads 8 bit data frames over SPI.
// Master also gets a reply from the slave, which is a a simple count (0, 1, 2, 3)
// that is incremented each time a data frame is received.
// Serial output is here for debug

#include <SPI.h>
#include <cstdint>

void setupSPI(void)
{
  // The clock value is not used
  // SPI1 is selected by default
  // MOSI, MISO, SCK and NSS PINs are set by the library
  SPI.beginTransactionSlave(SPISettings(18000000, MSBFIRST, SPI_MODE0, DATA_SIZE_8BIT));

  //Enable interrupts
//  spi_dev * spi_d = SPI._currentSetting->spi_d;
  //spi_dev * spi_d;
  //spi_d = SPI1;
  //spi_irq_enable(SPI2,SPI_CR2_RXNEIE);
//  spi_irq_enable(SPI1,SPI_RXNE_INTERRUPT);
 //   spi_irq_enable(SPI1,SPI_RXNE_INTERRUPT);
}

uint8_t count = 0;
void SPI_IRQ(void){
    // Blocking call to read SPI message
  //uint8_t msg = SPI.transfer(++count);
  uint8_t msg = SPI.read();
  Serial.print("Received = 0b");
  Serial.print(msg, BIN);
  Serial.print(", 0x");
  Serial.print(msg, HEX);
  Serial.print(", ");
  Serial.println(msg);
}

void setup()
{
  Serial.begin(115200);
  delay(100);
  setupSPI();
  attachInterrupt(PA4 , SPI_IRQ, FALLING);
}


//uint8_t count = 0;
////extern "C" 
//extern "C" void __irq_spi1(void) {
//    // Blocking call to read SPI message
//    //uint8_t msg = SPI.transfer(++count);
//    spi_dev * spi_d;
//    uint8_t msg = (uint8)spi_rx_reg(spi_d);
////    Serial.print("Received = 0b");
////    Serial.print(msg, BIN);
////    Serial.print(", 0x");
////    Serial.print(msg, HEX);
////    Serial.print(", ");
//    Serial.print("Val: ");
//    Serial.println(msg);
//        
//}



void loop()
{
  // Blocking call to read SPI message
//  uint8_t msg = SPI.transfer(++count);
//  Serial.print("Received = 0b");
//  Serial.print(msg, BIN);
//  Serial.print(", 0x");
//  Serial.print(msg, HEX);
//  Serial.print(", ");
//  Serial.println(msg);
}

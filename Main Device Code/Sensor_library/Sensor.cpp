#include "Arduino.h"
#include "Sensor.h"
#include "SPI.h"


Sensor::Sensor(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

char Sensor::whatsensor()
{
  
  SPI.beginTransaction(SPISettings(328125, MSBFIRST, SPI_MODE0));
  digitalWrite(_pin, LOW);
  //SPI.setClockDivider(SPI_CLOCK_DIV128);
  delay(10);
  receivedbyte=SPI.transfer(0);
  delay(10);
  SPI.endTransaction();
  digitalWrite(_pin, HIGH);
  Serial.println(receivedbyte);
  if (receivedbyte <= 0x10 && receivedbyte > 0x00)
  {
	  ID='c';
	  serialnumber = int (receivedbyte);
	  return ID;
  }
  if (receivedbyte <= 0x2F && receivedbyte > 0x20)
  {
	  ID = 'm';
	  serialnumber = int (receivedbyte-0x20);
	  return ID;
  }
}

int Sensor::whatserial()
{
	return serialnumber;
}

template <typename T> unsigned int Sensor::getsensordata(T& value)
{
	
	
	byte * p = (byte*) &value;
	
	for (i=0; i<sizeof(value); i++)
	{
		*p = SPI.transfer(choice);
		
		delay(100);
		Serial.println(*p);
		p++;
		
	}
	SPI.endTransaction();	
	digitalWrite(_pin, HIGH);
	return i;
	
	
}

void Sensor::startsensing(byte a)
{
	choice = a;
	
	SPI.beginTransaction(SPISettings(328125, MSBFIRST, SPI_MODE0));
	digitalWrite(_pin, LOW);
	//SPI.setClockDivider(SPI_CLOCK_DIV128);
	SPI.transfer(choice);
	delayMicroseconds(50);
}


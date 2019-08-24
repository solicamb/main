/*Copyright (c) 2019 Sagnik Middya and Jan Heck

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Authored by Sagnik Middya and Jan Heck
*/

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

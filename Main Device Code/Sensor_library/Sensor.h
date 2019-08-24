#ifndef Sensor_h
#define Sensor_h

#include "Arduino.h"
#include "SPI.h"



class Sensor
{
  public:
	Sensor(int pin);
    char whatsensor();
	int whatserial();
	template <typename T> unsigned int getsensordata(T& value);
	void startsensing(byte a);
	
  private:
    int _pin;
	int i;
	byte receivedbyte;
	byte * p;
	float sensordata;
	byte choice;
	char ID;
	int serialnumber;
	
	
};

#endif
/*
 * Development (debugging) setup for the BluePill controlling the moisture probe
 *
 * Authors:
 *  Jan (jh2109)
 *
 */

#include <Wire.h>

// Config
#define BAUDRATE 38400   // Arduino <=> PC serial baudrate
#define DOWNSAMPLING 2000 // number of ADC readings to average per serial message

#define ADC_FULL_SCALE_VOLTAGE 4.0f // full scale ADC voltage for scaling
// TODO/NB While this will correspond to VCC, don't assume the VCC=3.3V pin will have exactly that voltage
// One measurement gave 4V when powered via USB from a PC, hence this choice
// Ultimately, we should control/know what VCC we are referencing to
#define ADC_RESOLUTION 4096 // 12 bit resolution for blue pill

// Global scope
// (none so far)

void setup() {
	// Initialise serial
  Serial.begin(BAUDRATE);
	while (!Serial){
		// nop until serial becomes available
	}

	Serial.flush();
	Serial.println();
	Serial.println("START");
}

float read_average_ADC(int pin, int n){
	// Read ADC on $pin, taking the average of $n samples, and return reading in volt
	long sum = 0;
	for (int i = 1; i <= n; i++){
		sum += analogRead(pin);
	}

	float voltage = (float)sum/n; // average
	voltage *= ADC_FULL_SCALE_VOLTAGE/ADC_RESOLUTION; // convert to volt

	return voltage;
}

void write_measurement_to_serial(char const variable_name[], float value){
	// Send a measurement to the PC via Serial in the format that the Python script expects
	// One could make an argument to take the time of sampling rather than comunication, but ignore this difference for now
	Serial.print(variable_name);
	Serial.print(";");
	Serial.print(millis());
	Serial.print(";");
	Serial.println(value);
}

void loop() {
	// Measure and report data via serial and LED display
	float voltage_PA0 = read_average_ADC(PA0, DOWNSAMPLING);
	write_measurement_to_serial("y0", voltage_PA0);

	float voltage_PA1 = read_average_ADC(PA1, DOWNSAMPLING);
	write_measurement_to_serial("y1", voltage_PA1);
		
	float voltage_PA2 = read_average_ADC(PA2, DOWNSAMPLING);
	write_measurement_to_serial("y2", voltage_PA2);
}

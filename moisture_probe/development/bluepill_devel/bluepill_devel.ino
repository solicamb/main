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
#define DOWNSAMPLING 5000 // number of ADC readings to average per serial message

#define ADC_FULL_SCALE_VOLTAGE 4.0f // full scale ADC voltage for scaling
// TODO/NB While this will correspond to VCC, don't assume the VCC=3.3V pin will have exactly that voltage
// One measurement gave 4V when powered via USB from a PC, hence this choice
// Ultimately, we should control/know what VCC we are referencing to. On the other hand, this scaling is only
// to make it more physically meaningful; we can also just think in terms of percentage of full scale
#define ADC_FULL_SCALE_VALUE 4095 // 12 bit resolution for blue pill

// Global scope variables
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
	voltage *= ADC_FULL_SCALE_VOLTAGE/ADC_FULL_SCALE_VALUE; // convert to volt

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
	// Measure and report data via serial
	float voltage_PA0 = read_average_ADC(PA0, DOWNSAMPLING);
	write_measurement_to_serial("y0", voltage_PA0);

	float voltage_PA1 = read_average_ADC(PA1, DOWNSAMPLING);
	write_measurement_to_serial("y1", voltage_PA1);
		
	float voltage_PA2 = read_average_ADC(PA2, DOWNSAMPLING);
	write_measurement_to_serial("y2", voltage_PA2);
}

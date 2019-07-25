/*
 * Development (debugging) setup for the Arduino controlling the moisture probe
 *
 * Authors:
 *  Jan (jh2109)
 *
 */

#include <Wire.h>
#include "LedControl.h"

// Config
#define BAUDRATE 38400   // Arduino <=> PC serial baudrate
#define DOWNSAMPLING 200 // number of ADC readings to average per serial message
#define LED_BRIGHTNESS 9 // 0..15
#define LED_CONTROLLER 0 // Index of LED controller to use

// Global scope
//                 pins:   DIN CLK CS  number of controllers
LedControl lc = LedControl(12, 11, 10, 1);

void setup() {
	// Initialise serial
  Serial.begin(BAUDRATE);
	while (!Serial){
		// nop until serial becomes available
	}

	Serial.flush();
	Serial.println();
	Serial.println("START");

	// Initialise 7-segment display
  lc.shutdown(LED_CONTROLLER, false);
  lc.setIntensity(LED_CONTROLLER, LED_BRIGHTNESS);
  lc.clearDisplay(LED_CONTROLLER);
}

float read_average_ADC(int pin, int n){
	// Read ADC on $pin, taking the average of $n samples, and return reading in volt
	long sum = 0;
	for (int i = 1; i <= n; i++){
		sum += analogRead(pin);
	}

	float voltage = (float)sum/n; // average
	voltage *= 5./1023; // convert to volt (5V / 0..1023 ADC levels)

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

void display_number_on_7segment(int display_position, int number, int decimal_point_position){
	// Hardcoded: number up to 9999; LED controller id 0
	// To keep this function simple, we only handle integers and are told the decimal point position explicitly
	// TODO: implement negative numbers if needed
	int unit_place, tens_place, hundreds_place, thousands_place = 0;

	// First, make sure we can actually display the number
	if (number >= 10000 or number < 0){
		// not enough space on display: show "overflow" warning
		lc.setDigit(LED_CONTROLLER, display_position + 3, 0 , false);  // O
		lc.setRow(LED_CONTROLLER,   display_position + 2, B00111110);  // V
		lc.setChar(LED_CONTROLLER,  display_position + 1, 'F', false); // F
		lc.setChar(LED_CONTROLLER,  display_position + 0, 'L', false); // L
		return;
	}

	// Next, we go through the decimal digits of the number and extract the digit to display in that decimal position
	unit_place = ((int)(number / 1) % 10);
	lc.setDigit(LED_CONTROLLER, display_position, unit_place, decimal_point_position == display_position);

	display_position++;
	if (number >= 10){
		tens_place = ((int)(number / 10) % 10);
		lc.setDigit(LED_CONTROLLER, display_position, tens_place, decimal_point_position == display_position);
	} else {
		lc.setChar(LED_CONTROLLER, display_position, ' ', decimal_point_position == display_position);
	}
 
	display_position++;
	if (number >= 100){
		hundreds_place = ((int)(number / 100) % 10);
		lc.setDigit(LED_CONTROLLER, display_position, hundreds_place, decimal_point_position == display_position);
	} else {
		lc.setChar(LED_CONTROLLER, display_position, ' ', decimal_point_position == display_position);
	}

	display_position++;
	if (number >= 1000){
		thousands_place = ((int)(number / 1000) % 10);
		lc.setDigit(LED_CONTROLLER, display_position, thousands_place, decimal_point_position == display_position);
	} else {
		lc.setChar(LED_CONTROLLER, display_position, ' ', decimal_point_position == display_position);
	}
}

void loop() {
	// Measure and report data via serial and LED display
	float voltage_A0 = read_average_ADC(A0, DOWNSAMPLING);
	write_measurement_to_serial("y0", voltage_A0);
	display_number_on_7segment(0, (int)(voltage_A0*1000), 3);

	float voltage_A1 = read_average_ADC(A1, DOWNSAMPLING);
	write_measurement_to_serial("y1", voltage_A1);
	display_number_on_7segment(4, (int)(voltage_A1*1000), 7);
		
	float voltage_A2 = read_average_ADC(A2, DOWNSAMPLING);
	write_measurement_to_serial("y2", voltage_A2);
	/*display_number_on_7segment(...); // Not enough space on LED display for three numbers*/
}

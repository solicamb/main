/*
 * Development (debugging) setup for the BluePill controlling the moisture probe
 *
 * Authors:
 *  Jan (jh2109)
 *
 */

#include <Wire.h>
#include <SPI.h>

// Config
#define BAUDRATE 38400		// Arduino <=> PC serial baudrate
#define DOWNSAMPLING 5000 // number of ADC readings to average per measurement

#define SLAVE_DEVICE_TYPE 0b00100000 // Identifies us to the master as a moisture sensor slave device
#define SLAVE_DEVICE_SERIAL_NUMBER 1  // Serial number for our devices. 0..15

// Pin Config
#define SPI1_SS PA4
// All other SPI1 pins are pre-defined

#define ADC_FULL_SCALE_VOLTAGE 4.0f // full scale ADC voltage for scaling
// TODO/NB While this will correspond to VCC, don't assume the VCC=3.3V pin will have exactly that voltage
// One measurement gave 4V when powered via USB from a PC, hence this choice
// Ultimately, we should control/know what VCC we are referencing to. On the other hand, this scaling is only
// to make it more physically meaningful; we can also just think in terms of percentage of full scale
#define ADC_FULL_SCALE_VALUE 4095 // 12 bit resolution for blue pill

// Global scope variables
bool spi_initiated = 0;

void setup() {
	// Initialise serial
  Serial.begin(BAUDRATE);
	while (!Serial){
		// nop until serial becomes available
	}

	Serial.flush();
	Serial.println();
	delay(10); // give PC serial monitor time to catch up; otherwise we catch garbled mess at start
	Serial.println("START");

	// Set up pins (commented-out ones are predefined, so are skipped, but left in the code as a reminder)
	/*pinMode(SPI1_CLK, INPUT);*/
	/*pinMode(SPI1_MISO, OUTPUT);*/
	/*pinMode(SPI1_MOSI, INPUT);*/
	// TODO check if this is needed & used correctly (assignment of SS by default?)
	pinMode(SPI1_SS, INPUT);
  
  SPI.setModule(1);
  SPI.beginTransactionSlave(SPISettings(18000000, MSBFIRST, SPI_MODE0, DATA_SIZE_8BIT));
  // NB The clock value is not used, as we are a slave device TODO can we set it to 0 to make this obvious?

  // Data that master will receive when transferring a data frame over SPI
  SPI.dev()->regs->DR = 0; // TODO think about what is most meaningful here


	/*while (spi_initiated == false){*/
		initiate_communication_with_master();
	/*}*/

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

void initiate_communication_with_master(){
	// Tell master who we are
	// Specified format: upper nibble ID, lower nibble serial number
	Serial.print("INFO: Identifying ourselves to Master with ID+S/N 0x");
	Serial.println(SLAVE_DEVICE_TYPE | SLAVE_DEVICE_SERIAL_NUMBER, HEX);
	
	SPI.transfer(SLAVE_DEVICE_TYPE | SLAVE_DEVICE_SERIAL_NUMBER);

	spi_initiated = true;
	return;
}

void send_measurement_to_master(uint8_t measurement_type, uint8_t measurement_value){
	// Report a measurement $value of type $measurement_type to the master
	// TODO extend to non-measurements once needed (e.g., GUI changes)
	Serial.print("INFO: Sending to master: measurement_type: 0x");
	Serial.println(measurement_type, HEX);
	uint8_t msg = SPI.transfer(measurement_type);

	Serial.print("INFO: Sending to master: measurement_value: ");
	Serial.println(measurement_value);
	msg = SPI.transfer(measurement_value);
}

void loop() {
	// Measure and report data via serial
	float voltage_PA0 = read_average_ADC(PA0, DOWNSAMPLING);
	write_measurement_to_serial("y0", voltage_PA0);

	float voltage_PA1 = read_average_ADC(PA1, DOWNSAMPLING);
	write_measurement_to_serial("y1", voltage_PA1);
		
	float voltage_PA2 = read_average_ADC(PA2, DOWNSAMPLING);
	write_measurement_to_serial("y2", voltage_PA2);

	// Communicate result to master via SPI
	uint8_t measurement_type = 3;
	uint8_t measurement_value = (uint8_t)(voltage_PA0*100); // TODO dummy; implement algorithm on what to send to master
	send_measurement_to_master(measurement_type, measurement_value);
}

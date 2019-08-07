/*
 * Production setup for the BluePill controlling the moisture probe (i.e. the slave, the sensor probe)
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

#define NUMBER_OF_SIGNALS 3

// #defines other than constants for which I prefer real variables to make the code more readable
// they will be optimised away by the compiler anyway
const bool DEBUGGING = true;
const bool DEBUG_WAIT_FOR_MASTER = true;

// Constants
const uint8_t SPI_CMD_PROBE_INSERTED = 0xF1;
const uint8_t MEASUREMENT_TYPE_MOISTURE_LEVEL = 0x3;
const uint8_t MEASUREMENT_TYPE_MOISTURE_RETENTION = 0x4;


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
float calibration[NUMBER_OF_SIGNALS] = {};
bool measurement_in_progress = false;
unsigned long signal_detected_timer[NUMBER_OF_SIGNALS] = {};

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
  SPI.beginTransactionSlave(SPISettings(0, MSBFIRST, SPI_MODE0, DATA_SIZE_8BIT));
  /*SPI.beginTransactionSlave(SPISettings(18000000, MSBFIRST, SPI_MODE0, DATA_SIZE_8BIT));*/
  // NB The clock value is not used, as we are a slave device TODO can we set it to 0 to make this obvious?

  // Data that master will receive when transferring a data frame over SPI
<<<<<<< HEAD
	SPI.dev()->regs->DR = 10; // TODO think about what is most meaningful here
=======
  SPI.dev()->regs->DR = 0; // TODO think about what is most meaningful here
>>>>>>> 19fbe08

	initiate_communication_with_master();
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
	
	if (DEBUG_WAIT_FOR_MASTER){
		SPI.transfer(SLAVE_DEVICE_TYPE | SLAVE_DEVICE_SERIAL_NUMBER);
		spi_initiated = true;
	}

	return;
}

void send_measurement_to_master(uint8_t measurement_type, uint8_t measurement_value){
	// Report a measurement $value of type $measurement_type to the master
	// TODO extend to non-measurements once needed (e.g., GUI changes)
	if (DEBUG_WAIT_FOR_MASTER){
		Serial.print("INFO: Sending to master: measurement_type: 0x");
		Serial.println(measurement_type, HEX);
		SPI.transfer(measurement_type);

		Serial.print("INFO: Sending to master: measurement_value: ");
		Serial.println(measurement_value);
		SPI.transfer(measurement_value);
	}
	else {
		Serial.print("INFO: Skipping SPI transfer (DEBUG_WAIT_FOR_MASTER=false): type=");
		Serial.print(measurement_type);
		Serial.print(" val=");
		Serial.println(measurement_value);
	}
}

float return_calibrated_value(float raw_voltage, int signal_id){
	// Return calibrated measurement of signal $signal_id, with raw voltage reading $raw_voltage
	// Calibration values are held in the global variable calibration[]
	return raw_voltage - calibration[signal_id];
}
	
int evaluate_moisture_retention_score(float signals[]){
	// TODO stub function
	return 42;
}

bool threshold_detection(float signals[], unsigned long signal_detected_timer[]){
	// TODO stub function
	// Return true if all needed measurements have been done (i.e., water has reached all the probes)
	return 42;
}

uint8_t getMoistureLevel(float raw_voltages[]){
	// TODO stub function
	return 23;
}

void loop() {
	float raw_voltages[NUMBER_OF_SIGNALS];
	float signals[NUMBER_OF_SIGNALS];
	char signal_id_string[2] = ""; // will hold the (ASCII) number added to the signal name
	int adc_pin = PA0; // We assume three sequential pins, starting with this one. If not, need to implement pin mapping

	// For all signals (measurements):
	for (int i = 0; i < NUMBER_OF_SIGNALS; i++){
		// Measure and report raw data via serial
		raw_voltages[i] = read_average_ADC(adc_pin + i, DOWNSAMPLING);
		char signal_name[20] = "y"; // maximum length hardcoded, adjust if using longer signal names
		signal_id_string[0] = '0' + i; // convert int->ASCII by simple addition. itoa() not in stdlib
		strcat(signal_name, signal_id_string); // append signal index to form "y0" etc
		write_measurement_to_serial(signal_name, raw_voltages[i]);

		// Calibrate values, send to serial
		signals[i] = return_calibrated_value(raw_voltages[i], i);
		strcpy(signal_name, "calibrated");
		strcat(signal_name, signal_id_string);
		write_measurement_to_serial(signal_name, signals[i]);
	}

	if (measurement_in_progress == true){
		if (calibration[0] == 0){
			// Not yet calibrated: user has now confirmed that probe has been inserted into ground
			Serial.println("INFO: Setting calibration from previous reading");
			memcpy(&calibration, &raw_voltages, sizeof(calibration));

			// We determine the absolute moisture level (wetness) before irrigation
			Serial.println("INFO: Calculating absolute moisture level (wetness)");
			uint8_t moisture_level = getMoistureLevel(raw_voltages);

			// Send it out to master
			send_measurement_to_master(MEASUREMENT_TYPE_MOISTURE_LEVEL, moisture_level);

			// Start timer for irrigation measurement (moisture retention)
			memset(&signal_detected_timer, millis(), sizeof(signal_detected_timer));

			// Return to main loop, starting continuous measurements
			return;
		}
		
		if (threshold_detection(signals)){
			// Moisture intrusion event detected
			Serial.println("INFO: Moisture intrusion detected for probes number:(stub)");
			//TODO stub

			// Moisture retention algorithm
			int moisture_retention_score = evaluate_moisture_retention_score(signals, signal_detected_timer);
		
			// Communicate result to master via SPI
			send_measurement_to_master(MEASUREMENT_TYPE_MOISTURE_RETENTION, moisture_retention_score);
		}
	}
	else {
		// No measurement in progress yet (i.e. probe has not been inserted into ground)
		Serial.println("INFO: Waiting for master to confirm probe has been inserted");

		// Read from master
		uint8_t spi_rec_msg = SPI.transfer(0);

		// Compare to expected command constant
		if (spi_rec_msg == SPI_CMD_PROBE_INSERTED){
			measurement_in_progress = true;
		}
		else {
			Serial.print("WARN: received unexpected code from master: 0x");
			Serial.println(spi_rec_msg, HEX);
		}
	}
}


# Class Sensor


[**Class List**](annotated.md) **>** [**Sensor**](class_sensor.md)



_A class which models a Sensor/peripheral._ [More...](#detailed-description)

* `#include <Sensor.h>`



Inherits the following classes: [Instructable](class_instructable.md),  [Instructor](class_instructor.md),  [DataSource](class_data_source.md),  [Identifiable](class_identifiable.md)




























## Public Functions

| Type | Name |
| ---: | :--- |
|  int | [**PauseMeasurementForMillis**](class_sensor.md#function-pausemeasurementformillis) (int PauseTime) <br>_Instruct the sensor to pause the measurement procedure for a brief period._  |
|  int | [**RestartMeasurement**](class_sensor.md#function-restartmeasurement) (void) <br>_Instruct the sensor to restart the measurement procedure._  |
|   | [**Sensor**](class_sensor.md#function-sensor) (const int ChipSelect) <br>_Constructor._  |
|  int | [**StartMeasurement**](class_sensor.md#function-startmeasurement) (void) <br>_Instruct the sensor to initiate the measurement procedure._  |

## Public Functions inherited from Instructable

See [Instructable](class_instructable.md)

| Type | Name |
| ---: | :--- |
|   | [**Instructable**](class_instructable.md#function-instructable) (const int ChipSelect) <br>_A constructor._  |
|  bool | [**areYouConnected**](class_instructable.md#function-areyouconnected) (void) <br>_Checks to see whether the peripheral is connected._  |
|  bool | [**issueCommand**](class_instructable.md#function-issuecommand-1-4) ([**mInstruct**](_s_p_i___instruction_set_8h.md#enum-minstruct) Command) <br>_Issues a command to the peripheral._  |
|  bool | [**issueCommand**](class_instructable.md#function-issuecommand-2-4) ([**mInstruct**](_s_p_i___instruction_set_8h.md#enum-minstruct) Command, int intParam) <br>_Issues a command to the peripheral._  |
|  bool | [**issueCommand**](class_instructable.md#function-issuecommand-3-4) ([**mInstruct**](_s_p_i___instruction_set_8h.md#enum-minstruct) Command, float floatParam) <br>_Issues a command to the peripheral._  |
|  bool | [**issueCommand**](class_instructable.md#function-issuecommand-4-4) ([**mInstruct**](_s_p_i___instruction_set_8h.md#enum-minstruct) Command, int intParam, float floatParam) <br>_Issues a command to the peripheral._  |

## Public Functions inherited from Instructor

See [Instructor](class_instructor.md)

| Type | Name |
| ---: | :--- |
|   | [**Instructor**](class_instructor.md#function-instructor) (const int ChipSelect) <br>_Constructor._  |
|  float | [**getCurrentCommandFloat**](class_instructor.md#function-getcurrentcommandfloat) (void) <br>_Returns the float which qualifies the instruction currently loaded into local memory as issued by the_ [_**Sensor**_](class_sensor.md) _._ |
|  [**sInstruct**](_s_p_i___instruction_set_8h.md#enum-sinstruct) | [**getCurrentCommandInstruction**](class_instructor.md#function-getcurrentcommandinstruction) (void) <br>_Returns the sinstruct object which defines the instruction currently loaded into local memory as issued by the_ [_**Sensor**_](class_sensor.md) _._ |
|  int | [**getCurrentCommandInt**](class_instructor.md#function-getcurrentcommandint) (void) <br>_Returns the integer which qualifies the instruction currently loaded into local memory as issued by the_ [_**Sensor**_](class_sensor.md) _._ |
|  void | [**getCurrentCommandString**](class_instructor.md#function-getcurrentcommandstring) (char Instruction) <br>_Returns the character array which qualifies the instruction currently loaded into local memory as issued by the_ [_**Sensor**_](class_sensor.md) _._ |
|  int | [**howLongShouldIWait**](class_instructor.md#function-howlongshouldiwait) (void) <br>_Asks the sensor how long the master should pause for. Deprecated._  |
|  int | [**howManyInstructions**](class_instructor.md#function-howmanyinstructions) (void) <br>_Asks the_ [_**Sensor**_](class_sensor.md) _how many instructions there are in a measurement cycle._ |
|  void | [**loadNextCommand**](class_instructor.md#function-loadnextcommand) (void) <br>_Fetches the next instruction issued by the sensor in its instruction cycle._  |

## Public Functions inherited from DataSource

See [DataSource](class_data_source.md)

| Type | Name |
| ---: | :--- |
|   | [**DataSource**](class_data_source.md#function-datasource) (const int ChipSelect) <br>_Constructor._  |
|  void | [**getDataArray**](class_data_source.md#function-getdataarray) (float DataVals) <br>_Gets the entire data array._  |
|  void | [**getDataVector**](class_data_source.md#function-getdatavector) (const [**MeasurementVectors**](_s_p_i___instruction_set_8h.md#enum-measurementvectors) VectorNumber, float DataVect) <br>_Gets the indicated data vector._  |
|  int | [**getNumberOfDataColumns**](class_data_source.md#function-getnumberofdatacolumns) (const [**MeasurementVectors**](_s_p_i___instruction_set_8h.md#enum-measurementvectors) VectorNumber) <br>_Gets the number of data points along a particular row of the data array._  |
|  int | [**getNumberOfDataRows**](class_data_source.md#function-getnumberofdatarows) (void) <br>_Gets the number of rows used in the data array._  |
|  void | [**getRowHeadings**](class_data_source.md#function-getrowheadings) (char Headings) <br>_Gets string headings of all the vectors in the data array._  |
|  void | [**getRowUnits**](class_data_source.md#function-getrowunits) (char Units) <br>_Gets string units of all the vectors in the data array._  |
|  float | [**getValueOne**](class_data_source.md#function-getvalueone) (void) <br>_Gets the first data point in the first vector._  |
|  float | [**getValueThree**](class_data_source.md#function-getvaluethree) (void) <br>_Gets the third data point in the first vector._  |
|  float | [**getValueTwo**](class_data_source.md#function-getvaluetwo) (void) <br>_Gets the second data point in the first vector._  |
|  void | [**getVectorHeading**](class_data_source.md#function-getvectorheading) (const [**MeasurementVectors**](_s_p_i___instruction_set_8h.md#enum-measurementvectors) VectorNumber, char Heading) <br>_Gets the string heading for the vector in question._  |
|  int | [**getVectorLength**](class_data_source.md#function-getvectorlength) (const [**MeasurementVectors**](_s_p_i___instruction_set_8h.md#enum-measurementvectors) VectorNumber) <br>_Gets the indicated data vector length._  |
|  void | [**getVectorUnits**](class_data_source.md#function-getvectorunits) (const [**MeasurementVectors**](_s_p_i___instruction_set_8h.md#enum-measurementvectors) VectorNumber, char Units) <br>_Gets the string units for the vector in question._  |
|  bool | [**isThereData**](class_data_source.md#function-istheredata) (void) <br>_Asks Sensor/peripheral whether there is_ [_**Data**_](struct_data.md) _ready to be collected._ |
|  [**Data**](struct_data.md) | [**loadData**](class_data_source.md#function-loaddata) (void) <br>_Loads_ [_**Data**_](struct_data.md) _from the_[_**Sensor**_](class_sensor.md) _._ |

## Public Functions inherited from Identifiable

See [Identifiable](class_identifiable.md)

| Type | Name |
| ---: | :--- |
|   | [**Identifiable**](class_identifiable.md#function-identifiable) (const int ChipSelect) <br>_A constructor._  |
|  int | [**getIDNumber**](class_identifiable.md#function-getidnumber) (void) <br>_Gets the identity number of the attached peripheral._  |
|  void | [**getSensorName**](class_identifiable.md#function-getsensorname) (char name) <br>_Gets the sensor name of the attached peripheral._  |
|  bool | [**hasIdentityChanged**](class_identifiable.md#function-hasidentitychanged) (void) <br>_Checks to seee whether the_ [_**Identity**_](struct_identity.md) _in local memory is different to the_[_**Identity**_](struct_identity.md) _advertised by peripheral._ |
|  void | [**updateIdentity**](class_identifiable.md#function-updateidentity) (void) <br>_Loads the_ [_**Identity**_](struct_identity.md) _advertised by the peripheral into local memory._ |




































# Detailed Description


This class models a sensor peripheral as an entity which has a queriable [**Identity**](struct_identity.md), is a source of [**Data**](struct_data.md), can be issued commands and can issue a series of instructions in turn. In particular, a sensor is considered to perform a measurement procedure consisting of a series of steps; at each step, the sensor will issue instructions to the master to be acted upon and/or displayed to the user. The sensor may also require feedback from the user such as confirmation of the completion of an instruction, before proceeding to the next instruction in the measurement procedure. While the sensor dictates the flow of the measurement procedure, a master reserves the right to initiate the procedure, pause the procedure and restart the procedure. 


    
## Public Functions Documentation


### <a href="#function-pausemeasurementformillis" id="function-pausemeasurementformillis">function PauseMeasurementForMillis </a>


```cpp
int Sensor::PauseMeasurementForMillis (
    int PauseTime
) 
```


Instructs the sensor to temporarily pause the measurement procedure for a period defined in milliseconds. 

**Parameters:**


* int is the number of milliseconds for which the sensor is to pause. 



**Returns:**

True if the sensor acknowledges the request. 





        

### <a href="#function-restartmeasurement" id="function-restartmeasurement">function RestartMeasurement </a>


```cpp
int Sensor::RestartMeasurement (
    void
) 
```


Instructs the sensor to restart the measurement procedure. The sensor will wait revert to its initial state, waiting for a [**StartMeasurement()**](class_sensor.md#function-startmeasurement) command before proceeding to the first instruction in the procedure. 

**Returns:**

True if the sensor acknowledges the request. 





        

### <a href="#function-sensor" id="function-sensor">function Sensor </a>


```cpp
Sensor::Sensor (
    const int ChipSelect
) 
```




**Parameters:**


* ChipSelect is the Slave Select pin of the SPI peripheral in question. 




        

### <a href="#function-startmeasurement" id="function-startmeasurement">function StartMeasurement </a>


```cpp
int Sensor::StartMeasurement (
    void
) 
```


Informs the sensor to start the measurement procedure and proceed to the first instruction step. 

**Returns:**

True if the sensor acknowledges the request. 





        

------------------------------
The documentation for this class was generated from the following file `Sensor.h`
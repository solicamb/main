
# Class Instructor


[**Class List**](annotated.md) **>** [**Instructor**](class_instructor.md)



_A class which models a Sensor/peripheral as entity which can issue instructions to the master._ [More...](#detailed-description)

* `#include <Instructor.h>`





Inherited by the following classes: [Sensor](class_sensor.md)










## Public Functions

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








# Detailed Description


This class models a peripheral as an entity which can issue commands to the master. The premise is that a sensor peripheral will conduct a measurement by cycling through a number of steps. At each step the sensor may wish for the [**Master**](class_master.md) to perform certain actions, such as display a message to the user, pause for a certain period of time or wait until the user has acknowledged an instruction by button press. In general, the master is expected to iterate through the instruction set, loading an instruction each iteration and repsonding appropriately. i.e. follow the procedure: [**howManyInstructions()**](class_instructor.md#function-howmanyinstructions)-&gt;start loop-&gt;[**loadNextCommand()**](class_instructor.md#function-loadnextcommand)-&gt;React to command-&gt;repeat until all instructions have been processed. 


    
## Public Functions Documentation


### <a href="#function-instructor" id="function-instructor">function Instructor </a>


```cpp
Instructor::Instructor (
    const int ChipSelect
) 
```




**Parameters:**


* ChipSelect is the Slave Select pin of the SPI peripheral in question. 




        

### <a href="#function-getcurrentcommandfloat" id="function-getcurrentcommandfloat">function getCurrentCommandFloat </a>


```cpp
float Instructor::getCurrentCommandFloat (
    void
) 
```


The float which qualifies the instruction issued by the sensor is generally used to either augment the information displayed to the user to instruct the master as to how it should carry out the request of the slave. 


        

### <a href="#function-getcurrentcommandinstruction" id="function-getcurrentcommandinstruction">function getCurrentCommandInstruction </a>


```cpp
sInstruct Instructor::getCurrentCommandInstruction (
    void
) 
```


Elements of the sInstruct type define all the potential instructions which can be issued by a Slave. 

**Returns:**

The instruction issued by the slave. 





        

### <a href="#function-getcurrentcommandint" id="function-getcurrentcommandint">function getCurrentCommandInt </a>


```cpp
int Instructor::getCurrentCommandInt (
    void
) 
```


The integer which qualifies the instruction issued by the sensor is generally used to either augment the information displayed to the user to instruct the master as to how it should carry out the request of the slave, such as how long to pasue for. 

**Returns:**

The integer which qualifies the instruction. 





        

### <a href="#function-getcurrentcommandstring" id="function-getcurrentcommandstring">function getCurrentCommandString </a>


```cpp
void Instructor::getCurrentCommandString (
    char Instruction
) 
```


The character array (string) issued by the [**Sensor**](class_sensor.md) is generally intended to be displayed to the user, to update the user on the progress of the measurement procedure or instruct the user on the next step in the measurement procedure, such as inserting the probe into the measurement environment. 

**Parameters:**


* char is the character array into which the instruction string is loaded. 




        

### <a href="#function-howlongshouldiwait" id="function-howlongshouldiwait">function howLongShouldIWait </a>


```cpp
int Instructor::howLongShouldIWait (
    void
) 
```




**Returns:**

The duration, in milliseconds, the master should pause for. 





        

### <a href="#function-howmanyinstructions" id="function-howmanyinstructions">function howManyInstructions </a>


```cpp
int Instructor::howManyInstructions (
    void
) 
```


In general, the master is expected to iterate through the instrcution set. 

**Returns:**

The number of instructions in a measurement cycle. 





        

### <a href="#function-loadnextcommand" id="function-loadnextcommand">function loadNextCommand </a>


```cpp
void Instructor::loadNextCommand (
    void
) 
```


Fetches the next instruction from the [**Sensor**](class_sensor.md) and loads it into local memory. Instructions are issued in the [**sCmd**](structs_cmd.md) type and are therefore consititute an element of the sInstruct instruction set, qualified by a character array (string), integer and float. 


        

------------------------------
The documentation for this class was generated from the following file `Instructor.h`
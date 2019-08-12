
# Class Instructable


[**Class List**](annotated.md) **>** [**Instructable**](class_instructable.md)



_A class which models a Sensor/peripheral as entity which can recieve commands._ [More...](#detailed-description)

* `#include <Instructable.h>`





Inherited by the following classes: [Sensor](class_sensor.md)










## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Instructable**](class_instructable.md#function-instructable) (const int ChipSelect) <br>_A constructor._  |
|  bool | [**areYouConnected**](class_instructable.md#function-areyouconnected) (void) <br>_Checks to see whether the peripheral is connected._  |
|  bool | [**issueCommand**](class_instructable.md#function-issuecommand-1-4) ([**mInstruct**](_s_p_i___instruction_set_8h.md#enum-minstruct) Command) <br>_Issues a command to the peripheral._  |
|  bool | [**issueCommand**](class_instructable.md#function-issuecommand-2-4) ([**mInstruct**](_s_p_i___instruction_set_8h.md#enum-minstruct) Command, int intParam) <br>_Issues a command to the peripheral._  |
|  bool | [**issueCommand**](class_instructable.md#function-issuecommand-3-4) ([**mInstruct**](_s_p_i___instruction_set_8h.md#enum-minstruct) Command, float floatParam) <br>_Issues a command to the peripheral._  |
|  bool | [**issueCommand**](class_instructable.md#function-issuecommand-4-4) ([**mInstruct**](_s_p_i___instruction_set_8h.md#enum-minstruct) Command, int intParam, float floatParam) <br>_Issues a command to the peripheral._  |








# Detailed Description


This class models a peripheral as an entity which can be issued commands. The commands issued are elements of the set defined by the mInstruct type. Each instruction can be accompanied by and integer and/or float as required to act as parameters to qualify the command. For example, if the peripheral is commanded to pause for an interval, the integer parameter is used by the peripheral to determine the length of time for which to pause. 


    
## Public Functions Documentation


### <a href="#function-instructable" id="function-instructable">function Instructable </a>


```cpp
Instructable::Instructable (
    const int ChipSelect
) 
```




**Parameters:**


* The Slave Select pin of the SPI peripheral in question. 




        

### <a href="#function-areyouconnected" id="function-areyouconnected">function areYouConnected </a>


```cpp
bool Instructable::areYouConnected (
    void
) 
```


Initiates handshake and nop transaction with the sensor to ensure that it is connected and responding appropriately. 

**Returns:**

True if the peripheral is connected and communicating effectively. 





        

### <a href="#function-issuecommand-1-4" id="function-issuecommand-1-4">function issueCommand [1/4]</a>


```cpp
bool Instructable::issueCommand (
    mInstruct Command
) 
```


Sends a command which is an element of the mInstruct type. 

**Parameters:**


* mInstruct is the command issued to the peripheral. 



**Returns:**

True if the peripheral acknowledges the command. 





        

### <a href="#function-issuecommand-2-4" id="function-issuecommand-2-4">function issueCommand [2/4]</a>


```cpp
bool Instructable::issueCommand (
    mInstruct Command,
    int intParam
) 
```


Sends a command which is an element of the mInstruct type qualified by an integer parameter (generally used to instruct on wait time or similar). 

**Parameters:**


* mInstruct is the command issued to the peripheral and int is the integer qualifier. 



**Returns:**

True if the peripheral acknowledges the command. 





        

### <a href="#function-issuecommand-3-4" id="function-issuecommand-3-4">function issueCommand [3/4]</a>


```cpp
bool Instructable::issueCommand (
    mInstruct Command,
    float floatParam
) 
```


Sends a command which is an element of the mInstruct type qualified by a float parameter. 

**Parameters:**


* mInstruct is the command issued to the peripheral and float is the floating point qualifier. 



**Returns:**

True if the peripheral acknowledges the command. 





        

### <a href="#function-issuecommand-4-4" id="function-issuecommand-4-4">function issueCommand [4/4]</a>


```cpp
bool Instructable::issueCommand (
    mInstruct Command,
    int intParam,
    float floatParam
) 
```


Sends a command which is an element of the mInstruct type qualified by an integer parameter (generally used to instruct on wait time or similar) and a floating point parameter. 

**Parameters:**


* mInstruct is the command issued to the peripheral, int is the integer qualifier and float is the floating point qualifier. 



**Returns:**

True if the peripheral acknowledges the command. 





        

------------------------------
The documentation for this class was generated from the following file `Instructable.h`
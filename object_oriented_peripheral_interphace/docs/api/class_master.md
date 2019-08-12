
# Class Master


[**Class List**](annotated.md) **>** [**Master**](class_master.md)



_A monolithic class to encapsulate and abstract the slave's communication with the master._ [More...](#detailed-description)

* `#include <Master.h>`















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**ClearMeasurementVector**](class_master.md#function-clearmeasurementvector) ([**MeasurementVectors**](_s_p_i___instruction_set_8h.md#enum-measurementvectors) VectorNumber) <br>_Clears all data points from a particular vector._  |
|  bool | [**Handshake**](class_master.md#function-handshake) (void) <br>_Manages the handshake component of any transaction._  |
|   | [**Master**](class_master.md#function-master-1-3) (const int SensorIDNumber, const char SensorName, const char InstructionSet, const int NumberOfInstructions, const [**sInstruct**](_s_p_i___instruction_set_8h.md#enum-sinstruct) MasterInstructionSet, const int intParams, const float floatParams) <br> |
|   | [**Master**](class_master.md#function-master-2-3) (void) <br> |
|   | [**Master**](class_master.md#function-master-3-3) (volatile const [**Master**](class_master.md) & rhs) <br> |
|  bool | [**PopMeasurementVector**](class_master.md#function-popmeasurementvector) ([**MeasurementVectors**](_s_p_i___instruction_set_8h.md#enum-measurementvectors) VectorNumber) <br>_Pops a data point from the tail end of a designated vector._  |
|  bool | [**PushMeasurementVector**](class_master.md#function-pushmeasurementvector) (const [**MeasurementVectors**](_s_p_i___instruction_set_8h.md#enum-measurementvectors) VectorNumber, const float Measurement) <br>_Pushes a data point onto one of the data vectors._  |
|  void | [**SETUP**](class_master.md#function-setup) (const int SensorIDNumber, volatile char SensorName, volatile char InstructionSet, const int NumberOfInstructions, volatile [**sInstruct**](_s_p_i___instruction_set_8h.md#enum-sinstruct) MasterInstructionSet, volatile int intParams, volatile float floatParams) <br>_Set up of the commuication mechanism._  |
|  void | [**SPISetup**](class_master.md#function-spisetup) (void) <br>_Sets up SPI and attaches interrupt._  |
|  void | [**beginMeasurement**](class_master.md#function-beginmeasurement) (void) <br>_Updates state to indicate that_ [_**Master**_](class_master.md) _has requested the intitiation of the measurement procedure._ |
|  [**mInstruct**](_s_p_i___instruction_set_8h.md#enum-minstruct) | [**getCurrentInstruction**](class_master.md#function-getcurrentinstruction) (void) <br>_Returns the mInstruct component of the most recently loaded request sent by the master._  |
|  float | [**getCurrentInstructionFloatParameter**](class_master.md#function-getcurrentinstructionfloatparameter) (void) <br>_Returns the floating point parameter of the most recently loaded request sent by the master._  |
|  int | [**getCurrentInstructionIntParameter**](class_master.md#function-getcurrentinstructionintparameter) (void) <br>_Returns the integer parameter of the most recently loaded request sent by the master._  |
|  int | [**getCurrentInstructionNumber**](class_master.md#function-getcurrentinstructionnumber) (void) <br>_Gets the value of the counter which tracks the current instruction number throughout the measurement procedure._  |
|  bool | [**isThereData**](class_master.md#function-istheredata) (void) <br>_Checks to see whether any data has been pushed to any of the data vectors locally._  |
|  [**mCmd**](structm_cmd.md) | [**loadRequest**](class_master.md#function-loadrequest) (void) <br>_Retrieve the request sent by the master._  |
|  [**Master**](class_master.md) & | [**operator=**](class_master.md#function-operator) (const [**Master**](class_master.md) & rhs) <br> |
|  [**Master**](class_master.md) & | [**operator=**](class_master.md#function-operator-2) (volatile const [**Master**](class_master.md) & rhs) <br> |
|  void | [**resendCurrentUserInstruction**](class_master.md#function-resendcurrentuserinstruction) (void) <br>_Resends the cuurent instruction in the measurement procedure to the master._  |
|  void | [**restartUserInstructionCycle**](class_master.md#function-restartuserinstructioncycle) (void) <br>_Restarts the measurement prcedure._  |
|  void | [**sendData**](class_master.md#function-senddata) (void) <br>_Sends the local_ [_**Data**_](struct_data.md) _object to the master in reply to appropriate request._ |
|  void | [**sendIdentity**](class_master.md#function-sendidentity) (void) <br>_Sends slave_ [_**Identity**_](struct_identity.md) _object to the master in reply to appropriate request._ |
|  bool | [**sendNextUserInstruction**](class_master.md#function-sendnextuserinstruction) (void) <br>_Sends the next instruction in the measurement cycle to the master._  |
|  void | [**sendReply**](class_master.md#function-sendreply-1-9) (const [**sCmd**](structs_cmd.md) Reply) <br>_Send an_ [_**sCmd**_](structs_cmd.md) _object in reply to the request recieved from_[_**Master**_](class_master.md) _._ |
|  void | [**sendReply**](class_master.md#function-sendreply-2-9) (const [**sInstruct**](_s_p_i___instruction_set_8h.md#enum-sinstruct) Instruction) <br>_Send a reply to the request recieved from master._  |
|  void | [**sendReply**](class_master.md#function-sendreply-3-9) (const [**sInstruct**](_s_p_i___instruction_set_8h.md#enum-sinstruct) Instruction, volatile char InstructionString) <br>_Send a reply to the request recieved from master._  |
|  void | [**sendReply**](class_master.md#function-sendreply-4-9) (const [**sInstruct**](_s_p_i___instruction_set_8h.md#enum-sinstruct) Instruction, const int iParam) <br>_Send a reply to the request recieved from master._  |
|  void | [**sendReply**](class_master.md#function-sendreply-5-9) (const [**sInstruct**](_s_p_i___instruction_set_8h.md#enum-sinstruct) Instruction, const float fParam) <br>_Send a reply to the request recieved from master._  |
|  void | [**sendReply**](class_master.md#function-sendreply-6-9) (const [**sInstruct**](_s_p_i___instruction_set_8h.md#enum-sinstruct) Instruction, const int iParam, const int fParam) <br>_Send a reply to the request recieved from master._  |
|  void | [**sendReply**](class_master.md#function-sendreply-7-9) ([**sInstruct**](_s_p_i___instruction_set_8h.md#enum-sinstruct) Instruction, int iParam, volatile char InstructionString) <br>_Send a reply to the request recieved from master._  |
|  void | [**sendReply**](class_master.md#function-sendreply-8-9) ([**sInstruct**](_s_p_i___instruction_set_8h.md#enum-sinstruct) Instruction, float fParam, volatile char InstructionString) <br>_Send a reply to the request recieved from master._  |
|  void | [**sendReply**](class_master.md#function-sendreply-9-9) ([**sInstruct**](_s_p_i___instruction_set_8h.md#enum-sinstruct) Instruction, int iParam, float fParam, volatile char InstructionString) <br>_Send a reply to the request recieved from master._  |
|  void | [**sendTotalNumOfInstructions**](class_master.md#function-sendtotalnumofinstructions) (void) <br>_Sends a reply to_ [_**Master**_](class_master.md) _specifiying the total number of instructions in a measurement procedure._ |
|  void | [**setMeasurementVectorHeading**](class_master.md#function-setmeasurementvectorheading) ([**MeasurementVectors**](_s_p_i___instruction_set_8h.md#enum-measurementvectors) VectorNumber, volatile char Heading) <br>_Sets the string heading assigned to a paritcular data vector._  |
|  void | [**setMeasurementVectorUnits**](class_master.md#function-setmeasurementvectorunits) ([**MeasurementVectors**](_s_p_i___instruction_set_8h.md#enum-measurementvectors) VectorNumber, volatile char Units) <br>_Sets the string Units assigned to a paritcular data vector._  |
|  bool | [**shallIStart**](class_master.md#function-shallistart) (void) <br>_Checks whether the_ [_**beginMeasurement()**_](class_master.md#function-beginmeasurement) _method has been called._ |
|   | [**~Master**](class_master.md#function-master) (void) <br> |








# Detailed Description


A single transaction is characterised by the following flow of control: Clear SS -&gt; Enter IRQ -&gt; Recieve '?' from master -&gt; send 'ACK' (0x06) to master -&gt; recieve request [**mCmd**](structm_cmd.md) -&gt; send sCmd/Data/Identity as expected -&gt; exit IRQ. Where [**mCmd**](structm_cmd.md), [**sCmd**](structs_cmd.md), [**Data**](struct_data.md) and [**Identity**](struct_identity.md) are structures defined as types. The intial Recieve '?' -&gt; send 'ACK' is known as the handshake. This class' responsibilities include intitialising and handling the SPI, attaching the interrupt and providing the IRQ, managing the handshake and encapsulating the reponse mechanism. Note the use of a volatile interface to allow for safe use of the interrupt. 


    
## Public Functions Documentation


### <a href="#function-clearmeasurementvector" id="function-clearmeasurementvector">function ClearMeasurementVector </a>


```cpp
void Master::ClearMeasurementVector (
    MeasurementVectors VectorNumber
) 
```




**Parameters:**


* VectorNumber is the enumerated reference to the row/vector in the data array being accessed. 




        

### <a href="#function-handshake" id="function-handshake">function Handshake </a>


```cpp
bool Master::Handshake (
    void
) 
```


Manages the handshake between master and slave; defined by: Recieve '?' -&gt; send 'ACK' (0x06). 

**Returns:**

True if the handshake was successful. 





        

### <a href="#function-master-1-3" id="function-master-1-3">function Master [1/3]</a>


```cpp
Master::Master (
    const int SensorIDNumber,
    const char SensorName,
    const char InstructionSet,
    const int NumberOfInstructions,
    const sInstruct MasterInstructionSet,
    const int intParams,
    const float floatParams
) 
```



### <a href="#function-master-2-3" id="function-master-2-3">function Master [2/3]</a>


```cpp
Master::Master (
    void
) 
```



### <a href="#function-master-3-3" id="function-master-3-3">function Master [3/3]</a>


```cpp
Master::Master (
    volatile const Master & rhs
) 
```



### <a href="#function-popmeasurementvector" id="function-popmeasurementvector">function PopMeasurementVector </a>


```cpp
bool Master::PopMeasurementVector (
    MeasurementVectors VectorNumber
) 
```


Removes the most recent data point from the vector in question by marking said data slot writeable to be the next [**PushMeasurementVector()**](class_master.md#function-pushmeasurementvector). 

**Parameters:**


* VectorNumber is the enumerated reference to the row/vector in the data array being accessed. 



**Returns:**

False if the vector/row in question is empty. 





        

### <a href="#function-pushmeasurementvector" id="function-pushmeasurementvector">function PushMeasurementVector </a>


```cpp
bool Master::PushMeasurementVector (
    const MeasurementVectors VectorNumber,
    const float Measurement
) 
```


Adds a data point to the next available slot in a particular vector until the vector (row) in the data array is full. 

**Parameters:**


* VectorNumber is the enumerated reference to the row/vector in the data array being accessed. 
* Measurement is the data point to be stored. 



**Returns:**

False if the vector/row in question is full. (See DATA\_ROW\_LENGTH). 





        

### <a href="#function-setup" id="function-setup">function SETUP </a>


```cpp
void Master::SETUP (
    const int SensorIDNumber,
    volatile char SensorName,
    volatile char InstructionSet,
    const int NumberOfInstructions,
    volatile sInstruct MasterInstructionSet,
    volatile int intParams,
    volatile float floatParams
) 
```


Intialised the auto-instantiated [**Master**](class_master.md) object, attaches the IRQ and sets up SPI communications. 

**Parameters:**


* SensorIDNumber is the identity number of th slave. 
* SensorName is the string name of the slave. 
* InstructionSet is the array of strings associated with each instruction in the measuremnt cycle. Generally to be displayed to the user. 
* NumberOfInstructions is the number of instructions in a single measurement cycle/procedure. 
* MasterInstructionSet is the array of sInstruct objects associated with each instruction in the measurement cycle. Defines the required action by the master for each step of the measurement procedure. 
* IntParams is the array of integer parameter associated with each instruction. 
* FloatParams is the array of floating point parameters accosiated with each instruction. 




        

### <a href="#function-spisetup" id="function-spisetup">function SPISetup </a>


```cpp
void Master::SPISetup (
    void
) 
```



### <a href="#function-beginmeasurement" id="function-beginmeasurement">function beginMeasurement </a>


```cpp
void Master::beginMeasurement (
    void
) 
```


Designed to allow the IRQ to update the slave state so that the procedural code in main() can initiate the measurement procedure. 


        

### <a href="#function-getcurrentinstruction" id="function-getcurrentinstruction">function getCurrentInstruction </a>


```cpp
mInstruct Master::getCurrentInstruction (
    void
) 
```



### <a href="#function-getcurrentinstructionfloatparameter" id="function-getcurrentinstructionfloatparameter">function getCurrentInstructionFloatParameter </a>


```cpp
float Master::getCurrentInstructionFloatParameter (
    void
) 
```



### <a href="#function-getcurrentinstructionintparameter" id="function-getcurrentinstructionintparameter">function getCurrentInstructionIntParameter </a>


```cpp
int Master::getCurrentInstructionIntParameter (
    void
) 
```



### <a href="#function-getcurrentinstructionnumber" id="function-getcurrentinstructionnumber">function getCurrentInstructionNumber </a>


```cpp
int Master::getCurrentInstructionNumber (
    void
) 
```



### <a href="#function-istheredata" id="function-istheredata">function isThereData </a>


```cpp
bool Master::isThereData (
    void
) 
```




**Returns:**

True if any data points exist in the data vectors locally. 





        

### <a href="#function-loadrequest" id="function-loadrequest">function loadRequest </a>


```cpp
mCmd Master::loadRequest (
    void
) 
```


After each handshake, the master will proceed to send a request, defined by an [**mCmd**](structm_cmd.md) object. This function must runafter each handshake. This function reassembles the [**mCmd**](structm_cmd.md) request sent by the master, byte by byte and stores it in local memory. 

**Returns:**

the [**mCmd**](structm_cmd.md) object sent by the master. 





        

### <a href="#function-operator" id="function-operator">function operator= </a>


```cpp
inline Master & Master::operator= (
    const Master & rhs
) 
```



### <a href="#function-operator-2" id="function-operator-2">function operator= </a>


```cpp
inline Master & Master::operator= (
    volatile const Master & rhs
) 
```



### <a href="#function-resendcurrentuserinstruction" id="function-resendcurrentuserinstruction">function resendCurrentUserInstruction </a>


```cpp
void Master::resendCurrentUserInstruction (
    void
) 
```


This method will NOT advance the measurement cycle. 


        

### <a href="#function-restartuserinstructioncycle" id="function-restartuserinstructioncycle">function restartUserInstructionCycle </a>


```cpp
void Master::restartUserInstructionCycle (
    void
) 
```


Restarts the measuement procedure such that the next instruction sent will be the first instruction in the measurement cycle. 


        

### <a href="#function-senddata" id="function-senddata">function sendData </a>


```cpp
void Master::sendData (
    void
) 
```


Sends [**Data**](struct_data.md) object to the master in reponse to a request made by the master for [**Data**](struct_data.md). NOTE: This must be used as the response to the appropriate mInstruct request. In paricular, (mInstruct)SendDataPlease 


        

### <a href="#function-sendidentity" id="function-sendidentity">function sendIdentity </a>


```cpp
void Master::sendIdentity (
    void
) 
```


Sends the slave [**Identity**](struct_identity.md) object in response to an appropriate request made by master. NOTE: This must be used as the response to the appropriate mInstruct request. In paricular, (mInstruct)WhoAreYou 


        

### <a href="#function-sendnextuserinstruction" id="function-sendnextuserinstruction">function sendNextUserInstruction </a>


```cpp
bool Master::sendNextUserInstruction (
    void
) 
```


Sends the next instruction in the measurement cycle array in reponse to the appropriate request from master. Specifically, (mInstruct)NextCommandPlease. This method will auto-advance the measurement cycle to the next instruction and re-define the 'current instruction'. 

**Returns:**

False if the final instruction in the measurement procedure has already been sent and the measurement procedure is now complete. 





        

### <a href="#function-sendreply-1-9" id="function-sendreply-1-9">function sendReply [1/9]</a>


```cpp
void Master::sendReply (
    const sCmd Reply
) 
```



### <a href="#function-sendreply-2-9" id="function-sendreply-2-9">function sendReply [2/9]</a>


```cpp
void Master::sendReply (
    const sInstruct Instruction
) 
```


Assembles the [**sCmd**](structs_cmd.md) object from the supplied parameters. Overloaded. 


        

### <a href="#function-sendreply-3-9" id="function-sendreply-3-9">function sendReply [3/9]</a>


```cpp
void Master::sendReply (
    const sInstruct Instruction,
    volatile char InstructionString
) 
```


Assembles the [**sCmd**](structs_cmd.md) object from the supplied parameters. Overloaded. Note the need for the char\* to be defined locally as volatile char[]. Cannot pass string literals. 


        

### <a href="#function-sendreply-4-9" id="function-sendreply-4-9">function sendReply [4/9]</a>


```cpp
void Master::sendReply (
    const sInstruct Instruction,
    const int iParam
) 
```


Assembles the [**sCmd**](structs_cmd.md) object from the supplied parameters. Overloaded. 


        

### <a href="#function-sendreply-5-9" id="function-sendreply-5-9">function sendReply [5/9]</a>


```cpp
void Master::sendReply (
    const sInstruct Instruction,
    const float fParam
) 
```


Assembles the [**sCmd**](structs_cmd.md) object from the supplied parameters. Overloaded. 


        

### <a href="#function-sendreply-6-9" id="function-sendreply-6-9">function sendReply [6/9]</a>


```cpp
void Master::sendReply (
    const sInstruct Instruction,
    const int iParam,
    const int fParam
) 
```


Assembles the [**sCmd**](structs_cmd.md) object from the supplied parameters. Overloaded. 


        

### <a href="#function-sendreply-7-9" id="function-sendreply-7-9">function sendReply [7/9]</a>


```cpp
void Master::sendReply (
    sInstruct Instruction,
    int iParam,
    volatile char InstructionString
) 
```


Assembles the [**sCmd**](structs_cmd.md) object from the supplied parameters. Overloaded. Note the need for the char\* to be defined locally as volatile char[]. Cannot pass string literals. 


        

### <a href="#function-sendreply-8-9" id="function-sendreply-8-9">function sendReply [8/9]</a>


```cpp
void Master::sendReply (
    sInstruct Instruction,
    float fParam,
    volatile char InstructionString
) 
```


Assembles the [**sCmd**](structs_cmd.md) object from the supplied parameters. Overloaded. Note the need for the char\* to be defined locally as volatile char[]. Cannot pass string literals. 


        

### <a href="#function-sendreply-9-9" id="function-sendreply-9-9">function sendReply [9/9]</a>


```cpp
void Master::sendReply (
    sInstruct Instruction,
    int iParam,
    float fParam,
    volatile char InstructionString
) 
```


Assembles the [**sCmd**](structs_cmd.md) object from the supplied parameters. Overloaded. Note the need for the char\* to be defined locally as volatile char[]. Cannot pass string literals. 


        

### <a href="#function-sendtotalnumofinstructions" id="function-sendtotalnumofinstructions">function sendTotalNumOfInstructions </a>


```cpp
void Master::sendTotalNumOfInstructions (
    void
) 
```



### <a href="#function-setmeasurementvectorheading" id="function-setmeasurementvectorheading">function setMeasurementVectorHeading </a>


```cpp
void Master::setMeasurementVectorHeading (
    MeasurementVectors VectorNumber,
    volatile char Heading
) 
```


NOTE: The Heading parameter must be declared locally as volatile char[]. Literal strings cannot be passed to this function. 

**Parameters:**


* VectorNumber is the enumerated reference to the row/vector in the data array in question. 
* Heading[] is the character array containing the string heading. 




        

### <a href="#function-setmeasurementvectorunits" id="function-setmeasurementvectorunits">function setMeasurementVectorUnits </a>


```cpp
void Master::setMeasurementVectorUnits (
    MeasurementVectors VectorNumber,
    volatile char Units
) 
```


NOTE: The Units parameter must be declared locally as volatile char[]. Literal strings cannot be passed to this function. 

**Parameters:**


* VectorNumber is the enumerated reference to the row/vector in the data array in question. 
* Units[] is the character array containing the string heading. 




        

### <a href="#function-shallistart" id="function-shallistart">function shallIStart </a>


```cpp
bool Master::shallIStart (
    void
) 
```


Allows procedural code in main() to determine whether the system state has changed during an interrupt in response to a request by the master to initiate the measurement procedure. 


        

### <a href="#function-master" id="function-master">function ~Master </a>


```cpp
Master::~Master (
    void
) 
```



------------------------------
The documentation for this class was generated from the following file `Master.h`
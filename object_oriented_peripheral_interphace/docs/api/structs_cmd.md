
# Struct sCmd


[**Class List**](annotated.md) **>** [**sCmd**](structs_cmd.md)



_Type used by slave to send reply to master,._ [More...](#detailed-description)

* `#include <SPI_InstructionSet.h>`













## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**sInstruct**](_s_p_i___instruction_set_8h.md#enum-sinstruct) | [**Instruction**](structs_cmd.md#variable-instruction)  <br>_Instruction to master._  |
|  float | [**fParam**](structs_cmd.md#variable-fparam)  <br>_Floating point parameter which qualifies the instruction._  |
|  int | [**iParam**](structs_cmd.md#variable-iparam)  <br>_Integer parameter which qualifies the instruction._  |
|  char | [**sParam**](structs_cmd.md#variable-sparam)  <br>_String parameter which qualifies the instruction. Often used to convey instructions which are to be displayed to the user._  |


## Public Functions

| Type | Name |
| ---: | :--- |
|  [**sCmd**](structs_cmd.md) & | [**operator=**](structs_cmd.md#function-operator) (const volatile [**sCmd**](structs_cmd.md) & rhs) <br> |
|  [**sCmd**](structs_cmd.md) & | [**operator=**](structs_cmd.md#function-operator-2) (const [**sCmd**](structs_cmd.md) & rhs) <br> |








# Detailed Description


Each transaction, following the initial handshake, the master will send a request and the slave will send a reply. Replied made by the slave are generally in the form of an [**sCmd**](structs_cmd.md) object, which contains a parameterised instance of the slave instruction set, sInstruct, which defines the action which the slave requires the master to carry out. Other acceptable replies to particular requests from the master are [**Data**](struct_data.md) and [**Identity**](struct_identity.md) objects. 


    
## Public Attributes Documentation


### <a href="#variable-instruction" id="variable-instruction">variable Instruction </a>


```cpp
sInstruct Instruction;
```


Defines the reply made by the slave in repsonse to the request posed by the master during a single transaction. Used to confirm commands issued by the master or issue commands to the master. 


        

### <a href="#variable-fparam" id="variable-fparam">variable fParam </a>


```cpp
float fParam;
```



### <a href="#variable-iparam" id="variable-iparam">variable iParam </a>


```cpp
int iParam;
```



### <a href="#variable-sparam" id="variable-sparam">variable sParam </a>


```cpp
char sParam[SLAVE_COMMMAND_STRING_LENGTH];
```


## Public Functions Documentation


### <a href="#function-operator" id="function-operator">function operator= </a>


```cpp
inline sCmd & sCmd::operator= (
    const volatile sCmd & rhs
) 
```



### <a href="#function-operator-2" id="function-operator-2">function operator= </a>


```cpp
inline sCmd & sCmd::operator= (
    const sCmd & rhs
) 
```



------------------------------
The documentation for this class was generated from the following file `SPI_InstructionSet.h`
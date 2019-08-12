
# Struct mCmd


[**Class List**](annotated.md) **>** [**mCmd**](structm_cmd.md)



_Type used by master to send requests to slave._ [More...](#detailed-description)

* `#include <SPI_InstructionSet.h>`













## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**mInstruct**](_s_p_i___instruction_set_8h.md#enum-minstruct) | [**Instruction**](structm_cmd.md#variable-instruction)  <br>_Instruction to slave._  |
|  float | [**fParam**](structm_cmd.md#variable-fparam)  <br>_Floating point parameter which wualifies the instruction._  |
|  int | [**iParam**](structm_cmd.md#variable-iparam)  <br>_Integer paramter which qualifies the instruction._  |


## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**mCmd**](structm_cmd.md#function-mcmd-1-3) ([**mInstruct**](_s_p_i___instruction_set_8h.md#enum-minstruct) Instruct, int i, float f) <br> |
|   | [**mCmd**](structm_cmd.md#function-mcmd-2-3) () <br> |
|   | [**mCmd**](structm_cmd.md#function-mcmd-3-3) (volatile [**mCmd**](structm_cmd.md) & rhs) <br> |
|  [**mCmd**](structm_cmd.md) & | [**operator=**](structm_cmd.md#function-operator) (const volatile [**mCmd**](structm_cmd.md) & rhs) <br> |
|  [**mCmd**](structm_cmd.md) & | [**operator=**](structm_cmd.md#function-operator-2) (const [**mCmd**](structm_cmd.md) & rhs) <br> |








# Detailed Description


Each transaction, following the initial handshake, the master will send a request and the slave will send a reply. Requests made by the master will always take the form of an [**mCmd**](structm_cmd.md) object, which contains a parameterised instance of the instruction set, mInstruct, which defines the class of repsonse expected by the slave. 


    
## Public Attributes Documentation


### <a href="#variable-instruction" id="variable-instruction">variable Instruction </a>


```cpp
mInstruct Instruction;
```


Defines the request made of the slave by the master during any transacion. mInstruct defines a finite set of requests which the master can make of the slave. 


        

### <a href="#variable-fparam" id="variable-fparam">variable fParam </a>


```cpp
float fParam;
```



### <a href="#variable-iparam" id="variable-iparam">variable iParam </a>


```cpp
int iParam;
```


## Public Functions Documentation


### <a href="#function-mcmd-1-3" id="function-mcmd-1-3">function mCmd [1/3]</a>


```cpp
inline mCmd::mCmd (
    mInstruct Instruct,
    int i,
    float f
) 
```



### <a href="#function-mcmd-2-3" id="function-mcmd-2-3">function mCmd [2/3]</a>


```cpp
inline mCmd::mCmd () 
```



### <a href="#function-mcmd-3-3" id="function-mcmd-3-3">function mCmd [3/3]</a>


```cpp
inline mCmd::mCmd (
    volatile mCmd & rhs
) 
```



### <a href="#function-operator" id="function-operator">function operator= </a>


```cpp
inline mCmd & mCmd::operator= (
    const volatile mCmd & rhs
) 
```



### <a href="#function-operator-2" id="function-operator-2">function operator= </a>


```cpp
inline mCmd & mCmd::operator= (
    const mCmd & rhs
) 
```



------------------------------
The documentation for this class was generated from the following file `SPI_InstructionSet.h`
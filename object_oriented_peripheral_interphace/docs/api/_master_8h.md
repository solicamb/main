
# File Master.h


[**File List**](files.md) **>** [**Master.h**](_master_8h.md)

[Go to the source code of this file.](_master_8h_source.md)



* `#include <Arduino.h>`
* `#include "SPI_InstructionSet.h"`










## Classes

| Type | Name |
| ---: | :--- |
| class | [**Master**](class_master.md) <br>_A monolithic class to encapsulate and abstract the slave's communication with the master._  |
| struct | [**UserInstructions**](struct_user_instructions.md) <br> |



## Public Attributes

| Type | Name |
| ---: | :--- |
|  const int | [**MAX\_USER\_INSTRUCTION\_NUMBER**](_master_8h.md#variable-max-user-instruction-number)   = = 5<br> |
|  [**Master**](class_master.md) | [**SensorMaster**](_master_8h.md#variable-sensormaster)  <br>_Auto-instantiated instance of_ [_**Master**_](class_master.md) _class, called during the privately implemented IRQ routine and accessible externally by main code._ |


## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**RequestHandler**](_master_8h.md#function-requesthandler) ([**mCmd**](structm_cmd.md) & Request) <br>_Function prototype for user-implemented IRQ method; called after handshake and the reconstruction of the request from the master._  |
|  void | [**SPI\_IRQ**](_master_8h.md#function-spi-irq) (void) <br>_Innaccesible IRQ, called on SS falling._  |







## Macros

| Type | Name |
| ---: | :--- |
| define  | [**SPI1\_NSS\_PIN**](_master_8h.md#define-spi1-nss-pin)  () PA4<br> |

## Public Attributes Documentation


### <a href="#variable-max-user-instruction-number" id="variable-max-user-instruction-number">variable MAX\_USER\_INSTRUCTION\_NUMBER </a>


```cpp
const int MAX_USER_INSTRUCTION_NUMBER;
```



### <a href="#variable-sensormaster" id="variable-sensormaster">variable SensorMaster </a>


```cpp
volatile Master SensorMaster;
```


## Public Functions Documentation


### <a href="#function-requesthandler" id="function-requesthandler">function RequestHandler </a>


```cpp
void RequestHandler (
    mCmd & Request
) 
```



### <a href="#function-spi-irq" id="function-spi-irq">function SPI\_IRQ </a>


```cpp
void SPI_IRQ (
    void
) 
```


## Macro Definition Documentation



### <a href="#define-spi1-nss-pin" id="define-spi1-nss-pin">define SPI1\_NSS\_PIN </a>


```cpp
#define SPI1_NSS_PIN () 
```



------------------------------
The documentation for this class was generated from the following file `Master.h`

# File Master.cpp


[**File List**](files.md) **>** [**Master.cpp**](_master_8cpp.md)

[Go to the source code of this file.](_master_8cpp_source.md)



* `#include <Arduino.h>`
* `#include "Master.h"`
* `#include "SPI_InstructionSet.h"`
* `#include <SPI.h>`
* `#include "SPI_Anything_Slave.h"`













## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**Master**](class_master.md) | [**SensorMaster**](_master_8cpp.md#variable-sensormaster)  <br>_Auto-instantiated instance of_ [_**Master**_](class_master.md) _class, called during the privately implemented IRQ routine and accessible externally by main code._ |


## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**SPI\_IRQ**](_master_8cpp.md#function-spi-irq) (void) <br>_Innaccesible IRQ, called on SS falling._  |








## Public Attributes Documentation


### <a href="#variable-sensormaster" id="variable-sensormaster">variable SensorMaster </a>


```cpp
volatile Master SensorMaster;
```


## Public Functions Documentation


### <a href="#function-spi-irq" id="function-spi-irq">function SPI\_IRQ </a>


```cpp
void SPI_IRQ (
    void
) 
```



------------------------------
The documentation for this class was generated from the following file `Master.cpp`
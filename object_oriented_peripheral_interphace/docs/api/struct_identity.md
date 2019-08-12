
# Struct Identity


[**Class List**](annotated.md) **>** [**Identity**](struct_identity.md)



_Type used to convey the Slave identity._ 

* `#include <SPI_InstructionSet.h>`













## Public Attributes

| Type | Name |
| ---: | :--- |
|  char | [**SensorName**](struct_identity.md#variable-sensorname)  <br>_String name of the slave. Used for informative reporting to user._  |
|  int | [**sensorChipSelect**](struct_identity.md#variable-sensorchipselect)  <br>_SPI chip select of the peripheral in question. Used by slave, but used by_ [_**Master**_](class_master.md) _._ |
|  int | [**sensorID**](struct_identity.md#variable-sensorid)  <br>_Single byte identitfication number._  |


## Public Functions

| Type | Name |
| ---: | :--- |
|  [**Identity**](struct_identity.md) & | [**operator=**](struct_identity.md#function-operator) (const volatile [**Identity**](struct_identity.md) & rhs) <br> |
|  [**Identity**](struct_identity.md) & | [**operator=**](struct_identity.md#function-operator-2) (const [**Identity**](struct_identity.md) & rhs) <br> |








## Public Attributes Documentation


### <a href="#variable-sensorname" id="variable-sensorname">variable SensorName </a>


```cpp
char SensorName[IDENTITY_SENSOR_NAME_LENGTH];
```



### <a href="#variable-sensorchipselect" id="variable-sensorchipselect">variable sensorChipSelect </a>


```cpp
int sensorChipSelect;
```



### <a href="#variable-sensorid" id="variable-sensorid">variable sensorID </a>


```cpp
int sensorID;
```


## Public Functions Documentation


### <a href="#function-operator" id="function-operator">function operator= </a>


```cpp
inline Identity & Identity::operator= (
    const volatile Identity & rhs
) 
```



### <a href="#function-operator-2" id="function-operator-2">function operator= </a>


```cpp
inline Identity & Identity::operator= (
    const Identity & rhs
) 
```



------------------------------
The documentation for this class was generated from the following file `SPI_InstructionSet.h`
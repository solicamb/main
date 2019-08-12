
# Class Identifiable


[**Class List**](annotated.md) **>** [**Identifiable**](class_identifiable.md)



_A class which models a Sensor/peripheral as an identifiable entity._ [More...](#detailed-description)

* `#include <Identifiable.h>`





Inherited by the following classes: [Sensor](class_sensor.md)










## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Identifiable**](class_identifiable.md#function-identifiable) (const int ChipSelect) <br>_A constructor._  |
|  int | [**getIDNumber**](class_identifiable.md#function-getidnumber) (void) <br>_Gets the identity number of the attached peripheral._  |
|  void | [**getSensorName**](class_identifiable.md#function-getsensorname) (char name) <br>_Gets the sensor name of the attached peripheral._  |
|  bool | [**hasIdentityChanged**](class_identifiable.md#function-hasidentitychanged) (void) <br>_Checks to seee whether the_ [_**Identity**_](struct_identity.md) _in local memory is different to the_[_**Identity**_](struct_identity.md) _advertised by peripheral._ |
|  void | [**updateIdentity**](class_identifiable.md#function-updateidentity) (void) <br>_Loads the_ [_**Identity**_](struct_identity.md) _advertised by the peripheral into local memory._ |








# Detailed Description


This class models a peripheral as an identifiable entity with ID number and string name. The class allows for the identity to be loaded from the peripheral and interrogated. 


    
## Public Functions Documentation


### <a href="#function-identifiable" id="function-identifiable">function Identifiable </a>


```cpp
Identifiable::Identifiable (
    const int ChipSelect
) 
```


Constructor for class which loads the identity of any connected SPI peripheral into local memory. 

**Parameters:**


* The Slave Select pin of the SPI peripheral in question. 



**See also:** [**updateIdentity**](class_identifiable.md#function-updateidentity). 



        

### <a href="#function-getidnumber" id="function-getidnumber">function getIDNumber </a>


```cpp
int Identifiable::getIDNumber (
    void
) 
```


Reports the identity number of the peripheral currently stored in local memory. 

**Returns:**

The sensor ID number. 





        

### <a href="#function-getsensorname" id="function-getsensorname">function getSensorName </a>


```cpp
void Identifiable::getSensorName (
    char name
) 
```


Reports the sensor name of the peripheral currently stored in local memory. 

**Parameters:**


* name is the character array into which the sensor name is loaded. 




        

### <a href="#function-hasidentitychanged" id="function-hasidentitychanged">function hasIdentityChanged </a>


```cpp
bool Identifiable::hasIdentityChanged (
    void
) 
```




**Returns:**

True if the stored [**Identity**](struct_identity.md) is different than the [**Identity**](struct_identity.md) advertised by the peripheral. 




**See also:** [**Identity**](struct_identity.md) 



        

### <a href="#function-updateidentity" id="function-updateidentity">function updateIdentity </a>


```cpp
void Identifiable::updateIdentity (
    void
) 
```



------------------------------
The documentation for this class was generated from the following file `Identifiable.h`
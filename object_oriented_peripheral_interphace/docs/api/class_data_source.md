
# Class DataSource


[**Class List**](annotated.md) **>** [**DataSource**](class_data_source.md)



_A class which models a Sensor/peripheral as an entity which is a source of data._ [More...](#detailed-description)

* `#include <DataSource.h>`





Inherited by the following classes: [Sensor](class_sensor.md)










## Public Functions

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








# Detailed Description


This class models a [**Sensor**](class_sensor.md) as a source of data. The convention in use is that any [**Sensor**](class_sensor.md) can store data such that it occupies a two dimensional float array with maximum dimensions NUMBER\_OF\_DATA\_ROWS x DATA\_ROW\_LENGTH. The data can either be treated as a square array, the dimensions of which can be requested, or as a series of 'vectors', the length of which can be requested. 


    
## Public Functions Documentation


### <a href="#function-datasource" id="function-datasource">function DataSource </a>


```cpp
DataSource::DataSource (
    const int ChipSelect
) 
```




**Parameters:**


* ChipSelect is the Slave Select pin of the SPI peripheral in question. 




        

### <a href="#function-getdataarray" id="function-getdataarray">function getDataArray </a>


```cpp
void DataSource::getDataArray (
    float DataVals
) 
```


Retrieves the entire two dimensionsal data array, irrespective of which elements/vectors are actually in use. 

**Parameters:**


* float is the array into which the data is written. 



**See also:** [**Data**](struct_data.md) 



        

### <a href="#function-getdatavector" id="function-getdatavector">function getDataVector </a>


```cpp
void DataSource::getDataVector (
    const MeasurementVectors VectorNumber,
    float DataVect
) 
```


Retrieves a singel row in the two dimesnional data array. 

**Parameters:**


* VectorNumber is the row in the data array to be retrieved. 
* float is the floating point array into which the data points will be written. 



**See also:** [**Data**](struct_data.md), [**MeasurementVectors**](_s_p_i___instruction_set_8h.md#enum-measurementvectors) 



        

### <a href="#function-getnumberofdatacolumns" id="function-getnumberofdatacolumns">function getNumberOfDataColumns </a>


```cpp
int DataSource::getNumberOfDataColumns (
    const MeasurementVectors VectorNumber
) 
```




**Parameters:**


* VectorNumber is an enumerated type referring to the row in the two dimensional data array. 



**Returns:**

The number of data points along a particular row/vector. 




**See also:** [**MeasurementVectors**](_s_p_i___instruction_set_8h.md#enum-measurementvectors), [**Data**](struct_data.md) 



        

### <a href="#function-getnumberofdatarows" id="function-getnumberofdatarows">function getNumberOfDataRows </a>


```cpp
int DataSource::getNumberOfDataRows (
    void
) 
```


Returns the number of 'vectors' (rows) which the sensor has used to store data. Ideally, one should utilise the result of this function to iterate through the vectors. 

**Returns:**

The number of vectors in use. 




**See also:** [**Data**](struct_data.md) 



        

### <a href="#function-getrowheadings" id="function-getrowheadings">function getRowHeadings </a>


```cpp
void DataSource::getRowHeadings (
    char Headings
) 
```


Each vector/row is assigned a heading to describe the nature of the data contained within that vector. Such as "Ambient Temperature". 

**Parameters:**


* char is the array of character arrays into which the headings are loaded. 



**See also:** [**Data**](struct_data.md) 



        

### <a href="#function-getrowunits" id="function-getrowunits">function getRowUnits </a>


```cpp
void DataSource::getRowUnits (
    char Units
) 
```


Each vector/row is assigned a Units string to define the units of the data contained within that vector. Such as "V" or "Amperes". 

**Parameters:**


* char is the array of character arrays into which the units are loaded. 



**See also:** [**Data**](struct_data.md) 



        

### <a href="#function-getvalueone" id="function-getvalueone">function getValueOne </a>


```cpp
float DataSource::getValueOne (
    void
) 
```




**Returns:**

The first data point in the first vector. DataArray[0][0]. 




**See also:** [**Data**](struct_data.md), [**MeasurementVectors**](_s_p_i___instruction_set_8h.md#enum-measurementvectors) 



        

### <a href="#function-getvaluethree" id="function-getvaluethree">function getValueThree </a>


```cpp
float DataSource::getValueThree (
    void
) 
```




**Returns:**

The third data point in the first vector. DataArray[2][0]. 




**See also:** [**Data**](struct_data.md), [**MeasurementVectors**](_s_p_i___instruction_set_8h.md#enum-measurementvectors) 



        

### <a href="#function-getvaluetwo" id="function-getvaluetwo">function getValueTwo </a>


```cpp
float DataSource::getValueTwo (
    void
) 
```




**Returns:**

The second data point in the first vector. DataArray[1][0]. 




**See also:** [**Data**](struct_data.md), [**MeasurementVectors**](_s_p_i___instruction_set_8h.md#enum-measurementvectors) 



        

### <a href="#function-getvectorheading" id="function-getvectorheading">function getVectorHeading </a>


```cpp
void DataSource::getVectorHeading (
    const MeasurementVectors VectorNumber,
    char Heading
) 
```




**Parameters:**


* VectorNumber is the row in the data array to which the heading coresponds. 



**See also:** [**getRowHeadings()**](class_data_source.md#function-getrowheadings), [**Data**](struct_data.md), [**MeasurementVectors**](_s_p_i___instruction_set_8h.md#enum-measurementvectors) 



        

### <a href="#function-getvectorlength" id="function-getvectorlength">function getVectorLength </a>


```cpp
int DataSource::getVectorLength (
    const MeasurementVectors VectorNumber
) 
```


The data vectors (rows) have a max length of DATA\_ROW\_LENGTH and the [**Sensor**](class_sensor.md) will push data points into said vector. As the [**Sensor**](class_sensor.md) may not utilise the entire width of the data array, the length indicates the number of values which the [**Sensor**](class_sensor.md) has pushed into the vector in question. 

**Parameters:**


* VectorNumber is the row in the data array. 



**See also:** [**Data**](struct_data.md), [**MeasurementVectors**](_s_p_i___instruction_set_8h.md#enum-measurementvectors) 



        

### <a href="#function-getvectorunits" id="function-getvectorunits">function getVectorUnits </a>


```cpp
void DataSource::getVectorUnits (
    const MeasurementVectors VectorNumber,
    char Units
) 
```




**Parameters:**


* VectorNumber is the row in the data array to which the heading coresponds. 



**See also:** [**getRowUnits()**](class_data_source.md#function-getrowunits), [**Data**](struct_data.md), [**MeasurementVectors**](_s_p_i___instruction_set_8h.md#enum-measurementvectors) 



        

### <a href="#function-istheredata" id="function-istheredata">function isThereData </a>


```cpp
bool DataSource::isThereData (
    void
) 
```


Asks the sensor whether the data is ready to be retrieved by the master. Slave's are, however, required to instantiate a [**Data**](struct_data.md) object and so premature loads thereof will not fail. 

**Returns:**

True if the data is ready to be collected from the [**Sensor**](class_sensor.md). 





        

### <a href="#function-loaddata" id="function-loaddata">function loadData </a>


```cpp
Data DataSource::loadData (
    void
) 
```


Loads the [**Data**](struct_data.md) object from the [**Sensor**](class_sensor.md) into local memory. 

**Returns:**

The [**Data**](struct_data.md) object loaded into local memory. User of accessors preffered. 




**See also:** [**getNumberOfDataColumns()**](class_data_source.md#function-getnumberofdatacolumns), [**getNumberOfDataRows()**](class_data_source.md#function-getnumberofdatarows), [**getRowHeadings()**](class_data_source.md#function-getrowheadings), [**getRowUnits()**](class_data_source.md#function-getrowunits), [**getDataArray()**](class_data_source.md#function-getdataarray), [**getDataVector()**](class_data_source.md#function-getdatavector), [**getVectorLength()**](class_data_source.md#function-getvectorlength), [**getVectorHeading()**](class_data_source.md#function-getvectorheading),[**getVectorUnits()**](class_data_source.md#function-getvectorunits), [**getValueOne()**](class_data_source.md#function-getvalueone),[**getValueTwo()**](class_data_source.md#function-getvaluetwo),[**getValueThree()**](class_data_source.md#function-getvaluethree) 



        

------------------------------
The documentation for this class was generated from the following file `DataSource.h`
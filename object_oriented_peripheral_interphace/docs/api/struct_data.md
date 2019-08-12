
# Struct Data


[**Class List**](annotated.md) **>** [**Data**](struct_data.md)



_Type used to encapsulate the data collected by the slave._ [More...](#detailed-description)

* `#include <SPI_InstructionSet.h>`













## Public Attributes

| Type | Name |
| ---: | :--- |
|  float | [**DataPoints**](struct_data.md#variable-datapoints)  <br>_Two dimensional array of data. Each row generally treated as an independent vector._  |
|  int | [**NumColumns**](struct_data.md#variable-numcolumns)  <br>_Number of data points currently stored in each row._  |
|  int | [**NumRows**](struct_data.md#variable-numrows)  <br>_Number of rows. Defined at compilation._  |
|  char | [**RowHeadings**](struct_data.md#variable-rowheadings)  <br>_String headings to describe the data in each row._  |
|  char | [**rowUnits**](struct_data.md#variable-rowunits)  <br>_String units to qualify the data in each row._  |


## Public Functions

| Type | Name |
| ---: | :--- |
|  [**Data**](struct_data.md) & | [**operator=**](struct_data.md#function-operator) (const volatile [**Data**](struct_data.md) & rhs) <br> |
|  [**Data**](struct_data.md) & | [**operator=**](struct_data.md#function-operator-2) (const [**Data**](struct_data.md) & rhs) <br> |








# Detailed Description


[**Data**](struct_data.md) is contained in a two dimensional array but generally modelled as a collection of 'vectors' or rows of data. Each row is allowed a variable number of data points, a string heading and a string unit. 


    
## Public Attributes Documentation


### <a href="#variable-datapoints" id="variable-datapoints">variable DataPoints </a>


```cpp
float DataPoints[NUMBER_OF_DATA_ROWS][DATA_ROW_LENGTH];
```



### <a href="#variable-numcolumns" id="variable-numcolumns">variable NumColumns </a>


```cpp
int NumColumns[NUMBER_OF_DATA_ROWS];
```



### <a href="#variable-numrows" id="variable-numrows">variable NumRows </a>


```cpp
int NumRows;
```



### <a href="#variable-rowheadings" id="variable-rowheadings">variable RowHeadings </a>


```cpp
char RowHeadings[NUMBER_OF_DATA_ROWS][ROW_HEADING_LENGTH];
```



### <a href="#variable-rowunits" id="variable-rowunits">variable rowUnits </a>


```cpp
char rowUnits[NUMBER_OF_DATA_ROWS][ROW_UNIT_LENGTH];
```


## Public Functions Documentation


### <a href="#function-operator" id="function-operator">function operator= </a>


```cpp
inline Data & Data::operator= (
    const volatile Data & rhs
) 
```



### <a href="#function-operator-2" id="function-operator-2">function operator= </a>


```cpp
inline Data & Data::operator= (
    const Data & rhs
) 
```



------------------------------
The documentation for this class was generated from the following file `SPI_InstructionSet.h`
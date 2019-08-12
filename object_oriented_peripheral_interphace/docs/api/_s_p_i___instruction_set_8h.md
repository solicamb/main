
# File SPI\_InstructionSet.h


[**File List**](files.md) **>** [**SPI\_InstructionSet.h**](_s_p_i___instruction_set_8h.md)

[Go to the source code of this file.](_s_p_i___instruction_set_8h_source.md)













## Classes

| Type | Name |
| ---: | :--- |
| struct | [**Data**](struct_data.md) <br>_Type used to encapsulate the data collected by the slave._  |
| struct | [**Identity**](struct_identity.md) <br>_Type used to convey the Slave identity._  |
| struct | [**mCmd**](structm_cmd.md) <br>_Type used by master to send requests to slave._  |
| struct | [**sCmd**](structs_cmd.md) <br>_Type used by slave to send reply to master,._  |

## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**MeasurementVectors**](_s_p_i___instruction_set_8h.md#enum-measurementvectors)  <br>_Enumeration to provide human-readable references to different rows in the_ [_**Data**_](struct_data.md) _array._ |
| enum  | [**mInstruct**](_s_p_i___instruction_set_8h.md#enum-minstruct)  <br>_Instruction set used by_ [_**Master**_](class_master.md) _to instruct/request responses from Slave._ |
| enum  | [**sInstruct**](_s_p_i___instruction_set_8h.md#enum-sinstruct)  <br>_Instruction set used by slave to instruct master._  |


## Public Attributes

| Type | Name |
| ---: | :--- |
|  const int | [**DATA\_ROW\_LENGTH**](_s_p_i___instruction_set_8h.md#variable-data-row-length)   = = 64<br> |
|  const int | [**IDENTITY\_SENSOR\_NAME\_LENGTH**](_s_p_i___instruction_set_8h.md#variable-identity-sensor-name-length)   = = 25<br> |
|  const int | [**NUMBER\_OF\_DATA\_ROWS**](_s_p_i___instruction_set_8h.md#variable-number-of-data-rows)   = = 3<br> |
|  const int | [**ROW\_HEADING\_LENGTH**](_s_p_i___instruction_set_8h.md#variable-row-heading-length)   = = 10<br> |
|  const int | [**ROW\_UNIT\_LENGTH**](_s_p_i___instruction_set_8h.md#variable-row-unit-length)   = = 5<br> |
|  const int | [**SLAVE\_COMMMAND\_STRING\_LENGTH**](_s_p_i___instruction_set_8h.md#variable-slave-commmand-string-length)   = = 40<br> |










## Public Types Documentation


### <a href="#enum-measurementvectors" id="enum-measurementvectors">enum MeasurementVectors </a>


```cpp
enum MeasurementVectors {
    First,
    Second,
    Third
};
```



### <a href="#enum-minstruct" id="enum-minstruct">enum mInstruct </a>


```cpp
enum mInstruct {
    PauseMeasurementForiParam,
    RestartMeasurementProcedure,
    ResetDevice,
    HowManyInstructions,
    NextCommandPlease,
    IsThereData,
    SendDataPlease,
    WhoAreYou,
    HowLongShouldIWait,
    BeginMeasurement,
    SitRep
};
```


During a single transaction, the [**Master**](class_master.md) will send a request, characterised by an [**mCmd**](structm_cmd.md) object, which contains an mInstruct object, integer and float. The mInstruct object will determine how the request is processed by the slave and will define the object type which the master must expect in reply. In general, the master will expect replies in the form of [**sCmd**](structs_cmd.md) objects. However, the slave may also send [**Data**](struct_data.md) and [**Identity**](struct_identity.md) objects in repsonse to specific mInstruct instances; in particular: SendDataPlease and WhoAreYou. 


        

### <a href="#enum-sinstruct" id="enum-sinstruct">enum sInstruct </a>


```cpp
enum sInstruct {
    DisplayInstructionAndWait,
    DisplayInstructionAndWaitForUser,
    DontDisplayAndWait,
    DontDisplayAndContinue,
    ACK,
    Yes,
    No,
    NAK,
    ReferToInt,
    ReferToFloat,
    ReferToString
};
```


During a single transaction, the master will request a reply, [**Data**](struct_data.md) or [**Identity**](struct_identity.md). Replies are characterised by an [**sCmd**](structs_cmd.md) object, which contains an sInstruct object, which defines the action which the slave requires of the master. 


        
## Public Attributes Documentation


### <a href="#variable-data-row-length" id="variable-data-row-length">variable DATA\_ROW\_LENGTH </a>


```cpp
const int DATA_ROW_LENGTH;
```



### <a href="#variable-identity-sensor-name-length" id="variable-identity-sensor-name-length">variable IDENTITY\_SENSOR\_NAME\_LENGTH </a>


```cpp
const int IDENTITY_SENSOR_NAME_LENGTH;
```



### <a href="#variable-number-of-data-rows" id="variable-number-of-data-rows">variable NUMBER\_OF\_DATA\_ROWS </a>


```cpp
const int NUMBER_OF_DATA_ROWS;
```



### <a href="#variable-row-heading-length" id="variable-row-heading-length">variable ROW\_HEADING\_LENGTH </a>


```cpp
const int ROW_HEADING_LENGTH;
```



### <a href="#variable-row-unit-length" id="variable-row-unit-length">variable ROW\_UNIT\_LENGTH </a>


```cpp
const int ROW_UNIT_LENGTH;
```



### <a href="#variable-slave-commmand-string-length" id="variable-slave-commmand-string-length">variable SLAVE\_COMMMAND\_STRING\_LENGTH </a>


```cpp
const int SLAVE_COMMMAND_STRING_LENGTH;
```



------------------------------
The documentation for this class was generated from the following file `SPI_InstructionSet.h`
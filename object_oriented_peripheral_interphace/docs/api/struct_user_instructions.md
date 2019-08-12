
# Struct UserInstructions


[**Class List**](annotated.md) **>** [**UserInstructions**](struct_user_instructions.md)





* `#include <Master.h>`













## Public Attributes

| Type | Name |
| ---: | :--- |
|  int | [**InstructionCounter**](struct_user_instructions.md#variable-instructioncounter)  <br> |
|  char | [**InstructionSet**](struct_user_instructions.md#variable-instructionset)  <br> |
|  [**sInstruct**](_s_p_i___instruction_set_8h.md#enum-sinstruct) | [**MasterInstructionSet**](struct_user_instructions.md#variable-masterinstructionset)  <br> |
|  int | [**NumOfInstructions**](struct_user_instructions.md#variable-numofinstructions)  <br> |
|  float | [**fParams**](struct_user_instructions.md#variable-fparams)  <br> |
|  int | [**iParams**](struct_user_instructions.md#variable-iparams)  <br> |


## Public Functions

| Type | Name |
| ---: | :--- |
|  [**UserInstructions**](struct_user_instructions.md) & | [**operator=**](struct_user_instructions.md#function-operator) (const volatile [**UserInstructions**](struct_user_instructions.md) & rhs) <br> |
|  [**UserInstructions**](struct_user_instructions.md) & | [**operator=**](struct_user_instructions.md#function-operator-2) (const [**UserInstructions**](struct_user_instructions.md) & rhs) <br> |








## Public Attributes Documentation


### <a href="#variable-instructioncounter" id="variable-instructioncounter">variable InstructionCounter </a>


```cpp
int InstructionCounter;
```



### <a href="#variable-instructionset" id="variable-instructionset">variable InstructionSet </a>


```cpp
char InstructionSet[MAX_USER_INSTRUCTION_NUMBER][SLAVE_COMMMAND_STRING_LENGTH];
```



### <a href="#variable-masterinstructionset" id="variable-masterinstructionset">variable MasterInstructionSet </a>


```cpp
sInstruct MasterInstructionSet[MAX_USER_INSTRUCTION_NUMBER];
```



### <a href="#variable-numofinstructions" id="variable-numofinstructions">variable NumOfInstructions </a>


```cpp
int NumOfInstructions;
```



### <a href="#variable-fparams" id="variable-fparams">variable fParams </a>


```cpp
float fParams[MAX_USER_INSTRUCTION_NUMBER];
```



### <a href="#variable-iparams" id="variable-iparams">variable iParams </a>


```cpp
int iParams[MAX_USER_INSTRUCTION_NUMBER];
```


## Public Functions Documentation


### <a href="#function-operator" id="function-operator">function operator= </a>


```cpp
inline UserInstructions & UserInstructions::operator= (
    const volatile UserInstructions & rhs
) 
```



### <a href="#function-operator-2" id="function-operator-2">function operator= </a>


```cpp
inline UserInstructions & UserInstructions::operator= (
    const UserInstructions & rhs
) 
```



------------------------------
The documentation for this class was generated from the following file `Master.h`
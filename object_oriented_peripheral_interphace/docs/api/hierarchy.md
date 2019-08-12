
# Class Hierarchy

This inheritance list is sorted roughly, but not completely, alphabetically:


* **class** [**Communicative**](class_communicative.md) _A class to manage communication with slave module._ 
* **class** [**DataSource**](class_data_source.md) _A class which models a Sensor/peripheral as an entity which is a source of data._   
  * **class** [**Sensor**](class_sensor.md) _A class which models a Sensor/peripheral._ 
* **class** [**Identifiable**](class_identifiable.md) _A class which models a Sensor/peripheral as an identifiable entity._   
  * **class** [**Sensor**](class_sensor.md) _A class which models a Sensor/peripheral._ 
* **class** [**Instructable**](class_instructable.md) _A class which models a Sensor/peripheral as entity which can recieve commands._   
  * **class** [**Sensor**](class_sensor.md) _A class which models a Sensor/peripheral._ 
* **class** [**Instructor**](class_instructor.md) _A class which models a Sensor/peripheral as entity which can issue instructions to the master._   
  * **class** [**Sensor**](class_sensor.md) _A class which models a Sensor/peripheral._ 
* **class** [**Master**](class_master.md) _A monolithic class to encapsulate and abstract the slave's communication with the master._ 
* **struct** [**Data**](struct_data.md) _Type used to encapsulate the data collected by the slave._ 
* **struct** [**Identity**](struct_identity.md) _Type used to convey the Slave identity._ 
* **struct** [**UserInstructions**](struct_user_instructions.md) 
* **struct** [**mCmd**](structm_cmd.md) _Type used by master to send requests to slave._ 
* **struct** [**sCmd**](structs_cmd.md) _Type used by slave to send reply to master,._ 
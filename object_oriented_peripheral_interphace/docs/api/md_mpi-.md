
# s Summary



|Members  |Descriptions   |
|-----|-----|
|`class`[`Communicative`](#class_communicative)  |A class to manage communication with slave module.   |
|`class`[`DataSource`](#class_data_source)  |A class which models a Sensor/peripheral as an entity which is a source of data.   |
|`class`[`Identifiable`](#class_identifiable)  |A class which models a Sensor/peripheral as an identifiable entity.   |
|`class`[`Instructable`](#class_instructable)  |A class which models a Sensor/peripheral as entity which can recieve commands.   |
|`class`[`Instructor`](#class_instructor)  |A class which models a Sensor/peripheral as entity which can issue instructions to the master.   |
|`class`[`Master`](#class_master)  |A monolithic class to encapsulate and abstract the slave's communication with the master.   |
|`class`[`Sensor`](#class_sensor)  |A class which models a Sensor/peripheral.   |
|`struct`[`Data`](#struct_data)  |Type used to encapsulate the data collected by the slave.   |
|`struct`[`Identity`](#struct_identity)  |Type used to convey the Slave identity.   |
|`struct`[`mCmd`](#structm_cmd)  |Type used by master to send requests to slave.   |
|`struct`[`sCmd`](#structs_cmd)  |Type used by slave to send reply to master,.   |



`struct`[`UserInstructions`](#struct_user_instructions) |


## class &lt;tt&gt;Communicative&lt;/tt&gt;



A class to manage communication with slave module.


This class is designed for SPI communication with a slave device. The class responsibilities include both SPI initialisation and fundamental transactions. The transaction protocol implemented follows the following flow: Clear SS -&gt; Send '?' to slave -&gt; recieve 'ACK' (0x06) from slave -&gt; send request [mCmd](#structm_cmd) -&gt; recieve sCmd/Data/Identity as expected -&gt; set SS. Where [mCmd](#structm_cmd), [sCmd](#structs_cmd), [Data](#struct_data) and [Identity](#struct_identity) are structures defined as types.


## Summary






|Members  |Descriptions   |
|-----|-----|
|`public`[`Communicative`](#class_communicative_1aa92e21c2c2b3ee8dda993872f6b0c73a)`(const int CS)`  |Constructor.   |
|`public`[`~Communicative`](#class_communicative_1a53c7f2ec58bfb99f0ea10e238705c3ce)`(void)`  |Destructor.   |
|`public bool`[`isPeripheralConnected`](#class_communicative_1ac3d11fc6a7b276a19b1d92cd19e9a046)`(void)`  |Checks whether Slave is connected.   |
|`public`[`sCmd`](#structs_cmd)[`RequestReply`](#class_communicative_1a4fe112ad5a3d693e39ae44dd43eaf0c1)`(const  mCmd )`  |Performs a complete transaction; expects Slave to Reply with [sCmd](#structs_cmd) object.   |
|`public`[`Identity`](#struct_identity)[`RequestIdentity`](#class_communicative_1a01ee3d76d85bad6123c4d4f6262c6c2d)`(const  mCmd )`  |Performs a complete transaction; expects Slave to Reply with [Identity](#struct_identity) object.   |
|`public`[`Data`](#struct_data)[`RequestData`](#class_communicative_1a0a56aaa3248edae66ccb13cbf2bf156a)`(const  mCmd )`  |Performs a complete transaction; expects Slave to Reply with a [Data](#struct_data) object.   |






## Members






    
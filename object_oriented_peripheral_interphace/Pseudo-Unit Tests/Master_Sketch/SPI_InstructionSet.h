#ifndef SPIINSTRUCTIONSET_H
#define SPIINSTRUCTIONSET_H

//! Instruction set used by slave to instruct master.
/*! During a single transaction, the master will request a reply, Data or Identity. 
    Replies are characterised by an sCmd object, which contains an sInstruct object,
    which defines the action which the slave requires of the master.
 */
typedef enum sInstruct{
  DisplayInstructionAndWait, /*!< Require the master to display the string contained within the sCmd object and pause for a duration defined by the integer parameter of the sCmd object */ 
  DisplayInstructionAndWaitForUser, /*!< Require the master to display the string contained within the sCmd object and pause until the user has confirmed adherence to the instruction. */ 
  DontDisplayAndWait, /*!< Require the master to pause for a duration defined by the integer parameter of the sCmd object */ 
  DontDisplayAndContinue, /*!< Require the master to take no action. Essentially a nop. */ 
  ACK, /*!< Slave acknowleges the master's command/response. */
  Yes, /*!< Respond affirmative. */
  No, /*!< Respond negative. */
  NAK, /*!< Slave unable to adhere to Master's command or understand it. */
  ReferToInt, /*!< Points master to the integer parameter of sCmd. */
  ReferToFloat, /*!< Points master to the float parameter of sCmd */
  ReferToString /*!< Points master to the string parameter of sCmd*/
}; 

//! Instruction set used by Master to instruct/request responses from Slave.
/*! During a single transaction, the Master will send a request, characterised by an mCmd object, which contains an mInstruct object, integer and float.
    The mInstruct object will determine how the request is processed by the slave and will define the object type which the master must expect in reply.
    In general, the master will expect replies in the form of sCmd objects. However, the slave may also send Data and Identity objects in repsonse to 
    specific mInstruct instances; in particular: SendDataPlease and WhoAreYou.
 */
typedef enum mInstruct{
  PauseMeasurementForiParam, /*!< Require Slave to pause for a duration specified by the integer parameter of mCmd. Expects sCmd{ACK or NAK} in response. */
  RestartMeasurementProcedure, /*!< Require Slave to restart the measurement procedure from the first instruction. Expects sCmd{ACK or NAK} in response. */
  ResetDevice, /*!< Require Slave to reset. Expects sCmd{ACK or NAK} in response. */
  HowManyInstructions, /*!< Request the slave to confirm the number of instructions in a measurement cycle. Expects sCmd{ReferToInt, int NumberOfInstructions} in response. */
  NextCommandPlease, /*!< Request the next instrction in the measurement cycle from the slave. Expects sCmd{sInstruct SomeInstruction, int PotentialIntParam, float PotentialFloatParam, char* PotentialStringParam} or sCmd{No} in response. */
  IsThereData, /*!< Requests slave to confirm that Data is ready for collection by master. Expects sCmd{Yes or No}. */
  SendDataPlease, /*!< Require slave to send the data object. Expects Data object in response. */
  WhoAreYou, /*!< Require the slave to send its Identity object; contains char* Name and int SensorID. Expects Identity object in response. */
  HowLongShouldIWait, /*!< Ask the slave whether the Master should pause before calling for the next instruction. Unused. Expects sCmd{ReferToInt, int PauseDuration} in reply. */
  BeginMeasurement, /*!< Instruct the slave to initiate its measurement cycle and expect the first instruction to be called for. Expects sCmd{ACK or NAK}. */
  SitRep /*!< Request good/bad status from slave. Unused. Expects sCmd{} in reply. */
};

const int SLAVE_COMMMAND_STRING_LENGTH = 40;

//! Type used by slave to send reply to master,
/*! Each transaction, following the initial handshake, the master will send a request and the slave will send a reply. Replied made by the
    slave are generally in the form of an sCmd object, which contains a parameterised instance of the slave instruction set, sInstruct, which
    defines the action which the slave requires the master to carry out. Other acceptable replies to particular requests from the master are
    Data and Identity objects.
 */
typedef struct sCmd{
  //! Instruction to master.
  /*!
    Defines the reply made by the slave in repsonse to the request posed by the master during a single transaction. Used to confirm 
    commands issued by the master or issue commands to the master.
  */
  sInstruct Instruction; 
  //! String parameter which qualifies the instruction. Often used to convey instructions which are to be displayed to the user.
  char sParam[SLAVE_COMMMAND_STRING_LENGTH];
  //! Integer parameter which qualifies the instruction.
  int iParam;
  //! Floating point parameter which qualifies the instruction.
  float fParam;

  sCmd& operator = (const volatile sCmd& rhs) volatile{
    this->Instruction = rhs.Instruction;
    this->iParam = rhs.iParam;
    this->fParam = rhs.fParam;

    for (int i = 0; i<SLAVE_COMMMAND_STRING_LENGTH;i++){
      this->sParam[i] = rhs.sParam[i];
    }

  }

  volatile sCmd& operator = (const sCmd& rhs) volatile{
    this->Instruction = rhs.Instruction;
    this->iParam = rhs.iParam;
    this->fParam = rhs.fParam;

    for (int i = 0; i<SLAVE_COMMMAND_STRING_LENGTH;i++){
      this->sParam[i] = rhs.sParam[i];
    }

  }
};

//! Type used by master to send requests to slave.
/*! Each transaction, following the initial handshake, the master will send a request and the slave will send a reply. Requests made by
    the master will always take the form of an mCmd object, which contains a parameterised instance of the instruction set, mInstruct,
    which defines the class of repsonse expected by the slave.
 */
typedef struct mCmd{
  //! Instruction to slave.
  /*!
    Defines the request made of the slave by the master during any transacion. mInstruct defines a finite set of requests
    which the master can make of the slave.
  */
  mInstruct Instruction;
  //! Integer paramter which qualifies the instruction.
  int iParam;
  //! Floating point parameter which wualifies the instruction.
  float fParam;

  // mCmd(const mCmd& rhs){
  //   this->Instruction = rhs.Instruction;
  //   this->iParam = rhs.iParam;
  //   this->fParam = rhs.fParam;
  // }

  mCmd(mInstruct Instruct,int i, float f){
    this->Instruction = Instruct;
    this->iParam = i;
    this->fParam = f;
  }

  mCmd(){
    this->Instruction = SitRep;
    this->iParam = 0;
    this->fParam=0.0;
  }

  mCmd(volatile mCmd& rhs){
    this->Instruction = rhs.Instruction;
    this->iParam = rhs.iParam;
    this->fParam = rhs.fParam;
  }

  mCmd& operator = (const volatile mCmd& rhs) volatile{
    this->Instruction = rhs.Instruction;
    this->iParam = rhs.iParam;
    this->fParam = rhs.fParam;
  }

  volatile mCmd& operator = (const mCmd& rhs) volatile{
    this->Instruction = rhs.Instruction;
    this->iParam = rhs.iParam;
    this->fParam = rhs.fParam;
  }
};

const int IDENTITY_SENSOR_NAME_LENGTH = 25;


//! Type used to convey the Slave identity.
typedef struct Identity{
  //! String name of the slave. Used for informative reporting to user.
  char SensorName[IDENTITY_SENSOR_NAME_LENGTH];
  //! Single byte identitfication number.
  int sensorID;
  //! SPI chip select of the peripheral in question. Used by slave, but used by Master.
  int sensorChipSelect;

  Identity& operator = (const volatile Identity& rhs) volatile
    {
      for (int i =0; i<IDENTITY_SENSOR_NAME_LENGTH; i++){
        this->SensorName[i] = rhs.SensorName[i];
      }

      this->sensorID = rhs.sensorID;

      this->sensorChipSelect = rhs.sensorChipSelect;
    }

    volatile Identity& operator = (const Identity& rhs) volatile
    {
      for (int i =0; i<IDENTITY_SENSOR_NAME_LENGTH; i++){
        this->SensorName[i] = rhs.SensorName[i];
      }

      this->sensorID = rhs.sensorID;

      this->sensorChipSelect = rhs.sensorChipSelect;
    }
};

const int NUMBER_OF_DATA_ROWS = 3;
const int ROW_HEADING_LENGTH = 10;
const int ROW_UNIT_LENGTH = 5;
const int DATA_ROW_LENGTH = 64;

//! Type used to encapsulate the data collected by the slave.
/*! Data is contained in a two dimensional array but generally modelled as a collection of 'vectors' or rows of data.
    Each row is allowed a variable number of data points, a string heading and a string unit.
 */
typedef struct Data{
  //! Number of data points currently stored in each row.
  int NumColumns[NUMBER_OF_DATA_ROWS];
  //! Number of rows. Defined at compilation.
  int NumRows;
  //! String headings to describe the data in each row.
  char RowHeadings[NUMBER_OF_DATA_ROWS][ROW_HEADING_LENGTH];
  //! String units to qualify the data in each row.
  char rowUnits[NUMBER_OF_DATA_ROWS][ROW_UNIT_LENGTH];
  //! Two dimensional array of data. Each row generally treated as an independent vector.
  float DataPoints[NUMBER_OF_DATA_ROWS][DATA_ROW_LENGTH];

  Data& operator = (const volatile Data& rhs) volatile
    {
      this->NumRows = rhs.NumRows;

      for (int i = 0; i<NUMBER_OF_DATA_ROWS; i++){
        this->NumColumns[i] = rhs.NumColumns[i];

        for(int j = 0; j<ROW_HEADING_LENGTH; j++){
          this->RowHeadings[i][j] = rhs.RowHeadings[i][j];
        }


        for(int j = 0; j<ROW_UNIT_LENGTH; j++){
          this->rowUnits[i][j] = rhs.rowUnits[i][j];
        }
        

        for(int j = 0; j<DATA_ROW_LENGTH; j++){
          this->DataPoints[i][j] = rhs.DataPoints[i][j];
        }  

      }
    }

    volatile Data& operator = (const Data& rhs) volatile
    {
      this->NumRows = rhs.NumRows;

      for (int i = 0; i<NUMBER_OF_DATA_ROWS; i++){
        this->NumColumns[i] = rhs.NumColumns[i];

        for(int j = 0; j<ROW_HEADING_LENGTH; j++){
          this->RowHeadings[i][j] = rhs.RowHeadings[i][j];
        }


        for(int j = 0; j<ROW_UNIT_LENGTH; j++){
          this->rowUnits[i][j] = rhs.rowUnits[i][j];
        }
        

        for(int j = 0; j<DATA_ROW_LENGTH; j++){
          this->DataPoints[i][j] = rhs.DataPoints[i][j];
        }  

      }
    }
};

//! Enumeration to provide human-readable references to different rows in the Data array.
typedef enum MeasurementVectors{
    First,
    Second,
    Third
};

#endif

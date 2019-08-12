
// ensure this library description is only included once
#ifndef Master_h 
#define Master_h

// include types & constants of Wiring core API
#include <Arduino.h>
#include "SPI_InstructionSet.h"
#define SPI1_NSS_PIN PA4 

const int MAX_USER_INSTRUCTION_NUMBER = 5;

typedef struct UserInstructions{
  int NumOfInstructions;
  int InstructionCounter;
  char InstructionSet[MAX_USER_INSTRUCTION_NUMBER][SLAVE_COMMMAND_STRING_LENGTH];
  sInstruct MasterInstructionSet[MAX_USER_INSTRUCTION_NUMBER];
  int iParams[MAX_USER_INSTRUCTION_NUMBER];
  float fParams[MAX_USER_INSTRUCTION_NUMBER];

  UserInstructions& operator = (const volatile UserInstructions& rhs) volatile{
    this->NumOfInstructions = rhs.NumOfInstructions;
    this->InstructionCounter = rhs.InstructionCounter;

    for (int i =0; i<MAX_USER_INSTRUCTION_NUMBER;i++){
      this->iParams[i] = rhs.iParams[i];
      this->fParams[i] = rhs.fParams[i];
      this->MasterInstructionSet[i] = rhs.MasterInstructionSet[i];

      for (int j=0;j<SLAVE_COMMMAND_STRING_LENGTH;j++){
        this->InstructionSet[i][j] = rhs.InstructionSet[i][j];
      }
    }
  }

  volatile UserInstructions& operator = (const  UserInstructions& rhs) volatile{
    this->NumOfInstructions = rhs.NumOfInstructions;
    this->InstructionCounter = rhs.InstructionCounter;

    for (int i =0; i<MAX_USER_INSTRUCTION_NUMBER;i++){
      this->iParams[i] = rhs.iParams[i];
      this->fParams[i] = rhs.fParams[i];
      this->MasterInstructionSet[i] = rhs.MasterInstructionSet[i];

      for (int j=0;j<SLAVE_COMMMAND_STRING_LENGTH;j++){
        this->InstructionSet[i][j] = rhs.InstructionSet[i][j];
      }
    }
  }
};

// library interface description
//!  A monolithic class to encapsulate and abstract the slave's communication with the master.
/*!
  A single transaction is characterised by the following flow of control: Clear SS -> Enter IRQ -> Recieve '?' from master -> send 'ACK' (0x06) to master -> recieve request mCmd -> send sCmd/Data/Identity as expected -> exit IRQ.
  Where mCmd, sCmd, Data and Identity are structures defined as types. The intial Recieve '?' -> send 'ACK' is known as the handshake.
  This class' responsibilities include intitialising and handling the SPI, attaching the interrupt and providing the IRQ, managing the handshake and
  encapsulating the reponse mechanism. Note the use of a volatile interface to allow for safe use of the interrupt.
*/
class Master
{
  // user-accessible "public" interface
  public:
    Master(const int SensorIDNumber, const char SensorName[], const char InstructionSet[][SLAVE_COMMMAND_STRING_LENGTH], const int NumberOfInstructions, const sInstruct MasterInstructionSet[], const int intParams[], const float floatParams[]);
    Master(void);
    ~Master(void);
    Master(volatile const Master&);
    volatile Master& operator = (const  Master& rhs) volatile{
      this->CurrentRequest = rhs.CurrentRequest;
      this->ThisSensorID = rhs.ThisSensorID;
      this->MeasurementData = rhs.MeasurementData;
      this->UserInstructionSet = rhs.UserInstructionSet;
    }

    volatile Master& operator = (volatile const  Master& rhs) volatile{
      this->CurrentRequest = rhs.CurrentRequest;
      this->ThisSensorID = rhs.ThisSensorID;
      this->MeasurementData = rhs.MeasurementData;
      this->UserInstructionSet = rhs.UserInstructionSet;
    }

    //! Set up of the commuication mechanism.
    /*!
      Intialised the auto-instantiated Master object, attaches the IRQ and sets up SPI communications.
      \param SensorIDNumber is the identity number of th slave.
      \param SensorName is the string name of the slave.
      \param InstructionSet is the array of strings associated with each instruction in the measuremnt cycle. Generally to be displayed to the user.
      \param NumberOfInstructions is the number of instructions in a single measurement cycle/procedure.
      \param MasterInstructionSet is the array of sInstruct objects associated with each instruction in the measurement cycle. Defines the required action by the master for each step of the measurement procedure.
      \param IntParams is the array of integer parameter associated with each instruction.
      \param FloatParams is the array of floating point parameters accosiated with each instruction.
    */
    void SETUP(const int SensorIDNumber, volatile char SensorName[], volatile char InstructionSet[][SLAVE_COMMMAND_STRING_LENGTH], const int NumberOfInstructions, volatile sInstruct MasterInstructionSet[], volatile int intParams[], volatile float floatParams[]) volatile;
    //! Sets up SPI and attaches interrupt.
    void SPISetup(void) volatile;

    //Communications Interface
      //! Manages the handshake component of any transaction.
       /*!
        Manages the handshake between master and slave; defined by: Recieve '?' -> send 'ACK' (0x06).
        \return True if the handshake was successful.
       */
      bool Handshake(void) volatile;
      //! Retrieve the request sent by the master.
       /*!
        After each handshake, the master will proceed to send a request, defined by an mCmd object. This function must runafter each handshake.
        This function reassembles the mCmd request sent by the master, byte by byte and stores it in local memory.
        \return the mCmd object sent by the master.
       */
      mCmd loadRequest(void) volatile;
      //! Returns the mInstruct component of the most recently loaded request sent by the master.
      mInstruct getCurrentInstruction(void) volatile;\
      //! Returns the integer parameter of the most recently loaded request sent by the master.
      int getCurrentInstructionIntParameter(void) volatile;
      //! Returns the floating point parameter of the most recently loaded request sent by the master.
      float getCurrentInstructionFloatParameter(void) volatile;

      //! Send an sCmd object in reply to the request recieved from Master.
      void sendReply(const sCmd Reply) volatile;
      //! Send a reply to the request recieved from master.
      /*!
        Assembles the sCmd object from the supplied parameters. Overloaded.
       */
      void sendReply(const sInstruct Instruction) volatile;
      //! Send a reply to the request recieved from master.
      /*!
        Assembles the sCmd object from the supplied parameters. Overloaded.
        Note the need for the char* to be defined locally as volatile char[]. Cannot pass string literals.
       */
      void sendReply(const sInstruct Instruction, volatile char InstructionString[SLAVE_COMMMAND_STRING_LENGTH]) volatile;
       //! Send a reply to the request recieved from master.
      /*!
        Assembles the sCmd object from the supplied parameters. Overloaded.
       */
      void sendReply(const sInstruct Instruction, const int iParam) volatile;
       //! Send a reply to the request recieved from master.
      /*!
        Assembles the sCmd object from the supplied parameters. Overloaded.
       */
      void sendReply(const sInstruct Instruction, const float fParam) volatile;
       //! Send a reply to the request recieved from master.
      /*!
        Assembles the sCmd object from the supplied parameters. Overloaded.
       */
      void sendReply(const sInstruct Instruction, const int iParam, const int fParam) volatile;
       //! Send a reply to the request recieved from master.
      /*!
        Assembles the sCmd object from the supplied parameters. Overloaded.
        Note the need for the char* to be defined locally as volatile char[]. Cannot pass string literals.
       */
      void sendReply(sInstruct Instruction, int iParam, volatile char InstructionString[SLAVE_COMMMAND_STRING_LENGTH]) volatile;
       //! Send a reply to the request recieved from master.
      /*!
        Assembles the sCmd object from the supplied parameters. Overloaded.
        Note the need for the char* to be defined locally as volatile char[]. Cannot pass string literals.
       */
      void sendReply(sInstruct Instruction, float fParam, volatile char InstructionString[SLAVE_COMMMAND_STRING_LENGTH]) volatile;
       //! Send a reply to the request recieved from master.
      /*!
        Assembles the sCmd object from the supplied parameters. Overloaded.
        Note the need for the char* to be defined locally as volatile char[]. Cannot pass string literals.
       */
      void sendReply( sInstruct Instruction, int iParam, float fParam, volatile char InstructionString[SLAVE_COMMMAND_STRING_LENGTH]) volatile;

       //! Sends the local Data object to the master in reply to appropriate request.
      /*!
        Sends Data object to the master in reponse to a request made by the master for Data. NOTE: This must be used as the response
        to the appropriate mInstruct request. In paricular, (mInstruct)SendDataPlease 
       */
      void sendData(void) volatile;
      //! Sends slave Identity object to the master in reply to appropriate request.
      /*!
        Sends the slave Identity object in response to an appropriate request made by master. NOTE: This must be used as the response
        to the appropriate mInstruct request. In paricular, (mInstruct)WhoAreYou
       */
      void sendIdentity(void) volatile;

    //Data handling interface
      //! Pushes a data point onto one of the data vectors.
      /*!
        Adds a data point to the next available slot in a particular vector until the vector (row) in the data array is full.
        \param VectorNumber is the enumerated reference to the row/vector in the data array being accessed.
        \param Measurement is the data point to be stored.
        \return False if the vector/row in question is full. (See DATA_ROW_LENGTH).
       */
      bool PushMeasurementVector(const MeasurementVectors VectorNumber, const float Measurement) volatile;
      //! Pops a data point from the tail end of a designated vector.
      /*!
        Removes the most recent data point from the vector in question by marking said data slot writeable to be the next PushMeasurementVector().
        \param VectorNumber is the enumerated reference to the row/vector in the data array being accessed.
        \return False if the vector/row in question is empty.
       */
      bool PopMeasurementVector( MeasurementVectors VectorNumber) volatile;
      //! Clears all data points from a particular vector.
      /*!
        \param VectorNumber is the enumerated reference to the row/vector in the data array being accessed.
       */
      void ClearMeasurementVector(MeasurementVectors VectorNumber) volatile;
      //! Sets the string heading assigned to a paritcular data vector.
      /*!
        NOTE: The Heading parameter must be declared locally as volatile char[]. Literal strings cannot be passed to this function.
        \param VectorNumber is the enumerated reference to the row/vector in the data array in question.
        \param Heading[] is the character array containing the string heading.
       */
      void setMeasurementVectorHeading(MeasurementVectors VectorNumber, volatile char Heading[ROW_HEADING_LENGTH]) volatile;
      //! Sets the string Units assigned to a paritcular data vector.
      /*!
        NOTE: The Units parameter must be declared locally as volatile char[]. Literal strings cannot be passed to this function.
        \param VectorNumber is the enumerated reference to the row/vector in the data array in question.
        \param Units[] is the character array containing the string heading.
       */
      void setMeasurementVectorUnits(MeasurementVectors VectorNumber, volatile char Units[ROW_UNIT_LENGTH]) volatile;
      //! Checks to see whether any data has been pushed to any of the data vectors locally.
      /*!
        \return True if any data points exist in the data vectors locally.
       */
      bool isThereData(void) volatile;

    //User Instruction Interface
      //! Sends a reply to Master specifiying the total number of instructions in a measurement procedure.
      void sendTotalNumOfInstructions(void) volatile;
      //! Gets the value of the counter which tracks the current instruction number throughout the measurement procedure.
      int getCurrentInstructionNumber(void) volatile;
      //! Sends the next instruction in the measurement cycle to the master.
      /*!
        Sends the next instruction in the measurement cycle array in reponse to the appropriate request from master. Specifically, (mInstruct)NextCommandPlease.
        This method will auto-advance the measurement cycle to the next instruction and re-define the 'current instruction'.
        \return False if the final instruction in the measurement procedure has already been sent and the measurement procedure is now complete.
       */
      bool sendNextUserInstruction(void) volatile;
      //! Resends the cuurent instruction in the measurement procedure to the master.
      /*!
        This method will NOT advance the measurement cycle.
      */
      void resendCurrentUserInstruction(void) volatile;
      //! Restarts the measurement prcedure.
      /*!
        Restarts the measuement procedure such that the next instruction sent will be the first instruction in the measurement cycle.
      */
      void restartUserInstructionCycle(void) volatile;
      //! Updates state to indicate that Master has requested the intitiation of the measurement procedure.
      /*!
        Designed to allow the IRQ to update the slave state so that the procedural code in main() can initiate the measurement procedure.
      */
      void beginMeasurement(void) volatile;
      //! Checks whether the beginMeasurement() method has been called.
      /*!
        Allows procedural code in main() to determine whether the system state has changed during an interrupt in response to a request
        by the master to initiate the measurement procedure.
        */
      bool shallIStart(void) volatile;


  // library-accessible "private" interface
  private:
    template <typename T> unsigned int SPI_write (const T& value) volatile;
    template <typename T> unsigned int SPI_read(T& value) volatile;

    bool beginMeasurementYet;

    mCmd CurrentRequest;
  
    Identity ThisSensorID;
    Data MeasurementData;
    UserInstructions UserInstructionSet;
};

//! Innaccesible IRQ, called on SS falling.
void SPI_IRQ(void);

//! Function prototype for user-implemented IRQ method; called after handshake and the reconstruction of the request from the master.
void RequestHandler(mCmd& Request);

//! Auto-instantiated instance of Master class, called during the privately implemented IRQ routine and accessible externally by main code.
volatile extern Master SensorMaster;

#endif

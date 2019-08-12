
// ensure this library description is only included once
#ifndef DataSource_h
#define DataSource_h

// include types & constants of Wiring core API
#include <Arduino.h>
#include "SPI_InstructionSet.h"
#include "Instructable.h"

// library interface description
//!  A class which models a Sensor/peripheral as an entity which is a source of data.
/*!
  This class models a Sensor as a source of data. The convention in use is that any Sensor can store data such that it occupies a two dimensional
  float array with maximum dimensions NUMBER_OF_DATA_ROWS x DATA_ROW_LENGTH. The data can either be treated as a square array, the dimensions of which
  can be requested, or as a series of 'vectors', the length of which can be requested.
 */
class DataSource
{
  // user-accessible "public" interface
  public:

    //! Constructor
    /*!
      \param ChipSelect is the Slave Select pin of the SPI peripheral in question.
    */
    DataSource(const int ChipSelect);

    //! Asks Sensor/peripheral whether there is Data ready to be collected.
    /*!
      Asks the sensor whether the data is ready to be retrieved by the master. Slave's are, however, required to instantiate a Data object and
      so premature loads thereof will not fail.
      \return True if the data is ready to be collected from the Sensor.
    */
    bool isThereData(void);
    //! Loads Data from the Sensor.
    /*!
      Loads the Data object from the Sensor into local memory.
      \return The Data object loaded into local memory. User of accessors preffered.
      \sa getNumberOfDataColumns(), getNumberOfDataRows(), getRowHeadings(), getRowUnits(), getDataArray(), getDataVector(), getVectorLength(), getVectorHeading(),getVectorUnits(), getValueOne(),getValueTwo(),getValueThree()
    */
    Data loadData(void);

    //! Gets the number of data points along a particular row of the data array.
    /*!
      \param VectorNumber is an enumerated type referring to the row in the two dimensional data array.
      \return The number of data points along a particular row/vector. 
      \sa MeasurementVectors, Data
    */
    int getNumberOfDataColumns(const MeasurementVectors VectorNumber);
    //! Gets the number of rows used in the data array.
    /*!
      Returns the number of 'vectors' (rows) which the sensor has used to store data. Ideally, one should utilise the result of this 
      function to iterate through the vectors.
      \return The number of vectors in use. 
      \sa Data
    */
    int getNumberOfDataRows(void);

    //For handling data as square array
      //! Gets string headings of all the vectors in the data array.
      /*!
        Each vector/row is assigned a heading to describe the nature of the data contained within that vector. Such as "Ambient Temperature".
        \param char is the array of character arrays into which the headings are loaded.
        \sa Data
      */
      void getRowHeadings(char[NUMBER_OF_DATA_ROWS][ROW_HEADING_LENGTH]);
      //! Gets string units of all the vectors in the data array.
      /*!
        Each vector/row is assigned a Units string to define the units of the data contained within that vector. Such as "V" or "Amperes".
        \param char is the array of character arrays into which the units are loaded.
        \sa Data
      */
      void getRowUnits(char[NUMBER_OF_DATA_ROWS][ROW_UNIT_LENGTH]);
      //! Gets the entire data array.
      /*!
        Retrieves the entire two dimensionsal data array, irrespective of which elements/vectors are actually in use.
        \param float is the array into which the data is written.
        \sa Data
      */
      void getDataArray(float[NUMBER_OF_DATA_ROWS][DATA_ROW_LENGTH]);

    //For handling data as collection of 'vectors'
      //! Gets the indicated data vector
      /*!
        Retrieves a singel row in the two dimesnional data array.
        \param VectorNumber is the row in the data array to be retrieved.
        \param float is the floating point array into which the data points will be written.
        \sa Data, MeasurementVectors
      */
      void getDataVector(const MeasurementVectors VectorNumber, float[DATA_ROW_LENGTH]);
      //! Gets the indicated data vector length
      /*!
        The data vectors (rows) have a max length of DATA_ROW_LENGTH and the Sensor will push data points into said vector. As the Sensor
        may not utilise the entire width of the data array, the length indicates the number of values which the Sensor has pushed into
        the vector in question. 
        \param VectorNumber is the row in the data array.
        \sa Data, MeasurementVectors
      */
      int getVectorLength(const MeasurementVectors VectorNumber);
      //! Gets the string heading for the vector in question.
      /*!
        \param VectorNumber is the row in the data array to which the heading coresponds.
        \sa getRowHeadings(), Data, MeasurementVectors
      */
      void getVectorHeading(const MeasurementVectors VectorNumber, char[ROW_HEADING_LENGTH]);
      //! Gets the string units for the vector in question.
      /*!
        \param VectorNumber is the row in the data array to which the heading coresponds.
        \sa getRowUnits(), Data, MeasurementVectors
      */
      void getVectorUnits(const MeasurementVectors VectorNumber, char[ROW_UNIT_LENGTH]);

    //! Gets the first data point in the first vector.
      /*!
        \return The first data point in the first vector. DataArray[0][0].
        \sa  Data, MeasurementVectors
      */
    float getValueOne(void);
    //! Gets the second data point in the first vector.
      /*!
        \return The second data point in the first vector. DataArray[1][0].
        \sa  Data, MeasurementVectors
      */
    float getValueTwo(void);
    //! Gets the third data point in the first vector.
      /*!
        \return The third data point in the first vector. DataArray[2][0].
        \sa  Data, MeasurementVectors
      */
    float getValueThree(void);


  // library-accessible "private" interface
  private:
    Data CurrentData;
    Communicative CommsModule;

  };

#endif

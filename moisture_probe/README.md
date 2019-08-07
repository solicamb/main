This directory contains the code for the moisture retention probe.

# Development (debugging) version
There is a backend, which is the Arduino code for the microcontroller handling the measurements and transmitting them; and a frontend consisting of Python code plotting the data. It's purpose is to show the full data acquired during testing, and to save this data for further analysis.

For the latest moisture probe revisions based on BluePills, you can use the production version with a compile time flag set. See the `README` within [the BluePill development folder](./development/bluepill_devel).

# Production version
This consists of BluePill (STM32, Arduino-compatible, C) code that transmits a set of calculated, meaningful measures of soil health. Namely, a moisture level (wetness) and moisture retention (soil quality in resisting erosion) score is transmitted to the main device.

# Authorship
Initial version, 2019-07-16, jh2109

# Installation and dependencies
The Arduino code can be uploaded to any compatible board, testing has been performed on an Ardunio Uno and Micro. The BluePill code is compatible with the Arduino IDE once the STM32 has been installed via the board manager (see e.g. https://github.com/stm32duino/wiki/wiki/Getting-Started).

The supporting Python script used from a PC or Rasberry Pi is used to generate a csv file and display live sensor feedback. To run the python script some libraries should first be installed:

## Mac users
Python 3.x <br />
pip install pyqt5, pyqtgraph, pyserial

## Windows users
Python 3.x <br />
If using Anaconda or similar install pyserial, pyqtgraph and pyqt5


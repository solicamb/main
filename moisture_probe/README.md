This directory contains the code for the moisture retention probe.

# Development (debugging) version
There is a backend, which is the Arduino code for the microcontroller handling the measurements and transmitting them; and a frontend consisting of Python code plotting the data. It's purpose is to show the full data acquired during testing, and to save this data for further analysis.

# Production version
TBD This will consist of Arduino code that transmits a set of calculated, meaningful measures of soil health.

# Authorship
Initial version, 2019-07-16, jh2109

# Installation and dependencies
The Ardunio code can be uploaded to any compatable board, testing has been performed on an Ardunio Uno and Micro.
The supporting Python script used from a PC or Rasberry Pi is used to generate a csv file and display live sensor feedback. To run the python script some libraries should first be installed:

## Mac users
Python 3.x
	pip install pyqt5, pyqtgraph, pyserial

## Windows users
Python 3.x
	If using Anaconda or similar install pyserial, pyqtgraph and pyqt5



	

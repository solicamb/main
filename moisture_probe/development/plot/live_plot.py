#!/usr/bin/python3

# 
# Live plotting of data input from an Arduino via Serial in a defined, extensible data format (see Arduino code)
#
# Based on pyQtGraph for plotting with speed. Adjust MAX_POINTS for slower/faster computers (esp. Raspberry Pi)
# Porting this to any platform that support pyQtGraph should be straightforward, with only the PORT configuration and the serial_line.strip() call being platform-dependent
# 
# Authors:
#  Jan (jh2109)
# 
# NB In a possibly somewhat controversial move, I (jh2109) am refusing to adhere to PEP8 until somebody convinces me otherwise, meaning this file uses tabs and not spaces

import serial
import datetime
import re
import os
import csv
import numpy as np
from pyqtgraph.Qt import QtGui, QtCore
import pyqtgraph as pg


#
# CONFIG
#

# serial config
BAUDRATE = 38400
PORT = '/dev/ttyUSB0'

# plot config
MAX_POINTS = int(1e6)
DISPLAY_PREVIOUS_SECONDS = 30 # the plot is initially scaled such that the previous __ seconds are plotted, scrolling as time goes on
YRANGE = [1.0, 3.0] # initial plot y axis range

#
# MAIN
#

# Connect to serial port
ser = serial.Serial(PORT, BAUDRATE)

# Setup GUI
app = QtGui.QApplication([])
mw = QtGui.QMainWindow()
#mw.resize(800,800)
view = pg.GraphicsLayoutWidget() # GraphicsView with GraphicsLayout inserted by default
mw.setCentralWidget(view)
mw.show()
mw.setWindowTitle('Plot')

def quit_button_handler():
	global gui_command
	gui_command = 'quit' # The main loop acts on commands via this global variable

quitBtn = QtGui.QPushButton('Quit')
quitBtn.setParent(view)
quitBtn.show()
quitBtn.clicked.connect(quit_button_handler)
quitBtn.setStyleSheet("background-color: rgb(200,50,50)");

# Setup Plots
plt1 = view.addPlot()
startTime = pg.ptime.time()
plt1.setClipToView(True)
plt1.setRange(xRange=[-DISPLAY_PREVIOUS_SECONDS, 0])
plt1.setLimits(xMax=0)
plt1.setRange(yRange=YRANGE)
#plt1.setLabel('left', 'ADC voltage', units='V')
plt1.setLabel('left', 'Soil Dryness Measure (ADC voltage)', units='V')
plt1.setLabel('bottom', 'Time', units='s')
plt1.addLegend()

# Setup curves (i.e. graphs of the plot), one per measurement
curve0 = plt1.plot(pen=pg.mkPen((0, 255, 100), width=2), clipToView=True, name=". A0") # line only
#curve0 = plt1.plot(pen=pg.mkPen((0, 255, 100), width=2), symbol='o', symbolSize=5, symbolBrush=(0, 255, 100), clipToView=True, name=". A0") # with point markers
data_y0 = np.zeros((MAX_POINTS,2)) # Plot data buffer
ptr_y0 = 0 # Plot data buffer pointer

curve1 = plt1.plot(pen=pg.mkPen((255, 0, 100), width=2), clipToView=True, name=". A1") # line only
#curve1 = plt1.plot(pen=pg.mkPen((255, 0, 100), width=2), symbol='o', symbolSize=5, symbolBrush=(255, 0, 100), clipToView=True, name=". A1") # with point markers
data_y1 = np.zeros((MAX_POINTS,2)) # Plot data buffer
ptr_y1 = 0 # Plot data buffer pointer

curve2 = plt1.plot(pen=pg.mkPen((100, 0, 255), width=2), clipToView=True, name=". A2") # line only
#curve2 = plt1.plot(pen=pg.mkPen((100, 0, 255), width=2), symbol='o', symbolSize=5, symbolBrush=(100, 0, 255), clipToView=True, name=". A2") # with point markers
data_y2 = np.zeros((MAX_POINTS,2)) # Plot data buffer
ptr_y2 = 0 # Plot data buffer pointer

# Global variables
start_time = None # will be set to first ever data microcontroller timestamp to make times relative to start
TIME_START = datetime.datetime.now() # time of program start (from PC's point of view)
start_received = True # wait until microcontroller is ready and sends START. Otherwise we might catch trash still left in the serial buffer from previous runs
# TODO we set start_received to always on. This is because the bluepills don't self-reset on serial connection, so the user would need to press their reset button every time. Instead, log immediately
# TODO note that the downside of this is (and the reason why I implemented this code path in the first place) that the time axis now has an arbitrary offset (time since μC boot, not serial connection/program execution)
# TODO -> user should autoscale axis at beginning
gui_command = None # the main loop checks this global variable to act on GUI commands. Full rewrite to support interprocess signalling would be nice, but...

# Create subdirectories for data storage if they don't exist
filename_data = "./data/data-{}.csv".format(TIME_START.strftime("%Y_%m_%d-%H_%M_%S"))
for filename in [filename_data]:
	os.makedirs(os.path.dirname(filename), exist_ok=True)
	
# Write files
filehandle_data = open(filename_data, 'w')
csvwriter = csv.writer(filehandle_data, delimiter=';')

# Write CSV header to data file
name, t, val = 'variable_name', 'time(s)', 'value'
csvwriter.writerow([name, t, val])

# Wait for START signal
print("Waiting for START signal")

pg.QtGui.QApplication.processEvents() # Get up GUI. If we wait until START, slow PCs will have a noticeable lag
while True:
	serial_line = str(ser.readline())
	serial_line = serial_line.strip("\\r\\n'").strip("b'") # UNIX # Is there a less hack-ish way to make this cross-platform?
	#serial_line = serial_line.strip("\r\n").strip("b'") # Windows

	# GUI update (TODO write a proper async GUI application. Right now we are juggling two infinite loops: serial reading and GUI update)
	# Hand over to GUI thread until it is finished updating the plot
	pg.QtGui.QApplication.processEvents()

	# Echo to user
	print(serial_line)

	try: 
		# attempt to parse into one of the allowed message types; parsing fail means message was corrupted (or unexpected hardware etc. error)
		if serial_line == 'START':
			# Microcontroller has booted up succesfully
			start_received = True
			print("Beginning data acquisition")
			continue

		if start_received == False:
			# Microcontroller has not booted up succesfully yet, keep waiting
			continue

		if serial_line == 'STOP' or gui_command == 'quit':
			# Stopped
			print("Finished data acquisition. Data has been saved to disk as {}".format(filename_data))
			break

		if re.match('y\d;\d+;\d+',serial_line):
			# Data was logged (as opposed to info messages etc.); process it
			name, time_raw, val = serial_line.split(';')

			t = int(time_raw) / 1e3 # ms -> s
			val = float(val)

			if not start_time:
				# record first ever data timestamp to make times relative to it
				start_time = t

			t -= start_time # make times relative to start

			t = round(t, 3) # throw away spurious resolution. We are working with millis() i.e. millisecond resolution at best


			# Plot data according to its type (switch statement)
			if name == 'y0':
				if ptr_y0 >= len(data_y0):
					print("WARNING: plot point buffer (y0) full, restarting plot from beginning. Data saved to disk is not affected")
					ptr_y0 = 0

				# Update the plot data by writing incoming data into array
				data_y0[ptr_y0][0] = t
				data_y0[ptr_y0][1] = val

				# Tell pyQtGraph that the array has been updated
				curve0.setData(data_y0[:ptr_y0])

				# Shift curve to scroll left (i.e. rightmost point corresponds to new incoming data)
				now = pg.ptime.time()
				curve0.setPos(-(now-startTime), 0)

				# Update pointer of array
				ptr_y0 += 1

			elif name == 'y1':
				if ptr_y1 >= len(data_y1):
					print("WARNING: plot point buffer (y1) full, restarting plot from beginning. Data saved to disk is not affected")
					ptr_y1 = 0

				# Update the plot data by writing incoming data into array
				data_y1[ptr_y1][0] = t
				data_y1[ptr_y1][1] = val

				# Tell pyQtGraph that the array has been updated
				curve1.setData(data_y1[:ptr_y1])

				# Shift curve to scroll left (i.e. rightmost point corresponds to new incoming data)
				now = pg.ptime.time()
				curve1.setPos(-(now-startTime), 0)

				# Update pointer of array
				ptr_y1 += 1

			elif name == 'y2':
				if ptr_y2 >= len(data_y2):
					print("WARNING: plot point buffer (y2) full, restarting plot from beginning. Data saved to disk is not affected")
					ptr_y2 = 0

				# Update the plot data by writing incoming data into array
				data_y2[ptr_y2][0] = t
				data_y2[ptr_y2][1] = val

				# Tell pyQtGraph that the array has been updated
				curve2.setData(data_y2[:ptr_y2])

				# Shift curve to scroll left (i.e. rightmost point corresponds to new incoming data)
				now = pg.ptime.time()
				curve2.setPos(-(now-startTime), 0)

				# Update pointer of array
				ptr_y2 += 1

			# Save data to disk
			csvwriter.writerow([name, t, val])

			# Finished with tasks for this iteration of the main loop
			continue


	except:
		print("WARNING: Received malformed input, which was discarded:")
		print(serial_line)




#
# Finished
#

# Cleanup
filehandle_data.close()
ser.close()
app.closeAllWindows()

print("Done.")

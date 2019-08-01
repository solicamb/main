#!/usr/bin/python3
#
# Plot all the given data .csv files into a ./graphs directory as both .png and .pdf output for easier visual analysis
#
# Authors:
#  Jan (jh2109), Initial code base
#
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import sys
import os

# General setup
plt.rc('text', usetex=True)
plt.rc('font', family='sans-serif', size=12)
pi = np.pi

#
# Configuration
#
DELIMITER = ';'
SET_ASPECT_RATIO = False # Axis aspect ratio, e.g. 1 to have same scaling

# Labelling
#  LaTeX math example: u'Reference Temperature / $^\circ$C'
XLABEL = u'Time / s'
YLABEL1 = u'ADC voltage / V'
# Legend labels are done in the data import below, where columns are named

#
# main
#

# File paths from cmd line; output set to ./graphs
files_to_process = sys.argv[1:]
OUTPUT_FOLDER = './graphs'

if files_to_process == []:
	print("Missing command line arguments of .csv files to plot")
	print("Please specify the .csv files to plot (e.g. ./data/*.csv)")
	sys.exit(1)

if not os.path.exists(OUTPUT_FOLDER):
	# Create ./graphs if it doesn't exist yet
	os.mkdir(OUTPUT_FOLDER)

print("Beginning plotting")
# Iterate over all given data files
for DATA_FILENAME in files_to_process:
	# Load data
	print(DATA_FILENAME)
	data = pd.read_csv(DATA_FILENAME, delimiter=DELIMITER)

	# Separate into y0, y1, y2 datasets
	unique_names = data.variable_name.unique()
	data_dict = {elem : pd.DataFrame for elem in unique_names}
	for key in data_dict.keys():
			data_dict[key] = data[:][data.variable_name == key]

	# Define shorthands
	x0 = data_dict['y0']['time(s)']
	y0 = data_dict['y0']['value']
	Y0_LEGEND_LABEL = u'ADC 0'

	x1 = data_dict['y1']['time(s)']
	y1 = data_dict['y1']['value']
	Y1_LEGEND_LABEL = u'ADC 1'

	x2 = data_dict['y2']['time(s)']
	y2 = data_dict['y2']['value']
	Y2_LEGEND_LABEL = u'ADC 2'

	#
	# Plotting
	#
	fig, ax1 = plt.subplots()

	ax1.plot(x0, y0, label=Y0_LEGEND_LABEL, markersize=3, color='green')
	ax1.plot(x1, y1, label=Y1_LEGEND_LABEL, markersize=3, color='red')
	ax1.plot(x2, y2, label=Y2_LEGEND_LABEL, markersize=3, color='purple')

	# Axes tick marks
	#ax1.xaxis.set_major_locator(plt.MultipleLocator(20))		# x M
	#ax1.xaxis.set_minor_locator(plt.MultipleLocator(5))		# x m
	#ax1.yaxis.set_major_locator(plt.MultipleLocator(1))		# y1M
	#ax1.yaxis.set_minor_locator(plt.MultipleLocator(.1))		# y1m
	#ax2.yaxis.set_major_locator(plt.MultipleLocator(1))		# y2M
	#ax2.yaxis.set_minor_locator(plt.MultipleLocator(.25))	# y2m

	#
	# Figure setup
	#
	#plt.gcf().set_size_inches(13.85,10) # aspect ratio of given figure (measured):  9:6.5 = 1.385
	ax1.set_xlabel(XLABEL)
	ax1.set_ylabel(YLABEL1)
	ax1.legend()

	# Save figure
	plt.tight_layout()
	if SET_ASPECT_RATIO != False:
		plt.gca().set_aspect(SET_ASPECT_RATIO, adjustable='box')
	plt.savefig('{}/graph-{}.pdf'.format(OUTPUT_FOLDER, os.path.basename(DATA_FILENAME)), dpi=300, bbox_inches='tight')
	plt.savefig('{}/graph-{}.png'.format(OUTPUT_FOLDER, os.path.basename(DATA_FILENAME)), dpi=300, bbox_inches='tight')
	plt.close()

print("Done.")

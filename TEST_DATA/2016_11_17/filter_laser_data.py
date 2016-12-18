#!/usr/bin/env python

# File:     filter_laser_data.py
# Purpose:  Filter the and laser sensor data from accel_laser_data.csv and output original and filtered data
# Author:   Ryan Adams (@ninetimeout)
# Date:     2016-Dec-18

# Notes: maybe change alpha based on speed (slower speed = more reliance on old values; higher speed more reliance on samples? Seems confusing and possibly dangerous.)

################################################################
# Laser Sensor Processing
################################################################

# Global Variables
laser_sensor_alpha = 0.005  # larger alpha = higher reliance on current sample. Maybe move this elsewhere

# Laser sensor struct
class strLaserSensor:
    def __init__(self):
        current_value = 0.
        previous_value = 0.

def processLaserSensor(laser_sensor_struct, new_sample):
    """ Use an exponential moving average to filter laser sensor data """
    
    # Move us along
    laser_sensor_struct.previous_value = laser_sensor_struct.current_value
    
    # Calculate a new current_value
    # @see http://dsp.stackexchange.com/questions/20333/how-to-implement-a-moving-average-in-c-without-a-buffer
    laser_sensor_struct.current_value = laser_sensor_alpha * new_sample + (1 - laser_sensor_alpha) * laser_sensor_struct.previous_value
    
    return laser_sensor_struct.current_value
    

laser_l = strLaserSensor()
laser_r = strLaserSensor()
laser_aft = strLaserSensor()




################################################################
#  Everything below here is just .csv and file management
################################################################



# Note: command to create accel_laser_data.csv: 
#    python extract_laser_data.py -p "Flig*.csv" -o accel_laser_data.csv

import argparse
import csv
import glob

# Command line arguments
# @see http://stackoverflow.com/questions/11154946/argparse-require-either-of-two-arguments
parser = argparse.ArgumentParser(description="Utility for extracting I-beam laser sensor and accelerometer data from Flig_tellog .csv files. NOTE: You must supply either INPUT or PATTERN.")
input_pattern_group = parser.add_mutually_exclusive_group(required=True)
input_pattern_group.add_argument('-i', '--input', help=".csv file to import", required=False)
input_pattern_group.add_argument('-p', '--pattern', help="File matching pattern (e.g. Flig*.csv). Pattern must be in quotes.", required=False)
parser.add_argument('-o', '--output', help=".csv file to import", required=False, default=None)
args = parser.parse_args()
input_file = args.input


# Setup input files. Make it a list if we just have one to simplify the code
if args.input:
    input_filenames = [args.input]
elif args.pattern:
    input_filenames = glob.glob(args.pattern)


# Setup the channel indexes into the csv file (see go.m)
# @todo: where did these indices come from? 
# @todo: may need to offset all of these by 1 to get the right column...
col_indices = [
    ('timestamp', 0),
    ('ch_idx__accel_x', 57),
    ('ch_idx__accel_y', 60),
    ('ch_idx__accel_z', 63),
    ('ch_idx_laser_l_aft_height', 39),
    ('ch_idx_laser_r_aft_height', 42),
    ('ch_idx_laser_aft_yaw', 45),
]


def output_csv(input_filenames, col_indices, writer=None):
    """ Output csv data using list of input filenames, column indices, and an optional writer """
    
    for input_filename in input_filenames:

        with open(input_filename, 'rb') as infile:
            reader = csv.reader(infile)
            for row in reader:
                cols = [row[idx] for name, idx in col_indices]
                if writer is not None: 
                    writer.writerow(cols)
                else:
                    print ",".join(cols)


# Write output
if args.output is not None:
    with open(args.output, 'w+') as outfile:
        writer = csv.writer(outfile)
        output_csv(input_filenames, col_indices, writer)
else:
    output_csv(input_filenames, col_indices)
    
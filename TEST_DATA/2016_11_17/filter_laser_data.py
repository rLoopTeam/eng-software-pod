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
laser_sensor_alpha = 0.005  # larger alpha = higher reliance on current sample.

# Laser sensor struct
class strLaserSensor:
    def __init__(self):
        self.current_value = 0.
        self.previous_value = 0.
        
        # Maybe?
        self.confidence = 0.

def process_laser_sensor(laser_sensor_struct, new_sample):
    """ Use an exponential moving average to filter laser sensor data """
        
    # Move us along
    laser_sensor_struct.previous_value = laser_sensor_struct.current_value
    
    # Calculate a new current_value
    # @see http://dsp.stackexchange.com/questions/20333/how-to-implement-a-moving-average-in-c-without-a-buffer
    new_sample_influence = laser_sensor_alpha * new_sample
    old_value_influence = (1 - laser_sensor_alpha) * laser_sensor_struct.previous_value
    laser_sensor_struct.current_value = new_sample_influence + old_value_influence
    
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
parser = argparse.ArgumentParser(description="Example of processing laser sensor data function")
parser.add_argument('-i', '--input', help=".csv file to import", required=True)
parser.add_argument('-o', '--output', help="output .csv file", required=False, default=None)
args = parser.parse_args()
input_file = args.input


# Setup input files. Make it a list if we just have one to simplify the code
input_filename = args.input


# Setup the channel indexes into the csv file (see go.m)
# @todo: where did these indices come from? 
# @todo: may need to offset all of these by 1 to get the right column...
col_indices = [
    ('timestamp', 0),
    ('ch_idx__accel_x', 1),
    ('ch_idx__accel_y', 2),
    ('ch_idx__accel_z', 3),
    ('ch_idx_laser_l_aft_height', 4),
    ('ch_idx_laser_r_aft_height', 5),
    ('ch_idx_laser_aft_yaw', 6),
]


def output_csv(input_filename, col_indices, writer=None):
    """ Output csv data using list of input filenames, column indices, and an optional writer """
    
    with open(input_filename, 'rb') as infile:
        reader = csv.reader(infile)
        for row in reader:
            cols = [row[idx] for name, idx in col_indices]
            # Just hard code it for now -- process the laser sensors and append the values as new columns
            cols.append( str(process_laser_sensor(laser_l, float(row[4]))) )
            cols.append( str(process_laser_sensor(laser_r, float(row[5]))) )
            cols.append( str(process_laser_sensor(laser_aft, float(row[6]))) )
            if writer is not None: 
                writer.writerow(cols)
            else:
                print ",".join(cols)


# Write output
if args.output is not None:
    with open(args.output, 'w+') as outfile:
        writer = csv.writer(outfile)
        output_csv(input_filename, col_indices, writer)
else:
    output_csv(input_filename, col_indices)
    
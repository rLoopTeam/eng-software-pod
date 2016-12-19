#!/usr/bin/env python

# File:     filter_laser_data.py
# Purpose:  Filter the and laser sensor data from accel_laser_data.csv and output original and filtered data
# Author:   Ryan Adams (@ninetimeout)
# Date:     2016-Dec-18

# Running this file:  python filter_laser_data.py -i accel_laser_data.csv

################################################################
# Laser Sensor Processing
################################################################

# -----------------
# Structures
# -----------------

# Laser sensor struct
class strLaserSensor:
    def __init__(self):
        
        # Volatile values
        self.f32_current_value = 0.
        self.f32_previous_value = 0.

        # Stable values
        self.f32_alpha = 0.008  # @todo: how to calculate this? Based on sampling frequency? Varying based on speed? 

        # Configuration values (initialized later)
        self.int_sampling_rate_hz = 0
        self.f32_min_range_mm = 0.0
        self.f32_max_range_mm = 0.0


# -----------------
# Functions
# -----------------

# Function that processes the data coming in. Takes a laser sensor struct and a new sample as arguments, returns the new value
def process_laser_sensor(str_laser_sensor, f32_new_sample):
    """ Use an exponential moving average to filter laser sensor data """
    
    # If new sample is above f32_LASER_SENSOR_MAX_RANGE, it's a 'no value' -- keep our last value
    if f32_new_sample < str_laser_sensor.f32_max_range_mm:
        
        # Move us along
        str_laser_sensor.f32_previous_value = str_laser_sensor.f32_current_value
    
        # Calculate a new f32_current_value
        # @see http://dsp.stackexchange.com/questions/20333/how-to-implement-a-moving-average-in-c-without-a-buffer
        f32_new_sample_influence = str_laser_sensor.f32_alpha * f32_new_sample
        f32_old_value_influence = (1 - str_laser_sensor.f32_alpha) * str_laser_sensor.f32_previous_value
        str_laser_sensor.f32_current_value = f32_new_sample_influence + f32_old_value_influence
    
    return str_laser_sensor.f32_current_value

    
# -----------------
# Configuration
# -----------------

# Note: these could be put into an array in part of a substructure like the brakes or contrast sensors
# Just declare them in the global scope for now
laser_l = strLaserSensor()
laser_r = strLaserSensor()
laser_aft = strLaserSensor()

# Configure the laser sensors
# @todo: how do we handle configuration/calibration values in the FCU? e.g. setting zeros during calibration, etc.
laser_l.int_sampling_rate_hz = 250
laser_l.f32_min_range_mm = 0.0
laser_l.f32_max_range_mm = 50.0
laser_l.f32_alpha = 0.008  # @todo: how to calculate this? Based on sampling frequency? Varying based on speed? 

laser_r.int_sampling_rate_hz = 250.0
laser_r.f32_min_range_mm = 0.0
laser_r.f32_max_range_mm = 50.0
laser_r.f32_alpha = 0.008  # @todo: how to calculate this? Based on sampling frequency? Varying based on speed? 

laser_aft.int_sampling_rate_hz = 250.0
laser_aft.f32_min_range_mm = 0.0
laser_aft.f32_max_range_mm = 50.0
laser_aft.f32_alpha = 0.008  # @todo: how to calculate this? Based on sampling frequency? Varying based on speed? 

# Anything else we need to do? Do we want to calculate the alphas based on sampling frequency or something? 


#####################################################################
#  Everything below here is just .csv and file management
#  Description: A loop reads values from a .csv file and passes them 
#  to process_laser_sensor() along with the appropriate laser sensor 
#  struct (i.e. laser_l, laser_r, laser_aft). 
#####################################################################


import argparse
import csv
import glob

# Command line arguments
parser = argparse.ArgumentParser(description="Example of processing laser sensor data function")
parser.add_argument('-i', '--input', help=".csv file to import", required=True)
parser.add_argument('-o', '--output', help="output .csv file", required=False, default=None)
args = parser.parse_args()
input_file = args.input


# Setup input file
input_filename = args.input

# Setup the channel indexes into the csv file
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
            # Extract the columns. This is more necessary if you have specific data you want to read out of a larger file
            cols = [row[idx] for name, idx in col_indices]

            # Note: Just hard code the indices for now -- process the laser sensors and append the values as new columns
            cols.append( str(process_laser_sensor(laser_l, float(row[4]))) )
            cols.append( str(process_laser_sensor(laser_r, float(row[5]))) )
            cols.append( str(process_laser_sensor(laser_aft, float(row[6]))) )
            
            # Write or print the csv row
            if writer is not None: 
                writer.writerow(cols)
            else:
                print ",".join(cols)


# Handle output and call the output_csv function (which will read the csv)
if args.output is not None:
    with open(args.output, 'w+') as outfile:
        writer = csv.writer(outfile)
        output_csv(input_filename, col_indices, writer)
else:
    output_csv(input_filename, col_indices)
    
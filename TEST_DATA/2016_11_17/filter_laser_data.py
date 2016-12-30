#!/usr/bin/env python

# File:     filter_laser_data.py
# Purpose:  Filter the and laser sensor data from accel_laser_data.csv and output original and filtered data
# Author:   Ryan Adams (@ninetimeout)
# Date:     2016-Dec-18

# Running this file:  python filter_laser_data.py -i accel_laser_data.csv

################################################################
# Laser Sensor Processing
################################################################

###  This code is written in a style intended to be translated into c code.
###    - don't use fancy libraries (and most libraries are fancy. Think, "what's available in c?")
###    - no classes (except when they're used to emulate a struct) 
###    - indicate the types of all variables as a prefix (e.g. f32_myvar)
###    - if you're stuck, ask on #eng-embed slack channel

# -----------------
# Constants/ macros in c equivalent 
# -----------------
KALMAN_INITIAL_ESTIMATE_IN_MILLIMETERS          = 30.0 # this can be anything --> used test weekend data
KALMAN_INITIAL_ERROR_ESTIMATE_IN_MILLIMETERS    = 10.0 # this can be anything --> used test weekend data
KALMAN_ERROR_IN_MEASUREMENT_IN_MILLIMETERS      = 30.0 # 50mm is a bad value, 20 is good, just took the diff

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

class strKalmanFilter:
    def __init__(self):

        # The following two values will change every time we read sensor 
        self.f32_current_estimate = KALMAN_INITIAL_ESTIMATE_IN_MILLIMETERS
        self.f32_previous_estimate = 0
        
        self.f32_current_error_estimate = KALMAN_INITIAL_ERROR_ESTIMATE_IN_MILLIMETERS 
        self.f32_previous_error_estimate = 0        
 
        # Device or setup dependent, not expected to change
        self.f32_error_in_measurement = KALMAN_ERROR_IN_MEASUREMENT_IN_MILLIMETERS
        
        self.kalman_gain = self.f32_current_error_estimate / (self.f32_current_error_estimate + self.f32_error_in_measurement)

# -----------------
# Functions
# -----------------

# Function that processes the data coming in. Takes a laser sensor struct and a new sample as arguments, returns the new value
def process_laser_sensor(str_laser_sensor, f32_new_sample):
    """ Use an exponential moving average to filter laser sensor data """
    
    # If new sample is above the max range of this sensor, it's a 'no value' -- keep our last value
    if f32_new_sample < str_laser_sensor.f32_max_range_mm:
        
        # Move us along
        str_laser_sensor.f32_previous_value = str_laser_sensor.f32_current_value
    
        # Calculate a new f32_current_value
        # @see http://dsp.stackexchange.com/questions/20333/how-to-implement-a-moving-average-in-c-without-a-buffer
        f32_new_sample_influence = str_laser_sensor.f32_alpha * f32_new_sample
        f32_old_value_influence = (1 - str_laser_sensor.f32_alpha) * str_laser_sensor.f32_previous_value
        str_laser_sensor.f32_current_value = f32_new_sample_influence + f32_old_value_influence
    
    return str_laser_sensor.f32_current_value

def kalman_filter_init(kalman_filter):
    """ Initialize the estimates and error estimates of the
        kalman filter """
    kalman_filter.f32_previous_estimate         =  KALMAN_INITIAL_ESTIMATE_IN_MILLIMETERS
    kalman_filter.f32_previous_error_estimate   =  KALMAN_INITIAL_ERROR_ESTIMATE_IN_MILLIMETERS 

def process_laser_sensor_kalman(kalman_filter, f32_current_measurement):
    """
    Use 1-D Kalman filter to get better estimate on sensor information

    Filter explanation:
    The algorithm works in a two-step process. In the prediction
    step, the Kalman filter produces estimates of the current 
    state variables, along with their uncertainties. Once the 
    outcome of the next measurement (necessarily corrupted with 
    some amount of error, including random noise) is observed, 
    these estimates are updated using a weighted average, with 
    more weight being given to estimates with higher certainty. 

    Flow diagram: https://goo.gl/YooR9k
                                                                ^-----> this is the predicted value of sampled data 
                                                                |
    Read sample (from sensor) --> Calculate kalman_gain --> Calculate current_estimate --> Calculate new_estimate_error
            ^                                                                                           |
            |-------------------Ready for next Sensor/sample data--------<------------------------------V
    
    
    Three main calculations that need to be done:
    1) Find Kalman Gain (KG)
    2) Find Current Estimate of the sensor output
    3) Find new error/uncertainty in estimate
    
    kalman_gain = error_in_estimate / ( error_in_estimate + error_in_measurement )

    current_estimate = previous_estimate + ( kalman_gain * ( current_measurement -  previous_estimate ) )
    
    error_in_estimate = ( 1 - kalman_gain ) * (previous_error_in_estimate)    
    """ 
 
    # Calculate the new kalman_gain used for this iteration
    kalman_filter.kalman_gain = (kalman_filter.f32_previous_error_estimate 
                                 / (kalman_filter.f32_previous_error_estimate + kalman_filter.f32_error_in_measurement)) 
    
    # Find the predicted sensor value
    kalman_filter.f32_current_estimate = (kalman_filter.f32_previous_estimate 
                                          + (kalman_filter.kalman_gain * (f32_current_measurement - kalman_filter.f32_previous_estimate)))
    
    # Update the error estimate based on the new kalman_gain found. This will 
    # be used in predicting the next sample
    kalman_filter.f32_current_error_estimate = (1 - kalman_filter.kalman_gain) * kalman_filter.f32_previous_error_estimate 

    # Mark the calculated values as "previous". Will be used for predicting the
    # value of next sampled data from sensor 
    kalman_filter.f32_previous_error_estimate = kalman_filter.f32_current_error_estimate
    kalman_filter.f32_previous_estimate       = kalman_filter.f32_current_estimate

    return kalman_filter.f32_current_estimate

# -----------------
# Configuration
# -----------------

# Note: these could be put into an array in part of a substructure like the brakes or contrast sensors
# Just declare them in the global scope for now
laser_l = strLaserSensor()
laser_r = strLaserSensor()
laser_aft = strLaserSensor()

# Global kalman filter struct/object
kalman_filter_l = strKalmanFilter()
kalman_filter_r = strKalmanFilter()
kalman_filter_aft = strKalmanFilter()

kalman_filter_init(kalman_filter_l)
kalman_filter_init(kalman_filter_r)
kalman_filter_init(kalman_filter_aft)


# Configure the laser sensors
# @todo: how do we handle configuration/calibration values in the FCU? e.g. setting zeros during calibration, etc.
laser_l.int_sampling_rate_hz = 250.0
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

# Anything else we need to do? Do we want to calculate the alphas here based on sampling frequency or something? 


# -----------------
# Run/Test
# -----------------

#####################################################################
#  Everything below here is just .csv, file management, and run loop
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


# Main loop to read from the .csv, send values for processing, and create the output
def output_csv(input_filename, col_indices, writer=None):
    """ Output csv data using list of input filenames, column indices, and an optional writer """
    
    with open(input_filename, 'rb') as infile:
        reader = csv.reader(infile)
        for row in reader:
            # Extract the columns. This technique is more necessary if you have specific data you want to read out of a wider file
            cols = [row[idx] for name, idx in col_indices]

            # Process the laser sensor samples and append the returned values to the row
            # Note: Just hard code the indices for now -- 
            # Predict the sensor outputs using moving average
            cols.append( str(process_laser_sensor(laser_l, float(row[4]))) )
            cols.append( str(process_laser_sensor(laser_r, float(row[5]))) )
            cols.append( str(process_laser_sensor(laser_aft, float(row[6]))) )
            
            # predict the same sensor outputs using kalman filter 
            cols.append( str(process_laser_sensor_kalman(kalman_filter_l, float(row[4]))) )
            cols.append( str(process_laser_sensor_kalman(kalman_filter_r, float(row[5]))) )
            cols.append( str(process_laser_sensor_kalman(kalman_filter_aft, float(row[6]))) )
 
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
    

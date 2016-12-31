#!/usr/bin/env python

# File:     extract_laser_data.py
# Purpose:  Extract accelerometer and laser sensor data from Flig_tellog*.csv files
# Author:   Ryan Adams (@ninetimeout)
# Date:     2016-Dec-17
# @see:     go.m (Lachlan Grogan)

# Note: command to create accel_laser_data.csv: 
#    python extract_laser_data.py -p "Flig*.csv" -o accel_laser_data.csv

import argparse
import csv
import glob

# Command line arguments
# @see http://stackoverflow.com/questions/11154946/argparse-require-either-of-two-arguments
parser = argparse.ArgumentParser(description="Utility for extracting I-beam laser sensor and accelerometer data from Flig_tellog .csv files.")
input_pattern_group = parser.add_mutually_exclusive_group(required=True)
input_pattern_group.add_argument('-i', '--input', help=".csv file to import", required=False)
input_pattern_group.add_argument('-p', '--pattern', help="File matching pattern (e.g. Flig*.csv). Pattern must be in quotes.", required=False)
parser.add_argument('-o', '--output', help="output .csv file", required=False, default=None)
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
    

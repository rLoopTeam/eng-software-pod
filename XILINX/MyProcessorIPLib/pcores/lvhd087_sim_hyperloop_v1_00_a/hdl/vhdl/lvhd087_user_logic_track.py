#!/usr/bin/env python

# File:     lvhd087_user_logic_track.py
# Purpose:  Generate a code block for testing location of reflective strips that can be pasted into lvhd087_user_logic.vhd
# Author:   Ryan Adams (@ninetimeout)
# Date:     2017-Jan-01


# Stripped-down Tube class taken from https://github.com/rLoopTeam/eng-embed-sim/blob/master/src/tube.py, used only for reflective strips here
class Tube:

    def __init__(self, length, include_rumble_strips=False):
                
        # Physical
        # NOTE: @see diagram in http://confluence.rloop.org/display/SD/2.+Determine+Pod+Kinematics
        #       For the tube reference frame, x=0 at the start of the track, and x = length at the end.
        #       For the pod, x=0 is ahead and below the pod, with x+ being toward the read of the pod.
        self.length = length     # meters -- Length from pod start position to end of track
        self.include_rumble_strips = include_rumble_strips
        
        # Reference for the reflective stripes
        self.reflective_strip_width = 0.1016      # meters (4 inches)
        self.reflective_pattern_interval = 30.48  # meters (100 feet)
        self.reflective_pattern_spacing = 0.1016  # meters -- distance between stripes in a pattern

        # Initialize 
        self.reflective_strips = []
        self._init_reflective_strips()
        # self._init_strips_distance_remaining()  # @todo: finish this? or put it in the pod? 

    def _init_reflective_strips(self):
        # Add in the 100' strips (backwards)

        # Calculate the distance between strip edges in a pattern
        pattern_offset = self.reflective_strip_width + self.reflective_pattern_spacing

        cursor = self.length
        counter = 1  # 1 to account for the end of the tube

        while cursor > self.reflective_pattern_interval:  # Note: we'll put one in negative territory if we use 0 here
            cursor -= self.reflective_pattern_interval
            counter += 1
            self.reflective_strips.append(cursor)

            if self.include_rumble_strips:

                # Handle 500' pattern (5 strips)
                if counter == 5:
                    # Add the other 4 strips (we already added the 100' strip)
                    pattern = [cursor + (x+1) * pattern_offset for x in xrange(4)]
                    self.reflective_strips.extend(pattern)
            
                # Handle 1000' pattern (10 strips)
                if counter == 10:
                    # Add the other 9 strips (we already added the 100' strip)
                    pattern = [cursor + (x+1) * pattern_offset for x in xrange(9)]
                    self.reflective_strips.extend(pattern)
            
        # Sort and reverse for easy handling during the run
        self.reflective_strips = sorted(self.reflective_strips)

    def reflective_strips_distance_remaining_mm(self):
        # @todo: rename this or move it to a utils class/script
        strips_trf = [int((self.length - x) * 1000) for x in self.reflective_strips]
        #strips_trf.append(0)  # Add the last strip (the track end position) -- distance remaining = 0. @todo: is there a strip there? 
        return strips_trf
        
"""
    # Example taken from lvhd087_user_logic.vhd
	hloop_laser_o(0) <= '1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("30480000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("30582000000000000000000", s_displacement'length))) ) else
						'1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned("60960000000000000000000", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned("61062000000000000000000", s_displacement'length))) ) else


"""        
        

if __name__ == "__main__":
    import argparse
    
    parser = argparse.ArgumentParser(description="Generate reflective strip data code block to paste into lvhd087_user_logic.vhd file")
    parser.add_argument('-l', '--length', help="Length(s) of track to use for generating the reflective strips", type=int, required=True)
    parser.add_argument('-r', '--include_rumble_strips', help="Include 500' and 1000' rumble strips?", type=bool, required=False, default=False)
    args = parser.parse_args()

    tube = Tube(args.length, args.include_rumble_strips)
    remaining = sorted(tube.reflective_strips_distance_remaining_mm())
    template = "'1' when ( (s_displacement > std_logic_vector(decimal_string_to_unsigned(\"{}00000000000000000\", s_displacement'length))) and (s_displacement < std_logic_vector(decimal_string_to_unsigned(\"{}00000000000000000\", s_displacement'length))) )"

    lines = []
    for i, start_dist in enumerate(remaining):
        # Multiply by 10 so that we can add 101.6 without using decimals
        start_dist *= 10
        end_dist = start_dist + 1016
        lines.append(template.format(start_dist, end_dist))

    # Print everything. (@todo: this could be cleaned up to be more readable)
    print "\t--Lets assume track is {}m".format(args.length)
    print "\thloop_laser_o(0) <= " + (" else\n" + "\t"*6).join(lines)
    print ""
    print "\t"*6 + "else 0;"
    
    
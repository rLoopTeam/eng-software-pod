#!/usr/bin/env python

import sys
import os
import ctypes
import time

dll_path = "..\\APPLICATIONS\\PROJECT_CODE\\DLLS\\LDLL174__RLOOP__LCCM655\\bin\\Debug"
dll_name = "LDLL174__RLOOP__LCCM655.dll"
dll_filename = os.path.join(dll_path, dll_name)
print "DLL {} exists? {}".format(dll_filename, os.path.exists(dll_filename))
lib = ctypes.CDLL(dll_filename)
print "Lib loaded successfully!"

def errcheck_callback(result, func, arguments):
    if result is not None:  # @todo: should we do this? It seems that errcheck gets called when it is set up, with None as the result...
        print "Python errcheck_callback called: {}, {}, {}".format(result, func.__name__, arguments)

class StepdriveTimebaseTimer:
    
    def __init__(self, lib):
        self.lib = lib  # the dll
        self.vSTEPDRIVE_TIMEBASE__ISR = self.lib.vSTEPDRIVE_TIMEBASE__ISR
        self.vSTEPDRIVE_TIMEBASE__ISR.argtypes = []
        self.vSTEPDRIVE_TIMEBASE__ISR.restype = None
        self.vSTEPDRIVE_TIMEBASE__ISR.errcheck = errcheck_callback
        
        self.q = []

        self.calibration = 0.0000098

    def run(self):
        t0 = time.clock()
        for n in xrange(1000):
            t1 = time.clock()
            if t1 - t0 >= self.calibration:  # 10 microseconds, -.2usec for processing time
                self.q.append(t1 - t0)
                self.vSTEPDRIVE_TIMEBASE__ISR()
                t0 = t1
                
        
                
if __name__ == "__main__":
    import numpy as np
    
    timer = StepdriveTimebaseTimer(lib)
    timer.run()
    
    for t in timer.q:
        print "{0:.20f}".format(t)

    print "Average time between calls: {0:.20f}".format(np.mean(timer.q[3:]))  # Note: the first one or two might be a bit delayed, so we'll skip for averaging
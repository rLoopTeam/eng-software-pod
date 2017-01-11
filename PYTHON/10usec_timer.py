#!/usr/bin/env python

# Test a 10 microsecond timer in python on windows

import time

def measure_clock():
    t0 = time.clock()
    t1 = time.clock()
    while t1 == t0:
        t1 = time.clock()
    return (t0, t1, t1-t0)

t = reduce( lambda a,b:a+b, [measure_clock()[2] for i in range(1000000)] )/1000000.0

print "Resolution: {0:.20f}".format(t)

print "Let's try calling a function every 10usec:"

counter = 0
t0 = time.clock()
while counter < 100:
    t1 = time.clock()
    if t1 - t0 >= 0.00001:  # 10 microseconds
        print "{0:.20f}".format(t1 - t0)  # Note: print takes a while...
        t0 = t1
    counter += 1



class TimerTest:
    
    def __init__(self, n):
        self.n = n
        self.q = []
    
    def run(self):
        t0 = time.clock()
        for i in xrange(self.n):
            t1 = time.clock()
            if t1 - t0 >= 0.0000098:  # 10 microseconds, -.2usec for processing time
                self.q.append(t1 - t0)
                t0 = t1

print "-- Timer Test -----"

tt = TimerTest(1000)
tt.run()

import numpy as np

for t in tt.q:
    print "{0:.20f}".format(t)

print "Average time between calls: {0:.20f}".format(np.mean(tt.q))
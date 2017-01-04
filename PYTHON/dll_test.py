#!/usr/bin/env python

# NOTE: This must be done in a 32 bit version of python!
# @see http://stackoverflow.com/questions/33709391/using-multiple-python-engines-32bit-64bit-and-2-7-3-5

import sys
import os
import ctypes
import pprint


#dll_path = sys.argv[1]
dll_path = "C:\\Users\\radams\\Documents\\rLoop\\code\\eng-software-pod\\APPLICATIONS\\PROJECT_CODE\\DLLS\\LDLL173__RLOOP__LCCM653\\bin\\Debug"
dll_name = "LDLL173__RLOOP__LCCM653.dll"
dll_filename = os.path.join(dll_path, dll_name)
print "DLL {} exists? {}".format(dll_filename, os.path.exists(dll_filename))
lib = ctypes.CDLL(dll_filename)
print "Lib loaded successfully!"
value = lib.vPWRNODE__Init()
print "Called vPWRNODE__Init()! Got {} in return.".format(value)
try:
    hmm = lib.not_a_real_function()
    print "Called not_a_real_function(), got {} in return.".format(hmm)
except Exception as e:
    print "Called a fake function, got an (expected) exception! ({})".format(e)
    
print "-----"
print "Now let's try a callback..."
# @see http://stackoverflow.com/questions/17980167/writing-python-ctypes-for-function-pointer-callback-function-in-c

#debug_printf_callback = ctypes.WINFUNCTYPE(None, ctypes.POINTER(ctypes.c_byte))  # Returns nothing, takes a byte*

debug_printf_callback = ctypes.WINFUNCTYPE(None, ctypes.c_char_p)  # Returns nothing, takes a char*

vDEBUG_PRINTF_WIN32__Set_Callback = lib.vDEBUG_PRINTF_WIN32__Set_Callback
vDEBUG_PRINTF_WIN32__Set_Callback.argtypes = [debug_printf_callback]
vDEBUG_PRINTF_WIN32__Set_Callback.restype = None

# Define the python function that we'll use for the callback
def debug_printf(val):
    print "Python Debug printf callback called with value '{}'".format(val)
    
# reference the callback to keep it alive
_debug_printf_callback = debug_printf_callback(debug_printf)

# Pass in our referenced python function to the dll function
vDEBUG_PRINTF_WIN32__Set_Callback(_debug_printf_callback)

from time import sleep

def pwrnode_init():
    lib.vPWRNODE__Init()

def pwrnode_process():
    lib.vPWRNODE__Process()  # @todo: program exits on this call? 

print "Calling vPWRNODE__Init()"
pwrnode_init()

n = 10
print "Starting vPWRNODE__Process() loop ({})".format(n)
for i in xrange(n):
    print "  Calling vPWRNODE__Process()..."
    #lib.vPWRNODE__Process()
    pwrnode_process()
    print "  After vPWRNODE__Process() call"
    
print "Done with vPWRNODE__Process() loop!"

# @todo: The program exits during the lib.vPWRNODE__Process() call -- maybe need to initialize temperature or something? 


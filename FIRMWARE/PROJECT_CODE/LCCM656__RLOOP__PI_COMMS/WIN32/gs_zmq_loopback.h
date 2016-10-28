#include <stdint.h>


#pragma once

#define RPOD_I2C_BUFFER_SIZE 5000

#define _WINSOCK_DEPRECATED_NO_WARNINGS

//Starts broadcasting network beacon and initializes ZMQ context
extern "C" __declspec(dllexport) void __cdecl InitGSLoopback(char *_nodeName);

//Pushes the data out the zmq pub socket to the ground station
extern "C" __declspec(dllexport) void SendGSMessage(uint8_t *buf, uint16_t bufLen);

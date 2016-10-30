#include <stdint.h>

//On the pod this will be a UART to the Pi
//In VS it will simulate the Pi to broadcast
//and receive data from the ground station

void PowrNodePiUartSendData(uint8_t *buffer, uint16_t length)
{
	//Should process the frame and relay the latest data to the GS over ZMQ like the PI does
}
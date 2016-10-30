#include "BatteryCharger.h"
#include "PowerNodeMain.h"
#include "PowerNodeParameters.h"
#include "TempSensors.h"
#include "PowerNodePiUart.h"
#include "rI2CTX.h"

struct rI2CTX_Data txData;

//Called every time the node should send new
//data to the ground station
void SendParameters()
{
	rI2CTX_beginFrame(txData);

	//Add all the parameters to the frame here

	rI2CTX_endFrame(txData);
	PowrNodePiUartSendData(txData.buffer, txData.bufferPos);
}
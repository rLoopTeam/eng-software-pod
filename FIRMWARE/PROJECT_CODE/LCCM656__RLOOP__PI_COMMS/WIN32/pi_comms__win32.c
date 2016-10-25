/**
 * @file		PI_COMMS__WIN32.C
 * @brief		WIN32 emulation functions for the Pi Comms module.
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 * @st_fileID	LCCM656R0.FILE.003
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup PI_COMMS
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup PI_COMMS__WIN32
 * @ingroup PI_COMMS
 * @{ */

#include "../pi_comms.h"
#include "zmq.h"

#if C_LOCALDEF__LCCM656__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM656__USE_ON_WIN32 == 1U

 //this is our function pointer
pPICOMMS_WIN32__TxFrame__FuncType pTxFrameFunc;

//ZMQ stuff
void *context;
void *pubTelemetry; 
int rc;

//Sets up some ZMQ stuff for transmitting
void vPICOMMS_WIN32__Init(void)
{


	//Get the ZMQ Pub socket all setup

	context = zmq_ctx_new();
	pubTelemetry = zmq_socket(context, ZMQ_PUB);
	rc = zmq_bind(pubTelemetry, "tcp://*:3000");

	/* This code could go in a deconstructor
	zmq_close(pubTelemetry);
	zmq_ctx_destroy(context);
	*/
}

 //Simple test case 1, callable from DLL
void vPICOMMS_WIN32__Test1(void)
{
	Luint16 u16Length;
	Luint8 * pu8Buffer;
	char *nodeName = "PowerA"; //TODO: Abstract this somewhere
	Luint8 ZMQTxBuffer[RPOD_I2C_BUFFER_SIZE];

	//do one single parameter

	//start a new frame
	rI2CTX_beginFrame();

	//add 0xAA as param 1
	rI2CTX_addParameter_uint8(0x0001U, 0xAA);

	//finish the frame
	u16Length = rI2CTX_endFrame();

	//force it to be sent (this will change in the future)
	pu8Buffer = pu8I2CTx__Get_BufferPointer();
	vPICOMMS_WIN32__TxFrame_Callback(pu8Buffer, u16Length);
	
	//Pack the new data packet into the ZMQ transmit buffer
	//along with some metadata at the start and send it out
	if ((u16Length + strlen(nodeName) + strlen(nodeName)) < RPOD_I2C_BUFFER_SIZE) {
		char * t = "telemetry ";
		memcpy(&ZMQTxBuffer, t, strlen(t));
		memcpy(ZMQTxBuffer + strlen(t), nodeName, strlen(nodeName));
		memcpy(ZMQTxBuffer + strlen(t) + strlen(nodeName), pu8Buffer, u16Length + strlen(t) + strlen(nodeName));
		zmq_send(pubTelemetry, ZMQTxBuffer, u16Length + strlen(t) + strlen(nodeName), 0);
	}
	else {
		printf("ZMQ TX buffer too small.\n");
	}

}

//this is the callback for getting data out of the DLL into the upper layer.
void vPICOMMS_WIN32__TxFrame_Callback(const Luint8 * pu8Array, Luint16 u16Length)
{
	//allocate enough space for large strings
	Luint8 u8Buffer[1024];
	Luint16 u16Counter;
	
	//blind copy
	for (u16Counter = 0U; u16Counter < u16Length; u16Counter++)
	{
		u8Buffer[u16Counter] = pu8Array[u16Counter];
	}
	
	pTxFrameFunc((const Luint8 *)pu8Array, u16Length);
}

//allow the vb.net app to register the callback
DLL_DECLARATION void vPICOMMS_WIN32__TxFrame_Set_Callback(pPICOMMS_WIN32__TxFrame__FuncType pFunc)
{
	//assign
	pTxFrameFunc = pFunc;
}


#endif //C_LOCALDEF__LCCM656__USE_ON_WIN32

//safetys
#ifndef C_LOCALDEF__LCCM656__USE_ON_WIN32
	#error
#endif

#endif //#if C_LOCALDEF__LCCM656__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM656__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

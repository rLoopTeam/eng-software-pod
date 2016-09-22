#include <stdint.h>

#ifndef TeensyI2CReceiver_H
#define TeensyI2CReceiver_H

#define I2C_BUFFER_SIZE 5000 
#define I2C_CONTROL_CHAR 0xD5
#define I2C_FRAME_START 0xD0
#define I2C_PARAMETER_START 0xD3
#define I2C_FRAME_END 0xD8

struct rI2CRX_decParam {
	uint16_t index;
	uint8_t type;
	uint8_t length;
	void *val;
}rI2CRX_decParam_t;

extern void (*rI2CRX_frameRXBeginCB) ();
extern void (*rI2CRX_recvDecParamCB) (struct rI2CRX_decParam decParam);
extern void (*rI2CRX_frameRXEndCB) ();


enum rI2C_paramTypes
{
	rI2C_INT8 = 0x11,
	rI2C_UINT8 = 0x12,
	rI2C_INT16 = 0x21,
	rI2C_UINT16 = 0x22,
	rI2C_INT32 = 0x41,
	rI2C_UINT32 = 0x42,
	rI2C_INT64 = 0x81,
	rI2C_UINT64 = 0x82,
	rI2C_FLOAT = 0x43,
	rI2C_DOUBLE = 0x83
};

void rI2CRX_begin();
void rI2CRX_receiveBytes(uint8_t* data, uint16_t length);

#endif 


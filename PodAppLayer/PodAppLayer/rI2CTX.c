#include "rI2CTX.h"
#include <string.h>
#include "teensyByteOrder.h"

//uint8_t rI2CTX_buffer[RPOD_I2C_BUFFER_SIZE];
//uint16_t rI2CTX_bufferPos;
//uint8_t checksum;
//uint16_t rI2CTX_frameLength;

void rI2CTX_beginFrame(struct rI2CTX_Data I2CTXInstance)
{
	I2CTXInstance.buffer[0] = RPOD_I2C_CONTROL_CHAR;
	I2CTXInstance.buffer[1] = RPOD_I2C_FRAME_START;
	I2CTXInstance.bufferPos = 4;
	//2,3 will be filled in with the length in endFrame()
}

void rI2CTX_calculateChecksum(uint16_t lastByte, struct rI2CTX_Data I2CTXInstance)
{
	I2CTXInstance.checksum = 0;
	uint16_t i;
	for (i = 0; i < lastByte;i++)
		I2CTXInstance.checksum ^= I2CTXInstance.buffer[i];
}

void rI2CTX_add_checked_byte(uint8_t byte, struct rI2CTX_Data I2CTXInstance)
{
	I2CTXInstance.buffer[I2CTXInstance.bufferPos++] = byte;
	if(byte == RPOD_I2C_CONTROL_CHAR)
		I2CTXInstance.buffer[I2CTXInstance.bufferPos++] = byte;
}

void rI2CTX_add_unchecked_byte(uint8_t byte, struct rI2CTX_Data I2CTXInstance)
{
	I2CTXInstance.buffer[I2CTXInstance.bufferPos++] = byte;
}

uint16_t rI2CTX_endFrame(struct rI2CTX_Data I2CTXInstance)
{
	uint16_t rI2CTX_frameLength = I2CTXInstance.bufferPos;

	uint8_t length1 = rI2CTX_frameLength >> 8;
	uint8_t length2 = rI2CTX_frameLength & 0xFF;

	if (length1 != RPOD_I2C_CONTROL_CHAR && length2 != RPOD_I2C_CONTROL_CHAR)
	{
		I2CTXInstance.buffer[2] = length1;
		I2CTXInstance.buffer[3] = length2;
	}
	else if (length1 == RPOD_I2C_CONTROL_CHAR && length2 == RPOD_I2C_CONTROL_CHAR)
	{
		I2CTXInstance.buffer[2] = length1;
		I2CTXInstance.buffer[3] = length1;
		I2CTXInstance.buffer[4] = length2;
		I2CTXInstance.buffer[5] = length2;
		memcpy(I2CTXInstance.buffer + 4, I2CTXInstance.buffer + 6, I2CTXInstance.bufferPos - 4); //DOUBLE CHECK THIS
		I2CTXInstance.bufferPos += 2;
	}
	else{
		if (length1 == RPOD_I2C_CONTROL_CHAR){
			I2CTXInstance.buffer[2] = length1;
			I2CTXInstance.buffer[3] = length1;
			I2CTXInstance.buffer[4] = length2;
		}
		else{
			I2CTXInstance.buffer[2] = length1;
			I2CTXInstance.buffer[3] = length2;
			I2CTXInstance.buffer[4] = length2;
		}
		memcpy(I2CTXInstance.buffer + 4, I2CTXInstance.buffer + 5, I2CTXInstance.bufferPos - 4);  //DOUBLE CHECK THIS
		I2CTXInstance.bufferPos += 1;
	}
	
	rI2CTX_calculateChecksum(I2CTXInstance.bufferPos, I2CTXInstance);

	rI2CTX_add_unchecked_byte(RPOD_I2C_CONTROL_CHAR, I2CTXInstance);
	rI2CTX_add_unchecked_byte(RPOD_I2C_FRAME_END, I2CTXInstance);
	rI2CTX_add_unchecked_byte(I2CTXInstance.checksum, I2CTXInstance);
	rI2CTX_add_unchecked_byte(0x00, I2CTXInstance);

	return I2CTXInstance.bufferPos;
}

rI2CTX_addHeader(uint8_t dataType, uint16_t index, struct rI2CTX_Data I2CTXInstance)
{
	rI2CTX_add_unchecked_byte(RPOD_I2C_CONTROL_CHAR, I2CTXInstance);
	rI2CTX_add_checked_byte(RPOD_I2C_PARAMETER_START, I2CTXInstance);
	rI2CTX_add_checked_byte(dataType, I2CTXInstance);

	uint16_t i;

	for (i = 0; i < sizeof(index); i++)
	{
		uint8_t byte = index >> ((sizeof(index)-i-1)*8);
		rI2CTX_add_checked_byte(byte, I2CTXInstance);
	}
}

void rI2CTX_addParameter_int8(uint16_t index, int8_t data, struct rI2CTX_Data I2CTXInstance)
{
	rI2CTX_addHeader(0x11, index, I2CTXInstance);

	rI2CTX_add_checked_byte(data, I2CTXInstance);
}

void rI2CTX_addParameter_uint8(uint16_t index, uint8_t data, struct rI2CTX_Data I2CTXInstance)
{
	rI2CTX_addHeader(0x12, index, I2CTXInstance);

	rI2CTX_add_checked_byte(data, I2CTXInstance);
 }

void rI2CTX_addParameter_int16(uint16_t index, int16_t data, struct rI2CTX_Data I2CTXInstance)
{
	rI2CTX_addHeader(0x21, index, I2CTXInstance);

	uint16_t i;

	for (i = 0; i < sizeof(data); i++)
	{
		uint8_t byte = data >> ((sizeof(data)-i-1)*8);
		rI2CTX_add_checked_byte(byte, I2CTXInstance);
	}
}

void rI2CTX_addParameter_uint16(uint16_t index, uint16_t data, struct rI2CTX_Data I2CTXInstance)
{
	rI2CTX_addHeader(0x22, index, I2CTXInstance);

	uint16_t i;

	for (i = 0; i < sizeof(data); i++)
	{
		uint8_t byte = data >> ((sizeof(data) - i - 1) * 8);
		rI2CTX_add_checked_byte(byte, I2CTXInstance);
	}
}

void rI2CTX_addParameter_int64(uint16_t index, int64_t data, struct rI2CTX_Data I2CTXInstance)
{
	rI2CTX_addHeader(0x81, index, I2CTXInstance);

	uint16_t i;

	for (i = 0; i < sizeof(data); i++)
	{
		uint8_t byte = data >> ((sizeof(data) - i - 1) * 8);
		rI2CTX_add_checked_byte(byte, I2CTXInstance);
	}
}

void rI2CTX_addParameter_uint64(uint16_t index, uint64_t data, struct rI2CTX_Data I2CTXInstance)
{
	rI2CTX_addHeader(0x82, index, I2CTXInstance);

	uint16_t i;

	for (i = 0; i < sizeof(data); i++)
	{
		uint8_t byte = data >> ((sizeof(data) - i - 1) * 8);
		rI2CTX_add_checked_byte(byte, I2CTXInstance);
	}
}

void rI2CTX_addParameter_int32(uint16_t index, int32_t data, struct rI2CTX_Data I2CTXInstance)
{
	rI2CTX_addHeader(0x41, index, I2CTXInstance);

	uint16_t i;

	for (i = 0; i < sizeof(data); i++)
	{
		uint8_t byte = data >> ((sizeof(data) - i - 1) * 8);
		rI2CTX_add_checked_byte(byte, I2CTXInstance);
	}
}

void rI2CTX_addParameter_uint32(uint16_t index, uint32_t data, struct rI2CTX_Data I2CTXInstance)
{
	rI2CTX_addHeader(0x41, index, I2CTXInstance);

	uint16_t i;

	for (i = 0; i < sizeof(data); i++)
	{
		uint8_t byte = data >> ((sizeof(data) - i - 1) * 8);
		rI2CTX_add_checked_byte(byte, I2CTXInstance);
	}
}

void rI2CTX_addParameter_float(uint16_t index, float data, struct rI2CTX_Data I2CTXInstance)
{
	rI2CTX_addHeader(0x43, index, I2CTXInstance);

	uint32_t rawData;
	memcpy(&rawData, &data, 4);

	uint16_t i;

	for (i = 0; i < sizeof(rawData); i++)
	{
		uint8_t byte = rawData >> ((sizeof(rawData) - i - 1) * 8);
		rI2CTX_add_checked_byte(byte, I2CTXInstance);
	}
}

void rI2CTX_addParameter_double(uint16_t index, double data, struct rI2CTX_Data I2CTXInstance)
{
	rI2CTX_addHeader(0x83, index, I2CTXInstance);

	uint64_t rawData;
	memcpy(&rawData, &data, 8);

	uint16_t i;

	for (i = 0; i < sizeof(rawData); i++)
	{
		uint8_t byte = rawData >> ((sizeof(rawData) - i - 1) * 8);
		rI2CTX_add_checked_byte(byte, I2CTXInstance);
	}
}


#include "rI2CTX.h"
#include <string.h>

uint8_t rI2CTX_buffer[RPOD_I2C_BUFFER_SIZE];
uint16_t rI2CTX_bufferPos;
uint8_t checksum;
uint16_t rI2CTX_frameLength;

void rI2CTX_beginFrame()
{
	rI2CTX_buffer[0] = RPOD_I2C_CONTROL_CHAR;
	rI2CTX_buffer[1] = RPOD_I2C_FRAME_START;
	rI2CTX_bufferPos = 4;
	//2,3 will be filled in with the length in endFrame()
}

void rI2CTX_calculateChecksum(uint16_t lastByte)
{
	checksum = 0;
	uint16_t i;
	for (i = 0; i < lastByte;i++)
		checksum ^= rI2CTX_buffer[i];
}



void rI2CTX_add_checked_byte(uint8_t byte)
{
	rI2CTX_buffer[rI2CTX_bufferPos++] = byte;
	if(byte == RPOD_I2C_CONTROL_CHAR)
		rI2CTX_buffer[rI2CTX_bufferPos++] = byte;
}

void rI2CTX_add_unchecked_byte(uint8_t byte)
{
	rI2CTX_buffer[rI2CTX_bufferPos++] = byte;
}

uint16_t rI2CTX_endFrame()
{
	rI2CTX_frameLength = rI2CTX_bufferPos;

	uint8_t length1 = rI2CTX_frameLength >> 8;
	uint8_t length2 = rI2CTX_frameLength & 0xFF;

	if (length1 != RPOD_I2C_CONTROL_CHAR && length2 != RPOD_I2C_CONTROL_CHAR)
	{
		rI2CTX_buffer[2] = length1;
		rI2CTX_buffer[3] = length2;
	}
	else if (length1 == RPOD_I2C_CONTROL_CHAR && length2 == RPOD_I2C_CONTROL_CHAR)
	{
		rI2CTX_buffer[2] = length1;
		rI2CTX_buffer[3] = length1;
		rI2CTX_buffer[4] = length2;
		rI2CTX_buffer[5] = length2;
		memcpy(rI2CTX_buffer + 4, rI2CTX_buffer + 6, rI2CTX_bufferPos - 4); //DOUBLE CHECK THIS
		rI2CTX_bufferPos += 2;
	}
	else{
		if (length1 == RPOD_I2C_CONTROL_CHAR){
			rI2CTX_buffer[2] = length1;
			rI2CTX_buffer[3] = length1;
			rI2CTX_buffer[4] = length2;
		}
		else{
			rI2CTX_buffer[2] = length1;
			rI2CTX_buffer[3] = length2;
			rI2CTX_buffer[4] = length2;
		}
		memcpy(rI2CTX_buffer + 4, rI2CTX_buffer + 5, rI2CTX_bufferPos - 4);  //DOUBLE CHECK THIS
		rI2CTX_bufferPos += 1;
	}
	
	rI2CTX_calculateChecksum(rI2CTX_bufferPos);

	rI2CTX_add_unchecked_byte(RPOD_I2C_CONTROL_CHAR);
	rI2CTX_add_unchecked_byte(RPOD_I2C_FRAME_END);
	rI2CTX_add_unchecked_byte(checksum);
	rI2CTX_add_unchecked_byte(0x00);

	return rI2CTX_bufferPos;
}

rI2CTX_addHeader(uint8_t dataType, uint16_t index)
{
	rI2CTX_add_unchecked_byte(RPOD_I2C_CONTROL_CHAR);
	rI2CTX_add_checked_byte(RPOD_I2C_PARAMETER_START);
	rI2CTX_add_checked_byte(dataType);

	uint16_t i;

	for (i = 0; i < sizeof(index); i++)
	{
		uint8_t byte = index >> ((sizeof(index)-i-1)*8);
		rI2CTX_add_checked_byte(byte);
	}
}

void rI2CTX_addParameter_int8(uint16_t index, int8_t data)
{
	rI2CTX_addHeader(0x11,index);

	rI2CTX_add_checked_byte(data);
}

void rI2CTX_addParameter_uint8(uint16_t index, uint8_t data)
{
	rI2CTX_addHeader(0x12,index);

	rI2CTX_add_checked_byte(data);
 }

void rI2CTX_addParameter_int16(uint16_t index, int16_t data)
{
	rI2CTX_addHeader(0x21,index);

	uint16_t i;

	for (i = 0; i < sizeof(data); i++)
	{
		uint8_t byte = data >> ((sizeof(data)-i-1)*8);
		rI2CTX_add_checked_byte(byte);
	}
}

void rI2CTX_addParameter_uint16(uint16_t index, uint16_t data)
{
	rI2CTX_addHeader(0x22,index);

	uint16_t i;

	for (i = 0; i < sizeof(data); i++)
	{
		uint8_t byte = data >> ((sizeof(data) - i - 1) * 8);
		rI2CTX_add_checked_byte(byte);
	}
}

void rI2CTX_addParameter_int64(uint16_t index, int64_t data)
{
	rI2CTX_addHeader(0x81,index);

	uint16_t i;

	for (i = 0; i < sizeof(data); i++)
	{
		uint8_t byte = data >> ((sizeof(data) - i - 1) * 8);
		rI2CTX_add_checked_byte(byte);
	}
}

void rI2CTX_addParameter_uint64(uint16_t index, uint64_t data)
{
	rI2CTX_addHeader(0x82,index);

	uint16_t i;

	for (i = 0; i < sizeof(data); i++)
	{
		uint8_t byte = data >> ((sizeof(data) - i - 1) * 8);
		rI2CTX_add_checked_byte(byte);
	}
}

void rI2CTX_addParameter_int32(uint16_t index, int32_t data)
{
	rI2CTX_addHeader(0x41,index);

	uint16_t i;

	for (i = 0; i < sizeof(data); i++)
	{
		uint8_t byte = data >> ((sizeof(data) - i - 1) * 8);
		rI2CTX_add_checked_byte(byte);
	}
}

void rI2CTX_addParameter_uint32(uint16_t index, uint32_t data)
{
	rI2CTX_addHeader(0x42,index);

	uint16_t i;

	for (i = 0; i < sizeof(data); i++)
	{
		uint8_t byte = data >> ((sizeof(data) - i - 1) * 8);
		rI2CTX_add_checked_byte(byte);
	}
}

void rI2CTX_addParameter_float(uint16_t index, float data)
{
	rI2CTX_addHeader(0x43,index);

	uint32_t rawData;
	memcpy(&rawData, &data, 4);

	uint16_t i;

	for (i = 0; i < sizeof(rawData); i++)
	{
		uint8_t byte = rawData >> ((sizeof(rawData) - i - 1) * 8);
		rI2CTX_add_checked_byte(byte);
	}
}

void rI2CTX_addParameter_double(uint16_t index, double data)
{
	rI2CTX_addHeader(0x83,index);

	uint64_t rawData;
	memcpy(&rawData, &data, 8);

	uint16_t i;

	for (i = 0; i < sizeof(rawData); i++)
	{
		uint8_t byte = rawData >> ((sizeof(rawData) - i - 1) * 8);
		rI2CTX_add_checked_byte(byte);
	}
}

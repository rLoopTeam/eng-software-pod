#include <stdint.h>

#ifndef rI2CTX_H
#define rI2CTX_H

#define RPOD_I2C_BUFFER_SIZE 5000 
#define RPOD_I2C_CONTROL_CHAR 0xD5
#define RPOD_I2C_FRAME_START 0xD0
#define RPOD_I2C_PARAMETER_START 0xD3
#define RPOD_I2C_FRAME_END 0xD8

typedef struct rI2CTX_Data {
	uint8_t buffer[RPOD_I2C_BUFFER_SIZE];
	uint16_t  bufferPos;
	uint16_t frameLength;
	uint8_t checksum;
}rI2CTX_Data_t;

/*
extern uint8_t rI2CTX_buffer[RPOD_I2C_BUFFER_SIZE];
extern uint16_t rI2CTX_bufferPos;
extern uint16_t rI2CTX_frameLength;
*/

void rI2CTX_beginFrame(struct rI2CTX_Data I2CTXInstance);
void rI2CTX_CalculateChecksum(uint16_t lastByte, struct rI2CTX_Data I2CTXInstance);
uint16_t rI2CTX_endFrame(struct rI2CTX_Data I2CTXInstance);

void rI2CTX_addParameter_int8(uint16_t index, int8_t data, struct rI2CTX_Data I2CTXInstance);
void rI2CTX_addParameter_uint8(uint16_t index, uint8_t data, struct rI2CTX_Data I2CTXInstance);
void rI2CTX_addParameter_int16(uint16_t index, int16_t data, struct rI2CTX_Data I2CTXInstance);
void rI2CTX_addParameter_uint16(uint16_t index, uint16_t data, struct rI2CTX_Data I2CTXInstance);
void rI2CTX_addParameter_int64(uint16_t index, int64_t data, struct rI2CTX_Data I2CTXInstance);
void rI2CTX_addParameter_uint64(uint16_t index, uint64_t data, struct rI2CTX_Data I2CTXInstance);
void rI2CTX_addParameter_int32(uint16_t index, int32_t data, struct rI2CTX_Data I2CTXInstance);
void rI2CTX_addParameter_uint32(uint16_t index, uint32_t data, struct rI2CTX_Data I2CTXInstance);
void rI2CTX_addParameter_float(uint16_t index, float data, struct rI2CTX_Data I2CTXInstance);
void rI2CTX_addParameter_double(uint16_t index, double data, struct rI2CTX_Data I2CTXInstance);

#endif


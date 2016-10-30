#include "rI2CRX.h"
#include <stdint.h>
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include "teensyByteOrder.h"


uint8_t buffer[I2C_BUFFER_SIZE];
uint16_t bufferBegin;
uint16_t bufferLength;

void(*rI2CRX_frameRXBeginCB)();
void(*rI2CRX_recvDecParamCB)(struct rI2CRX_decParam decParam);
void(*rI2CRX_frameRXEndCB)();

void processBuffer();
int processFrame(uint8_t *frameBuffer, uint16_t length);
void receiveParam(uint8_t type, uint16_t index, uint64_t rawData);

void rI2CRX_begin()
{
	bufferLength = 0;
	bufferBegin = 0;
	rI2CRX_frameRXBeginCB = NULL;
	rI2CRX_recvDecParamCB = NULL;
	rI2CRX_frameRXEndCB = NULL;
}

void rI2CRX_receiveBytes(uint8_t* data, uint16_t length)
{
	int i = 0;

	if (length > I2C_BUFFER_SIZE)
		return; //somehthing's not right, drop this data and hope we catch up
	else {}//All is well, continue on

	//Got some bad data at some point
	if (bufferLength + length > I2C_BUFFER_SIZE)
	{
		bufferLength = 0;
		bufferBegin = 0;
	}

	for (i = 0; i < length; i++)
		buffer[(i + bufferBegin + bufferLength)%I2C_BUFFER_SIZE] = data[i];
	bufferLength += length;

	//See if there's enough data for a full frame
	if (bufferLength >= 8){
		processBuffer();
	}
	else
	{
		//Not enough data for a full frame, do nothing
	}

}

void processBuffer()
{
	uint8_t frameBuffer[I2C_BUFFER_SIZE];

	int i = 0;
	int bufferBeginJump = 0;

	//Search for a full frame
	for (i = 0; i < (bufferLength-1); i++)
	{
		//Is this a start code?
		if (buffer[(bufferBegin + i) % I2C_BUFFER_SIZE] == I2C_CONTROL_CHAR && buffer[((bufferBegin + i + 1) % I2C_BUFFER_SIZE)] == I2C_FRAME_START)
		{
			//See if we should have the whole header yet
			if (i + 5 < bufferLength)
			{
				//Grab the length of the frame from the header
				uint16_t frameLength = buffer[(bufferBegin + i + 2) % I2C_BUFFER_SIZE];
				int headerLength = 4;
				if (frameLength == I2C_CONTROL_CHAR){
					frameLength = frameLength * 256 + buffer[(bufferBegin + i + 4) % I2C_BUFFER_SIZE];
					headerLength++;
					if (buffer[(bufferBegin + i + 4) % I2C_BUFFER_SIZE] == I2C_CONTROL_CHAR)
						headerLength++;
				}
				else
					frameLength = frameLength*256 + buffer[(bufferBegin + i + 3) % I2C_BUFFER_SIZE];

				//See if we have the end of the frame in the buffer yet
				if (i + headerLength + frameLength <= bufferLength)
				{
					//Copy the frame into a flat buffer
					//This step isn't 100% necessary but it does make processing the frame a bit easier to follow
					int x;
					for (x = 0; x < (frameLength + headerLength); x++)
					{
						frameBuffer[x] = buffer[(x+i+bufferBegin) % I2C_BUFFER_SIZE];
					}

					//Process the frame!
					if (processFrame(frameBuffer, frameLength + 4)){
						i += frameLength + headerLength;
						bufferBeginJump += headerLength + frameLength;
					}
				}
				else{
					//We have a start code, but not enough data for a full frame yet
					i = bufferLength;
				}
			}
			else{
				//Don't have the full header yet, nothing to do for now
				i = bufferLength - 1;
			}
		}
		else{
			//Not sure what we got sent, but it's not a start code so advance the buffer.
			bufferBeginJump++;
		}
	}
	bufferBegin += bufferBeginJump;
	bufferBegin = bufferBegin % I2C_BUFFER_SIZE;
	bufferLength -= bufferBeginJump;

}

int processFrame(uint8_t *frameBuffer, uint16_t length)
{
	//Check the start and end headers
	if (frameBuffer[0] != I2C_CONTROL_CHAR || frameBuffer[1] != I2C_FRAME_START || frameBuffer[length - 4] != I2C_CONTROL_CHAR || frameBuffer[length - 3] != I2C_FRAME_END)
		return 0;

	int i = 0;
	uint8_t checksum = 0;
	for (i = 0; i < length-4; i++)
		checksum ^= frameBuffer[i];

	if (frameBuffer[length - 2] != checksum){
		return 0;
	}
	else {} //All good, continue on

	if (rI2CRX_frameRXBeginCB != NULL)
		rI2CRX_frameRXBeginCB();
	

	//Shorten any escaped data now that we've isolated a single frame
	for (i = 2; i < length-1; i++)
	{
		if (frameBuffer[i] == I2C_CONTROL_CHAR && frameBuffer[i + 1] == I2C_CONTROL_CHAR)
		{
			int x;
			for (x = i + 1; x < length - 1; x++)
			{
				frameBuffer[x] = frameBuffer[x + 1];
			}
			frameBuffer[length - 1] = 0x00;
		}
		else{}//no escaped data here, continue on.
	}
	
	uint16_t position = 4;
	uint64_t rawData;
	while (position < length)
	{
		if (frameBuffer[position] == 0xD5)
		{
			position++;
			switch (frameBuffer[position])
			{
			case I2C_PARAMETER_START:
				{
					position++;

					int dataType = frameBuffer[position] & 0x0F;
					uint8_t dataSize = (frameBuffer[position] & 0xF0) / 16;

					if (dataType == 1 || dataType == 2 || dataType == 3)
					{
						rawData = 0;
						//safety check for memcopy
						if (dataSize <= 8){
							memcpy(&rawData, &frameBuffer[position + 3], dataSize);
						}
						else{ break; } //Somethings not right

						receiveParam(frameBuffer[position], frameBuffer[position + 1] * 256 + frameBuffer[position+2], rawData);

					}
					else if (dataType == 0){

					}
					else{}

					position += dataSize+3;
				}
					break;
			case I2C_FRAME_END:
				if (rI2CRX_frameRXEndCB != NULL)
					rI2CRX_frameRXEndCB();
				return 1;
			}
		}
		else{
			//Should report an error
			position++;
		}
	}

		rI2CRX_frameRXEndCB();
		return 1;
}

int8_t temp_1byte;
int16_t temp_2byte;
int32_t temp_4byte;
int64_t temp_8byte;


void receiveParam(uint8_t type, uint16_t index, uint64_t rawData)
{
	struct rI2CRX_decParam receivedParam;
	receivedParam.index = index;
	receivedParam.type = type;
	switch (type)
	{
		case 0x11:	receivedParam.val = &temp_1byte;
					*((int8_t*)receivedParam.val) = (int8_t)rawData;
					receivedParam.length = 1;
					break;
		case 0x12:	receivedParam.val = &temp_1byte;
					*((uint8_t*)receivedParam.val) = (uint8_t)rawData;
					receivedParam.length = 1;
					break;

		case 0x21:	receivedParam.val = &temp_2byte;
					*((int16_t*)receivedParam.val) = (int16_t)ntohs((int16_t)rawData);
					receivedParam.length = 2;	
					break;

		case 0x22: 	receivedParam.val = &temp_2byte;
					*((uint16_t*)receivedParam.val) = ntohs((uint16_t)rawData);
					receivedParam.length = 2;
					break;

		case 0x41: 	receivedParam.val = &temp_4byte;
					*((int32_t*)receivedParam.val) = ntohl((int32_t)rawData);
					receivedParam.length = 4;
					break;

		case 0x42: 	receivedParam.val = &temp_4byte;
					*((uint32_t*)receivedParam.val) = ntohl((uint32_t)rawData);
					receivedParam.length = 4;
					break;
					
		case 0x81: 	receivedParam.val = &temp_8byte;
					*((int64_t*)receivedParam.val) = (int64_t)be64toh((uint64_t)rawData);
					receivedParam.length = 8;
					break;

		case 0x82:	receivedParam.val = &temp_8byte;
					*((uint64_t*)receivedParam.val) = be64toh((uint64_t)rawData);
					receivedParam.length = 8;
					break;
					
		case 0x43:	receivedParam.val = &temp_4byte;
					rawData = be64toh((uint64_t)rawData);
					rawData = rawData >> 32;
					memcpy(receivedParam.val, &rawData, 4);
					receivedParam.length = 4;
					break;
					
		case 0x83:	receivedParam.val = &temp_8byte;
					rawData = be64toh((uint64_t)rawData);
					memcpy(receivedParam.val, &rawData, 8);
					receivedParam.length = 8;
					break;
					
		default:return;
	}
	rI2CRX_recvDecParamCB(receivedParam);
}


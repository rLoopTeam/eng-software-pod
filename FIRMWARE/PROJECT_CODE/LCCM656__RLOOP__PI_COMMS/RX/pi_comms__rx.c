/**
 * @file		PI_COMMS__RX.C
 * @brief		Architecture neutral Rx code from Pi to Host
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 * @st_fileID	LCCM656R0.FILE.005
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup PI_COMMS
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup PI_COMMS__RX
 * @ingroup PI_COMMS
 * @{ */

#include "../pi_comms.h"
#if C_LOCALDEF__LCCM656__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM656__ENABLE_RX == 1U
//the main structure
extern struct _strPICOMMS sPC;


void (*PICOMMS_RX_frameRXBeginCB) ();
void (*PICOMMS_RX_frameRXEndCB) ();
void (*PICOMMS_RX_recvLuint8) (Luint16 index, Luint8 data);
void (*PICOMMS_RX_recvLint8) (Luint16 index, Lint8 data);
void (*PICOMMS_RX_recvLuint16) (Luint16 index, Luint16 data);
void (*PICOMMS_RX_recvLint16) (Luint16 index, Lint16 data);
void (*PICOMMS_RX_recvLuint32) (Luint16 index, Luint32 data);
void (*PICOMMS_RX_recvLint32) (Luint16 index, Lint32 data);
void (*PICOMMS_RX_recvLuint64) (Luint16 index, Luint64 data);
void (*PICOMMS_RX_recvLint64) (Luint16 index, Lint64 data);
void (*PICOMMS_RX_recvLfloat32) (Luint16 index, Lfloat32 data);
void (*PICOMMS_RX_recvLfloat64) (Luint16 index, Lfloat64 data);

void vPICOMMS_RX__ProcessBuffer();
Luint16 u16PICOMMS_RX__ProcessFrame(Luint8 *frameBuffer, Luint16 length);
void vPICOMMS_RX__ReceiveParam(Luint8 u8Type, Luint16 u16Index, Luint64 u64RawData);


void vPICOMMS_RX__Init()
{
	sPC.sRx.bufferLength = 0;
	sPC.sRx.bufferBegin = 0;
	sPC.sRx.u32Faults = 0U;


	PICOMMS_RX_frameRXBeginCB = 0;
	PICOMMS_RX_recvLuint8 = 0;
	PICOMMS_RX_recvLint8 = 0;
	PICOMMS_RX_recvLuint16 = 0;
	PICOMMS_RX_recvLint16 = 0;
	PICOMMS_RX_recvLuint32 = 0;
	PICOMMS_RX_recvLint32 = 0;
	PICOMMS_RX_recvLuint64 = 0;
	PICOMMS_RX_recvLint64 = 0;
	PICOMMS_RX_recvLfloat32 = 0;
	PICOMMS_RX_recvLfloat64 = 0;
	PICOMMS_RX_frameRXEndCB = 0;
}

void vPICOMMS_RX__Receive_Bytes(Luint8 *data, Luint16 length)
{
	int i = 0;

	if (length > RPOD_PICOMMS_BUFFER_SIZE)
	{
		//todo: Flags?
		//somehthing's not right, drop this data and hope we catch up
		return;
	}
	else
	{
		//All is well, continue on
	}

	//Got some bad data at some point
	if (sPC.sRx.bufferLength + length > RPOD_PICOMMS_BUFFER_SIZE)
	{
		sPC.sRx.bufferLength = 0;
		sPC.sRx.bufferBegin = 0;
	}
	else
	{
		//todo: what to do?
	}

	if((sPC.sRx.bufferBegin + sPC.sRx.bufferLength) < RPOD_PICOMMS_BUFFER_SIZE)
	{
		for (i = 0; i < length; i++)
		{
			sPC.sRx.u8Buffer[(i + sPC.sRx.bufferBegin + sPC.sRx.bufferLength) % RPOD_PICOMMS_BUFFER_SIZE] = data[i];
		}
	}
	else
	{
		sPC.sRx.u32Faults++;
	}

	sPC.sRx.bufferLength += length;

	//See if there's enough data for a full frame
	if (sPC.sRx.bufferLength >= 8)
	{
		//todo: really call this every time?
		vPICOMMS_RX__ProcessBuffer();
	}
	else
	{
		//Not enough data for a full frame, do nothing
	}

}

void vPICOMMS_RX__ProcessBuffer(void)
{

	int i = 0;
	int bufferBeginJump = 0;

	//Search for a full frame
	for (i = 0; i < (sPC.sRx.bufferLength - 1); i++)
	{
		//Is this a start code?
		if (sPC.sRx.u8Buffer[(sPC.sRx.bufferBegin + i) % RPOD_PICOMMS_BUFFER_SIZE] == RPOD_PICOMMS_CONTROL_CHAR && sPC.sRx.u8Buffer[((sPC.sRx.bufferBegin + i + 1) % RPOD_PICOMMS_BUFFER_SIZE)] == RPOD_PICOMMS_FRAME_START)
		{

			//See if we should have the whole header yet
			if ((i + 5) < sPC.sRx.bufferLength)
			{

				//Grab the length of the frame from the header
				Luint16 u16FrameLength = sPC.sRx.u8Buffer[(sPC.sRx.bufferBegin + i + 2) % RPOD_PICOMMS_BUFFER_SIZE];
				int headerLength = 4;
				if (u16FrameLength == RPOD_PICOMMS_CONTROL_CHAR)
				{
					u16FrameLength = u16FrameLength * 256 + sPC.sRx.u8Buffer[(sPC.sRx.bufferBegin + i + 4) % RPOD_PICOMMS_BUFFER_SIZE];
					headerLength++;

					if (sPC.sRx.u8Buffer[(sPC.sRx.bufferBegin + i + 4) % RPOD_PICOMMS_BUFFER_SIZE] == RPOD_PICOMMS_CONTROL_CHAR)
					{
						headerLength++;
					}
				}
				else
				{
					u16FrameLength = u16FrameLength * 256 + sPC.sRx.u8Buffer[(sPC.sRx.bufferBegin + i + 3) % RPOD_PICOMMS_BUFFER_SIZE];
				}

				//See if we have the end of the frame in the buffer yet
				if (i + headerLength + u16FrameLength <= sPC.sRx.bufferLength)
				{
					//Copy the frame into a flat buffer
					//This step isn't 100% necessary but it does make processing the frame a bit easier to follow
					int x;
					if((u16FrameLength + headerLength) < RPOD_PICOMMS_BUFFER_SIZE)
					{
						for (x = 0; x < (u16FrameLength + headerLength); x++)
						{

							sPC.sRx.u8TempFrameBuffer[x] = sPC.sRx.u8Buffer[((x + i) + sPC.sRx.bufferBegin) % RPOD_PICOMMS_BUFFER_SIZE];
						}
					}
					else
					{
						//major fault.
						sPC.sRx.u32Faults++;
					}


					//Process the frame!
					if (u16PICOMMS_RX__ProcessFrame(&sPC.sRx.u8TempFrameBuffer[0], u16FrameLength + 4))
					{
						i += u16FrameLength + headerLength;
						bufferBeginJump += headerLength + u16FrameLength;
					}
				}
				else
				{

					//We have a start code, but not enough data for a full frame yet
					i = sPC.sRx.bufferLength;
				}

			}
			else
			{
				//Don't have the full header yet, nothing to do for now
				i = sPC.sRx.bufferLength - 1;
			}
		}
		else
		{
			//Not sure what we got sent, but it's not a start code so advance the buffer.
			bufferBeginJump++;
		}
	}

	//tod: check that this is not an error
	sPC.sRx.bufferBegin += bufferBeginJump;
	sPC.sRx.bufferBegin = sPC.sRx.bufferBegin % RPOD_PICOMMS_BUFFER_SIZE;
	sPC.sRx.bufferLength -= bufferBeginJump;

}

Luint16 u16PICOMMS_RX__ProcessFrame(Luint8 *frameBuffer, Luint16 length)
{
	int i = 0;
	Luint8 checksum = 0;

	//Check the start and end headers

	//Check the start of the buffer for the sof control code
	//Check the end of the frame for the eof control code
	if (frameBuffer[0] != RPOD_PICOMMS_CONTROL_CHAR || frameBuffer[1] != RPOD_PICOMMS_FRAME_START || frameBuffer[length - 4] != RPOD_PICOMMS_CONTROL_CHAR || frameBuffer[length - 3] != RPOD_PICOMMS_FRAME_END)
	{
		//Improper packet framing, get out of here
		return 0;

	}
	else
	{
		//Proper packet framing so all is well, continue on
	}

	//Simple checkum on the packet, should implement a better scheme

	for (i = 0; i < length-4; i++)
	{
		checksum ^= frameBuffer[i];
	}

	if (frameBuffer[length - 2] != checksum)
	{
		//Bad checksum, abort
		return 0;
	}
	else
	{
		//Checksum is valid, continue on
	}


	//Call user code to indicate we're starting to process a new frame
	if (PICOMMS_RX_frameRXBeginCB != 0)
	{
		PICOMMS_RX_frameRXBeginCB();
	}


	//Shorten any escaped data now that we've isolated a single frame
	//So any {RPOD_PICOMMS_CONTROL_CHAR,RPOD_PICOMMS_CONTROL_CHAR}  becomes simply {RPOD_PICOMMS_CONTROL_CHAR}
	for (i = 2; i < length-1; i++)
	{
		if (frameBuffer[i] == RPOD_PICOMMS_CONTROL_CHAR && frameBuffer[i + 1] == RPOD_PICOMMS_CONTROL_CHAR)
		{
			int x;

			if((i + 1 + length) < RPOD_PICOMMS_BUFFER_SIZE)
			{

				for (x = i + 1; x < length - 1; x++)
				{
					frameBuffer[x] = frameBuffer[x + 1];
				}

				frameBuffer[length - 1] = 0x00;
			}
			else
			{
				sPC.sRx.u32Faults++;
			}
		}
		else
		{
			//no escaped data here, continue on.
		}
	}

	Luint16 position = 4;
	Luint64 rawData;

	//Scan the whole packet for data
	while (position < length)
	{
		//Found a control character
		if (frameBuffer[position] == RPOD_PICOMMS_CONTROL_CHAR)
		{
			position++;

			//See which control character we've got
			switch (frameBuffer[position])
			{

				//Found a data parameter in the packet
				case RPOD_PICOMMS_PARAMETER_START:
				{
					position++;

					//Figure out which type of data we're being given
					int dataType = frameBuffer[position] & 0x0F;
					Luint8 dataSize = (frameBuffer[position] & 0xF0) / 16;

					//Copy the parameter data into a buffer and pass it along for processing by user code
					if (dataType == 1 || dataType == 2 || dataType == 3)
					{

						//Copy data from the packet buffer to a 64 bit buffer and swap the endianess in the process
						rawData = frameBuffer[position+3];

						Luint8 i; //Put this somewhere else?
						for(i = 1; i <dataSize; i++)
						{
							rawData *= 256;
							rawData += frameBuffer[position+3 + i];
						}

						//TODO Add code and defines to not swap endianess on big endian CPUs

						vPICOMMS_RX__ReceiveParam(frameBuffer[position], frameBuffer[position + 1] * 256 + frameBuffer[position+2], rawData);

					}
					else if (dataType == 0)
					{

					}
					else
					{

					}

					position += dataSize+3;
				}
				break;

			case RPOD_PICOMMS_FRAME_END:
				if (PICOMMS_RX_frameRXEndCB != 0)
				{
					PICOMMS_RX_frameRXEndCB();
				}
				return 1;
			}
		}
		else
		{
			//Should report an error
			position++;
		}
	}

	if(PICOMMS_RX_frameRXEndCB != 0)
	{
		PICOMMS_RX_frameRXEndCB();

	}
	else
	{
		//No callback to make
	}
		return 1;
}




void vPICOMMS_RX__ReceiveParam(Luint8 u8Type, Luint16 u16Index, Luint64 u64RawData)
{
	Lfloat32 float32Ret = 0;
	Lfloat64 float64Ret = 0;
	switch (u8Type)
	{
		case PICOMMS_INT8:
			//Make sure the function pointer was assigned
			if(PICOMMS_RX_recvLint8 != 0)
			{
				PICOMMS_RX_recvLint8(u16Index, (Lint8)u64RawData);
			}else{
				//Do nothing
			}
			break;
		case PICOMMS_UINT8:
			if(PICOMMS_RX_recvLuint8 != 0)
			{
				PICOMMS_RX_recvLuint8(u16Index, (Luint8)u64RawData);
			}else{
				//Do nothing
			}
			break;

		case PICOMMS_INT16:
			if(PICOMMS_RX_recvLint16 != 0)
			{
				PICOMMS_RX_recvLint16(u16Index, (Lint16)u64RawData);
			}else{
				//Do nothing
			}
			break;

		case PICOMMS_UINT16:
			if(PICOMMS_RX_recvLuint16 != 0)
			{
				PICOMMS_RX_recvLuint16(u16Index, (Luint16)u64RawData);
			}else{
				//Do nothing
			}
			break;

		case PICOMMS_INT32:
			if(PICOMMS_RX_recvLint32 != 0)
			{
				PICOMMS_RX_recvLint32(u16Index, (Lint32)u64RawData);
			}else{
				//Do nothing
			}
			break;

		case PICOMMS_UINT32:
			if(PICOMMS_RX_recvLuint32 != 0)
			{
				PICOMMS_RX_recvLuint32(u16Index, (Luint32)u64RawData);
			}else{
				//Do nothing
			}
			break;

		case PICOMMS_INT64:
			if(PICOMMS_RX_recvLint64 != 0)
			{
				PICOMMS_RX_recvLint64(u16Index, (Lint64)u64RawData);
			}else{
				//Do nothing
			}
			break;

		case PICOMMS_UINT64:
			if(PICOMMS_RX_recvLuint64 != 0)
			{
				PICOMMS_RX_recvLuint64(u16Index, (Luint64)u64RawData);
			}else{
				//Do nothing
			}
			break;

		case PICOMMS_FLOAT:
			//Simply casting doesn't work so we have to resort to byte manipulation :/
			*((Luint8*)(&float32Ret)+3) = *((Luint8*)(&u64RawData)+3);
			*((Luint8*)(&float32Ret)+2) = *((Luint8*)(&u64RawData)+2);
			*((Luint8*)(&float32Ret)+1) = *((Luint8*)(&u64RawData)+1);
			*((Luint8*)(&float32Ret)+0) = *((Luint8*)(&u64RawData)+0);
			if(PICOMMS_RX_recvLfloat32 != 0)
			{
				PICOMMS_RX_recvLfloat32(u16Index,  float32Ret);
			}else{
				//Do nothing
			}
			break;

		case PICOMMS_DOUBLE:
			//Simply casting doesn't work so we have to resort to byte manipulation :/
			*((Luint8*)(&float64Ret)+7) = *((Luint8*)(&u64RawData)+7);
			*((Luint8*)(&float64Ret)+6) = *((Luint8*)(&u64RawData)+6);
			*((Luint8*)(&float64Ret)+5) = *((Luint8*)(&u64RawData)+5);
			*((Luint8*)(&float64Ret)+4) = *((Luint8*)(&u64RawData)+4);
			*((Luint8*)(&float64Ret)+3) = *((Luint8*)(&u64RawData)+3);
			*((Luint8*)(&float64Ret)+2) = *((Luint8*)(&u64RawData)+2);
			*((Luint8*)(&float64Ret)+1) = *((Luint8*)(&u64RawData)+1);
			*((Luint8*)(&float64Ret)+0) = *((Luint8*)(&u64RawData)+0);
			if(PICOMMS_RX_recvLfloat64 != 0)
			{
				PICOMMS_RX_recvLfloat64(u16Index, float64Ret);
			}else{
					//Do nothing
			}
			break;

		default:
			//fall on.
			break;
	}
}


#endif //C_LOCALDEF__LCCM656__ENABLE_RX
#endif //#if C_LOCALDEF__LCCM656__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM656__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

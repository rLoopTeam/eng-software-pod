/**
 * @file		PI_COMMS__TX.C
 * @brief		Architecture neutral transmit code from host to Pi.
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 * @st_fileID	LCCM656R0.FILE.004
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup PI_COMMS
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup PI_COMMS__TX
 * @ingroup PI_COMMS
 * @{ */

#include "../pi_comms.h"
#if C_LOCALDEF__LCCM656__ENABLE_THIS_MODULE == 1U

//the main structure
extern struct _strPICOMMS sPC;

void vPICOMMS_TX__Init(void)
{


}



void rI2CTX_beginFrame()
{
	sPC.rI2CTX_buffer[0] = RPOD_I2C_CONTROL_CHAR;
	sPC.rI2CTX_buffer[1] = RPOD_I2C_FRAME_START;
	sPC.rI2CTX_bufferPos = 4;
	//2,3 will be filled in with the length in endFrame()
}

void rI2CTX_calculateChecksum(Luint16 lastByte)
{
	sPC.checksum = 0;
	Luint16 i;
	for (i = 0; i < lastByte;i++)
	{
		sPC.checksum ^= sPC.rI2CTX_buffer[i];
	}
}



void rI2CTX_add_checked_byte(Luint8 byte)
{
	sPC.rI2CTX_buffer[sPC.rI2CTX_bufferPos++] = byte;
	if(byte == RPOD_I2C_CONTROL_CHAR)
	{
		sPC.rI2CTX_buffer[sPC.rI2CTX_bufferPos++] = byte;
	}
}

void rI2CTX_add_unchecked_byte(Luint8 byte)
{
	sPC.rI2CTX_buffer[sPC.rI2CTX_bufferPos++] = byte;
}

Luint16 rI2CTX_endFrame()
{
	sPC.rI2CTX_frameLength = sPC.rI2CTX_bufferPos;

	Luint8 length1 = sPC.rI2CTX_frameLength >> 8;
	Luint8 length2 = sPC.rI2CTX_frameLength & 0xFF;

	if (length1 != RPOD_I2C_CONTROL_CHAR && length2 != RPOD_I2C_CONTROL_CHAR)
	{
		sPC.rI2CTX_buffer[2] = length1;
		sPC.rI2CTX_buffer[3] = length2;
	}
	else if (length1 == RPOD_I2C_CONTROL_CHAR && length2 == RPOD_I2C_CONTROL_CHAR)
	{
		sPC.rI2CTX_buffer[2] = length1;
		sPC.rI2CTX_buffer[3] = length1;
		sPC.rI2CTX_buffer[4] = length2;
		sPC.rI2CTX_buffer[5] = length2;
		memcpy(rI2CTX_buffer + 4, rI2CTX_buffer + 6, rI2CTX_bufferPos - 4); //DOUBLE CHECK THIS
		sPC.rI2CTX_bufferPos += 2;
	}
	else
	{
		if (length1 == RPOD_I2C_CONTROL_CHAR)
		{
			sPC.rI2CTX_buffer[2] = length1;
			sPC.rI2CTX_buffer[3] = length1;
			sPC.rI2CTX_buffer[4] = length2;
		}
		else
		{
			sPC.rI2CTX_buffer[2] = length1;
			sPC.rI2CTX_buffer[3] = length2;
			sPC.rI2CTX_buffer[4] = length2;
		}
		memcpy(rI2CTX_buffer + 4, rI2CTX_buffer + 5, rI2CTX_bufferPos - 4);  //DOUBLE CHECK THIS
		sPC.rI2CTX_bufferPos += 1;
	}
	
	rI2CTX_calculateChecksum(rI2CTX_bufferPos);

	rI2CTX_add_unchecked_byte(RPOD_I2C_CONTROL_CHAR);
	rI2CTX_add_unchecked_byte(RPOD_I2C_FRAME_END);
	rI2CTX_add_unchecked_byte(sPC.checksum);
	rI2CTX_add_unchecked_byte(0x00);

	return sPC.rI2CTX_bufferPos;
}

rI2CTX_addHeader(Luint8 dataType, Luint16 u16Index)
{
	rI2CTX_add_unchecked_byte(RPOD_I2C_CONTROL_CHAR);
	rI2CTX_add_checked_byte(RPOD_I2C_PARAMETER_START);
	rI2CTX_add_checked_byte(dataType);

	Luint16 i;

	for (i = 0; i < sizeof(index); i++)
	{
		Luint8 byte = index >> ((sizeof(index)-i-1)*8);
		rI2CTX_add_checked_byte(byte);
	}
}

void rI2CTX_addParameter_int8(Luint16 u16Index, Lint8 data)
{
	rI2CTX_addHeader(0x11,index);

	rI2CTX_add_checked_byte(data);
}

void rI2CTX_addParameter_uint8(Luint16 u16Index, Luint8 data)
{
	rI2CTX_addHeader(0x12,index);

	rI2CTX_add_checked_byte(data);
 }

void rI2CTX_addParameter_int16(Luint16 u16Index, Lint16 data)
{
	rI2CTX_addHeader(0x21,index);

	Luint16 i;

	for (i = 0; i < sizeof(data); i++)
	{
		Luint8 byte = data >> ((sizeof(data)-i-1)*8);
		rI2CTX_add_checked_byte(byte);
	}
}

void rI2CTX_addParameter_uint16(Luint16 u16Index, Luint16 data)
{
	rI2CTX_addHeader(0x22,index);

	Luint16 i;

	for (i = 0; i < sizeof(data); i++)
	{
		Luint8 byte = data >> ((sizeof(data) - i - 1) * 8);
		rI2CTX_add_checked_byte(byte);
	}
}

void rI2CTX_addParameter_int64(Luint16 u16Index, Lint64 data)
{
	rI2CTX_addHeader(0x81,index);

	Luint16 i;

	for (i = 0; i < sizeof(data); i++)
	{
		Luint8 byte = data >> ((sizeof(data) - i - 1) * 8);
		rI2CTX_add_checked_byte(byte);
	}
}

void rI2CTX_addParameter_uint64(Luint16 u16Index, Luint64 data)
{
	rI2CTX_addHeader(0x82,index);

	Luint16 i;

	for (i = 0; i < sizeof(data); i++)
	{
		Luint8 byte = data >> ((sizeof(data) - i - 1) * 8);
		rI2CTX_add_checked_byte(byte);
	}
}

void rI2CTX_addParameter_int32(Luint16 u16Index, Lint32 data)
{
	rI2CTX_addHeader(0x41,index);

	Luint16 i;

	for (i = 0; i < sizeof(data); i++)
	{
		Luint8 byte = data >> ((sizeof(data) - i - 1) * 8);
		rI2CTX_add_checked_byte(byte);
	}
}

void rI2CTX_addParameter_uint32(Luint16 u16Index, Luint32 data)
{
	rI2CTX_addHeader(0x42,index);

	Luint16 i;

	for (i = 0; i < sizeof(data); i++)
	{
		Luint8 byte = data >> ((sizeof(data) - i - 1) * 8);
		rI2CTX_add_checked_byte(byte);
	}
}

void rI2CTX_addParameter_float(Luint16 u16Index, float data)
{
	rI2CTX_addHeader(0x43,index);

	Luint32 rawData;
	memcpy(&rawData, &data, 4);

	Luint16 i;

	for (i = 0; i < sizeof(rawData); i++)
	{
		Luint8 byte = rawData >> ((sizeof(rawData) - i - 1) * 8);
		rI2CTX_add_checked_byte(byte);
	}
}

void rI2CTX_addParameter_double(Luint16 u16Index, double data)
{
	rI2CTX_addHeader(0x83,index);

	Luint64 rawData;
	memcpy(&rawData, &data, 8);

	Luint16 i;

	for (i = 0; i < sizeof(rawData); i++)
	{
		Luint8 byte = rawData >> ((sizeof(rawData) - i - 1) * 8);
		rI2CTX_add_checked_byte(byte);
	}
}

#endif //#if C_LOCALDEF__LCCM656__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM656__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

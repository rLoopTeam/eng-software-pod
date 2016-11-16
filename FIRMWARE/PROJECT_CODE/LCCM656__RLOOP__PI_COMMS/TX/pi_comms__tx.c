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

void PICOMMS_TX_beginFrame()
{
	sPC.sTx.PICOMMS_TX_buffer[0] = RPOD_PICOMMS_CONTROL_CHAR;
	sPC.sTx.PICOMMS_TX_buffer[1] = RPOD_PICOMMS_FRAME_START;
	sPC.sTx.PICOMMS_TX_bufferPos = 4;
	//2,3 will be filled in with the length in endFrame()
}

void PICOMMS_TX_calculateChecksum(Luint16 lastByte)
{
	sPC.sTx.u8Checksum = 0;
	Luint16 i;
	for (i = 0; i < lastByte;i++)
	{
		sPC.sTx.u8Checksum ^= sPC.sTx.PICOMMS_TX_buffer[i];
	}
}



void PICOMMS_TX_add_checked_byte(Luint8 byte)
{

	if(sPC.sTx.PICOMMS_TX_bufferPos < (RPOD_PICOMMS_BUFFER_SIZE - 2))
	{
		sPC.sTx.PICOMMS_TX_buffer[sPC.sTx.PICOMMS_TX_bufferPos++] = byte;

		if(byte ==  RPOD_PICOMMS_CONTROL_CHAR)
		{
			sPC.sTx.PICOMMS_TX_buffer[sPC.sTx.PICOMMS_TX_bufferPos++] = byte;
		}
	}
}

void PICOMMS_TX_add_unchecked_byte(Luint8 byte)
{
	if(sPC.sTx.PICOMMS_TX_bufferPos < (RPOD_PICOMMS_BUFFER_SIZE - 2))
	{
		sPC.sTx.PICOMMS_TX_buffer[sPC.sTx.PICOMMS_TX_bufferPos++] = byte;
	}
}

Luint8 * pu8I2CTx__Get_BufferPointer(void)
{
	return &sPC.sTx.PICOMMS_TX_buffer[0];
}

Luint16 PICOMMS_TX_endFrame()
{
	sPC.sTx.PICOMMS_TX_frameLength = sPC.sTx.PICOMMS_TX_bufferPos;

	Luint8 length1 = sPC.sTx.PICOMMS_TX_frameLength >> 8;
	Luint8 length2 = sPC.sTx.PICOMMS_TX_frameLength & 0xFF;

	//TODO: Write test cases for the corner cases
	if (length1 !=  RPOD_PICOMMS_CONTROL_CHAR && length2 !=  RPOD_PICOMMS_CONTROL_CHAR)
	{
		sPC.sTx.PICOMMS_TX_buffer[2] = length1;
		sPC.sTx.PICOMMS_TX_buffer[3] = length2;
	}
	else if (length1 ==  RPOD_PICOMMS_CONTROL_CHAR && length2 ==  RPOD_PICOMMS_CONTROL_CHAR)
	{
		sPC.sTx.PICOMMS_TX_buffer[2] = length1;
		sPC.sTx.PICOMMS_TX_buffer[3] = length1;
		sPC.sTx.PICOMMS_TX_buffer[4] = length2;
		sPC.sTx.PICOMMS_TX_buffer[5] = length2;

		Luint16 i;
		for(i = 0; i < sPC.sTx.PICOMMS_TX_bufferPos - 4; i++)
		{
			sPC.sTx.PICOMMS_TX_buffer[i+4] = sPC.sTx.PICOMMS_TX_buffer[i+6];
		}

		sPC.sTx.PICOMMS_TX_bufferPos += 2;
	}
	else
	{
		if (length1 ==  RPOD_PICOMMS_CONTROL_CHAR)
		{
			sPC.sTx.PICOMMS_TX_buffer[2] = length1;
			sPC.sTx.PICOMMS_TX_buffer[3] = length1;
			sPC.sTx.PICOMMS_TX_buffer[4] = length2;
		}
		else
		{
			sPC.sTx.PICOMMS_TX_buffer[2] = length1;
			sPC.sTx.PICOMMS_TX_buffer[3] = length2;
			sPC.sTx.PICOMMS_TX_buffer[4] = length2;
		}

		Luint16 i;
		for(i = 0; i < sPC.sTx.PICOMMS_TX_bufferPos - 4; i++)
		{
			sPC.sTx.PICOMMS_TX_buffer[i+4] = sPC.sTx.PICOMMS_TX_buffer[i+5];
		}

		sPC.sTx.PICOMMS_TX_bufferPos += 1;
	}
	
	PICOMMS_TX_calculateChecksum(sPC.sTx.PICOMMS_TX_bufferPos);

	PICOMMS_TX_add_unchecked_byte( RPOD_PICOMMS_CONTROL_CHAR);
	PICOMMS_TX_add_unchecked_byte( RPOD_PICOMMS_FRAME_END);
	PICOMMS_TX_add_unchecked_byte(sPC.sTx.u8Checksum);
	PICOMMS_TX_add_unchecked_byte(0x00);

	return sPC.sTx.PICOMMS_TX_bufferPos;
}

void PICOMMS_TX_addHeader(Luint8 dataType, Luint16 u16Index)
{
	PICOMMS_TX_add_unchecked_byte( RPOD_PICOMMS_CONTROL_CHAR);
	PICOMMS_TX_add_checked_byte( RPOD_PICOMMS_PARAMETER_START);
	PICOMMS_TX_add_checked_byte(dataType);

	Luint16 i;

	for (i = 0; i < sizeof(u16Index); i++)
	{
		Luint8 byte = u16Index >> ((sizeof(u16Index)-i-1)*8);
		PICOMMS_TX_add_checked_byte(byte);
	}
}

void PICOMMS_TX_addParameter_int8(Luint16 u16Index, Lint8 data)
{
	PICOMMS_TX_addHeader(0x11, u16Index);

	PICOMMS_TX_add_checked_byte(data);
}

void vPICOMMS_TX__Add_U8(Luint16 u16Index, Luint8 data)
{
	PICOMMS_TX_addHeader(0x12, u16Index);

	PICOMMS_TX_add_checked_byte(data);
 }

void PICOMMS_TX_addParameter_int16(Luint16 u16Index, Lint16 data)
{
	PICOMMS_TX_addHeader(0x21, u16Index);

	Luint16 i;

	for (i = 0; i < sizeof(data); i++)
	{
		Luint8 byte = data >> ((sizeof(data)-i-1)*8);
		PICOMMS_TX_add_checked_byte(byte);
	}
}

void PICOMMS_TX_addParameter_uint16(Luint16 u16Index, Luint16 data)
{
	PICOMMS_TX_addHeader(0x22, u16Index);

	Luint16 i;

	for (i = 0; i < sizeof(data); i++)
	{
		Luint8 byte = data >> ((sizeof(data) - i - 1) * 8);
		PICOMMS_TX_add_checked_byte(byte);
	}
}

void PICOMMS_TX_addParameter_int64(Luint16 u16Index, Lint64 data)
{
	PICOMMS_TX_addHeader(0x81, u16Index);

	Luint16 i;

	for (i = 0; i < sizeof(data); i++)
	{
		Luint8 byte = data >> ((sizeof(data) - i - 1) * 8);
		PICOMMS_TX_add_checked_byte(byte);
	}
}

void PICOMMS_TX_addParameter_uint64(Luint16 u16Index, Luint64 data)
{
	PICOMMS_TX_addHeader(0x82, u16Index);

	Luint16 i;

	for (i = 0; i < sizeof(data); i++)
	{
		Luint8 byte = data >> ((sizeof(data) - i - 1) * 8);
		PICOMMS_TX_add_checked_byte(byte);
	}
}

void PICOMMS_TX_addParameter_int32(Luint16 u16Index, Lint32 data)
{
	PICOMMS_TX_addHeader(0x41, u16Index);

	Luint16 i;

	for (i = 0; i < sizeof(data); i++)
	{
		Luint8 byte = data >> ((sizeof(data) - i - 1) * 8);
		PICOMMS_TX_add_checked_byte(byte);
	}
}

void PICOMMS_TX_addParameter_uint32(Luint16 u16Index, Luint32 data)
{
	PICOMMS_TX_addHeader(0x42, u16Index);

	Luint16 i;

	for (i = 0; i < sizeof(data); i++)
	{
		Luint8 byte = data >> ((sizeof(data) - i - 1) * 8);
		PICOMMS_TX_add_checked_byte(byte);
	}
}

void vPICOMMS_TX__Add_F32(Luint16 u16Index, Lfloat32 data)
{
	PICOMMS_TX_addHeader(0x43, u16Index);

	Luint32 rawData;

	*((Luint8*)(&rawData)+3) = *((Luint8*)(&data)+3);
	*((Luint8*)(&rawData)+2) = *((Luint8*)(&data)+2);
	*((Luint8*)(&rawData)+1) = *((Luint8*)(&data)+1);
	*((Luint8*)(&rawData)+0) = *((Luint8*)(&data)+0);

	Luint16 i;

	for (i = 0; i < sizeof(rawData); i++)
	{
		Luint8 byte = rawData >> ((sizeof(rawData) - i - 1) * 8);
		PICOMMS_TX_add_checked_byte(byte);
	}
}

void PICOMMS_TX_addParameter_double(Luint16 u16Index, Lfloat64 data)
{
	PICOMMS_TX_addHeader(0x83, u16Index);

	Luint64 rawData;

	*((Luint8*)(&rawData)+7) = *((Luint8*)(&data)+7);
	*((Luint8*)(&rawData)+6) = *((Luint8*)(&data)+6);
	*((Luint8*)(&rawData)+5) = *((Luint8*)(&data)+5);
	*((Luint8*)(&rawData)+4) = *((Luint8*)(&data)+4);
	*((Luint8*)(&rawData)+3) = *((Luint8*)(&data)+3);
	*((Luint8*)(&rawData)+2) = *((Luint8*)(&data)+2);
	*((Luint8*)(&rawData)+1) = *((Luint8*)(&data)+1);
	*((Luint8*)(&rawData)+0) = *((Luint8*)(&data)+0);

	Luint16 i;

	for (i = 0; i < sizeof(rawData); i++)
	{
		Luint8 byte = rawData >> ((sizeof(rawData) - i - 1) * 8);
		PICOMMS_TX_add_checked_byte(byte);
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

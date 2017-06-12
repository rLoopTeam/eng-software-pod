/**
 * @file		DAQ.C
 * @brief		Main DAQ file.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM662R0.FILE.000
 */

#include "daq.h"
/**
 * @addtogroup MULTICORE
 * @{
*/
/**
 * @addtogroup DAQ
 * @ingroup MULTICORE
 * @{
*/
/**
 * @addtogroup DAQ__CORE
 * @ingroup DAQ
 * @{
*/
#if C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE == 1U

struct _strDAQ sDAQ;

/***************************************************************************//**
 * @brief
 * Init the DAQ module
 * To be called early in the program.
 * 
 * @st_funcMD5		B410D8BC951DF82A75D71AD117A809EA
 * @st_funcID		LCCM662R0.FILE.000.FUNC.001
 */
void vSIL3_DAQ__Init(void)
{

	Luint16 u16Counter;
	Luint16 u16Counter2;
	
	//init vars
	sDAQ.u8StreamingOn = 0U;
	sDAQ.sInterlock.u8U8 = 0U;
	sDAQ.sInterlock.u8S16 = 0U;
	sDAQ.sInterlock.u8U16 = 0U;
	sDAQ.sInterlock.u8S32 = 0U;
	sDAQ.sInterlock.u8U32 = 0U;
	sDAQ.sInterlock.u8F32 = 0U;

	u16Counter2 = 0U;
	#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U8 > 0
	for(u16Counter = 0U; u16Counter < C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U8; u16Counter++)
	{
		sDAQ.u16WatermarkLevel[u16Counter2] = C_LOCALDEF__LCCM662__BUFFER_WATERMARK_LEVEL * 4U;
		vSIL3_SOFTFIFO__Init(&sDAQ.sFIFO[u16Counter2], C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS * 4U);
		sDAQ.u8SizeMultiplier[u16Counter2] = 1U;
		//inc the global counter
		u16Counter2++;
	}
	#endif
	#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S16 > 0
	for(u16Counter = 0U; u16Counter < C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S16; u16Counter++)
	{
		sDAQ.u16WatermarkLevel[u16Counter2] = C_LOCALDEF__LCCM662__BUFFER_WATERMARK_LEVEL * 2U;
		vSIL3_SOFTFIFO__Init(&sDAQ.sFIFO[u16Counter2], C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS * 2U);
		sDAQ.u8SizeMultiplier[u16Counter2] = 2U;
		//inc the global counter
		u16Counter2++;
	}
	#endif
	#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U16 > 0
	for(u16Counter = 0U; u16Counter < C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U16; u16Counter++)
	{
		sDAQ.u16WatermarkLevel[u16Counter2] = C_LOCALDEF__LCCM662__BUFFER_WATERMARK_LEVEL * 2U;
		vSIL3_SOFTFIFO__Init(&sDAQ.sFIFO[u16Counter2], C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS * 2U);
		sDAQ.u8SizeMultiplier[u16Counter2] = 2U;
		//inc the global counter
		u16Counter2++;
	}
	#endif
	#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S32 > 0
	for(u16Counter = 0U; u16Counter < C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S32; u16Counter++)
	{
		sDAQ.u16WatermarkLevel[u16Counter2] = C_LOCALDEF__LCCM662__BUFFER_WATERMARK_LEVEL;
		vSIL3_SOFTFIFO__Init(&sDAQ.sFIFO[u16Counter2], C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS);
		sDAQ.u8SizeMultiplier[u16Counter2] = 4U;
		//inc the global counter
		u16Counter2++;
	}
	#endif
	#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U32 > 0
	for(u16Counter = 0U; u16Counter < C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U32; u16Counter++)
	{
		sDAQ.u16WatermarkLevel[u16Counter2] = C_LOCALDEF__LCCM662__BUFFER_WATERMARK_LEVEL;
		vSIL3_SOFTFIFO__Init(&sDAQ.sFIFO[u16Counter2], C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS);
		sDAQ.u8SizeMultiplier[u16Counter2] = 4U;
		//inc the global counter
		u16Counter2++;
	}
	#endif
	#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__F32 > 0
	for(u16Counter = 0U; u16Counter < C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__F32; u16Counter++)
	{
		sDAQ.u16WatermarkLevel[u16Counter2] = C_LOCALDEF__LCCM662__BUFFER_WATERMARK_LEVEL;
		vSIL3_SOFTFIFO__Init(&sDAQ.sFIFO[u16Counter2], C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS);
		sDAQ.u8SizeMultiplier[u16Counter2] = 4U;
		//inc the global counter
		u16Counter2++;
	}
	#endif

	//init the FIFO's
	for(u16Counter = 0U; u16Counter < M_DAQ__NUM_CHANNELS; u16Counter++)
	{
		//clear the watermarks
		sDAQ.u8WatermarkFlag[u16Counter] = 0U;
		sDAQ.u8ForceFlushFlag[u16Counter] = 0U;
		
		#if C_LOCALDEF__LCCM662__ENABLE_USER_PAYLOAD_TYPES == 1U
			sDAQ.u16User_PacketType[u16Counter] = 0U;
		#endif

		//clear the timer
		#if C_LOCALDEF__LCCM662__ENABLE_TIMER_IN_DATA == 1U
		for(u16Counter2 = 0U; u16Counter2 < C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS; u16Counter2++)
		{
			sDAQ.sBuffers.u32Timer[u16Counter][u16Counter2] = 0U;
		}
		#endif
	}
	
	//init the append module
	vSIL3_DAQ_APPEND__Init();

	//init the sates
	sDAQ.eMainState = DAQ_STATE__IDLE;

}


/***************************************************************************//**
 * @brief
 * Process any DAQ tasks
 * Call this as fast as possible from main program loop
 *
 * @note
 * Sould make sure the transport mechanism (such as eth) is up before
 * processing any data.
 * 
 * @st_funcMD5		90C4D1787121A78BCD8EBB02437A09E5
 * @st_funcID		LCCM662R0.FILE.000.FUNC.002
 */
void vSIL3_DAQ__Process(void)
{
	Luint16 u16Counter;
	Lint16 s16Return;
	Luint8 * pu8Temp;
	Lint16 s16Test;
	Luint16 u16Burst;
	Luint8 u8Flag;

	u8Flag = 0U;
	
	//process our state machine.
	switch(sDAQ.eMainState)
	{
		case DAQ_STATE__IDLE:
		
			//indicate our current fill check point.
			sDAQ.u16ProcessPoint = 0U;
		
			//just fall on
			sDAQ.eMainState = DAQ_STATE__CHECK_FILL;
			break;
		
		case DAQ_STATE__CHECK_FILL:
			//check the watermark level
			for(u16Counter = 0U; u16Counter < M_DAQ__NUM_CHANNELS; u16Counter++)
			{
				//mark any entries as appropriate.
				if(sDAQ.sFIFO[u16Counter].uFIFO_FillLevel >= sDAQ.u16WatermarkLevel[u16Counter])
				{
					sDAQ.u8WatermarkFlag[u16Counter] = 1U;
				}
				else
				{
					sDAQ.u8WatermarkFlag[u16Counter] = 0U;
				}
			}

			//move to process the fill levels

			//indicate our current fill check point.
			sDAQ.u16ProcessPoint = 0U;

			//just fall on
			sDAQ.eMainState = DAQ_STATE__PROCESS_FILL;
			break;
	
		case DAQ_STATE__PROCESS_FILL:
	
			//see if we are watermarked or need to flush
			if((sDAQ.u8WatermarkFlag[sDAQ.u16ProcessPoint] == 1U) || (sDAQ.u8ForceFlushFlag[sDAQ.u16ProcessPoint] == 1U))
			{
				//get the buffer pointer.
				pu8Temp = 0;
				s16Return = s16SIL3_DAQ_APPEND__Index_to_BufferPointer(sDAQ.u16ProcessPoint, &pu8Temp);
				if(s16Return == 0)
				{
					//copy our length
					u16Burst = (Luint16)sDAQ.sFIFO[sDAQ.u16ProcessPoint].uFIFO_FillLevel;

					if(u16Burst == 0U)
					{
						//if we have nothing to burst, but have wanted a flush then clear the flag.
						//The Tx function will return -ve if the burst is 0 anyhow.
						sDAQ.u8ForceFlushFlag[sDAQ.u16ProcessPoint] = 0U;
					}
					else
					{
						//fall on.
					}

					//transmit notification
					//we may fail here due to Eth interface currently processing something else, so come back and re-check
					s16Test = M_LOCALDEF__LCCM662__TX_HANDLER(sDAQ.u16ProcessPoint, pu8Temp, u16Burst * (Luint16)sDAQ.u8SizeMultiplier[sDAQ.u16ProcessPoint]);
					if(s16Test >= 0)
					{

						//empty the fifo now
						//risk here is we get another entry while drainging, so use flush.
						s16SIL3_SOFTFIFO__PopMany(&sDAQ.sFIFO[sDAQ.u16ProcessPoint], u16Burst);

						//clear.
						sDAQ.u8WatermarkFlag[sDAQ.u16ProcessPoint] = 0U;
						sDAQ.u8ForceFlushFlag[sDAQ.u16ProcessPoint] = 0U;

					}
					else
					{
						//transmitter was busy
						//this is not an error, come back and try again in a bit, do not clear
						//the current process point,
						u8Flag = 1U;
					}
				}
				else
				{
					//log the fault
					//we got the wrong buffer index or something out of range.
				}
			
			}
			else
			{
				//fall on.
				//nothing to do for this index.
			}
	
			if(u8Flag == 0U)
			{
				//increment for next time around
				sDAQ.u16ProcessPoint++;
				if(sDAQ.u16ProcessPoint >= M_DAQ__NUM_CHANNELS)
				{
					//reset.
					sDAQ.u16ProcessPoint = 0U;

					sDAQ.eMainState = DAQ_STATE__CHECK_FILL;

				}
				else
				{
					//stay in state
				}
			}
			else
			{
				//stay in state due to the Ethernet not being ready.
			}
	
			break;
	
	}//switch(sDAQ.eMainState)

}


//this will force the DAQ to transmit what is in its buffers.
//Useful for getting the last packet of data or flushing after a run.
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		3D7159BCDD5CA2DD5868A3A997AC65BE
 * @st_funcID		LCCM662R0.FILE.000.FUNC.009
 */
void vSIL3_DAQ__ForceFlush(void)
{
	Luint16 u16Counter;

	for(u16Counter = 0U; u16Counter < M_DAQ__NUM_CHANNELS; u16Counter++)
	{
		//foce it
		sDAQ.u8ForceFlushFlag[u16Counter] = 1U;
	}
}

#if C_LOCALDEF__LCCM662__ENABLE_USER_PAYLOAD_TYPES == 1U
/***************************************************************************//**
 * @brief
 * Setup the user packet type whcih can be used for transmission
 * 
 * @param[in]		u16Type					Packet type
 * @param[in]		u16Index				Stream Index
 * @st_funcMD5		D056C0C49A29017A501FB7BE0CDC726B
 * @st_funcID		LCCM662R0.FILE.000.FUNC.004
 */
void vSIL3_DAQ__Config_UserPacketType(Luint16 u16Index, Luint16 u16Type)
{
	if(u16Index < M_DAQ__NUM_CHANNELS)
	{
		//assign
		sDAQ.u16User_PacketType[u16Index] = u16Type;
	}
	else
	{
		//out of range,
		//log error
	}

}
#endif //C_LOCALDEF__LCCM662__ENABLE_USER_PAYLOAD_TYPES

/***************************************************************************//**
 * @brief
 * Call this to enable the append systems to work
 * 
 * @st_funcMD5		B7044EB3CED0B26CC84FCC8DE9ADD186
 * @st_funcID		LCCM662R0.FILE.000.FUNC.005
 */
void vSIL3_DAQ__Streaming_On(void)
{
	sDAQ.u8StreamingOn = 1U;

}

/***************************************************************************//**
 * @brief
 * Set this to off when you want to to allow streaming any more
 * 
 * @st_funcMD5		3808023010BF9B42433CCF1D0CA1D1AB
 * @st_funcID		LCCM662R0.FILE.000.FUNC.006
 */
void vSIL3_DAQ__Streaming_Off(void)
{
	sDAQ.u8StreamingOn = 0U;

}

/***************************************************************************//**
 * @brief
 * Return the system level timer / time stamp system
 * 
 * @st_funcMD5		5F1406D4982D87ACF9D12BE3093FC76E
 * @st_funcID		LCCM662R0.FILE.000.FUNC.003
 */
Luint32 u32SIL3_DAQ__Get_SystemTimer(void)
{
	return 0;
}

/***************************************************************************//**
 * @brief
 * Get the current FIFO fill level for a particular index for debug
 * 
 * @param[in]		u16Index			The stream index
 * @st_funcMD5		3744B6AA814D06E45A93130C7CCF562D
 * @st_funcID		LCCM662R0.FILE.000.FUNC.007
 */
Luint16 u16SIL3_DAQ__Get_FIFO_Level(Luint16 u16Index)
{
	return sDAQ.sFIFO[u16Index].uFIFO_FillLevel;
}

/***************************************************************************//**
 * @brief
 * Ge the max FIFO capacity for a particular stream
 * 
 * @param[in]		u16Index			Stream index
 * @st_funcMD5		5D5CE51E235E92CF20C1BD99C07B937A
 * @st_funcID		LCCM662R0.FILE.000.FUNC.008
 */
Luint16 u16SIL3_DAQ__Get_FIFO_Max(Luint16 u16Index)
{
	Lint16 u16Return;
	Luint16 u16Temp;
	
	
	if(u16Index < M_DAQ__S16_OFFSET)
	{
		u16Temp = u16Index - M_DAQ__U8_OFFSET;
		u16Return = C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS * 4;
	}
	else if (u16Index < M_DAQ__U16_OFFSET)
	{
	u16Temp = u16Index - M_DAQ__S16_OFFSET;
		u16Return = C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS * 2;
	}
	else if (u16Index < M_DAQ__S32_OFFSET)
	{
	u16Temp = u16Index - M_DAQ__U16_OFFSET;
		u16Return = C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS * 2;
	}
	else if (u16Index < M_DAQ__U32_OFFSET)
	{
	u16Temp = u16Index - M_DAQ__S32_OFFSET;
		u16Return = C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS;
	}
	else if (u16Index < M_DAQ__F32_OFFSET)
	{
		u16Temp = u16Index - M_DAQ__U32_OFFSET;
		u16Return = C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS;
	}
	else if (u16Index < M_DAQ__NUM_CHANNELS)
	{
		u16Temp = u16Index - M_DAQ__F32_OFFSET;
		u16Return = C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS ;
	}
	else
	{
		u16Return = 0;
	}

	return u16Return;

}

//safety checks
#if C_LOCALDEF__LCCM357__FIFO_DEPTH_U8 == 1U
#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U8 > 0
#if C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS >= 128U
	//cannot because 4*128 > fifo U8 range
	#error
#endif
#endif
#endif

#ifndef C_LOCALDEF__LCCM662__ENABLE_USER_PAYLOAD_TYPES
	#error
#endif

#endif //#if C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */


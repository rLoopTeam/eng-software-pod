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
 * @st_funcMD5		581A85E93EA1B2F3B62DF5E352EEE712
 * @st_funcID		LCCM662R0.FILE.000.FUNC.001
 */
void vDAQ__Init(void)
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
		vSOFTFIFO__Init(&sDAQ.sFIFO[u16Counter2], C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS * 4U);
		sDAQ.u8SizeMultiplier[u16Counter2] = 1U;
		//inc the global counter
		u16Counter2++;
	}
	#endif
	#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S16 > 0
	for(u16Counter = 0U; u16Counter < C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S16; u16Counter++)
	{
		sDAQ.u16WatermarkLevel[u16Counter2] = C_LOCALDEF__LCCM662__BUFFER_WATERMARK_LEVEL * 2U;
		vSOFTFIFO__Init(&sDAQ.sFIFO[u16Counter2], C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS * 2U);
		sDAQ.u8SizeMultiplier[u16Counter2] = 2U;
		//inc the global counter
		u16Counter2++;
	}
	#endif
	#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U16 > 0
	for(u16Counter = 0U; u16Counter < C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U16; u16Counter++)
	{
		sDAQ.u16WatermarkLevel[u16Counter2] = C_LOCALDEF__LCCM662__BUFFER_WATERMARK_LEVEL * 2U;
		vSOFTFIFO__Init(&sDAQ.sFIFO[u16Counter2], C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS * 2U);
		sDAQ.u8SizeMultiplier[u16Counter2] = 2U;
		//inc the global counter
		u16Counter2++;
	}
	#endif
	#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S32 > 0
	for(u16Counter = 0U; u16Counter < C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S32; u16Counter++)
	{
		sDAQ.u16WatermarkLevel[u16Counter2] = C_LOCALDEF__LCCM662__BUFFER_WATERMARK_LEVEL;
		vSOFTFIFO__Init(&sDAQ.sFIFO[u16Counter2], C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS);
		sDAQ.u8SizeMultiplier[u16Counter2] = 4U;
		//inc the global counter
		u16Counter2++;
	}
	#endif
	#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U32 > 0
	for(u16Counter = 0U; u16Counter < C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U32; u16Counter++)
	{
		sDAQ.u16WatermarkLevel[u16Counter2] = C_LOCALDEF__LCCM662__BUFFER_WATERMARK_LEVEL;
		vSOFTFIFO__Init(&sDAQ.sFIFO[u16Counter2], C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS);
		sDAQ.u8SizeMultiplier[u16Counter2] = 4U;
		//inc the global counter
		u16Counter2++;
	}
	#endif
	#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__F32 > 0
	for(u16Counter = 0U; u16Counter < C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__F32; u16Counter++)
	{
		sDAQ.u16WatermarkLevel[u16Counter2] = C_LOCALDEF__LCCM662__BUFFER_WATERMARK_LEVEL;
		vSOFTFIFO__Init(&sDAQ.sFIFO[u16Counter2], C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS);
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
	vDAQ_APPEND__Init();

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
 * @st_funcMD5		5DC7EDD39B36457CC06C98AD46AED619
 * @st_funcID		LCCM662R0.FILE.000.FUNC.002
 */
void vDAQ__Process(void)
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
	
			if(sDAQ.u8WatermarkFlag[sDAQ.u16ProcessPoint] == 1U)
			{
				//get the buffer pointer.
				pu8Temp = 0;
				s16Return = s16DAQ_APPEND__Index_to_BufferPointer(sDAQ.u16ProcessPoint, &pu8Temp);
				if(s16Return == 0)
				{
					//copy our length
					u16Burst = (Luint16)sDAQ.sFIFO[sDAQ.u16ProcessPoint].uFIFO_FillLevel;

					//transmit notification
					//we may fail here due to Eth interface currently processing something else, so come back and re-check
					s16Test = M_LOCALDEF__LCCM662__TX_HANDLER(sDAQ.u16ProcessPoint, pu8Temp, u16Burst * (Luint16)sDAQ.u8SizeMultiplier[sDAQ.u16ProcessPoint]);
					if(s16Test >= 0)
					{

						//empty the fifo now
						//risk here is we get another entry while drainging, so use flush.
						s16SOFTFIFO__PopMany(&sDAQ.sFIFO[sDAQ.u16ProcessPoint], u16Burst);

						//clear.
						sDAQ.u8WatermarkFlag[sDAQ.u16ProcessPoint] = 0U;

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

#if C_LOCALDEF__LCCM662__ENABLE_USER_PAYLOAD_TYPES == 1U
/***************************************************************************//**
 * @brief
 * Setup the user packet type whcih can be used for transmission
 * 
 * @param[in]		u16Type					Packet type
 * @param[in]		u16Index				Stream Index
 * @st_funcMD5		FDF58A2B7B3E921E1B031DC14AFEF139
 * @st_funcID		LCCM662R0.FILE.000.FUNC.004
 */
void vDAQ__Config_UserPacketType(Luint16 u16Index, Luint16 u16Type)
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
 * @st_funcMD5		4FF6B9000EF17A6B31BFBE78D0FDA6C0
 * @st_funcID		LCCM662R0.FILE.000.FUNC.005
 */
void vDAQ__Streaming_On(void)
{
	sDAQ.u8StreamingOn = 1U;

}

/***************************************************************************//**
 * @brief
 * Set this to off when you want to to allow streaming any more
 * 
 * @st_funcMD5		C2E19705FF8709A65750535A037F75CA
 * @st_funcID		LCCM662R0.FILE.000.FUNC.006
 */
void vDAQ__Streaming_Off(void)
{
	sDAQ.u8StreamingOn = 0U;

}

/***************************************************************************//**
 * @brief
 * Return the system level timer / time stamp system
 * 
 * @st_funcMD5		75F1C1FF5FC5481D6567E85928D769FA
 * @st_funcID		LCCM662R0.FILE.000.FUNC.003
 */
Luint32 u32DAQ__Get_SystemTimer(void)
{
	return 0;
}

/***************************************************************************//**
 * @brief
 * Get the current FIFO fill level for a particular index for debug
 * 
 * @param[in]		u16Index			The stream index
 * @st_funcMD5		A92421C110892A54E527939075EA311B
 * @st_funcID		LCCM662R0.FILE.000.FUNC.007
 */
Luint16 u16DAQ__Get_FIFO_Level(Luint16 u16Index)
{
	return sDAQ.sFIFO[u16Index].uFIFO_FillLevel;
}

/***************************************************************************//**
 * @brief
 * Ge the max FIFO capacity for a particular stream
 * 
 * @param[in]		u16Index			Stream index
 * @st_funcMD5		A8C7E9FA65D90623397A37522848F58C
 * @st_funcID		LCCM662R0.FILE.000.FUNC.008
 */
Luint16 u16DAQ__Get_FIFO_Max(Luint16 u16Index)
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


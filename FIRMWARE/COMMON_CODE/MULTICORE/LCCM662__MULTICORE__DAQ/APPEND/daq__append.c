/**
 * @file		DAQ__APPEND.C
 * @brief		Append ata to the DAQ
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM662R0.FILE.004
 */


#include "../daq.h"
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
 * @addtogroup DAQ__APPEND
 * @ingroup DAQ
 * @{
*/
#if C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE == 1U

extern struct _strDAQ sDAQ;

//locals
Lint16 s16SIL3_DAQ_APPEND__Index_to_Buffer_U8(Luint16 u16Index);
Lint16 s16DAQ_APPEND__Index_to_Buffer_S16(Luint16 u16Index);
Lint16 s16DAQ_APPEND__Index_to_Buffer_U16(Luint16 u16Index);
Lint16 s16DAQ_APPEND__Index_to_Buffer_S32(Luint16 u16Index);
Lint16 s16DAQ_APPEND__Index_to_Buffer_U32(Luint16 u16Index);
Lint16 s16DAQ_APPEND__Index_to_Buffer_F32(Luint16 u16Index);

/***************************************************************************//**
 * @brief
 * Init the append module.
 * 
 * @st_funcMD5		2B5FF6E522591A5E4000B0726733F592
 * @st_funcID		LCCM662R0.FILE.004.FUNC.001
 */
void vSIL3_DAQ_APPEND__Init(void)
{
	Luint16 u16Counter;
	Luint16 u16Counter2;

	//clear the stats
	sDAQ.sStats.u32FIFO_U8FullCount = 0U;
	sDAQ.sStats.u32FIFO_S16FullCount = 0U;
	sDAQ.sStats.u32FIFO_U16FullCount = 0U;
	sDAQ.sStats.u32FIFO_S32FullCount = 0U;
	sDAQ.sStats.u32FIFO_U32FullCount = 0U;
	sDAQ.sStats.u32FIFO_F32FullCount = 0U;

	#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U8 > 0U
		for(u16Counter = 0; u16Counter < C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U8; u16Counter++)
		{
			for(u16Counter2 = 0U; u16Counter2 < C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS * 4U; u16Counter2++)
			{
				sDAQ.sBuffers.u8Buffer[u16Counter][u16Counter2] = 0U;
			}
		}
	#endif //C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U8
	#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S16 > 0U
		for(u16Counter = 0; u16Counter < C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S16; u16Counter++)
		{
			for(u16Counter2 = 0U; u16Counter2 < C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS * 2; u16Counter2++)
			{
				sDAQ.sBuffers.s16Buffer[u16Counter][u16Counter2] = 0;
			}
		}
	#endif //C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S16
	#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U16 > 0U
		for(u16Counter = 0; u16Counter < C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U16 * 2U; u16Counter++)
		{
			for(u16Counter2 = 0U; u16Counter2 < C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS * 2; u16Counter2++)
			{
				sDAQ.sBuffers.u16Buffer[u16Counter][u16Counter2] = 0U;
			}
		}
	#endif //C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U16
	#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S32  > 0U
		for(u16Counter = 0; u16Counter < C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S32; u16Counter++)
		{
			for(u16Counter2 = 0U; u16Counter2 < C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS; u16Counter2++)
			{
				sDAQ.sBuffers.s32Buffer[u16Counter][u16Counter2] = 0;
			}
		}
	#endif //C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S32
	#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U32  > 0U
		for(u16Counter = 0; u16Counter < C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U32; u16Counter++)
		{
			for(u16Counter2 = 0U; u16Counter2 < C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS; u16Counter2++)
			{
				sDAQ.sBuffers.u32Buffer[u16Counter][u16Counter2] = 0U;
			}
		}
	#endif //C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U32
	#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__F32  > 0U
		for(u16Counter = 0; u16Counter < C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__F32; u16Counter++)
		{
			for(u16Counter2 = 0U; u16Counter2 < C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS; u16Counter2++)
			{
				sDAQ.sBuffers.f32Buffer[u16Counter][u16Counter2] = 0.0F;
			}
		}
	#endif //C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__F32
		
}

#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U8 > 0
/***************************************************************************//**
 * @brief
 * Append a U8 to the DAQ stream
 * 
 * @param[in]		u8Value					The value to append
 * @param[in]		u16Index				The stream index
 * @st_funcMD5		AC3BA579451A1EF038A58F2225BDF781
 * @st_funcID		LCCM662R0.FILE.004.FUNC.002
 */
void vSIL3_DAQ_APPEND__U8(Luint16 u16Index, Luint8 u8Value)
{
	Lint16 s16Return;
	Lint16 s16BuffIndex;
	Lint16 s16R;

	//init
	s16R = 0;
	
	if(sDAQ.u8StreamingOn == 1U)
	{
		//memory protection
		if(u16Index < M_DAQ__NUM_CHANNELS)
		{
			//check for an interlock
			if(sDAQ.sInterlock.u8U8 == 0U)
			{
				sDAQ.sInterlock.u8U8 = 1U;

				//get our index before we do too much more.
				s16BuffIndex = s16SIL3_DAQ_APPEND__Index_to_Buffer_U8(u16Index);
				if(s16BuffIndex >= 0)
				{
					s16Return = s16SIL3_SOFTFIFO__Push(&sDAQ.sFIFO[u16Index]);
					if(s16Return >= 0)
					{
						//write the data in the slot.
						sDAQ.sBuffers.u8Buffer[(Luint16)s16BuffIndex][(Luint16)s16Return] = u8Value;

						//do the timer if needed.
						#if C_LOCALDEF__LCCM662__ENABLE_TIMER_IN_DATA == 1U
							//timer index is based on global index, not related to the data type.
							sDAQ.sBuffers.u32Timer[u16Index][(Luint16)s16Return] = u32SIL3_DAQ__Get_SystemTimer();
						#endif
					}
					else
					{
						//log the fault
						sDAQ.sStats.u32FIFO_U8FullCount++;
						s16R = -1;
					}
				}
				else
				{
					//big error
					s16R = -2;
				}

				//clear the interlock.
				sDAQ.sInterlock.u8U8 = 0U;

			}//if (sDAQ.sInterlock.u8U8 == 0U)
			else
			{
				//error, we are interlocked
				sDAQ.sInterlock.u8U8 = 1U;
				s16R = -3;
			}//else if (sDAQ.sInterlock.u8U8 == 0U)
		}
		else
		{
			//log the fault
			s16R = -4;
		}

	}
	else
	{
		//streaming not enabled yet, fall on
	}

	//return s16R;
}

#endif

#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S16 > 0
/***************************************************************************//**
 * @brief
 * Append a S16 to the DAQ stream
 *
 * @param[in]		s16Value				The value to append
 * @param[in]		u16Index				The stream index
 * @st_funcMD5		600E9702BD683635DC27D82143040133
 * @st_funcID		LCCM662R0.FILE.004.FUNC.005
 */
void vSIL3_DAQ_APPEND__S16(Luint16 u16Index, Lint16 s16Value)
{
	Lint16 s16Return;
	Lint16 s16BuffIndex;

	if(sDAQ.u8StreamingOn == 1U)
	{
		//memory protection
		if(u16Index < M_DAQ__NUM_CHANNELS)
		{
			//check for an interlock
			if(sDAQ.sInterlock.u8S16 == 0U)
			{
				sDAQ.sInterlock.u8S16 = 1U;

				//get our index before we do too much more.
				s16BuffIndex = s16DAQ_APPEND__Index_to_Buffer_S16(u16Index);
				if(s16BuffIndex >= 0)
				{
					s16Return = s16SIL3_SOFTFIFO__Push(&sDAQ.sFIFO[u16Index]);
					if(s16Return >= 0)
					{
						//write the data in the slot.
						sDAQ.sBuffers.s16Buffer[(Luint16)s16BuffIndex][(Luint16)s16Return] = s16Value;

						//do the timer if needed.
						#if C_LOCALDEF__LCCM662__ENABLE_TIMER_IN_DATA == 1U
							//timer index is based on global index, not related to the data type.
							sDAQ.sBuffers.u32Timer[u16Index][(Luint16)s16Return] = u32SIL3_DAQ__Get_SystemTimer();
						#endif
					}
					else
					{
						sDAQ.sStats.u32FIFO_S16FullCount++;
						//log the fault
					}
				}
				else
				{
					//big error
				}

				sDAQ.sInterlock.u8S16 = 0U;
			}
			else
			{
				//interlocking error
				sDAQ.sInterlock.u8S16 = 1U;
			}
		}
		else
		{
			//log the fault
		}
	}
	else
	{
		//streaming not enabled yet, fall on
	}
}
#endif

#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U16 > 0
/***************************************************************************//**
 * @brief
 * Append a U16 to the DAQ stream
 *
 * @param[in]		u16Value				The value to append
 * @param[in]		u16Index				The stream index
 * @st_funcMD5		A6A76FCED1933596F9C7E208C593C499
 * @st_funcID		LCCM662R0.FILE.004.FUNC.006
 */
void vSIL3_DAQ_APPEND__U16(Luint16 u16Index, Luint16 u16Value)
{
	Lint16 s16Return;
	Lint16 s16BuffIndex;

	if(sDAQ.u8StreamingOn == 1U)
	{
		//memory protection
		if(u16Index < M_DAQ__NUM_CHANNELS)
		{

			//check for an interlock
			if(sDAQ.sInterlock.u8U16 == 0U)
			{
				sDAQ.sInterlock.u8U16 = 1U;

				//get our index before we do too much more.
				s16BuffIndex = s16DAQ_APPEND__Index_to_Buffer_U16(u16Index);
				if(s16BuffIndex >= 0)
				{
					s16Return = s16SIL3_SOFTFIFO__Push(&sDAQ.sFIFO[u16Index]);
					if(s16Return >= 0)
					{
						//write the data in the slot.
						sDAQ.sBuffers.u16Buffer[(Luint16)s16BuffIndex][(Luint16)s16Return] = u16Value;

						//do the timer if needed.
						#if C_LOCALDEF__LCCM662__ENABLE_TIMER_IN_DATA == 1U
							//timer index is based on global index, not related to the data type.
							sDAQ.sBuffers.u32Timer[u16Index][(Luint16)s16Return] = u32SIL3_DAQ__Get_SystemTimer();
						#endif
					}
					else
					{
						sDAQ.sStats.u32FIFO_U16FullCount++;
						//log the fault
					}
				}
				else
				{
					//big error
				}

				sDAQ.sInterlock.u8U16 = 0U;
			}
			else
			{
				//interlocking error
				sDAQ.sInterlock.u8U16 = 1U;
			}
		}
		else
		{
			//log the fault
		}
	}
	else
	{
		//streaming not enabled yet, fall on
	}
}
#endif

#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S32 > 0
/***************************************************************************//**
 * @brief
 * Append a S32 to the DAQ stream
 *
 * @param[in]		s32Value				The value to append
 * @param[in]		u16Index				The stream index
 * @st_funcMD5		3FD889D7270CAE7FE41FD2888234C066
 * @st_funcID		LCCM662R0.FILE.004.FUNC.007
 */
void vSIL3_DAQ_APPEND__S32(Luint16 u16Index, Lint32 s32Value)
{
	Lint16 s16Return;
	Lint16 s16BuffIndex;

	if(sDAQ.u8StreamingOn == 1U)
	{
		//memory protection
		if(u16Index < M_DAQ__NUM_CHANNELS)
		{
			//check for an interlock
			if(sDAQ.sInterlock.u8S32 == 0U)
			{
				sDAQ.sInterlock.u8S32 = 1U;

				//get our index before we do too much more.
				s16BuffIndex = s16DAQ_APPEND__Index_to_Buffer_S32(u16Index);
				if(s16BuffIndex >= 0)
				{
					s16Return = s16SIL3_SOFTFIFO__Push(&sDAQ.sFIFO[u16Index]);
					if(s16Return >= 0)
					{
						//write the data in the slot.
						sDAQ.sBuffers.s32Buffer[(Luint16)s16BuffIndex][(Luint16)s16Return] = s32Value;

						//do the timer if needed.
						#if C_LOCALDEF__LCCM662__ENABLE_TIMER_IN_DATA == 1U
							//timer index is based on global index, not related to the data type.
							sDAQ.sBuffers.u32Timer[u16Index][(Luint16)s16Return] = u32SIL3_DAQ__Get_SystemTimer();
						#endif
					}
					else
					{
						sDAQ.sStats.u32FIFO_S32FullCount++;
						//log the fault
					}
				}
				else
				{
					//big error
				}

				sDAQ.sInterlock.u8S32 = 0U;
			}
			else
			{
				//interlocking error
				sDAQ.sInterlock.u8S32 = 1U;
			}
		}
		else
		{
			//log the fault
		}
	}
	else
	{
		//streaming not enabled yet, fall on
	}
}
#endif

#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U32 > 0
/***************************************************************************//**
 * @brief
 * Append a U32 to the DAQ stream
 *
 * @param[in]		u32Value				The value to append
 * @param[in]		u16Index				The stream index
 * @st_funcMD5		706404C1DD0AAB58FFB2666580FD09CB
 * @st_funcID		LCCM662R0.FILE.004.FUNC.008
 */
void vSIL3_DAQ_APPEND__U32(Luint16 u16Index, Luint32 u32Value)
{
	Lint16 s16Return;
	Lint16 s16BuffIndex;

	if(sDAQ.u8StreamingOn == 1U)
	{
		//memory protection
		if(u16Index < M_DAQ__NUM_CHANNELS)
		{

			//check for an interlock
			if(sDAQ.sInterlock.u8U32 == 0U)
			{
				sDAQ.sInterlock.u8U32 = 1U;

				//get our index before we do too much more.
				s16BuffIndex = s16DAQ_APPEND__Index_to_Buffer_U32(u16Index);
				if(s16BuffIndex >= 0)
				{
					s16Return = s16SIL3_SOFTFIFO__Push(&sDAQ.sFIFO[u16Index]);
					if(s16Return >= 0)
					{
						//write the data in the slot.
						sDAQ.sBuffers.u32Buffer[(Luint16)s16BuffIndex][(Luint16)s16Return] = u32Value;

						//do the timer if needed.
						#if C_LOCALDEF__LCCM662__ENABLE_TIMER_IN_DATA == 1U
							//timer index is based on global index, not related to the data type.
							sDAQ.sBuffers.u32Timer[u16Index][(Luint16)s16Return] = u32SIL3_DAQ__Get_SystemTimer();
						#endif
					}
					else
					{
						sDAQ.sStats.u32FIFO_U32FullCount++;
						//log the fault
					}
				}
				else
				{
					//big error
				}

				sDAQ.sInterlock.u8U32 = 0U;
			}
			else
			{
				//interlock error
				sDAQ.sInterlock.u8U32 = 1U;
			}
		}
		else
		{
			//log the fault
		}
	}
	else
	{
		//streaming not enabled yet, fall on
	}
}
#endif

#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__F32 > 0
/***************************************************************************//**
 * @brief
 * Append a F32 to the DAQ stream
 *
 * @param[in]		f32Value				The value to append
 * @param[in]		u16Index				The stream index
 * @st_funcMD5		2C29E8D0D08CB43F2784AC1F6E1C700C
 * @st_funcID		LCCM662R0.FILE.004.FUNC.009
 */
void vSIL3_DAQ_APPEND__F32(Luint16 u16Index, Lfloat32 f32Value)
{
	Lint16 s16Return;
	Lint16 s16BuffIndex;

	if(sDAQ.u8StreamingOn == 1U)
	{
		//memory protection
		if(u16Index < M_DAQ__NUM_CHANNELS)
		{
			if(sDAQ.sInterlock.u8F32 == 0U)
			{
				sDAQ.sInterlock.u8F32 = 1U;

				//get our index before we do too much more.
				s16BuffIndex = s16DAQ_APPEND__Index_to_Buffer_F32(u16Index);
				if(s16BuffIndex >= 0)
				{
					s16Return = s16SIL3_SOFTFIFO__Push(&sDAQ.sFIFO[u16Index]);
					if(s16Return >= 0)
					{
						//write the data in the slot.
						sDAQ.sBuffers.f32Buffer[(Luint16)s16BuffIndex][(Luint16)s16Return] = f32Value;

						//do the timer if needed.
						#if C_LOCALDEF__LCCM662__ENABLE_TIMER_IN_DATA == 1U
							//timer index is based on global index, not related to the data type.
							sDAQ.sBuffers.u32Timer[u16Index][(Luint16)s16Return] = u32SIL3_DAQ__Get_SystemTimer();
						#endif
					}
					else
					{
						sDAQ.sStats.u32FIFO_F32FullCount++;
						//log the fault
					}
				}
				else
				{
					//big error
				}

				sDAQ.sInterlock.u8F32 = 0U;
			}
			else
			{
				//interlocking error
				sDAQ.sInterlock.u8F32  = 1U;
			}
		}
		else
		{
			//log the fault
		}

	}
	else
	{
		//streaming not enabled yet, fall on
	}

}

#endif

/***************************************************************************//**
 * @brief
 * Convert a DAQ channel to a buffer index for U8
 * 
 * @param[in]		u16Index				The system wide channel index
 * @return			The UB buffer index or\n
 * 					-ve if we are out of range.
 * @st_funcMD5		45D77B4675F16DCFD7AF86C1E4B7EE2B
 * @st_funcID		LCCM662R0.FILE.004.FUNC.003
 */
Lint16 s16SIL3_DAQ_APPEND__Index_to_Buffer_U8(Luint16 u16Index)
{
	Lint16 s16Return;
	
	//in range?
	if(u16Index < C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U8)
	{
		//start with the current index;
		s16Return = (Lint16)u16Index;
	
		//minus the next highest buffer type
		s16Return -= (Lint16)M_DAQ__U8_OFFSET;
	}
	else
	{
	//fault
		s16Return = -1;
	}
	
	return s16Return;
}

/***************************************************************************//**
 * @brief
 * Get the S16 buffer index
 * 
 * @param[in]		u16Index		## Desc ##
 * @st_funcMD5		02BB1CA9D83EC9A566D9753486CE7DEF
 * @st_funcID		LCCM662R0.FILE.004.FUNC.010
 */
Lint16 s16DAQ_APPEND__Index_to_Buffer_S16(Luint16 u16Index)
{
	Lint16 s16Return;

	//in range?
	if(u16Index < M_DAQ__NUM_CHANNELS)
	{
		//start with the current index;
		s16Return = (Lint16)u16Index;

		//minus the next highest buffer type
		s16Return -= (Lint16)M_DAQ__S16_OFFSET;
	}
	else
	{
		//fault
		s16Return = -1;
	}

	return s16Return;
}

/***************************************************************************//**
 * @brief
 * Get the U16 buffer index
 * 
 * @param[in]		u16Index		## Desc ##
 * @st_funcMD5		AE5BFEBA5151BFDEFD9857D75756A91C
 * @st_funcID		LCCM662R0.FILE.004.FUNC.011
 */
Lint16 s16DAQ_APPEND__Index_to_Buffer_U16(Luint16 u16Index)
{
	Lint16 s16Return;

	//in range?
	if(u16Index < M_DAQ__NUM_CHANNELS)
	{
		//start with the current index;
		s16Return = (Lint16)u16Index;

		//minus the next highest buffer type
		s16Return -= (Lint16)M_DAQ__U16_OFFSET;
	}
	else
	{
		//fault
		s16Return = -1;
	}

	return s16Return;
}

/***************************************************************************//**
 * @brief
 * Get the S32 buffer index
 * 
 * @param[in]		u16Index		## Desc ##
 * @st_funcMD5		D8DBCA1C6A79406C5668797C7703B3B8
 * @st_funcID		LCCM662R0.FILE.004.FUNC.012
 */
Lint16 s16DAQ_APPEND__Index_to_Buffer_S32(Luint16 u16Index)
{
	Lint16 s16Return;

	//in range?
	if(u16Index < M_DAQ__NUM_CHANNELS)
	{
		//start with the current index;
		s16Return = (Lint16)u16Index;

		//minus the next highest buffer type
		s16Return -= (Lint16)M_DAQ__S32_OFFSET;
	}
	else
	{
		//fault
		s16Return = -1;
	}

	return s16Return;
}

/***************************************************************************//**
 * @brief
 * Get the U32 buffer index
 * 
 * @param[in]		u16Index		## Desc ##
 * @st_funcMD5		4DD4FF34FB03CD1FC2B0011953AEF7E6
 * @st_funcID		LCCM662R0.FILE.004.FUNC.013
 */
Lint16 s16DAQ_APPEND__Index_to_Buffer_U32(Luint16 u16Index)
{
	Lint16 s16Return;

	//in range?
	if(u16Index < M_DAQ__NUM_CHANNELS)
	{
		//start with the current index;
		s16Return = (Lint16)u16Index;

		//minus the next highest buffer type
		s16Return -= (Lint16)M_DAQ__U32_OFFSET;
	}
	else
	{
		//fault
		s16Return = -1;
	}

	return s16Return;
}


/***************************************************************************//**
 * @brief
 * Get the F32 buffer index
 * 
 * @param[in]		u16Index		## Desc ##
 * @st_funcMD5		42B757FB3C180CE2BA99E2EF84247EEF
 * @st_funcID		LCCM662R0.FILE.004.FUNC.014
 */
Lint16 s16DAQ_APPEND__Index_to_Buffer_F32(Luint16 u16Index)
{
	Lint16 s16Return;

	//in range?
	if(u16Index < M_DAQ__NUM_CHANNELS)
	{
		//start with the current index;
		s16Return = (Lint16)u16Index;

		//minus the next highest buffer type
		s16Return -= (Lint16)M_DAQ__F32_OFFSET;
	}
	else
	{
	//fault
		s16Return = -1;
	}

	return s16Return;
}

/***************************************************************************//**
 * @brief
 * Give a pointer to the buffer for any index.
 * 
 * @param[out]		*pu8Buffer				The return pointer to the start of the buffer
 * @param[in]		u16Index				The system wide index.
 * @st_funcMD5		BCDBEA80709DEE9EEF26ECCCBBE2FA8C
 * @st_funcID		LCCM662R0.FILE.004.FUNC.004
 */
Lint16 s16SIL3_DAQ_APPEND__Index_to_BufferPointer(Luint16 u16Index, Luint8 **pu8Buffer)
{
	Lint16 s16Return;
	Luint16 u16Temp;
	Lint16 s16Index;
	
	s16Return = 0;
	*pu8Buffer = 0;

	//do the cast
	s16Index = (Lint16)u16Index;

	//Todo, question mark over this one becase values could be zero.
	if(s16Index < M_DAQ__S16_OFFSET)
	{
		#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U8 > 0
		u16Temp = u16Index - M_DAQ__U8_OFFSET;
		*pu8Buffer = (Luint8*)&sDAQ.sBuffers.u8Buffer[u16Temp][0];
		#endif
	}
	else if (s16Index < M_DAQ__U16_OFFSET)
	{
		#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S16 > 0
		u16Temp = u16Index - M_DAQ__S16_OFFSET;
		*pu8Buffer = (Luint8*)&sDAQ.sBuffers.s16Buffer[u16Temp][0];
		#endif
	}
	else if (s16Index < M_DAQ__S32_OFFSET)
	{
		#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U16 > 0
		u16Temp = u16Index - M_DAQ__U16_OFFSET;
		*pu8Buffer = (Luint8*)&sDAQ.sBuffers.u16Buffer[u16Temp][0];
		#endif
	}
	else if (s16Index < M_DAQ__U32_OFFSET)
	{
		#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S32 > 0
		u16Temp = u16Index - M_DAQ__S32_OFFSET;
		*pu8Buffer = (Luint8*)&sDAQ.sBuffers.s32Buffer[u16Temp][0];
		#endif
	}
	else if (s16Index < M_DAQ__F32_OFFSET)
	{
		#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U32 > 0
		u16Temp = u16Index - M_DAQ__U32_OFFSET;
		*pu8Buffer = (Luint8*)&sDAQ.sBuffers.u32Buffer[u16Temp][0];
		#endif
	}
	else if (s16Index < M_DAQ__NUM_CHANNELS)
	{
		#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__F32 > 0
		u16Temp = u16Index - M_DAQ__F32_OFFSET;
		*pu8Buffer = (Luint8*)&sDAQ.sBuffers.f32Buffer[u16Temp][0];
		#endif
	}
	else
	{
		//error
		s16Return = -1;
	}


#if 0
	//in range?
	if(u16Index < C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U8)
	{
		//start with the current index;
		u16Temp = u16Index;
	
		//minus the next highest buffer type
		u16Temp -= M_DAQ__U8_OFFSET;
		
		//get our pointer;
		*pu8Buffer = (Luint8*)&sDAQ.sBuffers.u8Buffer[u16Temp][0];

	}
	else if(u16Index < M_DAQ__NUM_CHANNELS)
	{
		//start with the current index;
		u16Temp = u16Index;

		//minus the next highest buffer type
		u16Temp -= (M_DAQ__F32_OFFSET - 1);

		//get our pointer;
		*pu8Buffer = (Luint8*)&sDAQ.sBuffers.f32Buffer[u16Temp][0];

	}
	else
	{
		//fault
		s16Return = -1;
	}
#endif //
	
	return s16Return;

}


#endif //#if C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */


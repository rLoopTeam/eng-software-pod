/**
 * @file		DAQ.H
 * @brief		Main Header
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM662R0.FILE.001
 */


#ifndef _DAQ_H_
#define _DAQ_H_
	#include <localdef.h>
	#if C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE == 1U

		/*******************************************************************************
		Includes
		*******************************************************************************/
		#include <MULTICORE/LCCM357__MULTICORE__SOFTWARE_FIFO/software_fifo__public.h>
		#include <MULTICORE/LCCM284__MULTICORE__FAULT_TREE/fault_tree__public.h>
	
		/*******************************************************************************
		Defines
		*******************************************************************************/

		#define M_DAQ__U8_OFFSET		(0U)
		#define M_DAQ__S16_OFFSET		(C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U8)

		#define M_DAQ__U16_OFFSET		(C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U8 + \
										C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S16)

		#define M_DAQ__S32_OFFSET		(C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U8 + \
										C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S16 + \
										C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U16)

		#define M_DAQ__U32_OFFSET		(C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U8 + \
										C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S16 + \
										C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U16 + \
										C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S32)

		#define M_DAQ__F32_OFFSET		(C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U8 + \
										C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S16 + \
										C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U16 + \
										C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S32 + \
										C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U32)
		
		#define M_DAQ__NUM_CHANNELS 	(C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U8 + \
										C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S16 + \
										C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U16 + \
										C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S32 + \
										C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U32 + \
										C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__F32)
		
		/** Main DAQ States */
		typedef enum
		{
			/** Do nothing */
			DAQ_STATE__IDLE = 0U,
			
			/** Check the fill level */
			DAQ_STATE__CHECK_FILL,
			
			/** Process Fill */
			DAQ_STATE__PROCESS_FILL
		
		}E_DAQ__MAIN_STATES;
		
		
		/*******************************************************************************
		Structures
		*******************************************************************************/
		struct _strDAQ
		{
			/** These are the buffers to hold the FIFO data */
			struct
			{
				#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U8 > 0U
				Luint8 u8Buffer[C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U8][C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS * 4U];
				#endif
				#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S16 > 0U
				Lint16 s16Buffer[C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S16][C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS * 2U];
				#endif
				#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U16 > 0U
				Luint16 u16Buffer[C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U16][C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS * 2U];
				#endif
				#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S32 > 0U
				Lint32 s32Buffer[C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S32][C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS];
				#endif
				#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U32 > 0U
				Luint32 u32Buffer[C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U32][C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS];
				#endif
				#if C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__F32 > 0U
				Lfloat32 f32Buffer[C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__F32][C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS];
				#endif				
				
				#if C_LOCALDEF__LCCM662__ENABLE_TIMER_IN_DATA == 1U
				Luint32 u32Timer[M_DAQ__NUM_CHANNELS][C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS];
				#endif
				
			}sBuffers;

			/** Statistics Module */
			struct
			{
				Luint32 u32FIFO_U8FullCount;
				Luint32 u32FIFO_S16FullCount;
				Luint32 u32FIFO_U16FullCount;
				Luint32 u32FIFO_S32FullCount;
				Luint32 u32FIFO_U32FullCount;
				Luint32 u32FIFO_F32FullCount;

			}sStats;
		
			/** the software FIFO's*/
			SOFTWARE_FIFO__USER_T sFIFO[M_DAQ__NUM_CHANNELS];
		
			#if C_LOCALDEF__LCCM662__ENABLE_USER_PAYLOAD_TYPES == 1U
				/** user configurable packet type for transmission purposes */
				Luint16 u16User_PacketType[M_DAQ__NUM_CHANNELS];
			#endif

			/** DAQ state machine */
			E_DAQ__MAIN_STATES eMainState;
			
			/** Watermark Fill Flag */
			Luint8 u8WatermarkFlag[M_DAQ__NUM_CHANNELS];

			/** Force a flush */
			Luint8 u8ForceFlushFlag[M_DAQ__NUM_CHANNELS];
		
			/** Watermark Fill Level */
			Luint16 u16WatermarkLevel[M_DAQ__NUM_CHANNELS];

			/** The size multiplier */
			Luint8 u8SizeMultiplier[M_DAQ__NUM_CHANNELS];

			/** Process fill check point */
			Luint16 u16ProcessPoint;

			/** Are we streaming, and if so can we append safely?*/
			Luint8 u8StreamingOn;

			/** For Interlocking Append functions 
			 * Not really needed other than for WIN32 simulations
			 * where multiple threads are writing at the same time and we
			 * want to detect these sorts of issues.*/
			struct
			{
				Luint8 u8U8;
				Luint8 u8S16;
				Luint8 u8U16;
				Luint8 u8S32;
				Luint8 u8U32;
				Luint8 u8F32;
			}sInterlock;

			#ifdef WIN32
			struct
			{
				/** Signal a new packet */
				Luint8 u8NewPacket[10];
				Luint16 u16LastPacketType[10];
				Luint8 u8LastArray[10][1500];
			}sWIN32;
			#endif
		
		};

		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		void vDAQ__Init(void);
		void vDAQ__Process(void);
		void vDAQ__ForceFlush(void);
		Luint32 u32DAQ__Get_SystemTimer(void);
		DLL_DECLARATION Luint16 u16DAQ__Get_FIFO_Level(Luint16 u16Index);
		DLL_DECLARATION Luint16 u16DAQ__Get_FIFO_Max(Luint16 u16Index);
		void vDAQ__Config_UserPacketType(Luint16 u16Index, Luint16 u16Type);
		void vDAQ__Streaming_On(void);
		void vDAQ__Streaming_Off(void);

		//append
		void vDAQ_APPEND__Init(void);
		void vDAQ_APPEND__Process(void);
		DLL_DECLARATION void vDAQ_APPEND__U8(Luint16 u16Index, Luint8 u8Value);
		DLL_DECLARATION void vDAQ_APPEND__S16(Luint16 u16Index, Lint16 s16Value);
		DLL_DECLARATION void vDAQ_APPEND__U16(Luint16 u16Index, Luint16 u16Value);
		DLL_DECLARATION void vDAQ_APPEND__S32(Luint16 u16Index, Lint32 s32Value);
		DLL_DECLARATION void vDAQ_APPEND__U32(Luint16 u16Index, Luint32 u32Value);
		DLL_DECLARATION void vDAQ_APPEND__F32(Luint16 u16Index, Lfloat32 f32Value);
		Lint16 s16DAQ_APPEND__Index_to_BufferPointer(Luint16 u16Index, Luint8 **pu8Buffer);
		
		#ifdef WIN32
			Lint16 s16DAQ_WIN32__TxHandler(Luint16 u16Index, Luint8 *pu8Buffer, Luint16 u16Length);
		#endif

		//template, user should implement their own
		Lint16 s16DAQ_TRANSMIT__Template(Luint16 u16Index, Luint8 *pu8BufferPointer, Luint16 u16LengthBytes);


		#if C_LOCALDEF__LCCM662__ENABLE_TEST_SPEC == 1U
			DLL_DECLARATION void vLCCM662R0_TS_000(void);
		#endif

	#endif //#if C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_DAQ_H_


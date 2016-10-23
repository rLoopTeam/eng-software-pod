/**
 * @file		rm4_dma.h
 * @brief		DMA header File
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM229R0.FILE.002
 */

#ifndef _RM4_DMA_H_
#define _RM4_DMA_H_

	/*lint -e537*/
	#include <localdef.h>
	#ifndef C_LOCALDEF__LCCM229__ENABLE_THIS_MODULE
		#error
	#endif
	#if C_LOCALDEF__LCCM229__ENABLE_THIS_MODULE == 1U

		#include <RM4/LCCM229__RM4__DMA/rm4_dma__private.h>
		#include <RM4/LCCM229__RM4__DMA/rm4_dma__request_types.h>

		/** Main DMA Structure */
		struct _strRM4DMA
		{
			/** Holds details about each channel */
			struct
			{
				/** Is the eChannel busy */
				Luint8 u8Busy;

			}sChannel[C_RM4_DMA__MAX_CHANNELS];


		};



		//function protos
		void vRM4_DMA__Init(void);
		void vRM4_DMA__Enable(void);
		void vRM4_DMA__Disable(void);
		void vRM4_DMA__Set_ControlPacket(RM4_DMA__CHANNEL_E eChannel, RM4_DMA__CONTROL_T g_dmaCTRLPKT);
		Luint32 u32RM4_DMA__Config_ControlPacket(RM4_DMA__CONTROL_T * g_dmaCTRLPKT, Luint32 u32SourceAddx,Luint32 u32DestAddx, Luint32 u32TransferSize);
		void vRM4_DMA__Set_ChannelEnable(RM4_DMA__CHANNEL_E eChannel,RM4_DMA__REQUEST_TYPE_T type);
		void vRM4_DMA__RequestAssign(RM4_DMA__CHANNEL_E eChannel, RM4_DMA__HW_REQUEST_TYPE__T eRequestLine);
		Luint32 u32RM4_DMA__Get_Request(RM4_DMA__CHANNEL_E eChannel);
		void vRM4_DMA__Set_Priority(RM4_DMA__CHANNEL_E eChannel, RM4_DMA__PRIORITY_T priority);
		void vRM4_DMA__EnableInterrupt(RM4_DMA__CHANNEL_E eChannel, RM4_DMA__INTERRUPT_T eInterruptType);
		void vRM4_DMA__DisableInterrupt(RM4_DMA__CHANNEL_E eChannel, RM4_DMA__INTERRUPT_T eInterruptType);
		void vRM4_DMA__DefineRegion(RM4_DMA__REGION_T eRegion, Luint32 u32StartAddx, Luint32 u32EndAddx);
		void vRM4_DMA__EnableRegion(RM4_DMA__REGION_T eRegion, RM4_DMA__REGION_ACCESS_T access, Luint8 intenable);
		void vRM4_DMA__DisableRegion(RM4_DMA__REGION_T eRegion);
		void vRM4_DMA__EnableParityCheck(void);
		void vRM4_DMA__DisableParityCheck(void);
		void vRM4_DMA__Set_ChannelBusy(RM4_DMA__CHANNEL_E eChannel);
		void vRM4_DMA__Clear_ChannelBusy(RM4_DMA__CHANNEL_E eChannel);
		Luint8 u8RM4_DMA__IsChannelBusy(RM4_DMA__CHANNEL_E eChannel);

		//interrupts.c
		void vRM4_DMA_ISR__BTCAInterrupt(void);
		void vRM4_DMA_ISR__HBCAInterrupt(void);
		void vRM4_DMA_ISR__LFSAInterrupt(void);
		void vRM4_DMA_ISR__FTCAInterrupt(void);

		//suspend
		void vRM4_DMA__Suspend(RM4_DMA__CHANNEL_E eChannel);
		void vRM4_DMA__Resume(RM4_DMA__CHANNEL_E eChannel);

		//notifications.c
		void vRM4_DMA__Notification(RM4_DMA__INTERRUPT_T eInterruptType, Luint8 u8Channel);

		//testing
		#if C_LOCALDEF__LCCM229__ENABLE_TEST_SPEC == 1U
			void vLCCM229_TS_001(void);
			void vLCCM229_TS_002(void);
			void vLCCM229_TS_003(void);
			void vLCCM229_TS_004(void);
			void vLCCM229_TS_005(void);
			void vLCCM229_TS_006(void);
			void vLCCM229_TS_007(void);
			void vLCCM229_TS_008(void);
			void vLCCM229_TS_009(void);
			void vLCCM229_TS_010(void);
			void vLCCM229_TS_011(void);
			void vLCCM229_TS_012(void);
			void vLCCM229_TS_013(void);
			void vLCCM229_TS_014(void);
			void vLCCM229_TS_015(void);
			void vLCCM229_TS_016(void);
			void vLCCM229_TS_017(void);
			void vLCCM229_TS_018(void);
			void vLCCM229_TS_019(void);
			void vLCCM229_TS_020(void);
			void vLCCM229_TS_021(void);
			void vLCCM229_TS_022(void);
			void vLCCM229_TS_023(void);
			void vLCCM229_TS_024(void);
			void vLCCM229_TS_025(void);
			void vLCCM229_TS_026(void);
			void vLCCM229_TS_027(void);
			void vLCCM229_TS_028(void);
			void vLCCM229_TS_029(void);
			void vLCCM229_TS_030(void);
		#endif
		
		#ifndef C_LOCALDEF__LCCM229__ENABLE_TEST_SPEC
			#error
		#endif
			
	#endif //C_LOCALDEF__LCCM229__ENABLE_THIS_MODULE
#endif //

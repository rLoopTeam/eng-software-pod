/**
 * @file		rm4_emac.h
 * @brief		EMAC main header file
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM254R0.FILE.002
 */

#ifndef _RM4_EMAC_H_
#define _RM4_EMAC_H_

	#include <localdef.h>
	#ifndef C_LOCALDEF__LCCM254__ENABLE_THIS_MODULE
		#error
	#endif
	#if C_LOCALDEF__LCCM254__ENABLE_THIS_MODULE == 1U

		#include "rm4_emac__private.h"
		#include "rm4_emac__dp83640_private.h"
		#include "rm4_emac__bd_private.h"

		/** The possible link states */
		typedef enum
		{

			/** we are idle / POR */
			LINK_STATE__IDLE,

			LINK_STATE__INIT_EMAC,

			LINK_STATE__INIT_MDIO,

			LINK_STATE__CHECK_PHY_ALIVE,

			LINK_STATE__CHECK_PHY_ALIVE_1,

			LINK_STATE__ENAB_RX_BROADCAST,

			LINK_STATE__SET_MAC_ADDX,

			LINK_STATE__GET_PHY_ID,

			LINK_STATE__GET_ALIVE_STATUS,

			LINK_STATE__LINK_PRE,

			LINK_STATE__LINK_SETUP_1,

			LINK_STATE__LINK_SETUP_2,

			LINK_STATE__BLOCK_DESC_INIT,

			LINK_STATE__INTERRUPTS_INIT,

			LINK_STATE__INTERRUPTS_INIT_2,

			LINK_STATE__CABLE_CHECK,

			LINK_STATE__GRAT_ARP,

			LINK_STATE__LLDP,

			LINK_STATE__RUN

		}RM4_EMAC__LINK_STATE_T;


		/*****************************************************************************
		 * Helper struct to hold private data used to operate the ethernet interface.
		*****************************************************************************/
		struct RM4_EMAC_IF
		{

			//the state machine used to get our link up and running.
			RM4_EMAC__LINK_STATE_T eLinkState;

			Luint8 u8MACAddx[6];
			Luint8 u8IPAddx[4];

			//The tx/rx channels for the interface
			struct RM4_EMAC__TX_CHANNEL_T pEMAC_Tx_Channel;
			struct RM4_EMAC__RX_CHANNEL_T pEMAC_Rx_Channel;

			
			//the transmit stack object
			/*****************************************************************************
			*****************************************************************************/
			struct
			{

				//the current stack position
				Luint8 u8StackPos;

			}sTxStack;


			/** Stats about the link */
			struct
			{
				Luint8 u8CableLength;
				Luint8 u8PairsSwapped;
				Luint8 u8PolarityInvert;

			}sStats;



		};

		/*****************************************************************************/
		/*
		** Macros which can be used as speed parameter to the API vRM4_EMAC__Set_RMII_Speed
		*/
		#define EMAC_RMIISPEED_10MBPS				 (0x00000000U)
		#define EMAC_RMIISPEED_100MBPS				(0x00008000U)

		/*
		** Macros which can be used as duplexMode parameter to the API
		** vRM4_EMAC__Set_Duplex
		*/
		#define EMAC_DUPLEX_FULL					 (0x00000001U)
		#define EMAC_DUPLEX_HALF					 (0x00000000U)

		/*
		** Macros which can be used as u32MatchFilter parameters to the API
		** vRM4_EMAC__Set_MACAddx
		*/
		/* Address not used to match/filter incoming packets */
		#define EMAC_MACADDR_NO_MATCH_NO_FILTER	 (0x00000000U)

		/* Address will be used to filter incoming packets */
		#define EMAC_MACADDR_FILTER				 (0x00100000U)

		/* Address will be used to match incoming packets */
		#define EMAC_MACADDR_MATCH					(0x00180000U)

		/*
		** Macros which can be passed as u32EOIFlag to vRM4_EMAC__RxIntAckToClear API
		*/
		#define EMAC_INT_CORE0_RX					 (0x1U)
		#define EMAC_INT_CORE1_RX					 (0x5U)
		#define EMAC_INT_CORE2_RX					 (0x9U)

		/*
		** Macros which can be passed as u32EOIFlag to EMACTxIntAckToClear API
		*/
		#define EMAC_INT_CORE0_TX					 (0x2U)
		#define EMAC_INT_CORE1_TX					 (0x6U)
		#define EMAC_INT_CORE2_TX					 (0xAU)

		/*****************************************************************************/
		/**
		* The EMAC controls the flow of packet data from the system to the PHY. The MDIO module controls PHY
		* configuration and status monitoring.
		*
		* Both the EMAC and the MDIO modules interface to the system core through a custom interface that
		* allows efficient data transmission and reception. This custom interface is referred to as the EMAC control
		* module and is considered integral to the EMAC/MDIO peripheral
		*
		*	Related Files
		* - emac.h
		* - emac.c
		* - hw_emac.h
		* - hw_emac_ctrl.h
		* - hw_mdio.h
		* - hw_reg_access.h
		* - mdio.h
		* - mdio.c
		*/
		/*
		** Prototypes for the APIs
		*/
		//user to call
		void vRM4_EMAC_LINK__Init(Luint8 *pu8MAC, Luint8 *pu8IP);
		void vRM4_EMAC_LINK__Set_State(RM4_EMAC__LINK_STATE_T eState);
		void vRM4_EMAC_LINK__Process(void);
		Luint8 u8RM4_EMAC_LINK__Is_LinkUp(void);


		//Rx
		void vRM4_EMAC_RX__RxIntHandler(void);

		//Tx
		void vRM4_EMAC_TX__Tx_IntHandler(void);


		Lint16 s16RM4_EMAC_LINK__Link_Setup(void);
		Lint16 s16RM4_EMAC_LINK__Link_Setup_AsyncStart(void);
		Lint16 s16RM4_EMAC_LINK__Link_Setup_AsyncCheck(void);

		void vRM4_EMAC__Init(void);

		void vRM4_EMAC__TxHdrDescPtrWrite(Luint32 u32DescriptorHeader, Luint32 u32Channel);
		void vRM4_EMAC__RxHdrDescPtrWrite(Luint32 u32DescriptorHeader, Luint32 u32Channel);
		void vRM4_EMAC__Write_TxChannelCompletionPointer(Luint32 u32Channel, Luint32 u32CompletionPointer);
		void vRM4_EMAC__Write_RxChannelCompletionPointer(Luint32 u32Channel, Luint32 u32CompletionPointer);

		void vRM4_EMAC__Set_MACSrcAddx(Luint8 *pu8MACAddx);
		void vRM4_EMAC__Set_MACAddx(Luint32 u32Channel, Luint8 *pu8MACAddx, Luint32 u32MatchFilter);
		void vRM4_EMAC__Enable_RxUnicast_OnChannel(Luint32 u32Channel);
		void vRM4_EMAC__Enable_RxBroadcast_OnChannel(Luint32 u32Channel);
		void vRM4_EMAC__Enable_RxPromiscous_OnChannel(Luint32 u32Channel);
		void vRM4_EMAC__Set_NumFreeRxBuffers(Luint32 u32Channel, Luint32 u32NumBuffers);
		Luint32 u32RM4_EMAC__Get_IntVector(void);
		void vRM4_EMAC__Set_Duplex(Luint32 u32DuplexMode);
		void vRM4_EMAC__Set_MACSrcAddx(Luint8 *pu8MACAddx);
		void vRM4_EMAC__Set_NumFreeRxBuffers(Luint32 u32Channel, Luint32 u32NumBuffers);
		void vRM4_EMAC__Enable_Tx(void);
		void vRM4_EMAC__Enable_Rx(void);
		void vRM4_EMAC__Enable_MII(void);
		void vRM4_EMAC__Set_RMII_Speed10Mb(void);
		void vRM4_EMAC__Set_RMII_Speed100Mb(void);

		void vRM4_EMAC_RESET__Soft_Reset(void);

		Lint16 s16RM4_EMAC_MDIO__Init(Luint32 mdioInputFreq, Luint32 mdioOutputFreq);
		Luint32 u32RM4_EMAC_MDIO__Get_ModuleRevisionID(void);
		Luint32 u32RM4_EMAC_MDIO__Get_AliveStatus(void);
		Luint32 u32RM4_EMAC_MDIO__Get_LinkStatus(void);
		Lint16 s16RM4_EMAC_MDIO__Read_Register(Luint32 u32RegisterNum, Luint16 *pu16Data);
		void vRM4_EMAC_MDIO__Write_Register(Luint32 u32RegisterNum, Luint16 RegVal);




		//buffer descriptors
		void vRM4_EMAC_BD__Init(void);
		Luint32 u32RM4_EMAC_BD__Get_TxBufferPointer(Luint8 u8BufferIndex);
		void vRM4_EMAC_BD__Set_Length(Luint8 u8BufferIndex, Luint16 u16Length);

		//interrupts
		void vRM4_EMAC_INT__TxISR(void);
		void vRM4_EMAC_INT__RxISR(void);
		void vRM4_EMAC_INT__Enable_TxIntPulse(Luint32 u32ControlCore, Luint32 u32Channel);
		void vRM4_EMAC_INT__Disable_TxIntPulse(Luint32 u32ControlCore, Luint32 u32Channel);
		void vRM4_EMAC_INT__Enable_RxIntPulse(Luint32 u32ControlCore, Luint32 u32Channel);
		void vRM4_EMAC_INT__Disable_RxIntPulse(Luint32 u32ControlCore, Luint32 u32Channel);
		void vRM4_EMAC_INT__CoreIntAck(Luint32 u32EOIFlag);

		//win32
#ifdef WIN32
		typedef void (__cdecl *pCallback_TxPacket__FuncType)(Luint16 u16Length, Luint8 *u8Buffer);
		DLL_DECLARATION void vRM4_EMAC_WIN32__PacketWrite(Luint16 u16PacketLength, Luint8 *pu8Data);
		DLL_DECLARATION void vRM4_EMAC_WIN32__TxPacket_SetCallback(pCallback_TxPacket__FuncType pFunc);
		void vRM4_EMAC_WIN32__TxPacket(Luint16 u16PacketLength, Luint8 *pu8Data);
#endif

		//pin testing
		#if C_LOCALDEF__LCCM254__ENABLE_IO_PIN_TESTING == 1U
			void vRM4_EMAC_PINS__Test(void);
		#endif

	#endif //C_LOCALDEF__LCCM254__ENABLE_THIS_MODULE

#endif //

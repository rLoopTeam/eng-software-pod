/**
 * @file		rm4_sci.h
 * @brief		SCI Header file
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM282R0.FILE.002
 */

 
#ifndef _RM4_SCI_H__
#define _RM4_SCI_H__

	/*lint -e537*/
	#include <localdef.h>
	#if C_LOCALDEF__LCCM282__ENABLE_THIS_MODULE == 1U

	/*****************************************************************************
	Includes
	*****************************************************************************/
	#include <RM4/LCCM282__RM4__SCI/rm4_sci__private.h>

	#if C_LOCALDEF__LCCM282__ENABLE_DMA == 1U
		#include <RM4/LCCM229__RM4__DMA/rm4_dma__private.h>
	#endif

	//There are two SCI channels, one is SCI1 (wich uses the SCI Pins) and the
	//other is SCI2 which shares the LIN pins
	typedef enum
	{
		#if C_LOCALDEF__LCCM282__ENABLE_SCI_1 == 1U
			SCI_CHANNEL__1 = 0U,
		#endif

		#if C_LOCALDEF__LCCM282__ENABLE_SCI_2 == 1U
			SCI_CHANNEL__2 = 1U
		#endif

	}RM4_SCI__CHANNEL_T;

	typedef enum
	{
	    SCI_LOOPBACK__DIGITAL = 0U,
	    SCI_LOOPBACK__ANALOG = 1U
	}RM4_SCI__LOOPBACK_T;

	/*****************************************************************************
	*****************************************************************************/
	typedef struct /*g_sciTransfer*/
	{
		Luint32   u32Mode;         /* Used to check for TX interrupt Enable */
		Luint32   u32TxLength;    /* Transmit data length in number of Bytes */
		Luint32   u32RxLength;    /* Receive data length in number of Bytes */
		Luint8    * pu8TxData;    /* Transmit data pointer */
		Luint8    * pu8RxData;    /* Receive data pointer */

	}RM4_SCI__TX_T;

	//Used with vRM4_SCI_INT__Enable_Notification, vRM4_SCI_INT__Disable_Notification
	typedef enum
	{
		SCI_FE_INT    = 0x04000000U,  /* framming error */
		SCI_OE_INT    = 0x02000000U,  /* overrun error */
		SCI_PE_INT    = 0x01000000U,  /* parity error */
		SCI_RX_INT    = 0x00000200U,  /* receive buffer ready */
		SCI_TX_INT    = 0x00000100U,  /* transmit buffer ready */
		SCI_WAKE_INT  = 0x00000002U,  /* wakeup */
		SCI_BREAK_INT = 0x00000001U   /* break detect */
	}RM4_SCI__INTERRUPT_FLAGS_T;


	/** Pin select types */
	enum sciPinSelect
	{
		PIN_SCI_TX = 0U,
		PIN_SCI_RX = 1U
	};

	/** Main Structure for SCI */
	struct _strRM4SCI
	{

		#if C_LOCALDEF__LCCM282__ENABLE_DMA == 1U
			struct
			{
				//dma control packet
				RM4_DMA__CONTROL_T pDMAControl;

			}sDMA[2];
		#else
			Luint8 u8Dummy;
		#endif


	};


	/*****************************************************************************
	Function Prototypes
	*****************************************************************************/
	void vRM4_SCI__Init(RM4_SCI__CHANNEL_T eChannel);
	void vRM4_SCI__Set_Baudrate(RM4_SCI__CHANNEL_T eChannel, Luint32 baud);

	void vRM4_SCI__Set_PortFunctional(RM4_SCI__CHANNEL_T eChannel, Luint32 u32Port);
	Luint32 u32RM4_SCI__Is_TxReady(RM4_SCI__CHANNEL_T eChannel);
	void vRM4_SCI__TxByte(RM4_SCI__CHANNEL_T eChannel, Luint8 byte);
	void vRM4_SCI__TxByteArray(RM4_SCI__CHANNEL_T eChannel, Luint32 u32Length, Luint8 *pu8Data);
	Luint32 u32RM4_SCI__Is__RxReady(RM4_SCI__CHANNEL_T eChannel);
	Luint32 u32RM4_SCI__Get__RxErrorFlags(RM4_SCI__CHANNEL_T eChannel);
	Luint8 u8RM4_SCI__RxByte(RM4_SCI__CHANNEL_T eChannel);
	void u8RM4_SCI__RxByteArray(RM4_SCI__CHANNEL_T eChannel, Luint32 u32Length, Luint8 *pu8Data);
	Luint8 u8RM4_SCI__Get_Rx_Value(RM4_SCI__CHANNEL_T eChannel);
	Luint8 u8RM4_SCI__IsIdle(RM4_SCI__CHANNEL_T eChannel);

	//loopback
	void vRM4_SCI_LOOPBACK__Enable(RM4_SCI__CHANNEL_T eChannel, RM4_SCI__LOOPBACK_T eLoopback);
	void vRM4_SCI_LOOPBACK__Disable(RM4_SCI__CHANNEL_T eChannel);

	//DMA
	#if C_LOCALDEF__LCCM282__ENABLE_DMA == 1U
		void vRM4_SCI_DMA__Init(void);
		void vRM4_SCI_DMA__Begin_Tx(RM4_SCI__CHANNEL_T eChannel, Luint8 *pu8SourceBuffer, Luint32 u32Length);
		Luint8 u8RM4_SCI_DMA__Is_TxBusy(RM4_SCI__CHANNEL_T eChannel);
		void vRM4_SCI_DMA__Cleanup(RM4_SCI__CHANNEL_T eChannel);
	#endif

	//interrupts
	#if C_LOCALDEF__LCCM282__ENABLE_INTERRUPTS == 1U
		void vRM4_SCI_INT__Enable_Notification(RM4_SCI__CHANNEL_T eChannel, RM4_SCI__INTERRUPT_FLAGS_T eFlags);
		void vRM4_SCI_INT__Disable_Notification(RM4_SCI__CHANNEL_T eChannel, RM4_SCI__INTERRUPT_FLAGS_T eFlags);

		/* This is a callback that is provided by the application and is called apon
		* an interrupt.  The parameter passed to the callback is a copy of the
		* interrupt flag register.
		*/
		void vRM4_SCI_INT__Notification(RM4_SCI__CHANNEL_T eChannel, RM4_SCI__INTERRUPT_FLAGS_T eFlags);

		//interrupts called by VIM
		void vRM4_SCI_ISR__LowLevel(void);
		void vRM4_SCILIN_ISR__LowLevel(void);
		void vRM4_SCI_ISR__HighLevel(void);
		void vRM4_SCILIN_ISR__HighLevel(void);
	#endif


	void vRM4_SCI__Init_Transfer(Luint32 u32Index, Luint32 u32Mode, Luint32 u32Length);
	Luint32 u32RM4_SCI_INT__Get_TransferMode(Luint32 u32Index);
	void vRM4_SCI_INT__Set_TransferMode(Luint32 u32Index, Luint32 u32Mode);
	void vRM4_SCI_INT__Set_TransferLength(Luint32 u32Index, Luint32 u32Length);
	void vRM4_SCI_INT__Set_TransferData(Luint32 u32Index, Luint8 *pu8Data);
	Luint8 * pu8RM4_SCI_INT__Get_TransferData(Luint32 u32Index);

	//helpers
	void vRM4_SCI_HELPERS__DisplayText(RM4_SCI__CHANNEL_T eChannel, const Luint8 *cpu8Text, Luint32 u32Length);
	#endif //C_LOCALDEF__LCCM282__ENABLE_THIS_MODULE
	
	#ifndef C_LOCALDEF__LCCM282__ENABLE_THIS_MODULE
		#error
	#endif

	
#endif

/**
 * @file		SC16__LOCALDEF.H
 * @brief		Main Localdef File
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 *				of companies, including Lockie Innovation Pty. Ltd (ACN 123 529 064) and
 *				Lockie Safety Systems Pty. Ltd (ACN 132 340 571).  This code may be distributed
 *				under a license from the Lockie Group of companies, and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright Lockie Innovation Pty Ltd 2003-2012, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2012, All Rights Reserved.
 * @st_fileID	LCCM487R0.FILE.004
 */

#if 0

/*******************************************************************************
SC16IS741 - UART TO SPI MODULE
*******************************************************************************/
	#define C_LOCALDEF__LCCM487__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM487__ENABLE_THIS_MODULE == 1U

		//architecture
		#define C_LOCALDEF__LCCM487__USE_ON_RM4								(1U)
		#define C_LOCALDEF__LCCM487__USE_ON_MSP430							(0U)
	
		//configure the number of devices in the system
		#define C_LOCALDEF__LCCM487__NUM_DEVICES							(1U)

		/** If we have multiple devices we can choose to have a common hardware
		reset line */
		#define C_LOCALDEF__LCCM487__HAVE_COMMON_HW_RESET					(1U)
	
	
		#if C_LOCALDEF__LCCM487__HAVE_COMMON_HW_RESET == 0U
			#define M_LOCALDEF__LCCM487__HW_RESET__TRIS(index)				{ \
																			if(index == 0U)	vRM4_N2HET_PINS__Set_PinDirection_Output(N2HET_CHANNEL__1 , 1U);\
																			else if (index == 1U) vRM4_N2HET_PINS__Set_PinDirection_Output(N2HET_CHANNEL__1 , 2U);\
																			else if (index == 2U) vRM4_N2HET_PINS__Set_PinDirection_Output(N2HET_CHANNEL__1 , 3U); }
		#else
			#define M_LOCALDEF__LCCM487__HW_RESET__TRIS()					{vRM4_N2HET_PINS__Set_PinDirection_Output(N2HET_CHANNEL__1 , 3U);}
		#endif

		#if C_LOCALDEF__LCCM487__HAVE_COMMON_HW_RESET == 0U
			#define M_LOCALDEF__LCCM487__HW_RESET__LATCH(index,value)		{ \
																			if(index == 0U)	vRM4_N2HET_PINS__Set_Pin(N2HET_CHANNEL__1 , 1U, value);\
																			else if(index == 1U) vRM4_N2HET_PINS__Set_Pin(N2HET_CHANNEL__1 , 2U, value);\
																			else if(index == 2U) vRM4_N2HET_PINS__Set_Pin(N2HET_CHANNEL__1 , 3U, value); }
		#else
			#define M_LOCALDEF__LCCM487__HW_RESET__LATCH(value)				{vRM4_N2HET_PINS__Set_Pin(N2HET_CHANNEL__1 , 3U, value);}
		#endif

		#define M_LOCALDEF__LCCM487__HW_CHIPSELECT__TRIS(index) 			{\
																			if(index == 0U)	vRM4_MIBSPI135_PINS__Set_OutputDirection(MIBSPI135_CHANNEL__3, MIBSPI135_PIN__CS0);\
																			else if(index == 1U) vRM4_MIBSPI135_PINS__Set_OutputDirection(MIBSPI135_CHANNEL__5, MIBSPI135_PIN__CS3);\
																			else if(index == 2U) vRM4_MIBSPI135_PINS__Set_OutputDirection(MIBSPI135_CHANNEL__3, MIBSPI135_PIN__ENA); }

		#define M_LOCALDEF__LCCM487__HW_CHIPSELECT__LATCH(index,value) 		{\
																			if(index == 0U)	vRM4_MIBSPI135_PINS__Set(MIBSPI135_CHANNEL__3, MIBSPI135_PIN__CS0, value);\
																			else if(index == 1U) vRM4_MIBSPI135_PINS__Set(MIBSPI135_CHANNEL__5, MIBSPI135_PIN__CS3, value);\
																			else if(index == 2U) vRM4_MIBSPI135_PINS__Set(MIBSPI135_CHANNEL__3, MIBSPI135_PIN__ENA, value); }

		#define M_LOCALDEF__LCCM487__HW_INTERUPTPIN__TRIS(index) 			{ \
																			if(index == 0U) vRM4_GIO__Set_BitDirection(gioPORTA, 2, GIO_DIRECTION__INPUT); \
																			else if(index == 1U) vRM4_GIO__Set_BitDirection(gioPORTA, 3, GIO_DIRECTION__INPUT); \
																			else if(index == 2U) vRM4_GIO__Set_BitDirection(gioPORTA, 4, GIO_DIRECTION__INPUT); }


		//SPI Interface
		#define M_LOCALDEF__LCCM487__SPI__TX_U8(u8Value)					u8RM4_MIBSPI135__Tx_U8(MIBSPI135_CHANNEL__1, MIBSPI135_DATA_FORMAT__0, MIBSPI135_CS__NONE, u8Value)
																			
		//testing
		#define C_LOCALDEF__LCCM487__ENABLE_TEST_SPEC							(1U)

		
		//main include file
		#include <MULTICORE/LCCM487__MULTICORE__SC16IS741/sc16.h>
	#endif //#if C_LOCALDEF__LCCM487__ENABLE_THIS_MODULE == 1U


#endif //#ifdef DOXYGEN_ENABLED


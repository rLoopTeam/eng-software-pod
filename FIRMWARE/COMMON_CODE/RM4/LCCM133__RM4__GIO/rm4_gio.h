/**
 * @file		rm4_gio.h
 * @brief		GIO main header file
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM133R0.FILE.002
 */


#ifndef _RM4_GIO_H_
#define _RM4_GIO_H_

	#include <localdef.h>

	#ifndef C_LOCALDEF__LCCM133__ENABLE_THIS_MODULE
		#error
	#endif
	#if C_LOCALDEF__LCCM133__ENABLE_THIS_MODULE == 1U

		#include <RM4/LCCM133__RM4__GIO/rm4_gio__private.h>


		//when handlign the interrupts, GIO interrupt bits are
		//all in the same register
		/*****************************************************************************
		*****************************************************************************/
		typedef enum
		{
			GIO_ISR_PIN__GIOA_0	= 0U,
			GIO_ISR_PIN__GIOA_1	= 1U,
			GIO_ISR_PIN__GIOA_2	= 2U,
			GIO_ISR_PIN__GIOA_3	= 3U,
			GIO_ISR_PIN__GIOA_4	= 4U,
			GIO_ISR_PIN__GIOA_5	= 5U,
			GIO_ISR_PIN__GIOA_6	= 6U,
			GIO_ISR_PIN__GIOA_7	= 7U,

			GIO_ISR_PIN__GIOB_0	= 8U,
			GIO_ISR_PIN__GIOB_1	= 9U,
			GIO_ISR_PIN__GIOB_2	= 10U,
			GIO_ISR_PIN__GIOB_3	= 11U,
			GIO_ISR_PIN__GIOB_4	= 12U,
			GIO_ISR_PIN__GIOB_5	= 13U,
			GIO_ISR_PIN__GIOB_6	= 14U,
			GIO_ISR_PIN__GIOB_7	= 15U


		}RM4_GIO__INTERRUPT_PIN_T;


		//the port direction
		/*****************************************************************************
		*****************************************************************************/
		typedef enum eRM4_GIO__PORT_DIRECTION
		{
			GIO_DIRECTION__INPUT = 0U,
			GIO_DIRECTION__OUTPUT = 1U

		}RM4_GIO__PORT_DIRECTION_T;

		//isr polarity types
		/*****************************************************************************
		*****************************************************************************/
		typedef enum
		{
			GIO_POLARITY__FALLING = 0U,
			GIO_POLARITY__RISING = 1U,
			GIO_POLARITY__BOTH = 2U

		}RM4_GIO__INTERRUPT_POLARITY_T;

		//isr level types
		/*****************************************************************************
		*****************************************************************************/
		typedef enum
		{
			GIO_LEVEL__VIM_LOW = 0U,
			GIO_LEVEL__VIM_HIGH = 1U

		}RM4_GIO__INTERRUPT_LEVEL_T;

		/** Port types */
		typedef enum
		{
			RM4_GIO__PORT_A = 0U,
			RM4_GIO__PORT_B = 1U
		}RM4_GIO__PORT_DEFINE_T;

		typedef enum
		{
			PULL_TYPE__PULLDOWN = 0U,
			PULL_TYPE__PULLUP = 1U

		}RM4_GIO__PULL_T;


		/*****************************************************************************
		//Function protos
		*****************************************************************************/
		void vRM4_GIO__Init(void);
		void vRM4_GIO__Set_PortDirection(RM4_GIO__PORT_DEFINE_T ePort, RM4_GIO__PORT_DIRECTION_T eDir);
		void vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_DEFINE_T ePort, Luint32 u32Bit, RM4_GIO__PORT_DIRECTION_T eDIR);
		void vRM4_GIO__Set_Bit(RM4_GIO__PORT_DEFINE_T ePort, Luint32 u32Bit, Luint32 u32Value);
		void vRM4_GIO__Set_Port(RM4_GIO__PORT_DEFINE_T ePort, Luint32 u32Value);
		void vRM4_GIO__Set_Port_Pullup(RM4_GIO__PORT_DEFINE_T ePort, Luint32 u32Bit);
		Luint32 u32RM4_GIO__Get_Bit(RM4_GIO__PORT_DEFINE_T ePort, Luint32 u32Bit);
		Luint32 u32RM4_GIO__Get_Port(RM4_GIO__PORT_DEFINE_T ePort);
		void vRM4_GIO__Toggle_Bit(RM4_GIO__PORT_DEFINE_T ePort, Luint32 u32Bit);

		//pullups
		void vRM4_GIO_PULL__Enable_Pull(RM4_GIO__PORT_DEFINE_T ePort, Luint8 u8BitIndex);
		void vRM4_GIO_PULL__Disable_Pull(RM4_GIO__PORT_DEFINE_T ePort, Luint8 u8BitIndex);
		void vRM4_GIO_PULL__Set_Pull_Direction(RM4_GIO__PORT_DEFINE_T ePort, Luint8 u8BitIndex, RM4_GIO__PULL_T ePullType);

		#if C_LOCALDEF__LCCM133__ENABLE_INTERRUPTS == 1U
			void vRM4_GIO_ISR__High(void);
			void vRM4_GIO_ISR__Low(void);
			void vRM4_GIO_ISR__DefaultRoutine(void);
			void vRM4_GIO_ISR__EnableISR(RM4_GIO__INTERRUPT_PIN_T ePin);
			void vRM4_GIO_ISR__DisableISR(RM4_GIO__INTERRUPT_PIN_T ePin);
			void vRM4_GIO_ISR__DisableAll(void);
			void vRM4_GIO_ISR__Set_InterruptPolarity(RM4_GIO__INTERRUPT_POLARITY_T ePolarity, RM4_GIO__INTERRUPT_PIN_T ePin);
			void vRM4_GIO_ISR__Set_Interrupt_VIMLevel(RM4_GIO__INTERRUPT_LEVEL_T eLevel, RM4_GIO__INTERRUPT_PIN_T ePin);
			void vRM4_GIO_ISR__Clear_InterruptFlag(RM4_GIO__INTERRUPT_PIN_T ePIN);
		#endif //#if C_LOCALDEF__LCCM133__ENABLE_INTERRUPTS == 1

		//safetys
		#ifndef C_LOCALDEF__LCCM133__ENABLE_INTERRUPTS
			#error
		#endif

	#endif //#if C_LOCALDEF__LCCM133__ENABLE_THIS_MODULE == 1
#endif /* RM4_GIO_H_ */

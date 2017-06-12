/**
 * @file		MCP23S17.H
 * @brief		Main header file.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 *				of companies, including SIL3 Pty. Ltd (ACN 123 529 064) and
 *				Lockie Safety Systems Pty. Ltd (ACN 132 340 571). This code may be distributed
 *				under a license from the Lockie Group of companies, and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2012, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2012, All Rights Reserved.
 * @st_fileID	LCCM121R0.FILE.002
 */
#ifndef __MCP23S17_H_
#define __MCP23S17_H_
 
	#include <localdef.h>
	#if C_LOCALDEF__LCCM121__ENABLE_THIS_MODULE == 1U

		/*******************************************************************************
		Includes
		*******************************************************************************/
		#include <MULTICORE/LCCM121__MULTICORE__MCP23S17/mcp23s17__private.h>
		#include <MULTICORE/LCCM121__MULTICORE__MCP23S17/mcp23s17__fault_flags.h>

		/*******************************************************************************
		Function Protos
		*******************************************************************************/
		void vSIL3_MCP23S17__Init(Luint8 u8DeviceIndex);
		Luint32 u32SIL3_MCP23S17__Get_FaultFlags(Luint8 u8DeviceIndex);
		void vSIL3_MCP23S17__Set_Pin_High(Luint8 u8DeviceIndex, MCP23S17__PORT_E ePort, Luint8 u8Bit);
		void vSIL3_MCP23S17__Set_Pin(Luint8 u8DeviceIndex, MCP23S17__PORT_E ePort, Luint8 u8Bit, Luint8 u8Value);
		void vSIL3_MCP23S17__Set_Pin_Low(Luint8 u8DeviceIndex, MCP23S17__PORT_E ePort, Luint8 u8Bit);
		void vSIL3_MCP23S17__Set_PinDirection_Output(Luint8 u8DeviceIndex, MCP23S17__PORT_E ePort, Luint8 u8Bit);
		void vSIL3_MCP23S17__Set_PinDirection_Input(Luint8 u8DeviceIndex, MCP23S17__PORT_E ePort, Luint8 u8Bit);
		void vSIL3_MCP23S17__Set_PinPolarity_Opposite(Luint8 u8DeviceIndex, MCP23S17__PORT_E ePort, Luint8 u8Bit);
		void vSIL3_MCP23S17__Set_PinPolarity_Same(Luint8 u8DeviceIndex, MCP23S17__PORT_E ePort, Luint8 u8Bit);
		void vSIL3_MCP23S17__EnablePullups(Luint8 u8DeviceIndex, MCP23S17__PORT_E ePort, Luint8 u8Mask);
		void vSIL3_MCP23S17__Set_Port(Luint8 u8DeviceIndex, MCP23S17__PORT_E ePort, Luint8 u8Value);
		Luint8 u8SIL3_MCP23S17__Read_PortA(Luint8 u8DeviceIndex);
		Luint8 u8SIL3_MCP23S17__Read_Input(Luint8 u8DeviceIndex, MCP23S17__PORT_E ePort, Luint8 u8Bit);
		Luint8 u8SIL3_MCP23S17__Read_PortB(Luint8 u8DeviceIndex);
		
		//ISR
		void vSIL3_MCP23S17_ISR__MirrorIntPins(Luint8 u8DeviceIndex);
		void vSIL3_MCP23S17_ISR__Enable_OnChange(Luint8 u8DeviceIndex, MCP23S17__PORT_E ePort, Luint8 u8Bit);
		void vSIL3_MCP23S17_ISR__Enable_OnChange_New(Luint8 u8DeviceIndex, MCP23S17__PORT_E ePort, Luint8 u8Bit);
		void vSIL3_MCP23S17_ISR__Enable_OnValue(Luint8 u8DeviceIndex, MCP23S17__PORT_E ePort, Luint8 u8Bit, Luint8 u8Value);
		void vSIL3_MCP23S17_ISR__Disable(Luint8 u8DeviceIndex, MCP23S17__PORT_E ePort, Luint8 u8Bit);
		void vSIL3_MCP23S17_ISR__Clear(Luint8 u8DeviceIndex);
		
		//lowlevel
		void vSIL3_MCP23S17_LOWLEVEL__ShutdownInterface(Luint8 u8DeviceIndex);
		Lint16 s16SIL3_MCP23S17_LOWLEVEL__WriteRegister(Luint8 u8DeviceIndex, Luint8 u8RegAddx, Luint8 u8Value);
		Lint16 s16SIL3_MCP23S17_LOWLEVEL__ReadRegister(Luint8 u8DeviceIndex, Luint8 u8Addx, Luint8 *pu8Data);

		

		
	#endif//C_LOCALDEF__LCCM121__ENABLE_THIS_MODULE
	#ifndef C_LOCALDEF__LCCM121__ENABLE_THIS_MODULE
		#error
	#endif

#endif //__MCP23S17_H_


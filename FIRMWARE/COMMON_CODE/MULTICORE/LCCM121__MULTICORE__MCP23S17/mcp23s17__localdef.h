/**
 * @file		MCP23S17__LOCALDEF.H
 * @brief		Localdef template.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 *				of companies, including SIL3 Pty. Ltd (ACN 123 529 064) and
 *				Lockie Safety Systems Pty. Ltd (ACN 132 340 571). This code may be distributed
 *				under a license from the Lockie Group of companies, and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2012, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2012, All Rights Reserved.
 * @st_fileID	LCCM121R0.FILE.003
 */

#if 0

/*******************************************************************************
SIL3 - MCP23S17 DRIVER
*******************************************************************************/
	#define C_LOCALDEF__LCCM121__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM121__ENABLE_THIS_MODULE == 1U

		//determine interface
		#define C_LOCALDEF__LCCM121__USE_I2C 								(0U)
		#define C_LOCALDEF__LCCM121__USE_SPI								(1U)

		#if C_LOCALDEF__LCCM121__USE_SPI == 1U
			//chip select port
			#define C_LOCALDEF__LCCM121__NCS_TRIS()							vRM4_MIBSPI135_PINS__Set_OutputDirection(MIBSPI135_CHANNEL__1, MIBSPI135_PIN__CS3)
			#define C_LOCALDEF__LCCM121__NCS_LATCH(x)						vRM4_MIBSPI135_PINS__Set(MIBSPI135_CHANNEL__1, MIBSPI135_PIN__CS3, x)

			//reset port
			#define C_LOCALDEF__LCCM121__NRESET_TRIS()						vRM4_N2HET1_PINS__Set_PinDirection_Output(15)
			#define C_LOCALDEF__LCCM121__NRESET_LATCH(x)					vRM4_N2HET1_PINS__Set_Pin(15, x)

			//interrupt port (if used)

			//this is the SPI send byte routine
			#define C_LOCALDEF__LCCM121__SPI_SENDBYTE(x) 					u8RM4_MIBSPI135__Tx_U8(MIBSPI135_CHANNEL__1, MIBSPI135_DATA_FORMAT__0,MIBSPI135_CS__NONE, x)
			
		#elif C_LOCALDEF__LCCM121__USE_I2C == 1U

			//Supply the address without shifting.
			//The 0x20 is fixed in the silicon
			//Only defined when a single chip is used. If more than one chip is used
			//the address is handled externally
			 #define C_LOCALDEF__LCCM121__I2C_ADDRESS	(0x20 | 0x00)

			//Reset and communication port are required for every microcontroller (PIC32, PIC18, RM4)
			#define C_LOCALDEF__LCCM121__NRESET_TRIS(index)						TRISCbits.TRISC5
			#define C_LOCALDEF__LCCM121__NRESET_LATCH(index, x)					(LATCbits.LATC5 = x)
			#define C_LOCALDEF__LCCM121__I2C_WRITE_REGISTER(u8DeviceAddx, u8RegisterAddx, u8Byte) s16PIC18_I2C_USER__TxByte(u8DeviceAddx, u8RegisterAddx, u8Byte)
			#define C_LOCALDEF__LCCM121__I2C_READ_REGISTER(u8DeviceAddx, u8RegisterAddx, pu8Byte) s16PIC18_I2C_USER__RxByte(u8DeviceAddx, u8RegisterAddx, pu8Byte)

		#endif

		//testing
		#define C_LOCALDEF__LCCM121__ENABLE_TEST_SPEC						(0U)
		
		//main include file
		#include <MULTICORE/LCCM121__MULTICORE__MCP23S17/mcp23s17.h>

	#endif //C_LOCALDEF__LCCM121__ENABLE_THIS_MODULE


#endif 


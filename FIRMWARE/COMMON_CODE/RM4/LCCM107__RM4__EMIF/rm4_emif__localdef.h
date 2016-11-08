/**
 * @file		rm4_emif__localdef.h
 * @brief		Localdef template for EMIF
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM107R0.FILE.003
 */

#if 0

/*******************************************************************************
EMIF (External Memory Interface)
*******************************************************************************/
 	#define C_LOCALDEF__LCCM107__ENABLE_THIS_MODULE 						(1U)
	#if C_LOCALDEF__LCCM107__ENABLE_THIS_MODULE == 1U

		//enable special features
		#define C_LOCALDEF__LCCM107__ENABLE_SPECIAL_FEATURES				(1U)

		//testing options
		#define C_LOCALDEF__LCCM107__ENABLE_TEST_SPEC						(0U)

		/* EMIF Clock Speed
		 * The EMIF clock is from VCLK3 which can be HCLK/1... HCLK/16
		 * Remember in our standard systems HCLK = VCLK/2.
		 * Valid values are 0x00..0x0F = (0..16d)
		 * Typical value is 1 (= HCLK/2 = 100MHZ for a 200MHZ system clock)
		 */
		#define C_LOCALDEF__LCCM107__EMIF_CLOCK_DIVISOR						(1U)


		//These are the nCS lines we can use, they relate to physical memory addresses
		//Refer to the microcontroller manual, however usually
		//CS0 - 0x80000000 -> 0x87FFFFFF 	= SDRAM (128MB)
		//CS2 - 0x60000000 -> 0x64000000
		//CS3 - 0x64000000 -> 0x68000000
		//CS4 - 0x68000000 -> 0x6C000000
		#define C_LOCALDEF__LCCM107__ENABLE_CS0								(0U)
		#define C_LOCALDEF__LCCM107__ENABLE_CS2								(1U)
		#define C_LOCALDEF__LCCM107__ENABLE_CS3								(0U)
		#define C_LOCALDEF__LCCM107__ENABLE_CS4								(0U)

		//various options
		//When run at 100MHZ (clock divisor = 1), widths are typically 10ns multiples
		#if C_LOCALDEF__LCCM107__ENABLE_CS2 == 1U
			//0-15
			#define C_LOCALDEF__LCCM107__CS2_WRITE_SETUP_WIDTH				(4U)
			//0-63
			#define C_LOCALDEF__LCCM107__CS2_WRITE_STROBE_WIDTH				(4U)
			//0-7
			#define C_LOCALDEF__LCCM107__CS2_WRITE_HOLD_WIDTH				(4U)
			//0-15
			#define C_LOCALDEF__LCCM107__CS2_READ_SETUP_WIDTH				(4U)
			//0-63
			#define C_LOCALDEF__LCCM107__CS2_READ_STROBE_WIDTH				(4U)
			//0-7
			#define C_LOCALDEF__LCCM107__CS2_READ_HOLD_WIDTH				(4U)
		#endif


		#if C_LOCALDEF__LCCM107__ENABLE_CS3 == 1U
			//0-15
			#define C_LOCALDEF__LCCM107__CS3_WRITE_SETUP_WIDTH				(4U)
			//0-63
			#define C_LOCALDEF__LCCM107__CS3_WRITE_STROBE_WIDTH				(4U)
			//0-7
			#define C_LOCALDEF__LCCM107__CS3_WRITE_HOLD_WIDTH				(4U)
			//0-15
			#define C_LOCALDEF__LCCM107__CS3_READ_SETUP_WIDTH				(4U)
			//0-63
			#define C_LOCALDEF__LCCM107__CS3_READ_STROBE_WIDTH				(4U)
			//0-7
			#define C_LOCALDEF__LCCM107__CS3_READ_HOLD_WIDTH				(4U)
		#endif

		#if C_LOCALDEF__LCCM107__ENABLE_CS4 == 1U
			//0-15
			#define C_LOCALDEF__LCCM107__CS4_WRITE_SETUP_WIDTH				(4U)
			//0-63
			#define C_LOCALDEF__LCCM107__CS4_WRITE_STROBE_WIDTH				(4U)
			//0-7
			#define C_LOCALDEF__LCCM107__CS4_WRITE_HOLD_WIDTH				(4U)
			//0-15
			#define C_LOCALDEF__LCCM107__CS4_READ_SETUP_WIDTH				(4U)
			//0-63
			#define C_LOCALDEF__LCCM107__CS4_READ_STROBE_WIDTH				(4U)
			//0-7
			#define C_LOCALDEF__LCCM107__CS4_READ_HOLD_WIDTH				(4U)
		#endif



		//enable standard encapsulation for FPGA comms
		#define C_LOCALDEF__LCCM107__ENABLE_ENCAP							(0U)

		#if C_LOCALDEF__LCCM107__ENABLE_ENCAP == 1U

			#define C_LOCALDEF__LCCM107__ENCAP_HWPIN__ISR_TRIS()			{vRM4_GIO__Set_BitDirection(gioPORTB, 7, GIO_DIRECTION__INPUT);}
			#define C_LOCALDEF__LCCM107__ENCAP_HWPIN__ISR_PORT()			u32RM4_GIO__Get_Bit(gioPORTB, 7U)
			#define C_LOCALDEF__LCCM107__ENCAP_HWPIN__BUSY_TRIS()			{vRM4_GIO__Set_BitDirection(gioPORTB, 6, GIO_DIRECTION__INPUT);}
			#define C_LOCALDEF__LCCM107__ENCAP_HWPIN__BUSY_PORT()			u32RM4_GIO__Get_Bit(gioPORTB, 6U)

		#endif

		//main include file
		#include <RM4/LCCM107__RM4__EMIF/rm4_emif.h>

	#endif //C_LOCALDEF__LCCM107__ENABLE_THIS_MODULE


#endif //0


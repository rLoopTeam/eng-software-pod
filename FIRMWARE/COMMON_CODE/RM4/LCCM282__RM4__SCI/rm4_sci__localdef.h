/**
 * @file		rm4_sci__localdef.h
 * @brief		Localdef template for SCI
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM282R0.FILE.003
 */
 
#if 0

/*******************************************************************************
SIL3 - RM48/RM57 - SCI / LIN Module
*******************************************************************************/
	#define C_LOCALDEF__LCCM282__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM282__ENABLE_THIS_MODULE == 1U

		//if you have to do debugging
		#define DEBUG_PRINT(x)												vRM4_SCI_HELPERS__DisplayText(SCI_CHANNEL__2, x, 100)

		//enable interrupts, else use polling Mode
		#define C_LOCALDEF__LCCM282__ENABLE_INTERRUPTS						(0U)

		/** Switch on DMA functions */
		#define C_LOCALDEF__LCCM282__ENABLE_DMA								(0U)

		//determine which SCI module to enable
		//SCI1 shares pins with EMAC
		#define C_LOCALDEF__LCCM282__ENABLE_SCI_1							(0U)

		//SCI 2 is also LIN and uses the LIN pins on ZWT Package
		//SCI2 is USB debug on HDK
		#define C_LOCALDEF__LCCM282__ENABLE_SCI_2							(0U)

        //SCI3 only on RM57, Launchpad Boosterpack Site 1
        #define C_LOCALDEF__LCCM282__ENABLE_SCI_3                           (0U)

        //SCI4 only on RM57
        #define C_LOCALDEF__LCCM282__ENABLE_SCI_4                           (0U)

		//testing
		#define C_LOCALDEF__LCCM282__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <RM4/LCCM282__RM4__SCI/rm4_sci.h>

	#else
		#define DEBUG_PRINT(x)
	#endif //C_LOCALDEF__LCCM282__ENABLE_THIS_MODULE

#endif //0


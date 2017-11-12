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
Note the following are the back channel debug ports:
RM48HDK - SCI2
RM57LAUNCH - SCI1 (LIN1)
*******************************************************************************/
	#define C_LOCALDEF__LCCM282__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM282__ENABLE_THIS_MODULE == 1U

		//if you have to do debugging
		#define DEBUG_PRINT(x)												vRM4_SCI_HELPERS__DisplayText(SCI_CHANNEL__1, x, 1000)

		//enable interrupts, else use polling Mode
		#define C_LOCALDEF__LCCM282__ENABLE_INTERRUPTS						(0U)

		/** Switch on DMA functions */
		#define C_LOCALDEF__LCCM282__ENABLE_DMA								(0U)

		//determine which SCI module to enable

		/** SCI 1
		 * RM48HDK: Shares pins with EMAC
		 * RM57LAUNCH: SCILIN1 - USB Backchannel and LIN1 on Booster-site 2 (J5:3=RX, J5:4=TX)
		 */
		#define C_LOCALDEF__LCCM282__ENABLE_SCI_1							(0U)

		/** SCI 2/LIN2
		 * RM48HDK: UART Back-channel on RM48HDK
		 * RM57LAUNCH: Proto Headers (J9:9=Tx, J9:10=Rx)
		 */
		#define C_LOCALDEF__LCCM282__ENABLE_SCI_2							(0U)

		/** SCI3
		 * RM57 Only
		 * SCI3 - Booster-site 1 (J1:3=RX, J1:4=TX)
		 */
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


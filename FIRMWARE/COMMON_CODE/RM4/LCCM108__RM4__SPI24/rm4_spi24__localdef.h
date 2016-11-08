/**
 * @file		RM4_SPI24__LOCALDEF.H
 * @brief		SPI2,4 Localdef Template
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM108R0.FILE.003
 */


#if 0

/*******************************************************************************
RM4 SPI2,4 MODULE
*******************************************************************************/
	#define C_LOCALDEF__LCCM108__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM108__ENABLE_THIS_MODULE == 1U

		/** interrupt support */
		#define C_LOCALDEF__LCCM108__ENABLE_INTERRUPTS 						(0U)

		/** Testing Options */
		#define C_LOCALDEF__LCCM108__ENABLE_TEST_SPEC		 				(0U)

		//based on our PinMUX system, there are various limitations
		//Use NENA = 1, or NCS1 = 0
		#define C_LOCALDEF__LCCM108__SPI2_PINMUX_NENA_OR_NCS1				(1U)


		//SPI2 Setup

		//the transfer length of up to 16 bits
		#define C_LOCALDEF__LCCM108__SPI2__DATAFMT_0__TXLEN_BITS			(8U)
		#define C_LOCALDEF__LCCM108__SPI2__DATAFMT_1__TXLEN_BITS			(8U)
		#define C_LOCALDEF__LCCM108__SPI2__DATAFMT_2__TXLEN_BITS			(8U)
		#define C_LOCALDEF__LCCM108__SPI2__DATAFMT_3__TXLEN_BITS			(8U)

		//set the speed of each format
		#define C_LOCALDEF__LCCM108__SPI2__DATAFMT_0__SPEED					SPI24_SPEED__5MHZ
		#define C_LOCALDEF__LCCM108__SPI2__DATAFMT_1__SPEED					SPI24_SPEED__5MHZ
		#define C_LOCALDEF__LCCM108__SPI2__DATAFMT_2__SPEED					SPI24_SPEED__5MHZ
		#define C_LOCALDEF__LCCM108__SPI2__DATAFMT_3__SPEED					SPI24_SPEED__5MHZ

		//clock phase
		#define C_LOCALDEF__LCCM108__SPI2__DATAFMT_0__CPHA					SPI24_CPHA__1
		#define C_LOCALDEF__LCCM108__SPI2__DATAFMT_1__CPHA					SPI24_CPHA__1
		#define C_LOCALDEF__LCCM108__SPI2__DATAFMT_2__CPHA					SPI24_CPHA__1
		#define C_LOCALDEF__LCCM108__SPI2__DATAFMT_3__CPHA					SPI24_CPHA__1


		//the transfer length of up to 16 bits
		#define C_LOCALDEF__LCCM108__SPI4__DATAFMT_0__TXLEN_BITS			(8U)
		#define C_LOCALDEF__LCCM108__SPI4__DATAFMT_1__TXLEN_BITS			(8U)
		#define C_LOCALDEF__LCCM108__SPI4__DATAFMT_2__TXLEN_BITS			(8U)
		#define C_LOCALDEF__LCCM108__SPI4__DATAFMT_3__TXLEN_BITS			(8U)

		//set the speed of each format
		#define C_LOCALDEF__LCCM108__SPI4__DATAFMT_0__SPEED					SPI24_SPEED__5MHZ
		#define C_LOCALDEF__LCCM108__SPI4__DATAFMT_1__SPEED					SPI24_SPEED__5MHZ
		#define C_LOCALDEF__LCCM108__SPI4__DATAFMT_2__SPEED					SPI24_SPEED__5MHZ
		#define C_LOCALDEF__LCCM108__SPI4__DATAFMT_3__SPEED					SPI24_SPEED__5MHZ

		//clock phase
		#define C_LOCALDEF__LCCM108__SPI4__DATAFMT_0__CPHA					SPI24_CPHA__1
		#define C_LOCALDEF__LCCM108__SPI4__DATAFMT_1__CPHA					SPI24_CPHA__1
		#define C_LOCALDEF__LCCM108__SPI4__DATAFMT_2__CPHA					SPI24_CPHA__1
		#define C_LOCALDEF__LCCM108__SPI4__DATAFMT_3__CPHA					SPI24_CPHA__1


		//main include file
		#include <RM4/LCCM108__RM4__SPI24/rm4_spi24.h>

	#endif //#if  C_LOCALDEF__LCCM108__ENABLE_THIS_MODULE == 1



#endif //0


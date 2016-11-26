/**
 * @file		rm4_emac__localdef.h
 * @brief		Localdef template for RM4 EMAC
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM254R0.FILE.005
 */
#if 0


/*******************************************************************************
EMAC Module
*******************************************************************************/
	#define C_LOCALDEF__LCCM254__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM254__ENABLE_THIS_MODULE == 1U

		//on some dev boards we need to use RMII mode, not MII mode
		#define C_LOCALDEF__LCCM254__ENABLE_RMII_MODE						(0U)

		//set to 1 if you have an external reset pin to the EMAC
		#define C_LOCALDEF__LCCM254__ENABLE_EXTERN_RESET					(1U)

		#if C_LOCALDEF__LCCM254__ENABLE_EXTERN_RESET == 1U
			#define C_LOCALDEF__LCCM254__NRESET_PIN__TRIS()						vRM4_N2HET_PINS__Set_PinDirection_Output(N2HET_CHANNEL__1, 0U)
			#define C_LOCALDEF__LCCM254__NRESET_PIN__LATCH(x)					vRM4_N2HET_PINS__Set_Pin(N2HET_CHANNEL__1, 0U, x)
		#endif

		//use LWIP or not
		#define C_LOCALDEF__LCCM254__USE_WITH_LWIP							(0U)
		#define C_LOCALDEF__LCCM254__USE_WITH_LCCM325						(1U)

		//testing options
		#define C_LOCALDEF__LCCM254__ENABLE_TEST_SPEC						(0U)
		#define C_LOCALDEF__LCCM254__ENABLE_IO_PIN_TESTING					(0U)

		//main include file
		#include <RM4/LCCM254__RM4__EMAC/rm4_emac.h>

	#endif //C_LOCALDEF__LCCM254__ENABLE_THIS_MODULE



#endif //0

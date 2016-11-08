/**
 * @file		RM4_SPI24__STATICDEF.H
 * @brief		Static constants
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM108R0.FILE.006
 */

#ifndef RM48_SPI_STATICDEF_H_
#define RM48_SPI_STATICDEF_H_


	/*Static definitions extracted from Technical Reference Manual*/

	/*****************************************************************************************/
									/*SPI GENERAL CONFIG*/
	/*****************************************************************************************/
	#define RM48L950_8_BIT_MODE   0
	#define RM48L950_32_BIT_MODE  1

	#define RM48L950_SPI_CLKMOD_EXTERNAL   0
	#define RM48L950_SPI_CLKMOD_INTERNAL   1

	#define RM48L950_SPI_SLAVE_MODE   0
	#define RM48L950_SPI_MASTER_MODE   1

	#define RM48L950_SPI_ENA_PIN_INACTIVE_STATE_PULL_HIGH   0
	#define RM48L950_SPI_ENA_PIN_INACTIVE_STATE_HIGH_Z   1
	/*****************************************************************************************/
										/*Data formats*/
	/*****************************************************************************************/
	#define RM48L950_SPIFMT_PARPOL_EVEN   0
	#define RM48L950_SPIFMT_PARPOL_ODD   1

	#define RM48L950_SPIFMT_PARITY_DISABLE   0
	#define RM48L950_SPIFMT_PARITY_ENABLE   1

	#define RM48L950_SPIFMT_WAITENA_DO_NOT_WAIT   0
	#define RM48L950_SPIFMT_WAITENA_WAIT   1

	#define RM48L950_SPIFMT_SHIFTDIR_MSB_FIRST   0
	#define RM48L950_SPIFMT_SHIFTDIR_LSB_FIRST   1

	#define RM48L950_SPIFMT_ENABLE_CS_TIMERS   0
	#define RM48L950_SPIFMT_DISABLE_CS_TIMERS   1

	#define RM48L950_SPIFMT_CLK_LOW_INACTIVE   0
	#define RM48L950_SPIFMT_CLK_HIGH_INACTIVE   1

	#define RM48L950_SPIFMT_CLK_NOT_DELAYED   0
	#define RM48L950_SPIFMT_CLK_DELAYED   1

	#define RM48L950_SPI_INT_LVL_HIGH 0
	#define RM48L950_SPI_INT_LVL_LOW  1

	#define RM48L950_SPI_INT_DISABLE 0
	#define RM48L950_SPI_INT_ENABLE  1

	#define RM48L950_SPI_PIN_VALUE_SET      1
	#define RM48L950_SPI_PIN_VALUE_CLEARED  0

	#define RM48L950_SPI_PIN_DIR_OUTPUT 1
	#define RM48L950_SPI_PIN_DIR_INPUT 0

	#define RM48L950_SPI_PIN_OPEN_DRAIN_ENABLE 1
	#define RM48L950_SPI_PIN_OPEN_DRAIN_DISABLE 0

	#define RM48L950_SPI_PIN_PULL_UP 1
	#define RM48L950_SPI_PIN_PULL_DOWN 0

	#define RM48L950_SPI_PIN_PU_PD_DISABLE 0
	#define RM48L950_SPI_PIN_PU_PD_ENABLE 1

	#define RM48L950_SPI_PIN_SPI_FUNCTION 1
	#define RM48L950_SPI_PIN_GPIO_FUNCTION 0

	#define RM48L950_SPI_DATA_FMT0 0
	#define RM48L950_SPI_DATA_FMT1 1
	#define RM48L950_SPI_DATA_FMT2 2
	#define RM48L950_SPI_DATA_FMT3 3

	#define RM48L950_SPI_CS_HOLD_INACTIVE 0
	#define RM48L950_SPI_CS_HOLD_ACTIVE 1

#endif /* RM48_SPI_STATICDEF_H_ */

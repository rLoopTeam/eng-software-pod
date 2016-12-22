/**
 * @file		ATA6870__INTERRUPTS.C
 * @brief		Interrupt handlers for the ATA6870 device driver
 *
 * @note
 * In NORM mode (normal mode), the reasons for an interrupt request are:
 * 		1. 	The availability of measured data (data ready)
 * 			When a voltage measurement is completed, the dataRdy flag is set in the status register.
 * 			The ATA6870N cannot decode any new incoming operation until the dataRdy flag is released.
 * 		2.	The low frequency timer (LFT) elapses (wakeup)
 * 			The wakeup flag is set in the status register when the LFT elapses. The LFT is controlled via the SPI interface.
 * 		3.	A transmission error is flagged during the last SPI transaction (the commError bit is set in the status register).
 * 		4.	If an undervoltage condition occurs. The undervoltage function is controllable via SPI interface.
 *
 * A mask bit in the irqMask register corresponds to each interrupt source. The MCU must read the ATA6870N status register
 * before the interrupt is cleared. With each SPI access a 16-bit IRQ state is sent via MISO to the MCU with the interrupt state
 * of all stacked ATA6870N (see Section 7.6.4.1 â€œSPI Transaction Fieldsâ€� on page 26).
 *
 * In PDmode (power down), if the digital control part and MCU are not supplied, neither SPI command nor interrupt are
 * transmitted over the interface.
 *
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM650R0.FILE.006
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup ATA6870
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup ATA6870__INTERRUPTS
 * @ingroup ATA6870
 * @{ */

#include "../ata6870.h"
#if C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE == 1U

extern struct _strPWRNODE sPWRNODE;

/***************************************************************************//**
 * @brief
 * Do what ever is needed to bring the interrupts up.
 * 
 * @st_funcMD5		9EAA9EEFFB445AA8F79C56A021B849B5
 * @st_funcID		LCCM650R0.FILE.006.FUNC.001
 */
void vATA6870_INT__Init(void)
{
	Luint8 u8Counter;
	
	for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM650__NUM_DEVICES; u8Counter++)
	{
		//clear the interrupt vars
		sPWRNODE.sATA6870.sDevice[u8Counter].sIRQ.u16IRQ_Status = 0x0000U;
	}

}


/***************************************************************************//**
 * @brief
 * Interrupt Service Routine.
 *
 * @note
 * As the ATA6870's can be cascaded the device index should always be 0.
 * Technically this parameter could allow us to have multiple chains of devices connected.
 * 
 * @param[in]		u8DeviceIndex			Must be 0.
 * @st_funcMD5		2B4561BF630B6F8526CA740D9F84E1E5
 * @st_funcID		LCCM650R0.FILE.006.FUNC.002
 */
void vATA6870_INT__ISR(Luint8 u8DeviceIndex)
{

}

#endif //#if C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */


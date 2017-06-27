/**
 * @file		rm4_pcr.h
 * @brief		PCR main header file
 * \par
 * The PCR manages the accesses to the peripheral registers and peripheral
 * 				memories. It provides a global reset for all the peripherals. It also supports the
 * 				capability to selectively enable or disable the clock for each peripheral
 * 				individually. The PCR also manages the accesses to the system module
 * 				registers required to configure the devices clocks, interrupts, and so on. The
 * 				system module registers also include status flags for indicating exception
 *				conditions, resets, aborts, errors, interrupts.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM223R0.FILE.002
 */

#ifndef _RM4_PCR_H_
#define _RM4_PCR_H_

	#include <localdef.h>
	
	#include <RM57/LCCM708__RM57__PERIPH_CENTRAL_RESOURCE/rm57_pcr__private.h>

	
	/* USER CODE BEGIN (0) */
	/* USER CODE END */

	#define QUADRANT0 1U
	#define QUADRANT1 2U
	#define QUADRANT2 4U
	#define QUADRANT3 8U

	typedef enum
	{
		PS0 = 0U,	PS1,	PS2,	PS3,
		PS4,		PS5,	PS6,	PS7,
		PS8,		PS9,	PS10,	PS11,
		PS12,		PS13,	PS14,	PS15,
		PS16,		PS17,	PS18,	PS19,
		PS20,		PS21,	PS22,	PS23,
		PS24,		PS25,	PS26,	PS27,
		PS28,		PS29,	PS30,	PS31
	}peripheral_Frame_t;

	typedef enum
	{
		PPS0 = 0U,	PPS1,	PPS2,	PPS3,
		PPS4,		PPS5,	PPS6,	PPS7
	}privileged_Peripheral_Frame_t;

	typedef enum
	{
		PPSE0 = 0U,	PPSE1,	PPSE2,	PPSE3,
		PPSE4,		PPSE5,	PPSE6,	PPSE7,
		PPSE8,		PPSE9,	PPSE10,	PPSE11,
		PPSE12,		PPSE13,	PPSE14,	PPSE15,
		PPSE16,		PPSE17,	PPSE18,	PPSE19,
		PPSE20,		PPSE21,	PPSE22,	PPSE23,
		PPSE24,		PPSE25,	PPSE26,	PPSE27,
		PPSE28,		PPSE29,	PPSE30,	PPSE31
	}privileged_Peripheral_Extended_Frame_t;

	typedef enum
	{
		PCS0 = 0U,	PCS1,	PCS2,	PCS3,
		PCS4,		PCS5,	PCS6,	PCS7,
		PCS8,		PCS9,	PCS10,	PCS11,
		PCS12,		PCS13,	PCS14,	PCS15,
		PCS16,		PCS17,	PCS18,	PCS19,
		PCS20,		PCS21,	PCS22,	PCS23,
		PCS24,		PCS25,	PCS26,	PCS27,
		PCS28,		PCS29,	PCS30,	PCS31,
		PCS32,		PCS33,	PCS34,	PCS35,
		PCS36,		PCS37,	PCS38,	PCS39,
		PCS40,		PCS41,	PCS42,	PCS43,
		PCS44,		PCS45,	PCS46,	PCS47,
		PCS48,		PCS49,	PCS50,	PCS51,
		PCS52,		PCS53,	PCS54,	PCS55,
		PCS56,		PCS57,	PCS58,	PCS59,
		PCS60,		PCS61,	PCS62,	PCS63
	}peripheral_Memory_t;

	typedef enum
	{
		PPCS0 = 0U,	PPCS1,	PPCS2,	PPCS3,
		PPCS4,		PPCS5,	PPCS6,	PPCS7,
		PPCS8,		PPCS9,	PPCS10,	PPCS11,
		PPCS12,		PPCS13,	PPCS14,	PPCS15
	}privileged_Peripheral_Memory_t;

	typedef enum
	{
		Master_CPU0 = 0U,
		Master_CPU1 = 1U, /* Reserved for Lock-Step device */
		Master_DMA  = 2U,
		Master_HTU1 = 3U,
		Master_HTU2 = 4U,
		Master_FTU  = 5U,
		Master_DMM  = 7U,
		Master_DAP  = 9U,
		Master_EMAC = 10U
	}master_ID_t;

	/**
	 * @defgroup PCR PCR
	 * @brief PPeripheral Central Resource Module
	 *
	 * Related files:
	 * - HL_reg_pcr.h
	 * - HL_sys_pcr.h
	 * - HL_sys_pcr.c
	 *
	 * @addtogroup PCR
	 * @{
	 */

	void peripheral_Memory_Protection_Set(pcrBASE_t *pcr, peripheral_Memory_t PCS);
	void peripheral_Memory_Protection_Clr(pcrBASE_t *pcr, peripheral_Memory_t PCS);
	void peripheral_Frame_Protection_Set (pcrBASE_t *pcr, peripheral_Frame_t PS, Luint32 quadrant);
	void peripheral_Frame_Protection_Clr (pcrBASE_t *pcr, peripheral_Frame_t PS, Luint32 quadrant);

	void peripheral_Memory_PowerDown_Set(pcrBASE_t *pcr, peripheral_Memory_t PCS);
	void peripheral_Memory_PowerDown_Clr(pcrBASE_t *pcr, peripheral_Memory_t PCS);
	void peripheral_Frame_PowerDown_Set (pcrBASE_t *pcr, peripheral_Frame_t PS, Luint32 quadrant);
	void peripheral_Frame_PowerDown_Clr (pcrBASE_t *pcr, peripheral_Frame_t PS, Luint32 quadrant);

	void peripheral_Frame_MasterIDFilter_Disable(pcrBASE_t *pcr, peripheral_Frame_t PS, Luint32 quadrant, master_ID_t master);
	void peripheral_Frame_MasterIDFilter_Enable (pcrBASE_t *pcr, peripheral_Frame_t PS, Luint32 quadrant, master_ID_t master);
	void privileged_Peripheral_Frame_MasterIDFilter_Disable(pcrBASE_t *pcr, privileged_Peripheral_Frame_t PPS, Luint32 quadrant, master_ID_t master);
	void privileged_Peripheral_Frame_MasterIDFilter_Enable (pcrBASE_t *pcr, privileged_Peripheral_Frame_t PPS, Luint32 quadrant, master_ID_t master);
	void privileged_Peripheral_Extended_Frame_MasterIDFilter_Disable(pcrBASE_t *pcr, privileged_Peripheral_Extended_Frame_t PPSE, Luint32 quadrant, master_ID_t master);
	void privileged_Peripheral_Extended_Frame_MasterIDFilter_Enable (pcrBASE_t *pcr, privileged_Peripheral_Extended_Frame_t PPSE, Luint32 quadrant, master_ID_t master);

	void peripheral_Memory_MasterIDFilter_Disable(pcrBASE_t *pcr, peripheral_Memory_t PCS, master_ID_t master);
	void peripheral_Memory_MasterIDFilter_Enable (pcrBASE_t *pcr, peripheral_Memory_t PCS, master_ID_t master);
	void privileged_Peripheral_Memory_MasterIDFilter_Disable(pcrBASE_t *pcr, privileged_Peripheral_Memory_t PPCS, master_ID_t master);
	void privileged_Peripheral_Memory_MasterIDFilter_Enable (pcrBASE_t *pcr, privileged_Peripheral_Memory_t PPCS, master_ID_t master);

	void pcrEnableMasterIDCheck (pcrBASE_t *pcr);
	void pcrDisableMasterIDCheck(pcrBASE_t *pcr);


#endif //_RM4_PCR_H_

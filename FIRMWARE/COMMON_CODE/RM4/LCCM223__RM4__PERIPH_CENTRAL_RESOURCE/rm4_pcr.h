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
	
	#include <RM4/LCCM223__RM4__PERIPH_CENTRAL_RESOURCE/rm4_pcr__private.h>

		//Function Protos
		void vRM4_PCR__Set_Frame_Protection(RM4_PCR__FRAME_SELECT_T tFrame);
		void vRM4_PCR__Clear_Frame_Protection(RM4_PCR__FRAME_SELECT_T tFrame);
		void vRM4_PCR__Set_Frame_Powerdown(RM4_PCR__FRAME_SELECT_T tFrame);
		void vRM4_PCR__Clear_Frame_Powerdown(RM4_PCR__FRAME_SELECT_T tFrame);

		void vRM4_PCR__Set_Protection(RM4_PCR__QUAD_CHIPSELECT_T tQuad_CS);
		void vRM4_PCR__Clear_Protection(RM4_PCR__QUAD_CHIPSELECT_T tQuad_CS);
		void vRM4_PCR__Protection_Status(RM4_PCR__QUAD_CHIPSELECT_T * tQuad_CS);
		void vRM4_PCR__Set_Powerdown(RM4_PCR__QUAD_CHIPSELECT_T tQuad_CS);
		void vRM4_PCR__Clear_Powerdown(RM4_PCR__QUAD_CHIPSELECT_T tQuad_CS);
		void vRM4_PCR__Powerdown_Status(RM4_PCR__QUAD_CHIPSELECT_T * tQuad_CS);

		void vRM4_PCR__Set_Memory_Protection(RM4_PCR__MEMORY_CHIPSELECT_T tMemory_CS);
		void vRM4_PCR__Clear_Memory_Protection(RM4_PCR__MEMORY_CHIPSELECT_T tMemory_CS);
		void vRM4_PCR__Memory_Protection_Status(RM4_PCR__MEMORY_CHIPSELECT_T* tMemory_CS);
		void vRM4_PCR__Set_Memory_Powerdown(RM4_PCR__MEMORY_CHIPSELECT_T tMemory_CS);
		void vRM4_PCR__Clear_Memory_Powerdown(RM4_PCR__MEMORY_CHIPSELECT_T tMemory_CS);
		void vRM4_PCR__Memory_Powerdown_Status(RM4_PCR__MEMORY_CHIPSELECT_T* tMemory_CS);

		void vRM4_PCR__Set_Mem_Frame_Protect(RM4_PCR__MEMORY_FRAME_CS_T tMemory_Frame_CS);
		void vRM4_PCR__Clear_Mem_Frame_Protect(RM4_PCR__MEMORY_FRAME_CS_T tMemory_Frame_CS);
		void vRM4_PCR__Set_Mem_Frame_Powerdown(RM4_PCR__MEMORY_FRAME_CS_T tMemory_Frame_CS);
		void vRM4_PCR__Clear_Mem_Frame_Powerdown (RM4_PCR__MEMORY_FRAME_CS_T tMemory_Frame_CS);


#endif //_RM4_PCR_H_

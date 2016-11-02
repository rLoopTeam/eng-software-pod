/**
 * @file		rm48_crc.h
 * @brief		CRC on RM4 main header.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM226R0.FILE.002
 */

#ifndef _RM4_CRC_H_
#define _RM4_CRC_H_
#ifndef WIN32
	#include <localdef.h>
	#ifndef C_LOCALDEF__LCCM226__ENABLE_THIS_MODULE
		#error
	#endif
	#if C_LOCALDEF__LCCM226__ENABLE_THIS_MODULE == 1U

		#include <rm4/lccm226__rm4__crc/rm4_crc__private.h>


	/* Function Prots */
	void vRM4_CRC__Init(void);
	void vRM4_CRC__SendPowerDown(RM4_CRC__BASET_T *crc);
	void vRM4_CRC__SignatureGen(const RM4_CRC__BASET_T *crc, const RM4_CRC__MODE_CONFIG__T *param);
	void vRM4_CRC__Set_Config(RM4_CRC__BASET_T *crc, const RM4_CRC__CONFIG_T *param);
	Luint64 vRM4_CRC__Get_PSASignature(const RM4_CRC__BASET_T *crc,Luint32 channel);
	Luint64 u64RM4_CRC__Get_SectorSignature(const RM4_CRC__BASET_T *crc,Luint32 channel);
	Luint32 u32RM4_CRC__Get_FailedSector(const RM4_CRC__BASET_T *crc,Luint32 channel);
	Luint32 u32RM4_CRC__Get_InterruptPending(const RM4_CRC__BASET_T *crc,Luint32 channel);
	void vRM4_CRC__ChannelReset(RM4_CRC__BASET_T *crc,Luint32 channel);
	void vRM4_CRC__EnableNotification(RM4_CRC__BASET_T *crc, Luint32 flags);
	void vRM4_CRC__DisableNotification(RM4_CRC__BASET_T *crc, Luint32 flags);

	/** @fn void crcNotification(RM4_CRC__BASET_T *crc, Luint32 flags)
	*   @brief Interrupt callback
	*   @param[in] crc   - crc module base address
	*   @param[in] flags - copy of error interrupt flags
	*
	* This is a callback that is provided by the application and is called upon
	* an interrupt.  The parameter passed to the callback is a copy of the
	* interrupt flag register.
	*/
	void crcNotification(RM4_CRC__BASET_T *crc, Luint32 flags);

	#endif //C_LOCALDEF__LCCM226__ENABLE_THIS_MODULE
#endif //WIN32
#endif //RM4_CRC

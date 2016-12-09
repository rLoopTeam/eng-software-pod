/**
 * @file		SAFE_UDP__LOCALDEF.H
 * @brief		Localdef template
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 *				of companies, including SIL3 Pty. Ltd (ACN 123 529 064) and
 *				Lockie Safety Systems Pty. Ltd (ACN 132 340 571).  This code may be distributed
 *				under a license from the Lockie Group of companies, and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2015, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2015, All Rights Reserved.
 * @st_fileID	LCCM528R0.FILE.003
 */

#if 0

/*******************************************************************************
SAFETY UDP LAYER
*******************************************************************************/
	#define C_LOCALDEF__LCCM528__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM528__ENABLE_THIS_MODULE == 1U

		/* Architecture Options*/
		#define C_LOCALDEF__LCCM528__USE_ON_XILINX							(0U)
		#define C_LOCALDEF__LCCM528__USE_ON_RM4								(0U)
		#define C_LOCALDEF__LCCM528__USE_ON_MSP430							(0U)
		#define C_LOCALDEF__LCCM528__USE_ON_WIN32							(0U)

		/** User Rx Callback
		* Payload, Length, Type, DestPort, Faults
		*/
		#define C_LOCALDEF__LCCM528__RX_CALLBACK(p,l,t,d,f)					vUSER__RxUDPSafe((Luint8 * pu8Payload, Luint16 u16PayloadLength, SAFE_UDP__PACKET_T ePacketType, Luint16 u16DestPort, SAFE_UDP__FAULTS_T eFault))
		
		/** The one and only UDP port we can operate on */
		#define C_LOCALDEF__LCCM528__ETHERNET_PORT_NUMBER					(9999U)
		#define C_LOCALDEF__LCCM528__ETHERNET_PORT_NUMBER2					(0U)
	
		/** Vision over SafeUDP Options */
		#define C_LOCALDEF__LCCM528__VISION__ENABLE_TX						(0U)
		#define C_LOCALDEF__LCCM528__VISION__ENABLE_RX						(0U)
		#define C_LOCALDEF__LCCM528__VISION__MAX_BUFFER_SIZE				(640UL * 480UL * 2UL)
	
		/** Testing Options */
		#define C_LOCALDEF__LCCM528__ENABLE_TEST_SPEC						(0U)
		
		/** Main include file */
		#include <MULTICORE/LCCM528__MULTICORE__SAFE_UDP/safe_udp.h>
		
	#endif //#if C_LOCALDEF__LCCM528__ENABLE_THIS_MODULE == 1U

#endif //#if 0


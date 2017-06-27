/**
 * @file		eth_localdef.h
 * @brief		Localdef template for Ethernet layer
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 *				of companies, including Lockie Innovation Pty. Ltd (ACN 123 529 064) and
 *				Lockie Safety Systems Pty. Ltd (ACN 132 340 571).  This code may be distributed
 *				under a license from the Lockie Group of companies, and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright Lockie Innovation Pty Ltd 2003-2012, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2012, All Rights Reserved.
 * @st_fileID	LCCM325R0.FILE.004
 */


#if 0

/*******************************************************************************
SIL3 - 802.3 ETHERNET
*******************************************************************************/
	#define C_LOCALDEF__LCCM325__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM325__ENABLE_THIS_MODULE == 1U

		/** On Xilinx Architectures we can use NPI burst transfers */
		#define C_LOCALDEF__LCCM325__XILINX_USE_NPI_INTERFACE				(0U)

		//various protocol options
		/** DHCP Client */
		#define C_LOCALDEF__LCCM325__ENABLE_DHCP_CLIENT						(0U)
		/** Link Layer Discovery Protocol */
		#define C_LOCALDEF__LCCM325__ENABLE_LLDP							(0U)
		/** Simple Network Management Protocol */
		#define C_LOCALDEF__LCCM325__ENABLE_SNMP							(0U)
		/** TCP/IP */
		#define C_LOCALDEF__LCCM325__ENABLE_TCP								(0U)

		//UDP Rx
		#define C_LOCALDEF__LCCM325__UDP_RX_CALLBACK(buffer,length,port)	vSIL3_SAFEUDP_RX__UDPPacket(buffer, length, port)
	
		//testing options
		#define C_LOCALDEF__LCCM325__ENABLE_TEST_SPEC						(0U)
	

		//protocol specific options
		//set to 1 to consider port numbers
		#define C_LOCALDEF__LCCM325__PROTO_UDP__ENABLE_PORT_NUMBERS			(0U)

		//main include file
		#include <MULTICORE/LCCM325__MULTICORE__802_3/eth.h>
	
	#endif //C_LOCALDEF__LCCM325__ENABLE_THIS_MODULE



#endif //0


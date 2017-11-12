/**
 * @file		ETH__TYPES.H
 * @brief		Ethernet type defines
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM325R0.FILE.062
 */

#ifndef _ETH_TYPES_H_
#define _ETH_TYPES_H_


	/** Used to determine how to handle the IP types in packets*/
	typedef enum
	{

		/** Normally use what ever IP is supplied by the parent function */
		SET_IP_TYPE__NORMAL = 0U,

		/** Set the IP address to all zero */
		SET_IP_TYPE__ALL_ZERO,

		/** Set the IP address to all 0xFF */
		SET_IP_TYPE__BROADCAST,

		/** Set the IP address to that of the DNS server addx */
		SET_IP_TYPE__DNS_SERVER


	}TE_ETH__SET_IP_TYPE;

	/** ARP Request state machine types */
	typedef enum
	{
		/** Idle state, do nothing */
		ARP_REQUEST_STATE__IDLE = 0U,
		
		/** Formulate and transmit a request */
		ARP_REQUEST_STATE__TX_REQUEST,
		
		/** Wait for a request to come in */
		ARP_REQUEST_STATE__WAIT_REQUEST,

		/** Cleanup after an ARP */
		ARP_REQUEST_STATE__CLEANUP

		
	}TE_ETH__ARP_REQUEST_STATE;

	/** DHCP Client States */
	typedef enum
	{
		/** Sit in idle state and do nothing */
		DHCP_CLI_STATE__IDLE = 0U,

		DHCP_CLI_STATE__SEND_DISCOVER,

		DHCP_CLI_STATE__WAIT_OFFER,

		DHCP_CLI_STATE__SEND_REQUEST,

		/** Wait for an ACK from the DHCP server */
		DHCP_CLI_STATE__WAIT_ACK,

		/** Cleanup anything we need after we got the ACK */
		DHCP_CLI_STATE__FINISH_UP

	}TE_ETH__DHCP_CLIENT_STATE;

	/** DNS Client Statemachine */
	typedef enum
	{
		/** Do nothing */
		DNS_CLIENT_STATE__IDLE = 0U,

		/** Check that we have a DNS IP address configured */
		DNS_CLIENT_STATE__CHECK_DNS_IP,

		/** Perform an ARP to get our DNS MAC */
		DNS_CLIENT_STATE__ARP_DNS_MAC,

		/** Wait while the ARP is performed */
		DNS_CLIENT_STATE__WAIT_ARP_DNS_MAC,

		/** Check that we have a DNS MAC after a ARP  */
		DNS_CLIENT_STATE__CHECK_DNS_MAC_AFTER_ARP,

		/** Transmit the query */
		DNS_CLIENT_STATE__TX_QUERY,

		/** Wait for a response from the query */
		DNS_CLIENT_STATE__WAIT_RESPONSE,

		/** Do the necessary tasks after the response */
		DNS_CLIENT_STATE__CLEANUP


	}TE_ETH__DNS_CLIENT_STATE;


#endif

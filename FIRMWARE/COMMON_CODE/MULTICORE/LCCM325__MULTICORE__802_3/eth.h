/**
 * @file		eth.h
 * @brief		Ethernet main header file
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 *				of companies, including Lockie Innovation Pty. Ltd (ACN 123 529 064) and
 *				Lockie Safety Systems Pty. Ltd (ACN 132 340 571).  This code may be distributed
 *				under a license from the Lockie Group of companies, and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright Lockie Innovation Pty Ltd 2003-2012, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2012, All Rights Reserved.
 * @st_fileID	LCCM325R0.FILE.002
 */

#ifndef _ETH__H_
#define _ETH__H_

	#include <localdef.h>
	#if C_LOCALDEF__LCCM325__ENABLE_THIS_MODULE == 1U

		/*****************************************************************************
		Includes
		*****************************************************************************/
		#include <MULTICORE/LCCM325__MULTICORE__802_3/eth__types.h>
//		#include <MULTICORE/LCCM325__MULTICORE__802_3/TCP_CLIENT/eth__tcp_client_types.h>
	
		/*****************************************************************************
		Defines
		*****************************************************************************/
		#define C_LCCM325__FIFO_DEPTH											(6U)

		/** Maximum MAC address size */
		#define C_LCCM325__MAX_HW_MAC_SIZE_BYTES								(6U)

		/** Maximum protocol size */
		#define C_LCCM325__MAX_PROTOCOL_SIZE_BYTES								(4U)

		/** Max string length for the DNS query */
		#define C_LCCM325__MAX_DNS_QUERY_URL_SIZE_BYTES							(128U)

		/** The maximum window buffer size for Rx and Tx in TCP*/
		#define C_LCCM325__MAX_TCP_WINDOW_SIZE_BYTES							(1460U)

		/*****************************************************************************
		Structures
		*****************************************************************************/
		struct _strEUFIFO
		{
		
			//the buffer index we have chosen
			Luint8 u8FIFO_BufferIndex[C_LCCM325__FIFO_DEPTH];
			Luint16 u16FIFO_PacketLength[C_LCCM325__FIFO_DEPTH];
	
			//FIFO Positions
			Luint8 u8FIFO_WritePosition;
			Luint8 u8FIFO_ReadPosition;
					
			//the full flag is set by the write position going to the end.
			Luint8 u8FIFO_Full;
			Luint8 u8FIFO_Empty;
			Luint8 u8FIFO_FillLevel;
		
		};


		/** Main ethernet structure*/
		struct _strETH
		{

			//is a transmit required?
			Luint8 u8TxRequired;

			/** Our Settings */
			struct
			{
				/** Our MAC6 which should match our hardware and is the same as the EMAC interface layer */
				Luint8 u8MAC6[C_LCCM325__MAX_HW_MAC_SIZE_BYTES];

				/** Our IPV4 address. Its either assigned by the user at start or set to 0.0.0.0 and DHCP will fix*/
				Luint8 u8IPV4[C_LCCM325__MAX_PROTOCOL_SIZE_BYTES];

				/** Our subnet IPV4 mask, this is set to 255.255.255.0 always, unless DHCP fixes it up */
				Luint8 u8SubnetMask[C_LCCM325__MAX_PROTOCOL_SIZE_BYTES];

				/** The gateway IP address used for DNS */
				Luint8 u8GatewayIPV4[C_LCCM325__MAX_PROTOCOL_SIZE_BYTES];

				#if C_LOCALDEF__LCCM325__DNS__ENABLE_DNS_CLIENT == 1U
					Luint8 u8DNS_IPV4[C_LCCM325__MAX_PROTOCOL_SIZE_BYTES];
				#endif

			}sOurSettings;



			#if (C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__XILINX_MICROBLAZE == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__XILINX_PPC405 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__XILINX_PPC440 == 1U) || (C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__WIN32 == 1U)
			struct
			{
				/** The length of the NPI payload to send */
				Luint32 u32PayloadLength;

				/** The memory addx of the payload to send */
				Luint32 u32PayloadAddx;

			}sXilinx;
			#endif

			/** Ethernet-II layer */
			struct
			{

				/** when we get some input from the wire */
				struct
				{
					/** Dest hardware MAC */
					Luint8 u8DestMAC[C_LCCM325__MAX_HW_MAC_SIZE_BYTES];

					/** Source hardware MAC */
					Luint8 u8SourceMAC[C_LCCM325__MAX_HW_MAC_SIZE_BYTES];

					/** Ethernet frame type */
					Luint16 u16EtherType;
				}sRx;


				/** When we want to transmit out the wire */
				struct
				{
					/** Allow us to set the destination MAC*/
					Luint8 u8DestMAC[C_LCCM325__MAX_HW_MAC_SIZE_BYTES];
				}sTx;

			}sETH_II;

			
			/** UDP Layer */
			struct
			{
				Luint16 u16SourcePort;
				Luint16 u16DestPort;
				Luint16 u16Length;
				Luint16 u16Checksum;
			}sUDP;

			#if C_LOCALDEF__LCCM325__TCPIP__ENABLE_TCPIP == 1U
			/** TCP Client Layer */
			struct
			{

				/** Details about the current connection */
				struct
				{

					/** The current TCP state machine */
					TE_ETH__TCP_CLI_STATE_TYPES eCurrentState;

					/** Keep track of the previous state*/
					TE_ETH__TCP_CLI_STATE_TYPES ePrevState;

					/** The target IPV4 address */
					Luint8 u8TargetIPV4[C_LCCM325__MAX_PROTOCOL_SIZE_BYTES];

					/** The target port number */
					Luint16 u16TargetPort;

					/** The source port number that we randomly configure at startup
					and use for each connection type*/
					Luint16 u16SourcePort;

					/** Pointer to the Rx buffer to hold Rx data */
					Luint8 *pu8RxBufferPointer;

					/** Maximum Rx buffer size in byte */
					Luint32 u32RxBufferSize;

					/** Signal to upper layers that we have new data avail*/
					Luint8 u8NewRxAvail;

					/** Rx parameters from the server */
					struct
					{
					
						/** The frame ID structure */
						TS_ETH__TCP_FRAME_ID tsFrameID;

						/** Signal to the state machine that we got a new Rx */
						Luint8 u8NewRxAvail;

						/** The Rx Data buffer */
						Luint8 u8RxBuffer[C_LCCM325__MAX_TCP_WINDOW_SIZE_BYTES];

					}sRx;

					/** Last packet Transmit Parameters */
					struct
					{

						/** The sequence number used for transmissions */
						Luint32 u32SequenceNumber;

						/** The acknowledgement number used for transmissions */
						Luint32 u32AckNumber;

						/** The last flags that were transmitted, helps with the state machine tasks */
						Luint16 u16Flags;

					}sTx;

				}sConnection;

				//global sequence number


			}sTCP;
			#endif

			/** IPV4 Layer */
			struct
			{
				/** IPV4 version */
				Luint8 u8Version;
				Luint8 u8InternetHeaderLength;
				Luint16 u16TotalLength;
				Luint8 u8Protocol;
				Luint8 u8SourceIP[C_LCCM325__MAX_PROTOCOL_SIZE_BYTES];
				Luint8 u8DestIP[C_LCCM325__MAX_PROTOCOL_SIZE_BYTES];

				/** If we are using Unicast use this, else it will be FF*/
				Luint8 u8UnicastDestIP[C_LCCM325__MAX_PROTOCOL_SIZE_BYTES];

			}sIPV4;

			/* ARP (Address resolution protocol) */
			struct
			{
				

				/** Details about some ARP info received. This could come from
				 * who has <our IP>
				 */
				struct
				{
					/** The hardware type for the Rx */
					Luint16 u16HardwareType;

					Luint16 u16ProtocolType;
					Luint8 u8HWAddxLen;
					Luint8 u8ProtocolAddxLen;
					Luint16 u16Operation;
					Luint8 u8SenderMAC[C_LCCM325__MAX_HW_MAC_SIZE_BYTES];
					Luint8 u8SenderProtocol[C_LCCM325__MAX_PROTOCOL_SIZE_BYTES];
					Luint8 u8TargetMAC[C_LCCM325__MAX_HW_MAC_SIZE_BYTES];
					Luint8 u8TargetProtocol[C_LCCM325__MAX_PROTOCOL_SIZE_BYTES];


					/** This flag is set when we receive an ARP reply and will be used
					 * by the ARP state machine to change state after a request
					 */
					Luint8 u8NewReply;

				}sRx;

				/** When transmitting a ARP response we need to provide the target MAC
				 * and IP in the response
				 */
				struct
				{
					Luint8 u8MACAddx[C_LCCM325__MAX_HW_MAC_SIZE_BYTES];
					Luint8 u8IPAddx[C_LCCM325__MAX_PROTOCOL_SIZE_BYTES];
				}sTx;

				/** This structure is used when we request the MAC for a given IP*/
				struct
				{
					
					/** Set to 1 if we currently have a request in progress */
					Luint8 u8RequestInProgress;
					
					/** The IPV4 request address */
					Luint8 u8RequestIP[C_LCCM325__MAX_PROTOCOL_SIZE_BYTES];
					
					/** Request state machine */
					TE_ETH__ARP_REQUEST_STATE eSM;
					
				}sRequest;

				#if C_LOCALDEF__LCCM325__ARP__ENABLE_CACHE == 1U
				/** Caching if we have it */
				struct
				{
					/** The actual cache entries */
					struct
					{
						/** Cache Entry MAC Address */
						Luint8 u8MAC[C_LCCM325__MAX_HW_MAC_SIZE_BYTES];

						/** Cache Entry IP Address */
						Luint8 u8IP[C_LCCM325__MAX_PROTOCOL_SIZE_BYTES];

						/** The age of the entry. The age increments each 100ms and when the age
						 * exceeds a defined time, the entry will be marked as invalid. If the
						 * system wants to find an IP again, it will need to issue a new ARP request */
						Luint32 u32Age;

						/** A flag to indicate that the entry is valid */
						Luint8 u8Valid;

					}sEntry[C_LOCALDEF__LCCM325__ARP__MAX_CACHE_SIZE];

				}sCache;
				#endif
			
			}sARP;
			
			#if C_LOCALDEF__LCCM325__DHCP__ENABLE_DHCP_CLIENT == 1U
			/** DHCP (Dynamic Host Config Protocol) structure */
			struct
			{
				//the current state the DHCP Client is in
				TE_ETH__DHCP_CLIENT_STATE eState;

				/** The DHCP Transaction ID. Initially set to some random value and then
				 * incremented with each transaction
				 */
				Luint32 u32TransactionID;

				Luint8 u8MAC6[6];
				Luint8 u8IPV4[4];

			}sDHCP;
			#endif //C_LOCALDEF__LCCM325__DHCP__ENABLE_DHCP_CLIENT
			
			#if C_LOCALDEF__LCCM325__DNS__ENABLE_DNS_CLIENT == 1U
			/** DNS Client */
			struct
			{

				/** The query state machine */
				TE_ETH__DNS_CLIENT_STATE eState;

				/** The Query URL size in bytes, we add +2 to protect because we
				 * need to grow the array for the QName system */
				Luint8 u8QueryURL[C_LCCM325__MAX_DNS_QUERY_URL_SIZE_BYTES + 2U];

				/** The length of the query URL, saves having to stringlen all the time */
				Luint8 u8QueryURL_Length;

				/** The incrementing transaction ID */
				Luint16 u16TransactionID;

				/** Response from a request */
				struct
				{
					/** Indicate that the Rx was valid */
					Luint8 u8Valid;

					/** The IP of the query */
					Luint8 u8IPV4[C_LCCM325__MAX_PROTOCOL_SIZE_BYTES];

				}sRx;

			}sDNS;
			#endif //C_LOCALDEF__LCCM325__DNS__ENABLE_DNS_CLIENT

			#ifdef WIN32
			struct
			{
				/** Temp Assy buffer for WIN32 systems */
				Luint8 u8WIN32_AssemblyBuffer[1600];
			}sWIN32;
			#endif

		};
	
	
		/*****************************************************************************
		Function Prototypes
		*****************************************************************************/
		DLL_DECLARATION void vSIL3_ETH__Init(Luint8 *pu8MAC, Luint8 *pu8IP);
		DLL_DECLARATION void vSIL3_ETH__Process(void);
		DLL_DECLARATION Luint8 u8SIL3_ETH__Get_IsBusy(void);
		DLL_DECLARATION void vSIL3_ETH__Set_DNS(Luint8 *pu8DNS);
		DLL_DECLARATION void vSIL3_ETH__Set_GatewayIPV4(Luint8 *pu8IPV4);

		//FIFO Subsystem
		Luint8 u8SIL3_ETH_FIFO__Is_Empty(void);
		Lint16 s16SIL3_ETH_FIFO__Pop(Luint8 * pu8BufferIndex, Luint16 * pu16PacketLength);
		void vSIL3_ETH_FIFO__Peek(Luint8 u8BufferPos, Luint8 * pu8BufferIndex, Luint16 * pu16PacketLength);
		Lint16 s16SIL3_ETH_FIFO__Push(Luint16 u16PacketLength);
		void vSIL3_ETH_FIFO__Push_UpdateLength(Luint8 u8FIFOIndex, Luint16 u16NewLength);
		void vSIL3_ETH_FIFO__Transmit(void);
		void vSIL3_ETH_FIFO__Reset(void);
		
		#if (C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM42L432 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM46L852 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM48L952 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__RM57L843 == 1U)
			void vSIL3_ETH_FIFO__Transmit_Worker_RM4(void);
		#elif (C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__XILINX_MICROBLAZE == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__XILINX_PPC405 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__XILINX_PPC440 == 1U)
			void vSIL3_ETH_XILINX__Init(void);
			void vSIL3_ETH_XILINX__Transmit_PLB(Luint8 u8DeviceIndex);
			#if C_LOCALDEF__LCCM325__XILINX_USE_NPI_INTERFACE == 1U
				void vSIL3_ETH_XILINX__Transmit_NPI(Luint8 u8DeviceIndex);
			#endif
		#elif C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__WIN32 == 1U
			void vSIL3_ETH_FIFO__Transmit_Worker_WIN32(void);
		#elif C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__MSP430F5529 == 1U
			Lint16 s16ETH_FIFO__Transmit_Worker_MSP430(void);
		#else
			#error
		#endif

		//helpers
		void vSIL3_ETH_HELPERS__Copy_MAC6(Luint8 *pu8Source, Luint8 *pu8Dest);
		void vSIL3_ETH_HELPERS__Copy_IPV4(Luint8 *pu8Source, Luint8 *pu8Dest);
		void vSIL3_ETH_HELPERS__Set_Broadcast_MAC6(Luint8 *pu8Buffer);
		Luint16 u16SIL3_ETH_HELPERS__Handle_U16(Luint8 *pu8Buffer, Luint16 u16Offset);
		Luint16 u16SIL3_ETH_HELPERS__NetworkArray_To_Host(Luint8 *pu8Buffer, Luint16 u16Offset);
		void vSIL3_ETH_HELPERS__Host_To_NetworkArrayU16(Luint16 u16Value, Luint8 *pu8TargetBuffer, Luint16 u16Offset);
		void vSIL3_ETH_HELPERS__Host_To_NetworkArrayU32(Luint32 u32Value, Luint8 *pu8TargetBuffer, Luint16 u16Offset);
		Luint32 u32SIL3_ETH_HELPERS__NetworkArray_To_Host(Luint8 *pu8Buffer, Luint16 u16Offset);
		
		Luint32 u32SIL3_ETH_HELPERS__Host_To_Network(Luint32 u32HostValue);
		Luint16 u16SIL3_ETH_HELPERS__Host_To_Network(Luint16 u16HostValue);
		Luint32 u32SIL3_ETH_HELPERS__Network_To_Host(Luint32 u32NetworkValue);
		Luint16 u16SIL3_ETH_HELPERS__Network_To_Host(Luint16 u16NetworkValue);

		//ethernet layer
		void vSIL3_ETH_ETH2__Init(void);
		void vSIL3_ETH_ETH2__Process(void);
		void vSIL3_ETH_ETH2__Input(Luint8 *pu8Buffer);
		void vSIL3_ETH_ETH2__Transmit(Luint16 u16EtherType);
	
		//ipv4 layer
		void vSIL3_ETH_IPV4__Init(void);
		void vSIL3_ETH_IPV4__Process(void);
		void vSIL3_ETH_IPV4__Input(Luint8 *pu8Buffer);
		void vSIL3_ETH_IPV4__Transmit(Luint16 u16Length, TE_ETH__SET_IP_TYPE eSourceIPType, TE_ETH__SET_IP_TYPE eDestIPType);
		void vSIL3_ETH_IPV4__Transmit_TCP(Luint16 u16Length, Luint8 *pu8DestIP);
		void vSIL3_ETH_IPV4__Set_UnicastAddx(Luint8 *pu8Addx);
	
		//ARP
		void vSIL3_ETH_ARP__Init(void);
		void vSIL3_ETH_ARP__Process(void);
		void vSIL3_ETH_ARP__Input(Luint8 *pu8Buffer);
		void vSIL3_ETH_ARP__Reply(void);
		void vSIL3_ETH_ARP__Gratuitous(void);
		Luint8 u8SIL3_ETH_ARP__Is_Busy(void);
		
			//ARP Request
			#if C_LOCALDEF__LCCM325__ARP__ENABLE_REQUEST == 1U
				void vSIL3_ETH_ARP_REQ__Init(void);
				void vSIL3_ETH_ARP_REQ__Process(void);
				Luint8 u8SIL3_ETH_ARP_REQ__Get_IsBusy(void);
				DLL_DECLARATION Lint16 s16SIL3_ETH_ARP_REQ__Request(Luint8 *pu8IP);
			#endif
			
			//ARP Cache
			#if C_LOCALDEF__LCCM325__ARP__ENABLE_CACHE == 1U
				void vSIL3_ETH_ARP_CACHE__Init(void);
				void vSIL3_ETH_ARP_CACHE__Process(void);
				void vSIL3_ETH_ARP_CACHE__Add(Luint8 *pu8IP, Luint8 *pu8MAC);
				Lint16 s16SIL3_ETH_ARP_CACHE__Find_IP(Luint8 *pu8FindIP, Luint8 *pu8MatchMAC);
				Lint16 s16SIL3_ETH_ARP_CACHE__Find_IPOnly(Luint8 *pu8FindIP);
			#endif
		
		
		//DNS Client
		#if C_LOCALDEF__LCCM325__DNS__ENABLE_DNS_CLIENT == 1U
			void vSIL3_ETH_DNS_CLIENT__Init(void);
			void vSIL3_ETH_DNS_CLIENT__Process(void);
			void vSIL3_ETH_DNS_CLIENT__Query(Luint8 *pu8URL);
			Lint16 s16SIL3_ETH_DNS__Get_HostIP(Luint8 *pu8HostName, Luint8 *pu8IPV4);
			Luint8 u8SIL3_ETH_DNS_CLIENT__Get_IsBusy(void);
			void vSIL3_ETH_DNS_CLIENT__Input(Luint8 *pu8Buffer);
			void vSIL3_ETH_DNS_CLIENT__URL_To_QNAME(void);
			void vSIL3_ETH_DNS_CLIENT__QNAME_Get_Length(Luint8 *pu8Buffer, Luint8 *pu8NameLength, Luint8 *pu8LabelCount, Luint8 *pu8MemoryCount);
		#endif

		//SNMP
		#if C_LOCALDEF__LCCM325__ENABLE_SNMP == 1U
			void vSIL3_ETH_SNMP__Init(void);
			void vSIL3_ETH_SNMP__Process(void);
			void vSIL3_ETH_SNMP__Input(Luint8 * pu8Buffer);
			void vSIL3_ETH_SNMP__Transmit(Luint16 *pu16OID, Luint8 u8OIDLength, Luint8 u8RequestType);
		#endif

		//UDP
		void vSIL3_ETH_UDP__Init();
		void vSIL3_ETH_UDP__Process(void);
		void vSIL3_ETH_UDP__Transmit(Luint16 u16Length, Luint16 u16SourcePort, Luint16 u16DestPort, TE_ETH__SET_IP_TYPE eSourceIPType, TE_ETH__SET_IP_TYPE eDestIPType);
		#if (C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__XILINX_MICROBLAZE == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__XILINX_PPC405 == 1U || C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__XILINX_PPC440 == 1U) || (C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__WIN32 == 1U)
			#if C_LOCALDEF__LCCM325__XILINX_USE_NPI_INTERFACE == 1U
				void vSIL3_ETH_UDP__Transmit_WithPayload(Luint16 u16Length, Luint16 u16SourcePort, Luint16 u16DestPort, Luint32 u32PayloadLength, Luint32 u32PayloadAddx);
			#endif
		#endif
		void vSIL3_ETH_UDP__Input(Luint8 * pu8Buffer);
		
		//DHCP
		#if C_LOCALDEF__LCCM325__DHCP__ENABLE_DHCP_CLIENT == 1U
			void vSIL3_ETH_DHCP_CLIENT__Init(void);
			void vSIL3_ETH_DHCP_CLIENT__Process(void);
			void vSIL3_ETH_DHCP_CLIENT__Start(void);
			Luint8 u8SIL3_ETH_DCHP_CLIENT__Get_IsBusy(void);
			void vSIL3_ETH_DHCP_CLIENT__Input(Luint8 *pu8Buffer);
		#endif

		//LLDP
		#if C_LOCALDEF__LCCM325__ENABLE_LLDP == 1U
			void vSIL3_ETH_LLDP__Init(void);
			void vSIL3_ETH_LLDP__Process(void);
			void vSIL3_ETH_LLDP__Input(Luint8 * pu8Buffer);
			void vSIL3_ETH_LLDP__TransmitFrame(void);
		#endif

		//TCP/IP
		#if C_LOCALDEF__LCCM325__TCPIP__ENABLE_TCPIP == 1U
			void vSIL3_ETH_TCP__Init(void);
			void vSIL3_ETH_TCP__Process(void);
			DLL_DECLARATION void vSIL3_ETH_TCP__Open_Connection(Luint8 *pu8IP, Luint16 u16Port, Luint8 *pu8RxBuffer, Luint32 u32MaxRxLength);
			DLL_DECLARATION void vSIL3_ETH_TCH__Close_Connection(Luint8 u8ConnectionID);
			DLL_DECLARATION Luint8 u8SIL3_ETH_TCP__Get_ConnectionIdle(Luint8 u8ConnectionID);
			DLL_DECLARATION Luint8 u8SIL3_ETH_TCP__Get_ConnectionOpen(Luint8 u8ConnectionID);
			DLL_DECLARATION Luint8 u8SIL3_ETH_TCP__Get_ReceiveAvail(Luint8 u8ConnectionID);
			DLL_DECLARATION void vSIL3_ETH_TCP__Clear_ReceiveAvail(Luint8 u8ConnectionID);
			DLL_DECLARATION void vSIL3_ETH_TCP__Send_Data(Luint8 u8ConnectionID, Luint8 *pu8Buffer, Luint16 u16Length);

			//input handling
			void vSIL3_ETH_TCP_INPUT__Input(Luint8 *pu8Buffer, Luint16 u16PayloadLength);

			//crc
			Luint16 u16SIL3_ETH_TCP_CRC__CRC(Luint8 *pu8Buffer, Luint16 u16Length);

			//helpers
			Luint8 u8SIL3_ETH_TCP_HELPERS__Flags_GetHeaderLength(Luint8 *pu8Array, Luint16 u16Offset);
			void vSIL3_ETH_TCP_HELPERS__Flags_Create(Luint8 *pu8Array, Luint16 u16Offset, Luint8 u8HeaderLength, Luint16 u16Flags);
			Luint16 u16SIL3_ETH_TCP_HELPERS__Flags_GetFlags(Luint8 *pu8Array, Luint16 u16Offset);

			//tx
			void vSIL3_ETH_TCPIP__Tx_SYN(Luint8 u8DoSYNACK);
			void vSIL3_ETH_TCPIP__Tx_FIN(void);
			void vSIL3_ETH_TCPIP__Tx_ACK(Luint32 u32Seq_Num, Luint32 u32Ack_Num);
			void vSIL3_ETH_TCPIP__Tx_PSH(Luint32 u32Seq_Num, Luint32 u32Ack_Num, Luint8 *pu8Data, Luint16 u16DataLength);

		#endif

		//buffer desc
		Luint32 u32SIL3_ETH_BUFFERDESC__Get_TxBufferPointer(Luint8 u8BufferIndex);
		Luint16 u16SIL3_ETH_BUFFERDESC__Get_BufferSize(Luint8 u8BufferIndex);
		void vSIL3_ETH_BUFFERDESC__Set_Length(Luint8 u8BufferIndex, Luint32 u32Length);
		
		#ifdef WIN32
			void vSIL3_ETH_WIN32__Init(void);
			//declare the type
			typedef void (__cdecl * pETH_WIN32__TxCallback_FuncType)(Luint8 * pu8Buffer, Luint16 u16BufferLength);
			DLL_DECLARATION void vSIL3_ETH_WIN32__Set_Ethernet_TxCallback(pETH_WIN32__TxCallback_FuncType pFunc);
			DLL_DECLARATION void vSIL3_ETH_WIN32__Ethernet_Input(Luint8 * pu8Buffer, Luint16 u16BufferLength);
			DLL_DECLARATION void vSIL3_ETH_WIN32__Ethernet_Output(Luint8 * pu8Buffer, Luint16 u16BufferLength);
		#endif		
		
		/*****************************************************************************
		Unit Test Prototypes
		*****************************************************************************/
		#if C_LOCALDEF__LCCM325__ENABLE_TEST_SPEC == 1U
			void vLCCM325R0_TS_001(void);
			void vLCCM325R0_TS_002(void);
			void vLCCM325R0_TS_003(void);
			void vLCCM325R0_TS_004(void);
			void vLCCM325R0_TS_005(void);
			void vLCCM325R0_TS_006(void);
			void vLCCM325R0_TS_007(void);
			void vLCCM325R0_TS_008(void);
			void vLCCM325R0_TS_009(void);
			void vLCCM325R0_TS_010(void);
			DLL_DECLARATION void vLCCM325R0_TS_011(void);
			void vLCCM325R0_TS_012(void);
			void vLCCM325R0_TS_013(void);
			void vLCCM325R0_TS_014(void);
			void vLCCM325R0_TS_015(void);
			void vLCCM325R0_TS_016(void);
			void vLCCM325R0_TS_017(void);
			void vLCCM325R0_TS_018(void);
			void vLCCM325R0_TS_019(void);
			void vLCCM325R0_TS_020(void);
			void vLCCM325R0_TS_021(void);
			void vLCCM325R0_TS_022(void);
			void vLCCM325R0_TS_023(void);
			void vLCCM325R0_TS_024(void);
			void vLCCM325R0_TS_025(void);
			DLL_DECLARATION void vLCCM325R0_TS_026(void);
			void vLCCM325R0_TS_027(void);
			void vLCCM325R0_TS_028(void);
			void vLCCM325R0_TS_029(void);
			DLL_DECLARATION void vLCCM325R0_TS_040(void);
			
			DLL_DECLARATION void vLCCM325R0_TS_041(void);
			DLL_DECLARATION void vLCCM325R0_TS_042(void);
			DLL_DECLARATION void vLCCM325R0_TS_043(void);
			DLL_DECLARATION void vLCCM325R0_TS_044(void);
			DLL_DECLARATION void vLCCM325R0_TS_045(void);
#endif

		/*****************************************************************************
		Safetys
		*****************************************************************************/
//		#ifndef C_LOCALDEF__LCCM325__ARP__MAX_CACHE_SIZE
//			#error
//		#endif

	
	#endif //C_LOCALDEF__LCCM325__ENABLE_THIS_MODULE
	#ifndef C_LOCALDEF__LCCM325__ENABLE_THIS_MODULE
		#error
	#endif
	



#endif //_ETH__H_



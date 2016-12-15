/**
 * @file		SAFE_UDP.H
 * @brief		Main header file
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 *				of companies, including SIL3 Pty. Ltd (ACN 123 529 064) and
 *				Lockie Safety Systems Pty. Ltd (ACN 132 340 571).  This code may be distributed
 *				under a license from the Lockie Group of companies, and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2015, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2015, All Rights Reserved.
 * @st_fileID	LCCM528R0.FILE.002
 */


#ifndef _SAFE_UDP_H_
#define _SAFE_UDP_H_
	#include <localdef.h>
	#if C_LOCALDEF__LCCM528__ENABLE_THIS_MODULE == 1U

		#include <MULTICORE/LCCM528__MULTICORE__SAFE_UDP/safe_udp__packet_types.h>
		#include <MULTICORE/LCCM528__MULTICORE__SAFE_UDP/safe_udp__types.h>

		/*******************************************************************************
		Defines
		*******************************************************************************/

		#if C_LOCALDEF__LCCM528__VISION__ENABLE_TX == 1U
		typedef enum
		{
			/** wait in idle state until we are ready to transfer */
			IMAGETX_STATE__IDLE,
			IMAGETX_STATE__SEND_HEADER,
			IMAGETX_STATE__WAIT_HEADER,
			IMAGETX_STATE__SEND_PAYLOAD,
			IMAGETX_STATE__WAIT_PAYLOAD
		
		}E_SPECIAL__IMAGE_TX_STATE;
		#endif

		#if (C_LOCALDEF__LCCM528__VISION__ENABLE_TX == 1U) || (C_LOCALDEF__LCCM528__VISION__ENABLE_RX == 1U)
		/** vision header detail, also includes the entire UDP */
		typedef struct
		{

			Luint32 u32Sequence;
			Luint16 u16PacketType;
			Luint16 u16PayloadLength;

			Luint32 u32ImageLength;
			Luint8 u8CameraIndex;
			Luint8 u8BytesPixel;
			Luint16 u16ImageWidth;
			Luint16 u16ImageHeight;
			Luint16 u16ChunkIndex;
			Luint16 u16HeaderCRC;


		}S_VISION_HEADER__T;
		#endif

		/*******************************************************************************
		Structures
		*******************************************************************************/
		struct _strSAFE_UDP
		{

			Luint32 u32Seq;

			#if C_LOCALDEF__LCCM528__VISION__ENABLE_TX == 1U
			/** Specialised structure for image transfer over safety udp */
			struct
			{
			
				/** The total data length in bytes in the image */
				Luint32 u32TotalDataLength;
				
				/** Image width in pixels */
				Luint16 u16ImageWidth;
				
				/** Image height in pixels */
				Luint16 u16ImageHeight;
				
				/** The address of the image in memory (linear addx) */
				Luint32 u32ImageAddx;
				
				
				/** The current transfer state */
				E_SPECIAL__IMAGE_TX_STATE eState;
			
			
			}sImageTx;
			
			#endif

		};


		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		void vSAFEUDP__Init(void);
		void vSAFEUDP__Process(void);
		void vSAFEUDP__100MS_TimerTick(void);
		
		//rx
		DLL_DECLARATION void vSAFE_UDP_RX__UDPPacket(Luint8 * pu8PacketBuffer, Luint16 u16PacketLength, Luint16 u16DestPort);
		
		//tx
		Luint16 s16SAFEUDP_TX__PreCommit(Luint16 u16PayloadLength, SAFE_UDP__PACKET_T ePacketType, Luint8 ** pu8Buffer, Luint8 * pu8BufferIndex);
		void vSAFEUDP_TX__Commit(Luint8 u8BufferIndex, Luint16 u16PayloadLength, Luint16 u16SrcPort, Luint16 u16DestPort);
		void vSAFEUDP_TX__Commit_ZeroCRC(Luint8 u8BufferIndex, Luint16 u16PayloadLength, Luint16 u16SrcPort, Luint16 u16DestPort);
		void vSAFEUDP_TX__Commit_WithPayload(Luint8 u8BufferIndex, Luint16 u16PayloadLength, Luint16 u16SrcPort, Luint16 u16DestPort, Luint32 u32ExtraLength, Luint32 u32ExtraAddx);

		//sequence
		void vSAFEUDP_SEQ__Init(void);
		void vSAFEUDP_SEQ__Process(void);
		SAFE_UDP__FAULTS_T eSAFE_UDP_SEQ__Rx(Luint32 u32Seq);

		//message types
		void vSAFEUDP_MSG__Init(void);
		void vSAFEUDP_MSG__Process(void);
		void vSAFEUDP_MSG__Register(SAFE_UDP__PACKET_T eMessageType, Luint32 u32Max100MS);
		SAFE_UDP__FAULTS_T eSAFEUDP_MSG__Rx(SAFE_UDP__PACKET_T eMessageType);
		
		//special functions
		#if C_LOCALDEF__LCCM528__VISION__ENABLE_TX == 1U
			void vSAFEUDP_VISION_TX__Init(void);
			Luint8 u8SAFEUDP_VISION_TX__Is_Busy(void);
			void vSAFEUDP_VISION_TX__Process(void);
			void vSAFEUDP_VISION_TX__Start(Luint32 u32TotalDataLength, Luint32 u32Width, Luint32 u32Height, Luint32 u32ImageAddx);
		#endif

		#if C_LOCALDEF__LCCM528__VISION__ENABLE_RX == 1U
			void vSAFEUDP_VISION_RX__Packet(Luint8 *pu8PacketBuffer, Luint16 u16PacketLength);
		#endif	
		
		//testing
		#if C_LOCALDEF__LCCM528__ENABLE_TEST_SPEC == 1U
			DLL_DECLARATION void vLCCM528R0_TS_000(void);
			DLL_DECLARATION void vLCCM528R0_TS_001(void);
		#endif	

#ifdef WIN32
		void vUSER__RxUDPSafe(Luint8 * pu8Payload, Luint16 u16PayloadLength, SAFE_UDP__PACKET_T ePayloadType, Luint16 u16DestPort, SAFE_UDP__FAULTS_T ePayloadFault);
#endif

	#endif //#if C_LOCALDEF__LCCM528__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM528__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_SAFE_UDP_H_


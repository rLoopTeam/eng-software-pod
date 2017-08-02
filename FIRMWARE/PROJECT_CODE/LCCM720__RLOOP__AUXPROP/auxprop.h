/**
 * @file		AUXPROP.H
 * @brief		Main Header
 * @author		Lachlan Grogan
 * @st_fileID	LCCM720R0.FILE.001
 */

#ifndef _AUXPROP_H_
#define _AUXPROP_H_
	#include <localdef.h>
	#if C_LOCALDEF__LCCM720__ENABLE_THIS_MODULE == 1U

		/*******************************************************************************
		Includes
		*******************************************************************************/
		#include <LCCM720__RLOOP__AUXPROP/auxprop__types.h>

		//cross system networking types
		#include <LCCM655__RLOOP__FCU_CORE/NETWORKING/fcu_core__net__packet_types.h>

		//for software fault tree handling
		#include <MULTICORE/LCCM284__MULTICORE__FAULT_TREE/fault_tree__public.h>

		/*******************************************************************************
		Defines
		*******************************************************************************/


		/*******************************************************************************
		Structures
		*******************************************************************************/
		typedef struct
		{

			/** Ethernet Systems */
			struct
			{
				/** our hardware MAC */
				Luint8 u8MACAddx[6U];

				/** our locally assigned IP*/
				Luint8 u8IPAddx[4U];
			}sEthernet;


			/** Clutch Control */
			struct
			{

				/** State either engaged (on) or disegnaged*/
				Luint8 u8State;

			}sClutch;

			/** UDP diagnostics system */
			struct
			{

				/** A flag to indicate 10ms has elapsed if we are using timed packets */
				Luint8 u810MS_Flag;

				/** 25x 10 MS ticks */
				Luint8 u8250MS_Flag;

				/** The next packet type to transmit */
				E_NET__PACKET_T eTxPacketType;

				/** If the user has enabled Tx streaming */
				E_NET__PACKET_T eTxStreamingType;


			}sUDPDiag;


			/** Throttle Control */
			struct
			{

				/** Motor Direction*/
				TE_RLOOP_AUXPROP__THROTTLE_DIR eDirection;

				/** Channel enables */
				TE_RLOOP_AUXPROP__THROTTLE_ENA eEnable;

				/** N2HET program index */
				Luint16 u16N2HET_Index;

				/** The last computed frequency */
				Luint32 u32Frequency;

			}sThrottle;

		}TS_APU__MAIN;

		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		DLL_DECLARATION void vAPU__Init(void);
		DLL_DECLARATION void vAPU__Process(void);
		
		//clutch control
		void vAPU_CLUTCH__Init(void);
		void vAPU_CLUTCH__Process(void);
		void vAPU_CLUTCH__Engage(void);
		void vAPU_CLUTCH__Disengage(void);

		//throttle
		void vAPU_THROTTLE__Init(void);
		void vAPU_THROTTLE__Process(void);
		void vAPU_THROTTLE__Set_Velocity_mms(Luint32 u32Veloc_mms);
		void vAPU_THROTTLE__Forward(void);
		void vAPU_THROTTLE__Reverse(void);
		void vAPU_THROTTLE__Enable(void);
		void vAPU_THROTTLE__Disable(void);
		
		//Ethernet Interface
		void vAPU_ETH__Init(void);
		void vAPU_ETH__Process(void);
		Luint8 u8APU_ETH__Is_LinkUp(void);
		void vAPU_ETH__RxUDP(Luint8 *pu8Buffer, Luint16 u16Length, Luint16 u16DestPort);
		void vAPU_ETH__RxSafeUDP(Luint8 *pu8Payload, Luint16 u16PayloadLength, Luint16 ePacketType, Luint16 u16DestPort, Luint16 u16Fault);
		void vAPU_ETH__10MS_ISR(void);

		//timers
		DLL_DECLARATION void vAPU_TIMERS__10MS_ISR(void);
		DLL_DECLARATION void vAPU_TIMERS__100MS_ISR(void);
		
		//DAQ
		void vAPU_DAQ__Init(void);

		//For WIN32
		#ifdef WIN32
			typedef void (__cdecl * pAPU_WIN32__UpdateData_Callback_FuncType)(Luint8 u8Clutch, Luint8 u8Dir, Luint8 u8Enable, Luint32 u32Freq);
			DLL_DECLARATION void vAPU_WIN32__SetCallback_UpdateData(pAPU_WIN32__UpdateData_Callback_FuncType pFunc);
			void vAPU_WIN32__UpdateData(Luint8 u8Clutch, Luint8 u8Dir, Luint8 u8Enable, Luint32 u32Freq);
			void vAPU_WIN32__Send_Generic_Update(void);

		#endif
		
		
	#endif //#if C_LOCALDEF__LCCM720__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM720__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_AUXPROP_H_


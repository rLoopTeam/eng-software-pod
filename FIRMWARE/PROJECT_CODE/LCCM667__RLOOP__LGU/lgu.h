/**
 * @file		LGU.H
 * @brief		Landing Gear Unit Main Header
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc
 * @st_fileID	LCCM667R0.FILE.001
 */



 
#ifndef _LGU_H_
#define _LGU_H_
	#include <localdef.h>
	#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U

		/*******************************************************************************
		Includes
		*******************************************************************************/
		#include <LCCM667__RLOOP__LGU/lgu__types.h>

		//cross system networking types
		#include <LCCM655__RLOOP__FCU_CORE/NETWORKING/fcu_core__net__packet_types.h>

		//for software fault tree handling
		#include <MULTICORE/LCCM284__MULTICORE__FAULT_TREE/fault_tree__public.h>

		/*******************************************************************************
		Defines
		*******************************************************************************/
		/** Number of actuators being controlled, don't EVER change this */
		#define C_LGU__NUM_ACTUATORS												(4U)

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

			#ifdef WIN32
			/** Win32 Simulation */
			struct
			{

				/** The ADC Value from the MLP */
				Luint16 u16ADCValue;

			}sWin32[C_LGU__NUM_ACTUATORS];

			#endif

            /** N2HET Programs */
            struct
            {

            	/** The Dynamic PWM program index */
            	Luint16 u16ProgIndex;

            }sPWM[C_LGU__NUM_ACTUATORS];

        }TS_LGU__MAIN;


		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		DLL_DECLARATION void vLGU__Init(void);
		DLL_DECLARATION void vLGU__Process(void);


		//timer functions
		DLL_DECLARATION void vLGU_TIMERS__10MS_ISR(void);
		DLL_DECLARATION void vLGU_TIMERS__100MS_ISR(void);
		
		
		//liftmech
		void vLGU_LIFT__Init(void);
		void vLGU_LIFT__Process(void);
		void vLGU_LIFT__Set_Speed(Luint8 u8Actuator, Lfloat32 f32Percent);
		void vLGU_LIFT__Set_Direction(Luint8 u8Actuator, TE_LGU__LIFT_DIRECTIONS eDir);

		//eth
		void vLGU_ETH__Init(void);
		void vLGU_ETH__Process(void);
		Luint8 u8LGU_ETH__Is_LinkUp(void);
		void vLGU_ETH__RxUDP(Luint8 *pu8Buffer, Luint16 u16Length, Luint16 u16DestPort);
		void vLGU_ETH__RxSafeUDP(Luint8 *pu8Payload, Luint16 u16PayloadLength, Luint16 ePacketType, Luint16 u16DestPort, Luint16 u16Fault);
		void vLGU_ETH__10MS_ISR(void);

		//win32 simulation
		#ifdef WIN32
			DLL_DECLARATION void vLGU_WIN32__Update_ADC_Value(Luint8 u8Index, Luint16 u16Value);
			DLL_DECLARATION void vLGU_WIN32__Update_Limit_Switches(Luint8 u8Index, Luint8 u8ExtendLimit, Luint8 u8RetractLimit);
		#endif

	#endif //#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_LGU_H_


/**
 * @file		LGU.H
 * @brief		Landing Gear Control Unit
 * @author		Lachlan, Frank
 * @copyright	rLoop Inc.
 */

 
#ifndef _LGU_H_
#define _LGU_H_
	#include <localdef.h>
	#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U

		/*******************************************************************************
		Defines
		*******************************************************************************/
		//#include <LCCM667__RLOOP__LGU/lgu__types.h>

		//cross system networking types
		#include <LCCM655__RLOOP__FCU_CORE/NETWORKING/fcu_core__net__packet_types.h>

		//for software fault tree handling
		#include <MULTICORE/LCCM284__MULTICORE__FAULT_TREE/fault_tree__public.h>

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


        }TS_LGU__MAIN;


		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		void vLGU__Init(void);
		void vLGU__Process(void);
		void vLGU__RTI_100MS_ISR(void);
		void vLGU__RTI_10MS_ISR(void);

		//eth
		void vLGU_ETH__Init(void);
		void vLGU_ETH__Process(void);
		Luint8 u8LGU_ETH__Is_LinkUp(void);
		void vLGU_ETH__RxUDP(Luint8 *pu8Buffer, Luint16 u16Length, Luint16 u16DestPort);
		void vLGU_ETH__RxSafeUDP(Luint8 *pu8Payload, Luint16 u16PayloadLength, Luint16 ePacketType, Luint16 u16DestPort, Luint16 u16Fault);



	#endif //#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_LGU_H_


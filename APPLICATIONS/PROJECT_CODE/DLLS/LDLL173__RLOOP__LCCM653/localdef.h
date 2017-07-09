#ifndef _LOCALDEF_H_
#define _LOCALDEF_H_

	#include "sil3_generic__cpu.h"

	//our basic defines
	#include <WIN32/BASIC_TYPES/basic_types.h>
	#include <WIN32/DEBUG_PRINTF/debug_printf.h>

	//some placeholders
	#define SAFETOOL_BRANCH(stFuncID)

	//#include "D:\SIL3\DESIGN\RLOOP\FIRMWARE\LFW513__RLOOP__POWER_NODE\MAIN\localdef.h"

/*******************************************************************************
SIL3 - SOFTWARE MULTIPURPOSE FAULT TREE HANDLER
*******************************************************************************/
	#define C_LOCALDEF__LCCM284__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM284__ENABLE_THIS_MODULE == 1U

		//testing options
		#define C_LOCALDEF__LCCM284__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <MULTICORE/LCCM284__MULTICORE__FAULT_TREE/fault_tree.h>

	#endif //C_LOCALDEF__LCCM284__ENABLE_THIS_MODULE

/*******************************************************************************
NUMERICAL MODULE
*******************************************************************************/
	#define C_LOCALDEF__LCCM118__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM118__ENABLE_THIS_MODULE == 1U

		/** set to 1 to include TRIG */
		#define C_LOCALDEF__LCCM118__ENABLE_TRIG							(1U)

		/** enable x^y */
		#define C_LOCALDEF__LCCM118__ENABLE_POWER							(1U)

		/** enable vector math */
		#define C_LOCALDEF__LCCM118__ENABLE_VECTORS							(0U)

		/** DISABLES */
		#define C_LOCALDEF__LCCM118__DISABLE_FILTERING__S16					(0U)
		#define C_LOCALDEF__LCCM118__DISABLE_FILTERING__U16					(0U)
		#define C_LOCALDEF__LCCM118__DISABLE_FILTERING__U32					(0U)
		#define C_LOCALDEF__LCCM118__DISABLE_FILTERING__S32					(0U)
		#define C_LOCALDEF__LCCM118__DISABLE_FILTERING__F32					(0U)

		#define C_LOCALDEF__LCCM118__DISABLE_NUMERICAL__S16					(0U)
		#define C_LOCALDEF__LCCM118__DISABLE_NUMERICAL__U16					(0U)
		#define C_LOCALDEF__LCCM118__DISABLE_NUMERICAL__S32					(0U)
		#define C_LOCALDEF__LCCM118__DISABLE_NUMERICAL__U32					(0U)
		#define C_LOCALDEF__LCCM118__DISABLE_NUMERICAL__F32					(0U)
		#define C_LOCALDEF__LCCM118__DISABLE_NUMERICAL__F64					(0U)

		/** Testing options */
		#define	C_LOCALDEF__LCCM118__ENABLE_TEST_SPEC						(0U)

		//main include
		#include <MULTICORE/LCCM118__MULTICORE__NUMERICAL/numerical.h>
	#endif //C_LOCALDEF__LCCM118__ENABLE_THIS_MODULE


/*******************************************************************************
EEPROM BASIC PARAMETERS
*******************************************************************************/
	#define C_LOCALDEF__LCCM188__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM188__ENABLE_THIS_MODULE == 1U

		/** Use the EEPRARAMS module with an external FLASH */
		#define C_LOCALDEF__LCCM188__USE_WITH_LCCM013						(0U)

		/** Define the number of parameters in the system */
		#define C_LOCALDEF__LCCM188__NUM_PARAMETERS							(128U)

		/** set to 1 if you want to enable CRC's across the entire paramter
		range.  If so you will loose one paramter at the end to store theCRC
		*/
		#define C_LOCALDEF__LCCM188__ENABLE_CRC								(1U)

		/** Offset to start in memory */
		#define C_LOCALDEF__LCCM188__EEPROM_START_OFFSET					(0U)

		/** DISABLES */
		#define C_LOCALDEF__LCCM188__DISABLE__U16							(0U)
		#define C_LOCALDEF__LCCM188__DISABLE__S16							(0U)
		#define C_LOCALDEF__LCCM188__DISABLE__U32							(0U)
		#define C_LOCALDEF__LCCM188__DISABLE__S32							(0U)
		#define C_LOCALDEF__LCCM188__DISABLE__F32							(0U)
		#define C_LOCALDEF__LCCM188__DISABLE__MAC							(0U)

		/** Testing options */
		#define C_LOCALDEF__LCCM188__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <MULTICORE/LCCM188__MULTICORE__EEPROM_PARAMS/eeprom_params.h>

	#endif //C_LOCALDEF__LCCM188__ENABLE_THIS_MODULE

/*******************************************************************************
SOFTWARE BASED CRC
*******************************************************************************/
	#define C_LOCALDEF__LCCM012__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM012__ENABLE_THIS_MODULE == 1U

		//set to 1 to enable test specification code
		#define C_LOCALDEF__LCCM012__ENABLE_TEST_SPEC						(0U)

		//types of CRC
		#define C_LOCALDEF__LCCM012__ENABLE_CRC7							(0U)
		#define C_LOCALDEF__LCCM012__ENABLE_CRC8							(1U)
		#define C_LOCALDEF__LCCM012__ENABLE_CRC16							(1U)

		//set to 1 to enable table based CRC16
		//Note: Not possible on PIC18 due to page sizes
		#define C_LOCALDEF__LCCM012__ENABLE_TABLE_BASED_CRC					(1U)


		#if C_LOCALDEF__LCCM012__ENABLE_CRC16 == 1U

			//if using tables, define any alignment issues
			#if C_LOCALDEF__LCCM012__ENABLE_TABLE_BASED_CRC == 1U
				#ifndef WIN32
					#define C_LOCALDEF__LCCM012__TABLE16_DEF const Luint16 u16SWCRC_CRC_TABLE[] __attribute__ ((aligned (128)))
				#else
					//no alignment possible on win32.
					#define C_LOCALDEF__LCCM012__TABLE16_DEF const Luint16 u16SWCRC_CRC_TABLE[]
				#endif
			#endif //C_LOCALDEF__LCCM012__ENABLE_TABLE_BASED_CRC
		#endif

		#include <MULTICORE/LCCM012__MULTICORE__SOFTWARE_CRC/software_crc.h>

	#endif

/*******************************************************************************
SIL3 - GENERAL PURPOSE SOFTWARE FIFO
*******************************************************************************/
    #define C_LOCALDEF__LCCM357__ENABLE_THIS_MODULE                         (1U)
    #if C_LOCALDEF__LCCM357__ENABLE_THIS_MODULE == 1U

        /** Software FIFO depth size, U8 = 255 or U16 = 65K, not both */
        #define C_LOCALDEF__LCCM357__FIFO_DEPTH_U8                          (0U)
        #define C_LOCALDEF__LCCM357__FIFO_DEPTH_U16                         (1U)

        //testing options
        #define C_LOCALDEF__LCCM357__ENABLE_TEST_SPEC                       (0U)

        //main include file
        #include <MULTICORE/LCCM357__MULTICORE__SOFTWARE_FIFO/software_fifo.h>

    #endif //C_LOCALDEF__LCCM357__ENABLE_THIS_MODULE

/*******************************************************************************
SIL3 - ETHERNET TRANSPORT
*******************************************************************************/
	#define C_LOCALDEF__LCCM325__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM325__ENABLE_THIS_MODULE == 1U

		//various protocol options
		//DHCP Client
		#define C_LOCALDEF__LCCM325__ENABLE_DHCP_CLIENT						(0U)
		//Link Layer Discovery Protocol
		#define C_LOCALDEF__LCCM325__ENABLE_LLDP							(0U)
		#define C_LOCALDEF__LCCM325__ENABLE_SNMP							(0U)

		//UDP Rx
		#define C_LOCALDEF__LCCM325__UDP_RX_CALLBACK(buffer,length,dest_port)	vPWRNODE_NET_RX__RxUDP(buffer, length, dest_port)
		/*vECU_ETHERNET_RX__UDPPacket*/

		//testing options
		#define C_LOCALDEF__LCCM325__ENABLE_TEST_SPEC						(0U)

		//protocol specific options
		//set to 1 to consider port numbers
		#define C_LOCALDEF__LCCM325__PROTO_UDP__ENABLE_PORT_NUMBERS			(1U)

		//main include file
		#include <MULTICORE/LCCM325__MULTICORE__802_3/eth.h>

	#endif //C_LOCALDEF__LCCM325__ENABLE_THIS_MODULE

/*******************************************************************************
SIL3 - SAFETY UDP LAYER
*******************************************************************************/
	#define C_LOCALDEF__LCCM528__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM528__ENABLE_THIS_MODULE == 1U

		/** User Rx Callback
		* Payload, Length, Type, DestPort, Faults
		*/
		#define C_LOCALDEF__LCCM528__RX_CALLBACK(p,l,t,d,f)					vPWRNODE_NET_RX__RxSafeUDP(p,l,t,d,f)

		/** The one and only UDP port we can operate on */
		#define C_LOCALDEF__LCCM528__ETHERNET_PORT_NUMBER					(9110U)
		#define C_LOCALDEF__LCCM528__ETHERNET_PORT_NUMBER2					(9111U)

		/** Vision over SafeUDP Options */
		#define C_LOCALDEF__LCCM528__VISION__ENABLE_TX						(0U)
		#define C_LOCALDEF__LCCM528__VISION__ENABLE_RX						(0U)
		#define C_LOCALDEF__LCCM528__VISION__MAX_BUFFER_SIZE				(640UL * 480UL * 2UL)


		/** Testing Options */
		#define C_LOCALDEF__LCCM528__ENABLE_TEST_SPEC						(0U)

		/** Main include file */
		#include <MULTICORE/LCCM528__MULTICORE__SAFE_UDP/safe_udp.h>
	#endif //#if C_LOCALDEF__LCCM528__ENABLE_THIS_MODULE == 1U

/*******************************************************************************
RLOOP - POWER NODE CORE
*******************************************************************************/
	#define C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U

		/** Enable or disable the PiComms layer */
		#define C_LOCALDEF__LCCM653__ENABLE_PI_COMMS						(0U)

		/** Enable the battery temperature measurement system */
		#define C_LOCALDEF__LCCM653__ENABLE_BATT_TEMP						(0U)

		/** Enable or disable battery temp search */
		#define C_LOCALDEF__LCCM653__ENABLE_BATT_TEMP_SEARCH				(0U)

		/** Enable the BMS Subsystem */
		#define C_LOCALDEF__LCCM653__ENABLE_BMS								(0U)

		/** Enable the PV temp system using TSYS01 */
		#define C_LOCALDEF__LCCM653__ENABLE_NODE_TEMP						(1U)

		/** Node pressure using MS5607 */
		#define C_LOCALDEF__LCCM653__ENABLE_NODE_PRESS						(1U)

		/** Enable the DC/DC converter subsystem */
		#define C_LOCALDEF__LCCM653__ENABLE_DC_CONVERTER					(0U)

		//when the DC/DC is enabled we can implement a timeout timer from
		//heartbeat (or any GS comms)
		#define C_LOCALDEF__LCCM653__ENABLE_DC_CONVERTER__HEART_TIMEOUT		(0U)

		//define the max amount of 100ms increments before the WDT turns off
		#define C_LOCALDEF__LCCM653__DC_CONVERTER__HEART_TIMER_MAX			(30U)

		/** Enable the charger subsystem */
		#define C_LOCALDEF__LCCM653__ENABLE_CHARGER							(0U)

		/** Enable Ethernet */
		#define C_LOCALDEF__LCCM653__ENABLE_ETHERNET						(1U)

		/** Enable Pressure Vesel Repress System */
		#define C_LOCALDEF__LCCM653__ENABLE_PV_REPRESS						(1U)

		/** Enable HE Cooling System */
		#define C_LOCALDEF__LCCM653__ENABLE_COOLING							(10U)


		/** Testing Options */
		#define C_LOCALDEF__LCCM653__ENABLE_TEST_SPEC						(0U)
		
		/** Main include file */
		#include <LCCM653__RLOOP__POWER_CORE/power_core.h>

	#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U


#endif //LOCALDEF

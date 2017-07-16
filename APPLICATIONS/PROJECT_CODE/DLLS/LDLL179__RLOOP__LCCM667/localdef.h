#ifndef _LOCALDEF_H_
#define _LOCALDEF_H_

	#include "sil3_generic__cpu.h"

	//our basic defines
	#include <WIN32/BASIC_TYPES/basic_types.h>
	#include <WIN32/DEBUG_PRINTF/debug_printf.h>

	//some placeholders
	#define SAFETOOL_BRANCH(stFuncID)

	#ifndef WIN32
		#include <../../BOARD_SUPPORT/RM57L843_LAUNCHPAD/rm57l843_launchpad__bsp.h>
		#include <../../BOARD_SUPPORT/NETWORKING/rloop_networking__ports.h>
	#else
		#include <../BOARD_SUPPORT/RM57L843_LAUNCHPAD/rm57l843_launchpad__bsp.h>
		#include <../BOARD_SUPPORT/NETWORKING/rloop_networking__ports.h>
	#endif

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
		#define C_LOCALDEF__LCCM325__UDP_RX_CALLBACK(buffer,length,dest_port)	vLGU_ETH__RxUDP(buffer, length, dest_port)
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
		#define C_LOCALDEF__LCCM528__RX_CALLBACK(p,l,t,d,f)					vLGU_ETH__RxSafeUDP(p,l,t,d,f)

		/** The one and only UDP port we can operate on */
		#define C_LOCALDEF__LCCM528__ETHERNET_PORT_NUMBER					(C_RLOOP_NET_PORT__LGU)
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


/*******************************************************************************
SIL3 - H-BRIDGE MOTOR CONTROLLER WITH PID
*******************************************************************************/
	#define C_LOCALDEF__LCCM492__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM492__ENABLE_THIS_MODULE == 1U

		//num devices (motors)
		#define C_LOCALDEF__LCCM492__NUM_MOTORS								(1U)


		/** Motor Direction A control */
		#define C_LOCALDEF__LCCM492__LATCH_DIR_A(index, x)					{}

		/** Motor Direction B control */
		#define C_LOCALDEF__LCCM492__LATCH_DIR_B(index, x)					{}

		/** Enable / PWM control - Connect to enable pin */
		#define C_LOCALDEF__LCCM492__LATCH_PWM(index, x)					{}



		//Hint at the driver type
		#define C_LOCALDEF__LCCM492__DRIVER_L298N							(1U)

		//testing
		#define C_LOCALDEF__LCCM492__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <MULTICORE/LCCM492__MULTICORE__HBRIDGE_MOTOR/h_bridge.h>
	#endif //#if C_LOCALDEF__LCCM492__ENABLE_THIS_MODULE == 1U

/*******************************************************************************
RLOOP - LANDING GEAR UNIT
*******************************************************************************/
    #define C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE                         (1U)
    #if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U

		#define C_LOCALDEF__LCCM667___PWM_1									N2HET_CHANNEL__1, 2U
		#define C_LOCALDEF__LCCM667___PWM_2									N2HET_CHANNEL__1, 16U
		#define C_LOCALDEF__LCCM667___PWM_3									N2HET_CHANNEL__1, 13U
		#define C_LOCALDEF__LCCM667___PWM_4									N2HET_CHANNEL__1, 9U

		#define C_LOCALDEF__LCCM667___DIR_A1								N2HET_CHANNEL__1, 18U
		#define C_LOCALDEF__LCCM667___DIR_B1								N2HET_CHANNEL__1, 6U
		#define C_LOCALDEF__LCCM667___DIR_A2								N2HET_CHANNEL__1, 14U
		#define C_LOCALDEF__LCCM667___DIR_B2								N2HET_CHANNEL__1, 13U
		#define C_LOCALDEF__LCCM667___DIR_A3								N2HET_CHANNEL__1, 4U
		#define C_LOCALDEF__LCCM667___DIR_B3								N2HET_CHANNEL__1, 27U
		#define C_LOCALDEF__LCCM667___DIR_A4								N2HET_CHANNEL__1, 22U
		#define C_LOCALDEF__LCCM667___DIR_B4								N2HET_CHANNEL__1, 29U

		#define C_LOCALDEF__LCCM667___RETRACT_1								RM4_GIO__PORT_A, 1U
		#define C_LOCALDEF__LCCM667___EXTEND_1								RM4_GIO__PORT_A, 0U
		#define C_LOCALDEF__LCCM667___RETRACT_2								RM4_GIO__PORT_A, 5U
		#define C_LOCALDEF__LCCM667___EXTEND_2								RM4_GIO__PORT_A, 2U
		#define C_LOCALDEF__LCCM667___RETRACT_3								RM4_GIO__PORT_A, 7U
		#define C_LOCALDEF__LCCM667___EXTEND_3								RM4_GIO__PORT_A, 6U
		#define C_LOCALDEF__LCCM667___RETRACT_4								RM4_GIO__PORT_B, 3U
		#define C_LOCALDEF__LCCM667___EXTEND_4								RM4_GIO__PORT_B, 2U


        /** Testing Options */
        #define C_LOCALDEF__LCCM667__ENABLE_TEST_SPEC                       (0U)

        /** Main include file */
        #include <LCCM667__RLOOP__LGU/lgu.h>
    #endif //#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U


#endif //LOCALDEF

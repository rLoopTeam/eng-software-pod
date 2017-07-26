#ifndef LOCALDEF_H_
#define LOCALDEF_H_

/*lint -e950*/

	//The launchpad
#ifndef WIN32
	#include <../../BOARD_SUPPORT/RM57L843_LAUNCHPAD/rm57l843_launchpad__bsp.h>
	#include <../../BOARD_SUPPORT/NETWORKING/rloop_networking__ports.h>
#else
	#include <../BOARD_SUPPORT/RM57L843_LAUNCHPAD/rm57l843_launchpad__bsp.h>
	#include <../BOARD_SUPPORT/NETWORKING/rloop_networking__ports.h>
#endif

//disable any BSP referenced
#ifdef C_LOCALDEF__LCCM282__ENABLE_THIS_MODULE
	#undef C_LOCALDEF__LCCM282__ENABLE_THIS_MODULE
	#undef DEBUG_PRINT
#endif

/*******************************************************************************
SIL3 - RM48/RM57 - SCI / LIN Module
*******************************************************************************/
	#define C_LOCALDEF__LCCM282__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM282__ENABLE_THIS_MODULE == 1U

		//if you have to do debugging
		#define DEBUG_PRINT(x)
		//vRM4_SCI_HELPERS__DisplayText(SCI_CHANNEL__2, x, 100)

		//enable interrupts, else use polling Mode
		#define C_LOCALDEF__LCCM282__ENABLE_INTERRUPTS						(0U)

		/** Switch on DMA functions */
		#define C_LOCALDEF__LCCM282__ENABLE_DMA								(0U)

		//determine which SCI module to enable
		//SCI1 shares pins with EMAC
		#define C_LOCALDEF__LCCM282__ENABLE_SCI_1							(0U)

		//SCI 2 is also LIN and uses the LIN pins on ZWT Package
		//SCI2 is USB debug on HDK
		#define C_LOCALDEF__LCCM282__ENABLE_SCI_2							(0U)

        //SCI3 only on RM57, Launchpad Boosterpack Site 1
        #define C_LOCALDEF__LCCM282__ENABLE_SCI_3                           (1U)

        //SCI4 only on RM57
        #define C_LOCALDEF__LCCM282__ENABLE_SCI_4                           (0U)


		//testing
		#define C_LOCALDEF__LCCM282__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <RM4/LCCM282__RM4__SCI/rm4_sci.h>

	#else
		#define DEBUG_PRINT(x)
	#endif //C_LOCALDEF__LCCM282__ENABLE_THIS_MODULE

/*******************************************************************************
RM4 GIO MODULE
*******************************************************************************/
	#define C_LOCALDEF__LCCM133__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM133__ENABLE_THIS_MODULE == 1U

		#define C_LOCALDEF__LCCM133__ENABLE_INTERRUPTS						(0U)

		#if C_LOCALDEF__LCCM133__ENABLE_INTERRUPTS == 1U

			#define GIOA_PIN_0_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOA_PIN_1_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOA_PIN_2_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOA_PIN_3_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOA_PIN_4_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOA_PIN_5_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOA_PIN_6_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOA_PIN_7_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOB_PIN_0_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOB_PIN_1_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOB_PIN_2_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOB_PIN_3_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOB_PIN_4_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOB_PIN_5_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOB_PIN_6_ISR()										vRM4_GIO_ISR__DefaultRoutine()
			#define GIOB_PIN_7_ISR()										vRM4_GIO_ISR__DefaultRoutine()

		#endif //#if C_LOCALDEF__LCCM133__ENABLE_INTERRUPTS == 1U

		//Testing options
		#define C_LOCALDEF__LCCM133__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <RM4/LCCM133__RM4__GIO/rm4_gio.h>

	#endif //#if C_LOCALDEF__LCCM133__ENABLE_THIS_MODULE == 1

/*******************************************************************************
RM4 - RTI MODULE
*******************************************************************************/
	#define C_LOCALDEF__LCCM124__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM124__ENABLE_THIS_MODULE == 1U

		//globally switch on the WDT
		#define C_LOCALDEF__LCCM124__ENABLE_WDT								(0U)

		/** RTI CLOCK FREQUENCY
		 * Based on our standard system, valid values are div(2,4,8):
		 * 100 	(100MHZ)
		 * 75 	(75MHZ - ONLY ON RM57)
		 * 50	(50MHZ)
		 * 25	(25MHZ)
		 * */
		#define C_LOCALDEF__LCCM124__RTI_CLK_FREQ							(75U)

		/** RTCLK0 feeds counter 0 and is used for general purpose compare times */
		#define C_LOCALDEF__LCCM124__RTI_COUNTER0_PRESCALER					(10U)

		/** RTCLK1 feeds counter 1 and can be used for 64bit timing */
		#define C_LOCALDEF__LCCM124__RTI_COUNTER1_PRESCALER					(1U)


		//Sets up the time periods for each compare. Must be defined in microSeconds.
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_0_PERIOD_US 				(10000U)
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_1_PERIOD_US 				(100000U)
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_2_PERIOD_US 				(1000000U)
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_3_PERIOD_US 				(1000000U)

		//these are the interrupt handlers which should point
		//to a function, otherwise leave as default
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_0_CALLBACK					vFCU__RTI_10MS_ISR()
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_1_CALLBACK					vFCU__RTI_100MS_ISR()
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_2_CALLBACK	 				vRM4_RTI_INTERRUPTS__DefaultCallbackHandler()
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_3_CALLBACK	 				vRM4_RTI_INTERRUPTS__DefaultCallbackHandler()

		//Testing options
		#define C_LOCALDEF__LCCM124__ENABLE_TEST_SPEC	 					(0U)

		#include <RM4/LCCM124__RM4__RTI/rm4_rti.h>

	#endif //#if C_LOCALDEF__LCCM124__ENABLE_THIS_MODULE == 1U

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
		#define C_LOCALDEF__LCCM325__UDP_RX_CALLBACK(buffer,length,dest_port)	vFCU_NET_RX__RxUDP(buffer, length, dest_port)
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
		#define C_LOCALDEF__LCCM528__RX_CALLBACK(p,l,t,d,f)					vFCU_NET_RX__RxSafeUDP(p,l,t,d,f)

		/** The one and only UDP port we can operate on */
		#define C_LOCALDEF__LCCM528__ETHERNET_PORT_NUMBER					(C_RLOOP_NET_PORT__FCU)
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
RLOOP - FLIGHT CONTROL UNIT - CORE
*******************************************************************************/
    #define C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE                         (1U)
    #if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U

        //special needs for DAQ compile time
        #include <LCCM655__RLOOP__FCU_CORE/fcu_core__daq_settings.h>

        /** Data Acqusition System */
        #define C_LOCALDEF__LCCM655__ENABLE_DAQ                             (0U)

        /** Enable or disable the PiComms layer */
        #define C_LOCALDEF__LCCM655__ENABLE_PI_COMMS                        (0U)

        /** Enable the OptoNCDT laser interface */
        #define C_LOCALDEF__LCCM655__ENABLE_LASER_OPTONCDT                  (0U)

        /** Enable the Laser contrast sensors */
        #define C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST                  (0U)

        /** Laser Distance Unit */
        #define C_LOCALDEF__LCCM655__ENABLE_LASER_DISTANCE                  (1U)

        /** Enable accel subsystem */
        #define C_LOCALDEF__LCCM655__ENABLE_ACCEL                           (0U)

        /** Enable the braking subsystems */
        #define C_LOCALDEF__LCCM655__ENABLE_BRAKES                          (0U)
        #define C_LOCALDEF__LCCM655__ENABLE_DEBUG_BRAKES                    (0U)

        /** Enable the throttle control */
        #define C_LOCALDEF__LCCM655__ENABLE_THROTTLE                        (0U)

        /** Enable the ASI_RS485 */
        #define C_LOCALDEF__LCCM655__ENABLE_ASI_RS485                       (0U)

        /** Enable the pusher detection system */
        #define C_LOCALDEF__LCCM655__ENABLE_PUSHER                          (0U)

        /** Ethernet Systems */
        #define C_LOCALDEF__LCCM655__ENABLE_ETHERNET                        (1U)

        /** SpaceX Telemetry Requirements Enable */
        #define C_LOCALDEF__LCCM655__ENABLE_SPACEX_TELEMETRY                (0U)

        /** Serial comms to and from the LGU */
        #define C_LOCALDEF__LCCM655__LGU_COMMS_SYSTEM                       (0U)

        /**Geom system */
        #define C_LOCALDEF__LCCM655__ENABLE_GEOM                            (0U)

        /** Flight control specifics */
        #define C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL                  (0U)

            /** Main SM */
            #define C_LOCALDEF__LCCM655__ENABLE_MAIN_SM                         (0U)

            //Pitch/Roll/Yaw
            #define C_LOCALDEF__LCCM655__ENABLE_FCTL_ORIENTATION                (0U)

            //Brake Controller
            #define C_LOCALDEF__LCCM655__ENABLE_FCTL_BRAKE_CONTROL              (0U)

            //Contrast Sensor Navigation
            #define C_LOCALDEF__LCCM655__ENABLE_FCTL_CONTRAST_NAV               (0U)

            //hover engine drag modelling
            #define C_LOCALDEF__LCCM655__ENABLE_FCTL_HE_DRAG                    (0U)

            //aero drag modelling
            #define C_LOCALDEF__LCCM655__ENABLE_FCTL_AERO_DRAG                  (0U)

            /** Allow us to control the gimbals and include in calculations */
            #define C_LOCALDEF__LCCM655__ENABLE_GIMBAL_CONTROL                  (0U)

            /** Track Database */
            #define C_LOCALDEF__LCCM655__ENABLE_TRACK_DB                        (0U)

            /** Pod Health System */
            #define C_LOCALDEF__LCCM655__ENABLE_POD_HEALTH                      (0U)


            /** Hover Engine Control */
            #define C_LOCALDEF__LCCM655__ENABLE_HOVERENGINES_CONTROL            (0U)

            /** Drive Pod Control */
            #define C_LOCALDEF__LCCM655__ENABLE_DRIVEPOD_CONTROL                (0U)

            /** Eddy Brakes Control */
            #define C_LOCALDEF__LCCM655__ENABLE_EDDY_BRAKES                     (0U)

            /** Lift Mechanism Control */
            #define C_LOCALDEF__LCCM655__ENABLE_LIFT_MECH_CONTROL               (0U)

            /** Navigation function */
            #define C_LOCALDEF__LCCM655__ENABLE_FCTL_NAVIGATION                 (0U)

            /** Control Aux Propulsion */
            #define C_LOCALDEF__LCCM655__ENABLE_AUX_PROPULSION_CONTROL          (0U)

            /** Enable PID for the Brakes */
            #define C_LOCALDEF__LCCM655__ENABLE_BRAKEPID                        (0U)

            /** Enable Cooling control */
            #define C_LOCALDEF__LCCM655__ENABLE_COOLING_CONTROL                 (0U)

            /** Enable fault handling out ethernet */
            #define C_LOCALDEF__LCCM655__ENABLE_ETHERNET_FAULTS                 (0U)

        /** ADC Sample Limits */
        #define C_LOCALDEF__LCCM655__ADC_SAMPLE__LOWER_BOUND                    (300U)
        #define C_LOCALDEF__LCCM655__ADC_SAMPLE__UPPER_BOUND                    (3000U)

        /** Testing Options */
        #define C_LOCALDEF__LCCM655__ENABLE_TEST_SPEC                       (0U)

        /** Main include file */
        #include <LCCM655__RLOOP__FCU_CORE/fcu_core.h>
    #endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U

#endif /* LOCALDEF_H_ */

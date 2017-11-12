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

/*******************************************************************************
SIL3 - RM4 ADC DRIVER
*******************************************************************************/
    #define C_LOCALDEF__LCCM414__ENABLE_THIS_MODULE                         (1U)
    #if C_LOCALDEF__LCCM414__ENABLE_THIS_MODULE == 1U

        /** Vref constant used for voltage calc 3.3/(2^12)*/
        #define C_LOCALDEF__LCCM414__VREF_CONSTANT                          (0.0008056640625F)

        /** The number of ADC channels (modules) being used
         * Keep a 1 for now
         */
        #define C_LOCALDEF__LCCM414__NUM_ADC_MODULES                        (1U)

        /** Continuous Conversion Mode:  When enabled the ADC
         * Will always keep making samples of the configured channels
         */
        #define C_LOCALDEF__LCCM414__ENABLE_CONTINUOUS_CONVERSION           (0U)

        /** Averaging is enabled across all channels.
         * It can consume serious CPU time for a fully enabled ADC
         */
        #define C_LOCALDEF__LCCM414__ENABLE_AVERAGING                       (1U)

        /** The number of samples for each channels ADC averager */
        #define C_LOCALDEF__LCCM414__AVERAGE_MAX_SAMPLES                    (4U)


        /** Determine which of ADC1 to enable */
        #define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN0                       (1U)
        #define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN1                       (1U)
        #define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN2                       (0U)
        #define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN3                       (0U)
        #define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN4                       (0U)
        #define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN5                       (0U)
        #define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN6                       (0U)
        #define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN7                       (0U)
        #define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN8                       (0U)
        #define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN9                       (0U)
        #define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN10                      (0U)
        #define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN11                      (0U)
        #define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN12                      (0U)
        #define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN13                      (0U)
        #define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN14                      (0U)
        #define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN15                      (0U)
        #define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN16                      (0U)
        #define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN17                      (0U)
        #define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN18                      (1U)
        #define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN19                      (1U)
        #define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN20                      (1U)
        #define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN21                      (1U)
        #define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN22                      (0U)
        #define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN23                      (0U)

        /** The number of connected devices to the ADC's
         * We store a local copy of our ADC results in a user addressable
         * structure to reduce the complexity of finding our result
         * Value can be from 1 to 24
         */
        #define C_LOCALDEF__LCCM414__NUM_CONNECTED_DEVICES                  (4U)

        /** For each device we determine the location of the device within our strucrture
         * You must configure an index from 0 to NUM_CONNECTED_DEVICES - 1
         * No two units may have the same index
         * Example MAP ADC1_IN0 to Device (1)
         */
        #define C_LOCALDEF__LCCM414__ADC1_IN0__INDEX                        (0U)
        #define C_LOCALDEF__LCCM414__ADC1_IN1__INDEX                        (1U)
        #define C_LOCALDEF__LCCM414__ADC1_IN2__INDEX                        (2U)
        #define C_LOCALDEF__LCCM414__ADC1_IN3__INDEX                        (0U)
        #define C_LOCALDEF__LCCM414__ADC1_IN4__INDEX                        (0U)
        #define C_LOCALDEF__LCCM414__ADC1_IN5__INDEX                        (0U)
        #define C_LOCALDEF__LCCM414__ADC1_IN6__INDEX                        (0U)
        #define C_LOCALDEF__LCCM414__ADC1_IN7__INDEX                        (0U)
        #define C_LOCALDEF__LCCM414__ADC1_IN8__INDEX                        (0U)
        #define C_LOCALDEF__LCCM414__ADC1_IN9__INDEX                        (0U)
        #define C_LOCALDEF__LCCM414__ADC1_IN10__INDEX                       (0U)
        #define C_LOCALDEF__LCCM414__ADC1_IN11__INDEX                       (0U)
        #define C_LOCALDEF__LCCM414__ADC1_IN12__INDEX                       (0U)
        #define C_LOCALDEF__LCCM414__ADC1_IN13__INDEX                       (0U)
        #define C_LOCALDEF__LCCM414__ADC1_IN14__INDEX                       (0U)
        #define C_LOCALDEF__LCCM414__ADC1_IN15__INDEX                       (0U)
        #define C_LOCALDEF__LCCM414__ADC1_IN16__INDEX                       (0U)
        #define C_LOCALDEF__LCCM414__ADC1_IN17__INDEX                       (0U)

        //MLP1
        #define C_LOCALDEF__LCCM414__ADC1_IN18__INDEX                       (0U)
        //MLP2
        #define C_LOCALDEF__LCCM414__ADC1_IN19__INDEX                       (1U)
        //MLP3
        #define C_LOCALDEF__LCCM414__ADC1_IN20__INDEX                       (2U)
        //MLP4
        #define C_LOCALDEF__LCCM414__ADC1_IN21__INDEX                       (3U)


        #define C_LOCALDEF__LCCM414__ADC1_IN22__INDEX                       (0U)
        #define C_LOCALDEF__LCCM414__ADC1_IN23__INDEX                       (0U)

        /** Enable voltage conversion to return the voltage value
         * for a device.  This reduces the external workload to compute the
         * voltage based on VREF
         */
        #define C_LOCALDEF__LCCM414__ENABLE_VOLTAGE_CALC                    (1U)

        /** Use interrupts */
        #define C_LOCALDEF__LCCM414__ENABLE_INTERRUPTS                      (0U)

        //testing
        #define C_LOCALDEF__LCCM414__ENABLE_TEST_SPEC                       (0U)

        //main include file
        #include <RM4/LCCM414__RM4__ADC/rm4_adc.h>
    #endif

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
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_0_CALLBACK					vLGU_TIMERS__10MS_ISR()
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_1_CALLBACK					vLGU_TIMERS__100MS_ISR()
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_2_CALLBACK	 				vRM4_RTI_INTERRUPTS__DefaultCallbackHandler()
		#define C_LOCALDEF__LCCM124__RTI_COMPARE_3_CALLBACK	 				vRM4_RTI_INTERRUPTS__DefaultCallbackHandler()

		//Testing options
		#define C_LOCALDEF__LCCM124__ENABLE_TEST_SPEC	 					(0U)

		#include <RM4/LCCM124__RM4__RTI/rm4_rti.h>

	#endif //#if C_LOCALDEF__LCCM124__ENABLE_THIS_MODULE == 1U



/*******************************************************************************
SIL3 - 802.3 ETHERNET
*******************************************************************************/
    #define C_LOCALDEF__LCCM325__ENABLE_THIS_MODULE                         (1U)
    #if C_LOCALDEF__LCCM325__ENABLE_THIS_MODULE == 1U

        /** On Xilinx Architectures we can use NPI burst transfers */
        #define C_LOCALDEF__LCCM325__XILINX_USE_NPI_INTERFACE               (0U)

        //ARP Configuration
        /** Enable ARP Requesting */
        #define C_LOCALDEF__LCCM325__ARP__ENABLE_REQUEST                    (0U)
        /** Enable ARP Cache */
        #define C_LOCALDEF__LCCM325__ARP__ENABLE_CACHE                      (0U)
        /** If caching is enabled what is the maximum ARP cache size (entries) */
        #define C_LOCALDEF__LCCM325__ARP__MAX_CACHE_SIZE                    (4U)
        /** If caching is enabled how long until the entry expires in 100ms
         * The default is 300 seconds */
        #define C_LOCALDEF__LCCM325__ARP__ENTRY_EXPIRE_X100MS               (3000U)
        /** The amount of time from when a request is sent to a timeout occurring
         * Currently set at 3 seconds. */
        #define C_LOCALDEF__LCCM325__ARP__RESPONSE_TIMEOUT_X100MS           (30U)

        //DNS Client Configuration
        /** Enable the DNS Client for DNS lookup */
        #define C_LOCALDEF__LCCM325__DNS__ENABLE_DNS_CLIENT                 (0U)
        /** Maximum number of host names in the cache */
        #define C_LOCALDEF__LCCM325__DNS__MAX_CACHE_SIZE                    (4U)


        //DHCP Client Configuration
        /** DHCP Client */
        #define C_LOCALDEF__LCCM325__DHCP__ENABLE_DHCP_CLIENT               (0U)

        //TCP/IP Settings
        /** TCP/IP Module Enable*/
        #define C_LOCALDEF__LCCM325__TCPIP__ENABLE_TCPIP                    (0U)
        /** New TCP data callback */
        #define M_LOCALDEF__LCCM325__TCPIP__NEW_RX_DATA(id, buffer, length) {}



        //various protocol options
        /** Link Layer Discovery Protocol */
        #define C_LOCALDEF__LCCM325__ENABLE_LLDP                            (0U)
        /** Simple Network Management Protocol */
        #define C_LOCALDEF__LCCM325__ENABLE_SNMP                            (0U)

        //UDP Rx
        #define C_LOCALDEF__LCCM325__UDP_RX_CALLBACK(buffer,length,port)    vLGU_ETH__RxUDP(buffer, length, port)

        //testing options
        #define C_LOCALDEF__LCCM325__ENABLE_TEST_SPEC                       (0U)


        //protocol specific options
        //set to 1 to consider port numbers
        #define C_LOCALDEF__LCCM325__PROTO_UDP__ENABLE_PORT_NUMBERS         (1U)

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


        /** Clutch control*/
        #define C_LOCALDEF__LCCM667__ENABLE_CLUTCHES                        (1U)

        /** Lift Mechanisms*/
        #define C_LOCALDEF__LCCM667__LGU_ENABLE_LIFT                        (0U)

        /** MLP Systems */
        #define C_LOCALDEF__LCCM667__ENABLE_MLP                             (1U)

        /** Testing Options */
        #define C_LOCALDEF__LCCM667__ENABLE_TEST_SPEC                       (0U)

        /** Main include file */
        #include <LCCM667__RLOOP__LGU/lgu.h>
    #endif //#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U

#endif /* LOCALDEF_H_ */

/**
 * @file		FCU_CORE__LOCALDEF.H
 * @brief		Local definitions template for the FCU
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 * @st_fileID	LCCM655R0.FILE.002
 */


#if 0

/*******************************************************************************
RLOOP - FLIGHT CONTROL UNIT - CORE
*******************************************************************************/
	#define C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U

		//special needs for DAQ compile time
		#include <LCCM655__RLOOP__FCU_CORE/fcu_core__daq_settings.h>

		/** Data Acqusition System */
		#define C_LOCALDEF__LCCM655__ENABLE_DAQ								(1U)

		/** Enable or disable the PiComms layer */
		#define C_LOCALDEF__LCCM655__ENABLE_PI_COMMS						(0U)

		/** Enable the OptoNCDT laser interface */
		#define C_LOCALDEF__LCCM655__ENABLE_LASER_OPTONCDT					(1U)

		/** Enable the Laser contrast sensors */
		#define C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST					(1U)

		/** Laser Distance Unit */
		#define C_LOCALDEF__LCCM655__ENABLE_LASER_DISTANCE					(1U)

		/** Enable accel subsystem */
		#define C_LOCALDEF__LCCM655__ENABLE_ACCEL							(0U)

		/** Enable the braking subsystems */
		#define C_LOCALDEF__LCCM655__ENABLE_BRAKES							(0U)
		#define C_LOCALDEF__LCCM655__ENABLE_DEBUG_BRAKES					(0U)

		/** Enable the throttle control */
		#define C_LOCALDEF__LCCM655__ENABLE_THROTTLE						(1U)

		/** Enable the ASI_RS485 */
		#define C_LOCALDEF__LCCM655__ENABLE_ASI_RS485						(1U)

		/** Enable the pusher detection system */
		#define C_LOCALDEF__LCCM655__ENABLE_PUSHER							(0U)

		/** Ethernet Systems */
		#define C_LOCALDEF__LCCM655__ENABLE_ETHERNET						(1U)

		/** SpaceX Telemetry Requirements Enable */
		#define C_LOCALDEF__LCCM655__ENABLE_SPACEX_TELEMETRY				(1U)

		/** Serial comms to and from the LGU */
		#define C_LOCALDEF__LCCM655__LGU_COMMS_SYSTEM						(1U)

		/** Flight control specifics */
		#define C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL					(1U)

			//Pitch/Roll/Yaw
			#define C_LOCALDEF__LCCM655__ENABLE_FCTL_ORIENTATION				(1U)

			//Brake Controller
			#define C_LOCALDEF__LCCM655__ENABLE_FCTL_BRAKE_CONTROL				(1U)

			//Contrast Sensor Navigation
			#define C_LOCALDEF__LCCM655__ENABLE_FCTL_CONTRAST_NAV				(1U)

			//hover engine drag modelling
			#define C_LOCALDEF__LCCM655__ENABLE_FCTL_HE_DRAG					(1U)

			//aero drag modelling
			#define C_LOCALDEF__LCCM655__ENABLE_FCTL_AERO_DRAG					(1U)

			/** Allow us to control the gimbals and include in calculations */
			#define C_LOCALDEF__LCCM655__ENABLE_GIMBAL_CONTROL					(1U)

			/** Track Database */
			#define C_LOCALDEF__LCCM655__ENABLE_TRACK_DB						(1U)

			/** Pod Health System */
			#define C_LOCALDEF__LCCM655__ENABLE_POD_HEALTH						(1U)


		/** ADC Sample Limits */
		#define C_LOCALDEF__LCCM655__ADC_SAMPLE__LOWER_BOUND					(300U)
		#define C_LOCALDEF__LCCM655__ADC_SAMPLE__UPPER_BOUND					(3000U)

		/** Testing Options */
		#define C_LOCALDEF__LCCM655__ENABLE_TEST_SPEC						(0U)
		
		/** Main include file */
		#include <LCCM655__RLOOP__FCU_CORE/fcu_core.h>
	#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U

#endif //#if 0


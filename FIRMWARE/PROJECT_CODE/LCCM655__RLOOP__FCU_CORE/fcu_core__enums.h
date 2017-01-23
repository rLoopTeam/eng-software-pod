/**
 * @file		FCU_CORE__ENUMS.H
 * @brief		Flight control code constants
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 */
#ifndef RLOOP_LCCM655__RLOOP__FCU_CORE_FCU_CORE__ENUMS_H_
#define RLOOP_LCCM655__RLOOP__FCU_CORE_FCU_CORE__ENUMS_H_



	/** For transmitting to the LGU*/
	typedef enum
	{

		/** IDLE */
		LGU_COMMS_STATE__IDLE = 0U,

		/** beign a transmission */
		LGU_COMMS_STATE__TX_BEGIN,

		/** process the transmision */
		LGU_COMMS_STATE__TX_PROCESS,

		/** process the new Rx packet*/
		LGU_COMMS_STATE__PROCESS_RX

	}E_LGU_COMMS_STATE_T;


	/** OptoNCDT Laser Positions
	 *  must be in order from A0:2, B0:2
	 *  */
	typedef enum
	{

		LASER_OPTO__HEIGHT_FL = 0U,
		LASER_OPTO__HEIGHT_FR = 1U,
		LASER_OPTO__HEIGHT_RL = 2U,
		LASER_OPTO__HEIGHT_RR = 3U,
		LASER_OPTO__IBEAM_FWD = 4U,
		LASER_OPTO__IBEAM_AFT = 5U,
		LASER_OPTO__NUM = 6U

	}E_FCU__LASER_OPTO__INDEX_T;

	/** Laser contrast sensors */
	typedef enum
	{
		LASER_CONT__FWD = 0U,

		LASER_CONT__MID = 1U,

		LASER_CONT__AFT = 2U,

		LASER_CONT__MAX = 3U

	}E_FCU__LASER_CONT_INDEX_T;

	/** enum type for the left or right brakes */
	typedef enum
	{
		/** left brake */
		FCU_BRAKE__LEFT = 0U,

		/** Right hand brake */
		FCU_BRAKE__RIGHT = 1U,


		FCU_BRAKE__MAX_BRAKES = 2U


	}E_FCU__BRAKE_INDEX_T;

	/** Brake limit switch enums */
	typedef enum
	{
		/** Fully extended limit switch */
		BRAKE_SW__EXTEND = 0U,

		/** Fully retracted switch */
		BRAKE_SW__RETRACT = 1U,

		BRAKE_SW__MAX_SWITCHES = 2U

	}E_FCU__BRAKE_LIMSW_INDEX_T;

	/** The final swtich state, and indeed any switch state */
	typedef enum
	{

		/** Big issue, unknown state type */
		SW_STATE__UNKNOWN = 0U,

		/** The switch is closed, physically but maybe not electrically */
		SW_STATE__CLOSED,

		/** The switch is open */
		SW_STATE__OPEN


	}E_FCU__SWITCH_STATE_T;


	/** Ground station commands for throttle layer  */
	// (added by @gsweriduk on 23 NOV 2016)
	// Partial list, see http://confluence.rloop.org/display/SD/Commands+from+Ground+Station+to+rPod

	typedef enum
	{
		STATIC_HOVERING,
		RELEASE_STATIC_HOVERING,
		SET_HEX_SPEED,
		SET_ALL_HE_SPEED
	} E_GS_COMMANDS;

	/** Flight Control Unit Modes  */
	// (added by @gsweriduk on 23 NOV 2016)
	// Obtained on 11 NOV 2016 from FCU Spec http://confluence.rloop.org/display/SD/1.+Determine+Operating+Mode

	typedef enum
	{
		STOPPED_UNLIFTED,
		STOPPED_LIFTED,
		AUXILIARY_PROPULSION,
		UNEXPECTED_MOVE_ON_WHEELS,
		PUSHER_INTERLOCK_MODE,
		RUN_MODE_FLIGHT,
		RUN_MODE_STANDBY,
		RUN_MODE_STOPPED,
		CONTROLLED_EMERGENCY_BRAKE,
		FAIL_SAFE_BRAKE
	} E_FCU_MODES;

	/** State types for the THROTTLE state machine */
	typedef enum
	{

		/** Waiting here */
		THROTTLE_STATE__IDLE = 0U,

		/** Run mode, allow the HE's to throttle up */
		THROTTLE_STATE__RUN,

		/** Step command(s) to the HEs */
		THROTTLE_STATE__STEP,

		/** Ramp command(s) to the HEs */
		THROTTLE_STATE__RAMP_UP,

		/** Ramp command(s) to the HEs */
		THROTTLE_STATE__RAMP_DOWN,

		/** Mode to the next scanning index */
		THROTTLE_STATE__INC_INDEX,

		/** an error was encountered */
		THROTTLE_STATE__ERROR,

	} E_THROTTLE_STATES_T;


#endif /* RLOOP_LCCM655__RLOOP__FCU_CORE_FCU_CORE__ENUMS_H_ */

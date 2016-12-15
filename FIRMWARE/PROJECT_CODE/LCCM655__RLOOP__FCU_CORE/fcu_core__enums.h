/**
 * @file		FCU_CORE__ENUMS.H
 * @brief		Flight control code constants
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 */
#ifndef RLOOP_LCCM655__RLOOP__FCU_CORE_FCU_CORE__ENUMS_H_
#define RLOOP_LCCM655__RLOOP__FCU_CORE_FCU_CORE__ENUMS_H_



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
	// (added by @gsweriduk on 25 NOV 2016)

	typedef enum
	{

		// do nothing
		THROTTLE_STATE__IDLE = 0U,

		// an error was encountered
		THROTTLE_STATE__ERROR,

		// init the device, force a reset
		THROTTLE_STATE__INIT,

		// Ramp command(s) to the HEs
		THROTTLE_STATE__RAMP_COMMAND,

		// Step command(s) to the HEs
		THROTTLE_STATE__STEP_COMMAND,

		// Write throttle command(s) to the DAC, substate of RAMP and STEP
		THROTTLE_STATE__WRITE_TO_DAC,

		// Waiting for the start of a conversion, substate of I/O
		THROTTLE_STATE__WAITING,

		// Issue the conversion command, substate of I/O
		//THROTTLE_STATE__BEGIN_SAMPLE,

		//  No change since last command was given
		THROTTLE_STATE__HOLD


	} E_THROTTLE_STATES_T;


#endif /* RLOOP_LCCM655__RLOOP__FCU_CORE_FCU_CORE__ENUMS_H_ */

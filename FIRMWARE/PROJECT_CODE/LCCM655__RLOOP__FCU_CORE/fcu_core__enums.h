/**
 * @file		FCU_CORE__ENUMS.H
 * @brief		Flight control code constatants
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


#endif /* RLOOP_LCCM655__RLOOP__FCU_CORE_FCU_CORE__ENUMS_H_ */

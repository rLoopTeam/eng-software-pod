/**
 * @file		AUXPROP__TYPES.H
 * @brief		APU Types
 * @author		Lachlan Grogan
 * @st_fileID	LCCM720R0.FILE.003
 */

#ifndef _AUXPROP__TYPES_H_
#define _AUXPROP__TYPES_H_
	
	/** Side defintions */
	typedef enum
	{
		/** Left */
		AUXPROP_SIDE__LEFT = 0,
		
		/** Right */
		AUXPROP_SIDE__RIGHT
		
	}TE_RLOOP_AUXPROP__SIDE;
	

	/** Clutch States */
	typedef enum
	{
		CLUTCH_STATE__DISENGAGED = 0U,

		CLUTCH_STATE__ENGAGED = 1U

	}TE_RLOOP_AUXPROP__CLUTCH_STATE;

	/** Throttle Directions */
	typedef enum
	{

		/** Reverse */
		THROTTLE_DIR__REVERSE = 0U,

		/** Forward */
		THROTTLE_DIR__FORWARD = 1U

	}TE_RLOOP_AUXPROP__THROTTLE_DIR;

#endif //_AUXPROP__TYPES_H_


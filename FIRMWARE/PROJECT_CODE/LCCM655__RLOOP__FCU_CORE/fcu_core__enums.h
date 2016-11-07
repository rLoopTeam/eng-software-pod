/**
 * @file		FCU_CORE__ENUMS.H
 * @brief		Flight control code constatants
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 */
#ifndef RLOOP_LCCM655__RLOOP__FCU_CORE_FCU_CORE__ENUMS_H_
#define RLOOP_LCCM655__RLOOP__FCU_CORE_FCU_CORE__ENUMS_H_


	/** enum type for the left or right brakes */
	typedef enum
	{
		/** left brake */
		FCU_BRAKE__LEFT = 0U,

		/** Right hand brake */
		FCU_BRAKE__RIGHT = 1U,


		FCU_BRAKE__MAX_BRAKES,


	}E_FCU__BRAKE_INDEX_T;




#endif /* RLOOP_LCCM655__RLOOP__FCU_CORE_FCU_CORE__ENUMS_H_ */

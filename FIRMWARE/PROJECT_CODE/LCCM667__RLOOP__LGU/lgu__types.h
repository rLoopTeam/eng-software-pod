/*
 * lgu__types.h
 *
 *  Created on: Jul 30, 2017
 *      Author: Lachlan
 */

#ifndef LCCM667__RLOOP__LGU_LGU__TYPES_H_
#define LCCM667__RLOOP__LGU_LGU__TYPES_H_

	/** Lifting directions */
	typedef enum
	{
		/** Actuator Off */
		LIFT_DIR__NONE = 0U,

		/** Raise the actuator */
		LIFT_DIR__RETRACT = 1U,

		/** Lower the actuator*/
		LIFT_DIR__EXTEND = 2U


	}TE_LGU__LIFT_DIRECTIONS;



#endif /* LCCM667__RLOOP__LGU_LGU__TYPES_H_ */

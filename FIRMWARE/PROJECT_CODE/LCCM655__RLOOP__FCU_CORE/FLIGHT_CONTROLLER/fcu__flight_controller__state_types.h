/*
 * fcu__flight_controller__state_types.h
 *
 *  Created on: 19Aug.,2017
 *      Author: Lachlan
 */

#ifndef __FLIGHT_CONTROLLER__STATE_TYPES_H_
#define __FLIGHT_CONTROLLER__STATE_TYPES_H_

	/** Pod state types */
	typedef enum
	{
		POD_STATE__NULL = 0U,

		POD_STATE__INIT,

		POD_STATE__IDLE,

		POD_STATE__TEST_MODE,

		POD_STATE__DRIVE,

		POD_STATE__ARMED_WAIT,

		POD_STATE__FLIGHT_PREP,

		POD_STATE__READY,

		POD_STATE__ACCEL,

		POD_STATE__COAST_INTERLOCK,

		POD_STATE__BRAKE,

		POD_STATE__SPINDOWN,

		/** Keep this as the last item */
		POD_STATE__NUM_STATES

	}TE_POD_STATE_T;



#endif /* __FLIGHT_CONTROLLER__STATE_TYPES_H_ */

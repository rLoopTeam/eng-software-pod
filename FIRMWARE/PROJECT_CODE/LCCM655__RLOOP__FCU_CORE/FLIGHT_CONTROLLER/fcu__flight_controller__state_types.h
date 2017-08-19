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

    /** Pod Commands */    
    typedef enum 
    {
        POD_COMMAND__NO_COMMAND = 0U,
        
        POD_COMMAND__IDLE,
        
        POD_COMMAND__TEST_MODE,
        
        POD_COMMAND__DRIVE,
        
        POD_COMMAND__FLIGHT_PREP,
        
        POD_COMMAND__ARMED_WAIT,
        
        POD_COMMAND__READY,
        
        /** Keep this as the last item */
        POD_COMMAND__NUM_COMMANDS

    }TE_POD_COMMAND_T;


#endif /* __FLIGHT_CONTROLLER__STATE_TYPES_H_ */

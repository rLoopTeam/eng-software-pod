/*
 * fcu__flight_controller__state_types.h
 *
 *  Created on: 19Aug.,2017
 *      Author: Lachlan
 */

#ifndef __FLIGHT_CONTROLLER__STATE_TYPES_H_
#define __FLIGHT_CONTROLLER__STATE_TYPES_H_

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U

	#if C_LOCALDEF__LCCM655__ENABLE_MAIN_SM == 1U
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

	/**  State machine management struct */
	typedef struct
	{
		/** Current state */
		TE_POD_STATE_T eCurrentState;

		/** Previous state */
		TE_POD_STATE_T ePrevState;

		/** For when we start, to trigger if entry(sm, state) stanzas */
		Luint8 u8StateChanged;

	} TS_FCTL__STATE_MACHINE_T;
	#endif //C_LOCALDEF__LCCM655__ENABLE_MAIN_SM


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


	/** Timer/Timeout struct */
	typedef struct
	{
		/** Duration of the timeout */
		Luint32 u32Duration_x10ms;

		/** Is the timer running?*/
		Luint8 u8IsStarted;

		/** Elapsed time in milliseconds*/
		Luint32 u32Elapsed_x10ms;

	} TS_FCTL__TIMEOUT_T;

	/** Interlock command struct */
	typedef struct
	{
		// Has the command been enabled?
		Luint8 enabled;

		// Once the command has been enabled, start the timeout and don't allow execution if it's expired.
		TS_FCTL__TIMEOUT_T commandTimeout;

	} strInterlockCommand;


	/** Pod command struct */
	typedef struct
	{
		// Command
		TE_POD_COMMAND_T command;

		struct
		{
		// Args would go here, under a sub-struct with the same name as the command
		// e.g. struct { Luint16 some_arg; } POD_COMMAND__ARMED_WAIT
		} args;

	} strPodCmd;


//safetys
#endif //C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
#ifndef C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
	#error
#endif
#endif //C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif


#endif /* __FLIGHT_CONTROLLER__STATE_TYPES_H_ */


#ifndef RLOOP_LCCM655__RLOOP__FCU_CORE_FCU_CORE__TYPES_H_
#define RLOOP_LCCM655__RLOOP__FCU_CORE_FCU_CORE__TYPES_H_

	/** Run state types */
	typedef enum
	{
		/** Come out of reset and handle any startup tasks*/
		RUN_STATE__RESET = 0U,

		/** Init rPod specific systems */
		RUN_STATE__INIT_SYSTEMS,

		/** Run the flight computer in startup, do any diagnostics, etc*/
		RUN_STATE__STARTUP_MODE,

		/** Run the flight computer in flight mode*/
		RUN_STATE__FLIGHT_MODE,


	}E_FCU__RUN_STATE_T;


	/** Flight control state machine INIT types */
	typedef enum
	{

		/** Just come out of reset */
		INIT_STATE__RESET = 0U,

		/** Setup the IO */
		INIT_STATE__INIT_IO,


		/** Init the comms chanels */
		INIT_STATE__INIT_COMMS,

		/** Setup the SPI uarts */
		INIT_STATE__INIT_SPI_UARTS,

		/** Setup any lower systems */
		INIT_STATE__LOWER_SYSTEMS,


		/** Setup any timers */
		INIT_STATE__START_TIMERS,


		/** init is done, run the main state machine */
		INIT_STATE__RUN,

	}E_FCU__INIT_STATE_TYPES;

	/** Brakes states */
		typedef enum
		{

			/** We are in idle state */
			BRAKE_STATE__IDLE = 0U,

			/** Beginning to move the brakes */
			BRAKE_STATE__BEGIN_MOVE,

			/** The brakes are moving */
			BRAKE_STATE__MOVING,

			/** The brakes were moving, and now they have stopped, cleanup any necessary stuff */
			BRAKE_STATE__MOVE_STOPPED,

			/** A fault has occurred with the brake system */
			BRAKE_STATE__FAULT,

			BRAKE_STATE__TEST

		}E_FCU_BRAKES__STATES_T;


		/** Pusher interlock state machine */
		typedef enum
		{
			/** Idle state, doing nothing. */
			PUSH_STATE__IDLE = 0U,

			/** Take a sample of the switches and see whats going on */
			PUSH_STATE__SAMPLE_SWITCHES,

			/** we have detected a state change on a switch, it may be one sw, or both swtiches
			 * here we need to wait until all of the swtiches are stable.
			 */
			PUSH_STATE__WAIT_SW_STABLE,

			/** Determine the pusher state to ensure that we know what combinations
			 * of switches are valid
			 */
			PUSH_STATE__DETERMINE_PUSHER_STATE,

			/** Check if there is some long term disagree with the switches */
			PUSH_STATE__CHECK_DISAGREE,

		}E_FCU_PUSHER__STATES_T;



#endif /* RLOOP_LCCM655__RLOOP__FCU_CORE_FCU_CORE__TYPES_H_ */

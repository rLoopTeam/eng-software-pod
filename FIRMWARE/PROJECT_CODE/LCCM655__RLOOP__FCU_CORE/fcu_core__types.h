
#ifndef RLOOP_LCCM655__RLOOP__FCU_CORE_FCU_CORE__TYPES_H_
#define RLOOP_LCCM655__RLOOP__FCU_CORE_FCU_CORE__TYPES_H_

	/** Throttle control types */
	typedef enum
	{
		/** Step response */
		THROTTLE_TYPE__STEP = 0U,

		/** Ramp type response */
		THROTTLE_TYPE__RAMP = 1U

	}E_THROTTLE_CTRL_T;

	/** ASI communication (modbus client) states */
	typedef enum
	{
		/** Idle state */
		ASI_COMM_STATE__IDLE = 0U,

		/** Wait until slaves have time to process broadcast command */
		ASI_COMM_STATE__WAIT_TURNAROUND_DELAY,

		/** Wait until hear back from slave after unicast command */
		ASI_COMM_STATE__WAIT_REPLY,

		/** Receive state */
		ASI_COMM_STATE__PROCESS_REPLY,

		/** Process error */
		ASI_COMM_STATE__PROCESS_ERROR

	} E_FCU_MODBUS__STATE_T;

	/** Scanning states for ASI */
	typedef enum
	{
		/** We are doing nothing */
		ASI_STATE__IDLE = 0U,

		/** Set the MUX to the device we want to read */
		ASI_STATE__CONFIG_MUX,

		/** Issue a command to the ASI */
		ASI_STATE__ISSUE_COMMAND,

		/** Wait until the recent issued command is complete */
		ASI_STATE__WAIT_COMMAND_COMPLETE,


		/** Change to the next scanning address */
		ASI_STATE__INC_SCAN_INDEX

	}E_FCU__ASI_STATE_T;


	/** Mission Phase Types */
	typedef enum
	{
		/** Come out of reset and handle any startup tasks. This is done when
		 * power is first applied to the FCU*/
		MISSION_PHASE__RESET = 0U,


		/** Run the flight computer in startup, do any diagnostics, etc
		 * Diagnostics here will be on systems that do not involve actuators such as
		 * memory CRC tests, etc.
		 * We can stay in startup mode, or startup-fail mode if something is not right here.*/
		MISSION_PHASE__TEST_PHASE,


		MISSION_PHASE__PRE_RUN_PHASE,

		MISSION_PHASE__PUSH_INTERLOCK_PHASE,


		/** Run the flight computer in flight mode, the flight controller takes care
		 * of everything until flight finished*/
		MISSION_PHASE__FLIGHT_MODE,

		/** we have aborted flight, need to cleanup systems, landing gear and safe the pod.
		 * This mode can also be the flight finished mode. */
		RUN_STATE__FLIGHT_ABORT,
		/** In this mode the pod takes care of its functional tests as a terminal countdown.
		 * Autosequence is entered by the GS and once Autosequence tests are complete we
		 * move to flight mode. */
		MISSION_PHASE__AUTO_SEQUENCE_MODE,


	}E_FCU__RUN_STATE_T;


	/** Auto sequence functional mode cheks */
	typedef enum
	{
		/** Come out of reset and handle any startup tasks*/
		AUTOSEQ_STATE__RESET = 0U,

		/** Doing nothing, return here when idle */
		AUTOSEQ_STATE__IDLE,

		AUTOSEQ_STATE__TEST_FUNCTION_X


	}E_FCU__AUTO_SEQUENCE_STATE_T;



	/** Opto NCDT Laser processing subsystem state machine */
	typedef enum
	{

		/** just come out of reset */
		OPTOLASER_STATE__RESET = 0U,

		/** we need to wait until the lasers power up before issuing a command*/
		OPTOLASER_STATE__WAIT_LASER_RESET,

		/** configure the laser into RS422 mode */
		OPTOLASER_STATE__INIT_LASER,

		/** Wait until the laser has been initted */
		OPTOLASER_STATE__WAIT_INIT_DONE,

		/** Check if any new data is avail from the laser FIFO's */
		OPTOLASER_STATE__CHECK_NEW_DATA,

		/** Check if a new packet is avail for each laser */
		OPTOLASER_STATE__CHECK_NEW_PACKET,

		/** Perform packet filtering */
		OPTOLASER_STATE__FILTER_PACKET

	}E_FCU_OPTOLASER__STATE_T;

	/** laser distance state types */
	typedef enum
	{

		/** just come out of reset */
		LASERDIST_STATE__RESET = 0U,

		/** we need to wait until the lasers power up before issuing a command*/
		LASERDIST_STATE__WAIT_LASER_RESET,

		/** configure the laser to turn on */
		LASERDIST_STATE__INIT_LASER_TURNON,

		/** Wait until the laser has been initted */
		LASERDIST_STATE__WAIT_INIT_DONE,

		/** Check if any new data is avail from the laser FIFO's */
		LASERDIST_STATE__CHECK_NEW_DATA,

		/** Check if a new packet is avail for each laser */
		LASERDIST_STATE__CHECK_NEW_PACKET

	}E_FCU_LASERDIST__STATE_T;

	/** State types for the LaserOrientation state machine */
	typedef enum
	{

		/** do nothing*/
		LASER_ORIENTATION_STATE__IDLE = 0U,

		/** We are in an error condition */
		LASER_ORIENTATION_STATE__ERROR,

		/** init the device, force a reset */
		LASER_ORIENTATION_STATE__INIT,

		/** Wait for a number of processing loops to expire */
		LASER_ORIENTATION_STATE__WAIT_LOOPS,

		/** Get laser measurements and states from optoncdt code */
		LASER_ORIENTATION_STATE__GET_LASER_DATA,

		LASER_ORIENTATION_STATE__RECALCULATE_PITCH_ROLL_TWIST,

		LASER_ORIENTATION_STATE__RECALCULATE_YAW_AND_LATERAL

	}E_LASER_ORIENTATION__STATE_T;


	/** Rx state machine for the laser data from OptoNCDT*/
	typedef enum
	{
		OPTONCDT_RX__BYTE_1 = 0U,
		OPTONCDT_RX__BYTE_2,
		OPTONCDT_RX__BYTE_3

	}E_OPTONCDT__RX_STATE_T;

	/** Laser distance Rx states */
	typedef enum
	{
		LASERDIST_RX__BYTE_D = 0U,
		LASERDIST_RX__BYTE_0,
		LASERDIST_RX__BYTE_1,
		LASERDIST_RX__BYTE_2,
		LASERDIST_RX__BYTE_3,
		LASERDIST_RX__BYTE_4


	}E_LASERDIST__RX_STATE_T;


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
		INIT_STATE__RUN

	}E_FCU__INIT_STATE_TYPES;

		/** Brakes states */
		typedef enum
		{

			/** Just come out of reset */
			BRAKE_STATE__RESET = 0U,

			/** We are in idle state */
			BRAKE_STATE__IDLE,

			/** Beginning to move the brakes */
			BRAKE_STATE__BEGIN_MOVE,

			/** Compute the I_Beam distances */
			BRAKE_STATE__COMPUTE,

			/** The brakes are moving */
			BRAKE_STATE__MOVING,

			/** The brakes were moving, and now they have stopped, cleanup any necessary stuff */
			BRAKE_STATE__MOVE_STOPPED,

			/** A fault has occurred with the brake system */
			BRAKE_STATE__FAULT,

			BRAKE_STATE__TEST,

			BRAKE_STATE__BEGIN_CAL,

			BRAKE_STATE__WAIT_CAL_DONE

		}E_FCU_BRAKES__STATES_T;

		/** Brake calibration states */
		typedef enum
		{

			/** We are in idle state */
			BRAKE_CAL_STATE__IDLE = 0U,

			/** Start off and retract both motors */
			BRAKE_CAL_STATE__EXTEND_MOTORS,

			/** Wait for the motors to retract the brakes */
			BRAKE_CAL_STATE__WAIT_EXTEND_MOTORS,

			/** Release the zero end stops */
			BRAKE_CAL_STATE__RELEASE_ZERO,

			/** Due to the nature of the switches, we may not be symetrical, so
			 apply a little zero here.
			 */
			BRAKE_CAL_STATE__APPLY_NEW_ZERO,

			/** Wait until the new zero is done */
			BRAKE_CAL_STATE__WAIT_NEW_ZERO,

			/** Cal is done */
			BRAKE_CAL_STATE__COMPLETE

		}E_FCU_CAL_BRAKES__STATES_T;



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
			PUSH_STATE__CHECK_DISAGREE

		}E_FCU_PUSHER__STATES_T;



#endif /* RLOOP_LCCM655__RLOOP__FCU_CORE_FCU_CORE__TYPES_H_ */

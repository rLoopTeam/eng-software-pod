/**
 * @file		FCU__THROTTLES.C
 * @brief		Throttle Controller
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup FCU
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup FCU__THROTTLES
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

//#include <MULTICORE/LCCM658__MULTICORE__AMC7812/amc7812.h>


#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_THROTTLE == 1U

//the structure
extern struct _strFCU sFCU;



// throttle command tolerance
#define u16THROTTLE_TOL			0U

// All-engines flag
#define ALL_HES					0U

#define RAMP_DONE				99U

#define THROTTLE_RAMP_TIMER_INTERVAL 100.0F

//xxxxxxxxxxxxxxxx  DUMMY VALUES - TO BE FINALIZED IN FCU  xxxxxxxxxxxxxxxxx
#define HOVER_ENGINE_MINIMUM_SPEED			0U
#define HOVER_ENGINE_MAXIMUM_SPEED			50000U
#define HOVER_ENGINE_STATIC_HOVER_SPEED		20000U
#define HOVER_ENGINE_STANDBY_SPEED			20000U
#define FCU_MODE							STOPPED_LIFTED
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

//xxxxxxxxxxxxx  DUMMY VALUES - TO BE SENT BY GROUND STATION  xxxxxxxxxxxxxx
#define GS_COMMAND_MODE						SET_HEX_SPEED
#define GS_COMMAND_UNITS					0U
#define GS_THROTTLE_COMMAND					15000U
#define GS_ENGINE_NUMBER					6U//0U
#define GS_THROTTLE_RAMP_DURATION			3000U
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

// last command values
static Luint16 u16LastThrottleSetPoint;
static Luint16 u16LastThrottleCommandValue;
static Luint16 u16InitThrottleCommand;


/***************************************************************************//**
 * @brief
 * Init any variables
 *
 */
void vFCU_THROTTLE__Init(void)
{

	//configure dev mode
	sFCU.sThrottle.sDevMode.u32SecurityKey = 0U;
	sFCU.sThrottle.sDevMode.u8Enabled = 0U;

	// initialize static variables

	u16LastThrottleSetPoint = 0U;
	u16LastThrottleCommandValue = 0U;
	u16InitThrottleCommand = 0U;

	// initialize throttle struct values
	sFCU.sThrottle.u16ThrottleCommands[0] =   0U;
	sFCU.sThrottle.u16ThrottleCommands[1] =   0U;
	sFCU.sThrottle.u16ThrottleCommands[2] =   0U;
	sFCU.sThrottle.u16ThrottleCommands[3] =   0U;
	sFCU.sThrottle.u16ThrottleCommands[4] =   0U;
	sFCU.sThrottle.u16ThrottleCommands[5] =   0U;
	sFCU.sThrottle.u16ThrottleCommands[6] =   0U;
	sFCU.sThrottle.u16ThrottleCommands[7] =   0U;
	sFCU.sThrottle.u16ThrottleCommands[8] =   0U;

	sFCU.sThrottle.u8EngineNumber = 0U;

	sFCU.sThrottle.u16HE_MIN_SPD = HOVER_ENGINE_MINIMUM_SPEED;
	sFCU.sThrottle.u16HE_MAX_SPD = HOVER_ENGINE_MAXIMUM_SPEED;

	sFCU.sThrottle.u8CommandUnits = GS_COMMAND_UNITS;

	sFCU.sThrottle.u16rpmHEStaticHoveringSpeed = HOVER_ENGINE_STATIC_HOVER_SPEED;

	sFCU.sThrottle.u16maxRunModeStandbySpeed = HOVER_ENGINE_STANDBY_SPEED;

	sFCU.sThrottle.u16throttleStartRampDuration = GS_THROTTLE_RAMP_DURATION;

}


/***************************************************************************//**
 * @brief
 * Process any Throttle tasks
 * 
 */
// REQUIRED INPUTS: sFCU.sThrottle
void vFCU_THROTTLE__Process(void)
{

	// variable declarations
	Lint16 s16Return;
	//Luint16 u16ThrottleCommands[9];
	static Luint8 u8Counter = 0U;
	static Luint8 u8Counter2 = 0U;
	Luint16 u16DoneFlag;

	Luint16 u16Command;
	Luint16 u8EngNum;

	// xxxxxxxxxxx GET DUMMY VALUES  xxxxxxxxxxxxxxxxxxxxxx
	vFCU_THROTTLE__GetGroundStationStructValues();
	//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


	// Determine if a change of state is required:

	// If the GS commands STATIC HOVERING and the FCU is in STOPPED_LIFTED_MODE,
	// Then ramp up the speed commands for all engines to rpmHEStaticHoveringSpeed
	// over the interval throttleStartRampDuration

	// If the GS commands RELEASE STATIC HOVERING and the FCU is in RUN MODE STANDBY,
	// then set all HE speed commands to zero

	// If the GS commands SET HEX SPEED and the speed is less than maxRunModeStandbySpeed,
	// then set the throttle command for HE_x to the given value

	// If the GS commands SET ALL HE SPEED and the speed is less than maxRunModeStandbySpeed,
	// then set the throttle commands for all HEs to [the given value]


	if(sFCU.sThrottle.eGS_Command == STATIC_HOVERING && sFCU.sThrottle.eFCU_Mode == STOPPED_LIFTED)
	{
		// set command variables

		sFCU.sThrottle.u16ThrottleCommands[0] =   sFCU.sThrottle.u16rpmHEStaticHoveringSpeed;
		sFCU.sThrottle.u8EngineNumber = 6U;//ALL_HES;//xxxxxxxxxxxxxxxxxxxxxTEMPORARYXXXXXXXXXXXXXXXXXXXXXXXXXXXX

		// change the state

		sFCU.sThrottle.eState = THROTTLE_STATE__RAMP_COMMAND;
	}

	if(sFCU.sThrottle.eGS_Command == RELEASE_STATIC_HOVERING && sFCU.sThrottle.eFCU_Mode == RUN_MODE_STANDBY)
	{
		// set command variables

		sFCU.sThrottle.u16ThrottleCommands[0] =   0U;
		sFCU.sThrottle.u8EngineNumber = ALL_HES;

		// change the state

		sFCU.sThrottle.eState = THROTTLE_STATE__STEP_COMMAND;
	}

	if(sFCU.sThrottle.eGS_Command == SET_HEX_SPEED)
	{
		// set command variables - values should be set by ground station interface

		//sFCU.sThrottle.u8EngineNumber = GS_ENGINE_NUMBER;
		//sFCU.sThrottle.u16ThrottleCommands[u8EngNum] = GS_THROTTLE_COMMAND;

		// change the state

		sFCU.sThrottle.eState = THROTTLE_STATE__STEP_COMMAND;
	}

	if(sFCU.sThrottle.eGS_Command == SET_ALL_HE_SPEED)
	{
		// set command variables - value should be set by ground station interface

		sFCU.sThrottle.u16ThrottleCommands[0] =  GS_THROTTLE_COMMAND;
		sFCU.sThrottle.u8EngineNumber = ALL_HES;

		// change the state

		sFCU.sThrottle.eState = THROTTLE_STATE__STEP_COMMAND;
	}


	// define action according to the state

	switch(sFCU.sThrottle.eState)
	{
		case THROTTLE_STATE__IDLE:

			//do nothing,

			break;

		case THROTTLE_STATE__INIT:

			//reset the device

			//vFCU_THROTTLE__Init();

			// set the throttle state to idle

			sFCU.sThrottle.eState = THROTTLE_STATE__IDLE;

			break;

		case THROTTLE_STATE__HOLD:

			// may not be needed depending on how AMC7812 handles data

			break;

		case THROTTLE_STATE__STEP_COMMAND:

			// call step

			s16Return = s16FCU_THROTTLE__Step_Command();

			// check for errors in data output

			if(s16Return < 0)
			{
				// an error flag has been thrown

				//printf("Error in step command\n");

				// change the throttle state

				sFCU.sThrottle.eState = THROTTLE_STATE__ERROR;

				s16Return = -1;

			}
			else
			{
				sFCU.sThrottle.eState = THROTTLE_STATE__IDLE;
			}
			break;

		case THROTTLE_STATE__RAMP_COMMAND:

			u8Counter2++;

			// Check the timer state: the output command will increment every 100 milliseconds

			if(sFCU.sThrottle.u8100MS_Timer == 1U)
			{

				u8Counter++;

				// call ramp (currently set to command all HEs, can be set to a specific HE: change index of u16ThrottleCommand)

				s16Return = -1;
				s16Return = s16FCU_THROTTLE__Ramp_Command();

				if(s16Return < 0)		// an error flag has been thrown
				{
					//printf("Error in step command\n");

					// change the throttle state

					sFCU.sThrottle.eState = THROTTLE_STATE__ERROR;

				}
				else
				{
					u16DoneFlag = RAMP_DONE;

					if ( s16Return == u16DoneFlag )
					{
						// Change the state to idle

						sFCU.sThrottle.eState = THROTTLE_STATE__IDLE;
					}
					else
					{
						//
					}
				}

				// Reset timer state

				sFCU.sThrottle.u8100MS_Timer = 0U;
			}
			else
			{
				// Wait for it...
			}


			break;


		case THROTTLE_STATE__ERROR:

			// an error has occurred

			//printf("Error in THROTTLE function\n");

			break;

	}	// end of switch()

}	// end of vFCU_THROTTLE__Process(...)


void vFCU_THROTTLE__Set_Throttle(Luint8 u8EngineIndex, Luint16 u16RPM, Luint8 u8RampType)
{


}


//safetly switch on dev mode
void vFCU_THROTTLE__Enable_DevMode(Luint32 u32Key0, Luint32 u32Key1)
{

	if(u32Key0 == 0x11223344U)
	{
		sFCU.sThrottle.sDevMode.u8Enabled = 1U;
		sFCU.sThrottle.sDevMode.u32SecurityKey = 0x77558833U;
	}
	else
	{
		sFCU.sThrottle.sDevMode.u8Enabled = 0U;
		sFCU.sThrottle.sDevMode.u32SecurityKey = 0U;
	}

}




// --- Writes throttle commands for a constant value ---

Lint16 s16FCU_THROTTLE__Step_Command(void)
{
	// variable declarations

	Lint16 s16Return;
	Lint16 s16DACReturn;
	Luint16 u16ThrottleCommand;

	// get command value

	u16ThrottleCommand = sFCU.sThrottle.u16ThrottleCommands[sFCU.sThrottle.u8EngineNumber];

	// Check if this is a new command

	if(u16LastThrottleCommandValue != u16ThrottleCommand)
	{
		// Is throttle command in RPM (CommandUnits = 0) or percent (CommandUnits = 1)?
		// Convert throttle command
	//
		if(sFCU.sThrottle.u8CommandUnits == 1U)		// units are percent
		{
			u16ThrottleCommand *= (Luint16)( (Lfloat32)sFCU.sThrottle.u16HE_MAX_SPD / 100.0F );		// Convert from percent to RPM*10
		}
		else
		{
			// command is in RPM*10, do nothing
		}


		// Check if the command is out of bounds

		if(u16ThrottleCommand > sFCU.sThrottle.u16HE_MAX_SPD)
		{
			// Too high, reset command to max value
			u16ThrottleCommand = sFCU.sThrottle.u16HE_MAX_SPD;
		}

		if(u16ThrottleCommand < sFCU.sThrottle.u16HE_MIN_SPD)
		{
			// Too low, Reset command to min value

			u16ThrottleCommand = sFCU.sThrottle.u16HE_MIN_SPD;
		}

		// Save the current command value

		u16LastThrottleCommandValue = u16ThrottleCommand;

	//
		// write to DAC

		s16DACReturn = -1;

		if(sFCU.sThrottle.u8EngineNumber == ALL_HES)
		{
			// write command to all engines

			s16DACReturn = s16FCU_THROTTLE__Write_All_HE_Throttle_Commands_to_DAC(u16ThrottleCommand);
		}
		else
		{
			// write command to engine # {u8EngineNumber}

			s16DACReturn = s16FCU_THROTTLE__Write_HEx_Throttle_Command_to_DAC(u16ThrottleCommand, sFCU.sThrottle.u8EngineNumber);
		}

	}
	else
	{
		// Nothing to do
		s16DACReturn = 0U;
	}

	// check for errors

	if(s16DACReturn < 0)
	{
		// an error has occurred

		s16Return = -1;
	}
	else
	{
		s16Return = 0;
	}

	return s16Return;

}	// end of s16THROTTLE__Step_Command()



// --- Writes throttle command for a ramp function ---
// Ramps up from the last commanded throttle value to u16ThrottleSetPoint over the duration contained in sFCU.sThrottle

Lint16 s16FCU_THROTTLE__Ramp_Command(void)
{
	// variable declarations

	Lint16 s16Return;
	Lint16 s16DACReturn;
	Luint16 u16RampThrottleCommand;
	static Lfloat32 f32CommandSlope;
	static Luint16 u16CommandIncrement;
	Luint16 u16ThrottleSetPoint;

	u16ThrottleSetPoint = sFCU.sThrottle.u16ThrottleCommands[sFCU.sThrottle.u8EngineNumber];

	// Is this a new command?

	if(u16LastThrottleSetPoint != u16ThrottleSetPoint)
	{
		// reset timer

//		u32RampStartTime = u32ClockTime;

		// Convert throttle command to RPM if units are percent

		if(sFCU.sThrottle.u8CommandUnits == 1U)
		{
			// Convert from percent to RPM*10

			u16ThrottleSetPoint *= (Luint16)( (Lfloat32)sFCU.sThrottle.u16HE_MAX_SPD / 100.0F );
		}
		else
		{
			// assume units are RPM*10, do nothing
		}


		// Check if the command is out of bounds

		if(u16ThrottleSetPoint > sFCU.sThrottle.u16HE_MAX_SPD)
		{
			// too high, reset command to max value

			u16ThrottleSetPoint = sFCU.sThrottle.u16HE_MAX_SPD;
		}

		if(u16ThrottleSetPoint < sFCU.sThrottle.u16HE_MIN_SPD)
		{
			// Too low, reset command to min value

			u16ThrottleSetPoint = sFCU.sThrottle.u16HE_MIN_SPD;
		}


		// save the current set point value

		u16LastThrottleSetPoint = u16ThrottleSetPoint;

		// save the initial command value

		u16InitThrottleCommand = u16LastThrottleCommandValue;

		// compute the slope of the ramp command

		f32CommandSlope = ( (Lfloat32)(u16ThrottleSetPoint - u16InitThrottleCommand) / (Lfloat32)(sFCU.sThrottle.u16throttleStartRampDuration) );

		// compute command increment for 100 ms

		u16CommandIncrement =  (Luint16)(f32CommandSlope * THROTTLE_RAMP_TIMER_INTERVAL);


	}


	// compute the new throttle command value

	u16RampThrottleCommand = u16CommandIncrement + u16LastThrottleCommandValue;

	// Save the current command value

	u16LastThrottleCommandValue = u16RampThrottleCommand;

	// write command to DAC

	s16DACReturn = -1;

	if(sFCU.sThrottle.u8EngineNumber == ALL_HES)
	{
		// command to all engines

		s16DACReturn = s16FCU_THROTTLE__Write_All_HE_Throttle_Commands_to_DAC(u16RampThrottleCommand);
	}
	else
	{
		// command to engine # {u8EngineNumber}

		s16DACReturn = s16FCU_THROTTLE__Write_HEx_Throttle_Command_to_DAC(u16RampThrottleCommand, sFCU.sThrottle.u8EngineNumber);
	}

	// check for errors in data output

	if(s16DACReturn < 0)		// an error flag has been thrown
	{
		//printf("Error in ramp command\n");

		s16Return = -1;
	}
	else
	{
		// okay

		s16Return = 0;
	}


	// if the ramp command is at the final value, set flag to change the state in vFCU_THROTTLE__Process()

	if (u16RampThrottleCommand >= u16ThrottleSetPoint)
	{

		// set return value to change the state

		s16Return = RAMP_DONE;
	}

	return s16Return;

}	// end of s16THROTTLE__Ramp_Command(...)




// --- Write throttle commands for all HEs to the DAC  ---
//   Normal return value is 0; returns the highest engine number of the writes that failed */

Lint16 s16FCU_THROTTLE__Write_All_HE_Throttle_Commands_to_DAC(Luint16 u16ThrottleCommand)
{
	// variable declarations

	Lint16 s16Return;
	Lint16 s16DACReturn;
	Luint8 u8EngineNumberCtr;

	// initialize flags

	s16Return = -1;
	s16DACReturn = -1;

	// initialize counter

	u8EngineNumberCtr = 0U;

	// loop through engine numbers 1 to 8 and call the write function

	for(u8EngineNumberCtr = 1; u8EngineNumberCtr <= C_FCU__NUM_HOVER_ENGINES; u8EngineNumberCtr++)
	{
		s16DACReturn = s16FCU_THROTTLE__Write_HEx_Throttle_Command_to_DAC(u16ThrottleCommand, u8EngineNumberCtr);

		if(s16DACReturn >= 0)
		{
			s16Return = 0;		// okay
		}
		else
		{
			// error writing command to HE No. {u8EngineNumberCtr} address, set error flag

			s16Return =  -1 * (Lint16)u8EngineNumberCtr;
		}
	}

	return s16Return;

}	// end of s16THROTTLE__Write_All_HE_Throttle_Commands_to_DAC(...)





// --- Write throttle command (in RPM) for HEx to the AMC7812 DAC over i2c ---

Lint16 s16FCU_THROTTLE__Write_HEx_Throttle_Command_to_DAC(Luint16 u16ThrottleCommand, Luint8 u8EngineNumber)
{
	// variable declarations

	Lint16 s16Return;

	// Define variables for AMC7812 DAC to set output

//LG	strAMC7812_DAC.u16Command = u16ThrottleCommand;
//LG	strAMC7812_DAC.u16MaxCommandValue = sFCU.sThrottle.u16HE_MAX_SPD;
//LG	strAMC7812_DAC.u16MinCommandValue = sFCU.sThrottle.u16HE_MIN_SPD;

	// Set DAC data register for output (see schematic LPCB235 and file amc7812.h)

//LG	strAMC7812_DAC.u8DACRegAddr = u8DACOutputChannelAddr[u8EngineNumber - 1U];

	s16Return = -1;

	// call AMC7812 to set the output

	s16Return = s16AMC7812_DAC__SetPinVoltage();

	// return the status of the I2C write

	return s16Return;

}	// end of s16THROTTLE__Write_HEx_Throttle_Command_to_DAC(...)



// --- Hold function ---
// May or may not be needed depending on whether the command has to be written to the DAC again at each update

Lint16 s16FCU_THROTTLE__Hold(void)
{

	Luint16 s16Return = 0;

	return s16Return;
}


// Timer function, returns after 100 milliseconds

void vFCU_THROTTLE__100MS_ISR(void)
{
	// set the timer flag to 1

	sFCU.sThrottle.u8100MS_Timer = 1U;

}


void vFCU_THROTTLE__GetGroundStationStructValues(void)
{
	// DUMMY FUNCTION FOR TEST PURPOSES
	sFCU.sThrottle.eGS_Command = GS_COMMAND_MODE;
	sFCU.sThrottle.eFCU_Mode = FCU_MODE;
	sFCU.sThrottle.u16throttleStartRampDuration = GS_THROTTLE_RAMP_DURATION;
	sFCU.sThrottle.u16ThrottleCommands[GS_ENGINE_NUMBER] = GS_THROTTLE_COMMAND;
	sFCU.sThrottle.u8EngineNumber = GS_ENGINE_NUMBER;

}


#endif //C_LOCALDEF__LCCM655__ENABLE_THROTTLE
#ifndef C_LOCALDEF__LCCM655__ENABLE_THROTTLE
	#error
#endif
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */


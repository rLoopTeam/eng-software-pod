/**
 * @file		FCU__PUSHER.C
 * @brief		Pusher Interface subsystem
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
 * @addtogroup FCU__PUSHER
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_PUSHER == 1U

//the structure
extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init any variables
 *
 */
void vFCU_PUSHER__Init(void)
{

	//init
	sFCU.sPusher.u8Pusher_Status = 0U;;
	sFCU.sPusher.sSwitches[0].u8EdgeFlag = 0U;
	sFCU.sPusher.sSwitches[1].u8EdgeFlag = 0U;
	sFCU.sPusher.sSwitches[0].u8SwitchState = 0U;
	sFCU.sPusher.sSwitches[1].u8SwitchState = 0U;
	sFCU.sPusher.u32SwtichTimer = 0U;
	sFCU.sPusher.u32Guard1 = 0x12344321U;
	sFCU.sPusher.u32Guard2 = 0x01020304U;

	sFCU.sPusher.eState = PUSH_STATE__IDLE;
}


/***************************************************************************//**
 * @brief
 * Process any pusher interface tasks
 * 
 */
void vFCU_PUSHER__Process(void)
{

	if(sFCU.sPusher.u32Guard1 != 0x12344321U)
	{
		//guarding error
	}
	else
	{
		if(sFCU.sPusher.u32Guard2 != 0x01020304U)
		{
			//guarding error
		}
		else
		{
			//we are safe, move on
		}
	}



	//handle the state machine for the pusher.
	switch(sFCU.sPusher.eState)
	{
		case PUSH_STATE__IDLE:

			//just vector immediate to this state after POR
			sFCU.sPusher.eState = PUSH_STATE__SAMPLE_SWITCHES;
			break;

		case PUSH_STATE__SAMPLE_SWITCHES:

			//check the edge flags
			if(sFCU.sPusher.sSwitches[0].u8EdgeFlag == 1U)
			{
				//we have a new edge on switch A, process it

				//sample the switch
				sFCU.sPusher.sSwitches[0].u8SwitchState = u8FCU_PUSHER__Get_InterlockA();


				//clear the edge flag
				sFCU.sPusher.sSwitches[0].u8EdgeFlag = 0U;

				//lets do a state change
				sFCU.sPusher.u32SwtichTimer = 0U;
				sFCU.sPusher.eState = PUSH_STATE__WAIT_SW_STABLE;
			}
			else
			{
				//todo:
				//we can just sample the swtich again, even tho we did not get an interrupt this time
				//this could be some condition in that we were too quick for the interrupt
				//or there is some software configuation error not sending interrupts.

			}

			if(sFCU.sPusher.sSwitches[1].u8EdgeFlag == 1U)
			{
				//we have a new edge on switch A, process it

				//sample the switch
				sFCU.sPusher.sSwitches[1].u8SwitchState = u8FCU_PUSHER__Get_InterlockB();


				//clear the edge flag
				sFCU.sPusher.sSwitches[1].u8EdgeFlag = 0U;

				//lets do a state change
				sFCU.sPusher.u32SwtichTimer = 0U;
				sFCU.sPusher.eState = PUSH_STATE__WAIT_SW_STABLE;
			}
			else
			{
				//todo:
				//we can just sample the swtich again, even tho we did not get an interrupt this time
				//this could be some condition in that we were too quick for the interrupt
				//or there is some software configuation error not sending interrupts.

			}

			break;

		case PUSH_STATE__WAIT_SW_STABLE:
			//The purpose of this state is to make sure that the swtiches are stable after a
			//edge transition

			//We have two things that can happen here. We have received a state change on one switch or
			//on both switches.

			//we can treat both switches the same in ensuring some time elapses, however if we get a new
			//state transition during this time

			//wait for 100ms, could be +/-10ms tho due to the relationship of interrupt timing to our
			//state machine
			if(sFCU.sPusher.u32SwtichTimer > 10U)
			{
				//we have waited 100ms
				//change state.
				sFCU.sPusher.eState = PUSH_STATE__DETERMINE_PUSHER_STATE;
			}
			else
			{
				//stay in state;
				//todo:
				//we should maybe check that we areactually getting timer increments, otherwise
				//if something happens to the RTI system we could loose the abiltiy to change out of this state.

			}

			break;

		case PUSH_STATE__DETERMINE_PUSHER_STATE:
			//there are two conditions here.


			//if both switches are off then we are disconnected
			//if both switches are on then we are connected
			//if one or the other switch is on, then we are connected, but this
			//state needs some safety as a damaged switch would interlock our brakes
			//as we think the pusher is connected.
			if(sFCU.sPusher.sSwitches[0U].u8EdgeFlag == 1U || sFCU.sPusher.sSwitches[1].u8EdgeFlag == 1U)
			{
				//pusher connected.
				sFCU.sPusher.u8Pusher_Status = 1U;
			}
			else
			{
				//pusher not connected.
				sFCU.sPusher.u8Pusher_Status = 0U;
			}

			//go back and do another sample for us.
			sFCU.sPusher.eState = PUSH_STATE__CHECK_DISAGREE;

			break;

		case PUSH_STATE__CHECK_DISAGREE:
			//check if there is some long term disagree between the switches.

			//a disagree could occur if we are travelling and one switch is damaged.


			//go back and do another sample for us.
			sFCU.sPusher.eState = PUSH_STATE__SAMPLE_SWITCHES;
			break;

	}

}
#endif //C_LOCALDEF__LCCM655__ENABLE_PUSHER


/***************************************************************************//**
 * @brief
 * Called from the N2HET notifications that an edge has occurred on Interlock A
 *
 */
void vFCU_PUSHER__InterlockA_ISR(void)
{
	#if C_LOCALDEF__LCCM655__ENABLE_PUSHER == 1U
		//indicate that the pusher interlock A has had an edge and we should re-read the pin
		sFCU.sPusher.sSwitches[0].u8EdgeFlag = 1U;
	#endif
}

/***************************************************************************//**
 * @brief
 * Called from the N2HET notifications that an edge has occurred on Interlock B
 *
 */
void vFCU_PUSHER__InterlockB_ISR(void)
{
	#if C_LOCALDEF__LCCM655__ENABLE_PUSHER == 1U
		//indicate that the pusher interlock A has had an edge and we should re-read the pin
		sFCU.sPusher.sSwitches[1].u8EdgeFlag = 1U;
	#endif
}

#if C_LOCALDEF__LCCM655__ENABLE_PUSHER == 1U

Luint8 u8FCU_PUSHER__Get_Switch(Luint8 u8Switch)
{
	return sFCU.sPusher.sSwitches[u8Switch].u8SwitchState;
}

Luint8 u8FCU_PUSHER__Get_PusherState(void)
{
	return sFCU.sPusher.u8Pusher_Status;
}

/***************************************************************************//**
 * @brief
 * Gets the current pin status of interlock A
 *
 * @return		0 = switch open\n
 * 				1 = switch closed.
 *
 */
Luint8 u8FCU_PUSHER__Get_InterlockA(void)
{
	Luint8 u8Return;

	//read
	u8Return = u8RM4_N2HET_PINS__Get_Pin(N2HET_CHANNEL__1, 4U);

	//todo
	//mapping

	return u8Return;
}

/***************************************************************************//**
 * @brief
 * Gets the current pin status of interlock B
 *
 * @return		0 = switch open\n
 * 				1 = switch closed.
 *
 */
Luint8 u8FCU_PUSHER__Get_InterlockB(void)
{
	Luint8 u8Return;

	//read
	u8Return = u8RM4_N2HET_PINS__Get_Pin(N2HET_CHANNEL__1, 5U);

	//todo
	//mapping

	return u8Return;
}
#endif //C_LOCALDEF__LCCM655__ENABLE_PUSHER

/***************************************************************************//**
 * @brief
 * 10ms interrupt function, coming from FCU Core indicating that a new
 * 10mS event has occurred.
 *
 */
void vFCU_PUSHER__10MS_ISR(void)
{
	#if C_LOCALDEF__LCCM655__ENABLE_PUSHER == 1U
		//increment the timer always. Dont be concerned with rollover as we manage the timer
		//in the state machine.
		sFCU.sPusher.u32SwtichTimer++;
	#endif
}

#ifndef C_LOCALDEF__LCCM655__ENABLE_PUSHER
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


/**
 * @file		FCU__BRAKES__STEPPER.C
 * @brief		Stepper interface for the brakes.
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
 * @addtogroup FCU__BRAKES__STEPPER
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U

//the structure
extern struct _strFCU sFCU;


void vFCU_BRAKES_STEP__Init(void)
{

	//init any IO as neede

	//setup the stepper drive system
	vSTEPDRIVE__Init();
}


//example move function
void vFCU_BRAKES_STEP__Move(void)
{
	Lint16 s16Return;

	//The poistion to move to in microns
	Lint32 s32XYZABC[6];

	//The linear velocity for the move
	Lint32 s32Velocity[6];

	//The linear accel for the move.
	Lint32 s32Accel[6];

	/** Unique ID for each task */
	Luint32 u32TaskID;

	//todo, setup the move position.

	//command the stepper to actual position, it will start moving based on timer interrupts
	s16Return = s16STEPDRIVE_POSITION__Set_Position(&s32XYZABC[0], &s32Velocity[0], &s32Accel[0], u32TaskID);

	//check the return to see if we were able to move.

}

#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */


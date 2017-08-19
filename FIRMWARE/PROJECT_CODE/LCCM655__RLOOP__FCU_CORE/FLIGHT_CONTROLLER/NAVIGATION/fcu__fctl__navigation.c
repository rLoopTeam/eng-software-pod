#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_MAIN_SM == 1U

 //the structure
extern struct _strFCU sFCU;

void vFCU_FCTL_NAV__Init(void)
{
	//init the variables
	sFCU.sNavigation.sCalc.s32Accel_mm_ss = 0;
	sFCU.sNavigation.sCalc.s32Veloc_mm_s = 0;
	sFCU.sNavigation.sCalc.s32Displacement_mm = 0;
	sFCU.sNavigation.sCalc.s32Position_mm = 0;

	/** The navigation state machine */
	sFCU.sNavigation.sStateMachine = NAV_STATE__IDLE;


}

void vFCU_FCTL_NAV__Process(void)
{

	//handle the main statemachine
	switch(sFCU.sNavigation.sStateMachine)
	{
		/** Idle state */
		case NAV_STATE__IDLE:
			//stay in idle mode here, we can't transition until told to

			break;

		/** Nav reset */
		case NAV_STATE__RESET:

			//reset our systems
			sFCU.sNavigation.sCalc.s32Accel_mm_ss = 0;
			sFCU.sNavigation.sCalc.s32Veloc_mm_s = 0;
			sFCU.sNavigation.sCalc.s32Displacement_mm = 0;
			sFCU.sNavigation.sCalc.s32Position_mm = 0;

			//also reset anything that relies on us


			//do not move to run mode until instructed
			break;

		/** Nav run, processing the navigation */
		case NAV_STATE__RUN:

			//determine what source of navigation we have requested, for now just
			//work on the accel system

			//get the data
			sFCU.sNavigation.sCalc.s32Accel_mm_ss = sFCU_ACCEL_VALID__Get_Accel_mm_ss();
			sFCU.sNavigation.sCalc.s32Veloc_mm_s = sFCU_ACCEL_VALID__Get_Velocity_mm_s();
			sFCU.sNavigation.sCalc.s32Displacement_mm = sFCU_ACCEL_VALID__Get_Displacement_mm();

			//compute the position which depending on how we take pos, could be from the end of the track backwards
			//for now just assign
			sFCU.sNavigation.sCalc.s32Position_mm = sFCU.sNavigation.sCalc.s32Displacement_mm;


			break;

		default:
			//should not get here
			break;

	}//switch(sFCU.sNavigation.sStateMachine)

}

//run the flight controller
void vFCU_FCTL_NAV__Run(void)
{
	sFCU.sNavigation.sStateMachine = NAV_STATE__RUN;
}

//reset the nav, and start it running
void vFCU_FCTL_NAV__Reset(Luint32 u32Key)
{
	if(u32Key == 0x11229955U)
	{
		sFCU.sNavigation.sStateMachine = NAV_STATE__RESET;
	}
	else
	{
		//error
	}


}

Lint32 s32FCU_FCTL_NAV__Get_Accel_mm_ss(void)
{
	return sFCU.sNavigation.sCalc.s32Accel_mm_ss;
}

Lint32 s32FCU_FCTL_NAV__Get_Veloc_mm_s(void)
{
	return sFCU.sNavigation.sCalc.s32Veloc_mm_s;
}

Lint32 s32FCU_FCTL_NAV__Get_Displacement_mm(void)
{
	return sFCU.sNavigation.sCalc.s32Displacement_mm;
}

Lint32 s32FCU_FCTL_NAV__Get_Track_Position_mm(void)
{
	return sFCU.sNavigation.sCalc.s32Position_mm;
}


#endif //C_LOCALDEF__LCCM655__ENABLE_MAIN_SM
#ifndef C_LOCALDEF__LCCM655__ENABLE_MAIN_SM
	#error
#endif
#endif //C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif

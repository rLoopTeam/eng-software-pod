#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_MAIN_SM == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FCTL_NAVIGATION == 1U

 //the structure
extern struct _strFCU sFCU;

void vFCU_FCTL_NAV__Init(void)
{
	//init the variables
	sFCU.sNavigation.sCalc.s32Accel_mm_ss = 0;
	sFCU.sNavigation.sCalc.s32Veloc_mm_s = 0;
	sFCU.sNavigation.sCalc.s32Displacement_mm = 0;
	sFCU.sNavigation.sCalc.s32Position_mm = 0;
	sFCU.sNavigation.u8NewSampleAvail = 0U;

	/** The navigation state machine */
	sFCU.sNavigation.sStateMachine = NAV_STATE__IDLE;


}

void vFCU_FCTL_NAV__Process(void)
{
	Luint8 u8Test;

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
			sFCU.sNavigation.u8NewSampleAvail = 0U;

			//also reset anything that relies on us


			//do not move to run mode until instructed
			break;

		/** Nav run, processing the navigation */
		case NAV_STATE__RUN:

			//determine what source of navigation we have requested, for now just
			//work on the accel system

			//get the data
			u8Test = u8FCU_ACCEL_VALID__Get_New_Sample_Avail();
			if(u8Test == 1U)
			{
				sFCU.sNavigation.sCalc.s32Accel_mm_ss = sFCU_ACCEL_VALID__Get_Accel_mm_ss();
				sFCU.sNavigation.sCalc.s32Veloc_mm_s = sFCU_ACCEL_VALID__Get_Velocity_mm_s();
				sFCU.sNavigation.sCalc.s32Displacement_mm = sFCU_ACCEL_VALID__Get_Displacement_mm();

				//clear it
				vFCU_ACCEL_VALID__Clear_NewSample_Avail();

				//new data avail
				sFCU.sNavigation.u8NewSampleAvail = 1U;

			}
			else
			{
				//no new sample avail yet
			}

			//compute the position which depending on how we take pos, could be from the end of the track backwards
			//for now just assign
			sFCU.sNavigation.sCalc.s32Position_mm = sFCU.sNavigation.sCalc.s32Displacement_mm;


			break;

		default:
			//should not get here
			break;

	}//switch(sFCU.sNavigation.sStateMachine)

	if(sFCU.sNavigation.u8NewSampleAvail == 1U)
	{
		//do our DAQ
		#if C_FCU_DAQ_SET__ENABLE__DAQ_FOR_NAV == 1U
		/*
			vSIL3_DAQ_APPEND__S16(C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A0X_S16, sFCU.sAccel.sChannels[u8Counter].s16LastSample[MMA8451_AXIS__X]);
			vSIL3_DAQ_APPEND__S16(C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A0Y_S16, sFCU.sAccel.sChannels[u8Counter].s16LastSample[MMA8451_AXIS__Y]);
			vSIL3_DAQ_APPEND__S16(C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A0Z_S16, sFCU.sAccel.sChannels[u8Counter].s16LastSample[MMA8451_AXIS__Z]);

			vSIL3_DAQ_APPEND__S32(C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A0_ACCEL_S32, sFCU.sAccel.sChannels[u8Counter].s32CurrentAccel_mm_ss);
			vSIL3_DAQ_APPEND__S32(C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A0_VELOC_S32, sFCU.sAccel.sChannels[u8Counter].s32CurrentVeloc_mm_s);
			vSIL3_DAQ_APPEND__S32(C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A0_DISP_S32, sFCU.sAccel.sChannels[u8Counter].s32CurrentDisplacement_mm);
		*/
		#endif



		//clear it
		sFCU.sNavigation.u8NewSampleAvail = 0U;
	}
	else
	{
		//no new data yet
	}

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

#endif //C_LOCALDEF__LCCM655__ENABLE_FCTL_NAVIGATION

#endif //C_LOCALDEF__LCCM655__ENABLE_MAIN_SM
#ifndef C_LOCALDEF__LCCM655__ENABLE_MAIN_SM
	#error
#endif
#endif //C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif

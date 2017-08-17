#include "../fcu_core.h"
#if C_LOCALDEF__LCCM655__ENABLE_LASER_DISTANCE == 1U

//the structure
extern struct _strFCU sFCU;

void vFCU_LASERDIST_VALID__Init(void)
{
	sFCU.sLaserDist.sValid.u8Enable = 0U;
	sFCU.sLaserDist.sValid.u8Valid = 0U;
	sFCU.sLaserDist.sValid.s32ValidAccel_mm_ss = 0;
	sFCU.sLaserDist.sValid.s32ValidVeloc_mm_s = 0;
	sFCU.sLaserDist.sValid.s32ValidDistance_mm = 0;
}

//process the current laser data and check that it is valid
void vFCU_LASERDIST_VALID__Process(void)
{

	Luint8 u8Valid;

	//see if we are OK
	if(sFCU.sLaserDist.sFaultFlags.u32Flags[0] == 0U)
	{
		//we are good to go

		//todo: check the sensor range
		if(sFCU.sLaserDist.s32Distance_mm < 40000)
		{
			//if the range is good, apply the current dat
			sFCU.sLaserDist.sValid.s32ValidAccel_mm_ss = sFCU.sLaserDist.s32Accel_mm_ss;
			sFCU.sLaserDist.sValid.s32ValidVeloc_mm_s = sFCU.sLaserDist.s32Velocity_mm_s;
			sFCU.sLaserDist.sValid.s32ValidDistance_mm = sFCU.sLaserDist.s32Distance_mm;

			//our data is valid
			u8Valid = 1U;

		}
		else
		{
			//we are greater than 40m, not valid anymore
			u8Valid = 0U;
		}

	}
	else
	{
		//we are not available
		u8Valid = 0U;
	}


	//finally assign the valid state
	sFCU.sLaserDist.sValid.u8Valid = u8Valid;
}

//must set this to 1 to enable laser distance as a valid data source
void vFCU_LASERDIST_VALID__Enable(Luint8 u8Enable)
{
	sFCU.sLaserDist.sValid.u8Enable = u8Enable;
}


//return 1 if the accel source is valid
Luint8 vFCU_LASERDIST_VALID__Get_IsValid(void)
{
	Luint8 u8Return;
	if(sFCU.sLaserDist.sValid.u8Enable == 1U)
	{
		u8Return = sFCU.sLaserDist.sValid.u8Valid;
	}
	else
	{
		//not enabled, so not valid
		u8Return = 0U;
	}

	return u8Return;
}


Lint32 s32FCU_LASERDIST_VALID__Get_Accel_mm_ss(void)
{
	return sFCU.sLaserDist.sValid.s32ValidAccel_mm_ss;
}

Lint32 s32FCU_LASERDIST_VALID__Get_Velocity_mm_s(void)
{
	return sFCU.sLaserDist.sValid.s32ValidVeloc_mm_s;
}

Lint32 s32FCU_LASERDIST_VALID__Get_Distance_mm(void)
{
	return sFCU.sLaserDist.sValid.s32ValidDistance_mm;
}

#endif //C_LOCALDEF__LCCM655__ENABLE_LASER_DISTANCE

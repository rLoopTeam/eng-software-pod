#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_ACCEL == 1U

//the structure
extern struct _strFCU sFCU;


//Init the accel valid systems
void vFCU_ACCEL_VALID__Init(void)
{
	sFCU.sAccel.sValid.u8Enabled = 0U;
	sFCU.sAccel.sValid.u8IsValid = 0U;
	sFCU.sAccel.sValid.s32ValidAccel_mm_ss = 0;
	sFCU.sAccel.sValid.s32ValidDisplacement_mm = 0;
	sFCU.sAccel.sValid.s32ValidVeloc_mm_s = 0;
	sFCU.sAccel.sValid.u8NewDataAvail = 0U;
}


//process and determine what sensor is most valid
void vFCU_ACCEL_VALID__Process(void)
{

	Luint8 u8Counter;
	Luint32 u32Temp;
	Luint8 u8Valid;
	Luint8 u8Channel;
	Luint8 u8Test;


	//If any faults, accel not valid
	u8Valid = 0U;
	for(u8Counter = 0U; u8Counter < C_FCU__NUM_ACCEL_CHIPS; u8Counter++)
	{

		//if we have any fault, then clear our flag
		u32Temp = u32SIL3_MMA8451__Get_FaultFlags(u8Counter);
		if(u32Temp != 0x00000000U)
		{
			//don't inc
		}
		else
		{
			//inc the count of valid channels
			u8Valid += 1U;
		}
	}

	//if we are valid, then process
	if(u8Valid > 0U)
	{

		//so we are valid, but who is valid

		//see if channel 0 is avail, and if so its the priority
		u8Channel = 0U;

		//get the channels fault flags
		u32Temp = u32SIL3_MMA8451__Get_FaultFlags(u8Channel);
		if(u32Temp == 0U)
		{
			//valid
			u8Valid = 1U;

			u8Test = u8FCU_ACCEL__Get_New_Sample_Avail(u8Channel);
			if(u8Test == 1U)
			{

				//do the simple assignment
				sFCU.sAccel.sValid.s32ValidAccel_mm_ss = sFCU.sAccel.sChannels[u8Channel].s32CurrentAccel_mm_ss;
				sFCU.sAccel.sValid.s32ValidDisplacement_mm = sFCU.sAccel.sChannels[u8Channel].s32CurrentDisplacement_mm;
				sFCU.sAccel.sValid.s32ValidVeloc_mm_s = sFCU.sAccel.sChannels[u8Channel].s32CurrentVeloc_mm_s;

				sFCU.sAccel.sValid.u8NewDataAvail = 1U;

				//clear
				vFCU_ACCEL__Clear_New_Sample_Avail(u8Channel);
			}
			else
			{
				//no new data
			}
		}
		else
		{
			//this channel was not valid

			//what about the next channel?
			u8Channel = 1U;

			//get the channels fault flags
			u32Temp = u32SIL3_MMA8451__Get_FaultFlags(u8Channel);
			if(u32Temp == 0U)
			{
				//valid
				u8Valid = 1U;

				u8Test = u8FCU_ACCEL__Get_New_Sample_Avail(u8Channel);
				if(u8Test == 1U)
				{

					//do the simple assignment
					sFCU.sAccel.sValid.s32ValidAccel_mm_ss = sFCU.sAccel.sChannels[u8Channel].s32CurrentAccel_mm_ss;
					sFCU.sAccel.sValid.s32ValidDisplacement_mm = sFCU.sAccel.sChannels[u8Channel].s32CurrentDisplacement_mm;
					sFCU.sAccel.sValid.s32ValidVeloc_mm_s = sFCU.sAccel.sChannels[u8Channel].s32CurrentVeloc_mm_s;

					sFCU.sAccel.sValid.u8NewDataAvail = 1U;

					//clear
					vFCU_ACCEL__Clear_New_Sample_Avail(u8Channel);

				}
				else
				{
					//no new data
				}

			}
			else
			{
				//major issue here, the last channel failed while processing it
				u8Valid = 0U;

			}
		}

	}
	else
	{
		//clear our data so as we dont have out of range values
		sFCU.sAccel.sValid.s32ValidAccel_mm_ss = 0;
		sFCU.sAccel.sValid.s32ValidDisplacement_mm = 0;
		sFCU.sAccel.sValid.s32ValidVeloc_mm_s = 0;
	}


	//assign at the end
	sFCU.sAccel.sValid.u8IsValid = u8Valid;


}

Luint8 u8FCU_ACCEL_VALID__Get_New_Sample_Avail(void)
{
	return sFCU.sAccel.sValid.u8NewDataAvail;
}

void vFCU_ACCEL_VALID__Clear_NewSample_Avail(void)
{
	sFCU.sAccel.sValid.u8NewDataAvail = 0U;
}

//set enable to 1 if we want to use the accel module, and therefore
//want it to produce valid data.
void vFCU_ACCEL_VALID__Enable(Luint8 u8Enable)
{
	sFCU.sAccel.sValid.u8Enabled = u8Enable;
}


//return 1 if the accel source is valid
Luint8 u8FCU_ACCEL_VALID__Get_IsValid(void)
{
	Luint8 u8Return;
	if(sFCU.sAccel.sValid.u8Enabled == 1U)
	{
		u8Return = sFCU.sAccel.sValid.u8IsValid;
	}
	else
	{
		//not enabled, so not valid
		u8Return = 0U;
	}

	return u8Return;
}

Lint32 sFCU_ACCEL_VALID__Get_Accel_mm_ss(void)
{
	return sFCU.sAccel.sValid.s32ValidAccel_mm_ss;
}

Lint32 sFCU_ACCEL_VALID__Get_Velocity_mm_s(void)
{
	return sFCU.sAccel.sValid.s32ValidVeloc_mm_s;
}

Lint32 sFCU_ACCEL_VALID__Get_Displacement_mm(void)
{
	return sFCU.sAccel.sValid.s32ValidDisplacement_mm;
}

#endif //C_LOCALDEF__LCCM655__ENABLE_ACCEL
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif

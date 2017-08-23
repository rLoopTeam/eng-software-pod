/**
 * @file		FCU__FCTL__TRACK_DATABASE.C
 * @brief		Track Management Database
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
 * @addtogroup FCU__FLIGHT_CTL__TRACK_DATABASE
 * @ingroup FCU
 * @{ */

#include "../../fcu_core.h"

#include "fcu__fctl__track_database__types.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
#if C_LOCALDEF__LCCM655__ENABLE_TRACK_DB == 1U

//the structure
extern struct _strFCU sFCU;

TS_FCU_TRACK_DB sTrackDB;

//The current working track database
//struct _strTrackDatabase sTrackDB;

Luint32 u32FCU_FCTL_TRACKDB__Get_Current_TrackEndPosX_mm(void);

/***************************************************************************//**
 * @brief
 * Init the track database
 * 
 * @st_funcMD5		B16481ED485CD446B788B5CBF79BA24E
 * @st_funcID		LCCM655R0.FILE.084.FUNC.001
 */
void vFCU_FCTL_TRACKDB__Init(void)
{

	//init some vars
	sFCU.sFlightControl.sTrackDB.u32CurrentDB = u32SIL3_EEPARAM__Read(C_LOCALDEF__LCCM655__FCTL_TRACKDB___CURRENT_DB);
	if(sFCU.sFlightControl.sTrackDB.u32CurrentDB >= C_FCTL_TRACKDB__MAX_MEM_DATABASES)
	{
		//reset to zero
		//don't bother updating EEPROM as we can do this later.
		sFCU.sFlightControl.sTrackDB.u32CurrentDB = 0U;
	}

	vSIL3_FAULTTREE__Init(&sFCU.sFlightControl.sTrackDB.sFaultFlags);

#ifdef WIN32
	//ALWAYS CALL THIS BEFORE MEM INIT
	vFCU_FCTL_TRACKDB_WIN32__Init();
#endif


	//get the memory up
	//The risk here is that we load with DB 0, which is OK for now, but in
	//the actual run we need to make sure as part of our configuration that we
	//have the correct DB selected.
	vFCU_FCTL_TRACKDB_MEM__Init();


}

/***************************************************************************//**
 * @brief
 * Process any track database tasks
 * 
 * @st_funcMD5		206F04609970B5F4F96D6892F9CE1978
 * @st_funcID		LCCM655R0.FILE.084.FUNC.002
 */
void vFCU_FCTL_TRACKDB__Process(void)
{
	vFCU_FCTL_TRACKDB_MEM__Process();

#ifdef WIN32
	vFCU_FCTL_TRACKDB_WIN32__Process();
#endif

}

/***************************************************************************//**
 * @brief
 * Allow the ground to change the current database, this will force a re-load
 * 
 * @param[in]		u32TrackID			The ID of the track
 * @param[in]		u32Key				Safety Key 0x11223344U
 * @st_funcMD5		5F888CDB9B306EC97E64358C7F7B7772
 * @st_funcID		LCCM655R0.FILE.084.FUNC.003
 */
void vFCU_FCTL_TRACKDB__Set_CurrentDB(Luint32 u32Key, Luint32 u32TrackID)
{
	if(u32Key == 0x11223344U)
	{
		//check
		if(u32TrackID < C_FCTL_TRACKDB__MAX_MEM_DATABASES)
		{
			sFCU.sFlightControl.sTrackDB.u32CurrentDB = u32TrackID;

			//update the EEPROM
			vSIL3_EEPARAM__WriteU32(C_LOCALDEF__LCCM655__FCTL_TRACKDB___CURRENT_DB, sFCU.sFlightControl.sTrackDB.u32CurrentDB, DELAY_T__IMMEDIATE_WRITE);

			//reinit the track database memory
			vFCU_FCTL_TRACKDB_MEM__Init();
		}
		else
		{
			//big issue, can't set
		}
	}
	else
	{

	}
}

/***************************************************************************//**
 * @brief
 * The current EEPROM config of the track database
 * 
 * @st_funcMD5		76D332CEC704875969A1CE33030DE949
 * @st_funcID		LCCM655R0.FILE.084.FUNC.004
 */
Luint32 u32FCU_FCTL_TRACKDB__Get_CurrentDB(void)
{
	return sFCU.sFlightControl.sTrackDB.u32CurrentDB;

}


/***************************************************************************//**
 * @brief
 * Use accelerometers option?
 * 
 * @st_funcMD5		47FF4E89A2B51DD87321DC6EF545998A
 * @st_funcID		LCCM655R0.FILE.084.FUNC.015
 */
Luint8 u8FCU_FCTL_TRACKDB__Accel__Get_Use(void)
{
	return sTrackDB.sDB2[sFCU.sFlightControl.sTrackDB.u32CurrentDB].sAccel.u8Use;
}

Lint32 s32FCU_FCTL_TRACKDB__Accel__Get_Accel_Threshold_mm_ss(void)
{
	return s32SIL3_NUM_CONVERT__Array(&sTrackDB.sDB2[sFCU.sFlightControl.sTrackDB.u32CurrentDB].sAccel.u8AccelThresh_mm_ss[0]);
}

Lint16 s16FCU_FCTL_TRACKDB__Accel__Get_Accel_ThresholdTime_x10ms(void)
{
	return s32SIL3_NUM_CONVERT__Array(&sTrackDB.sDB2[sFCU.sFlightControl.sTrackDB.u32CurrentDB].sAccel.u8AccelThresh_x10ms[0]);
}

Lint32 s32FCU_FCTL_TRACKDB__Accel__Get_Decel_Threshold_mm_ss(void)
{
	return s32SIL3_NUM_CONVERT__Array(&sTrackDB.sDB2[sFCU.sFlightControl.sTrackDB.u32CurrentDB].sAccel.u8DecelThresh_mm_ss[0]);
}

Lint16 s16FCU_FCTL_TRACKDB__Accel__Get_Decel_ThresholdTime_x10ms(void)
{
	return s32SIL3_NUM_CONVERT__Array(&sTrackDB.sDB2[sFCU.sFlightControl.sTrackDB.u32CurrentDB].sAccel.u8DecelThresh_x10ms[0]);
}

Luint8 u8FCU_FCTL_TRACKDB__Accel__Get_UsePusherSeparaation(void)
{
	return sTrackDB.sDB2[sFCU.sFlightControl.sTrackDB.u32CurrentDB].sControl.u8EnablePuserSeparationDetection;
}


Luint32 u32FCU_FCTL_TRACKDB__Time__Get_Accel_to_Coast_Max(void)
{
	return u32SIL3_NUM_CONVERT__Array(&sTrackDB.sDB2[sFCU.sFlightControl.sTrackDB.u32CurrentDB].sTime.u8Accel_Coast[0]);
}

Luint32 u32FCU_FCTL_TRACKDB__Time__Get_Coast_to_Brake(void)
{
	return u32SIL3_NUM_CONVERT__Array(&sTrackDB.sDB2[sFCU.sFlightControl.sTrackDB.u32CurrentDB].sTime.u8Coast_Brake[0]);
}


#endif //C_LOCALDEF__LCCM655__ENABLE_TRACK_DB
#ifndef C_LOCALDEF__LCCM655__ENABLE_TRACK_DB
	#error
#endif

#endif //C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
#ifndef C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
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


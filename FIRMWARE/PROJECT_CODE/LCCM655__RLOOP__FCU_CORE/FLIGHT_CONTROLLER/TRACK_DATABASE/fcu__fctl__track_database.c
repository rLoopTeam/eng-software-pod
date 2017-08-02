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

//The current working track database
struct _strTrackDatabase sTrackDB;

Luint32 u32FCU_FCTL_TRACKDB__Get_Current_TrackEndPosX_mm(void);

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		B286AD7FA7BCE655DDB9E0A5A9436A2F
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

	//get the memory up
	//The risk here is that we load with DB 0, which is OK for now, but in
	//the actual run we need to make sure as part of our configuration that we
	//have the correct DB selected.
	vFCU_FCTL_TRACKDB_MEM__Init();

#ifdef WIN32
	vFCU_FCTL_TRACKDB_WIN32__Init();
#endif

}



/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		6ADE11075F825B49F38C20A1ADB8F9D5
 * @st_funcID		LCCM655R0.FILE.084.FUNC.002
 */
void vFCU_FCTL_TRACKDB__Process(void)
{
	Luint32 u32Test;

	vFCU_FCTL_TRACKDB_MEM__Process();

#ifdef WIN32
	vFCU_FCTL_TRACKDB_WIN32__Process();
#endif

	u32Test = u32FCU_FCTL_TRACKDB__Get_Current_TrackEndPosX_mm();

	u32Test = 0U;

}


//allow the ground to change the current database, this will force a re-load
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32TrackID		## Desc ##
 * @param[in]		u32Key		## Desc ##
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

//the current EEPROM config of the track database
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		76D332CEC704875969A1CE33030DE949
 * @st_funcID		LCCM655R0.FILE.084.FUNC.004
 */
Luint32 u32FCU_FCTL_TRACKDB__Get_CurrentDB(void)
{
	return sFCU.sFlightControl.sTrackDB.u32CurrentDB;

}

//the track ID stored with each entry, should match current DB
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		D8FA2DCDC7DD31B1E332894A34A1D70F
 * @st_funcID		LCCM655R0.FILE.084.FUNC.005
 */
Luint32 u32FCU_FCTL_TRACKDB__Get_TrackID(void)
{
	return u32SIL3_NUM_CONVERT__Array(&sTrackDB.sDB.u8TrackID[0]);
}

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		46FD0DA45EA6BA98ADDAEF8E76D62F70
 * @st_funcID		LCCM655R0.FILE.084.FUNC.006
 */
Luint32 u32FCU_FCTL_TRACKDB__Get_TrackStartPosX_mm(void)
{
	return u32SIL3_NUM_CONVERT__Array(&sTrackDB.sDB.u8TrackBeginningXPosition_mm[0]);
}

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		7701296F8611FDE543E9FF1C82909818
 * @st_funcID		LCCM655R0.FILE.084.FUNC.007
 */
Luint32 u32FCU_FCTL_TRACKDB__Get_Current_TrackEndPosX_mm(void)
{
	return u32SIL3_NUM_CONVERT__Array(&sTrackDB.sDB.u8TrackEndXPosition_mm[0]);
}

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		FCFA1AF5AE66FD5DEAE571982E3176B2
 * @st_funcID		LCCM655R0.FILE.084.FUNC.008
 */
Luint32 u32FCU_FCTL_TRACKDB__Get_LRF_StartPosX_mm(void)
{
	return u32SIL3_NUM_CONVERT__Array(&sTrackDB.sDB.u8LRFAreaBeginningXPosition_mm[0]);
}

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		C7F56046516B933691FDA93BE9CE6FAA
 * @st_funcID		LCCM655R0.FILE.084.FUNC.009
 */
Luint32 u32FCU_FCTL_TRACKDB__Get_NumStripes(void)
{
	return u32SIL3_NUM_CONVERT__Array(&sTrackDB.sDB.u8NumberOfStripes[0]);
}

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32StripeIndex		## Desc ##
 * @return			## Desc ##
 * @st_funcMD5		CCC8BE049D422F2A2E21B947F6F017EC
 * @st_funcID		LCCM655R0.FILE.084.FUNC.010
 */
Luint32 u32FCU_FCTL_TRACKDB__Get_StripeStartPosX_mm(Luint32 u32StripeIndex)
{
	return u32SIL3_NUM_CONVERT__Array(&sTrackDB.sDB.u8StripeBeginningXPosition_mm[u32StripeIndex][0]);
}

//enable LRF for track
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		7973902B7DAA5F4F43F87BB8CCF3BC49
 * @st_funcID		LCCM655R0.FILE.084.FUNC.011
 */
Luint32 u32FCU_FCTL_TRACKDB__Get_EnableLRF(void)
{
	return u32SIL3_NUM_CONVERT__Array(&sTrackDB.sDB.u8EnableLRF[0]);
}

//enable accels for track DB
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		36883E9DB4C59A4610DEE804E786AAD1
 * @st_funcID		LCCM655R0.FILE.084.FUNC.012
 */
Luint32 u32FCU_FCTL_TRACKDB__Get_EnableAccels(void)
{
	return u32SIL3_NUM_CONVERT__Array(&sTrackDB.sDB.u8EnableAccels[0]);
}

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		6BCE5BC6EF0D5A1EB78BF421CE7545BC
 * @st_funcID		LCCM655R0.FILE.084.FUNC.013
 */
Luint32 u32FCU_FCTL_TRACKDB__Get_EnableContrast(void)
{
	return u32SIL3_NUM_CONVERT__Array(&sTrackDB.sDB.u8EnableContrast[0]);
}

//get the footer, a really easy way of checking if things are good
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		7B73ABE1DA6CE38A9B417ED4B7C67B25
 * @st_funcID		LCCM655R0.FILE.084.FUNC.014
 */
Luint32 u32FCU_FCTL_TRACKDB__Get_GetFooter(void)
{
	return u32SIL3_NUM_CONVERT__Array(&sTrackDB.sDB.u8Footer[0]);
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


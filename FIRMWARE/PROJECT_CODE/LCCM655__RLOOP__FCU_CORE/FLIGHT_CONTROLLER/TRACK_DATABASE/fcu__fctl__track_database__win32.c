/**
 * @file		FCU__FCTL__TRACK_DATABASE__WIN32.C
 * @brief		Win32 functions for the track database
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
 * @addtogroup FCU__FLIGHT_CTL__TRACK_DATABASE__WIN32
 * @ingroup FCU
 * @{ */

#include "../../fcu_core.h"

#include "fcu__fctl__track_database__types.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
#if C_LOCALDEF__LCCM655__ENABLE_TRACK_DB == 1U
#ifdef WIN32

//the structure
extern struct _strFCU sFCU;

//The current working track database
extern struct _strTrackDatabase sTrackDB;

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		E54E0B6EFABF762040B6145F052A5CBC
 * @st_funcID		LCCM655R0.FILE.088.FUNC.001
 */
void vFCU_FCTL_TRACKDB_WIN32__Init(void)
{


}



/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		863EDC7743B4BC2A097EFB5B30CBDDB5
 * @st_funcID		LCCM655R0.FILE.088.FUNC.002
 */
void vFCU_FCTL_TRACKDB_WIN32__Process(void)
{


}

//zero the array
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		6DFAA77B344B57DB54D01D8A018F338D
 * @st_funcID		LCCM655R0.FILE.088.FUNC.003
 */
void vFCU_FCTL_TRACKDB_WIN32__Clear_Array(void)
{
	Luint16 u16Counter;
	Luint8 * pu8Struct;

	//get a pointer to our first byte
	pu8Struct = (Luint8*)&sTrackDB;

	//do a blind copy
	for(u16Counter = 0U; u16Counter < (Luint16)sizeof(struct _strTrackDatabase); u16Counter++)
	{
		pu8Struct[u16Counter] = 0x00U;

	}
}


//Get the copy of the array in bytes
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		pu8ByteArray		## Desc ##
 * @st_funcMD5		073378FAE4C956D8FB0C3F0D2376A8AE
 * @st_funcID		LCCM655R0.FILE.088.FUNC.004
 */
void vFCU_FCTL_TRACKDB_WIN32__Get_Array(Luint8 * pu8ByteArray)
{
	Luint16 u16Counter;
	Luint8 * pu8Struct;

	//get a pointer to our first byte
	pu8Struct = (Luint8*)&sTrackDB;

	//do a blind copy
	for(u16Counter = 0U; u16Counter < (Luint16)sizeof(struct _strTrackDatabase); u16Counter++)
	{
		pu8ByteArray[u16Counter] = pu8Struct[u16Counter];

	}
}

//Return the structure size
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		03FDD59CDD8D94E154BE7574806E08C9
 * @st_funcID		LCCM655R0.FILE.088.FUNC.005
 */
Luint16 u16FCU_FCTL_TRACKDB_WIN32__Get_StructureSize(void)
{
	return (Luint16)sizeof(struct _strTrackDatabase);

}

//Update the internal structure from an extrnal byte array
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		pu8ByteArray		## Desc ##
 * @st_funcMD5		5EE6CCC97D1D5A09662B3C120970217E
 * @st_funcID		LCCM655R0.FILE.088.FUNC.006
 */
void vFCU_FCTL_TRACKDB_WIN32__Set_Array(Luint8 *pu8ByteArray)
{
	Luint16 u16Counter;
	Luint8 * pu8Struct;

	//get a pointer to our first byte
	pu8Struct = (Luint8*)&sTrackDB;

	//do a blind copy
	for(u16Counter = 0U; u16Counter < (Luint16)sizeof(struct _strTrackDatabase); u16Counter++)
	{
		pu8Struct[u16Counter] = pu8ByteArray[u16Counter];

	}

}

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Value		## Desc ##
 * @st_funcMD5		D3F26AEFAAF4E792541D578C93EBF5AD
 * @st_funcID		LCCM655R0.FILE.088.FUNC.007
 */
void vFCU_FCTL_TRACKDB_WIN32__Set_Header(Luint32 u32Value)
{
	vSIL3_NUM_CONVERT__Array_U32(&sTrackDB.sDB.u8Header[0], u32Value);
}

//The total length of the data from after this point to the end of the CRC
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Value		## Desc ##
 * @st_funcMD5		577FA524828AEB273C6C743EF904FD5F
 * @st_funcID		LCCM655R0.FILE.088.FUNC.008
 */
void vFCU_FCTL_TRACKDB_WIN32__Set_DataLength(Luint32 u32Value)
{
	vSIL3_NUM_CONVERT__Array_U32(&sTrackDB.sDB.u8DataLength[0], u32Value);
}

//This is the ID of the track database entry.  User should match this to
//what is expected for the current run
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Value		## Desc ##
 * @st_funcMD5		7D7BF4A0940253465A1F61ACC9D51F6F
 * @st_funcID		LCCM655R0.FILE.088.FUNC.009
 */
void vFCU_FCTL_TRACKDB_WIN32__Set_TrackID(Luint32 u32Value)
{
	vSIL3_NUM_CONVERT__Array_U32(&sTrackDB.sDB.u8TrackID[0], u32Value);
}

//Track beginning. Should be always 0 by construction
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Value		## Desc ##
 * @st_funcMD5		D5216525A7F6678E7A17B7355042B5CD
 * @st_funcID		LCCM655R0.FILE.088.FUNC.010
 */
void vFCU_FCTL_TRACKDB_WIN32__Set_TrackStartXPos(Luint32 u32Value)
{
	vSIL3_NUM_CONVERT__Array_U32(&sTrackDB.sDB.u8TrackBeginningXPosition_mm[0], u32Value);
}

//Track end. x position of foam pit
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Value		## Desc ##
 * @st_funcMD5		A579997DD90BB65D9A0B354E52BAA89C
 * @st_funcID		LCCM655R0.FILE.088.FUNC.011
 */
void vFCU_FCTL_TRACKDB_WIN32__Set_TrackEndXPos(Luint32 u32Value)
{
	vSIL3_NUM_CONVERT__Array_U32(&sTrackDB.sDB.u8TrackEndXPosition_mm[0], u32Value);
}

//Minimum x position in tube to start using LRF.
//Called "min position to use laser range finder" in FCU spec 2.3
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Value		## Desc ##
 * @st_funcMD5		43F8B5565C348A57D3DC387E7BDC38ED
 * @st_funcID		LCCM655R0.FILE.088.FUNC.012
 */
void vFCU_FCTL_TRACKDB_WIN32__Set_LRF_StartXPos(Luint32 u32Value)
{
	vSIL3_NUM_CONVERT__Array_U32(&sTrackDB.sDB.u8LRFAreaBeginningXPosition_mm[0], u32Value);
}

//Number of stripes on this track
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Value		## Desc ##
 * @st_funcMD5		5A7E54C0D774E0DC24C2504F5B775656
 * @st_funcID		LCCM655R0.FILE.088.FUNC.013
 */
void vFCU_FCTL_TRACKDB_WIN32__Set_NumStripes(Luint32 u32Value)
{
	vSIL3_NUM_CONVERT__Array_U32(&sTrackDB.sDB.u8NumberOfStripes[0], u32Value);
}

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Value		## Desc ##
 * @param[in]		u32Index		## Desc ##
 * @st_funcMD5		FD594BDE3FA943A58B053AD25BC74101
 * @st_funcID		LCCM655R0.FILE.088.FUNC.014
 */
void vFCU_FCTL_TRACKDB_WIN32__Set_StripeStartX(Luint32 u32Index, Luint32 u32Value)
{
	vSIL3_NUM_CONVERT__Array_U32(&sTrackDB.sDB.u8StripeBeginningXPosition_mm[u32Index][0], u32Value);
}

//Enable accels for use on the track
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Value		## Desc ##
 * @st_funcMD5		36AED3EA80E1F21BE0B19EF160418E03
 * @st_funcID		LCCM655R0.FILE.088.FUNC.015
 */
void vFCU_FCTL_TRACKDB_WIN32__Set_EnableAccels(Luint32 u32Value)
{
	vSIL3_NUM_CONVERT__Array_U32(&sTrackDB.sDB.u8EnableAccels[0], u32Value);
}
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Value		## Desc ##
 * @st_funcMD5		16F5195412FD749FB1C0E105788C83A0
 * @st_funcID		LCCM655R0.FILE.088.FUNC.016
 */
void vFCU_FCTL_TRACKDB_WIN32__Set_EnableLRF(Luint32 u32Value)
{
	vSIL3_NUM_CONVERT__Array_U32(&sTrackDB.sDB.u8EnableLRF[0], u32Value);
}
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Value		## Desc ##
 * @st_funcMD5		0BE4170AB3C32674304688B436847984
 * @st_funcID		LCCM655R0.FILE.088.FUNC.017
 */
void vFCU_FCTL_TRACKDB_WIN32__Set_EnableContrast(Luint32 u32Value)
{
	vSIL3_NUM_CONVERT__Array_U32(&sTrackDB.sDB.u8EnableContrast[0], u32Value);
}



/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Value		## Desc ##
 * @param[in]		u32Index		## Desc ##
 * @st_funcMD5		1E2095125B334E7E5C52F2255D5688C7
 * @st_funcID		LCCM655R0.FILE.088.FUNC.018
 */
void vFCU_FCTL_TRACKDB_WIN32__Set_HeaderSpare(Luint32 u32Index, Luint32 u32Value)
{
	vSIL3_NUM_CONVERT__Array_U32(&sTrackDB.sDB.u8SpareData[u32Index][0], u32Value);
}

//Footer to know we are valid here
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Value		## Desc ##
 * @st_funcMD5		5BC28FA80FD260B9BC76136040C1C761
 * @st_funcID		LCCM655R0.FILE.088.FUNC.019
 */
void vFCU_FCTL_TRACKDB_WIN32__Set_Footer(Luint32 u32Value)
{
	vSIL3_NUM_CONVERT__Array_U32(&sTrackDB.sDB.u8Footer[0], u32Value);
}

//x position of the front of the pusher car (or rear of pod) before the run. Called "pusher start x position" in FCU spec 2.3 "*/
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Value		## Desc ##
 * @st_funcMD5		5A767C1FFBCF18D977B34108492B8C3A
 * @st_funcID		LCCM655R0.FILE.088.FUNC.020
 */
void vFCU_FCTL_TRACKDB_WIN32__Set_Profile_PusherFrontStartPos(Luint32 u32Value)
{
	vSIL3_NUM_CONVERT__Array_U32(&sTrackDB.sDB.sRunProfile.u8PusherFrontStartXPosition_mm[0], u32Value);
}

//expected x position of the front of the pusher car at the end of push phase. Called "end pushed phase x position" in FCU spec 1.1 */
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Value		## Desc ##
 * @st_funcMD5		E5DC5AAE2099D86D8136623B64E732EC
 * @st_funcID		LCCM655R0.FILE.088.FUNC.021
 */
void vFCU_FCTL_TRACKDB_WIN32__Set_Profile_PusherFrontEndPos(Luint32 u32Value)
{
	vSIL3_NUM_CONVERT__Array_U32(&sTrackDB.sDB.sRunProfile.u8PusherFrontEndXPosition_mm[0], u32Value);
}

//arget x position of pod front at the end of the run. Called "stop x position" in FCU spec 8.4 */
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Value		## Desc ##
 * @st_funcMD5		170ACC44B30EBEC83A5BB4A521E15553
 * @st_funcID		LCCM655R0.FILE.088.FUNC.022
 */
void vFCU_FCTL_TRACKDB_WIN32__Set_Profile_PodFrontTargetXPos(Luint32 u32Value)
{
	vSIL3_NUM_CONVERT__Array_U32(&sTrackDB.sDB.sRunProfile.u8PodFrontTargetXPosition_mm[0], u32Value);
}

//Number of setpoints of braking curve for this run.
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Value		## Desc ##
 * @st_funcMD5		D429B49D54A8A1192F0D75B46A08740C
 * @st_funcID		LCCM655R0.FILE.088.FUNC.023
 */
void vFCU_FCTL_TRACKDB_WIN32__Set_Profile_NumSetpoints(Luint32 u32Value)
{
	vSIL3_NUM_CONVERT__Array_U32(&sTrackDB.sDB.sRunProfile.u8NumberOfSetpoints[0], u32Value);
}

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Value		## Desc ##
 * @param[in]		u32Index		## Desc ##
 * @st_funcMD5		9E2935516825DCE49C0182833B00768F
 * @st_funcID		LCCM655R0.FILE.088.FUNC.024
 */
void vFCU_FCTL_TRACKDB_WIN32__Set_Profile_BrakeSetpointPosX(Luint32 u32Index, Luint32 u32Value)
{
	vSIL3_NUM_CONVERT__Array_U32(&sTrackDB.sDB.sRunProfile.u8BrakingSetPointXPosition_mm[u32Index][0], u32Value);
}

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Value		## Desc ##
 * @param[in]		u32Index		## Desc ##
 * @st_funcMD5		28B6E0035ADB6C351214D0B871C04E06
 * @st_funcID		LCCM655R0.FILE.088.FUNC.025
 */
void vFCU_FCTL_TRACKDB_WIN32__Set_Profile_BrakeSetpointVelocityX(Luint32 u32Index, Luint32 u32Value)
{
	vSIL3_NUM_CONVERT__Array_U32(&sTrackDB.sDB.sRunProfile.u8BrakingSetPointSpeed_mms[u32Index][0], u32Value);
}

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Value		## Desc ##
 * @param[in]		u32Index		## Desc ##
 * @st_funcMD5		893E613B0995468405333851C2558E10
 * @st_funcID		LCCM655R0.FILE.088.FUNC.026
 */
void vFCU_FCTL_TRACKDB_WIN32__Set_Profile_Spare(Luint32 u32Index, Luint32 u32Value)
{
	vSIL3_NUM_CONVERT__Array_U32(&sTrackDB.sDB.sRunProfile.u8SpareData[u32Index][0], u32Value);
}


/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		71B875E9D443D73BF9E31D1ED1EFF7B9
 * @st_funcID		LCCM655R0.FILE.088.FUNC.027
 */
Luint16 u16FCTL_TRAKDB_WIN32__ComputeCRC(void)
{

	Luint16 u16Size;
	Luint16 u16CRC;
	Luint8 *pu8Array;

	//get our size
	u16Size = u16FCU_FCTL_TRACKDB_WIN32__Get_StructureSize();

	//add room for the CRC
	u16Size -= 2;

	//todo:
	//check the size is aligned and safe

	//array
	pu8Array = (Luint8*)&sTrackDB;

	//do the actual CRC
	u16CRC = u16SIL3_SWCRC__CRC(pu8Array, u16Size);

	return u16CRC;
}

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u16Value		## Desc ##
 * @st_funcMD5		9D02B39F99268F9B0A5A5032F2F79675
 * @st_funcID		LCCM655R0.FILE.088.FUNC.028
 */
void vFCU_FCTL_TRACKDB_WIN32__Set_CRC(Luint16 u16Value)
{
	vSIL3_NUM_CONVERT__Array_U16(&sTrackDB.sDB.u8CRC[0], u16Value);
}

#endif //WIN32
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


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

void vFCU_FCTL_TRACKDB_WIN32__Init(void)
{


}



void vFCU_FCTL_TRACKDB_WIN32__Process(void)
{


}

//zero the array
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
Luint16 u16FCU_FCTL_TRACKDB_WIN32__Get_StructureSize(void)
{
	return (Luint16)sizeof(struct _strTrackDatabase);

}

//Update the internal structure from an extrnal byte array
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

void vFCU_FCTL_TRACKDB_WIN32__Set_Header(Luint32 u32Value)
{
	vNUMERICAL_CONVERT__Array_U32(&sTrackDB.sDB.u8Header[0], u32Value);
}

//The total length of the data from after this point to the end of the CRC
void vFCU_FCTL_TRACKDB_WIN32__Set_DataLength(Luint32 u32Value)
{
	vNUMERICAL_CONVERT__Array_U32(&sTrackDB.sDB.u8DataLength[0], u32Value);
}

//This is the ID of the track database entry.  User should match this to
//what is expected for the current run
void vFCU_FCTL_TRACKDB_WIN32__Set_TrackID(Luint32 u32Value)
{
	vNUMERICAL_CONVERT__Array_U32(&sTrackDB.sDB.u8TrackID[0], u32Value);
}

//Track beginning. Should be always 0 by construction
void vFCU_FCTL_TRACKDB_WIN32__Set_TrackStartXPos(Luint32 u32Value)
{
	vNUMERICAL_CONVERT__Array_U32(&sTrackDB.sDB.u8TrackBeginningXPosition_mm[0], u32Value);
}

//Track end. x position of foam pit
void vFCU_FCTL_TRACKDB_WIN32__Set_TrackEndXPos(Luint32 u32Value)
{
	vNUMERICAL_CONVERT__Array_U32(&sTrackDB.sDB.u8TrackEndXPosition_mm[0], u32Value);
}

//Minimum x position in tube to start using LRF.
//Called "min position to use laser range finder" in FCU spec 2.3
void vFCU_FCTL_TRACKDB_WIN32__Set_LRF_StartXPos(Luint32 u32Value)
{
	vNUMERICAL_CONVERT__Array_U32(&sTrackDB.sDB.u8LRFAreaBeginningXPosition_mm[0], u32Value);
}

//Number of stripes on this track
void vFCU_FCTL_TRACKDB_WIN32__Set_NumStripes(Luint32 u32Value)
{
	vNUMERICAL_CONVERT__Array_U32(&sTrackDB.sDB.u8NumberOfStripes[0], u32Value);
}

void vFCU_FCTL_TRACKDB_WIN32__Set_StripeStartX(Luint32 u32Index, Luint32 u32Value)
{
	vNUMERICAL_CONVERT__Array_U32(&sTrackDB.sDB.u8StripeBeginningXPosition_mm[u32Index][0], u32Value);
}

void vFCU_FCTL_TRACKDB_WIN32__Set_HeaderSpare(Luint32 u32Index, Luint32 u32Value)
{
	vNUMERICAL_CONVERT__Array_U32(&sTrackDB.sDB.u8SpareData[u32Index][0], u32Value);
}

//Footer to know we are valid here
void vFCU_FCTL_TRACKDB_WIN32__Set_Footer(Luint32 u32Value)
{
	vNUMERICAL_CONVERT__Array_U32(&sTrackDB.sDB.u8Footer[0], u32Value);
}

//x position of the front of the pusher car (or rear of pod) before the run. Called "pusher start x position" in FCU spec 2.3 "*/
void vFCU_FCTL_TRACKDB_WIN32__Set_Profile_PusherFrontStartPos(Luint32 u32Value)
{
	vNUMERICAL_CONVERT__Array_U32(&sTrackDB.sDB.sRunProfile.u8PusherFrontStartXPosition_mm[0], u32Value);
}

//expected x position of the front of the pusher car at the end of push phase. Called "end pushed phase x position" in FCU spec 1.1 */
void vFCU_FCTL_TRACKDB_WIN32__Set_Profile_PusherFrontEndPos(Luint32 u32Value)
{
	vNUMERICAL_CONVERT__Array_U32(&sTrackDB.sDB.sRunProfile.u8PusherFrontEndXPosition_mm[0], u32Value);
}

//arget x position of pod front at the end of the run. Called "stop x position" in FCU spec 8.4 */
void vFCU_FCTL_TRACKDB_WIN32__Set_Profile_PodFrontTargetXPos(Luint32 u32Value)
{
	vNUMERICAL_CONVERT__Array_U32(&sTrackDB.sDB.sRunProfile.u8PodFrontTargetXPosition_mm[0], u32Value);
}

//Number of setpoints of braking curve for this run.
void vFCU_FCTL_TRACKDB_WIN32__Set_Profile_NumSetpoints(Luint32 u32Value)
{
	vNUMERICAL_CONVERT__Array_U32(&sTrackDB.sDB.sRunProfile.u8NumberOfSetpoints[0], u32Value);
}

void vFCU_FCTL_TRACKDB_WIN32__Set_Profile_BrakeSetpointPosX(Luint32 u32Index, Luint32 u32Value)
{
	vNUMERICAL_CONVERT__Array_U32(&sTrackDB.sDB.sRunProfile.u8BrakingSetPointXPosition_mm[u32Index][0], u32Value);
}

void vFCU_FCTL_TRACKDB_WIN32__Set_Profile_BrakeSetpointVelocityX(Luint32 u32Index, Luint32 u32Value)
{
	vNUMERICAL_CONVERT__Array_U32(&sTrackDB.sDB.sRunProfile.u8BrakingSetPointSpeed_mms[u32Index][0], u32Value);
}

void vFCU_FCTL_TRACKDB_WIN32__Set_Profile_Spare(Luint32 u32Index, Luint32 u32Value)
{
	vNUMERICAL_CONVERT__Array_U32(&sTrackDB.sDB.sRunProfile.u8SpareData[u32Index][0], u32Value);
}


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
	u16CRC = u16SWCRC__CRC(pu8Array, u16Size);

	return u16CRC;
}

void vFCU_FCTL_TRACKDB_WIN32__Set_CRC(Luint16 u16Value)
{
	vNUMERICAL_CONVERT__Array_U16(&sTrackDB.sDB.u8CRC[0], u16Value);
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


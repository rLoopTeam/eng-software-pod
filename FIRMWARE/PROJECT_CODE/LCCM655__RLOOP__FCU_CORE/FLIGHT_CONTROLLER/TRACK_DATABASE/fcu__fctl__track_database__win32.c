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

#include <stdio.h>

Luint8 u32WIN32_TRACK_DATABASE[32000];

//the structure
extern struct _strFCU sFCU;

//The current working track database
extern TS_FCU_TRACK_DB sTrackDB;

/***************************************************************************//**
 * @brief
 * Init the track database on WIN32.  What we want to do here is to load up
 * a normal track databse into the FCU
 * 
 * @st_funcMD5		E54E0B6EFABF762040B6145F052A5CBC
 * @st_funcID		LCCM655R0.FILE.088.FUNC.001
 */
void vFCU_FCTL_TRACKDB_WIN32__Init(void)
{

	//on win32 simulate, read the file in
	FILE * pFile = fopen("..\\..\\..\\..\\FIRMWARE\\PROJECT_CODE\\LCCM655__RLOOP__FCU_CORE\\FLIGHT_CONTROLLER\\TRACK_DATABASE\\DATABASES\\database2.bin", "rb");

	if (pFile != 0)
	{

		//set the file pointer to end of file
		fseek(pFile, 0, SEEK_END);

		//get the file size
		Luint32 u32Size = ftell(pFile);

		//return the file pointer to begin of file if you want to read it
		rewind(pFile);

		//read in
		fread(&u32WIN32_TRACK_DATABASE[0], 1, u32Size, pFile);

		fclose(pFile);

	}

}



/***************************************************************************//**
 * @brief
 * Do any win32 processing
 * 
 * @st_funcMD5		863EDC7743B4BC2A097EFB5B30CBDDB5
 * @st_funcID		LCCM655R0.FILE.088.FUNC.002
 */
void vFCU_FCTL_TRACKDB_WIN32__Process(void)
{
	//nothing here
}

/***************************************************************************//**
 * @brief
 * Zero the array
 * Use this before trying to update a fresh database
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

	//do a blind clear
	for(u16Counter = 0U; u16Counter < (Luint16)sizeof(TS_FCU_TRACK_DB); u16Counter++)
	{
		pu8Struct[u16Counter] = 0x00U;

	}
}



/***************************************************************************//**
 * @brief
 * ToDoGet the copy of the array in bytes
 * 
 * @param[in]		*pu8ByteArray			Pointer to return array
 * @st_funcMD5		073378FAE4C956D8FB0C3F0D2376A8AE
 * @st_funcID		LCCM655R0.FILE.088.FUNC.004
 */
void vFCU_FCTL_TRACKDB_WIN32__Get_Array(Luint8 *pu8ByteArray)
{
	Luint16 u16Counter;
	Luint8 * pu8Struct;

	//get a pointer to our first byte
	pu8Struct = (Luint8*)&sTrackDB;

	//do a blind copy
	for(u16Counter = 0U; u16Counter < (Luint16)sizeof(TS_FCU_TRACK_DB); u16Counter++)
	{
		pu8ByteArray[u16Counter] = pu8Struct[u16Counter];

	}
}

/***************************************************************************//**
 * @brief
 * Return the structure size
 * 
 * @st_funcMD5		03FDD59CDD8D94E154BE7574806E08C9
 * @st_funcID		LCCM655R0.FILE.088.FUNC.005
 */
Luint16 u16FCU_FCTL_TRACKDB_WIN32__Get_StructureSize(void)
{
	return (Luint16)sizeof(TS_FCU_TRACK_DB);

}


/***************************************************************************//**
 * @brief
 * Update the internal structure from an extrnal byte array
 * 
 * @param[in]		pu8ByteArray			Pointer to input array
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
	for(u16Counter = 0U; u16Counter < (Luint16)sizeof(TS_FCU_TRACK_DB); u16Counter++)
	{
		pu8Struct[u16Counter] = pu8ByteArray[u16Counter];

	}

}


/***************************************************************************//**
 * @brief
 * Set the structure header
 * 
 * @param[in]		u32Value				Header value
 * @st_funcMD5		D3F26AEFAAF4E792541D578C93EBF5AD
 * @st_funcID		LCCM655R0.FILE.088.FUNC.007
 */
void vFCU_FCTL_TRACKDB_WIN32__Set_Header(Luint32 u32Value)
{
	vSIL3_NUM_CONVERT__Array_U32(&sTrackDB.u8Header[0], u32Value);
}

/*
//Do we want to use the accelerometers on this track?
void vFCU_FCTL_TRACKDB_WIN32__Set_Accel__Use(Luint8 u8TrackIndex, Luint8 u8Value)
{
	sTrackDB.sDB2[u8TrackIndex].sAccel.u8Use = u8Value;
}
*/

//Accel threshold in mm/ss
void vFCU_FCTL_TRACKDB_WIN32__Set_Accel__Threshold_mm_ss(Luint8 u8TrackIndex, Lint32 s32Thresh_mm_ss)
{
	vSIL3_NUM_CONVERT__Array_S32(&sTrackDB.sDB2[u8TrackIndex].sAccel.u8AccelThresh_mm_ss[0], s32Thresh_mm_ss);
}

//Accel threshold time
void vFCU_FCTL_TRACKDB_WIN32__Set_Accel__Threshold_x10ms(Luint8 u8TrackIndex, Luint16 u16Thresh_x10ms)
{
	vSIL3_NUM_CONVERT__Array_U32(&sTrackDB.sDB2[u8TrackIndex].sAccel.u8AccelThresh_x10ms[0], u16Thresh_x10ms);
}

//Decel threshold in mm/ss
void vFCU_FCTL_TRACKDB_WIN32__Set_Decel__Threshold_mm_ss(Luint8 u8TrackIndex, Lint32 s32Thresh_mm_ss)
{
	vSIL3_NUM_CONVERT__Array_S32(&sTrackDB.sDB2[u8TrackIndex].sAccel.u8DecelThresh_mm_ss[0], s32Thresh_mm_ss);
}

//Decel threshold time
void vFCU_FCTL_TRACKDB_WIN32__Set_Decel__Threshold_x10ms(Luint8 u8TrackIndex, Luint16 u16Thresh_x10ms)
{
	vSIL3_NUM_CONVERT__Array_U32(&sTrackDB.sDB2[u8TrackIndex].sAccel.u8DecelThresh_x10ms[0], u16Thresh_x10ms);
}

/*
void vFCU_FCTL_TRACKDB_WIN32__Set_Track__TrackStart_mm(Luint8 u8TrackIndex, Luint32 u32Value)
{
	vSIL3_NUM_CONVERT__Array_U32(&sTrackDB.sDB2[u8TrackIndex].sTrack.u8TrackStart_mm[0], u32Value);
}

void vFCU_FCTL_TRACKDB_WIN32__Set_Track__TrackEnd_mm(Luint8 u8TrackIndex, Luint32 u32Value)
{
	vSIL3_NUM_CONVERT__Array_U32(&sTrackDB.sDB2[u8TrackIndex].sTrack.u8TrackEnd_mm[0], u32Value);
}

void vFCU_FCTL_TRACKDB_WIN32__Set_Track__TrackLength_mm(Luint8 u8TrackIndex, Luint32 u32Value)
{
	vSIL3_NUM_CONVERT__Array_U32(&sTrackDB.sDB2[u8TrackIndex].sTrack.u8TrackLength_mm[0], u32Value);
}
*/

void vFCU_FCTL_TRACKDB_WIN32__Set_Time__Accel_Coast_x10ms(Luint8 u8TrackIndex, Luint32 u32Value)
{
	vSIL3_NUM_CONVERT__Array_U32(&sTrackDB.sDB2[u8TrackIndex].sTime.u8Accel_Coast[0], u32Value);
}

void vFCU_FCTL_TRACKDB_WIN32__Set_Time__Coast_Brake_x10ms(Luint8 u8TrackIndex, Luint32 u32Value)
{
	vSIL3_NUM_CONVERT__Array_U32(&sTrackDB.sDB2[u8TrackIndex].sTime.u8Coast_Brake[0], u32Value);
}

void vFCU_FCTL_TRACKDB_WIN32__Set_Time__Brake_Spindown_x10ms(Luint8 u8TrackIndex, Luint32 u32Value)
{
	vSIL3_NUM_CONVERT__Array_U32(&sTrackDB.sDB2[u8TrackIndex].sTime.u8Brake_Spindown[0], u32Value);
}

/*
void vFCU_FCTL_TRACKDB_WIN32__Set_UsePusherSeparation(Luint8 u8TrackIndex, Luint8 u8Value)
{
	sTrackDB.sDB2[u8TrackIndex].sControl.u8EnablePuserSeparationDetection = u8Value;
}
*/

/***************************************************************************//**
 * @brief
 * Compute the CRC across the structure
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
 * Update the CRC
 * 
 * @param[in]		u16Value		CRC value
 * @st_funcMD5		9D02B39F99268F9B0A5A5032F2F79675
 * @st_funcID		LCCM655R0.FILE.088.FUNC.028
 */
void vFCU_FCTL_TRACKDB_WIN32__Set_CRC(Luint16 u16Value)
{
	vSIL3_NUM_CONVERT__Array_U16(&sTrackDB.u8CRC[0], u16Value);
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


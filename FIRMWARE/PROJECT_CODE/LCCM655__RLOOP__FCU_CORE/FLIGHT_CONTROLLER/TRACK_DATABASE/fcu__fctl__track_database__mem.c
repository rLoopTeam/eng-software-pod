/**
 * @file		FCU__FCTL__TRACK_DATABASE__MEM.C
 * @brief		Memory load and save of the track databases
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
 * @addtogroup FCU__FLIGHT_CTL__TRACK_DATABASE__MEM
 * @ingroup FCU
 * @{ */

#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
#if C_LOCALDEF__LCCM655__ENABLE_TRACK_DB == 1U

#include "fcu__fctl__track_database__types.h"

//locals
void vFCU_FCLT_TRACKDB_MEM__Save_TrackDB(void);
Lint16 s16FCU_FCLT_TRACKDB_MEM__Load_TrackDB(void);

//the structure
extern struct _strFCU sFCU;

//The current working track database
extern TS_FCU_TRACK_DB sTrackDB;

#ifdef WIN32
	//win32 loaded track database for emulation
	extern Luint8 u32WIN32_TRACK_DATABASE[32000];
#endif

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		AA87CDA3908B109DBFD6F1FE61B04FE0
 * @st_funcID		LCCM655R0.FILE.086.FUNC.001
 */
void vFCU_FCTL_TRACKDB_MEM__Init(void)
{
	Lint16 s16Return;

	//load up our database
	s16Return = s16FCU_FCLT_TRACKDB_MEM__Load_TrackDB();

}



/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		BF9E2D2FD7A2F82C2241D8CFF63AC9EB
 * @st_funcID		LCCM655R0.FILE.086.FUNC.002
 */
void vFCU_FCTL_TRACKDB_MEM__Process(void)
{
	//nothing
}

//
/***************************************************************************//**
 * @brief
 * Upload a chunk of memory from the eth to the FCU
 * 
 * @param[in]		*pu8Buffer				Pointer to ethernet buffer
 * @param[in]		u32Length				Total length of data
 * @param[in]		u32ChunkIndex			Index for multipart (should be 0)
 * @st_funcMD5		BF45F30CFD3CD8648FF594932635D7E5
 * @st_funcID		LCCM655R0.FILE.086.FUNC.003
 */
void vFCU_FCTL_TRACKDB_MEM__UploadChunk(Luint32 u32ChunkIndex, Luint32 u32Length, Luint8 *pu8Buffer)
{
	Luint8 *pu8Temp;
	Luint32 u32Offset;
	Luint32 u32Counter;

	//point to our working track database
	pu8Temp = (Luint8*)&sTrackDB;

	//create the offiset
	//rule here is that all chunk indexes have to be the same, else we need to track the packet sizes
	u32Offset = u32ChunkIndex * u32Length;

	//set the offset
	pu8Temp += u32Offset;

	//do the mem copy
	for(u32Counter = 0U; u32Counter < u32Length; u32Counter++)
	{
		pu8Temp[u32Counter] = pu8Buffer[u32Counter];
	}



	//we need to determine what the last chunk size is
	u32Offset = (u32ChunkIndex + 1U) * u32Length;
	if(u32Offset >= (Luint32)sizeof(TS_FCU_TRACK_DB))
	{
		//save it
		vFCU_FCLT_TRACKDB_MEM__Save_TrackDB();
	}
	else
	{
		//keep going.
	}

}


//
/***************************************************************************//**
 * @brief
 * Save the current track index into the memory buffer
 * 
 * @param[in]		u32Index		## Desc ##
 * @st_funcMD5		43D277C878ECC7EB4B16C5C5AD0D776B
 * @st_funcID		LCCM655R0.FILE.086.FUNC.004
 */
void vFCU_FCLT_TRACKDB_MEM__Save_TrackDB(void)
{

	Luint32 u32Length;
	Luint32 u32Addx;
	Lint16 s16Return;

	//get the length of the structure
	u32Length = (Luint32)sizeof(TS_FCU_TRACK_DB);

	//set the first only addx
	u32Addx = 0x00180000U;

	//erase the area
#ifndef WIN32
	s16Return = s16RM4_FLASH__SectorErase(1, u32Addx, 0x0001FFFFU);
#else
	s16Return = 0;
#endif
	if(s16Return >= 0)
	{
		//write the new data
	#ifndef WIN32
		s16Return = s16RM4_FLASH__BlockProgram(1, u32Addx, (Luint32)&sTrackDB, u32Length);
	#else
		s16Return = 0;
	#endif
		if(s16Return >= 0)
		{
			//reload

		}
		else
		{

		}
	}
	else
	{
		//big error during erase
	}

}

/***************************************************************************//**
 * @brief
 * Load a track database from the memory pool based on a index.
 * 
 * @return			0 = success
 * @st_funcMD5		FF11C88AF01843D3751C86BF064EF7D5
 * @st_funcID		LCCM655R0.FILE.086.FUNC.005
 */
Lint16 s16FCU_FCLT_TRACKDB_MEM__Load_TrackDB(void)
{
	Lint16 s16Return;
	Luint32 u32Length;
	Luint8 *pu8Mem;
	Luint8 *pu8Temp;
	Luint32 u32Counter;
	Luint16 u16CRC;
	Luint16 u16CRCTest;


	//get the length of the structure
	u32Length = (Luint32)sizeof(TS_FCU_TRACK_DB);

	//point to our working track database
	pu8Temp = (Luint8 *)&sTrackDB;

	//addx of our memory
#ifndef WIN32
	pu8Mem = (Luint8 *)0x00180000U;
#else
	//on win32 load from our file.
	pu8Mem = (Luint8 *)&u32WIN32_TRACK_DATABASE[0];
#endif

	//blind copy
	for(u32Counter = 0U; u32Counter < u32Length; u32Counter++)
	{
		pu8Temp[u32Counter] = pu8Mem[u32Counter];
	}

	//check the CRC
	pu8Temp = (Luint8*)&sTrackDB;

	//subtract 2 for the CRC
	u32Length -= 2U;

	//do the actual CRC
	u16CRC = u16SIL3_SWCRC__CRC(pu8Temp, u32Length);

	//check for a match
	u16CRCTest = u16SIL3_NUM_CONVERT__Array(&sTrackDB.u8CRC[0]);
	if(u16CRC == u16CRCTest)
	{
		s16Return = 0;
	}
	else
	{
		//fault
		s16Return = -1;
	}

	return s16Return;

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


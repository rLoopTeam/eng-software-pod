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

//the structure
extern struct _strFCU sFCU;

//The current working track database
extern struct _strTrackDatabase sTrackDB;

void vFCU_FCTL_TRACKDB_MEM__Init(void)
{


}



void vFCU_FCTL_TRACKDB_MEM__Process(void)
{

}

//upload a chunk of memory from the eth to the FCU
void vFCU_FCTL_TRACKDB_MEM__UploadChunk(Luint32 u32TrackID, Luint32 u32ChunkIndex, Luint32 u32Length, Luint8 *pu8Buffer)
{
	Luint8 *pu8Temp;
	Luint32 u32Offset;
	Luint32 u32Counter;

	if(u32TrackID < C_FCTL_TRACKDB__MAX_MEM_DATABASES)
	{
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
		if(u32Offset >= (Luint32)sizeof(struct _strTrackDatabase))
		{
			//save it
		}
		else
		{
			//keep going.
		}

	}
	else
	{
		//big error
	}

}


//save the current track index into the memory buffer
void vFCU_FCLT_TRACKDB_MEM__Save_TrackDB(Luint32 u32Index)
{

	Luint32 u32Length;
	Luint32 u32Addx;
	Lint16 s16Return;

	if(u32Index < C_FCTL_TRACKDB__MAX_MEM_DATABASES)
	{
		//get the length of the structure
		u32Length = sizeof(struct _strTrackDatabase);

		//compute the memory offset
		switch(u32Index)
		{
			case 0:
				u32Addx = 0x00180000U;
				break;
			case 1:
				u32Addx = 0x001A0000U;
				break;
			case 2:
				u32Addx = 0x001C0000U;
				break;
			case 3:
				u32Addx = 0x001E0000U;
				break;
			case 4:
				u32Addx = 0x00200000U;
				break;
			case 5:
				u32Addx = 0x00220000U;
				break;
			case 6:
				u32Addx = 0x00240000U;
				break;
			case 7:
				u32Addx = 0x00260000U;
				break;

			default:
				//safety and overwrite the last DB
				u32Addx = 0x00260000U;
				break;

		}//switch(u32Index)


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
				//relaod

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
	else
	{
		//big error
	}

}


//Load a track database from the memory pool based on a index.
Lint16 s16FCU_FCLT_TRACKDB_MEM__Load_TrackDB(Luint32 u32Index)
{
	Lint16 s16Return;

	//init
	s16Return = 0;



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


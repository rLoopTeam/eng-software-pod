/**
 * @file		FCU__LASER_CONT__TRACK_DATABASE.C
 * @brief		Maintain a track / contrast sensor database
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
 * @addtogroup FCU__LASER_CONTRAST__TRACK_DATABASE
 * @ingroup FCU
 * @{ */


#include "../../fcu_core.h"
#if C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST == 1U

extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Create the database
 *
 */
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		3C773A24A7F84F027224A6C44349E55E
 * @st_funcID		LCCM655R0.FILE.041.FUNC.001
 */
void vFCU_LASERCONT_TRKDB__Init(void)
{
	Luint8 u8LaserCount;

	//for now just fill in the track database manually
	//we may need several databases, and one for the test track too
	for(u8LaserCount = 0U; u8LaserCount < (Luint8)LASER_CONT__MAX; u8LaserCount++)
	{

		//clear the elapsed maker counter
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u8ElapsedCount = 0U;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistRemain = 0U;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32LastIncrement = 0U;

		//setup
		//todo: this is a hard coded hack, fix it.
		//sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[0] = 6.48
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[0] = 1493520;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[1] = 1463040;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[2] = 1432560;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[3] = 1402080;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[4] = 1371600;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[5] = 1341120;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[6] = 1310640;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[7] = 1280160;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[8] = 1249680;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[9] = 1219200;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[10] = 1188720;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[11] = 1158240;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[12] = 1127760;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[13] = 1097280;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[14] = 1066800;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[15] = 1036320;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[16] = 1005840;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[17] = 975360;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[18] = 944880;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[19] = 914400;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[20] = 883920;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[21] = 853440;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[22] = 822960;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[23] = 792480;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[24] = 762000;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[25] = 731520;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[26] = 701040;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[27] = 670560;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[28] = 640080;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[29] = 609600;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[30] = 579120;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[31] = 548640;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[32] = 518160;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[33] = 487680;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[34] = 457200;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[35] = 426720;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[36] = 396240;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[37] = 365760;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[38] = 335280;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[39] = 304800;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[40] = 274320;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[41] = 274116;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[42] = 273913;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[43] = 273710;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[44] = 273507;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[45] = 273304;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[46] = 273100;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[47] = 272897;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[48] = 272694;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[49] = 272491;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[50] = 243840;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[51] = 213360;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[52] = 182880;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[53] = 152400;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[54] = 121920;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[55] = 121716;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[56] = 121513;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[57] = 121310;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[58] = 121107;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[59] = 91440;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[60] = 60960;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[61] = 30480;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[62] = 0;
		
		
	}//for(u8LaserCount = 0U; u8LaserCount < (Luint8)LASER_CONT__MAX; u8LaserCount++)

}

/***************************************************************************//**
 * @brief
 *  Process track database systems
 * 
 * @st_funcMD5		6EF07E2EEC2ECB4D66687A49F883A6C3
 * @st_funcID		LCCM655R0.FILE.041.FUNC.002
 */
void vFCU_LASERCONT_TRKDB__Process(void)
{
	//nothing here
}


/***************************************************************************//**
 * @brief
 * Increment the next marker position based on a rising edge from the system.
 * 
 * @param[in]		eLaser					The laser index
 * @st_funcMD5		82CCBDEE1895BD30BA9EC79492F2C184
 * @st_funcID		LCCM655R0.FILE.041.FUNC.003
 */
void vFCU_LASERCONT_TRKDB__Inc_Marker(E_FCU__LASER_CONT_INDEX_T eLaser)
{
	//increment the maker position
	if(eLaser < LASER_CONT__MAX)
	{
		sFCU.sContrast.sTrackDatabase[(Luint8)eLaser].u8ElapsedCount++;
	}
	else
	{
		//big error, out of range
	}
}

/***************************************************************************//**
 * @brief
 * Compute the previous track distance
 * Should really only do this on a new marker, but for constatnt CPU loading can do repeateldy.
 * 
 * @param[in]		eLaser				Laser Index
 * @st_funcMD5		58AB4F17401D6FA1ACE8E38F7211DE8E
 * @st_funcID		LCCM655R0.FILE.041.FUNC.004
 */
void vFCU_LASERCONT_TRKDB__Compute(E_FCU__LASER_CONT_INDEX_T eLaser)
{
	Luint8 u8Index;
	Luint8 u8Index1;

	if(eLaser < LASER_CONT__MAX)
	{
		//can only do this is if we are > 0
		if(sFCU.sContrast.sTrackDatabase[(Luint8)eLaser].u8ElapsedCount > 0)
		{

			//get the distance remaining index
			u8Index = sFCU.sContrast.sTrackDatabase[(Luint8)eLaser].u8ElapsedCount;
			//safe due to entry condition
			u8Index1 = sFCU.sContrast.sTrackDatabase[(Luint8)eLaser].u8ElapsedCount - 1U;


			//based on the track DB the distance remaining is easy.
			sFCU.sContrast.sTrackDatabase[(Luint8)eLaser].u32DistRemain = sFCU.sContrast.sTrackDatabase[(Luint8)eLaser].u32DistanceRemain_mm[u8Index];

			//get the elapsed distance, only
			sFCU.sContrast.sTrackDatabase[(Luint8)eLaser].u32LastIncrement = sFCU.sContrast.sTrackDatabase[(Luint8)eLaser].u32DistanceRemain_mm[u8Index1] - sFCU.sContrast.sTrackDatabase[(Luint8)eLaser].u32DistanceRemain_mm[u8Index];

		}
		else
		{
			//we have not passed the first maker yet, so we can't get a distance.
			//todo:
			//Handle this
		}

	}
	else
	{
		//todo:
		//error

	}
}


/***************************************************************************//**
 * @brief
 * Return the distance remaining until the end of the track in mm
 * 
 * @param[in]		eLaser					Laser Index
 * @st_funcMD5		5C7C6D7E6AD5B0BD3CC857371100E2CC
 * @st_funcID		LCCM655R0.FILE.041.FUNC.005
 */
Luint32 u32FCU_LASERCONT_TRKDB__Get_DistanceRemain_mm(E_FCU__LASER_CONT_INDEX_T eLaser)
{
	return sFCU.sContrast.sTrackDatabase[(Luint8)eLaser].u32DistRemain;
}


/***************************************************************************//**
 * @brief
 * Gets the distance in the previous 100ft, 30.48m segment. This does not include the distance
 * Over the ripple strips, only full 100ft strips.
 * 
 * @param[in]		eLaser				The laser index
 * @st_funcMD5		8BFF83813FEA97EB683772F0EBA4ABBB
 * @st_funcID		LCCM655R0.FILE.041.FUNC.006
 */
Luint32 u32FCU_LASERCONT_TRKDB__Get_DistancePrevSeg_mm(E_FCU__LASER_CONT_INDEX_T eLaser)
{
	return sFCU.sContrast.sTrackDatabase[(Luint8)eLaser].u32LastIncrement;
}

#endif
#ifndef C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST
	#error
#endif

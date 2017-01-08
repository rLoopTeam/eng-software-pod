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
 * @st_funcMD5		5BCA6D7C693A37A2E92E348B16F52B90
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
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistElapsed = 0U;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32LastIncrement = 0U;

		//bit of safety here.
#if C_FCU__LASER_CONTRAST__MAX_STRIPES != 55U
	#error
#endif

		//setup
		//todo: this is a hard coded hack, fix it.
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[54] = 1249680;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[53] = 1219200;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[52] = 1188720;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[51] = 1158240;

		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[50] = 1127760;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[49] = 1097280;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[48] = 1066800;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[47] = 1036320;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[46] = 1005840;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[45] = 975360;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[44] = 944880;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[43] = 914400;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[42] = 883920;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[41] = 853440;

		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[40] = 822960;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[39] = 792480;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[38] = 762000;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[37] = 731520;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[36] = 701040;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[35] = 670560;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[34] = 640080;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[33] = 609600;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[32] = 579120;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[31] = 548640;
		
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[30] = 518160;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[29] = 487680;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[28] = 457200;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[27] = 426720;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[26] = 396240;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[25] = 365760;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[24] = 335280;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[23] = 304800;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[22] = 274320;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[21] = 274116;

		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[20] = 273913;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[19] = 273710;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[18] = 273507;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[17] = 273304;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[16] = 273100;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[15] = 272897;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[14] = 272694;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[13] = 272491;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[12] = 243840;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[11] = 213360;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[10] = 182880;

		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[9] = 152400;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[7] = 121920;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[7] = 121716;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[6] = 121513;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[5] = 121310;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[4] = 121107;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[3] = 91440;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[2] = 60960;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[1] = 30480;
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceElapsed_mm[0] = 0;

		
	}//for(u8LaserCount = 0U; u8LaserCount < (Luint8)LASER_CONT__MAX; u8LaserCount++)

}

/***************************************************************************//**
 * @brief
 * Process track database systems
 * 
 * @st_funcMD5		59870A039EA6479C2E49ADD9A7F4EE73
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
 * @st_funcMD5		FF8FA81B389EEB2F431E86CD917648DA
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


			//based on the track DB the distance elapsed is easy.
			sFCU.sContrast.sTrackDatabase[(Luint8)eLaser].u32DistElapsed = sFCU.sContrast.sTrackDatabase[(Luint8)eLaser].u32DistanceElapsed_mm[u8Index];

			//get the elapsed distance, only
			sFCU.sContrast.sTrackDatabase[(Luint8)eLaser].u32LastIncrement = sFCU.sContrast.sTrackDatabase[(Luint8)eLaser].u32DistanceElapsed_mm[u8Index1] - sFCU.sContrast.sTrackDatabase[(Luint8)eLaser].u32DistanceElapsed_mm[u8Index];

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
 * Return the distance that has current elpased.
 * 
 * @param[in]		eLaser					Laser Index
 * @st_funcMD5		0F5DAA0273EF50CD102CD47026CF8B6C
 * @st_funcID		LCCM655R0.FILE.041.FUNC.005
 */
Luint32 u32FCU_LASERCONT_TRKDB__Get_DistanceElapsed_mm(E_FCU__LASER_CONT_INDEX_T eLaser)
{
	return sFCU.sContrast.sTrackDatabase[(Luint8)eLaser].u32DistElapsed;
}


/***************************************************************************//**
 * @brief
 * Gets the distance in the previous 100ft, 30.48m segment. This does not include the distance
 * Over the ripple strips, only full 100ft strips.
 * 
 * @param[in]		eLaser				The laser index
 * @st_funcMD5		DC0197FE8B3ADC5DD71049F3419E3E40
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

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
void vFCU_LASERCONT_TRKDB__Init(void)
{
	Luint8 u8LaserCount;

	//for now just fill in the track database manually
	//we may need several databases, and one for the test track too
	for(u8LaserCount = 0U; u8LaserCount < (Luint8)LASER_CONT__MAX; u8LaserCount++)
	{

		//clear the elapsed maker counter
		sFCU.sContrast.sTrackDatabase[u8LaserCount].u8ElapsedCount = 0U;


		//setup
		//todo: this is a hard coded hack, fix it.
		//sFCU.sContrast.sTrackDatabase[u8LaserCount].u32DistanceRemain_mm[0] = 6.48

	}//for(u8LaserCount = 0U; u8LaserCount < (Luint8)LASER_CONT__MAX; u8LaserCount++)

}

/***************************************************************************//**
 * @brief
 * Process track database systems
 *
 */
void vFCU_LASERCONT_TRKDB__Process(void)
{

}


//increment the next marker position based on a rising edge from the system.
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

//compute the previous track distance
//should really only do this on a new marker, but for constatnt CPU loading can do repeateldy.
void vFCU_LASERCONT_TRKDB__Compute(E_FCU__LASER_CONT_INDEX_T eLaser)
{
	if(eLaser < LASER_CONT__MAX)
	{
		//can only do this is if we are > 0
		if(sFCU.sContrast.sTrackDatabase[(Luint8)eLaser].u8ElapsedCount > 0)
		{

			//get the distance remaining
			//get the elapsed distance, only


		}
		else
		{
			//we have not passed the first maker yet, so we can't get a distance.
		}

	}
	else
	{

	}
}

//return the distance remaining until the end of the track in mm
Luint32 u32FCU_LASERCONT_TRKDB__Get_DistanceRemain_mm(E_FCU__LASER_CONT_INDEX_T eLaser)
{
	return 0;
}

//gets the distance in the previous 100ft, 30.48m segment. This does not include the distance
//over the ripple strips, only full 100ft strips.
Luint32 u32FCU_LASERCONT_TRKDB__Get_DistancePrevSeg_mm(E_FCU__LASER_CONT_INDEX_T eLaser)
{
	return 0;
}

#endif
#ifndef C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST
	#error
#endif

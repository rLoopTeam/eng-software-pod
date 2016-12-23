/**
 * @file		FCU__LASER_CONT.C
 * @brief		Contrast laser top level interface.
 * @note		http://confluence.rloop.org/display/SD/2.3.+Determine+Pod+x+Position%2C+Speed+and+Acceleration+in+tube
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
 * @addtogroup FCU__LASER_CONTRAST
 * @ingroup FCU
 * @{ */


#include "../fcu_core.h"
#if C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST == 1U

extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init the contrast laser system
 * 
 * @st_funcMD5		590B7FC2DBDF273D9CDE2745149FB0D1
 * @st_funcID		LCCM655R0.FILE.034.FUNC.001
 */
void vFCU_LASERCONT__Init(void)
{

	sFCU.sContrast.u32Guard1 = 0xAB12AB34U;
	sFCU.sContrast.u32Guard2 = 0x76540987U;

	//Update the distance remaining in mm.
	//This could be set to the max track distance, or some other distance, but we really need
	//to use caution here has if distremain = 0 then maybe the brakes will be hard on.
	sFCU.sContrast.u32DistRemain_mm = 0U;
	sFCU.sContrast.u32DistLastStripe_mm = 0U;

	//at the entry point here the N2HET should have created 3 programs for either
	//edge capture, or HTU.
	//todo: Verify the N2HET programs are valid and operating correctly.


	//init the timing list capture system
	vFCU_LASERCONT_TL__Init();

	//init veloc calculation
	vFCU_LASERCONT_VELOC__Init();

	//start track database
	vFCU_LASERCONT_TRKDB__Init();

}

/***************************************************************************//**
 * @brief
 * Process the laser contrast system
 * 
 * @st_funcMD5		D1F8C137ABF865560FD54E143FB36D33
 * @st_funcID		LCCM655R0.FILE.034.FUNC.002
 */
void vFCU_LASERCONT__Process(void)
{
	Luint8 u8LaserCount;
	Luint8 u8Test;

	if(sFCU.sContrast.u32Guard1 != 0xAB12AB34U)
	{
		//error
	}
	if(sFCU.sContrast.u32Guard2 != 0x76540987U)
	{
		//error
	}

	//process the timing list.
	vFCU_LASERCONT_TL__Process();

	//laser contrast will have a few states.
	//we can't really start timing until we are moving.
	//moving should be notified, and confirmed on the first marker.

	//process the velocity calculation.
	vFCU_LASERCONT_VELOC__Process();

	//compute the track database.
	vFCU_LASERCONT_TRKDB__Process();

	//process all the lasers
	for(u8LaserCount = 0U; u8LaserCount < (Luint8)LASER_CONT__MAX; u8LaserCount++)
	{
		u8Test = u8FCU_LASERCONT_TL__Get_NewRisingAvail((E_FCU__LASER_CONT_INDEX_T)u8LaserCount);
		if(u8Test == 1U)
		{

			//tell the track database about our new edge
			vFCU_LASERCONT_TRKDB__Inc_Marker((E_FCU__LASER_CONT_INDEX_T)u8LaserCount);

			//recompute the last distance covered and dist remain
			vFCU_LASERCONT_TRKDB__Compute((E_FCU__LASER_CONT_INDEX_T)u8LaserCount);

			//update our internal structure of either the dist remain, or a fault
			sFCU.sContrast.u32DistRemain_mm = u32FCU_LASERCONT_TRKDB__Get_DistanceRemain_mm((E_FCU__LASER_CONT_INDEX_T)u8LaserCount);

			//get the distance covered in the last stripe:
			//Note: This could be 0 when we are starting off before the first maker.
			sFCU.sContrast.u32DistLastStripe_mm = u32FCU_LASERCONT_TRKDB__Get_DistancePrevSeg_mm((E_FCU__LASER_CONT_INDEX_T)u8LaserCount);

			//use the previous distance to compute our veloc.

			//done with the flag, clear it.
			vFCU_LASERCONT_TL__Clear_NewRisingAvail((E_FCU__LASER_CONT_INDEX_T)u8LaserCount);
		}
		else
		{
			//laser edge not ready yet
			//todo: check for a timeout
		}

	}//for(u8LaserCount = 0U; u8LaserCount < (Luint8)LASER_CONT__MAX; u8LaserCount++)



}

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Key		## Desc ##
 * @st_funcMD5		9B7EF718A626E5BD6764A01761302CFF
 * @st_funcID		LCCM655R0.FILE.034.FUNC.004
 */
void vFCU_LASERCONT__Reset(Luint32 u32Key)
{

	if(u32Key == 0xABCDABCD)
	{
		//upper layer wants to reset the position system
	}
	else
	{
		//invalid key
	}


}


/***************************************************************************//**
 * @brief
 * Interrupt from the RM4 notification system
 * 
 * @param[in]		eLaser					The laser index
 * @st_funcMD5		85A22E789F8036525ED16796EED95EC4
 * @st_funcID		LCCM655R0.FILE.034.FUNC.003
 */
void vFCU_LASERCONT__ISR(E_FCU__LASER_CONT_INDEX_T eLaser, Luint32 u32Register)
{
	//pass off to the timing list
	vFCU_LASERCONT_TL__ISR(eLaser, u32Register);
}


#endif
#ifndef C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST
	#error
#endif

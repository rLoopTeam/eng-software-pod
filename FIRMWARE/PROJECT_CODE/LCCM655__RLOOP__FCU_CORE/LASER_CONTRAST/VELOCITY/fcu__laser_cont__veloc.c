/**
 * @file		FCU__LASER_CONT__VELOC.C
 * @brief		Velocity Calculator
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
 * @addtogroup FCU__LASER_CONTRAST__VELOC
 * @ingroup FCU
 * @{ */


#include "../../fcu_core.h"
#if C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST == 1U

extern struct _strFCU sFCU;


void vFCU_LASERCONT_VELOC__Init(void)
{

	sFCU.sContrast.sVeloc.u32CurrentVeloc_mms = 0U;;

}



void vFCU_LASERCONT_VELOC__Process(void)
{
	Luint8 u8LaserCount;
	Luint8 u8Temp;

	//so we need to know what the last captured rising edge was for purposes of veloc calculation
	for(u8LaserCount = 0U; u8LaserCount < (Luint8)LASER_CONT__MAX; u8LaserCount++)
	{

		//see if we have any new edges avail?
		u8Temp = u8FCU_LASERCONT_TL__Get_NewRisingAvail(u8LaserCount);
		if(u8Temp == 1U)
		{

			//we can compute the distance between stripes based on the database.
			//but we need the database here!!

			//OR: We need to know that there are no ripple strips.


			//clear
			vFCU_LASERCONT_TL__Clear_NewRisingAvail(u8LaserCount);

		}
		else
		{
			//no new data avail.
		}

	}//for(u8LaserCount = 0U; u8LaserCount < (Luint8)LASER_CONT__MAX; u8LaserCount++)

}



#endif
#ifndef C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST
	#error
#endif

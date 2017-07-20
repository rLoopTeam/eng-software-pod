/**
 * @file		FCU__LASER_CONT__VELOC.C
 * @brief		Velocity Calculator based on laser contrast sensor distance.
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
#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST == 1U

extern struct _strFCU sFCU;


/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		2248CD3745D2D329825B4B41A5F777E9
 * @st_funcID		LCCM655R0.FILE.040.FUNC.001
 */
void vFCU_LASERCONT_VELOC__Init(void)
{

	//sFCU.sContrast.sVeloc.u32CurrentVeloc_mms = 0U;;

}



/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		A630BB7D8CB5F66027917286E6DE41BC
 * @st_funcID		LCCM655R0.FILE.040.FUNC.002
 */
void vFCU_LASERCONT_VELOC__Process(void)
{
	//do nothing.

}

//get the result of the computation
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		50C036B4AF050E1193B9F57E0B5390FD
 * @st_funcID		LCCM655R0.FILE.040.FUNC.003
 */
Luint32 u32FCU_LASERCONT_VELOC__Get_CurrentVeloc_mms(void)
{
	return 0; //sFCU.sContrast.sVeloc.u32CurrentVeloc_mms;
}

//compute the veloc
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u64TimeDelta		## Desc ##
 * @param[in]		u32Distance		## Desc ##
 * @st_funcMD5		ECF00834753BE38E259AC1C2C5F9310A
 * @st_funcID		LCCM655R0.FILE.040.FUNC.004
 */
Luint32 u32FCU_LASERCONT_VELOC__Compute(Luint32 u32Distance, Luint64 u64TimeDelta)
{
	Luint64 u64Temp;
	Luint64 u64Temp2;
	//Velocity = Distance * time
	//Distance is in mm
	//Time is in 20ns increments

	u64Temp = (Luint64)u32Distance;
	//make very large so as the math and div works out nice.
	u64Temp *= 1000000000U;

	//compute the time
	u64Temp2 = u64TimeDelta;

	//safety
	#if C_LOCALDEF__LCCM124__RTI_CLK_FREQ != 50U
		#error
	#else
		//convert to ns
		//todo: we could technically shift to div by 2 here and reduce the size of the numerator
		u64Temp2 *= 20U;
	#endif

	//divide
	//math safety
	if (u64Temp2 == 0U)
	{
		u64Temp = 0U;
	}
	else
	{
		u64Temp /= u64Temp2;
	}

	return (Luint32)u64Temp;

}


#endif
#ifndef C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST
	#error
#endif
#endif //C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE


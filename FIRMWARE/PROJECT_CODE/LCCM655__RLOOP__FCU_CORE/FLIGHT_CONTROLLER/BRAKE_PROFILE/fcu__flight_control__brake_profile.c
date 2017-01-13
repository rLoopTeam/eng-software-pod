/**
 * @file		FCU__FLIGHT_CONTROL__BRAKE_PROFILE.C
 * @brief		Brake profile control
 * 				This is the top level point that we can control the brakes from.
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
 * @addtogroup FCU__FLIGHT_CTL__BRAKE_PROFILE
 * @ingroup FCU
 * @{ */

#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FCTL_BRAKE_CONTROL == 1U

//https://drive.google.com/open?id=0B6nyc_uvAyY0YTdyNmotZ2p6Nlk

#ifndef WIN32
extern const Lfloat32 f32A34_BrakeTable[];
#else
extern Lfloat32 f32A34_BrakeTable[];
#endif

//the structure
extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init the braking table
 * 
 * @st_funcMD5		2EC54F06C0A18BE0BED2CE59E992814A
 * @st_funcID		LCCM655R0.FILE.051.FUNC.001
 */
void vFCU_FLIGHTCTL_BRAKES__Init(void)
{


}


/***************************************************************************//**
 * @brief
 * Process any brake tasks
 * 
 * @st_funcMD5		2B9E44569F388001FE49ADD857317492
 * @st_funcID		LCCM655R0.FILE.051.FUNC.002
 */
void vFCU_FLIGHTCTL_BRAKES__Process(void)
{

}



/***************************************************************************//**
 * @brief
 * Peroform a brake lookup.
 * 
 * @param[out]		*pu32IBDistance_um			The computed i-beam dist
 * @param[in]		u32DragForce_n				Requested drag force in newtons
 * @param[in]		u32Veloc_mms				The current pod velocity in mm/sec
 * @st_funcMD5		3A46A8C5ACB8F1DEE6D0AF081D21F985
 * @st_funcID		LCCM655R0.FILE.051.FUNC.003
 */
Lint16 s16FCU_FLIGHTCTL_BRAKES__Brake_Lookup(Luint32 u32Veloc_mms, Luint32 u32DragForce_n, Luint32 *pu32IBDistance_um)
{

	Luint32 u32Veloc_ms;
	Lint16 s16Return;
	Luint32 u32LookupIndex;
	Lfloat32 f32DragPow3;
	Lfloat32 f32DragPow2;
	Lfloat32 f32Result;

	//firstly lets convert our mm/sec veloc into whole units of meters/second
	u32Veloc_ms = u32Veloc_mms;
	u32Veloc_ms /= 1000U;

	//do a range check on the data, we are hard limited to 160m/s
	//NOTE: AND CAUTION:
	//The brake table is only good for values over about 25m/s, below that the polyfitter is unable to produce a good
	//brake curve. The controller is designed to go into a "full on" brake mode below 30m/s so this should not be a problem.
	//Just remember this fact when you are trying to do unit testing below 30m/s
	if(u32Veloc_ms < 160U)
	{

		//the velocity is the index into our braking table
		//and there are 4 polynomials per entry so its easy and efficent to compute our lookup position
		u32LookupIndex = u32Veloc_ms;

		//mult by 4
		u32LookupIndex <<= 2U;

		//compute the drags's
		f32DragPow2 = (Lfloat32)u32DragForce_n;
		f32DragPow2 *= (Lfloat32)u32DragForce_n;
		f32DragPow3 = f32DragPow2 * (Lfloat32)u32DragForce_n;

		//do the poly calc
		f32Result = (f32A34_BrakeTable[u32LookupIndex] * f32DragPow3);
		f32Result += (f32A34_BrakeTable[u32LookupIndex + 1U] * f32DragPow2);
		f32Result += (f32A34_BrakeTable[u32LookupIndex + 2U] * (Lfloat32)u32DragForce_n);
		f32Result += f32A34_BrakeTable[u32LookupIndex + 3U];

		//convert to microns from meters
		f32Result *= 1000000U;

		//hard limiting issues here
		if(f32Result < 0)
		{
			*pu32IBDistance_um = 0U;
		}
		else
		{
			*pu32IBDistance_um = (Luint32)f32Result;
		}

		s16Return = 0;

	}
	else
	{
		//error input data out of range
		//max braking to be safe
		*pu32IBDistance_um = 0U;
		s16Return = -1;
	}


	return s16Return;
}


#endif //C_LOCALDEF__LCCM655__ENABLE_FCTL_BRAKE_CONTROL
#ifndef C_LOCALDEF__LCCM655__ENABLE_FCTL_BRAKE_CONTROL
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

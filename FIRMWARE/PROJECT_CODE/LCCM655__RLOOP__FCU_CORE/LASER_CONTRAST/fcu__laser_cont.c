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
#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST == 1U

extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init the contrast laser system
 * 
 * @st_funcMD5		17BB21481013532CE4A1C8E5152D1DB3
 * @st_funcID		LCCM655R0.FILE.034.FUNC.001
 */
void vFCU_LASERCONT__Init(void)
{
	Luint8 u8Counter;

	sFCU.sContrast.u32Guard1 = 0xAB12AB34U;
	sFCU.sContrast.u32Guard2 = 0x76540987U;
	sFCU.sContrast.u32Guard3 = 0x00112233U;
	sFCU.sContrast.u32Guard4 = 0x34343434U;


	//init the fault system for top level
	vSIL3_FAULTTREE__Init(&sFCU.sContrast.sFaultFlags);

	//init the sensor specifics
	for(u8Counter = 0U; u8Counter < LASER_CONT__MAX; u8Counter++)
	{

		vSIL3_FAULTTREE__Init(&sFCU.sContrast.sSensors[u8Counter].sFaultFlags);

		//Update the distance remaining in mm.
		//This could be set to the max track distance, or some other distance, but we really need
		//to use caution here has if distremain = 0 then maybe the brakes will be hard on.
		sFCU.sContrast.sSensors[u8Counter].u32DistElapsed_mm = 0U;
		sFCU.sContrast.sSensors[u8Counter].u32DistLastStripe_mm = 0U;
		sFCU.sContrast.sSensors[u8Counter].u32CurrentVeloc_mms = 0U;
		sFCU.sContrast.sSensors[u8Counter].u32PreviousVeloc_mms = 0U;
		sFCU.sContrast.sSensors[u8Counter].s32CurrentAccel_mmss = 0;

	}

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
 * @st_funcMD5		5243039BF23965BD12D80A2CE0C8D864
 * @st_funcID		LCCM655R0.FILE.034.FUNC.002
 */
void vFCU_LASERCONT__Process(void)
{
	Luint8 u8LaserCount;
	Luint8 u8Test;
	Luint64 u64Temp;
	Lint64 s64Temp;

	if(sFCU.sContrast.u32Guard1 != 0xAB12AB34U)
	{
		//error
	}
	if(sFCU.sContrast.u32Guard2 != 0x76540987U)
	{
		//error
	}
	if(sFCU.sContrast.u32Guard3 != 0x00112233U)
	{
		//error
	}
	if(sFCU.sContrast.u32Guard4 != 0x34343434U)
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

		//This is where the $1M problem exists.  In FPGA testing it was found that due to various system
		//delays we can actually cause this not to process the new rising edge avail, based on the 1ms gap at very high speed
		//Now this is not likely to happen in real life, but we need a better solution.


		//we have a count of rising edges detected, we should compare this with our current count
		//if the counts do not match, process it.
		if (sFCU.sContrast.sTimingList[u8LaserCount].u16RisingCount > sFCU.sContrast.sTimingList[u8LaserCount].u16PrevRisingCount)
		{

			//we know that we have received at least one new rising edge, but we could have 20 new edges
			//lets just process the most recent one

			//we know each stripe is 30.48 meters.
			sFCU.sContrast.sSensors[u8LaserCount].u32DistElapsed_mm += 30480U;

			//same with this, hard coded.
			sFCU.sContrast.sSensors[u8LaserCount].u32DistLastStripe_mm = 30480U;

			//we can also hit the first rising edge and call this 0, so just because we have one
			//edge does not mean we have actually travelled.

			//get the difference in time between pulses.
			u64Temp = u64FCU_LASERCONT_TL__Get_TimeDelta((E_FCU__LASER_CONT_INDEX_T)u8LaserCount, sFCU.sContrast.sTimingList[u8LaserCount].u16PrevRisingCount);

			//use the previous distance to compute our veloc.
			//Todo: hard coded 100ft mark
			sFCU.sContrast.sSensors[u8LaserCount].u32CurrentVeloc_mms = u32FCU_LASERCONT_VELOC__Compute(30480U, u64Temp);

			//compute accel from prev

			//safetys
			if(u64Temp == 0U)
			{
				//set accel to 0
				s64Temp = 0;
			}
			else
			{
				//a = (v1 - v0)/t
				s64Temp = (Lint64)sFCU.sContrast.sSensors[u8LaserCount].u32CurrentVeloc_mms;
				s64Temp -= (Lint64)sFCU.sContrast.sSensors[u8LaserCount].u32PreviousVeloc_mms;
				//make the delta nice and big so our math works out well.
				s64Temp *= 1000000000;
				//convert to nanoseconds.
				u64Temp *= 20U;
				s64Temp /= (Lint64)u64Temp;
			}

			//save
			sFCU.sContrast.sSensors[u8LaserCount].s32CurrentAccel_mmss = (Lint32)s64Temp;


			//update
			sFCU.sContrast.sSensors[u8LaserCount].u32PreviousVeloc_mms = sFCU.sContrast.sSensors[u8LaserCount].u32CurrentVeloc_mms;

			//do some DAQ
			#if C_FCU_DAQ_SET__ENABLE__DAQ_FOR_LASER_CONTRAST == 1U
			if(u8LaserCount == 0U)
			{
				vDAQ_APPEND__U16(C_FCU_DAQ_SET__DAQ_FOR_CONTRAST__L0_RISING_EDGE_COUNT_U16, sFCU.sContrast.sTimingList[u8LaserCount].u16RisingCount);
				vDAQ_APPEND__U32(C_FCU_DAQ_SET__DAQ_FOR_CONTRAST__L0_DISTANCE_ELAPSED_U32, sFCU.sContrast.sSensors[u8LaserCount].u32DistElapsed_mm);
				vDAQ_APPEND__U32(C_FCU_DAQ_SET__DAQ_FOR_CONTRAST__L0_CURRENT_VELOCITY_U32, sFCU.sContrast.sSensors[u8LaserCount].u32CurrentVeloc_mms);
				vSIL3_DAQ_APPEND__S32(C_FCU_DAQ_SET__DAQ_FOR_CONTRAST__L0_CURRENT_ACCEL_S32, sFCU.sContrast.sSensors[u8LaserCount].s32CurrentAccel_mmss);
			}
			else if(u8LaserCount == 1U)
			{

			}
			else
			{
				//not for this
			}
			#endif

			//update now
			sFCU.sContrast.sTimingList[u8LaserCount].u16PrevRisingCount += 1U;

		}
		else
		{
			//rising count has not changed yet
		}


//this code below did not work well with ultra high speed simulation
#if 0
		u8Test = u8FCU_LASERCONT_TL__Get_NewRisingAvail((E_FCU__LASER_CONT_INDEX_T)u8LaserCount);
		if(u8Test == 1U)
		{

			//tell the track database about our new edge
			vFCU_LASERCONT_TRKDB__Inc_Marker((E_FCU__LASER_CONT_INDEX_T)u8LaserCount);

			//recompute the last distance covered and dist remain
			vFCU_LASERCONT_TRKDB__Compute((E_FCU__LASER_CONT_INDEX_T)u8LaserCount);

			//update our internal structure of either the dist remain, or a fault
			sFCU.sContrast.sSensors[u8LaserCount].u32DistElapsed_mm = u32FCU_LASERCONT_TRKDB__Get_DistanceElapsed_mm((E_FCU__LASER_CONT_INDEX_T)u8LaserCount);

			//get the distance covered in the last stripe:
			//Note: This could be 0 when we are starting off before the first maker.
			sFCU.sContrast.sSensors[u8LaserCount].u32DistLastStripe_mm = u32FCU_LASERCONT_TRKDB__Get_DistancePrevSeg_mm((E_FCU__LASER_CONT_INDEX_T)u8LaserCount);

			//get the difference in time between pulses.
			u64Temp = u64FCU_LASERCONT_TL__Get_TimeDelta((E_FCU__LASER_CONT_INDEX_T)u8LaserCount, sFCU.sContrast.sTimingList[u8LaserCount].u16RisingCount);

			//the time delta is in 20ns increments (50MHz)

			//use the previous distance to compute our veloc.
			sFCU.sContrast.sSensors[u8LaserCount].u32CurrentVeloc_mms = u32FCU_LASERCONT_VELOC__Compute(sFCU.sContrast.sSensors[u8LaserCount].u32DistLastStripe_mm, u64Temp);

			//done with the flag, clear it.
			vFCU_LASERCONT_TL__Clear_NewRisingAvail((E_FCU__LASER_CONT_INDEX_T)u8LaserCount);


			//do some DAQ
			#if C_FCU_DAQ_SET__ENABLE__DAQ_FOR_LASER_CONTRAST == 1U
			if(u8LaserCount == 0U)
			{
				vDAQ_APPEND__U16(C_FCU_DAQ_SET__DAQ_FOR_CONTRAST__L0_RISING_EDGE_COUNT_U16, sFCU.sContrast.sTimingList[u8LaserCount].u16RisingCount);
				vDAQ_APPEND__U32(C_FCU_DAQ_SET__DAQ_FOR_CONTRAST__L0_DISTANCE_ELAPSED_U32, sFCU.sContrast.sSensors[u8LaserCount].u32DistElapsed_mm);
				vDAQ_APPEND__U32(C_FCU_DAQ_SET__DAQ_FOR_CONTRAST__L0_CURRENT_ACCEL_S32, sFCU.sContrast.sSensors[u8LaserCount].u32DistLastStripe_mm);
				vDAQ_APPEND__U32(C_FCU_DAQ_SET__DAQ_FOR_CONTRAST__L0_CURRENT_VELOCITY_U32, sFCU.sContrast.sSensors[u8LaserCount].u32CurrentVeloc_mms);
			}
			else if(u8LaserCount == 1U)
			{

			}
			else
			{
				//not for this
			}
			#endif
		}
		else
		{
			//laser edge not ready yet
			//todo: check for a timeout
		}
#endif //0

	}//for(u8LaserCount = 0U; u8LaserCount < (Luint8)LASER_CONT__MAX; u8LaserCount++)



}

/***************************************************************************//**
 * @brief
 * Reset the laser contrast system. This will need to be done by the flight controller
 * PRIOR to any run.
 * 
 * @param[in]		u32Key				0xABCDABCDU
 * @st_funcMD5		F6F060589AB5BB11032BD32EEAFCCEA0
 * @st_funcID		LCCM655R0.FILE.034.FUNC.004
 */
void vFCU_LASERCONT__Reset(Luint32 u32Key)
{

	if(u32Key == 0xABCDABCDU)
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

//safetys
#ifndef C_FCU_DAQ_SET__ENABLE__DAQ_FOR_LASER_CONTRAST
	#error
#endif

#endif
#ifndef C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST
	#error
#endif
#endif //C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE


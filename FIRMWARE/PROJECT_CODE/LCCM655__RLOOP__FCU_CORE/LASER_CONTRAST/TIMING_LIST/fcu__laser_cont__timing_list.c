/**
 * @file		FCU__LASER_CONT__TIMING_LIST.C
 * @brief		Management of a timing list based on edges.
 * 				Purpose of this module is to maintian a timing list of
 * 				rising and falling edges of a sensor
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
 * @addtogroup FCU__LASER_CONTRAST__TIMING_LIST
 * @ingroup FCU
 * @{ */


#include "../../fcu_core.h"
#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST == 1U

extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init the timing list
 * 
 * @st_funcMD5		9BA52F4C0FCD64FBCF621D2764E85A47
 * @st_funcID		LCCM655R0.FILE.042.FUNC.001
 */
void vFCU_LASERCONT_TL__Init(void)
{
	Luint8 u8LaserCount;
	Luint32 u32ListCount;

	//clear the lists
	for(u8LaserCount = 0U; u8LaserCount < (Luint8)LASER_CONT__MAX; u8LaserCount++)
	{
		//clear the stripe counters.
		for(u32ListCount = 0U; u32ListCount < C_FCU__LASER_CONTRAST__MAX_STRIPES; u32ListCount++)
		{
			sFCU.sContrast.sTimingList[u8LaserCount].u64RisingList[u32ListCount] = 0U;
			sFCU.sContrast.sTimingList[u8LaserCount].u64FallingList[u32ListCount] = 0U;
			sFCU.sContrast.sTimingList[u8LaserCount].u64ElapsedList_Rising[u32ListCount] = 0U;

		}

		//clear the counts
		sFCU.sContrast.sTimingList[u8LaserCount].u16RisingCount = 0U;
		sFCU.sContrast.sTimingList[u8LaserCount].u16PrevRisingCount = 0U;
		sFCU.sContrast.sTimingList[u8LaserCount].u16FallingCount = 0U;
		sFCU.sContrast.sTimingList[u8LaserCount].u8NewRisingAvail = 0U;

	}

}

/***************************************************************************//**
 * @brief
 * Process the laser contrast list system
 * 
 * @st_funcMD5		B49F777F22EE331A3A234297EEC04270
 * @st_funcID		LCCM655R0.FILE.042.FUNC.002
 */
void vFCU_LASERCONT_TL__Process(void)
{
	Luint32 u32ListCount;
	Luint8 u8LaserCount;
	Luint64 u64Temp;

	//We need to do a couple of tasks here

	//1.See if we got a new edge

	//2.Compute the time distance between the stripes
	//This could be run constantly so as we keep a consistent CPU load.
	//this will also prevent unexpected load if we hit the ripple strips and can't simulate it easy.
	for(u8LaserCount = 0U; u8LaserCount < (Luint8)LASER_CONT__MAX; u8LaserCount++)
	{
		//do only up to the last marker -1
		//because we are +1 internal to the for loop.
		for(u32ListCount = 0U; u32ListCount < (C_FCU__LASER_CONTRAST__MAX_STRIPES - 1); u32ListCount++)
		{
			//here we have to assume that *always* one is greater than the other
			//but this will chew computing time
			if(sFCU.sContrast.sTimingList[u8LaserCount].u64RisingList[u32ListCount] < sFCU.sContrast.sTimingList[u8LaserCount].u64RisingList[u32ListCount + 1])
			{

				//get the next entry
				u64Temp = sFCU.sContrast.sTimingList[u8LaserCount].u64RisingList[u32ListCount + 1];

				//subtract it from the current entry
				u64Temp -= sFCU.sContrast.sTimingList[u8LaserCount].u64RisingList[u32ListCount];

				//update the elapsed list.
				sFCU.sContrast.sTimingList[u8LaserCount].u64ElapsedList_Rising[u32ListCount] = u64Temp;

			}
			else
			{
				//big issue here, we are not able to subtract;
			}

		}//for(u32ListCount = 0U; u32ListCount < (C_FCU__LASER_CONTRAST__MAX_STRIPES - 1); u32ListCount++)

	}//for(u8LaserCount = 0U; u8LaserCount < (Luint8)LASER_CONT__MAX; u8LaserCount++)

	//3. Update a rolling database of markers passed

	//4. Handle any error rejection.
}

/***************************************************************************//**
 * @brief
 * Rising and falling edge Interrupts from the RM4 notification system
 *
 * @note
 * This is an interrupt task!. Take Care
 *
 * @param[in]		eLaser					The laser
 * @param[in]		u32Register				Snapshot of pin
 * @st_funcMD5		C9E0D08D7A05712DAD2D8ACF97A7DF77
 * @st_funcID		LCCM655R0.FILE.042.FUNC.003
 */
void vFCU_LASERCONT_TL__ISR(E_FCU__LASER_CONT_INDEX_T eLaser, Luint32 u32Register)
{
	Luint32 u32Mask;

	u32Mask = 0U;

	//determine our laser
	//6,7,13
	switch(eLaser)
	{
		case LASER_CONT__FWD:
			//generate the mask for this laser
			u32Mask = (1U << 6U);
			break;

		case LASER_CONT__MID:
			//generate the mask for this laser
			u32Mask = (1U << 7U);
			break;

		case LASER_CONT__AFT:
			//generate the mask for this laser
			u32Mask = (1U << 13U);
			break;

		default:
			//do nothing.
			break;

	}//switch(eLaser)

	if(eLaser < LASER_CONT__MAX)
	{
		//here all we can do is save off the next list item and then increment.
		//rising or falling
		if((u32Register & u32Mask) == 0U)
		{
			//falling
			//make sure we are safe
			if(sFCU.sContrast.sTimingList[(Luint8)eLaser].u16FallingCount < C_FCU__LASER_CONTRAST__MAX_STRIPES)
			{
				sFCU.sContrast.sTimingList[(Luint8)eLaser].u64FallingList[sFCU.sContrast.sTimingList[(Luint8)eLaser].u16FallingCount] = u64RM4_RTI__Get_Counter1();
				sFCU.sContrast.sTimingList[(Luint8)eLaser].u16FallingCount++;
			}
			else
			{
				//BIG ISSUE!
			}
		}
		else
		{
			//rising
			//make sure we are safe
			if(sFCU.sContrast.sTimingList[(Luint8)eLaser].u16RisingCount < C_FCU__LASER_CONTRAST__MAX_STRIPES)
			{
				sFCU.sContrast.sTimingList[(Luint8)eLaser].u64RisingList[sFCU.sContrast.sTimingList[(Luint8)eLaser].u16RisingCount] = u64RM4_RTI__Get_Counter1();
				sFCU.sContrast.sTimingList[(Luint8)eLaser].u16RisingCount++;

				//update the velocity system
				sFCU.sContrast.sTimingList[(Luint8)eLaser].u8NewRisingAvail = 1U;
			}
			else
			{
				//BIG ISSUE!
			}
		}
	}
	else
	{
		//big error
	}
}


/***************************************************************************//**
 * @brief
 * Gets the difference btween the current edge and previous edge.
 * can only use used if new rising edge avail = 1 and there is suitable rising data
 * 
 * @param[in]		eLaser				The laser index
 * @param[in]		u16CurrentIndex		The current index to compare against
 * @st_funcMD5		A7C670C712B3C8EA0B5451ECAABE9577
 * @st_funcID		LCCM655R0.FILE.042.FUNC.006
 */
Luint64 u64FCU_LASERCONT_TL__Get_TimeDelta(E_FCU__LASER_CONT_INDEX_T eLaser, Luint16 u16CurrentIndex)
{
	Luint64 u64Return;
	Luint16 u16Index0;
	Luint16 u16Index1;

	//can only do if we have AT LEAST one spot
	if(u16CurrentIndex >= 1U)
	{

		//compute the indexes
		u16Index0 = u16CurrentIndex;
		u16Index1 = u16CurrentIndex - 1U;

		u64Return = sFCU.sContrast.sTimingList[(Luint8)eLaser].u64RisingList[u16Index0];
		u64Return -= sFCU.sContrast.sTimingList[(Luint8)eLaser].u64RisingList[u16Index1];
	}
	else
	{
		u64Return = 0U;
	}
	
	return u64Return;
}

/***************************************************************************//**
 * @brief
 * Return if a new rising edge has been detected
 * 
 * @param[in]		eLaser					The laser index
 * @st_funcMD5		92F834345EEDB528E2092A78E1806443
 * @st_funcID		LCCM655R0.FILE.042.FUNC.004
 */
Luint8 u8FCU_LASERCONT_TL__Get_NewRisingAvail(E_FCU__LASER_CONT_INDEX_T eLaser)
{
	return sFCU.sContrast.sTimingList[(Luint8)eLaser].u8NewRisingAvail;
}

/***************************************************************************//**
 * @brief
 * Clear out the new rising edge flag once its been taken
 * 
 * @param[in]		eLaser					The laser index
 * @st_funcMD5		E776E69E5EDEE8E30C9B3BC6D316D0A2
 * @st_funcID		LCCM655R0.FILE.042.FUNC.005
 */
void vFCU_LASERCONT_TL__Clear_NewRisingAvail(E_FCU__LASER_CONT_INDEX_T eLaser)
{
	sFCU.sContrast.sTimingList[(Luint8)eLaser].u8NewRisingAvail = 0U;
}

#endif
#ifndef C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST
	#error
#endif
#endif //C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE

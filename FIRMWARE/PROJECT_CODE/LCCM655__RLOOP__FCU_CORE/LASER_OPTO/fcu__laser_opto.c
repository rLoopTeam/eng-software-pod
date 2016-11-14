/**
 * @file		FCU__LASER_OPTO.C
 * @brief		OptoNCDT laser interface for pitch and yaw
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
 * @addtogroup FCU__LASER_OPTO
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_LASER_OPTONCDT == 1U

//the structure
extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init any variables
 *
 */
void vFCU_LASEROPTO__Init(void)
{
	Luint8 u8Counter;

	sFCU.sLasers.eOptoNCDTState = OPTOLASER_STATE__RESET;

	//reset everything that is needed
	for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM655__NUM_LASER_OPTONCDT; u8Counter++)
	{
		sFCU.sOptoLaser[u8Counter].u8Dummy = 0U;
	}

}


/***************************************************************************//**
 * @brief
 * Process any laser opto tasks
 * 
 */
void vFCU_LASEROPTO__Process(void)
{
	Luint8 u8Counter;
	Luint8 u8Temp;

	//handle the optoNCDT laser state
	switch(sFCU.sLasers.eOptoNCDTState)
	{
		case OPTOLASER_STATE__RESET:
			//just fresh out of reset.
			break;

		case OPTOLASER_STATE__CHECK_NEW_DATA:
			//check if any new laser data is available on the bus.
			for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM655__NUM_LASER_OPTONCDT; u8Counter++)
			{
				//see if there is at least one byte of data avail in the FIFO's
				u8Temp = u8SC16_USER__Get_ByteAvail(u8Counter);
				if(u8Temp == 0U)
				{
					//no new data
				}
				else
				{
					//yep some new laser data avail, what to do with it?

					//get the byte and send it off for processing if we have enough data
					u8SC16_USER__Get_Byte

				}

			}
			break;


	}//switch(sFCU.sLasers.eOptoNCDTState)

}

//append a newly received byte of data onto the laser subsystem
void vFCU_LASEROPTO__Append_Byte(Luint8 u8LaserIndex, Luint8 u8Value)
{



	uint8_t c = laser->uart->read();
			if ((c & (1 << 7)) != 0) // higher bits, sent last
			{
				laser->buff[2] = c;
				optoncdt_processSample(laser);
			}
			else if ((c & 0xC0) != 0) // middle bits
			{
				laser->buff[1] = c;
			}
			else if ((c & 0xC0) == 0) // lower bits
			{
				laser->buff[0] = c;
			}
}


#endif //C_LOCALDEF__LCCM655__ENABLE_LASER_OPTONCDT

#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */


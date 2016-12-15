/**
 * @file		FCU__LASER_DISTANCE.C
 * @brief		Forward looking laser distance
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
 * @addtogroup FCU__LASER_DISTANCE
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"
#if C_LOCALDEF__LCCM655__ENABLE_LASER_DISTANCE == 1U

//the structure
extern struct _strFCU sFCU;

//locals
void vFCU_LASERDIST__Append_Byte(Luint8 u8Value);
void vFCU_LASERDIST__Process_Packet(void);


/***************************************************************************//**
 * @brief
 * Init any of the laser distance items
 * 
 * @st_funcMD5		5460A1E482BCAA1EB7422B7279A9EBB2
 * @st_funcID		LCCM655R0.FILE.033.FUNC.001
 */
void vFCU_LASERDIST__Init(void)
{

	sFCU.sLaserDist.eLaserState = LASERDIST_STATE__RESET;
	sFCU.sLaserDist.eRxState = LASERDIST_RX__BYTE_1;
	sFCU.sLaserDist.u8NewPacket = 0U;
	sFCU.sLaserDist.u8NewDistanceAvail = 0U;
	sFCU.sLaserDist.u32LaserPOR_Counter = 0U;
	//just set to some obscene distance
	sFCU.sLaserDist.f32Distance = 99999.9F;


}

/***************************************************************************//**
 * @brief
 * Process the laser distance system
 * 
 * @st_funcMD5		F25EE9036909B9D41BC3F505D556DAE8
 * @st_funcID		LCCM655R0.FILE.033.FUNC.002
 */
void vFCU_LASERDIST__Process(void)
{

	Luint8 u8Counter;
	Luint8 u8Temp;
	Luint8 u8BurstCount;

	//handle the LASERDIST laser state
	switch(sFCU.sLaserDist.eLaserState)
	{
		case LASERDIST_STATE__RESET:
			//just fresh out of reset.

			sFCU.sLaserDist.u32LaserPOR_Counter = 0U;

			//setup the lasers
			sFCU.sLaserDist.eLaserState = LASERDIST_STATE__WAIT_LASER_RESET;
			break;

		case LASERDIST_STATE__WAIT_LASER_RESET:

			//wait here until the lasers are out of rest.
			if(sFCU.sLaserDist.u32LaserPOR_Counter > 50U)
			{
				sFCU.sLaserDist.eLaserState = LASERDIST_STATE__INIT_LASER;
			}
			else
			{
				//stay in state
			}


			break;

		case LASERDIST_STATE__INIT_LASER:

			//just fall on here, the laser does not need any commands sent to it.

			sFCU.sLaserDist.eLaserState = LASERDIST_STATE__WAIT_INIT_DONE;
			break;

		case LASERDIST_STATE__WAIT_INIT_DONE:

			//wait until the laser is up
			//nothing to do here.

			//continue to check for new data.
			sFCU.sLaserDist.eLaserState = LASERDIST_STATE__CHECK_NEW_DATA;
			break;

		case LASERDIST_STATE__CHECK_NEW_DATA:

			//do a burst here
			for(u8BurstCount = 0U; u8BurstCount < 3U; u8BurstCount++)
			{

				//see if there is at least one byte of data avail in the FIFO's
				u8Temp = u8SC16_USER__Get_ByteAvail(9U);
				if(u8Temp == 0U)
				{
					//no new data
				}
				else
				{
					//yep some new laser data avail, what to do with it?

					//get the byte and send it off for processing if we have enough data
					u8Temp = u8SC16_USER__Get_Byte(9U);

					//process the byte.
					vFCU_LASERDIST__Append_Byte(u8Temp);
				}

			}


			sFCU.sLaserDist.eLaserState = LASERDIST_STATE__CHECK_NEW_PACKET;
			break;

		case LASERDIST_STATE__CHECK_NEW_PACKET:

			//check the packet state of each laser
			if(sFCU.sLaserDist.u8NewPacket == 1U)
			{
				//we have a new laser packet, process it for distance or error code.
				vFCU_LASERDIST__Process_Packet();

				//clear the flag
				sFCU.sLaserDist.u8NewPacket = 0U;

			}
			else
			{
				//no new packet has arrived, loop around
			}

			//back to check for more data
			sFCU.sLaserDist.eLaserState = LASERDIST_STATE__CHECK_NEW_DATA;
			break;

	}//switch(sFCU.sLasers.eLaserState)

}

/***************************************************************************//**
 * @brief
 * Return the current computed distance.
 * 
 * @st_funcMD5		CF507F43EE6F2A661AD1A8989A05000A
 * @st_funcID		LCCM655R0.FILE.033.FUNC.003
 */
Lfloat32 f32FCU_LASERDIST__Get_Distance(void)
{
	return sFCU.sLaserDist.f32Distance;
}

//
/***************************************************************************//**
 * @brief
 * Process the laser packet
 * Take the laser packet byte array that has been captured and process it into a length
 * including fault detection
 * 
 * @st_funcMD5		50D2F735AC8706F6B0746CCB9860BD5A
 * @st_funcID		LCCM655R0.FILE.033.FUNC.004
 */
void vFCU_LASERDIST__Process_Packet(void)
{

	//todo, process all the bytes

}


/***************************************************************************//**
 * @brief
 * Append a new byte from the UART into the internal array, handle any error checking
 * 
 * @param[in]		u8Value				The new byte
 * @st_funcMD5		4CFB149BFF4B44D13D8DC54626482976
 * @st_funcID		LCCM655R0.FILE.033.FUNC.005
 */
void vFCU_LASERDIST__Append_Byte(Luint8 u8Value)
{

	//TODO:
	//NEED TO UPDATE THIS RX STRUCTURE PER DETAILS ON:
	//https://github.com/rLoopTeam/eng-controls-acc-vs-lrf-test-rig/blob/master/LRF/LRF.ino
	//document in documents folder.


	//handle the laser distance rx states
	switch(sFCU.sLaserDist.eRxState)
	{
		case LASERDIST_RX__BYTE_1:

			//make sure the first two bits are valid
			//todo
			if(0U)
			{
				//the top two bits are zero, we are good to go
				//save the byte
				//todo
				sFCU.sLaserDist.u8NewByteArray[0] = u8Value;

				//wait for byte 2
				sFCU.sLaserDist.eRxState = LASERDIST_RX__BYTE_2;
			}
			else
			{
				//we are not at the right point for detection of the packet start, loop back

				//todo: check if we can see a laser error here
			}
			break;

		case LASERDIST_RX__BYTE_2:

			//check for byte 1
			if(0) //todo
			{
				//the top two bits are 1, we are good to go
				//save the byte
				//todo
				sFCU.sLaserDist.u8NewByteArray[1] = u8Value;

				//wait for byte 3
				sFCU.sLaserDist.eRxState = LASERDIST_RX__BYTE_3;
			}
			else
			{
				//go back to the start, becase we have lost our position
				//todo
				sFCU.sLaserDist.eRxState = LASERDIST_RX__BYTE_1;
			}
			break;

		case LASERDIST_RX__BYTE_3:

			//check for byte 3
			//todo
			if(0)
			{
				//the top two bits are valid, we are good to go
				//save the byte
				//todo
				sFCU.sLaserDist.u8NewByteArray[2] = u8Value & 0x0FU;

				//signal that a new packet is ready
				sFCU.sLaserDist.u8NewPacket = 1U;

				//go back and rx the next new packet
				sFCU.sLaserDist.eRxState = LASERDIST_RX__BYTE_1;
			}
			else
			{
				//go back to the start, becase we have lost our position
				sFCU.sLaserDist.eRxState = LASERDIST_RX__BYTE_1;
			}

			break;

		default:
			//todo, log the error
			break;

	}//switch
}


/***************************************************************************//**
 * @brief
 * 100ms Timer interrupt.
 * 
 * @st_funcMD5		D7AC2E42B341C67C3BC9659D2E8CEC02
 * @st_funcID		LCCM655R0.FILE.033.FUNC.006
 */
void vFCU_LASERDIST__100MS_ISR(void)
{

	sFCU.sLaserDist.u32LaserPOR_Counter++;
}


#endif
/** @} */
/** @} */
/** @} */


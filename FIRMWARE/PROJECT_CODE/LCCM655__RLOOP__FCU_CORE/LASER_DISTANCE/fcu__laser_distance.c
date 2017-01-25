/**
 * @file		FCU__LASER_DISTANCE.C
 * @brief		Forward looking laser distance
 *
 * @note
 * https://drive.google.com/drive/folders/0B-Gl6KhA0fayOENvbWQtOU0tNWc
 *
 * 2.2 Output at starting of the operation mode
 * Output of the Sensor after mode command (<esc>M<No.><cr>) are following:
 *
 * Mode <No.> 			Output
 * 0 					MOK, no effect
 *
 * 1 					MOK
 * 						Dxxxxx [aaaaa]
 * 						Dxxxxx [aaaaa] ....
 *
 * 2 					MOK
 * 						(Binary format distances)
 *
 * 3 					MOK
 * 						HW BINARY MODE
 * 						ESC to EXIT
 *
 * 4 					MOK
 * 						RS BINARY MODE
 * 						ESC to EXIT
 *
 * 5 (example) 			MOK
 * 						TRIGGER MODE
 * 						TRIG IN 500–550 cm
 * 						ESC to EXIT
 *
 * 6 (example) 			MOK
 * 						TWO DEVICE SPEED MODE
 * 						TRIG IN 500–550 cm
 * 						ESC to EXIT
 *
 * 7 (example) 			MOK
 * 						SINGLE DEVICE SPEED MODE
 * 						Approaching vehicles mode Speed window size : 100 cm
 * 						TRIG IN 2000–2500cm
 * 						ESC to EXIT
 *
 * 8 					MOK
 * 						ESC to EXIT
 * 						HW CAPTURE MODE (1000 SAMPLES)
 *
 * 9 					RS CAPTURE MODE (1000 SAMPLES)
 * 						ESC to EXIT
 *
 * 10 					CONTINUOUS SPEED MODE. ESC TO EXIT
 *
 * 11 (example) 		SINGLE DEVICE SIZE MODE
 * 						Departing vehicles mode
 * 						Speed window size : 300 cm
 * 						Vehicle classification activated.
 * 						TRIG IN 2460–2960 cm
 * 						ESC to EXIT
 *
 * 12 (example) 		MULTILANE SINGLE DEVICE SPEED MODE
 * 						Lane Configuration:
 * 						ESC to EXIT
 *
 * 13 (example) 		MOVEMENT TRIGGER MODE
 * 						Reference distance : 995 cm
 * 						TRIG IN 945- 1045 cm
 * 						ESC to EXIT
 *
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
 * @st_funcMD5		CB16DEE2A7F5C05AABD3BA9584754C90
 * @st_funcID		LCCM655R0.FILE.033.FUNC.001
 */
void vFCU_LASERDIST__Init(void)
{

	//setup eth systems if needed
	vFCU_LASERDIST_ETH__Init();


	sFCU.sLaserDist.eLaserState = LASERDIST_STATE__RESET;
	sFCU.sLaserDist.eRxState = LASERDIST_RX__BYTE_D;
	sFCU.sLaserDist.u8NewPacket = 0U;
	sFCU.sLaserDist.u8NewDistanceAvail = 0U;
	sFCU.sLaserDist.u32LaserPOR_Counter = 0U;
	//just set to some obscene distance
	sFCU.sLaserDist.s32Distance_mm = 0;
	sFCU.sLaserDist.s32PrevDistance_mm = 0;
	sFCU.sLaserDist.s32Velocity_mms = 0;
	sFCU.sLaserDist.s32PrevVelocity_mms = 0;

	//setup the filtering
	vFCU_LASERDIST_FILT__Init();

}

/***************************************************************************//**
 * @brief
 * Process the laser distance system
 * 
 * @st_funcMD5		36297D2EDE06DBA5285970E47A1EC16B
 * @st_funcID		LCCM655R0.FILE.033.FUNC.002
 */
void vFCU_LASERDIST__Process(void)
{

	Luint8 u8Counter;
	Luint8 u8Temp;
	Luint8 u8BurstCount;
	Luint8 u8Array[4];




	//check for emulation
	if(sFCU.sLaserDist.sEmu.u8EmulationEnabled == 1U)
	{
		if(sFCU.sLaserDist.sEmu.u32EmuKey == 0x98984343U)
		{
			//assign
			sFCU.sLaserDist.s32Distance_mm = sFCU.sLaserDist.sEmu.s32Distance;
		}
		else
		{
			//fall on
		}
	}
	else
	{
		//fall on
	}


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
				sFCU.sLaserDist.eLaserState = LASERDIST_STATE__INIT_LASER_TURNON;
			}
			else
			{
				//stay in state
			}
			break;

		case LASERDIST_STATE__INIT_LASER_TURNON:

			//tell the laser to turn on
			//<ESC>, O, 1, <CR>
			u8Array[0] = 0x1BU;
			u8Array[1] = 0x4FU;
			u8Array[2] = 0x31U;
			u8Array[3] = 0x0DU;

			//send it.
			vSC16__Tx_ByteArray(C_FCU__SC16_FWD_LASER_INDEX, (Luint8*)&u8Array[0], 4U);

#ifndef WIN32
			vRM4_DELAYS__Delay_mS(50);
#endif

			//<ESC>, M, 1, <CR>
			u8Array[0] = 0x1BU;
			u8Array[1] = 0x4DU;
			u8Array[2] = 0x31U;
			u8Array[3] = 0x0DU;

			//send it.
			vSC16__Tx_ByteArray(C_FCU__SC16_FWD_LASER_INDEX, (Luint8*)&u8Array[0], 4U);

#ifndef WIN32
			vRM4_DELAYS__Delay_mS(50);
#endif

			//C
			u8Array[0] = 0x1BU;
			u8Array[1] = 0x63U;
			u8Array[2] = 0x0DU;

			//send it.
			vSC16__Tx_ByteArray(C_FCU__SC16_FWD_LASER_INDEX, (Luint8*)&u8Array[0], 3U);

			sFCU.sLaserDist.eLaserState = LASERDIST_STATE__WAIT_INIT_DONE;
			break;

		case LASERDIST_STATE__WAIT_INIT_DONE:

			//wait until the laser is up
			//nothing to do here.
#ifndef WIN32
			vRM4_DELAYS__Delay_mS(50);
#endif

			//continue to check for new data.
			sFCU.sLaserDist.eLaserState = LASERDIST_STATE__CHECK_NEW_DATA;
			break;

		case LASERDIST_STATE__CHECK_NEW_DATA:

			//do a burst here
			for(u8BurstCount = 0U; u8BurstCount < 3U; u8BurstCount++)
			{

				//see if there is at least one byte of data avail in the FIFO's
				u8Temp = u8SC16_USER__Get_ByteAvail(C_FCU__SC16_FWD_LASER_INDEX);
				if(u8Temp == 0U)
				{
					//no new data
				}
				else
				{
					//yep some new laser data avail, what to do with it?

					//get the byte and send it off for processing if we have enough data
					u8Temp = u8SC16_USER__Get_Byte(C_FCU__SC16_FWD_LASER_INDEX);

					//process the byte.
					vFCU_LASERDIST__Append_Byte(u8Temp);
				}

			}//for(u8BurstCount = 0U; u8BurstCount < 3U; u8BurstCount++)


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

		default:
			//fall on
			break;

	}//switch(sFCU.sLasers.eLaserState)

	//process the laser distance filtering.
	vFCU_LASERDIST_FILT__Process();

}

/***************************************************************************//**
 * @brief
 * Return the current computed distance.
 * 
 * @st_funcMD5		130FEC5285C1E938EA3350D14F3B468C
 * @st_funcID		LCCM655R0.FILE.033.FUNC.003
 */
Lint32 s32FCU_LASERDIST__Get_Distance_mm(void)
{
	return sFCU.sLaserDist.s32Distance_mm;
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
	Lfloat32 f32Delta;
	Luint32 u32Distance;
	Luint32 u32Temp;
	Luint8 u8Temp;

	//compute the distance
	//1s
	u8Temp = sFCU.sLaserDist.u8NewByteArray[4];
	u8Temp -= 0x30U;
	u32Distance = (Luint32)u8Temp;

	//10s
	u8Temp = sFCU.sLaserDist.u8NewByteArray[3];
	u8Temp -= 0x30U;
	u32Temp = (Luint32)u8Temp;
	u32Temp *= 10U;
	u32Distance += u32Temp;

	//100s
	u8Temp = sFCU.sLaserDist.u8NewByteArray[2];
	u8Temp -= 0x30U;
	u32Temp = (Luint32)u8Temp;
	u32Temp *= 100U;
	u32Distance += u32Temp;

	//1000s
	u8Temp = sFCU.sLaserDist.u8NewByteArray[1];
	u8Temp -= 0x30U;
	u32Temp = (Luint32)u8Temp;
	u32Temp *= 1000U;
	u32Distance += u32Temp;

	//10000s
	u8Temp = sFCU.sLaserDist.u8NewByteArray[0];
	u8Temp -= 0x30U;
	u32Temp = (Luint32)u8Temp;
	u32Temp *= 10000U;
	u32Distance += u32Temp;

	//update
	sFCU.sLaserDist.s32Distance_mm = (Lint32)u32Distance;

	//compute veloc
	f32Delta = (Lfloat32)sFCU.sLaserDist.s32PrevDistance_mm;
	f32Delta -= sFCU.sLaserDist.s32Distance_mm;

	//50hz
	f32Delta *= 0.05;

	//do it.
	sFCU.sLaserDist.s32Velocity_mms = (Lint32)f32Delta;

	//save prev
	sFCU.sLaserDist.s32PrevDistance_mm = sFCU.sLaserDist.s32Distance_mm;


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
		case LASERDIST_RX__BYTE_D:

			//make sure the first two bits are valid
			//todo
			if(u8Value == 'D')
			{
				//wait for byte 2
				sFCU.sLaserDist.eRxState = LASERDIST_RX__BYTE_1;
			}
			else
			{
				//we are not at the right point for detection of the packet start, loop back

				//todo: check if we can see a laser error here
			}
			break;

		case LASERDIST_RX__BYTE_0:

			sFCU.sLaserDist.u8NewByteArray[0] = u8Value;
			sFCU.sLaserDist.eRxState = LASERDIST_RX__BYTE_1;
			break;

		case LASERDIST_RX__BYTE_1:

			sFCU.sLaserDist.u8NewByteArray[1] = u8Value;
			sFCU.sLaserDist.eRxState = LASERDIST_RX__BYTE_2;
			break;

		case LASERDIST_RX__BYTE_2:

			sFCU.sLaserDist.u8NewByteArray[2] = u8Value;
			sFCU.sLaserDist.eRxState = LASERDIST_RX__BYTE_3;
			break;

		case LASERDIST_RX__BYTE_3:

			sFCU.sLaserDist.u8NewByteArray[3] = u8Value;
			sFCU.sLaserDist.eRxState = LASERDIST_RX__BYTE_4;
			break;

		case LASERDIST_RX__BYTE_4:

			sFCU.sLaserDist.u8NewByteArray[4] = u8Value;

			//signal that a new packet is ready
			sFCU.sLaserDist.u8NewPacket = 1U;

			//go back and rx the next new packet
			sFCU.sLaserDist.eRxState = LASERDIST_RX__BYTE_D;
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


#ifdef WIN32
/***************************************************************************//**
 * @brief
 * On win32, set the raw value only
 * 
 * @param[in]		f32Value				Raw value in laser units
 * @st_funcMD5		7AFFF2A59E13949E9BFCA62BCED1FAA4
 * @st_funcID		LCCM655R0.FILE.033.FUNC.007
 */
void vFCU_LASERDIST_WIN32__Set_DistanceRaw(Lint32 s32Value)
{
	sFCU.sLaserDist.s32Distance_mm = s32Value;
}

#endif


#endif
/** @} */
/** @} */
/** @} */


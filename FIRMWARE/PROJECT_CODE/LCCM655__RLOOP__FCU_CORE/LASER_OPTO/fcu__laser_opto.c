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

// Note:
	// ../LASER_ORIENTATION/fcu__laser_orientation.c relies on index reqs:
 		// 0-4: Ground facing lasers
 		// 5-6: I-beam facing lasers

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_LASER_OPTONCDT == 1U

/** OptoNCDT's error value (out of range) */
#define C_LASEROPTO__ERROR_CODE_VALUE					(65467U)

//the structure
extern struct _strFCU sFCU;

//locals
static void vFCU_LASEROPTO__Process_Packet(E_FCU__LASER_OPTO__INDEX_T eLaser);
static void vFCU_LASEROPTO__Append_Byte(E_FCU__LASER_OPTO__INDEX_T eLaser, Luint8 u8Value);

/***************************************************************************//**
 * @brief
 * Init any variables
 * 
 * @st_funcMD5		275DF44B14084F7D934217BB273DC9F5
 * @st_funcID		LCCM655R0.FILE.021.FUNC.001
 */
void vFCU_LASEROPTO__Init(void)
{
	Luint8 u8Counter;
	Luint8 u8Test;

	sFCU.sLaserOpto.eOptoNCDTState = OPTOLASER_STATE__RESET;
	vFAULTTREE__Init(&sFCU.sLaserOpto.sFaultFlags);

	//reset everything that is needed
	for(u8Counter = 0U; u8Counter < C_FCU__NUM_LASERS_OPTONCDT; u8Counter++)
	{
		sFCU.sLaserOpto.sOptoLaser[u8Counter].eRxState = OPTONCDT_RX__BYTE_1;
		sFCU.sLaserOpto.sOptoLaser[u8Counter].u8NewPacket = 0U;
		sFCU.sLaserOpto.sOptoLaser[u8Counter].u8ReadyForFiltering = 0U;
		sFCU.sLaserOpto.sOptoLaser[u8Counter].u8NewDistanceAvail = 0U;
		//just set to some obscene distance
		sFCU.sLaserOpto.sOptoLaser[u8Counter].f32DistanceRAW = 99999.9F;
		sFCU.sLaserOpto.sOptoLaser[u8Counter].sFiltered.f32FilteredValue = 0.0F;
		sFCU.sLaserOpto.sOptoLaser[u8Counter].sFiltered.f32PreviousValue = 0.0F;
		sFCU.sLaserOpto.sOptoLaser[u8Counter].u8Error = 0U;

		sFCU.sLaserOpto.sOptoLaser[u8Counter].sCounters.u32ErrorCode = 0U;
		sFCU.sLaserOpto.sOptoLaser[u8Counter].sCounters.u32Byte1Wrong = 0U;

		sFCU.sLaserOpto.sCalibration[u8Counter].f32Offset = 0.0F;

		vFAULTTREE__Init(&sFCU.sLaserOpto.sOptoLaser[u8Counter].sFaultFlags);


	}//for(u8Counter = 0U; u8Counter < C_FCU__NUM_LASERS_OPTONCDT; u8Counter++)

	//check the CRC
	u8Test = u8EEPARAM_CRC__Is_CRC_OK(	C_LOCALDEF__LCCM655__FCTL_OPTONCDT___FL_ZERO,
										C_LOCALDEF__LCCM655__FCTL_OPTONCDT___RR_ZERO,
										C_LOCALDEF__LCCM655__FCTL_OPTONCDT___CRC);

	if(u8Test == 1U)
	{
		//valid
		sFCU.sLaserOpto.sCalibration[C_FCU__SC16_OPTO_FL_INDEX].f32Offset = f32EEPARAM__Read(C_LOCALDEF__LCCM655__FCTL_OPTONCDT___FL_ZERO);
		sFCU.sLaserOpto.sCalibration[C_FCU__SC16_OPTO_FR_INDEX].f32Offset = f32EEPARAM__Read(C_LOCALDEF__LCCM655__FCTL_OPTONCDT___FR_ZERO);
		sFCU.sLaserOpto.sCalibration[C_FCU__SC16_OPTO_RL_INDEX].f32Offset = f32EEPARAM__Read(C_LOCALDEF__LCCM655__FCTL_OPTONCDT___RL_ZERO);
		sFCU.sLaserOpto.sCalibration[C_FCU__SC16_OPTO_RR_INDEX].f32Offset = f32EEPARAM__Read(C_LOCALDEF__LCCM655__FCTL_OPTONCDT___RR_ZERO);

	}//if(u8Test == 1U)
	else
	{
		//CRC is invalid
		//rewrite.

		sFCU.sLaserOpto.sCalibration[C_FCU__SC16_OPTO_FL_INDEX].f32Offset = 0.0F;
		sFCU.sLaserOpto.sCalibration[C_FCU__SC16_OPTO_FR_INDEX].f32Offset = 0.0F;
		sFCU.sLaserOpto.sCalibration[C_FCU__SC16_OPTO_RL_INDEX].f32Offset = 0.0F;
		sFCU.sLaserOpto.sCalibration[C_FCU__SC16_OPTO_RR_INDEX].f32Offset =	0.0F;

		//do the eeprom
		vEEPARAM__WriteF32(C_LOCALDEF__LCCM655__FCTL_OPTONCDT___FL_ZERO, sFCU.sLaserOpto.sCalibration[C_FCU__SC16_OPTO_FL_INDEX].f32Offset, DELAY_T__DELAYED_WRITE);
		vEEPARAM__WriteF32(C_LOCALDEF__LCCM655__FCTL_OPTONCDT___FR_ZERO, sFCU.sLaserOpto.sCalibration[C_FCU__SC16_OPTO_FR_INDEX].f32Offset, DELAY_T__DELAYED_WRITE);
		vEEPARAM__WriteF32(C_LOCALDEF__LCCM655__FCTL_OPTONCDT___RL_ZERO, sFCU.sLaserOpto.sCalibration[C_FCU__SC16_OPTO_RL_INDEX].f32Offset, DELAY_T__DELAYED_WRITE);
		vEEPARAM__WriteF32(C_LOCALDEF__LCCM655__FCTL_OPTONCDT___RR_ZERO, sFCU.sLaserOpto.sCalibration[C_FCU__SC16_OPTO_RR_INDEX].f32Offset, DELAY_T__IMMEDIATE_WRITE);

		//redo the CRC;
		vEEPARAM_CRC__Calculate_And_Store_CRC(	C_LOCALDEF__LCCM655__FCTL_OPTONCDT___FL_ZERO,
											C_LOCALDEF__LCCM655__FCTL_OPTONCDT___RR_ZERO,
											C_LOCALDEF__LCCM655__FCTL_OPTONCDT___CRC);

		//set the flags for a general fault and cal data reload fault.
		vFAULTTREE__Set_Flag(&sFCU.sLaserOpto.sFaultFlags, 0);
		vFAULTTREE__Set_Flag(&sFCU.sLaserOpto.sFaultFlags, 1);

	}//else if(u8Test == 1U)


}		

//Do the calibration
void vFCU_LASEROPTO__Set_CalValue(Luint32 u32Key, Lfloat32 f32Offset)
{
	Lfloat32 f32Temp;

	if(u32Key == 0x11221122U)
	{

		//take the current val and subtract to = the offset
		f32Temp = f32Offset;
		f32Temp -= sFCU.sLaserOpto.sOptoLaser[C_FCU__SC16_OPTO_FL_INDEX].f32DistanceRAW;
		sFCU.sLaserOpto.sCalibration[C_FCU__SC16_OPTO_FL_INDEX].f32Offset = f32Temp;

		f32Temp = f32Offset;
		f32Temp -= sFCU.sLaserOpto.sOptoLaser[C_FCU__SC16_OPTO_FR_INDEX].f32DistanceRAW;
		sFCU.sLaserOpto.sCalibration[C_FCU__SC16_OPTO_FR_INDEX].f32Offset = f32Temp;

		f32Temp = f32Offset;
		f32Temp -= sFCU.sLaserOpto.sOptoLaser[C_FCU__SC16_OPTO_RL_INDEX].f32DistanceRAW;
		sFCU.sLaserOpto.sCalibration[C_FCU__SC16_OPTO_RL_INDEX].f32Offset = f32Temp;

		f32Temp = f32Offset;
		f32Temp -= sFCU.sLaserOpto.sOptoLaser[C_FCU__SC16_OPTO_RR_INDEX].f32DistanceRAW;
		sFCU.sLaserOpto.sCalibration[C_FCU__SC16_OPTO_RR_INDEX].f32Offset = f32Temp;

		//do the eeprom
		vEEPARAM__WriteF32(C_LOCALDEF__LCCM655__FCTL_OPTONCDT___FL_ZERO, sFCU.sLaserOpto.sCalibration[C_FCU__SC16_OPTO_FL_INDEX].f32Offset, DELAY_T__DELAYED_WRITE);
		vEEPARAM__WriteF32(C_LOCALDEF__LCCM655__FCTL_OPTONCDT___FR_ZERO, sFCU.sLaserOpto.sCalibration[C_FCU__SC16_OPTO_FR_INDEX].f32Offset, DELAY_T__DELAYED_WRITE);
		vEEPARAM__WriteF32(C_LOCALDEF__LCCM655__FCTL_OPTONCDT___RL_ZERO, sFCU.sLaserOpto.sCalibration[C_FCU__SC16_OPTO_RL_INDEX].f32Offset, DELAY_T__DELAYED_WRITE);
		vEEPARAM__WriteF32(C_LOCALDEF__LCCM655__FCTL_OPTONCDT___RR_ZERO, sFCU.sLaserOpto.sCalibration[C_FCU__SC16_OPTO_RR_INDEX].f32Offset, DELAY_T__IMMEDIATE_WRITE);

		//redo the CRC;
		vEEPARAM_CRC__Calculate_And_Store_CRC(	C_LOCALDEF__LCCM655__FCTL_OPTONCDT___FL_ZERO,
											C_LOCALDEF__LCCM655__FCTL_OPTONCDT___RR_ZERO,
											C_LOCALDEF__LCCM655__FCTL_OPTONCDT___CRC);

	}
	else
	{
		//error
	}
}

/***************************************************************************//**
 * @brief
 * Process any laser opto tasks
 * 
 * @st_funcMD5		64CE185AAAF228A5697E5F6E4B2D0629
 * @st_funcID		LCCM655R0.FILE.021.FUNC.002
 */
void vFCU_LASEROPTO__Process(void)
{
	Luint8 u8Counter;
	Luint8 u8Temp;
	Luint8 u8BurstCount;

	//handle the optoNCDT laser state
	switch(sFCU.sLaserOpto.eOptoNCDTState)
	{
		case OPTOLASER_STATE__RESET:
			//just fresh out of reset.

			sFCU.sLaserOpto.u32LaserPOR_Counter = 0U;

			//setup the lasers
			sFCU.sLaserOpto.eOptoNCDTState = OPTOLASER_STATE__WAIT_LASER_RESET;
			break;

		case OPTOLASER_STATE__WAIT_LASER_RESET:

			//wait here until the lasers are out of rest.
			if(sFCU.sLaserOpto.u32LaserPOR_Counter > 50U)
			{
				sFCU.sLaserOpto.eOptoNCDTState = OPTOLASER_STATE__INIT_LASER;
			}
			else
			{
				//stay in state
			}


			break;

		case OPTOLASER_STATE__INIT_LASER:

			//sucks but we have had to set the profile called rLoop into each sensor
			//put the lasers into RS422 mode.
			for(u8Counter = C_FCU__SC16_OPTO_FL_INDEX; u8Counter <= C_FCU__SC16_OPTO_YAWR_INDEX; u8Counter++)
			{
				//send the command
				vSC16__Tx_ByteArray(u8Counter, (Luint8*)"\r\nOUTPUT RS422\r\n", 16U);
			}
			//todo:
			//Check that the laser is in the mode.
			sFCU.sLaserOpto.eOptoNCDTState = OPTOLASER_STATE__WAIT_INIT_DONE;
			break;

		case OPTOLASER_STATE__WAIT_INIT_DONE:
			//wait until the laser is up


			//continue to check for new data.
			sFCU.sLaserOpto.eOptoNCDTState = OPTOLASER_STATE__CHECK_NEW_DATA;
			break;

		case OPTOLASER_STATE__CHECK_NEW_DATA:

			//do a sneeky burst here
			for(u8BurstCount = 0U; u8BurstCount < 3U; u8BurstCount++)
			{

				//check if any new laser data is available on the bus.
				for(u8Counter = C_FCU__SC16_OPTO_FL_INDEX; u8Counter <= C_FCU__SC16_OPTO_YAWR_INDEX; u8Counter++)
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
						u8Temp = u8SC16_USER__Get_Byte(u8Counter);

						//process the byte.
						vFCU_LASEROPTO__Append_Byte((E_FCU__LASER_OPTO__INDEX_T)u8Counter, u8Temp);
					}

				}//for(u8Counter = 0U; u8Counter < C_FCU__NUM_LASERS_OPTONCDT; u8Counter++)

			}//for(u8BurstCount = 0U; u8BurstCount < 3U; u8BurstCount++)

			sFCU.sLaserOpto.eOptoNCDTState = OPTOLASER_STATE__CHECK_NEW_PACKET;
			break;

		case OPTOLASER_STATE__CHECK_NEW_PACKET:

			//check the packet state of each laser
			for(u8Counter = C_FCU__SC16_OPTO_FL_INDEX; u8Counter <= C_FCU__SC16_OPTO_YAWR_INDEX; u8Counter++)
			{
				if(sFCU.sLaserOpto.sOptoLaser[u8Counter].u8NewPacket == 1U)
				{
					//we have a new laser packet, process it for distance or error code.
					vFCU_LASEROPTO__Process_Packet((E_FCU__LASER_OPTO__INDEX_T)u8Counter);

					//good for packet filtering.
					sFCU.sLaserOpto.sOptoLaser[u8Counter].u8ReadyForFiltering = 1U;

					//clear the flag
					sFCU.sLaserOpto.sOptoLaser[u8Counter].u8NewPacket = 0U;
				}
				else
				{
					//no new packet has arrived, loop around
				}

			}//or(u8Counter = 0U; u8Counter < C_FCU__NUM_LASERS_OPTONCDT; u8Counter++)

			//now filter it
			sFCU.sLaserOpto.eOptoNCDTState = OPTOLASER_STATE__FILTER_PACKET;
			break;

		case OPTOLASER_STATE__FILTER_PACKET:

			//check the packet state of each laser
			for(u8Counter = C_FCU__SC16_OPTO_FL_INDEX; u8Counter <= C_FCU__SC16_OPTO_YAWR_INDEX; u8Counter++)
			{
				if(sFCU.sLaserOpto.sOptoLaser[u8Counter].u8ReadyForFiltering == 1U)
				{
					//filter the data
					vFCU_LASEROPTO_FILT__FilterPacket((E_FCU__LASER_OPTO__INDEX_T)u8Counter);

					//clear the flag
					sFCU.sLaserOpto.sOptoLaser[u8Counter].u8ReadyForFiltering = 0U;

					//set a flag allowing the upper layer or the DAQ to read us.

				}
				else
				{
					//no filtering needed on this packet.
				}

			}//or(u8Counter = 0U; u8Counter < C_FCU__NUM_LASERS_OPTONCDT; u8Counter++)

			//back to check for more data
			sFCU.sLaserOpto.eOptoNCDTState = OPTOLASER_STATE__CHECK_NEW_DATA;
			break;


		default:
			//log;
			break;
	}//switch(sFCU.sLaserOpto.eOptoNCDTState)

}

/***************************************************************************//**
 * @brief
 * Get a lasers distance (The filtered value)
 * 
 * @param[in]		u8LaserIndex			The laser index
 * @st_funcMD5		730AD78103D781F1DA11563860869910
 * @st_funcID		LCCM655R0.FILE.021.FUNC.003
 */
Lfloat32 f32FCU_LASEROPTO__Get_Distance(E_FCU__LASER_OPTO__INDEX_T eLaser)
{
	return sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].sFiltered.f32FilteredValue;
}


/***************************************************************************//**
 * @brief
 * Get laser error state
 * 
 * @param[in]		u8LaserIndex			The laser index
 * @st_funcMD5		826C100C0C830F2FFD57066B7877AF99
 * @st_funcID		LCCM655R0.FILE.021.FUNC.007
 */
Luint8 u8FCU_LASEROPTO__Get_Error(E_FCU__LASER_OPTO__INDEX_T eLaser)
{
	return sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].u8Error;
}

/***************************************************************************//**
 * @brief
 * Process the laser packet
 * 
 * @param[in]		u8LaserIndex		The laser index
 * @st_funcMD5		A3236EC91277B738FFEC7B324049DFD7
 * @st_funcID		LCCM655R0.FILE.021.FUNC.004
 */
void vFCU_LASEROPTO__Process_Packet(E_FCU__LASER_OPTO__INDEX_T eLaser)
{
	Lfloat32 f32Temp;
	Luint32 u32ValA;
	Luint32 u32ValB;
	Luint32 u32ValC;

	//protect the laser index
	if((Luint8)eLaser < C_FCU__NUM_LASERS_OPTONCDT)
	{

		//assemble
		u32ValA = sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].u8NewByteArray[0];
		u32ValB = sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].u8NewByteArray[1];
		u32ValC = sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].u8NewByteArray[2];

		//format
		u32ValA += u32ValB << 6U;
		u32ValA += u32ValC << 12U;

		//check for error value
		//todo: 0U is a stand-in, shouldnt cause any trouble unless we end up mastering 
		//	the lasers; insert real error value(s); Appx 3.7, man pg99	
		if(u32ValA == C_LASEROPTO__ERROR_CODE_VALUE) 
		{
			//Laser returned the error value
			sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].u8Error = 1U;

			//Increment the count of error code values from the laser
			sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].sCounters.u32ErrorCode++;
		}
		else
		{
			//convert
			f32Temp = (Lfloat32)u32ValA;
			f32Temp *= 102.0F;
			f32Temp /= 65520.0F;
			f32Temp -= 1.0F;
			f32Temp *= 50.0F;
			f32Temp /= 100.0F;

			//save off the distance.
			sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].f32DistanceRAW = f32Temp;

			//save off.
			sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].u8NewDistanceAvail = 1U; //todo: currently never cleared

			// Value is not the error value, clear error flag
			sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].u8Error = 0U;
		}
	}
	else
	{
		//laser addressing error
	}


}

/***************************************************************************//**
 * @brief
 * Append a newly received byte of data onto the laser subsystem
 *
 * @note
 * 8.2 Measurement Data Format
 * 18 bits are transmitted per output value, see Chap. 7.5.2. An output value is divided into three bytes
 * that differ in the two most significant bits. The transmission of additional output values is optional.
 * Output value 1 / additional:
 *
 * L-Byte 	0 	0 	D5 	D4 	D3 	D2 	D1 	D0
 * M-Byte 	0 	1 	D11 D10 D9 	D8 	D7 	D6
 * H-Byte 	1 	0(2)0(3) 0(3) D15 D14 D13 D12
 * Output sequence: L-Byte, M-Byte, H-Byte.
 * 1, 3) Error values are coded with 18 Bit.
 * 2) To decide between the 1st output value and additional output values, bit 7 in the H-Byte is set to 1. Bit 7 in
 * the H-Byte is set to 0 for the 1st output value. This simultaneously represents the identifier of a new block. De-
 * pending on the measuring rate, baud rate and output data rate output all data can be output in one block. If
 * data output is not possible, a run-time error will be output. Use the command GETOUTINFO_RS422 to query
 * for data selection and output sequence.
 * 
 * @param[in]		u8Value					New byte value
 * @param[in]		u8LaserIndex			The laser index.
 * @st_funcMD5		DA0F12390988943896FBFA359E063324
 * @st_funcID		LCCM655R0.FILE.021.FUNC.005
 */
void vFCU_LASEROPTO__Append_Byte(E_FCU__LASER_OPTO__INDEX_T eLaser, Luint8 u8Value)
{
	//protect the laser structures from accidential addressing.
	if((Luint8)eLaser < C_FCU__NUM_LASERS_OPTONCDT)
	{
		switch(sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].eRxState)
		{
			case OPTONCDT_RX__BYTE_1:

				//make sure the first two bits are valid
				if((u8Value & 0xC0U) == 0U)
				{
					//the top two bits are zero, we are good to go
					//save the byte
					sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].u8NewByteArray[0] = u8Value & 0x3FU;

					//wait for byte 2
					sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].eRxState = OPTONCDT_RX__BYTE_2;
				}
				else
				{
					//we are not at the right point for detection of the packet start, loop back

					//todo: check if we can see a laser error here

					//inc the counter
					sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].sCounters.u32Byte1Wrong++;
				}

				break;
			case OPTONCDT_RX__BYTE_2:

				//check for byte 1
				if((u8Value & 0xC0U) == 0x40U)
				{
					//the top two bits are 1, we are good to go
					//save the byte
					sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].u8NewByteArray[1] = u8Value & 0x3FU;

					//wait for byte 3
					sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].eRxState = OPTONCDT_RX__BYTE_3;
				}
				else
				{
					//go back to the start, becase we have lost our position
					sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].eRxState = OPTONCDT_RX__BYTE_1;
				}
				break;

			case OPTONCDT_RX__BYTE_3:

				//check for byte 1
				if((u8Value & 0xC0U) == 0x80U)
				{
					//the top two bits are valid, we are good to go
					//save the byte
					sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].u8NewByteArray[2] = u8Value & 0x0FU;

					//signal that a new packet is ready
					sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].u8NewPacket = 1U;

					//go back and rx the next new packet
					sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].eRxState = OPTONCDT_RX__BYTE_1;
				}
				else
				{
					//go back to the start, becase we have lost our position
					sFCU.sLaserOpto.sOptoLaser[(Luint8)eLaser].eRxState = OPTONCDT_RX__BYTE_1;
				}

				break;

			default:
				//todo, log the error
				break;
		}//switch(sFCU.sOptoLaser[u8LaserIndex].eRxState)
	}
	else
	{
		//some major error
	}
}

/***************************************************************************//**
 * @brief
 * 100MS ISR point
 * 
 * @st_funcMD5		E23807C52369107D55D0953516ED2BFB
 * @st_funcID		LCCM655R0.FILE.021.FUNC.006
 */
void vFCU_LASEROPTO__100MS_ISR(void)
{

	sFCU.sLaserOpto.u32LaserPOR_Counter++;
}


#ifdef WIN32
/***************************************************************************//**
 * @brief
 * On win32, set the raw value only
 *
 * @param[in]		f32Value				Raw value in laser units
 * @param[in]		u32Index				The laser index
 * @st_funcMD5		B2906B4ECE0EF676386C646951C577AE
 * @st_funcID		LCCM655R0.FILE.021.FUNC.008
 */
void vFCU_LASEROPTO_WIN32__Set_DistanceRaw(Luint32 u32Index, Lfloat32 f32Value)
{

	sFCU.sLaserOpto.sOptoLaser[u32Index].f32DistanceRAW = f32Value;
	sFCU.sLaserOpto.sOptoLaser[u32Index].u8ReadyForFiltering = 1U;
}

#endif


#endif //C_LOCALDEF__LCCM655__ENABLE_LASER_OPTONCDT

#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */


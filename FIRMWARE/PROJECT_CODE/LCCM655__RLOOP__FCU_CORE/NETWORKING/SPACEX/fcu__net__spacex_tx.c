/**
 * @file		FCU__NET__SPACEX_TX.C
 * @brief		SpaceX specific network transmission
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
 * @addtogroup FCU__CORE_NET_SPACEX
 * @ingroup FCU
 * @{ */

#include "../../fcu_core.h"
#if C_LOCALDEF__LCCM655__ENABLE_ETHERNET == 1U
#if C_LOCALDEF__LCCM655__ENABLE_SPACEX_TELEMETRY == 1U

extern struct _strFCU sFCU;

//init the spaceX timed network transmission process
void vFCU_NET_SPACEX_TX__Init(void)
{
	//Clear the timer flag
	sFCU.sSpaceX.u8100MS_Flag = 0U;
	sFCU.sSpaceX.u32TestCounter = 0U;

}


//do the transmission

/* Teams shall send a binary telemetry frame for SpaceX monitoring of the status of their pod. The frame
 * shall be sent via UDP to IP 192.168.0.1, port 3000 at no greater than 10Hz, and must obey the following
 * format, where the type UINTx is an unsigned integer of x bits in length, and INTx is a twos-complement
 * signed integer of x bits in length. The first 5 fields are required; the latter five fields are optional. If a
 * field is unused, its value must be left as 0.
 *
 * Name 			Type 			Description
 * team_id 			UINT8 			Identifier for the team, assigned by SpaceX. Required.
 * status 			UINT8 			Pod status, indicating current pod health and pushing state, as defined below. Required.
 * acceleration 	INT32 			Acceleration in centimeters per second squared. Required.
 * position 		INT32 			Velocity in centimeters per second. Required.
 * velocity 		INT32 			Position in centimeters. Required.
 * battery_voltage 	INT32 			Battery voltage in millivolts.
 * battery_current 	INT32 			Battery current in milliamps.
 * battery_temperature INT32 		Battery temperature in tenths of a degree Celsius.
 * pod_temperature 	INT32 			Pod temperature in tenths of a degree Celsius.
 * stripe_count 	UINT32 			Count of optical navigation stripes detected in the tube.
 *
 */

void vFCU_NET_SPACEX_TX__Process(void)
{
	Luint8 u8Test;
	Luint16 u16PacketLength;
	Lint16 s16Return;
	Luint32 u32Buffer;
	Luint8 *pu8Return;

	//do we have a timer flag?
	if(sFCU.sSpaceX.u8100MS_Flag == 1U)
	{
		//send the UDP stream
		//see if we have space to transmit
		u8Test = u8ETH_FIFO__Is_Empty();
		if(u8Test == 1U)
		{

			//add space for the network packet
			u16PacketLength = 34U;
			s16Return = s16ETH_FIFO__Push(u16PacketLength);
			if(s16Return >= 0)
			{

				//get a pointer to the buffer
				u32Buffer = u32ETH_BUFFERDESC__Get_TxBufferPointer((Luint8)s16Return);
				pu8Return = (Luint8 *)u32Buffer;


				//team_id 			UINT8 			Identifier for the team, assigned by SpaceX. Required.
				pu8Return[0] = 0xAAU;
				pu8Return += 1U;

				//status 			UINT8 			Pod status, indicating current pod health and pushing state, as defined below. Required.
				pu8Return[0] = 0x01U;
				pu8Return += 1U;

				//acceleration 	INT32 			Acceleration in centimeters per second squared. Required.
				vNUMERICAL_CONVERT__Array_S32(pu8Return, 1111);
				pu8Return += 4U;

				//position 		INT32 			Velocity in centimeters per second. Required.
				vNUMERICAL_CONVERT__Array_S32(pu8Return, 22222);
				pu8Return += 4U;

				//velocity 		INT32 			Position in centimeters. Required.
				vNUMERICAL_CONVERT__Array_S32(pu8Return, 33333);
				pu8Return += 4U;

				//battery_voltage 	INT32 			Battery voltage in millivolts.
				vNUMERICAL_CONVERT__Array_S32(pu8Return, 4444);
				pu8Return += 4U;

				//battery_current 	INT32 			Battery current in milliamps.
				vNUMERICAL_CONVERT__Array_S32(pu8Return, 55555);
				pu8Return += 4U;

				//battery_temperature INT32 		Battery temperature in tenths of a degree Celsius.
				vNUMERICAL_CONVERT__Array_S32(pu8Return, 66666);
				pu8Return += 4U;

				//pod_temperature 	INT32 			Pod temperature in tenths of a degree Celsius.
				vNUMERICAL_CONVERT__Array_S32(pu8Return, -77777);
				pu8Return += 4U;

				//stripe_count 	UINT32 			Count of optical navigation stripes detected in the tube.
				vNUMERICAL_CONVERT__Array_U32(pu8Return, sFCU.sSpaceX.u32TestCounter++);
				pu8Return += 4U;

				//send it our SpaceX required port
				vETH_UDP__Transmit(u16PacketLength, 3000U, 3000U);

				//clear the flag only after a send because im sure SpX want the data
				//on the 100ms mark.
				sFCU.sSpaceX.u8100MS_Flag = 0U;

			}//if(s16Return >= 0)
			else
			{
				//FIFO error

			}//else if(s16Return >= 0)

		}//if(u8Test == 1U)
		else
		{
			//mo more space

		}//else if(u8Test == 1U)



	}
	else
	{
		//check later
	}


}


/***************************************************************************//**
 * @brief
 * To be called from the 10ms timer routine
 * Sets a flag to allow this module to determine that 10ms has elapsed
 *
 * @st_funcMD5		3A00D72EA0E8E8896C26BBDFA0E4F006
 * @st_funcID		LCCM655R0.FILE.019.FUNC.003
 */
void vFCU_NET_SPACEX_TX__100MS_ISR(void)
{
	sFCU.sSpaceX.u8100MS_Flag = 1U;
}

#endif //C_LOCALDEF__LCCM655__ENABLE_SPACEX_TELEMETRY
#ifndef C_LOCALDEF__LCCM655__ENABLE_SPACEX_TELEMETRY
	#error
#endif

#endif //C_LOCALDEF__LCCM653__ENABLE_ETHERNET
/** @} */
/** @} */
/** @} */


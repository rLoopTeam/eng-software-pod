/**
 * @file		FCU__BRAKES__ETHERNET.C
 * @brief		Eth diagnostics for brakes system
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
 * @addtogroup FCU__BRAKES__ETHERNET
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
#if C_LOCALDEF__LCCM655__ENABLE_ETHERNET == 1U

//the structure
extern struct _strFCU sFCU;


void vFCU_BRAKES_ETH__Init(void)
{

}


void vFCU_BRAKES_ETH__Process(E_NET__PACKET_T ePacketType)
{
	Lint16 s16Return;
	Luint8 * pu8Buffer;
	Luint8 u8BufferIndex;
	Luint16 u16Length;
	Luint8 u8Device;
	Luint8 u8Counter;

	pu8Buffer = 0;

	//setup length based on packet.
	switch(ePacketType)
	{
		case NET_PKT__FCU_BRAKES__TX_DATA:
			u16Length = 24U + 5U + 16U + 12U;
			break;

		default:
			u16Length = 0U;
			break;

	}//switch(ePacketType)

	//pre-comit
	s16Return = s16SAFEUDP_TX__PreCommit(u16Length, (SAFE_UDP__PACKET_T)ePacketType, &pu8Buffer, &u8BufferIndex);
	if(s16Return == 0)
	{
		//handle the packet
		switch(ePacketType)
		{
			case NET_PKT__FCU_BRAKES__TX_DATA:

				//for each brake
				for(u8Counter = 0U; u8Counter < FCU_BRAKE__MAX_BRAKES; u8Counter++)
				{
					//fault flags (general)
					vNUMERICAL_CONVERT__Array_U32(pu8Buffer, sFCU.sBrakes[u8Counter].sFaultFlags.u32Flags[0]);
					pu8Buffer += 4U;
					//spare
					vNUMERICAL_CONVERT__Array_U32(pu8Buffer, 0U);
					pu8Buffer += 4U;
					vNUMERICAL_CONVERT__Array_U32(pu8Buffer, 0U);
					pu8Buffer += 4U;
					vNUMERICAL_CONVERT__Array_U32(pu8Buffer, 0U);
					pu8Buffer += 4U;
					vNUMERICAL_CONVERT__Array_U32(pu8Buffer, 0U);
					pu8Buffer += 4U;
					vNUMERICAL_CONVERT__Array_U32(pu8Buffer, 0U);
					pu8Buffer += 4U;

					//switches area
					pu8Buffer[0] = (Luint8)sFCU.sBrakes[u8Counter].sLimits[BRAKE_SW__EXTEND].eSwitchState;
					pu8Buffer[1] = (Luint8)sFCU.sBrakes[u8Counter].sLimits[BRAKE_SW__RETRACT].eSwitchState;
					pu8Buffer[2] = sFCU.sBrakes[u8Counter].sLimits[BRAKE_SW__EXTEND].u8EdgeSeen;
					pu8Buffer[3] = sFCU.sBrakes[u8Counter].sLimits[BRAKE_SW__RETRACT].u8EdgeSeen;
					pu8Buffer[4] = sFCU.sBrakes[u8Counter].u8BrakeSWErr;
					pu8Buffer += 5U;

					//MLP
					vNUMERICAL_CONVERT__Array_U16(pu8Buffer, sFCU.sBrakes[u8Counter].sMLP.u16ADC_Sample);
					pu8Buffer += 2U;
					vNUMERICAL_CONVERT__Array_U16(pu8Buffer, sFCU.sBrakes[u8Counter].sMLP.u16ADC_Zero);
					pu8Buffer += 2U;
					vNUMERICAL_CONVERT__Array_S32(pu8Buffer, sFCU.sBrakes[u8Counter].sMLP.s32ADC_Minus_Zero);
					pu8Buffer += 4U;
					vNUMERICAL_CONVERT__Array_F32(pu8Buffer, sFCU.sBrakes[u8Counter].sMLP.f32SystemSpan);
					pu8Buffer += 4U;
					vNUMERICAL_CONVERT__Array_F32(pu8Buffer, sFCU.sBrakes[u8Counter].sMLP.f32BrakePosition_mm);
					pu8Buffer += 4U;

					//stepper system
					vNUMERICAL_CONVERT__Array_S32(pu8Buffer, sFCU.sBrakes[u8Counter].sMove.s32LinearVeloc);
					pu8Buffer += 4U;
					vNUMERICAL_CONVERT__Array_S32(pu8Buffer, sFCU.sBrakes[u8Counter].sMove.s32LinearAccel);
					pu8Buffer += 4U;
					vNUMERICAL_CONVERT__Array_S32(pu8Buffer, sFCU.sBrakes[u8Counter].sMove.s32currentPos);
					pu8Buffer += 4U;



				}//for(u8Counter = 0U; u8Counter < 2U; u8Counter++)

				break;

			default:
				//fall on
				break;

		}//switch(ePacketType)

		//send it
		vSAFEUDP_TX__Commit(u8BufferIndex, u16Length, C_LOCALDEF__LCCM528__ETHERNET_PORT_NUMBER, C_LOCALDEF__LCCM528__ETHERNET_PORT_NUMBER);

	}//if(s16Return == 0)
	else
	{
		//fault

	}//else if(s16Return == 0)

}


#endif //C_LOCALDEF__LCCM655__ENABLE_ETHERNET

#endif //C_LOCALDEF__LCCM655__ENABLE_BRAKES
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */


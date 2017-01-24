/**
 * @file		FCU__ASI__ETHERNET.C
 * @brief		Ethernet UDP layer for ASI interface
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
 * @addtogroup FCU__ASI__ETHERNET
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_ASI_RS485 == 1U
#if C_LOCALDEF__LCCM655__ENABLE_ETHERNET == 1U

extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init ASI ethernet interface
 * 
 * @st_funcMD5		FEFE127F7FF6EBDE796C21A3E09A0D0C
 * @st_funcID		LCCM655R0.FILE.074.FUNC.001
 */
void vFCU_ASI_ETH__Init(void)
{

}

/***************************************************************************//**
 * @brief
 * Do the ASI eth transmission
 * 
 * @param[in]		ePacketType				Packet Type
 * @st_funcMD5		83113C0895F1F7105CCD5AAA800911B8
 * @st_funcID		LCCM655R0.FILE.074.FUNC.002
 */
void vFCU_ASI_ETH__Transmit(E_NET__PACKET_T ePacketType)
{

	Lint16 s16Return;
	Luint8 * pu8Buffer;
	Luint8 u8BufferIndex;
	Luint16 u16Length;
	Luint8 u8Counter;

	pu8Buffer = 0;

	//setup length based on packet.
	switch(ePacketType)
	{
		case NET_PKT__FCU_ASI__TX_ASI_DATA:
			u16Length = 9U + 7U + 3U;
			u16Length += (C_FCU__NUM_HOVER_ENGINES * 12U);
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
			case NET_PKT__FCU_ASI__TX_ASI_DATA:


				//fault flags
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, 0U);
				pu8Buffer += 4U;

				pu8Buffer[0] = (Luint8)sFCU.sASI.eMainState;
				pu8Buffer += 1U;

				pu8Buffer[0] = (Luint8)sFCU.sASI.eModBusState;
				pu8Buffer += 1U;

				pu8Buffer[0] = (Luint8)sFCU.sASI.u8ScanIndex;
				pu8Buffer += 1U;

				vNUMERICAL_CONVERT__Array_U16(pu8Buffer, (Luint16)sFCU.sASI.eCommandList[sFCU.sASI.u8CommandListIndex]);
				pu8Buffer += 2U;

				//current command details
				pu8Buffer[0] = (Luint8)sFCU.sASI.sCurrentCommand.u8SlaveAddress;
				pu8Buffer += 1U;
				pu8Buffer[0] = (Luint8)sFCU.sASI.sCurrentCommand.eFunctionCode;
				pu8Buffer += 1U;
				vNUMERICAL_CONVERT__Array_U16(pu8Buffer, (Luint16)sFCU.sASI.sCurrentCommand.eObjectType);
				pu8Buffer += 2U;
				vNUMERICAL_CONVERT__Array_U16(pu8Buffer, sFCU.sASI.sCurrentCommand.u16ParamValue);
				pu8Buffer += 2U;
				pu8Buffer[0] = (Luint8)sFCU.sASI.sCurrentCommand.eDestVarType;
				pu8Buffer += 1U;


				//rxdata
				pu8Buffer[0] = (Luint8)sFCU.sASI.sCurrentCommand.eErrorType;
				pu8Buffer += 1U;
				vNUMERICAL_CONVERT__Array_U16(pu8Buffer, sFCU.sASI.sCurrentCommand.unDestVar.u16[0]);
				pu8Buffer += 2U;

				for(u8Counter = 0U; u8Counter < C_FCU__NUM_HOVER_ENGINES; u8Counter++)
				{
					vNUMERICAL_CONVERT__Array_U16(pu8Buffer, sFCU.sASI.sHolding[u8Counter].u16Faults);
					pu8Buffer += 2U;
				}
				for(u8Counter = 0U; u8Counter < C_FCU__NUM_HOVER_ENGINES; u8Counter++)
				{
					vNUMERICAL_CONVERT__Array_F32(pu8Buffer, sFCU.sASI.sHolding[u8Counter].f32TempC);
					pu8Buffer += 4U;
				}
				for(u8Counter = 0U; u8Counter < C_FCU__NUM_HOVER_ENGINES; u8Counter++)
				{
					vNUMERICAL_CONVERT__Array_F32(pu8Buffer, sFCU.sASI.sHolding[u8Counter].f32MotorCurrentA);
					pu8Buffer += 4U;
				}
				for(u8Counter = 0U; u8Counter < C_FCU__NUM_HOVER_ENGINES; u8Counter++)
				{
					vNUMERICAL_CONVERT__Array_U16(pu8Buffer, sFCU.sASI.sHolding[u8Counter].u16RPM);
					pu8Buffer += 2U;
				}
				break;

			default:

				break;

		}//switch(ePacketType)

		//send it
		vSAFEUDP_TX__Commit(u8BufferIndex, u16Length,
				C_RLOOP_NET__FCU__PORT,
				C_RLOOP_NET__FCU__PORT);

	}//if(s16Return == 0)
	else
	{
		//fault

	}//else if(s16Return == 0)

}



#endif //C_LOCALDEF__LCCM655__ENABLE_ETHERNET
#endif //C_LOCALDEF__LCCM655__ENABLE_ASI_RS485
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

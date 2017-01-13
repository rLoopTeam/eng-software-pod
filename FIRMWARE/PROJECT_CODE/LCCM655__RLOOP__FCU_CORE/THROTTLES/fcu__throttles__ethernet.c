/**
 * @file		FCU__THROTTLE__ETHERNET.C
 * @brief		Eth interface to throttle system
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
 * @addtogroup FCU__THROTTLE__ETHERNET
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_THROTTLE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_ETHERNET == 1U

extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init the throttle eth layer
 * 
 * @st_funcMD5		9668C2BF99BB9AE8A102370F75A04DE1
 * @st_funcID		LCCM655R0.FILE.073.FUNC.001
 */
void vFCU_THROTTLE_ETH__Init(void)
{

}

/***************************************************************************//**
 * @brief
 * Send a throttle eth packet
 * 
 * @param[in]		ePacketType				Packet Type
 * @st_funcMD5		A4CFC93349CAA75AE865E8DA5B587D50
 * @st_funcID		LCCM655R0.FILE.073.FUNC.002
 */
void vFCU_THROTTLE_ETH__Transmit(E_NET__PACKET_T ePacketType)
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
		case NET_PKT__FCU_THROTTLE__TX_DATA:
			u16Length = 8U;
			u16Length += (6U * C_FCU__NUM_HOVER_ENGINES);
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
			case NET_PKT__FCU_THROTTLE__TX_DATA:


				//throttle fault flags
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, sFCU.sThrottle.sFaultFlags.u32Flags[0]);
				pu8Buffer += 4U;

				//AMC Flags
				vNUMERICAL_CONVERT__Array_U32(pu8Buffer, u32AMC7812__Get_FaultFlags());
				pu8Buffer += 4U;

				//Requested RPM
				for(u8Counter = 0U; u8Counter < C_FCU__NUM_HOVER_ENGINES; u8Counter++)
				{
					vNUMERICAL_CONVERT__Array_U16(pu8Buffer, 0U);
					pu8Buffer += 2U;
				}

				//Current RPM
				for(u8Counter = 0U; u8Counter < C_FCU__NUM_HOVER_ENGINES; u8Counter++)
				{
					vNUMERICAL_CONVERT__Array_U16(pu8Buffer, 0U);
					pu8Buffer += 2U;
				}

				//see if we can feed back ASI data?
				for(u8Counter = 0U; u8Counter < C_FCU__NUM_HOVER_ENGINES; u8Counter++)
				{
					//ASI RPM
					vNUMERICAL_CONVERT__Array_U16(pu8Buffer, 0U);
					pu8Buffer += 2U;
				}

				break;

			default:

				break;

		}//switch(ePacketType)

		//send it
		vSAFEUDP_TX__Commit(u8BufferIndex, u16Length,
							C_LOCALDEF__LCCM528__ETHERNET_PORT_NUMBER,
							C_LOCALDEF__LCCM528__ETHERNET_PORT_NUMBER);

	}//if(s16Return == 0)
	else
	{
		//fault

	}//else if(s16Return == 0)

}


//safetly switch on dev mode
//Key1 = 0x77558833U
void vFCU_THROTTLE_ETH__Enable_DevMode(Luint32 u32Key0, Luint32 u32Key1)
{

	if(u32Key0 == 0x11223344U)
	{
		sFCU.sThrottle.sDevMode.u8Enabled = 1U;
		sFCU.sThrottle.sDevMode.u32SecurityKey = u32Key1;
	}
	else
	{
		sFCU.sThrottle.sDevMode.u8Enabled = 0U;
		sFCU.sThrottle.sDevMode.u32SecurityKey = 0U;
	}

}


void vFCU_THROTTLE_ETH__Set_Throttle(Luint8 u8EngineIndex, Luint16 u16RPM, Luint8 u8RampType)
{


}


#endif //C_LOCALDEF__LCCM655__ENABLE_ETHERNET
#endif //C_LOCALDEF__LCCM655__ENABLE_THROTTLES
#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

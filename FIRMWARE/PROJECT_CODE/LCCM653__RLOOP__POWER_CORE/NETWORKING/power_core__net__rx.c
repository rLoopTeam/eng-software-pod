/**
 * @file		POWER_CORE__NET__RX.C
 * @brief		Network Rx portion of the power core
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE__NETWORK__RX
 * @ingroup POWER_NODE
 * @{ */

#include "../power_core.h"

#if C_LOCALDEF__LCCM653__ENABLE_ETHERNET == 1U
#include <LCCM655__RLOOP__FCU_CORE/NETWORKING/fcu_core__net__packet_types.h>

extern struct _strPWRNODE sPWRNODE;

/***************************************************************************//**
 * @brief
 * Rx a standard UDP packet
 * 
 * @param[in]		u16DestPort			The desination UDP port
 * @param[in]		u16Length			The UDP Length
 * @param[in]		*pu8Buffer			Pointer to the UDP packet data
 * @st_funcMD5		7474DC6F85CD0C2610EA3ED9A058AC33
 * @st_funcID		LCCM653R0.FILE.018.FUNC.001
 */
void vPWRNODE_NET_RX__RxUDP(Luint8 *pu8Buffer, Luint16 u16Length, Luint16 u16DestPort)
{
	//pass to safety udp processor
	vSAFE_UDP_RX__UDPPacket(pu8Buffer,u16Length, u16DestPort);
}



/***************************************************************************//**
 * @brief
 * Rx a SafetyUDP
 * 
 * @param[in]		u16Fault				Fault details (if any)
 * @param[in]		u16DestPort				The destination port in the UDP packet
 * @param[in]		ePacketType				SafeUDP Packet Type
 * @param[in]		u16PayloadLength		SafeUDP Payload Length
 * @param[in]		*pu8Payload				Pointer to SafeUDP Payload
 * @st_funcMD5		AD548DCA137258A5308B46F94D254866
 * @st_funcID		LCCM653R0.FILE.018.FUNC.002
 */
void vPWRNODE_NET_RX__RxSafeUDP(Luint8 *pu8Payload, Luint16 u16PayloadLength, Luint16 ePacketType, Luint16 u16DestPort, Luint16 u16Fault)
{

	Luint32 u32Block[4];
	Lfloat32 f32Block[4];

	//make sure we are rx'ing on our port number
	if(u16DestPort == C_LOCALDEF__LCCM528__ETHERNET_PORT_NUMBER)
	{

		//blocks are good for putting into functions
		//this is inhernet in the safetyUDP layer
		u32Block[0] = u32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload);
		u32Block[1] = u32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload + 4U);
		u32Block[2] = u32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload + 8U);
		u32Block[3] = u32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload + 12U);

		f32Block[0] = f32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload);
		f32Block[1] = f32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload + 4U);
		f32Block[2] = f32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload + 8U);
		f32Block[3] = f32NUMERICAL_CONVERT__Array((const Luint8 *)pu8Payload + 12U);

		//determine the type of packet that came in
		switch((E_NET__PACKET_T)ePacketType)
		{


			case NET_PKT__PWR_GEN__POD_SAFE_COMMAND:
				if(u32Block[0] == 0x75643210U)
				{
					//Safe the pod

				}
				else
				{
					//maybe should log this error.
				}
				break;

			case NET_PKT__PWR_GEN__POD_EMULATION_CONTROL:

				break;


			case NET_PKT__PWR_GEN__CHARGER_CONTROL:
				//handle the charger
				if(u32Block[0] == 0x11229988U)
				{
					//see if we want to enable charging.
					if(u32Block[1] == 0x01)
					{
						vPWRNODE_SM__Enable_ChargingState();
					}
					else
					{
						vPWRNODE_SM__Stop_ChargingState();
					}
				}
				else
				{
					vPWRNODE_SM__Stop_ChargingState();
				}
				break;

			case NET_PKT__PWR_GEN__STREAMING_CONTROL:
				//if the host wants to stream data packets.
				if(u32Block[0] == 1U)
				{
					//streaming on
					sPWRNODE.sUDPDiag.eTxStreamingType = (E_NET__PACKET_T)u32Block[1];
				}
				else
				{
					//streaming off
					sPWRNODE.sUDPDiag.eTxStreamingType = NET_PKT__NONE;
				}

				break;

			case NET_PKT__PWR_GEN__MANUAL_BALANCE_CONTROL:

				//check our key
				if(u32Block[0] == 0x34566543U)
				{
					//check our enable bit
					if(u32Block[1] == 1U)
					{
						vPWRNODE_GHG__Start_ManualBalance();

						//apply
						vPWRNODE_BMS__Balance_Manual((Luint8)u32Block[2], (Luint8)u32Block[3]);

					}
					else
					{
						//abort
						vPWRNODE_GHG__Stop_ManualBalance();
						vPWRNODE_BMS__Balance_Stop();
					}
				}
				else
				{
					//abort
					vPWRNODE_GHG__Stop_ManualBalance();
					vPWRNODE_BMS__Balance_Stop();
				}
				break;

			case NET_PKT__PWR_GEN__LATCH:

				if(u32Block[0] == 0xABCD1245U)
				{
					if(u32Block[1] == 0U)
					{
						//Power Node A
						vPWRNODE_DC__Latch(0xABAB1122U);
					}
					else if(u32Block[1] == 1U)
					{
						//Power Node B
						vPWRNODE_DC__Latch(0xABAB1122U);
					}
					else
					{
						//not valid
					}
				}
				else
				{
					//invalid
				}
				break;

			case NET_PKT__PWR_TEMP__REQ_CURRENT_TEMPS:
				sPWRNODE.sUDPDiag.eTxPacketType = NET_PKT__PWR_TEMP__TX_CURRENT_TEMPS;
				break;

			case NET_PKT__PWR_TEMP__REQ_SENSOR_LOCATION:
				sPWRNODE.sUDPDiag.eTxPacketType = NET_PKT__PWR_TEMP__TX_SENSOR_LOCATION_DATA;
				break;

			case NET_PKT__PWR_TEMP__REQ_ROMID_INDEX:
				sPWRNODE.sUDPDiag.u32Block0 = u32Block[0];
				sPWRNODE.sUDPDiag.eTxPacketType = NET_PKT__PWR_TEMP__TX_ROMID_INDEX;
				break;

			case NET_PKT__PWR_TEMP__SET_ROMID_INDEX:
				#if C_LOCALDEF__LCCM653__ENABLE_BATT_TEMP == 1U
					vPWRNODE_BATTEMP_MEM__Set_ROMID(u32Block[0], u32Block[1], u32Block[2]);
				#endif
				break;

			case NET_PKT__PWR_TEMP__SET_USERDATA_INDEX:
				#if C_LOCALDEF__LCCM653__ENABLE_BATT_TEMP == 1U
					vPWRNODE_BATTEMP_MEM__Set_UserData(u32Block[0], u32Block[1], u32Block[2], u32Block[3]);
				#endif
				break;

			case NET_PKT__PWR_BMS__REQ_BMS:
				sPWRNODE.sUDPDiag.eTxPacketType = NET_PKT__PWR_BMS__TX_BMS_STATUS;
				break;

			case NET_PKT__PWR_BMS__SET_CHG_VALUES:
				switch(u32Block[0])
				{
					case 1U:
						vEEPARAM__WriteF32(C_POWERCORE__EEPARAM_INDEX__CHARGER__MAX_CELL_VOLT, f32Block[1], C_LOCALDEF__LCCM188_IMMEDIATE_WRITE);
						sPWRNODE.sCharger.f32MaxHighestCell = f32EEPARAM__Read(C_POWERCORE__EEPARAM_INDEX__CHARGER__MAX_CELL_VOLT);
						break;

					case 2U:
						vEEPARAM__WriteF32(C_POWERCORE__EEPARAM_INDEX__CHARGER__MAX_PACK_VOLT, f32Block[1], C_LOCALDEF__LCCM188_IMMEDIATE_WRITE);
						sPWRNODE.sCharger.f32MaxPackVoltage = f32EEPARAM__Read(C_POWERCORE__EEPARAM_INDEX__CHARGER__MAX_PACK_VOLT);
						break;

					case 3U:
						vEEPARAM__WriteF32(C_POWERCORE__EEPARAM_INDEX__CHARGER__MIN_PACK_VOLT, f32Block[1], C_LOCALDEF__LCCM188_IMMEDIATE_WRITE);
						sPWRNODE.sCharger.f32MinPackVoltage = f32EEPARAM__Read(C_POWERCORE__EEPARAM_INDEX__CHARGER__MIN_PACK_VOLT);
						break;

					case 4U:
						vEEPARAM__WriteF32(C_POWERCORE__EEPARAM_INDEX__CHARGER__MAX_CELL_TEMP, f32Block[1], C_LOCALDEF__LCCM188_IMMEDIATE_WRITE);
						sPWRNODE.sCharger.f32MaxCellTemp = f32EEPARAM__Read(C_POWERCORE__EEPARAM_INDEX__CHARGER__MAX_CELL_TEMP);
						break;

					default:
						break;
				}//switch(u32Block[0])
				break;



			default:
				//do nothing
				break;

		}//switch((E_FCU_NET_PACKET_TYPES)ePacketType)
	}
	else
	{
		//not for us
	}

}


#endif //C_LOCALDEF__LCCM653__ENABLE_ETHERNET
/** @} */
/** @} */
/** @} */


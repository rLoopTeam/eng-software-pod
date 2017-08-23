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
 * @st_funcMD5		846C8A515C3244ECDD1DA5B609B8C1E7
 * @st_funcID		LCCM653R0.FILE.018.FUNC.001
 */
void vPWRNODE_NET_RX__RxUDP(Luint8 *pu8Buffer, Luint16 u16Length, Luint16 u16DestPort)
{
	//pass to safety udp processor
	vSIL3_SAFEUDP_RX__UDPPacket(pu8Buffer,u16Length, u16DestPort);
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
 * @st_funcMD5		116A9079EF71D980FE146B60F169983E
 * @st_funcID		LCCM653R0.FILE.018.FUNC.002
 */
void vPWRNODE_NET_RX__RxSafeUDP(Luint8 *pu8Payload, Luint16 u16PayloadLength, Luint16 ePacketType, Luint16 u16DestPort, Luint16 u16Fault)
{

	Luint32 u32Block[4];
	Lfloat32 f32Block[4];


	//hard coded hack for podsafe
	if((u16DestPort == 9110U) || (u16DestPort == 9111U))
	{
		if(ePacketType == NET_PKT__PWR_GEN__POD_SAFE_COMMAND)
		{
			u32Block[0] = u32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload);
			if(u32Block[0] == 0x76543210U)
			{
				#if C_LOCALDEF__LCCM653__ENABLE_DC_CONVERTER == 1U
					//Safe the pod
					vPWRNODE_DC__Pod_Safe_Unlock(0xABCD1298U);
					vPWRNODE_DC__Pod_Safe_Go();
				#endif
			}
			else
			{
				//maybe should log this error.
			}
		}
		else
		{
			//fall on, another packet type
		}
	}
	else
	{
		//fall on.
	}


	//make sure we are rx'ing on our port number
	if(u16DestPort == sPWRNODE.u16EthPort)
	{

		//blocks are good for putting into functions
		//this is inhernet in the safetyUDP layer
		u32Block[0] = u32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload);
		u32Block[1] = u32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload + 4U);
		u32Block[2] = u32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload + 8U);
		u32Block[3] = u32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload + 12U);

		f32Block[0] = f32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload);
		f32Block[1] = f32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload + 4U);
		f32Block[2] = f32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload + 8U);
		f32Block[3] = f32SIL3_NUM_CONVERT__Array((const Luint8 *)pu8Payload + 12U);

		//determine the type of packet that came in
		switch((E_NET__PACKET_T)ePacketType)
		{


			case NET_PKT__PWR_GEN__POD_SAFE_COMMAND:
				//already done above
				break;

			case NET_PKT__PWR_GEN__POD_EMULATION_CONTROL:
				//not implemented yet.
				break;


			case NET_PKT__PWR_GEN__CHARGER_CONTROL:
				//handle the charger
				if(u32Block[0] == 0x11229988U)
				{
					//see if we want to enable charging.
					if(u32Block[1] == 1U)
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

				#if C_LOCALDEF__LCCM653__ENABLE_CHARGER == 1U
				//check our key
				if(u32Block[0] == 0x34566543U)
				{
					//check our enable bit
					if(u32Block[1] == 1U)
					{
						
						vPWRNODE_GHG__Start_ManualBalance();

						//apply
						#if C_LOCALDEF__LCCM653__ENABLE_BMS == 1U
							vPWRNODE_BMS__Balance_Manual((Luint8)u32Block[2], (Luint8)u32Block[3]);
						#endif

					}
					else
					{
						//abort
						vPWRNODE_GHG__Stop_ManualBalance();
						#if C_LOCALDEF__LCCM653__ENABLE_BMS == 1U
							vPWRNODE_BMS__Balance_Stop();
						#endif
					}
				}
				else
				{
					//abort
					vPWRNODE_GHG__Stop_ManualBalance();
					#if C_LOCALDEF__LCCM653__ENABLE_BMS == 1U
						vPWRNODE_BMS__Balance_Stop();
					#endif
				}
				#endif //C_LOCALDEF__LCCM653__ENABLE_CHARGER

				break;

			case NET_PKT__PWR_GEN__LATCH:
				#if C_LOCALDEF__LCCM653__ENABLE_DC_CONVERTER == 1U
				//latch the power on.
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
				#endif //C_LOCALDEF__LCCM653__ENABLE_DC_CONVERTER
				break;

			case NET_PKT__PWR_GEN__PV_REPRESS:
				#if C_LOCALDEF__LCCM653__ENABLE_PV_REPRESS == 1U
					vPWR_PVPRESS__Enable(u32Block[0]);
				#endif
				break;

			case NET_PKT__PWR_GEN__POWER_PERSONALITY:

				//personality key
				if(u32Block[0] == 0x11223344U)
				{
					if(u32Block[1] == 0U)
					{
						//Power Node A
						vSIL3_EEPARAM__WriteU32(C_POWERCORE__EEPARAM_INDEX__NODE_TYPE__TYPE_A, (Luint32)PWRNODE_TYPE__PACK_A, DELAY_T__DELAYED_WRITE);
						vSIL3_EEPARAM__WriteU32(C_POWERCORE__EEPARAM_INDEX__NODE_TYPE__TYPE_B, (Luint32)PWRNODE_TYPE__PACK_A, DELAY_T__IMMEDIATE_WRITE);

						vSIL3_EEPARAM_CRC__Calculate_And_Store_CRC(	C_POWERCORE__EEPARAM_INDEX__NODE_TYPE__TYPE_A,
																C_POWERCORE__EEPARAM_INDEX__NODE_TYPE__TYPE_B,
																C_POWERCORE__EEPARAM_INDEX__NODE_TYPE__TYPE_CRC);
						sPWRNODE.ePersonality = PWRNODE_TYPE__PACK_A;
					}
					else if(u32Block[1] == 1U)
					{
						//Power Node B
						vSIL3_EEPARAM__WriteU32(C_POWERCORE__EEPARAM_INDEX__NODE_TYPE__TYPE_A, (Luint32)PWRNODE_TYPE__PACK_B, DELAY_T__DELAYED_WRITE);
						vSIL3_EEPARAM__WriteU32(C_POWERCORE__EEPARAM_INDEX__NODE_TYPE__TYPE_B, (Luint32)PWRNODE_TYPE__PACK_B, DELAY_T__IMMEDIATE_WRITE);

						vSIL3_EEPARAM_CRC__Calculate_And_Store_CRC(	C_POWERCORE__EEPARAM_INDEX__NODE_TYPE__TYPE_A,
																C_POWERCORE__EEPARAM_INDEX__NODE_TYPE__TYPE_B,
																C_POWERCORE__EEPARAM_INDEX__NODE_TYPE__TYPE_CRC);
						sPWRNODE.ePersonality = PWRNODE_TYPE__PACK_B;
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
						#if C_LOCALDEF__LCCM653__ENABLE_CHARGER == 1U
							vSIL3_EEPARAM__WriteF32(C_POWERCORE__EEPARAM_INDEX__CHARGER__MAX_CELL_VOLT, f32Block[1], DELAY_T__IMMEDIATE_WRITE);
							sPWRNODE.sCharger.f32MaxHighestCell = f32SIL3_EEPARAM__Read(C_POWERCORE__EEPARAM_INDEX__CHARGER__MAX_CELL_VOLT);
						#endif
						break;

					case 2U:
						#if C_LOCALDEF__LCCM653__ENABLE_CHARGER == 1U
							vSIL3_EEPARAM__WriteF32(C_POWERCORE__EEPARAM_INDEX__CHARGER__MAX_PACK_VOLT, f32Block[1], DELAY_T__IMMEDIATE_WRITE);
							sPWRNODE.sCharger.f32MaxPackVoltage = f32SIL3_EEPARAM__Read(C_POWERCORE__EEPARAM_INDEX__CHARGER__MAX_PACK_VOLT);
						#endif
						break;

					case 3U:
						#if C_LOCALDEF__LCCM653__ENABLE_CHARGER == 1U
							vSIL3_EEPARAM__WriteF32(C_POWERCORE__EEPARAM_INDEX__CHARGER__MIN_PACK_VOLT, f32Block[1], DELAY_T__IMMEDIATE_WRITE);
							sPWRNODE.sCharger.f32MinPackVoltage = f32SIL3_EEPARAM__Read(C_POWERCORE__EEPARAM_INDEX__CHARGER__MIN_PACK_VOLT);
						#endif
						break;

					case 4U:
						#if C_LOCALDEF__LCCM653__ENABLE_CHARGER == 1U
							vSIL3_EEPARAM__WriteF32(C_POWERCORE__EEPARAM_INDEX__CHARGER__MAX_CELL_TEMP, f32Block[1], DELAY_T__IMMEDIATE_WRITE);
							sPWRNODE.sCharger.f32MaxCellTemp = f32SIL3_EEPARAM__Read(C_POWERCORE__EEPARAM_INDEX__CHARGER__MAX_CELL_TEMP);
						#endif
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


    //make sure we are rx'ing on our port number
    if(u16DestPort == C_PWRCORE__IPS_CHARGER_PORT)
    {
        //determine the type of packet that came in
        switch((E_NET__PACKET_T)ePacketType)
        {
            case NET_PKT__IPS__STATUS:

                break;
        }

    }else{
        //Nothing to do
    }
}


#endif //C_LOCALDEF__LCCM653__ENABLE_ETHERNET
/** @} */
/** @} */
/** @} */


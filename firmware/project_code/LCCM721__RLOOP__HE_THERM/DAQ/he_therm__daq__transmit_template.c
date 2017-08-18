/**
 * @file		HE_THERM__DAQ__TRANSMIT_TEMPLATE.C
 * @brief		DAQ transmit template
 * @author		Lachlan Grogan
 * @st_fileID	LCCM721R0.FILE.010
 */

/**
 * @addtogroup RLOOP
 * @{
*/
/**
 * @addtogroup HE_THERM
 * @ingroup RLOOP
 * @{
*/
/**
 * @addtogroup HE_THERM__DAQ
 * @ingroup HE_THERM
 * @{
*/
#include <LCCM721__RLOOP__HE_THERM/he_therm.h>
#if C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE == 1U


#include <MULTICORE/LCCM528__MULTICORE__SAFE_UDP/safe_udp__packet_types.h>

extern struct _strDAQ sDAQ;


/***************************************************************************//**
 * @brief
 * Do the DAQ transmit
 * 
 * @param[in]		u16LengthBytes			Transmit Length
 * @param[in]		pu8BufferPointer		Memory BUffer
 * @param[in]		u16Index				Channel Index
 * @st_funcMD5		5AFA15F5DAA5EF460C8A50BBFDBCAEC2
 * @st_funcID		LCCM720R0.FILE.010.FUNC.001
 */
Lint16 s16SIL3_DAQ_TRANSMIT__Template(Luint16 u16Index, Luint8 *pu8BufferPointer, Luint16 u16LengthBytes)
{
	Lint16 s16R;
	//the UDP payload Length
	Luint16 u16Length;
	//the UDP packet type.
	// Luint16 u16PacketType;
	Lint16 s16Return;
	Luint16 u16Counter;
	Luint8 u8BufferIndex;
	//pointer to the EMAC data allowing us to fill up here.
	Luint8 *pu8Buffer;


	//set the payload length
	u16Length = u16LengthBytes;


	//try and precommit to a UDP packet, if successful space then we get a buffer pointer and index
	//for future transmit
	#if C_LOCALDEF__LCCM662__ENABLE_USER_PAYLOAD_TYPES == 1U
	s16Return = s16SIL3_SAFEUDP_TX__PreCommit(u16Length, (SAFE_UDP__PACKET_T)sDAQ.u16User_PacketType[u16Index], &pu8Buffer, &u8BufferIndex);
	#else
	s16Return = s16SIL3_SAFEUDP_TX__PreCommit(u16Length, (SAFE_UDP__PACKET_T)((Luint16)NET_PKT__HE_THERM_DAQ__OFFSET_INDEX + u16Index), &pu8Buffer, &u8BufferIndex);
	#endif
	if(s16Return == 0)
	{

		//do the actual copy, blind for now, DMA in future
		for(u16Counter = 0U; u16Counter < u16Length; u16Counter++)
		{
			pu8Buffer[u16Counter] = pu8BufferPointer[u16Counter];
		}

		//send the buffer index, with a payload length, on UDP ports (source and dest port)
		vSIL3_SAFEUDP_TX__Commit(u8BufferIndex, u16Length, C_RLOOP_NET_PORT__HETHERM, C_RLOOP_NET_PORT__HETHERM);

		s16R = 0;
	}
	else
	{
		//some big error, unable to transmit
		//maybe the ETH was busy with an ARP or something, come back around and re-try in a minute
		s16R = -1;
	}

	return s16R;
}

#endif //C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE
#ifndef C_LOCALDEF__LCCM721__ENABLE_THIS_MODULE
	#error
#endif


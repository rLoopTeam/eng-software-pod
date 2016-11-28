//networking Rx

#include "../power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_ETHERNET == 1U

//rx a standard UDP packet
void vPWRNODE_NET_RX__RxUDP(Luint8 *pu8Buffer, Luint16 u16Length, Luint16 u16DestPort)
{

}
//rx a SafetyUDP
void vPWRNODE_NET_RX__RxSafeUDP(Luint8 *pu8Payload, Luint16 u16PayloadLength, Luint16 ePacketType, Luint16 u16DestPort, Luint16 u16Fault)
{

}


#endif //C_LOCALDEF__LCCM653__ENABLE_ETHERNET

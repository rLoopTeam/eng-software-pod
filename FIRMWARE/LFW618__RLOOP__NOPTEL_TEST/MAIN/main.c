#include <localdef.h>

int main()
{

	//init
	vFCU__Init();


	while(1)
	{
		//process
		vFCU__Process();
	}

}


//need to fake some things
Luint8 u8SIL3_SC16_USER__Get_Byte(Luint8 u8DeviceIndex)
{
    return u8RM4_SCI__RxByte(SCI_CHANNEL__3);
}

Luint8 u8SIL3_SC16_USER__Get_ByteAvail(Luint8 u8DeviceIndex)
{
    return u32RM4_SCI__Is__RxReady(SCI_CHANNEL__3);
}

void vSIL3_SC16__Tx_ByteArray(Luint8 u8DeviceIndex, Luint8 *pu8Array, Luint8 u8Length)
{
	vRM4_SCI__TxByteArray(SCI_CHANNEL__3, u8Length, pu8Array);
}

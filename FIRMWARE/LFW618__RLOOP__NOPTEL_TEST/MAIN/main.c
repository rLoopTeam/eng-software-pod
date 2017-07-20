#include <localdef.h>

//main FCU structure;
extern struct _strFCU sFCU;

int main()
{

	//init
	vFCU__Init();


	while(1)
	{
		//process
		vFCU__Process();

		if(sFCU.eInitStates == INIT_STATE__INIT_IO)
		{
			//on RM57 Launch, need this pin high
			vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_A, 3U, GIO_DIRECTION__OUTPUT);
			vRM4_GIO__Set_Bit(RM4_GIO__PORT_A, 3U, 1U);

			vRM4_DELAYS__Delay_mS(250);

			//test LED
			vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_B, 6, GIO_DIRECTION__OUTPUT);
			vRM4_GIO__Set_Bit(RM4_GIO__PORT_B, 6U, 0U);
			vRM4_GIO__Set_Bit(RM4_GIO__PORT_B, 6U, 1U);

		}

		//sneeky hack for this noptel test
		if(sFCU.eInitStates == INIT_STATE__INIT_COMMS)
		{
			//init the SCI for the laser
			#if C_LOCALDEF__LCCM282__ENABLE_THIS_MODULE == 1U
				vRM4_SCI__Init(SCI_CHANNEL__3);
				vRM4_SCI_BAUD__Set_Baudrate(SCI_CHANNEL__3, 9600U);
			#endif
		}

	}

}


//need to fake some things
Luint8 u8SIL3_SC16_USER__Get_Byte(Luint8 u8DeviceIndex)
{
    return u8RM4_SCI_RX__Rx_U8(SCI_CHANNEL__3);
}

Luint8 u8SIL3_SC16_USER__Get_ByteAvail(Luint8 u8DeviceIndex)
{

	Luint32 u32Test;
	Luint8 u8Return;

	u32Test = u32RM4_SCI_RX__Get_Is_Ready(SCI_CHANNEL__3);
	if(u32Test != 0)
	{
		u8Return = 1U;
	}
	else
	{
		u8Return = 0U;
	}

    return u8Return;
}

void vSIL3_SC16__Tx_ByteArray(Luint8 u8DeviceIndex, Luint8 *pu8Array, Luint8 u8Length)
{
	vRM4_SCI_TX__Tx_U8Array(SCI_CHANNEL__3, u8Length, pu8Array);
}

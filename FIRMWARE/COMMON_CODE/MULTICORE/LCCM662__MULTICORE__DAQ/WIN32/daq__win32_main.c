//WIN32 emulation routines.
#include "../daq.h"
#if C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE == 1U
#ifdef WIN32

Luint8 u8MACAddx[6];
Luint8 u8IPAddx[4];
Luint8 u8DataCounter;
//for sine wave samples
Luint16 u16CurrentSineSample;
Luint8 u8Timer;

//main section for the win32 emulation tests.
DLL_DECLARATION void vSIL3_DAQ_WIN32_MAIN__Init(void)
{
	Luint8 u8Test;

	
	//init
	u8DataCounter = 0U;
	u8Timer = 0U;

	//setup DAQ
	vSIL3_DAQ__Init();
	vSIL3_DAQ__Streaming_On();

	//config our packet types
	#if C_LOCALDEF__LCCM662__ENABLE_USER_PAYLOAD_TYPES == 1U
		vSIL3_DAQ__Config_UserPacketType(0U, 0x5000);
	#endif

	u8MACAddx[0] = 0x00;
	u8MACAddx[1] = 0x26;
	u8MACAddx[2] = 0x80;
	u8MACAddx[3] = 0x00;
	u8MACAddx[4] = 0x00;
	u8MACAddx[5] = 200;

	u8IPAddx[0] = 192;
	u8IPAddx[1] = 168;
	u8IPAddx[2] = 1;
	u8IPAddx[3] = 200;

	vSIL3_SAFEUDP__Init();

	//init the EMAC via its link setup routine.
	//vRM4_EMAC_LINK__Init(&u8MACAddx[0], &u8IPAddx[0]);

	//init the ethernet layer
	vSIL3_ETH__Init(&u8MACAddx[0], &u8IPAddx[0]);

}

//process the loop
DLL_DECLARATION void vSIL3_DAQ_WIN32_MAIN__Process(void)
{
	Lfloat32 f32Temp1;
	Lfloat32 f32Temp2;
	Luint8 u8Test;

	//process any safety UDP items
	vSIL3_SAFEUDP__Process();

	//constantly process the EMAC link as it will take some time to get operational
	//vRM4_EMAC_LINK__Process();

	//process the ethernet layer.
	vSIL3_ETH__Process();

	//process any DAQ tasks.
	vSIL3_DAQ__Process();

}

//1hz timer, use this to emulate the CPU load meter
//U8
DLL_DECLARATION void vSIL3_DAQ_WIN32_MAIN__1HZ_ISR(Luint8 u8Value)
{
	//cpu load
	vSIL3_DAQ_APPEND__U8(0, u8Value);
}


void vSIL3_DAQ_WIN32_MAIN__RxUDPSafe(Luint8 *pu8Payload, Luint16 u16PayloadLength, SAFE_UDP__PACKET_T ePacketType, Luint16 u16DestPort, SAFE_UDP__FAULTS_T eFault)
{

	Luint32 u32Temp;

	switch((Luint16)ePacketType)
	{

		case SAFE_UDP__LCCM662__DAQ_STREAMING_CONTROL:

			u32Temp = u32SIL3_NUM_CONVERT__Array(pu8Payload + 0);

			//enable / disable streaming
			if(u32Temp == 0)
			{
				vSIL3_DAQ__Streaming_Off();
			}
			else
			{
				vSIL3_DAQ__Streaming_On();
			}

			break;

	}

}

#endif //win32
#endif //C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE



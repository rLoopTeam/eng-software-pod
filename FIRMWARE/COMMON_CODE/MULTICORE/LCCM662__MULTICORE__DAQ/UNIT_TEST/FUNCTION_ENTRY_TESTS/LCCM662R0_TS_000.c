#include <localdef.h>

#ifndef C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE
	#error
#endif

#if C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM662__ENABLE_TEST_SPEC == 1U
/*
VB.NET CALL
<System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)> Private Shared Sub vLCCM662R0_TS_000()
End Sub
copy to localdef.h
#include <stdio.h>
#define DEBUG_PRINT(x) vLU_SendString(XPAR_LVHD016_UART_0_BASEADDR, (const Xuint8 *)x)
#define DEBUG_PRINT(x) printf(x)
*/
extern struct _strDAQ sDAQ;
void vLCCM662R0_TS_000_TCASE_001(void);


//Function to call the tests for this test specification
void vLCCM662R0_TS_000(void)
{

	//Call the test cases
	vLCCM662R0_TS_000_TCASE_001();

}

//Individual Test Cases can be found below
/***************************************************************************//**
 * @st_test_case_id
 * LCCM662R0.TS.000.TCASE.001
 * @st_test_desc
 * Basic Add Test Case
 * 
*/
void vLCCM662R0_TS_000_TCASE_001(void)
{
	Luint16 u16Index;
	Luint8 u8Value;
	Luint16 u16Counter;
	Luint8 u8Test;
	DEBUG_PRINT("START:LCCM662R0.TS.000.TCASE.001\r\n");

	//setup
	vSIL3_DAQ__Init();

	//switch on streaming
	vSIL3_DAQ__Streaming_On();

	//Call the target function
	u16Index = 0U;
	u8Value = 0xAA;
	for (u16Counter = 0U; u16Counter < C_LOCALDEF__LCCM662__BUFFER_WATERMARK_LEVEL*4; u16Counter++)
	{
		vSIL3_DAQ_APPEND__U8(u16Index, (Luint8)u16Counter);
	}

	//add one more
	vSIL3_DAQ_APPEND__U8(u16Index, 0xBB);
	
	u16Index = 1U;
	for (u16Counter = 0U; u16Counter < C_LOCALDEF__LCCM662__BUFFER_WATERMARK_LEVEL; u16Counter++)
	{
		vSIL3_DAQ_APPEND__F32(u16Index, (Lfloat32)u16Counter);
	}

	//add one more
	vSIL3_DAQ_APPEND__F32(u16Index, 999.999F);

	#ifdef WIN32
		sDAQ.sWIN32.u8NewPacket[0] = 0U;

		do
		{
			vSIL3_DAQ__Process();

		} while (sDAQ.sWIN32.u8NewPacket[0] == 0U);

		//check
		u8Test = 0U;
		u16Index = 0U;
		for (u16Counter = 0U; u16Counter < C_LOCALDEF__LCCM662__BUFFER_WATERMARK_LEVEL * 4; u16Counter++)
		{
			//check for a buffer match
			if (sDAQ.sWIN32.u8LastArray[u16Index][u16Counter] != (Luint8)u16Counter)
			{
				u8Test = 1U;
			}
			else
			{
				//good to go
			}
		}

		//check the last one
		if (sDAQ.sWIN32.u8LastArray[u16Index][u16Counter] != 0xBBU)
		{
			u8Test = 1U;
		}
	#else	
		//do a bit of processing
		vSIL3_DAQ__Process();
		vSIL3_DAQ__Process();
		vSIL3_DAQ__Process();
	#endif



	//todo: USER TO ADD
	if(1)
	{
		DEBUG_PRINT("PASS:LCCM662R0.TS.000.TCASE.001\r\n");
	}
	else
	{
		DEBUG_PRINT("FAIL:LCCM662R0.TS.000.TCASE.001\r\n");
	}
	DEBUG_PRINT("END:LCCM662R0.TS.000.TCASE.001\r\n");

}

#endif
#ifndef C_LOCALDEF__LCCM662__ENABLE_TEST_SPEC
	#error
#endif

#endif


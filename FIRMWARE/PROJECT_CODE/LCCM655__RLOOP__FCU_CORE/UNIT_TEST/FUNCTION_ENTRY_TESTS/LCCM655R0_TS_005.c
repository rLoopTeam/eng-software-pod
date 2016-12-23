#include <localdef.h>

#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_TEST_SPEC == 1U
/*
VB.NET CALL
<System.Runtime.InteropServices.DllImport(C_DLL_NAME, CallingConvention:=System.Runtime.InteropServices.CallingConvention.Cdecl)> Private Shared Sub vLCCM655R0_TS_005()
End Sub
copy to localdef.h
#include <stdio.h>
#define DEBUG_PRINT(x) vLU_SendString(XPAR_LVHD016_UART_0_BASEADDR, (const Xuint8 *)x)
#define DEBUG_PRINT(x) printf(x)
*/

void vLCCM655R0_TS_005_TCASE_001(void);
//local function declarations
void vLCCM655R0_TS_005(void);

/*
int main()
{
	//Call your setup functions here...

	//Start the tests
	vLCCM655R0_TS_005();

}
*/

//Function to call the tests for this test specification
void vLCCM655R0_TS_005(void)
{

	//Call the test cases
	vLCCM655R0_TS_005_TCASE_001();

}

//Individual Test Cases can be found below
/***************************************************************************//**
 * @st_test_case_id
 * LCCM655R0.TS.005.TCASE.001
 * @st_test_desc
 * Todo
 * 
*/
void vLCCM655R0_TS_005_TCASE_001(void)
{
	DEBUG_PRINT("START:LCCM655R0.TS.005.TCASE.001\r\n");

	//Call the target function
	E_FCU__LASER_CONT_INDEX_T eLaser = ;
	Luint32 u32Test = u32FCU_LASERCONT_TRKDB__Get_DistancePrevSeg_mm(eLaser);
	//todo: USER TO ADD
	if(u32Test == )
	{
		DEBUG_PRINT("PASS:LCCM655R0.TS.005.TCASE.001\r\n");
	}
	else
	{
		DEBUG_PRINT("FAIL:LCCM655R0.TS.005.TCASE.001\r\n");
	}
	DEBUG_PRINT("END:LCCM655R0.TS.005.TCASE.001\r\n");

}

#endif
#ifndef C_LOCALDEF__LCCM655__ENABLE_TEST_SPEC
	#error
#endif

#endif


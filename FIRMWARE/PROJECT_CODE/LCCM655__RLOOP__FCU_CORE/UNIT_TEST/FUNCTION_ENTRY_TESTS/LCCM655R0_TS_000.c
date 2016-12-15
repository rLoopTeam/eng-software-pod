#include <localdef.h>

#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_TEST_SPEC == 1U

void vLCCM655R0_TS_000_TCASE_001(void);

//Function to call the tests for this test specification
void vLCCM655R0_TS_000(void)
{

	//Call the test cases
	vLCCM655R0_TS_000_TCASE_001();

	//todo, otehr test states

}

//Individual Test Cases can be found below
/***************************************************************************//**
 * @st_test_case_id
 * LCCM655R0.TS.000.TCASE.001
 * @st_test_desc
 * Check the left extend switch
 * 
*/
void vLCCM655R0_TS_000_TCASE_001(void)
{
	E_FCU__BRAKE_INDEX_T eBrake = FCU_BRAKE__LEFT;
	E_FCU__BRAKE_LIMSW_INDEX_T eSwitch = BRAKE_SW__EXTEND;
	E_FCU__SWITCH_STATE_T eReturn;

	DEBUG_PRINT("START:LCCM655R0.TS.000.TCASE.001\r\n");

	//pre-setup the test by faking the structure
	sFCU.sBrakes[eBrake].sLimits[eSwitch].eSwitchState = SW_STATE__UNKNOWN;

	//Call the target function
	eReturn = eFCU_BRAKES__Get_SwtichState(eBrake, eSwitch);

	//do the test
	if(eReturn == SW_STATE__UNKNOWN)
	{
		DEBUG_PRINT("PASS:LCCM655R0.TS.000.TCASE.001\r\n");
	}
	else
	{
		DEBUG_PRINT("FAIL:LCCM655R0.TS.000.TCASE.001\r\n");
	}
	DEBUG_PRINT("END:LCCM655R0.TS.000.TCASE.001\r\n");

}

#endif
#ifndef C_LOCALDEF__LCCM655__ENABLE_TEST_SPEC
	#error
#endif

#endif


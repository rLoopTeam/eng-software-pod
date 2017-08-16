#include <localdef.h>

#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_TEST_SPEC == 1U

void vLCCM655R0_TS_000_TCASE_001(void);
void vLCCM655R0_TS_000_TCASE_002(void);
void vLCCM655R0_TS_000_TCASE_003(void);
void vLCCM655R0_TS_000_TCASE_004(void);

//Function to call the tests for this test specification
void vLCCM655R0_TS_000(void)
{

	//Call the test cases

	//Tests for getting the switch state
	vLCCM655R0_TS_000_TCASE_001();
	vLCCM655R0_TS_000_TCASE_002();
	vLCCM655R0_TS_000_TCASE_003();
	vLCCM655R0_TS_000_TCASE_004();

	//todo, other test states

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

#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
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

#endif

	DEBUG_PRINT("END:LCCM655R0.TS.000.TCASE.001\r\n");

}

/***************************************************************************//**
 * @st_test_case_id
 * LCCM655R0.TS.000.TCASE.002
 * @st_test_desc
 * Check the right extend switch
 *
*/
void vLCCM655R0_TS_000_TCASE_002(void)
{
	E_FCU__BRAKE_INDEX_T eBrake = FCU_BRAKE__RIGHT;
	E_FCU__BRAKE_LIMSW_INDEX_T eSwitch = BRAKE_SW__EXTEND;
	E_FCU__SWITCH_STATE_T eReturn;

	DEBUG_PRINT("START:LCCM655R0.TS.000.TCASE.002\r\n");

#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
	//pre-setup the test by faking the structure
	sFCU.sBrakes[eBrake].sLimits[eSwitch].eSwitchState = SW_STATE__UNKNOWN;

	//Call the target function
	eReturn = eFCU_BRAKES__Get_SwtichState(eBrake, eSwitch);

	//do the test
	if(eReturn == SW_STATE__UNKNOWN)
	{
		DEBUG_PRINT("PASS:LCCM655R0.TS.000.TCASE.002\r\n");
	}
	else
	{
		DEBUG_PRINT("FAIL:LCCM655R0.TS.000.TCASE.002\r\n");
	}

#endif

	DEBUG_PRINT("END:LCCM655R0.TS.000.TCASE.002\r\n");

}

/***************************************************************************//**
 * @st_test_case_id
 * LCCM655R0.TS.000.TCASE.003
 * @st_test_desc
 * Check the left retract switch
 *
*/
void vLCCM655R0_TS_000_TCASE_003(void)
{
	E_FCU__BRAKE_INDEX_T eBrake = FCU_BRAKE__LEFT;
	E_FCU__BRAKE_LIMSW_INDEX_T eSwitch = BRAKE_SW__RETRACT;
	E_FCU__SWITCH_STATE_T eReturn;

	DEBUG_PRINT("START:LCCM655R0.TS.000.TCASE.003\r\n");

#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
	//pre-setup the test by faking the structure
	sFCU.sBrakes[eBrake].sLimits[eSwitch].eSwitchState = SW_STATE__UNKNOWN;

	//Call the target function
	eReturn = eFCU_BRAKES__Get_SwtichState(eBrake, eSwitch);

	//do the test
	if(eReturn == SW_STATE__UNKNOWN)
	{
		DEBUG_PRINT("PASS:LCCM655R0.TS.000.TCASE.003\r\n");
	}
	else
	{
		DEBUG_PRINT("FAIL:LCCM655R0.TS.000.TCASE.003\r\n");
	}

#endif

	DEBUG_PRINT("END:LCCM655R0.TS.000.TCASE.003\r\n");

}

/***************************************************************************//**
 * @st_test_case_id
 * LCCM655R0.TS.000.TCASE.004
 * @st_test_desc
 * Check the right retract switch
 *
*/
void vLCCM655R0_TS_000_TCASE_004(void)
{
	E_FCU__BRAKE_INDEX_T eBrake = FCU_BRAKE__RIGHT;
	E_FCU__BRAKE_LIMSW_INDEX_T eSwitch = BRAKE_SW__RETRACT;
	E_FCU__SWITCH_STATE_T eReturn;

	DEBUG_PRINT("START:LCCM655R0.TS.000.TCASE.004\r\n");

#if C_LOCALDEF__LCCM655__ENABLE_BRAKES == 1U
	//pre-setup the test by faking the structure
	sFCU.sBrakes[eBrake].sLimits[eSwitch].eSwitchState = SW_STATE__UNKNOWN;

	//Call the target function
	eReturn = eFCU_BRAKES__Get_SwtichState(eBrake, eSwitch);

	//do the test
	if(eReturn == SW_STATE__UNKNOWN)
	{
		DEBUG_PRINT("PASS:LCCM655R0.TS.000.TCASE.004\r\n");
	}
	else
	{
		DEBUG_PRINT("FAIL:LCCM655R0.TS.000.TCASE.004\r\n");
	}

#endif

	DEBUG_PRINT("END:LCCM655R0.TS.000.TCASE.004\r\n");

}

#endif
#ifndef C_LOCALDEF__LCCM655__ENABLE_TEST_SPEC
	#error
#endif

#endif


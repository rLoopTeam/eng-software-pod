#include <localdef.h>

#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_TEST_SPEC == 1U
#if C_LOCALDEF__LCCM655__ENABLE_ASI_RS485 == 1U

void vLCCM655R0_TS_007_TCASE_001(void);


//Function to call the tests for this test specification
void vLCCM655R0_TS_007(void)
{

	//Call the test cases
	vLCCM655R0_TS_007_TCASE_001();

}

//Individual Test Cases can be found below
/***************************************************************************//**
 * @st_test_case_id
 * LCCM655R0.TS.007.TCASE.001
 * @st_test_desc
 * Call the ASI command to read rpm on all 8 devices
 *
*/
void vLCCM655R0_TS_007_TCASE_001(void)
{
	Luint16 u16RPM;
	Lint16 status;
	Luint8 devIndex;
	char msg[256];

	DEBUG_PRINT("START:LCCM655R0.TS.007.TCASE.001\r\n");

	// go through all asi controllers
	for (devIndex=0; devIndex < 8; devIndex++)
	{
		status = s16FCU_ASI__ReadMotorRpm(devIndex, &u16RPM);
		if (status != 0)
		{
			sprintf(msg, "ERROR:LCCM655R0.TS.007.TCASE.001: reading %d\r\n", devIndex);
			DEBUG_PRINT(msg);
		}
		if (u16RPM == 1750)
		{
			sprintf(msg, "PASS:LCCM655R0.TS.007.TCASE.001: reading %d\r\n", devIndex);
			DEBUG_PRINT(msg);
		}
		else
		{
			sprintf(msg, "FAIL:LCCM655R0.TS.007.TCASE.001: reading %d\r\n", devIndex);
			DEBUG_PRINT(msg);
		}
	}

	DEBUG_PRINT("END:LCCM655R0.TS.007.TCASE.001\r\n");

}

#endif //C_LOCALDEF__LCCM655__ENABLE_ASI_RS485
#endif
#ifndef C_LOCALDEF__LCCM655__ENABLE_TEST_SPEC
	#error
#endif

#endif


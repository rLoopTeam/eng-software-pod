#include <localdef.h>

#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_TEST_SPEC == 1U
#if C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST == 1U

void vLCCM655R0_TS_001_TCASE_001(void);


//Function to call the tests for this test specification
void vLCCM655R0_TS_001(void)
{

	//Call the test cases
	vLCCM655R0_TS_001_TCASE_001();

}

//Individual Test Cases can be found below
/***************************************************************************//**
 * @st_test_case_id
 * LCCM655R0.TS.001.TCASE.001
 * @st_test_desc
 * Trigger the laser interface
 * 
*/
void vLCCM655R0_TS_001_TCASE_001(void)
{
	E_FCU__LASER_CONT_INDEX_T eLaser;
	Luint32 u32Register;
	Luint8 u8Test;
	
	DEBUG_PRINT("START:LCCM655R0.TS.001.TCASE.001\r\n");

	//setup
	vFCU_LASERCONT__Init();


	//Call the target function
	eLaser = LASER_CONT__FWD;

	//trigger rising edge on pin 6
	u32Register = 1 << 6U;
	vFCU_LASERCONT_TL__ISR(eLaser, u32Register);

	//at this point we should have incremented to the next marker on the track
	u8Test = 1U;

	if (u8FCU_LASERCONT_TL__Get_NewRisingAvail(eLaser) != 1U)
	{
		u8Test = 0U;
	}

	
	
	if(u8Test == 1U)
	{
		DEBUG_PRINT("PASS:LCCM655R0.TS.001.TCASE.001\r\n");
	}
	else
	{
		DEBUG_PRINT("FAIL:LCCM655R0.TS.001.TCASE.001\r\n");
	}
	DEBUG_PRINT("END:LCCM655R0.TS.001.TCASE.001\r\n");

}
#endif //C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST

#endif
#ifndef C_LOCALDEF__LCCM655__ENABLE_TEST_SPEC
	#error
#endif

#endif


#include <localdef.h>

#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_TEST_SPEC == 1U
#if C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST == 1U

void vLCCM655R0_TS_003_TCASE_001(void);


//Function to call the tests for this test specification
void vLCCM655R0_TS_003(void)
{

	//Call the test cases
	vLCCM655R0_TS_003_TCASE_001();

}

//Individual Test Cases can be found below
/***************************************************************************//**
 * @st_test_case_id
 * LCCM655R0.TS.003.TCASE.001
 * @st_test_desc
 * Compute the track database info based on the last interupt edge
 * 
*/
void vLCCM655R0_TS_003_TCASE_001(void)
{
	E_FCU__LASER_CONT_INDEX_T eLaser;
	Luint8 u8Test;
	Luint32 u32Register;

	DEBUG_PRINT("START:LCCM655R0.TS.003.TCASE.001\r\n");

	//setup
	vFCU_LASERCONT__Init();

	//work on the forward laser only
	eLaser = LASER_CONT__FWD;

	//generate one interrupt, this means we have passed our first track marker
	
	//rising edge, at 1000 x 20ns = 
	u64RTI_WIN32__Counter1 = 1000;
	u32Register = 1 << 6U;
	vFCU_LASERCONT_TL__ISR(eLaser, u32Register);

	//falling edge
	u64RTI_WIN32__Counter1 = 2000;
	u32Register = 0 << 6U;
	vFCU_LASERCONT_TL__ISR(eLaser, u32Register);

	//rising edge, at 11000 x 20ns
	//total time between edges is 10000 * 20ns = 200us
	//total distance between edges is 30480 mm
	//veloc = dist/time = 30480 / 200u = 152.4x10^6 mm/sec
	u64RTI_WIN32__Counter1 = 11000;
	u32Register = 1 << 6U;
	vFCU_LASERCONT_TL__ISR(eLaser, u32Register);

	//falling edge
	u64RTI_WIN32__Counter1 = 12000;
	u32Register = 0 << 6U;
	vFCU_LASERCONT_TL__ISR(eLaser, u32Register);

	//allow processing to take place
	vFCU_LASERCONT__Process();

	//Call the target function
	vFCU_LASERCONT_TRKDB__Compute(eLaser);

	u8Test = 1U;


	if(u8Test == 1U)
	{
		DEBUG_PRINT("PASS:LCCM655R0.TS.003.TCASE.001\r\n");
	}
	else
	{
		DEBUG_PRINT("FAIL:LCCM655R0.TS.003.TCASE.001\r\n");
	}
	DEBUG_PRINT("END:LCCM655R0.TS.003.TCASE.001\r\n");

}


#endif //C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST
#endif
#ifndef C_LOCALDEF__LCCM655__ENABLE_TEST_SPEC
	#error
#endif

#endif


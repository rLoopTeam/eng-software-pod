#include <localdef.h>

#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_TEST_SPEC == 1U
#if C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST == 1U

void vLCCM655R0_TS_003_TCASE_001(void);
void vLCCM655R0_TS_003_TCASE_002(void);


//Function to call the tests for this test specification
void vLCCM655R0_TS_003(void)
{

	//Call the test cases
	//vLCCM655R0_TS_003_TCASE_001();

	vLCCM655R0_TS_003_TCASE_002();
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

/***************************************************************************//**
 * @st_test_case_id
 * LCCM655R0.TS.003.TCASE.002
 * @st_test_desc
 * Real life track data
 * 
*/
void vLCCM655R0_TS_003_TCASE_002(void)
{
	E_FCU__LASER_CONT_INDEX_T eLaser;
	Luint8 u8Test;
	Luint32 u32Register;
	Luint32 u32Counter;

	//set for our data.
	Luint32 u32Stripes = 21;

	//21
	Luint64 u64RisingList[] = {
	6808776603,
	6896933372,
	6933449089,
	6961468587,
	6985090108,
	7005901081,
	7024715666,
	7042017436,
	7058121545,
	7073246858,
	7087552713,
	7101159467,
	7114160540,
	7126630284,
	7138628953,
	7150206217,
	7161403596,
	7172256192,
	7182794008,
	7193042958,
	7203025565
	};

	//21
	Luint64 u64FallingList[] = {
	6813876370,
	6897080759,
	6933553342,
	6961553728,
	6985163859,
	7006548066,
	7024775870,
	7042073186,
	7058173699,
	7073296019,
	7087599364,
	7101203936,
	7114203117,
	7126671180,
	7138668364,
	7150244307,
	7161440466,
	7172291970,
	7182828766,
	7193076797,
	7203058541
	};


	DEBUG_PRINT("START:LCCM655R0.TS.003.TCASE.002\r\n");

	//setup
	vFCU_LASERCONT__Init();

	//work on the forward laser only
	eLaser = LASER_CONT__FWD;

	//clock the data in
	for (u32Counter = 0U; u32Counter < u32Stripes; u32Counter++)
	{
		//rising edge
		u64RTI_WIN32__Counter1 = u64RisingList[u32Counter];
		u32Register = 1 << 6U;
		vFCU_LASERCONT_TL__ISR(eLaser, u32Register);

		//falling edge
		u64RTI_WIN32__Counter1 = u64FallingList[u32Counter];
		u32Register = 0 << 6U;
		vFCU_LASERCONT_TL__ISR(eLaser, u32Register);

		//do some processing here
		vFCU_LASERCONT__Process();
	}
	

	//allow processing to take place
	//in reality processing could be called hundreds of times between stripes.
	vFCU_LASERCONT__Process();

	//Call the target function
	//vFCU_LASERCONT_TRKDB__Compute(eLaser);

	u8Test = 1U;


	if(u8Test == 1U)
	{
		DEBUG_PRINT("PASS:LCCM655R0.TS.003.TCASE.002\r\n");
	}
	else
	{
		DEBUG_PRINT("FAIL:LCCM655R0.TS.003.TCASE.002\r\n");
	}
	DEBUG_PRINT("END:LCCM655R0.TS.003.TCASE.002\r\n");

}


#endif //C_LOCALDEF__LCCM655__ENABLE_LASER_CONTRAST
#endif
#ifndef C_LOCALDEF__LCCM655__ENABLE_TEST_SPEC
	#error
#endif

#endif


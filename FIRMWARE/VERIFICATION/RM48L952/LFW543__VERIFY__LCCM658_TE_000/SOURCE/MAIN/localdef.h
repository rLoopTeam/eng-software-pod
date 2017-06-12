

#ifndef LOCALDEF_H_
#define LOCALDEF_H_

	/*lint -e950*/

	//Run on Flight Control Hardware
	#include <../../../../BOARD_SUPPORT/lpcb235r0__board_support.h>

	#undef C_LOCALDEF__LCCM280__ENABLE_THIS_MODULE
	#define C_LOCALDEF__LCCM280__ENABLE_THIS_MODULE 0


/*******************************************************************************
AMC7812
*******************************************************************************/
	#define C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE == 1U

        //I2C Bus Address
        // See Table 8, p. 49 and p. 51, ACM7812 datasheet
        #define C_LOCALDEF__LCCM658__BUS_ADDX                               (0xC2)

        /** Num devices on the bus */
        #define C_LOCALDEF__LCCM658__NUM_DEVICES                            (1U)

        /** Testing Options */
        #define C_LOCALDEF__LCCM658__ENABLE_TEST_SPEC                       (0U)

        /** The number of main program loops to wait for conversion */
        #define C_LOCALDEF__LCCM658__NUM_CONVERSION_LOOPS                   (10000U)

        //Reset pin
        #define C_LOCALDEF__LCCM658__NRESET__TRIS(x)                        {vRM4_N2HET_PINS__Set_PinDirection_Output(N2HET_CHANNEL__1, 18U);}
        #define C_LOCALDEF__LCCM658__NRESET__LATCH(x)                       {if(x == 0)vRM4_N2HET_PINS__Set_PinLow(N2HET_CHANNEL__1, 18U); else vRM4_N2HET_PINS__Set_PinHigh(N2HET_CHANNEL__1, 18U);}


		/** Main include file */
		#include <MULTICORE/LCCM658__MULTICORE__AMC7812/amc7812.h>
	#endif //#if C_LOCALDEF__LCCM658__ENABLE_THIS_MODULE == 1U


	/*lint +e950*/
	


#endif /* LOCALDEF_H_ */

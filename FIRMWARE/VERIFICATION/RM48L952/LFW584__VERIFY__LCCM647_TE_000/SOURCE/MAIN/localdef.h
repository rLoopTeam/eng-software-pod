

#ifndef LOCALDEF_H_
#define LOCALDEF_H_

	/*lint -e950*/

	//Run on RM48 CNCD
	#include <../../../../../BOARD_SUPPORT/lpcb234r0__board_support.h>


/*******************************************************************************
TSYS01 - DIGITAL TEMP SENSOR
*******************************************************************************/
    #define C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE                         (1U)
    #if C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE == 1U

        /** The number of main program loops to wait for conversion */
        #define C_LOCALDEF__LCCM647__NUM_CONVERSION_LOOPS                   (10000U)

        /** the I2C address on the bus */
        #define C_LOCALDEF__LCCM647__BUS_ADDX                               (0x77U)

        /** Testing Options */
        #define C_LOCALDEF__LCCM647__ENABLE_TEST_SPEC                       (0U)


        /** Enable datasheet values to test math
         * DO NOT put this in production */
        #define C_LOCALDEF__LCCM647__ENABLE_DS_VALUES                       (0U)

        /** Main include file */
        #include <MULTICORE/LCCM647__MULTICORE__TSYS01/tsys01.h>

    #endif //#if C_LOCALDEF__LCCM647__ENABLE_THIS_MODULE == 1U



	/*lint +e950*/
	


#endif /* LOCALDEF_H_ */

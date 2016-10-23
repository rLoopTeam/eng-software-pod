/**
 * @file		RM4_I2C__LOCALDEF.H
 * @brief		I2C localdef template
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2015, All Rights Reserved.
 * @st_fileID	LCCM215R0.FILE.003
 */

#if 0

/*******************************************************************************
RM4 I2C
*******************************************************************************/
	#define C_LOCALDEF__LCCM215__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM215__ENABLE_THIS_MODULE == 1U

		//The bus freq (100K, 400K, 1MHZ)
		#define C_LOCALDEF__LCCM215__BUS_FREQUENCY_HZ   					(100000U)

		#define C_LOCALDEF__LCCM215__OWN_ADDRESS                        	(0x50)

		/** Number of loops to wait for the timeout*/
		#define C_LOCALDEF__LCCM215__TIMEOUT_CYCLES   						(10000000U)

		#define C_LOCALDEF__LCCM215__USE_INTERRUPTS 						(0U)

		#if C_LOCALDEF__LCCM215__USE_INTERRUPTS == 1U

			#define C_LOCALDEF__LCCM215__ISR_ARBITRATION_LOST_ENABLE 		(1U)
			#define C_LOCALDEF__LCCM215__ISR_NACK_ENABLE					(1U)
			#define C_LOCALDEF__LCCM215__ISR_ACCESS_READY_ENABLE 			(1U)
			#define C_LOCALDEF__LCCM215__ISR_RECEIVE_ENABLE					(1U)
			#define C_LOCALDEF__LCCM215__ISR_TRANSMIT_ENABLE 				(1U)
			#define C_LOCALDEF__LCCM215__ISR_STOP_ENABLE					(1U)
			#define C_LOCALDEF__LCCM215__ISR_ADDRESS_AS_SLAVE_ENABLE 		(1U)

			//Callbacks to handle I2C interrupts
			#if C_LOCALDEF__LCCM215__ISR_ARBITRATION_LOST_ENABLE ==	(1U)
				#define C_LOCALDEF__LCCM215__ISR_ARBITRATION_LOST() 		vRM4_I2C_ISR__DefaultRoutine()
			#endif
			#if C_LOCALDEF__LCCM215__ISR_NACK_ENABLE ==	(1U)
				#define C_LOCALDEF__LCCM215__ISR_NACK() 					vRM4_I2C_ISR__DefaultRoutine()
			#endif
			#if C_LOCALDEF__LCCM215__ISR_ACCESS_READY_ENABLE ==	(1U)
				#define C_LOCALDEF__LCCM215__ISR_ACCESS_READY() 			vRM4_I2C_ISR__DefaultRoutine()
			#endif
			#if C_LOCALDEF__LCCM215__ISR_RECEIVE_ENABLE == 1U
				#define C_LOCALDEF__LCCM215__ISR_RECEIVE() 					vRM4_I2C_ISR__DefaultRoutine()
			#endif
			#if C_LOCALDEF__LCCM215__ISR_TRANSMIT_ENABLE ==	(1U)
				#define C_LOCALDEF__LCCM215__ISR_TRANSMIT() 				vRM4_I2C_ISR__DefaultRoutine()
			#endif
			#if C_LOCALDEF__LCCM215__ISR_STOP_ENABLE ==	(1U)
				#define C_LOCALDEF__LCCM215__ISR_STOP() 					vRM4_I2C_ISR__DefaultRoutine()
			#endif
			#if C_LOCALDEF__LCCM215__ISR_ADDRESS_AS_SLAVE_ENABLE ==	(1U)
				#define C_LOCALDEF__LCCM215__ISR_ADDRESS_AS_SLAVE() 		vRM4_I2C_ISR__DefaultRoutine()
			#endif
		#endif

		/** Testing Options */
		#define C_LOCALDEF__LCCM215__ENABLE_TEST_SPEC						(0U)
		
		
		//main include file
		#include <RM4/LCCM215__RM4__I2C/rm4_i2c.h>

	#endif //C_LOCALDEF__LCCM215__ENABLE_THIS_MODULE

#endif

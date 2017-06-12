/**
 * @file		RM4_ADC__LOCALDEF.H
 * @brief		Localdef Template
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM414R0.FILE.005
 */


#if 0

/*******************************************************************************
SIL3 - RM4 ADC DRIVER
*******************************************************************************/
	#define C_LOCALDEF__LCCM414__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM414__ENABLE_THIS_MODULE == 1U

		/** The number of ADC channels (modules) being used
		 * Keep a 1 for now
		 */
		#define C_LOCALDEF__LCCM414__NUM_ADC_MODULES						(1U)

		/** Continuous Conversion Mode:  When enabled the ADC
		 * Will always keep making samples of the configured channels
		 */
		#define C_LOCALDEF__LCCM414__ENABLE_CONTINUOUS_CONVERSION			(0U)

		/** Averaging is enabled across all channels.
		 * It can consume serious CPU time for a fully enabled ADC
		 */
		#define C_LOCALDEF__LCCM414__ENABLE_AVERAGING						(1U)

		/** The number of samples for each channels ADC averager */
		#define C_LOCALDEF__LCCM414__AVERAGE_MAX_SAMPLES					(4U)


		/** Determine which of ADC1 to enable */
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN0						(1U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN1						(1U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN2						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN3						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN4						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN5						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN6						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN7						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN8						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN9						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN10						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN11						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN12						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN13						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN14						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN15						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN16						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN17						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN18						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN19						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN20						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN21						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN22						(0U)
		#define C_LOCALDEF__LCCM414__ADC1__ENABLE_IN23						(0U)

		/** The number of connected devices to the ADC's
		 * We store a local copy of our ADC results in a user addressable
		 * structure to reduce the complexity of finding our result
		 * Value can be from 1 to 24
		 */
		#define C_LOCALDEF__LCCM414__NUM_CONNECTED_DEVICES					(3U)

		/** For each device we determine the location of the device within our strucrture
		 * You must configure an index from 0 to NUM_CONNECTED_DEVICES - 1
		 * No two units may have the same index
		 * Example MAP ADC1_IN0 to Device (1)
		 */
		#define C_LOCALDEF__LCCM414__ADC1_IN0__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN1__INDEX						(1U)
		#define C_LOCALDEF__LCCM414__ADC1_IN2__INDEX						(2U)
		#define C_LOCALDEF__LCCM414__ADC1_IN3__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN4__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN5__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN6__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN7__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN8__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN9__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN10__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN11__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN12__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN13__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN14__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN15__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN16__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN17__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN18__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN19__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN20__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN21__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN22__INDEX						(0U)
		#define C_LOCALDEF__LCCM414__ADC1_IN23__INDEX						(0U)

		/** Enable voltage conversion to return the voltage value
		 * for a device.  This reduces the external workload to compute the
		 * voltage based on VREF
		 */
		#define C_LOCALDEF__LCCM414__ENABLE_VOLTAGE_CALC					(1U)

		/** Use interrupts */
		#define C_LOCALDEF__LCCM414__ENABLE_INTERRUPTS						(0U)

		//testing
		#define C_LOCALDEF__LCCM414__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <RM4/LCCM414__RM4__ADC/rm4_adc.h>

	#endif //C_LOCALDEF__LCCM414__ENABLE_THIS_MODULE

#endif //0



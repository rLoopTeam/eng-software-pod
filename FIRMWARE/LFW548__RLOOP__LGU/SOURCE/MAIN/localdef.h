#ifndef LOCALDEF_H_
#define LOCALDEF_H_

	//The PCB's main files
	#ifndef WIN32
		#include <../../../BOARD_SUPPORT/lgu__board_support.h>
	#else
		#include <../BOARD_SUPPORT/lgu__board_support.h>
	#endif

/*******************************************************************************
MULTIPURPOSE DAQ MODULE
*******************************************************************************/
	#define C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE							(0U)
	#if C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE == 1U

		/** Number of DAQ channels in each data format
		* The channels are allocated on an index basis in descending order
		* with F32 being the last channel. If you change the number of channels
		* The indexing needs to change. Macros are avail for this.
		*/
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U8					(1U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S16					(1U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U16					(1U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S32					(1U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U32					(1U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__F32					(1U)

		/** Maximum length of DAQ data for each channel in 4 byte blocks
		* WARNING: Value must be divisible by 4 and will be aligned.*/
		#define C_LOCALDEF__LCCM662__MAX_DAQ_BUFFER_BLOCKS					(128U)

		/** The level at which a notification should occur on all buffers
		 * For buffers that are not 4 bytes, this value will be expanded.
		 *  */
		#define C_LOCALDEF__LCCM662__BUFFER_WATERMARK_LEVEL					(64U)

		/** enable double buffering of DAQ channels */
		#define C_LOCALDEF__LCCM662__ENABLE_DOUBLE_BUFFER					(0U)

		/** Enable user payload types, otherwise use the standard 0x1210+ for up
		 * to 128 streams. Typically this is 0
		 */
		#define C_LOCALDEF__LCCM662__ENABLE_USER_PAYLOAD_TYPES				(0U)

		/** Enable a snapshot of the core timer along with each channel of data
		* this chews NUM_CHANNELS * 4 worth of bytes and will have a slight performance
		* penalty */
		#define C_LOCALDEF__LCCM662__ENABLE_TIMER_IN_DATA					(0U)

		/** Transmission notification handler */
		#define M_LOCALDEF__LCCM662__TX_HANDLER(index, pbuffer, length)

		/** Testing Options */
		#define C_LOCALDEF__LCCM662__ENABLE_TEST_SPEC						(0U)

		/** Main include file */
		#include <MULTICORE/LCCM662__MULTICORE__DAQ/daq.h>
	#endif //#if C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE == 1U

/*******************************************************************************
RLOOP - LANDING GEAR UNIT
*******************************************************************************/
	#define C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U

		/** Clutch control*/
		#define C_LOCALDEF__LCCM667__LGU_ENABLE_CLUTCHES					(0U)

		/** Motor Cooling*/
		#define C_LOCALDEF__LCCM667__LGU_ENABLE_COOLING						(0U)

		/** Gimbal Subsystem*/
		#define C_LOCALDEF__LCCM667__LGU_ENABLE_GIMBALS						(0U)

		/** Lift Mechanisms*/
		#define C_LOCALDEF__LCCM667__LGU_ENABLE_LIFT						(0U)

		/** PV Pressure Control System*/
		#define C_LOCALDEF__LCCM667__LGU_ENABLE_PVPRESS						(0U)

		/** FCU Serial Link*/
		#define C_LOCALDEF__LCCM667__LGU_SERIAL								(0U)

		/** Testing Options */
		#define C_LOCALDEF__LCCM667__ENABLE_TEST_SPEC						(0U)

		/** Main include file */
		#include <LCCM667__RLOOP__LGU/lgu.h>
	#endif //#if C_LOCALDEF__LCCM667__ENABLE_THIS_MODULE == 1U


#endif /* LOCALDEF_H_ */

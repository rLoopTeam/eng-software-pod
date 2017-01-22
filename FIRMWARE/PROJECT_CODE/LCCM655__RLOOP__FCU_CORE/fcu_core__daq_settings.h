//defines for setting of the DAQ

#ifndef FCU_CORE__DAQ_SETTINGS_H_
#define FCU_CORE__DAQ_SETTINGS_H_


	/* Because DAQ has to be built into our application because I'm lazy and didn't implement
	 * a memory pool.
	 *
	 * Select below the DAQ enable.
	 */


	/** Accelerometer DAQ */
	#define C_FCU_DAQ_SET__ENABLE__DAQ_FOR_ACCELS							(0U)
	#if C_FCU_DAQ_SET__ENABLE__DAQ_FOR_ACCELS == 1U

		//define here the actual DAQ channel indexes
		#define C_FCU_DAQ_SET__DAQ_FOR_ACCELS__CPU_LOAD_U8					(0U)
		#define C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A0X_S16						(1U)
		#define C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A0Y_S16						(2U)
		#define C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A0Z_S16						(3U)
		#define C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A1X_S16						(4U)
		#define C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A1Y_S16						(5U)
		#define C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A1Z_S16						(6U)

		//computed values
		#define C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A0_ACCEL_S32					(7U)
		#define C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A0_VELOC_S32					(8U)
		#define C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A0_DISP_S32					(9U)
		#define C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A1_ACCEL_S32					(10U)
		#define C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A1_VELOC_S32					(11U)
		#define C_FCU_DAQ_SET__DAQ_FOR_ACCELS__A1_DISP_S32					(12U)

		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U8					(1U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S16					(6U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U16					(0U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S32					(6U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U32					(0U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__F32					(0U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U64					(0U)

	#endif //#if C_FCU_DAQ_SET__ENABLE__DAQ_FOR_ACCELS == 1U



	#define C_FCU_DAQ_SET__ENABLE__DAQ_FOR_BRAKES							(1U)
	#if C_FCU_DAQ_SET__ENABLE__DAQ_FOR_BRAKES == 1U

		//configured DAQ channels
		#define C_FCU_DAQ_SET__DAQ_FOR_BRAKES__CPU_LOAD_U8					(0U)

		#define C_FCU_DAQ_SET__DAQ_FOR_BRAKES__LEFT_CURRENTPOS_S32			(1U)
		#define C_FCU_DAQ_SET__DAQ_FOR_BRAKES__RIGHT_CURRENTPOS_S32			(2U)

		#define C_FCU_DAQ_SET__DAQ_FOR_BRAKES__LEFT_TARGET_U32				(3U)
		#define C_FCU_DAQ_SET__DAQ_FOR_BRAKES__RIGHT_TARGET_U32				(4U)

		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U8					(1U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S16					(0U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U16					(0U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S32					(2U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U32					(2U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__F32					(0U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U64					(0U)

	#endif //C_FCU_DAQ_SET__ENABLE__DAQ_FOR_BRAKES

	/** Contrast Sensor Testing DAQ*/
	#define C_FCU_DAQ_SET__ENABLE__DAQ_FOR_LASER_CONTRAST						(0U)
	#if C_FCU_DAQ_SET__ENABLE__DAQ_FOR_LASER_CONTRAST == 1U

		//define here the actual DAQ channel indexes
		#define C_FCU_DAQ_SET__DAQ_FOR_CONTRAST__CPU_LOAD_U8					(0U)

		//count of rising edges
		#define C_FCU_DAQ_SET__DAQ_FOR_CONTRAST__L0_RISING_EDGE_COUNT_U16		(1U)

		//distance between the last stripe
		#define C_FCU_DAQ_SET__DAQ_FOR_CONTRAST__L0_CURRENT_ACCEL_S32			(2U)

		//total distance that has elapsed in this run
		#define C_FCU_DAQ_SET__DAQ_FOR_CONTRAST__L0_DISTANCE_ELAPSED_U32		(3U)

		//current instant velocity based on previous stripe
		#define C_FCU_DAQ_SET__DAQ_FOR_CONTRAST__L0_CURRENT_VELOCITY_U32		(4U)



		//Setup the channels
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U8					(1U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S16					(0U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U16					(1U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S32					(1U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U32					(2U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__F32					(0U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U64					(0U)

	#endif


	#define C_FCU_DAQ_SET__ENABLE__DAQ_FOR_LASER_DISTANCE			(0U)

	#define C_FCU_DAQ_SET__ENABLE__DAQ_FOR_LASER_OPTOS				(0U)

	/** The actual flight DAQ */
	#define C_FCU_DAQ_SET__ENABLE__DAQ_FOR_FLIGHT					(0U)



/*******************************************************************************
MULTIPURPOSE DAQ MODULE
*******************************************************************************/
	#define C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE == 1U

		/** Number of DAQ channels in each data format
		* The channels are allocated on an index basis in descending order
		* with F32 being the last channel. If you change the number of channels
		* The indexing needs to change. Macros are avail for this.
		*/
/*
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U8					(1U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S16					(1U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U16					(1U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__S32					(1U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U32					(1U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__F32					(1U)
		#define C_LOCALDEF__LCCM662__NUM_DAQ_CHANNELS__U64					(0U)
*/
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
		#define M_LOCALDEF__LCCM662__TX_HANDLER(index, pbuffer, length)		s16DAQ_TRANSMIT__Template(index, pbuffer, length)

		/** Testing Options */
		#define C_LOCALDEF__LCCM662__ENABLE_TEST_SPEC						(0U)

		/** Main include file */
		#include <MULTICORE/LCCM662__MULTICORE__DAQ/daq.h>
	#endif //#if C_LOCALDEF__LCCM662__ENABLE_THIS_MODULE == 1U


#endif /* FCU_CORE__DAQ_SETTINGS_H_ */

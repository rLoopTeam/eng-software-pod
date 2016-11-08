/**
 * @file		RM4_ADC__PRIVATE.H
 * @brief		Private types
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM414R0.FILE.006
 */
#ifndef __RM4_ADC_PRIVATE_H__
#define __RM4_ADC_PRIVATE_H__

	/** The ADC Index Number */
	typedef enum
	{
		RM4_ADC__1 = 0U,
		RM4_ADC__2 = 1U,

	}RM4_ADC__INDEX_T;

	/** The groups associated with the ADC */
	typedef enum
	{
		/** Event group can only be triggered by hardware */
		ADC_GROUP__EVENT = 0U,

		/** Group 1 can be triggered by HW or SW */
		ADC_GROUP__GROUP_1 = 1U,

		/** Group 2 can be triggered by HW or SW */
		ADC_GROUP__GROUP_2 = 2U


	}RM4_ADC__GROUPS_T;


	typedef enum
	{

		CONVERSION_MODE__SINGLE = 0U,
		CONVERSION_MODE__CONTINUOUS = 1U

	}RM4_ADC__CONVERT_MODE_E;

	/** The ADC Precision
	 * 10 bit or 12 bit or 8 bit.
	 * In addition to to these enums being used to configure the ADC channel, they are also
	 * used in code as bit test and to set various registers, so don't change their values.
	 */
	typedef enum
	{
		/** Configure for 12 bit mode */
		ADC_PRECISION__12BIT = 0x00000000U,

		/** Configure for 10 bit mode */
		ADC_PRECISION__10BIT = 0x00000100U,

		/** Configure for 8 bit mode */
		ADC_PRECISION__8BIT = 0x00000200U


	}RM4_ADC__PRECISION_T;


	/** @enum adc1HwTriggerSource
		* @brief Alias names for hardware trigger source
		* This enumeration is used to provide alias names for the hardware trigger sources:
		*/

		typedef enum
		{
			ADC1_HWTRIG__EVENT_PIN = 0U,	 /**< Alias for event pin			 */
			ADC1_HET1_8 = 1U,	 /**< Alias for HET1 pin 8			*/
			ADC1_HET1_10 = 2U,	 /**< Alias for HET1 pin 10		 */
			ADC1_RTI_COMP0 = 3U, /**< Alias for RTI compare 0 match */
			ADC1_HET1_12 = 4U,	 /**< Alias for HET1 pin 12		 */
			ADC1_HET1_14 = 5U,	 /**< Alias for HET1 pin 14		 */
			ADC1_GIOB0 = 6U,	 /**< Alias for GIO port b pin 0	 */
			ADC1_GIOB1 = 7U,	 /**< Alias for GIO port b pin 1	 */

			ADC1_HET2_5 = 1U,	 /**< Alias for HET2 pin 5			*/
			ADC1_HET1_27 = 2U,	 /**< Alias for HET1 pin 27		 */
			ADC1_HET1_17 = 4U,	 /**< Alias for HET1 pin 17		 */
			ADC1_HET1_19 = 5U,	 /**< Alias for HET1 pin 19		 */
			ADC1_HET1_11 = 6U,	 /**< Alias for HET1 pin 11		 */
			ADC1_HET2_13 = 7U,	 /**< Alias for HET2 pin 13		 */

			ADC1_EPWM_B = 1U,	 /**< Alias for B Signal EPWM		 */
			ADC1_EPWM_A1 = 3U,	 /**< Alias for A1 Signal EPWM		*/
			ADC1_HET2_1 = 5U,	 /**< Alias for HET2 pin 1			*/
			ADC1_EPWM_A2 = 6U,	 /**< Alias for A2 Signal EPWM		*/
			ADC1_EPWM_AB = 7U	 /**< Alias for AB Signal EPWM		*/

		}RM4_ADC1__HW_TRIG_SOURCE__T;


	/** @struct adcData
	* @brief ADC Conversion data structure
	*
	* This type is used to pass adc conversion data.
	*/
	/** @typedef RM4_ADC__DATA_T
	* @brief ADC Data Type Definition
	*/
	typedef struct adcData
	{
		/** Channel or PIN ID */
		Luint32 u32ID;

		/** Converted data value */
		Luint16 u16Value;
	} RM4_ADC__DATA_T;

	/** The ADC structure Type */
	typedef struct
	{

		/** Each of the ADC Channels */
		struct
		{

			/** Is the conversion complete for this channel */
			Luint8 u8ConversionInProgress;

			/** Has new data been acquired and put into the structure */
			Luint8 u8NewDataAcquired;

			/** The actual ADC data being read from the device registers */
			RM4_ADC__DATA_T sADC_Data[24];

			/** Our simplified structure for each device (ADC port) of data
			 * We add +1 to the size of the structure as index 0 is the dump for
			 * all not-enabled channels.
			 */
			struct
			{
				/** The current RAW collected value */
				Luint16 u16RAWValue;


				#if C_LOCALDEF__LCCM414__ENABLE_AVERAGING == 1U

					/** The current sample position counter */
					Luint16 u16AverageCounter;

					/** The collected samples */
					Luint16 u16Samples[C_LOCALDEF__LCCM414__AVERAGE_MAX_SAMPLES];

					/** The average result */
					Luint16 u16AverageValue;

				#endif


				/** The number of samples taken */
				Luint8 u8NumberOfSamples;

				Luint32 u32AccumulatedValue;

				#if C_LOCALDEF__LCCM414__ENABLE_VOLTAGE_CALC == 1U
					Lfloat32 f32Voltage;
				#endif


			}sDevice[C_LOCALDEF__LCCM414__NUM_CONNECTED_DEVICES + 1];

		}sChannel[C_LOCALDEF__LCCM414__NUM_ADC_MODULES];

	}RM4_ADC_T;


/*Adc Register Frame Definition */
/** @struct adcBase
* @brief ADC Register Frame Definition
*
* This type is used to access the ADC Registers.
*/
/** @typedef RM4_ADC__BASE_T
* @brief ADC Register Frame Type Definition
*
* This type is used to access the ADC Registers.
*/
	typedef volatile struct adcBase
	{
		/**< 0x0000: Reset control register							*/
		Luint32 RSTCR;
		/**< 0x0004: Operating mode control register				 */
		Luint32 OPMODECR;
		Luint32 CLOCKCR;			/**< 0x0008: Clock control register							*/
		Luint32 CALCR;			 /**< 0x000C: Calibration control register					 */
		Luint32 GxMODECR[3U];	 /**< 0x0010,0x0014,0x0018: Group 0-2 mode control register	 */
		Luint32 EVSRC;			 /**< 0x001C: Group 0 trigger source control register		 */
		Luint32 G1SRC;			 /**< 0x0020: Group 1 trigger source control register		 */
		Luint32 G2SRC;			 /**< 0x0024: Group 2 trigger source control register		 */
		Luint32 GxINTENA[3U];	 /**< 0x0028,0x002C,0x0030: Group 0-2 interrupt enable register */
		Luint32 GxINTFLG[3U];	 /**< 0x0034,0x0038,0x003C: Group 0-2 interrupt flag register */
		Luint32 GxINTCR[3U];		/**< 0x0040-0x0048: Group 0-2 interrupt threshold register	 */
		Luint32 EVDMACR;			/**< 0x004C: Group 0 DMA control register					 */
		Luint32 G1DMACR;			/**< 0x0050: Group 1 DMA control register					 */
		Luint32 G2DMACR;			/**< 0x0054: Group 2 DMA control register					 */
		Luint32 BNDCR;			 /**< 0x0058: Buffer boundary control register				 */
		Luint32 BNDEND;			 /**< 0x005C: Buffer boundary end register					 */
		Luint32 EVSAMP;			 /**< 0x0060: Group 0 sample window register					*/
		Luint32 G1SAMP;			 /**< 0x0064: Group 1 sample window register					*/
		Luint32 G2SAMP;			 /**< 0x0068: Group 2 sample window register					*/
		Luint32 EVSR;			 /**< 0x006C: Group 0 status register						 */
		Luint32 G1SR;			 /**< 0x0070: Group 1 status register						 */
		Luint32 G2SR;			 /**< 0x0074: Group 2 status register						 */
		Luint32 GxSEL[3U];		 /**< 0x0078-0x007C: Group 0-2 channel select register		 */
		Luint32 CALR;			 /**< 0x0084: Calibration register							 */
		Luint32 SMSTATE;			/**< 0x0088: State machine state register					 */
		Luint32 LASTCONV;		 /**< 0x008C: Last conversion register						 */
		struct
		{
			Luint32 BUF0;		 /**< 0x0090,0x00B0,0x00D0: Group 0-2 result buffer 1 register */
			Luint32 BUF1;		 /**< 0x0094,0x00B4,0x00D4: Group 0-2 result buffer 1 register */
			Luint32 BUF2;		 /**< 0x0098,0x00B8,0x00D8: Group 0-2 result buffer 2 register */
			Luint32 BUF3;		 /**< 0x009C,0x00BC,0x00DC: Group 0-2 result buffer 3 register */
			Luint32 BUF4;		 /**< 0x00A0,0x00C0,0x00E0: Group 0-2 result buffer 4 register */
			Luint32 BUF5;		 /**< 0x00A4,0x00C4,0x00E4: Group 0-2 result buffer 5 register */
			Luint32 BUF6;		 /**< 0x00A8,0x00C8,0x00E8: Group 0-2 result buffer 6 register */
			Luint32 BUF7;		 /**< 0x00AC,0x00CC,0x00EC: Group 0-2 result buffer 7 register */
		} GxBUF[3U];
		Luint32 EVEMUBUFFER;		/**< 0x00F0: Group 0 emulation result buffer				 */
		Luint32 G1EMUBUFFER;		/**< 0x00F4: Group 1 emulation result buffer				 */
		Luint32 G2EMUBUFFER;		/**< 0x00F8: Group 2 emulation result buffer				 */
		Luint32 EVTDIR;			 /**< 0x00FC: Event pin direction register					 */
		Luint32 EVTOUT;			 /**< 0x0100: Event pin digital output register				 */
		Luint32 EVTIN;			 /**< 0x0104: Event pin digital input register				 */
		Luint32 EVTSET;			 /**< 0x0108: Event pin set register							*/
		Luint32 EVTCLR;			 /**< 0x010C: Event pin clear register						 */
		Luint32 EVTPDR;			 /**< 0x0110: Event pin open drain register					 */
		Luint32 EVTDIS;			 /**< 0x0114: Event pin pull disable register				 */
		Luint32 EVTPSEL;			/**< 0x0118: Event pin pull select register					*/
		Luint32 EVSAMPDISEN;		/**< 0x011C: Group 0 sample discharge register				 */
		Luint32 G1SAMPDISEN;		/**< 0x0120: Group 1 sample discharge register				 */
		Luint32 G2SAMPDISEN;		/**< 0x0124: Group 2 sample discharge register				 */
		Luint32 MAGINTCR1;		 /**< 0x0128: Magnitude interrupt control register 1			*/
		Luint32 MAGINT1MASK;		/**< 0x012C: Magnitude interrupt mask register 1			 */
		Luint32 MAGINTCR2;		 /**< 0x0130: Magnitude interrupt control register 2			*/
		Luint32 MAGINT2MASK;		/**< 0x0134: Magnitude interrupt mask register 2			 */
		Luint32 MAGINTCR3;		 /**< 0x0138: Magnitude interrupt control register 3			*/
		Luint32 MAGINT3MASK;		/**< 0x013C: Magnitude interrupt mask register 3			 */
		Luint32 rsvd1;			/**< 0x0140: Reserved										 */
		Luint32 rsvd2;			/**< 0x0144: Reserved										 */
		Luint32 rsvd3;			/**< 0x0148: Reserved										 */
		Luint32 rsvd4;			/**< 0x014C: Reserved										 */
		Luint32 rsvd5;			/**< 0x0150: Reserved										 */
		Luint32 rsvd6;			/**< 0x0154: Reserved										 */
		Luint32 MAGTHRINTENASET;	/**< 0x0158: Magnitude interrupt set register				 */
		Luint32 MAGTHRINTENACLR;	/**< 0x015C: Magnitude interrupt clear register				*/
		Luint32 MAGTHRINTFLG;	 /**< 0x0160: Magnitude interrupt flag register				 */
		Luint32 MAGTHRINTOFFSET;	/**< 0x0164: Magnitude interrupt offset register			 */
		Luint32 GxFIFORESETCR[3U]; /**< 0x0168,0x016C,0x0170: Group 0-2 fifo reset register	 */
		Luint32 EVRAMADDR;		 /**< 0x0174: Group 0 RAM pointer register					 */
		Luint32 G1RAMADDR;		 /**< 0x0178: Group 1 RAM pointer register					 */
		Luint32 G2RAMADDR;		 /**< 0x017C: Group 2 RAM pointer register					 */
		Luint32 PARCR;			 /**< 0x0180: Parity control register						 */
		Luint32 PARADDR;			/**< 0x0184: Parity error address register					 */
		Luint32 PWRUPDLYCTRL;	 /**< 0x0188: Power-Up delay control register				 */

	} RM4_ADC__BASE_T;





/*
	typedef enum
	{
		RX_SM_IDLE = 0U,
		RX_SM_WAITING_DATA = 1U,
		RX_SM_WAITING_DATA_IS_USED = 2U

	}RM4_ARRAY_RX_STATE_MACHINE_STATES_T;
*/






	/** @def adcREG1
	* @brief ADC1 Register Frame Pointer
	*
	* This pointer is used by the ADC driver to access the ADC1 registers.
	*/
	#define adcREG1 ((RM4_ADC__BASE_T *)0xFFF7C000U)

	/** @def adcREG2
	* @brief ADC2 Register Frame Pointer
	*
	* This pointer is used by the ADC driver to access the ADC2 registers.
	*/
	#define adcREG2 ((RM4_ADC__BASE_T *)0xFFF7C200U)

	/** @def adcRAM1
	* @brief ADC1 RAM Pointer
	*
	* This pointer is used by the ADC driver to access the ADC1 RAM.
	*/
	#define adcRAM1 (*(volatile Luint32 *)0xFF3E0000U)

	/** @def adcRAM2
	* @brief ADC2 RAM Pointer
	*
	* This pointer is used by the ADC driver to access the ADC2 RAM.
	*/
	#define adcRAM2 (*(volatile Luint32 *)0xFF3A0000U)

	/** @def adcPARRAM1
	* @brief ADC1 Parity RAM Pointer
	*
	* This pointer is used by the ADC driver to access the ADC1 Parity RAM.
	*/
	#define adcPARRAM1 (*(volatile Luint32 *)(0xFF3E0000U + 0x1000U))

	/** @def adcPARRAM2
	* @brief ADC2 Parity RAM Pointer
	*
	* This pointer is used by the ADC driver to access the ADC2 Parity RAM.
	*/
	#define adcPARRAM2 (*(volatile Luint32 *)(0xFF3A0000U + 0x1000U))


	//safetys
	#ifndef C_LOCALDEF__LCCM414__NUM_ADC_MODULES
		#error
	#endif
	#ifndef C_LOCALDEF__LCCM414__ENABLE_AVERAGING
		#error
	#endif

#endif //__RM4_ADC_PRIVATE_H__

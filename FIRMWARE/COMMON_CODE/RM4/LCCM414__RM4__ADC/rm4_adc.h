/**
 * @file		RM4_ADC.H
 * @brief		Main Header
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM414R0.FILE.004
 */
#ifndef RM4_ADC_H_
#define RM4_ADC_H_

	#include <localdef.h>
	#if C_LOCALDEF__LCCM414__ENABLE_THIS_MODULE == 1U

		#include <RM4/LCCM414__RM4__ADC/rm4_adc__private.h>

		//3.3/(2^12)
		#define C_RM4ADC__VREF_CONSTANT		0.0008056640625F


	/*ADC General Definitions */

	/** @def adcGROUP0
	* @brief Alias name for ADC event u32Group
	*
	* @note This value should be used for API argument @a u32Group
	*/
//	#define adcGROUP0 0U

	/** @def adcGROUP1
	* @brief Alias name for ADC u32Group 1
	*
	* @note This value should be used for API argument @a u32Group
	*/
//	#define adcGROUP1 1U

	/** @def adcGROUP2
	* @brief Alias name for ADC u32Group 2
	*
	* @note This value should be used for API argument @a u32Group
	*/
//	#define adcGROUP2 2U

	/** @def ADC_12_BIT_MODE
	* @brief Alias name for ADC 12-bit mode of operation
	*/
	#define ADC_12_BIT_MODE 0x80000000U


	/** @enum adcFiFoStatus
	* @brief Alias names for FiFo status
	* This enumeration is used to provide alias names for the current FiFo states:
	*	 - FiFo is not full
	*	 - FiFo is full
	*	 - FiFo overflow occurred
	*/

	enum adcFiFoStatus
	{
		ADC_FIFO_IS_NOT_FULL = 0U, /**< Alias for FiFo is not full	 */
		ADC_FIFO_IS_FULL	 = 1U, /**< Alias for FiFo is full		 */
		ADC_FIFO_OVERFLOW	= 3U /**< Alias for FiFo overflow occurred */
	};

	/** @enum adcConversionStatus
	* @brief Alias names for conversion status
	* This enumeration is used to provide alias names for the current conversion states:
	*	 - Conversion is not finished
	*	 - Conversion is finished
	*/

	enum adcConversionStatus
	{
		ADC_CONVERSION_IS_NOT_FINISHED = 0U, /**< Alias for current conversion is not finished */
		ADC_CONVERSION_IS_FINISHED	 = 8U /**< Alias for current conversion is finished	*/
	};



	/** @enum adc2HwTriggerSource
	* @brief Alias names for hardware trigger source
	* This enumeration is used to provide alias names for the hardware trigger sources:
	*/

	enum adc2HwTriggerSource
	{
		ADC2_EVENT = 0U,	 /**< Alias for event pin			 */
		ADC2_HET1_8 = 1U,	 /**< Alias for HET1 pin 8			*/
		ADC2_HET1_10 = 2U,	 /**< Alias for HET1 pin 10		 */
		ADC2_RTI_COMP0 = 3U, /**< Alias for RTI compare 0 match */
		ADC2_HET1_12 = 4U,	 /**< Alias for HET1 pin 12		 */
		ADC2_HET1_14 = 5U,	 /**< Alias for HET1 pin 14		 */
		ADC2_GIOB0 = 6U,	 /**< Alias for GIO port b pin 0	 */
		ADC2_GIOB1 = 7U,	 /**< Alias for GIO port b pin 1	 */
		ADC2_HET2_5 = 1U,	 /**< Alias for HET2 pin 5			*/
		ADC2_HET1_27 = 2U,	 /**< Alias for HET1 pin 27		 */
		ADC2_HET1_17 = 4U,	 /**< Alias for HET1 pin 17		 */
		ADC2_HET1_19 = 5U,	 /**< Alias for HET1 pin 19		 */
		ADC2_HET1_11 = 6U,	 /**< Alias for HET1 pin 11		 */
		ADC2_HET2_13 = 7U,	 /**< Alias for HET2 pin 13		 */

		ADC2_EPWM_B = 1U,	 /**< Alias for B Signal EPWM		 */
		ADC2_EPWM_A1 = 3U,	 /**< Alias for A1 Signal EPWM		*/
		ADC2_HET2_1 = 5U,	 /**< Alias for HET2 pin 1			*/
		ADC2_EPWM_A2 = 6U,	 /**< Alias for A2 Signal EPWM		*/
		ADC2_EPWM_AB = 7U	 /**< Alias for AB Signal EPWM		*/

	};

	/*USER CODE BEGIN (1) */
	/*USER CODE END */



	void vRM4_ADC_USER__Init(void);
	void vRM4_ADC_USER__StartConversion(void);
	void vRM4_ADC_USER__Process(void);
	Luint16 u16RM4_ADC_USER__Get_RawData(Luint8 u8DeviceIndex);
	Luint16 u16RM4_ADC_USER__Get_AveragedData(Luint8 u8DeviceIndex);
	Lfloat32 f32RM4_ADC_USER__Get_Voltage(Luint8 u8DeviceIndex);
	Luint8 u8RM4_ADC_USER__Is_ConversionInProgress(void);
	Luint8 u8RM4_ADC_USER__Is_NewDataAvailable(void);
	void vRM4_ADC_USER__Clear_NewDataAvailable(void);

	void vRM4_ADC__Enable_GroupPin(RM4_ADC__INDEX_T eADC, RM4_ADC__GROUPS_T eGroup, Luint32 u32PinIndex);
	void vRM4_ADC__Disable_GroupPin(RM4_ADC__INDEX_T eADC, RM4_ADC__GROUPS_T eGroup, Luint32 u32PinIndex);
	void vRM4_ADC__Clear_GroupPins(RM4_ADC__INDEX_T eADC, RM4_ADC__GROUPS_T eGroup);
	void vRM4_ADC__Set_ConversionMode(RM4_ADC__INDEX_T eADC, RM4_ADC__GROUPS_T eGroup, RM4_ADC__CONVERT_MODE_E eMode);
	void vRM4_ADC__ChannelID_InResult(RM4_ADC__INDEX_T eADC, RM4_ADC__GROUPS_T eGroup, Luint8 u8Enable);

	//inits
	void vRM4_ADC_INIT__Group_1(RM4_ADC__INDEX_T eADC, RM4_ADC__PRECISION_T ePrecision);
	void vRM4_ADC_INIT__Group_2(RM4_ADC__INDEX_T eADC);
	void vRM4_ADC_INIT__Event_Group(RM4_ADC__INDEX_T eADC);
	void vRM4_ADC_INIT__Event_Trigger(RM4_ADC__INDEX_T eADC);

	void vRM4_ADC_INIT__Init(RM4_ADC__INDEX_T eADC, RM4_ADC__PRECISION_T ePrecision);

	void vRM4_ADC_LOWLEVEL__StartConversion(RM4_ADC__BASE_T *adc, RM4_ADC__GROUPS_T eGroup);
	void vRM4_ADC_LOWLEVEL__StopConversion(RM4_ADC__BASE_T *adc, RM4_ADC__GROUPS_T eGroup);
	void vRM4_ADC_LOWLEVEL__Reset_FIFO(RM4_ADC__BASE_T *adc, RM4_ADC__GROUPS_T eGroup);
	Luint32 u32RM4_ADC_LOWLEVEL__GetData(RM4_ADC__BASE_T *adc, RM4_ADC__GROUPS_T eGroup, RM4_ADC__DATA_T *data);
	Luint32 u32RM4_ADC_LOWLEVEL__Is_FIFOFull(RM4_ADC__BASE_T *adc, RM4_ADC__GROUPS_T eGroup);
	Luint8 u8RM4_ADC_LOWLEVEL__Is_ConversionComplete(RM4_ADC__BASE_T *adc, RM4_ADC__GROUPS_T eGroup);
	void vRM4_ADC_LOWLEVEL__Calibration(RM4_ADC__BASE_T *adc);
	Luint32 u32RM4_ADC_LOWLEVEL__MidPointCalibration(RM4_ADC__BASE_T *adc);
	void vRM4_ADC_LOWLEVEL__Set_EVTPin(RM4_ADC__BASE_T *adc, Luint32 value);
	Luint32 vRM4_ADC_LOWLEVEL__Get_EVTPin(RM4_ADC__BASE_T *adc);



	//interrupts
	void vRM4_ADC_LOWLEVEL__Enable_Notification(RM4_ADC__INDEX_T eADC, RM4_ADC__GROUPS_T eGroup);
	void vRM4_ADC_LOWLEVEL__Disable_Notification(RM4_ADC__INDEX_T eADC, RM4_ADC__GROUPS_T eGroup);
	void vRM4_ADC_INT__UserNotification(RM4_ADC__INDEX_T eADC, RM4_ADC__GROUPS_T eGroup);
	void vRM4_ADC1_INT__Group0_ISR(void);
	void vRM4_ADC1_INT__Group1_ISR(void);
	void vRM4_ADC1_INT__Group2_ISR(void);
	void vRM4_ADC2_INT__Group0_ISR(void);
	void vRM4_ADC2_INT__Group1_ISR(void);
	void vRM4_ADC2_INT__Group2_ISR(void);

	//DMA
	void vRM4_ADC_DMA__Setup_Interleave(RM4_ADC__INDEX_T eADC, RM4_ADC__GROUPS_T eGroup, Luint32 u32ArrayDestAddx, Luint32 u32ArraySize, Luint32 u32NumChannels);

#endif

#endif /*RM4_ADC_H_ */

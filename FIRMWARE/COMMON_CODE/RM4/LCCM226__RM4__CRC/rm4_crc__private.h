/**
 * @file		RM4_CRC__PRIVATE.H
 * @brief		Private types for RM4 CRC module
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM226R0.FILE.004
 */

#ifndef _RM4_CRC_PRIVATE_H_
#define _RM4_CRC_PRIVATE_H_
#ifndef WIN32
	/* Crc Register Frame Definition */
	/** @struct crcBase
	*   @brief CRC Register Frame Definition
	*
	*   This type is used to access the CRC Registers.
	*/
	/** @typedef RM4_CRC__BASET_T
	*   @brief CRC Register Frame Type Definition
	*
	*   This type is used to access the CRC Registers.
	*/
	/*****************************************************************************
	*****************************************************************************/
	typedef volatile struct crcBase
	{
		Luint32      CTRL0;                /**< 0x0000: Global Control Register 0 >**/
		Luint32      rvd1;                 /**< 0x0004: reserved >**/
		Luint32      CTRL1;                /**< 0x0008: Global Control Register 1 >**/
		Luint32      rvd2;                 /**< 0x000C: reserved >**/
		Luint32      CTRL2;                /**< 0x0010: Global Control Register 2 >**/
		Luint32      rvd3;                 /**< 0x0014: reserved >**/
		Luint32      INTS;                 /**< 0x0018: Interrupt Enable Set Register >**/
		Luint32      rvd4;                 /**< 0x001C: reserved >**/
		Luint32      INTR;                 /**< 0x0020: Interrupt Enable Reset Register >**/
		Luint32      rvd5;                 /**< 0x0024: reserved >**/
		Luint32      STATUS;               /**< 0x0028: Interrupt Status Register >**/
		Luint32      rvd6;                 /**< 0x002C: reserved >**/
		Luint32      INT_OFFSET_REG;       /**< 0x0030: Interrupt Offset >**/
		Luint32      rvd7;                 /**< 0x0034: reserved >**/
		Luint32      BUSY;                 /**< 0x0038: CRC Busy Register >**/
		Luint32      rvd8;                 /**< 0x003C: reserved >**/
		Luint32      PCOUNT_REG1;          /**< 0x0040: Pattern Counter Preload Register1 >**/
		Luint32      SCOUNT_REG1;          /**< 0x0044: Sector Counter Preload Register1 >**/
		Luint32      CURSEC_REG1;          /**< 0x0048: Current Sector Register 1 >**/
		Luint32      WDTOPLD1;             /**< 0x004C: Channel 1 Watchdog Timeout Preload Register A >**/
		Luint32      BCTOPLD1;             /**< 0x0050: Channel 1 Block Complete Timeout Preload Register B >**/
		Luint32      rvd9[3];              /**< 0x0054: reserved >**/
		Luint32      PSA_SIGREGL1;         /**< 0x0060: Channel 1 PSA signature low register >**/
		Luint32      PSA_SIGREGH1;         /**< 0x0064: Channel 1 PSA signature high register >**/
		Luint32      REGL1;                /**< 0x0068: Channel 1 CRC value low register >**/
		Luint32      REGH1;                /**< 0x006C: Channel 1 CRC value high register >**/
		Luint32      PSA_SECSIGREGL1;      /**< 0x0070: Channel 1 PSA sector signature low register >**/
		Luint32      PSA_SECSIGREGH1;      /**< 0x0074: Channel 1 PSA sector signature high register >**/
		Luint32      RAW_DATAREGL1;        /**< 0x0078: Channel 1 Raw Data Low Register >**/
		Luint32      RAW_DATAREGH1;        /**< 0x007C: Channel 1 Raw Data High Register >**/
		Luint32      PCOUNT_REG2;          /**< 0x0080: CRC Pattern Counter Preload Register2 >**/
		Luint32      SCOUNT_REG2;          /**< 0x0084: Sector Counter Preload Register2 >**/
		Luint32      CURSEC_REG2;          /**< 0x0088: Current Sector Register 2>**/
		Luint32      WDTOPLD2;             /**< 0x008C: Channel 2 Watchdog Timeout Preload Register A >**/
		Luint32      BCTOPLD2;             /**< 0x0090: Channel 2 Block Complete Timeout Preload Register B >**/
		Luint32      rvd10[3];             /**< 0x0094: reserved >**/
		Luint32      PSA_SIGREGL2;         /**< 0x00A0: Channel 2 PSA signature low register >**/
		Luint32      PSA_SIGREGH2;         /**< 0x00A4: Channel 2 PSA signature high register >**/
		Luint32      REGL2;                /**< 0x00A8: Channel 2 CRC value low register >**/
		Luint32      REGH2;                /**< 0x00AC: Channel 2 CRC value high register >**/
		Luint32      PSA_SECSIGREGL2;      /**< 0x00B0: Channel 2 PSA sector signature low register >**/
		Luint32      PSA_SECSIGREGH2;      /**< 0x00B4: Channel 2 PSA sector signature high register >**/
		Luint32      RAW_DATAREGL2;        /**< 0x00B8: Channel 2 Raw Data Low Register >**/
		Luint32      RAW_DATAREGH2;        /**< 0x00BC: Channel 2 Raw Data High Register >**/
	}RM4_CRC__BASET_T;

	/** @def crcREG
	*   @brief CRC Register Frame Pointer
	*
	*   This pointer is used by the CRC driver to access the CRC registers.
	*/
	#define crcREG ((RM4_CRC__BASET_T *)0xFE000000U)



	/* CRC General Definitions */

	/** @def CRCLEVEL_ACTIVE
	*   @brief Alias name for CRC error operation level active
	*/
	#define CRCLEVEL_ACTIVE 0x00U


	/** @def CRC_AUTO
	*   @brief Alias name for CRC auto mode
	*/
	#define CRC_AUTO 0x00000001U


	/** @def CRC_SEMI_CPU
	*   @brief Alias name for semi cpu mode setting
	*/
	#define CRC_SEMI_CPU 0x00000002U


	/** @def CRC_FULL_CPU
	*   @brief Alias name for CRC cpu full mode
	*/
	#define CRC_FULL_CPU 0x00000003U


	/** @def CRC_CH4_TO
	*   @brief Alias name for channel4 time out interrupt flag
	*/
	#define CRC_CH4_TO 0x10000000U

	/** @def CRC_CH4_UR
	*   @brief Alias name for channel4 underrun interrupt flag
	*/
	#define CRC_CH4_UR 0x08000000U

	/** @def CRC_CH4_OR
	*   @brief Alias name for channel4 overrun interrupt flag
	*/
	#define CRC_CH4_OR 0x04000000U

	/** @def CRC_CH4_FAIL
	*   @brief Alias name for channel4 crc fail interrupt flag
	*/
	#define CRC_CH4_FAIL 0x02000000U

	/** @def CRC_CH4_CC
	*   @brief Alias name for channel4 compression complete interrupt flag
	*/
	#define CRC_CH4_CC 0x01000000U

	/** @def CRC_CH3_TO
	*   @brief Alias name for channel3 time out interrupt flag
	*/
	#define CRC_CH3_TO 0x00100000U

	/** @def CRC_CH3_UR
	*   @brief Alias name for channel3 underrun interrupt flag
	*/
	#define CRC_CH3_UR 0x00080000U

	/** @def CRC_CH3_OR
	*   @brief Alias name for channel3 overrun interrupt flag
	*/
	#define CRC_CH3_OR 0x00040000U

	/** @def CRC_CH3_FAIL
	*   @brief Alias name for channel3 crc fail interrupt flag
	*/
	#define CRC_CH3_FAIL 0x00020000U

	/** @def CRC_CH3_CC
	*   @brief Alias name for channel3 compression complete interrupt flag
	*/
	#define CRC_CH3_CC 0x00010000U

	/** @def CRC_CH2_TO
	*   @brief Alias name for channel2 time out interrupt flag
	*/
	#define CRC_CH2_TO 0x00001000U

	/** @def CRC_CH2_UR
	*   @brief Alias name for channel2 underrun interrupt flag
	*/
	#define CRC_CH2_UR 0x00000800U

	/** @def CRC_CH2_OR
	*   @brief Alias name for channel2 overrun interrupt flag
	*/
	#define CRC_CH2_OR 0x00000400U

	/** @def CRC_CH2_FAIL
	*   @brief Alias name for channel2 crc fail interrupt flag
	*/
	#define CRC_CH2_FAIL 0x00000200U

	/** @def CRC_CH2_CC
	*   @brief Alias name for channel2 compression complete interrupt flag
	*/
	#define CRC_CH2_CC 0x00000100U

	/** @def CRC_CH1_TO
	*   @brief Alias name for channel1 time out interrupt flag
	*/
	#define CRC_CH1_TO 0x00000010U

	/** @def CRC_CH1_UR
	*   @brief Alias name for channel1 underrun interrupt flag
	*/
	#define CRC_CH1_UR 0x00000008U


	/** @def CRC_CH1_OR
	*   @brief Alias name for channel1 overrun interrupt flag
	*/
	#define CRC_CH1_OR 0x00000004U

	/** @def CRC_CH1_FAIL
	*   @brief Alias name for channel1 crc fail interrupt flag
	*/
	#define CRC_CH1_FAIL 0x00000002U

	/** @def CRC_CH1_CC
	*   @brief Alias name for channel1 compression complete interrupt flag
	*/
	#define CRC_CH1_CC 0x00000001U

	/** @def CRC_CH1
	*   @brief Alias name for channel1
	*/
	#define CRC_CH1    0x00000000U

	/** @def CRC_CH1
	*   @brief Alias name for channel2
	*/
	#define CRC_CH2    0x00000001U

	/** @def CRC_CH3
	*   @brief Alias name for channel3
	*/
	#define CRC_CH3    0x00000002U

	/** @def CRC_CH4
	*   @brief Alias name for channel4
	*/
	#define CRC_CH4    0x00000003U

	/** @struct crcModConfig
	*   @brief CRC mode specific parameters
	*
	*   This type is used to pass crc mode specific parameters
	*/
	/** @typedef RM4_CRC__MODE_CONFIG__T
	*   @brief CRC Data Type Definition
	*/
	/*****************************************************************************
	*****************************************************************************/
	typedef struct crcModConfig
	{
	    Luint32 mode;     /**< Mode of operation        */
	    Luint32 crc_channel;     /**< CRC channel-0,1       */
	    Luint64 * src_data_pat;  /**< Pattern data */
	    Luint32 data_length;  /**< Pattern data length.Number of 64 bit size word*/
	} RM4_CRC__MODE_CONFIG__T;

	/** @struct crcConfig
	*   @brief CRC configuration for different modes
	*
	*   This type is used to pass crc configuration
	*/
	/** @typedef RM4_CRC__CONFIG_T
	*   @brief CRC Data Type Definition
	*/
	/*****************************************************************************
	*****************************************************************************/
	typedef struct crcConfig
	{
	    Luint32 crc_channel;     /**< CRC channel-0,1         */
	    Luint32 mode;     /**< Mode of operation        */
	    Luint32 pcount;     /**< Pattern count*/
	    Luint32 scount;     /**< Sector count  */
	    Luint32 wdg_preload;  /**< Watchdog period */
	    Luint32 block_preload;  /**< Block period*/

	} RM4_CRC__CONFIG_T;

	/* USER CODE BEGIN (1) */
	/* USER CODE END */

	/*****************************************************************************
	*****************************************************************************/
	typedef struct crc_config_reg
	{
	    Luint32 CONFIG_CTRL0;
		Luint32 CONFIG_CTRL1;
		Luint32 CONFIG_CTRL2;
	    Luint32 CONFIG_INTS;
	    Luint32 CONFIG_PCOUNT_REG1;
	    Luint32 CONFIG_SCOUNT_REG1;
	    Luint32 CONFIG_WDTOPLD1;
	    Luint32 CONFIG_BCTOPLD1;
	    Luint32 CONFIG_PCOUNT_REG2;
	    Luint32 CONFIG_SCOUNT_REG2;
	    Luint32 CONFIG_WDTOPLD2;
	    Luint32 CONFIG_BCTOPLD2;
	}RM4_CRC__CONFIG_REG_T;

	#define CRC_CTRL0_CONFIGVALUE			0x00000000U
	#define CRC_CTRL1_CONFIGVALUE			0x00000000U
	#define CRC_CTRL2_CONFIGVALUE			((1U << 4U) | (CRC_FULL_CPU)  | (CRC_FULL_CPU << 8U))
	#define CRC_INTS_CONFIGVALUE			(0x00000000U | 0x00000000U | 0x00000000U | 0x00000000U | 0x00000000U | 0x00000000U | 0x00000000U | 0x00000000U | 0x00000000U | 0x00000000U)
	#define CRC_PCOUNT_REG1_CONFIGVALUE		(0x00000000U)
	#define CRC_SCOUNT_REG1_CONFIGVALUE		(0x00000000U)
	#define CRC_WDTOPLD1_CONFIGVALUE		(0x00000000U)
	#define CRC_BCTOPLD1_CONFIGVALUE		(0x00000000U)
	#define CRC_PCOUNT_REG2_CONFIGVALUE		(0x00000000U)
	#define CRC_SCOUNT_REG2_CONFIGVALUE		(0x00000000U)
	#define CRC_WDTOPLD2_CONFIGVALUE		(0x00000000U)
	#define CRC_BCTOPLD2_CONFIGVALUE		(0x00000000U)

#endif //WIN32
#endif //_RM4_CRC_PRIVATE_H_

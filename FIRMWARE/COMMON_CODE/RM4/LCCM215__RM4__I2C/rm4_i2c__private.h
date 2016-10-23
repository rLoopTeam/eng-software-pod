/**
 * @file		RM4_I2C__PRIVATE.H
 * @brief		Private types for I2C
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
  * 
 * @st_fileID	LCCM215R0.FILE.004
 */
#ifndef _RM4_I2C_PRIVATE_H_
#define _RM4_I2C_PRIVATE_H_

	/* USER CODE BEGIN (0) */
	/* USER CODE END */

	/* I2c Register Frame Definition */
	/** @struct i2cBase
	* @brief I2C Base Register Definition
	*
	* This structure is used to access the I2C module registers.
	*/
	/** @typedef RM4_I2C__BASE_T
	* @brief I2C Register Frame Type Definition
	*
	* This type is used to access the I2C Registers.
	*/
	typedef volatile struct i2cBase
	{

		Luint32 OAR;		 /**< 0x0000 I2C Own Address register			 */
		Luint32 IMR;		 /**< 0x0004 I2C Interrupt Mask/Status register	 */
		Luint32 STR;		 /**< 0x0008 I2C Interrupt Status register		 */
		Luint32 CKL;		 /**< 0x000C I2C Clock Divider Low register		 */
		Luint32 CKH;		 /**< 0x0010 I2C Clock Divider High register		 */
		Luint32 CNT;		 /**< 0x0014 I2C Data Count register				*/
		Luint8 DRR;			/**< 0x0018: I2C Data Receive register,			 */
		Luint8 rsvd1;		 /**< 0x0018: I2C Data Receive register, Reserved	*/
		Luint8 rsvd2;		 /**< 0x0018: I2C Data Receive register, Reserved	*/
		Luint8 rsvd3;		 /**< 0x0018: I2C Data Receive register, Reserved	*/
		Luint32 SAR;		 /**< 0x001C I2C Slave Address register			 */
		Luint8 DXR;			/**< 0x0020: I2C Data Transmit register,			*/
		Luint8 rsvd4;		 /**< 0x0020: I2C Data Transmit register, Reserved */
		Luint8 rsvd5;		 /**< 0x0020: I2C Data Transmit register, Reserved */
		Luint8 rsvd6;		 /**< 0x0020: I2C Data Transmit register, Reserved */
		Luint32 MDR;		 /**< 0x0024 I2C Mode register					 */
		Luint32 IVR;		 /**< 0x0028 I2C Interrupt Vector register		 */
		Luint32 EMDR;		 /**< 0x002C I2C Extended Mode register			 */
		Luint32 PSC;		 /**< 0x0030 I2C Prescaler register				 */
		Luint32 PID11;		 /**< 0x0034 I2C Peripheral ID register 1		 */
		Luint32 PID12;		 /**< 0x0038 I2C Peripheral ID register 2		 */
		Luint32 DMACR;		 /**< 0x003C I2C DMA Control Register			 */
		Luint32 rsvd7;		 /**< 0x0040 Reserved							 */
		Luint32 rsvd8;		 /**< 0x0044 Reserved							 */
		Luint32 PFNC;		 /**< 0x0048 Pin Function Register				 */
		Luint32 DIR;		 /**< 0x004C Pin Direction Register				 */
		Luint32 DIN;		 /**< 0x0050 Pin Data In Register				 */
		Luint32 DOUT;		 /**< 0x0054 Pin Data Out Register				 */
		Luint32 SET;		 /**< 0x0058 Pin Data Set Register				 */
		Luint32 CLR;		 /**< 0x005C Pin Data Clr Register				 */
		Luint32 PDR;		 /**< 0x0060 Pin Open Drain Output Enable Register */
		Luint32 PDIS;		 /**< 0x0064 Pin Pullup/Pulldown Disable Register */
		Luint32 PSEL;		 /**< 0x0068 Pin Pullup/Pulldown Selection Register */
		Luint32 PSRS;		 /**< 0x006C Pin Slew Rate Select Register		 */
	} RM4_I2C__BASE_T;


	/** @def i2cREG1
	* @brief I2C Register Frame Pointer
	*
	* This pointer is used by the I2C driver to access the I2C module registers.
	*/
	#define i2cREG1 ((RM4_I2C__BASE_T *)0xFFF7D400U)

	/* USER CODE BEGIN (1) */
	/* USER CODE END */


	/** @def i2cPORT1
	* @brief I2C GIO Port Register Pointer
	*
	* Pointer used by the GIO driver to access I/O PORT of I2C
	* (use the GIO drivers to access the port pins).
	*/
	#define i2cPORT1 ((gioPORT_t *)0xFFF7D44CU)


	/*
	 No-acknowledge (NACK) mode
	This bit is used to send an acknowledge (ACK) or a no-acknowledge (NACK) to the transmitter.
	This bit is only applicable when the I2C is in receiver mode. In master receiver mode, when the
	internal data counter decrements to zero, the I2C sends a NACK.
	The master receiver I2C finshes	a transfer when it sends a NACK. The I2C ignores ICCNT when NACKMOD is 1. The NACKMOD
	bit should be set before the rising edge of the last data bit if a NACK must be sent, and this bit is
	cleared once a NACK has been sent.
	0 The I2C sends an ACK to the transmitter during the acknowledge cycle.
	1 The I2C sends a NACK to the transmitter during the acknowledge cycle.
	 */
	#define C_RM4I2C__MDR_REG__NACKMOD_BIT__ACK 0U
	#define C_RM4I2C__MDR_REG__NACKMOD_BIT__NACK 1U
	#define C_RM4I2C__MDR_REG__NACKMOD_BIT__SHIFT 15U
	#define C_RM4I2C__MDR_REG__NACKMOD_BIT__MASK 1U

	#define C_RM4I2C__MDR_REG__BIT__FREE_STOP 0U
	#define C_LOCALDEF__LCCM215__I2CMDR_FREE_RUN 1U
	#define C_LOCALDEF__LCCM215__I2CMDR_FREE_SHIFT 14U
	#define C_LOCALDEF__LCCM215__I2CMDR_FREE_MASK 1U

	#define C_LOCALDEF__LCCM215__I2CMDR_STT_HARDWARE 0U
	#define C_LOCALDEF__LCCM215__I2CMDR_STT_DEVICE 1U
	#define C_RM4I2C__MDR_REG__STT_BIT_SHIFT	13U
	#define C_LOCALDEF__LCCM215__I2CMDR_STT_MASK	 1U

	#define C_LOCALDEF__LCCM215__I2CMDR_STP_HARDWARE 0U
	#define C_LOCALDEF__LCCM215__I2CMDR_STP_DEVICE 1U
	#define C_LOCALDEF__LCCM215__I2CMDR_STP_SHIFT	11U
	#define C_LOCALDEF__LCCM215__I2CMDR_STP_MASK	 1U

	#define C_LOCALDEF__LCCM215__I2CMDR_MST_SLAVE 0U
	#define C_LOCALDEF__LCCM215__I2CMDR_MST_MASTER 1U
	#define C_LOCALDEF__LCCM215__I2CMDR_MST_SHIFT 10U
	#define C_LOCALDEF__LCCM215__I2CMDR_MST_MASK	1U

	#define C_LOCALDEF__LCCM215__I2CMDR_TRX_TRANSMIT 1U
	#define C_LOCALDEF__LCCM215__I2CMDR_TRX_RECEIVE 0U
	#define C_LOCALDEF__LCCM215__I2CMDR_TRX_SHIFT 9U
	#define C_LOCALDEF__LCCM215__I2CMDR_TRX_MASK	1U

	#define C_LOCALDEF__LCCM215__I2CMDR_XA_SEVEN	0U
	#define C_LOCALDEF__LCCM215__I2CMDR_XA_TEN	 1U
	#define C_LOCALDEF__LCCM215__I2CMDR_XA_SHIFT	8U
	#define C_LOCALDEF__LCCM215__I2CMDR_XA_MASK	 1U

	#define C_LOCALDEF__LCCM215__I2CMDR_RM_NOT_REPEAT 0U
	#define C_LOCALDEF__LCCM215__I2CMDR_RM_REPEAT	 1U
	#define C_LOCALDEF__LCCM215__I2CMDR_RM_SHIFT	 7U
	#define C_LOCALDEF__LCCM215__I2CMDR_RM_MASK		1U

	#define C_LOCALDEF__LCCM215__I2CMDR_DLB_DISABLED 0U
	#define C_LOCALDEF__LCCM215__I2CMDR_DLB_ENABLED	1U
	#define C_LOCALDEF__LCCM215__I2CMDR_DLB_SHIFT	 6U
	#define C_LOCALDEF__LCCM215__I2CMDR_DLB_MASK	 1U

	#define C_LOCALDEF__LCCM215__I2CMDR_nIRS_RESET		 0U
	#define C_LOCALDEF__LCCM215__I2CMDR_nIRS_OUT_OF_RESET 1U
	#define C_LOCALDEF__LCCM215__I2CMDR_nIRS_SHIFT		 5U
	#define C_LOCALDEF__LCCM215__I2CMDR_nIRS_MASK		 1U

	#define C_LOCALDEF__LCCM215__I2CMDR_STB_NOT_START 0U
	#define C_LOCALDEF__LCCM215__I2CMDR_STB_START	 1U
	#define C_LOCALDEF__LCCM215__I2CMDR_STB_SHIFT	 4U
	#define C_LOCALDEF__LCCM215__I2CMDR_STB_MASK	 1U

	#define C_LOCALDEF__LCCM215__I2CMDR_FDF_NOT_FREE 0U
	#define C_LOCALDEF__LCCM215__I2CMDR_FDF_FREE	 1U
	#define C_LOCALDEF__LCCM215__I2CMDR_FDF_SHIFT	 3U
	#define C_LOCALDEF__LCCM215__I2CMDR_FDF_MASK	 1U

	#define C_LOCALDEF__LCCM215__I2CMDR_BC_IN_FDF_8_WITH_ACK_9 0U
	#define C_LOCALDEF__LCCM215__I2CMDR_BC_IN_FDF_2_WITH_ACK_3 2U
	#define C_LOCALDEF__LCCM215__I2CMDR_BC_IN_FDF_3_WITH_ACK_4 3U
	#define C_LOCALDEF__LCCM215__I2CMDR_BC_IN_FDF_4_WITH_ACK_5 4U
	#define C_LOCALDEF__LCCM215__I2CMDR_BC_IN_FDF_5_WITH_ACK_6 5U
	#define C_LOCALDEF__LCCM215__I2CMDR_BC_IN_FDF_6_WITH_ACK_7 6U
	#define C_LOCALDEF__LCCM215__I2CMDR_BC_IN_FDF_7_WITH_ACK_8 7U
	#define C_LOCALDEF__LCCM215__I2CMDR_BC_SHIFT	 0U
	#define C_LOCALDEF__LCCM215__I2CMDR_BC_MASK		7U

	#define C_LOCALDEF__LCCM215__I2CPFNC_PINFUNCT_I2C	0
	#define C_LOCALDEF__LCCM215__I2CPFNC_PINFUNCT_IO	 1
	#define C_LOCALDEF__LCCM215__I2CPFNC_PINFUNCT_SHIFT 0
	#define C_LOCALDEF__LCCM215__I2CPFNC_PINFUNCT_MASK 1

	#define C_LOCALDEF__LCCM215__I2CDOUT_SDAOUT_LOW	 0
	#define C_LOCALDEF__LCCM215__I2CDOUT_SDAOUT_HIGH	 1
	#define C_LOCALDEF__LCCM215__I2CDOUT_SDAOUT_SHIFT	1
	#define C_LOCALDEF__LCCM215__I2CDOUT_SDAOUT_MASK	 1

	#define C_LOCALDEF__LCCM215__I2CDOUT_SCLOUT_LOW	 0
	#define C_LOCALDEF__LCCM215__I2CDOUT_SCLOUT_HIGH	 1
	#define C_LOCALDEF__LCCM215__I2CDOUT_SCLOUT_SHIFT	0
	#define C_LOCALDEF__LCCM215__I2CDOUT_SCLOUT_MASK	 1

	#define C_LOCALDEF__LCCM215__PDIR_SDADIR_INPUT	0
	#define C_LOCALDEF__LCCM215__PDIR_SDADIR_OUTPUT 1
	#define C_LOCALDEF__LCCM215__PDIR_SDADIR_SHIFT	1
	#define C_LOCALDEF__LCCM215__PDIR_SDADIR_MASK	 1

	#define C_LOCALDEF__LCCM215__PDIR_SCLDIR_INPUT	0
	#define C_LOCALDEF__LCCM215__PDIR_SCLDIR_OUTPUT 1
	#define C_LOCALDEF__LCCM215__PDIR_SCLDIR_SHIFT	0
	#define C_LOCALDEF__LCCM215__PDIR_SCLDIR_MASK	 1

	#define C_LOCALDEF__LCCM215__PDR_SDAPDR_OPENDRAIN_ENABLE		 0
	#define C_LOCALDEF__LCCM215__PDR_SDAPDR_OPENDRAIN_DISABLE		 1
	#define C_LOCALDEF__LCCM215__PDR_SDAPDR_SHIFT	1
	#define C_LOCALDEF__LCCM215__PDR_SDAPDR_MASK	 1

	#define C_LOCALDEF__LCCM215__PDR_SCLPDR_OPENDRAIN_ENABLE		 0
	#define C_LOCALDEF__LCCM215__PDR_SCLPDR_OPENDRAIN_DISABLE		 1
	#define C_LOCALDEF__LCCM215__PDR_SCLPDR_SHIFT	0
	#define C_LOCALDEF__LCCM215__PDR_SCLPDR_MASK	 1

	#define C_LOCALDEF__LCCM215__PDIS_SDAPDIS_PULL_ENABLE		 0
	#define C_LOCALDEF__LCCM215__PDIS_SDAPDIS_PULL_DISABLE		 1
	#define C_LOCALDEF__LCCM215__PDIS_SDAPDIS_SHIFT	1
	#define C_LOCALDEF__LCCM215__PDIS_SDAPDIS_MASK	 1

	#define C_LOCALDEF__LCCM215__PDIS_SCLPDIS_PULL_ENABLE		 0
	#define C_LOCALDEF__LCCM215__PDIS_SCLPDIS_PULL_DISABLE		 1
	#define C_LOCALDEF__LCCM215__PDIS_SCLPDIS_SHIFT	0
	#define C_LOCALDEF__LCCM215__PDIS_SCLPDIS_MASK	 1

	#define C_LOCALDEF__LCCM215__PSEL_SDAPSEL_PULL_DOWN		 0
	#define C_LOCALDEF__LCCM215__PSEL_SDAPSEL_PULL_UP			 1
	#define C_LOCALDEF__LCCM215__PSEL_SDAPSEL_SHIFT			 1
	#define C_LOCALDEF__LCCM215__PSEL_SDAPSEL_MASK				1

	#define C_LOCALDEF__LCCM215__PSEL_SCLPSEL_PULL_DOWN		 0
	#define C_LOCALDEF__LCCM215__PSEL_SCLPSEL_PULL_UP			 1
	#define C_LOCALDEF__LCCM215__PSEL_SCLPSEL_SHIFT			 0
	#define C_LOCALDEF__LCCM215__PSEL_SCLPSEL_MASK				1

	//INTERRUPT MASK REGISTER BITS
	//arbitration lost
	#define C_RM4I2C__IMR_REG__BIT__ALEN			0x0001U
	//no acknowledgment
	#define C_RM4I2C__IMR_REG__BIT__NACKEN		 0x0002U
	//access ready
	#define C_RM4I2C__IMR_REG__BIT__ARDYEN		 0x0004U
	//receive data ready
	#define C_RM4I2C__IMR_REG__BIT__RXRDYRN		 0x0008U
	//transmit data ready
	#define C_RM4I2C__IMR_REG__BIT__TXRDYEN		 0x0010U
	//stop condition detect
	#define C_RM4I2C__IMR_REG__BIT__SCDEN		 0x0020U
	//address as slave
	#define C_RM4I2C__IMR_REG__BIT__AASEN			 0x0040U

	//STATUS REG BITS
	//Arbitration lost
	#define C_RM4I2C__STR_REG__BIT__AL								(0x0001U)
	//Nack
	#define C_RM4I2C__STR_REG__BIT__NACK							(0x0002U)
	//Access ready interrupt flag
	#define C_RM4I2C__STR_REG__BIT__ARDY							(0x0004U)
	#define C_RM4I2C__STR_REG__BIT__RXRDY							(0x0008U)
	#define C_RM4I2C__STR_REG__BIT__TXRDY							(0x0010U)
	#define C_RM4I2C__STR_REG__BIT__SCD								(0x0020U)
	#define C_RM4I2C__STR_REG__BIT__AD0								(0x0100U)
	#define C_RM4I2C__STR_REG__BIT__AAS								(0x0200U)
	#define C_RM4I2C__STR_REG__BIT__XSMT							(0x0400U)
	#define C_RM4I2C__STR_REG__BIT__RSFULL							(0x0800U)
	#define C_RM4I2C__STR_REG__BIT__BB								(0x1000U)
	#define C_RM4I2C__STR_REG__BIT__NACKSNT							(0x2000U)
	#define C_RM4I2C__STR_REG__BIT__SDIR							(0x4000U)


	/***********************************************************************************
	 **************************** Initial configuration*********************************
	 **********************************************************************************/
	//Keep running when in debugger mode.
	#define C_LOCALDEF__LCCM215__I2CMDR_FREE	 C_RM4I2C__MDR_REG__BIT__FREE_STOP
	#define C_LOCALDEF__LCCM215__I2CMDR_STT	 C_LOCALDEF__LCCM215__I2CMDR_STT_HARDWARE
	#define C_LOCALDEF__LCCM215__I2CMDR_STP	 C_LOCALDEF__LCCM215__I2CMDR_STP_DEVICE
	#define C_LOCALDEF__LCCM215__I2CMDR_MST	 C_LOCALDEF__LCCM215__I2CMDR_MST_MASTER
	#define C_LOCALDEF__LCCM215__I2CMDR_TRX	 C_LOCALDEF__LCCM215__I2CMDR_TRX_TRANSMIT
	#define C_LOCALDEF__LCCM215__I2CMDR_XA		C_LOCALDEF__LCCM215__I2CMDR_XA_SEVEN
	#define C_LOCALDEF__LCCM215__I2CMDR_RM		C_LOCALDEF__LCCM215__I2CMDR_RM_NOT_REPEAT
	#define C_LOCALDEF__LCCM215__I2CMDR_DLB	 C_LOCALDEF__LCCM215__I2CMDR_DLB_DISABLED
	#define C_LOCALDEF__LCCM215__I2CMDR_STB	 C_LOCALDEF__LCCM215__I2CMDR_STB_NOT_START
	#define C_LOCALDEF__LCCM215__I2CMDR_FDF	 C_LOCALDEF__LCCM215__I2CMDR_FDF_NOT_FREE
	#define C_LOCALDEF__LCCM215__I2CMDR_BC		C_LOCALDEF__LCCM215__I2CMDR_BC_IN_FDF_8_WITH_ACK_9
	#define C_LOCALDEF__LCCM215__I2CPFNC_PINFUNCT C_LOCALDEF__LCCM215__I2CPFNC_PINFUNCT_I2C
	#define C_LOCALDEF__LCCM215__I2CDOUT_SDAOUT C_LOCALDEF__LCCM215__I2CDOUT_SDAOUT_LOW
	#define C_LOCALDEF__LCCM215__I2CDOUT_SCLOUT C_LOCALDEF__LCCM215__I2CDOUT_SCLOUT_LOW
	#define C_LOCALDEF__LCCM215__PDIR_SDADIR	 C_LOCALDEF__LCCM215__PDIR_SDADIR_OUTPUT
	#define C_LOCALDEF__LCCM215__PDIR_SCLDIR	 C_LOCALDEF__LCCM215__PDIR_SCLDIR_OUTPUT
	#define C_LOCALDEF__LCCM215__PDR_SDAPDR	 C_LOCALDEF__LCCM215__PDR_SDAPDR_OPENDRAIN_ENABLE
	#define C_LOCALDEF__LCCM215__PDR_SCLPDR	 C_LOCALDEF__LCCM215__PDR_SCLPDR_OPENDRAIN_ENABLE
	#define C_LOCALDEF__LCCM215__PDIS_SDAPDIS	 C_LOCALDEF__LCCM215__PDIS_SDAPDIS_PULL_ENABLE
	#define C_LOCALDEF__LCCM215__PDIS_SCLPDIS	 C_LOCALDEF__LCCM215__PDIS_SCLPDIS_PULL_ENABLE
	#define C_LOCALDEF__LCCM215__PSEL_SDAPSEL	 C_LOCALDEF__LCCM215__PSEL_SDAPSEL_PULL_UP
	#define C_LOCALDEF__LCCM215__PSEL_SCLPSEL	 C_LOCALDEF__LCCM215__PSEL_SCLPSEL_PULL_UP

#endif //_RM4_I2C_PRIVATE_H_

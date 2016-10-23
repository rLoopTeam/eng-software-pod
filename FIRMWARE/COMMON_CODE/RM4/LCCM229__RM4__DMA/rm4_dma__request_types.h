/**
 * @file		RM4_DMA__REQUEST_TYPES.H
 * @brief		DMA Request Types
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM229R0.FILE.031
 */

#ifndef _RM4_DMA__REQUEST_TYPES_H_
#define _RM4_DMA__REQUEST_TYPES_H_

	/*
	4.16.2 Default DMA Request Map
	The DMA module on this microcontroller has 16 channels and up to 32 hardware DMA requests. The
	module contains DREQASIx registers which are used to map the DMA requests to the DMA channels. By
	default, channel 0 is mapped to request 0, channel 1 to request 1, and so on.
	Some DMA requests have multiple sources, as shown in Table 4-32. The application must ensure that
	only one of these DMA request sources is enabled at any time.

	Table 4-32. DMA Request Line Connection
	Modules 			DMA Request Sources 					DMA Request
	-----------------------------------------------------------------------------
	MIBSPI1 			MIBSPI1[1](1) 							DMAREQ[0]
	MIBSPI1 			MIBSPI1[0](2) 							DMAREQ[1]
	SPI2 				SPI2 receive 							DMAREQ[2]
	SPI2 				SPI2 transmit 							DMAREQ[3]

	MIBSPI1				MIBSPI1[2]								DMAREQ[4]
	MIBSPI3				MIBSPI3[2]
	DCAN2  				DCAN2 IF3

	MIBSPI1 / MIBSPI3 / DCAN2 MIBSPI1[3] / MIBSPI3[3] / DCAN2 IF2 DMAREQ[5]
	DCAN1 / MIBSPI5 DCAN1 IF2 / MIBSPI5[2] DMAREQ[6]

	MIBADC1				MIBADC1 event							DMAREQ[7]
	MIBSPI5  			MIBSPI5[3]

	MIBSPI1 / MIBSPI3 / DCAN1 MIBSPI1[4] / MIBSPI3[4] / DCAN1 IF1 DMAREQ[8]
	MIBSPI1 / MIBSPI3 / DCAN2 MIBSPI1[5] / MIBSPI3[5] / DCAN2 IF1 DMAREQ[9]

	MIBADC1 			MIBADC1 G1								 DMAREQ[10]
	I2C					I2C receive
	MIBSPI5  			MIBSPI5[4]

	MIBADC1 			MIBADC1 G2								DMAREQ[11]
	I2C 				I2C transmit
	MIBSPI5				MIBSPI5[5]

	RTI / MIBSPI1 / MIBSPI3 RTI DMAREQ0 / MIBSPI1[6] / MIBSPI3[6] DMAREQ[12]
	RTI / MIBSPI1 / MIBSPI3 RTI DMAREQ1 / MIBSPI1[7] / MIBSPI3[7] DMAREQ[13]
	MIBSPI3 / USB Device / MibADC2 / MIBSPI5 MIBSPI3[1](1) / USB_FUNC.DMATXREQ_ON[0] / DMAREQ[14]
	MibADC2 event / MIBSPI5[6]
	MIBSPI3 / USB Device / MIBSPI5 MIBSPI3[0](2) / USB_FUNC.DMARXREQ_ON[0] / DMAREQ[15]
	MIBSPI5[7]
	MIBSPI1 / MIBSPI3 / DCAN1 / MibADC2 MIBSPI1[8] / MIBSPI3[8] / DCAN1 IF3 / MibADC2 G1 DMAREQ[16]
	MIBSPI1 / MIBSPI3 / DCAN3 / MibADC2 MIBSPI1[9] / MIBSPI3[9] / DCAN3 IF1 / MibADC2 G2 DMAREQ[17]
	RTI / USB Device / MIBSPI5 RTI DMAREQ2 / USB_FUNC.DMATXREQ_ON[1] / DMAREQ[18]
	MIBSPI5[8]
	RTI / USB Device / MIBSPI5 RTI DMAREQ3 / USB_FUNC.DMARXREQ_ON[1] / DMAREQ[19]
	MIBSPI5[9]
	N2HET1 / N2HET2 / DCAN3 N2HET1 DMAREQ[4] / N2HET2 DMAREQ[4] / DCAN3 DMAREQ[20]
	IF2
	N2HET1 / N2HET2 / DCAN3 N2HET1 DMAREQ[5] / N2HET2 DMAREQ[5] / DCAN3 DMAREQ[21]
	IF3
	MIBSPI1 / MIBSPI3 / MIBSPI5 MIBSPI1[10] / MIBSPI3[10] / MIBSPI5[10] DMAREQ[22]
	MIBSPI1 / MIBSPI3 / MIBSPI5 MIBSPI1[11] / MIBSPI3[11] / MIBSPI5[11] DMAREQ[23]
	N2HET1 / N2HET2 / SPI4 / MIBSPI5 N2HET1 DMAREQ[6] / N2HET2 DMAREQ[6] / SPI4 DMAREQ[24]
	receive / MIBSPI5[12]
	N2HET1 / N2HET2 / SPI4 / MIBSPI5 N2HET1 DMAREQ[7] / N2HET2 DMAREQ[7] / SPI4 DMAREQ[25]
	transmit / MIBSPI5[13]
	CRC / MIBSPI1 / MIBSPI3 CRC DMAREQ[0] / MIBSPI1[12] / MIBSPI3[12] DMAREQ[26]
	CRC / MIBSPI1 / MIBSPI3 CRC DMAREQ[1] / MIBSPI1[13] / MIBSPI3[13] DMAREQ[27]
	LIN / USB Device / MIBSPI5 LIN receive / USB_FUNC.DMATXREQ_ON[2] / DMAREQ[28]
	MIBSPI5[14]
	LIN / USB Device / MIBSPI5 LIN transmit / USB_FUNC.DMARXREQ_ON[2] / DMAREQ[29]
	MIBSPI5[15]
	MIBSPI1 / MIBSPI3 / SCI / MIBSPI5 MIBSPI1[14] / MIBSPI3[14] / SCI receive / DMAREQ[30]
	MIBSPI5[1](1)
	MIBSPI1 / MIBSPI3 / SCI / MIBSPI5 MIBSPI1[15] / MIBSPI3[15] / SCI transmit / DMAREQ[31]

	Notes:
	(1) SPI1, SPI3, SPI5 receive in compatibility mode
	(2) SPI1, SPI3, SPI5 transmit in compatibility mode

	 */
	typedef enum
	{

		HW_REQ__DMA0_GROUP	= 0U,
		HW_REQ__DMA1_GROUP	= 1U,

		HW_REQ__ADC1_EVENT_GROUP	= 7U,

		HW_REQ__ADC1_GROUP_1	= 10U,

		HW_REQ__ADC1_GROUP_2	= 11U


	}RM4_DMA__HW_REQUEST_TYPE__T;

#endif // _RM4_DMA__REQUEST_TYPES_H_


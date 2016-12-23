/**
 * @file		ATA6870__LOWLEVEL.C
 * @brief		Lowlevel interface for the ATA6870 driver.
 * 				This file provides basically the lowest point before we hit silicon.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM650R0.FILE.005
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup ATA6870
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup ATA6870__LOWLEVEL
 * @ingroup ATA6870
 * @{ */


#include "../ata6870.h"
#if C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE == 1U

extern struct _str6870 sATA6870;

//Constant value Boolean [MISRA 2004 Rules 13.7 and 14.1], reviewed
/*lint -e506*/

//Boolean within 'if' always evaluates to True, reviewed
/*lint -e774*/

//locals
static void vATA6870_LOWLEVEL__Reset(void);
static Luint16 u16ATA6870_LOWLEVEL__Tx_DeviceID(Luint8 u8DeviceIndex, Luint8 *pu8CRC);
static Luint8 u8ATA6870_LOWLEVEL__CRC(Luint8 u8InitialCRC, Luint8 u8Data);

/***************************************************************************//**
 * @brief
 * Perform an init of any low level systems, including IO pins.
 * 
 * @st_funcMD5		B097BAEE07BFD2D10039B3FAF2B830F1
 * @st_funcID		LCCM650R0.FILE.005.FUNC.001
 */
void vATA6870_LOWLEVEL__Init(void)
{
	//configure the IO

	//power down control
	M_LOCALDEF__LCCM650__POWER_ENABLE_TRIS(0U);
	M_LOCALDEF__LCCM650__POWER_ENABLE_LATCH(0U);
	
	//tris for SPI
	M_LOCALDEF__LCCM650__NCS_TRIS(0U);
	M_LOCALDEF__LCCM650__NCS_LATCH(1U);

	//power avail flag
	M_LOCALDEF__LCCM650__POWER_AVAIL_TRIS(1U);
	
	//do a reset
	vATA6870_LOWLEVEL__Reset();

}


/***************************************************************************//**
 * @brief
 * Generate a reset pulse on the [Just discovered] No reset line :(
 * 
 * @st_funcMD5		C191E716625B3D1604ED5FD8B46C5F98
 * @st_funcID		LCCM650R0.FILE.005.FUNC.003
 */
void vATA6870_LOWLEVEL__Reset(void)
{

	//like all quality devices.. no reset line :(

}


/***************************************************************************//**
 * @brief
 * Write a U8 to a devices register
 * 
 * @note
 * This function will master the bus and take command of the chip selects and
 * other SPI functions
 *
 * @note
 * 7.6.4.1 SPI Transaction Fields
 * Most of the time, the SPI frame is defined by 4 distinct fields:
 * NAME				SIZE		DETAILS
 * -------------------------------------------------------------------------------------
 * IDENTIFICATION	2 bytes		16-bit chip identification (MOSI), in parallel 16-bit IRQ state (MISO)
 * CONTROL 			1 byte		7-bit register address + 1-bit read/write information (MOSI)
 * DATA 			k byte		k*8 bits data (MOSI or MISO depending on the access direction)
 * CHKSUM			1 byte		8 bits if the Chksum_ena bit is set in the Ctrl register (register 0x01, bit 4)
 * 
 * @param[in]		u8Length				The length of the data to write
 * @param[in]		*pu8Data				Pointer to the array of data to write
 * @param[in]		eRegister				The register type.
 * @param[in]		u8DeviceIndex			The ATA6870N device index on the bus.
 * @st_funcMD5		4637864D351E79A0ABF1372F5DBA550A
 * @st_funcID		LCCM650R0.FILE.005.FUNC.002
 */
void vATA6870_LOWLEVEL__Reg_WriteU8(Luint8 u8DeviceIndex, ATA6870_REGS_T eRegister, Luint8 *pu8Data, Luint8 u8Length)
{
	//the returned IRQ status as a result of the device ID command
	Luint16 u16IRQStatus;
	Luint8 u8Counter;
	Luint8 u8Temp;
	Luint8 u8TempData;
	Luint8 u8Control;
	Luint8 u8CRC;
	
	
	/*
	7.6.4.6 Communication Error
	For internal synchronization, it is mandatory to keep CLK running during any SPI access; 
	CLK must be set on 4 clock cycles [at least) before SPI access starts, and must be kept on 4 clock cycles [at least)
	after SPI access ends up. Keeping at least 4 CLK clock cycles between two consecutive SPI accesses is mandatory.
	*/
	u8Temp = M_LOCALDEF__LCCM650__SPI_TX_U8(0x00U);
	
	//deasert the nCS
	M_LOCALDEF__LCCM650__NCS_LATCH(0U);

	//initial CRC conditions
	u8CRC = 0U;
	
	//send the device ID and at the same time rx the IRQ status.
	u16IRQStatus = u16ATA6870_LOWLEVEL__Tx_DeviceID(u8DeviceIndex, &u8CRC);
	
	//save off the interrupt status from this transaction
	if(u8DeviceIndex < C_LOCALDEF__LCCM650__NUM_DEVICES)
	{

		sATA6870.sDevice[u8DeviceIndex].sIRQ.u16IRQ_Status = u16IRQStatus;
	}
	else
	{
		//todo: log the fault
	}
	
	//send the control field
	u8Control = (Luint8)eRegister;
	
	//mask for the write
	u8Control <<= 1U;
	u8Control |= 0x01U;
	
	//transmit the control value
	u8Temp = M_LOCALDEF__LCCM650__SPI_TX_U8(u8Control);
	
	#if C_LOCALDEF__LCCM650__ENABLE_CRC == 1U
		//CRC the control
		u8CRC = u8ATA6870_LOWLEVEL__CRC(u8CRC, u8Control);
	#endif
	
	//transmit out the data
	//we are not clocking data back in, so ignore the return data
	for(u8Counter = 0U; u8Counter < u8Length; u8Counter++)
	{
		//data value from the array
		u8TempData = pu8Data[u8Counter];
	
		//transmit the byte in the array.
		u8Temp = M_LOCALDEF__LCCM650__SPI_TX_U8(u8TempData);
		
	#if C_LOCALDEF__LCCM650__ENABLE_CRC == 1U
			//CRC the data
			u8CRC = u8ATA6870_LOWLEVEL__CRC(u8CRC, u8TempData);
	#endif

	}
	
	#if C_LOCALDEF__LCCM650__ENABLE_CRC == 1U
		//finally send the CRC.
		u8Temp = M_LOCALDEF__LCCM650__SPI_TX_U8(u8CRC);
	#endif
	
	//raise nCS
	M_LOCALDEF__LCCM650__NCS_LATCH(1U);

	//4+ clocks.
	u8Temp = M_LOCALDEF__LCCM650__SPI_TX_U8(0x00U);
	
}



/***************************************************************************//**
 * @brief
 * Read a byte / byte array from a device with a given length.
 * 
 * @param[in]		u8Length				The length of data we wish to read
 * @param[out]		*pu8Data				Pointer to the return data buffer
 * @param[in]		eRegister				The register to hit
 * @param[in]		u8DeviceIndex			The device in the chain.
 * @st_funcMD5		AEAD2F62CAC76236213F277D4C718361
 * @st_funcID		LCCM650R0.FILE.005.FUNC.006
 */
void vATA6870_LOWLEVEL__Reg_ReadU8(Luint8 u8DeviceIndex, ATA6870_REGS_T eRegister, Luint8 *pu8Data, Luint8 u8Length)
{
	//the returned IRQ status as a result of the device ID command
	Luint16 u16IRQStatus;
	Luint8 u8Counter;
	Luint8 u8Temp;
	Luint8 u8TempData;
	Luint8 u8Control;
	Luint8 u8CRC;
	
	
	/*
	7.6.4.6 Communication Error
	For internal synchronization, it is mandatory to keep CLK running during any SPI access; 
	CLK must be set on 4 clock cycles [at least) before SPI access starts, and must be kept on 4 clock cycles [at least)
	after SPI access ends up. Keeping at least 4 CLK clock cycles between two consecutive SPI accesses is mandatory.
	*/
	u8Temp = M_LOCALDEF__LCCM650__SPI_TX_U8(0x00U);
	
	//deasert the nCS
	M_LOCALDEF__LCCM650__NCS_LATCH(0U);

	//initial CRC conditions
	u8CRC = 0U;
	
	//send the device ID and at the same time rx the IRQ status.
	u16IRQStatus = u16ATA6870_LOWLEVEL__Tx_DeviceID(u8DeviceIndex, &u8CRC);
	
	//save off the interrupt status from this transaction
	if(u8DeviceIndex < C_LOCALDEF__LCCM650__NUM_DEVICES)
	{
		sATA6870.sDevice[u8DeviceIndex].sIRQ.u16IRQ_Status = u16IRQStatus;
	}
	else
	{
		//todo: log the fault
	}
	
	
	//send the control field
	u8Control = (Luint8)eRegister;
	
	//mask for the read
	u8Control <<= 1U;
	u8Control &= 0xFEU;
	
	//transmit the control value
	u8Temp = M_LOCALDEF__LCCM650__SPI_TX_U8(u8Control);

	#if C_LOCALDEF__LCCM650__ENABLE_CRC == 1U
		//CRC the control
		u8CRC = u8ATA6870_LOWLEVEL__CRC(u8CRC, u8Control);
	#endif
	
	//transmit out the data
	//we are not clocking data back in, so ignore the return data
	for(u8Counter = 0U; u8Counter < u8Length; u8Counter++)
	{
		//Read back via a dummy byte
		pu8Data[u8Counter] = M_LOCALDEF__LCCM650__SPI_TX_U8(0x00U);

	#if C_LOCALDEF__LCCM650__ENABLE_CRC == 1U
			//CRC the data, its zero and I am not sure if we actually need to do this
			//or if the CRC won't change if we are clocking in 0's
			u8CRC = u8ATA6870_LOWLEVEL__CRC(u8CRC, 0x00U);
	#endif
	}
	
	#if C_LOCALDEF__LCCM650__ENABLE_CRC == 1U
		//finally send the CRC.
		u8Temp = M_LOCALDEF__LCCM650__SPI_TX_U8(u8CRC);
	#endif
	
	//raise nCS
	M_LOCALDEF__LCCM650__NCS_LATCH(1U);

	//4+ clocks.
	u8Temp = M_LOCALDEF__LCCM650__SPI_TX_U8(0x00U);
	
}

/***************************************************************************//**
 * @brief
 * Transmit the device ID portion on the SPI transaction.
 * The DEV ID is the first two bytes indicating which device in the string we are communicating with
 * 
 * @param[in]		*pu8CRC					The initial CRC and the returned CRC
 * @param[in]		u8DeviceIndex			The device index in the chain we want to communicate with.
 * @st_funcMD5		149F5B6BB5ACD08C3AB13E1429096332
 * @st_funcID		LCCM650R0.FILE.005.FUNC.004
 */
Luint16 u16ATA6870_LOWLEVEL__Tx_DeviceID(Luint8 u8DeviceIndex, Luint8 *pu8CRC)
{

	Luint16 u16Addx;
	#if C_LOCALDEF__LCCM650__ENABLE_CRC == 1U
		Luint8 u8CRC;
	#endif
	
	//I know, MISRA-C issues, but its ok.
	union
	{
		Luint16 u16;
		Luint8 u8[2];
	}unT, unR;
	
	//generate the address of the device in the chain
	u16Addx = 0x0001U;
	u16Addx <<= (Luint16)u8DeviceIndex;

	//perform the transfer
	unT.u16 = u16Addx;

	//send the lower
	unR.u8[1] = M_LOCALDEF__LCCM650__SPI_TX_U8(unT.u8[1]);

	#if C_LOCALDEF__LCCM650__ENABLE_CRC == 1U
		//compute the CRC on the lower
		u8CRC = u8ATA6870_LOWLEVEL__CRC(*pu8CRC, unT.u8[1]);
	#endif

	//send the upper
	unR.u8[0] = M_LOCALDEF__LCCM650__SPI_TX_U8(unT.u8[0]);

	#if C_LOCALDEF__LCCM650__ENABLE_CRC == 1U
		//compute the CRC on the upper and retun the CRC
		*pu8CRC = u8ATA6870_LOWLEVEL__CRC(u8CRC, unT.u8[0]);
	#else
		*pu8CRC = 0U;
	#endif

	//return with the IRQ
	return unR.u16;
	
}


/***************************************************************************//**
 * @brief
 * Compute one byte of the CRC.
 * 
 * @note
 *  7.6.4.7 CHKSUM Field
 * The ATA6870N provides the possibility of verifying the transmitted data using a checksum. Setting chksum_ena bit
 * to 1 in the Ctrl register [default = 0) activates the checksum feature.
 * The chksum field is an 8-bit checksum computed from the proceeding data [control and data fields, byte 3 to byte n-1). It is
 * based on the polynomial x8+x2+x1+1. The way it is computed is depicted below:
 
 * The checksum is calculated from the CONTROL field and DATA field by a polynomial division. The DATA field can consist of
 * 1 byte up to 14 bytes [112-bit read-only â€œburst accessâ€�). The IDENTIFICATION field [2 bytes) is not used to generate the
 * checksum. The checksum is always sent by the microcontroller, independent of read write mode.
 * The checksum is in the LFSR [linear feedback shift register) when the complete bitstream [the whole fields of the
 * transaction) followed by 0x00 have been shifted in the LFSR.
 * The checksum verification on the complete data transmission was OK when the complete bitstream followed by the
 * checksum have been shifted in the LFSR, and the content of the LFSR is 0x00. If this is not the case, the receiving
 * ATA6870N will set the chkError bit in the status register. This will cause an interrupt to the MCU if the chkError is not masked
 * by the chkErrorMsk bit in the IrqMask register. See the example below. The checksum is serially computed from the 8-bit
 * value 0x57. So the bitstream 0x5700 is shifted in the LFSR. The resulting checksum is [f6o, f6i, f5i â€¦ f0i] at the last shift in
 * cycle:
 * During an SPI write access, the checksum is computed by the MCU and sent MSB first in the CHKSUM field. For an SPI
 * read access, the checksum is computed by the  ATA6870N and is checked by the MCU. During CHKSUM, MCU has
 * to send 0x00 on MOSI, and must check that its own LFSR equals 0x00 at the end of CHKSUM field.
 * 
 * @param[in]		u8Data					The new data value to add to the CRC.
 * @param[in]		u8InitialCRC			The initial CRC conditions.
 * @return			The new CRC
 * @st_funcMD5		BF1E1427911C29BED3835813AB683097
 * @st_funcID		LCCM650R0.FILE.005.FUNC.005
 */
Luint8 u8ATA6870_LOWLEVEL__CRC(Luint8 u8InitialCRC, Luint8 u8Data)
{
	Luint8 u8Mask;
	Luint8 u8BitSet;
	Luint8 u8Return;
	
	//assign the initial conditions
	u8Return = u8InitialCRC;
	
	//slide the mask along
	for(u8Mask = 0x01U; u8Mask > 0U; u8Mask <<= 1U)
	{
	
		//is the LSB set?
		if((u8Return & 0x01U) != 0x00U)
		{
			u8BitSet = 1U;
		}
		else
		{
			u8BitSet = 0U;
		}
	
		//shift over
		u8Return >>= 1U;
	
		if((u8Data & u8Mask) != 0x00U)
		{
			//set the bit to 1 if we have a match for the mask as this point
			u8Return |= 0x80U;
		}
		else
		{
			//fall on
		}
	
		//do we need to do the toggle
		if(u8BitSet == 0x01U)
		{
			//0xE0 = x^8+x^2+x+1
			u8Return ^= 0xE0U;
		}
		else
		{
			//fall on
		}
	
	}//for(u8Mask = 0x01U; u8Mask > 0U; u8Mask <<= 1U)
	
	return u8Return;
}


/***************************************************************************//**
 * @brief
 * Switch the power on to the BMS pod.
 * 
 * @st_funcMD5		D0A7A5D65486B84F91C1390D6882133B
 * @st_funcID		LCCM650R0.FILE.005.FUNC.007
 */
void vATA6870_LOWLEVEL__PowerOn(void)
{
	M_LOCALDEF__LCCM650__POWER_ENABLE_LATCH(1U);
}

/***************************************************************************//**
 * @brief
 * Switch the power off control signal to the BMS pod 
 * 
 * @st_funcMD5		5E2B8A13F25C190740AB36DC429FFC0E
 * @st_funcID		LCCM650R0.FILE.005.FUNC.008
 */
void vATA6870_LOWLEVEL__PowerOff(void)
{
	M_LOCALDEF__LCCM650__POWER_ENABLE_LATCH(0U);
}

/***************************************************************************//**
 * @brief
 * Check the power available signal.
 * 
 * @return			1 = Power is on the BMS device\n
 *					0 = no power avail.
 * @st_funcMD5		A26A5127AD35DF7F7C6CBE88C04722A4
 * @st_funcID		LCCM650R0.FILE.005.FUNC.009
 */
Luint8 u8ATA6870_LOWLEVEL__Get_PowerAvail(void)
{
	Luint32 u32Test;
	Luint8 u8Return;

	u32Test = M_LOCALDEF__LCCM650__POWER_AVAIL_PORT();

	if(u32Test == 0U)
	{
		u8Return = 0U;
	}
	else
	{
		u8Return = 1U;
	}

	return u8Return;
}



#endif //#if C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */

/*lint +e506*/
/*lint +e774*/


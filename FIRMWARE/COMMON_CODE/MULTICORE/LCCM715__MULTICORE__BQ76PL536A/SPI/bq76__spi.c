/**
 * @file		BQ76__SPI.C
 * @brief		SPI Interface
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM715R0.FILE.006
 */

/**
 * @addtogroup MULTICORE
 * @{
*/
/**
 * @addtogroup BQ76
 * @ingroup MULTICORE
 * @{
*/
/**
 * @addtogroup BQ76__SPI
 * @ingroup BQ76
 * @{
*/
#include <MULTICORE/LCCM715__MULTICORE__BQ76PL536A/bq76.h>
#if C_LOCALDEF__LCCM715__ENABLE_THIS_MODULE == 1U

extern TS_BQ76__MAIN sBQ76;

//locals
void vBQ76_SPI__Set_Addresses(void);

/***************************************************************************//**
 * @brief
 * Init the SPI system
 * 
 * @st_funcMD5		FE8D7268E138C5C629636317DE96F3DA
 * @st_funcID		LCCM715R0.FILE.006.FUNC.001
 */
void vBQ76_SPI__Init(void)
{
	Luint8 u8Device;

	//chip select off
	M_LOCALDEF__LCCM715__LATCH__CS(1U);

	//software reset all devices
	vBQ76_SPI__Reset_All();

#ifndef WIN32
	vRM4_DELAYS__Delay_uS(50);
#endif
	//configure our addx stack
	vBQ76_SPI__Set_Addresses();
	
#ifndef WIN32
	vRM4_DELAYS__Delay_uS(10);
#endif
	//Configure all the cells to sample each run
	for(u8Device = 0U; u8Device < C_LOCALDEF__LCCM715__NUM_DEVICES; u8Device++)
	{
		//convert all 6 cells
		//can or 0x40 to switch the ADC on always if needed.
		vBQ76_SPI__Write_U8(u8Device + 1U, BQ76_REG__ADC_CONTROL, 0x05U);
		
#ifndef WIN32
		vRM4_DELAYS__Delay_uS(10);
#endif

	}
	
}

/***************************************************************************//**
 * @brief
 * Process any SPI subsystems
 * 
 * @st_funcMD5		6E2E95BD60B1DA9E00CCE23F1296632F
 * @st_funcID		LCCM715R0.FILE.006.FUNC.002
 */
void vBQ76_SPI__Process(void)
{
	//do nothing.
}

/***************************************************************************//**
 * @brief
 * Reset all devices on the broadcast address
 * 
 * @st_funcMD5		61FF74D3EC4F1A5C329FF06B755CC96C
 * @st_funcID		LCCM715R0.FILE.006.FUNC.006
 */
void vBQ76_SPI__Reset_All(void)
{
	vBQ76_SPI__Write_U8(0x3FU, BQ76_REG__RESET, 0xA5U);
}

/***************************************************************************//**
 * @brief
 * Set all the addresses of devices on the bus
 * 
 * @st_funcMD5		9AD3C95638E48719DC5F2FE8A956CCD5
 * @st_funcID		LCCM715R0.FILE.006.FUNC.007
 */
void vBQ76_SPI__Set_Addresses(void)
{
	
	Luint8 u8Temp;
	Luint8 u8Counter;
	

	//loop through each device
	for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM715__NUM_DEVICES; u8Counter++)
	{


		//set addx 0 to addx n_1
		vBQ76_SPI__Write_U8(0, BQ76_REG__ADDX_CONTROL, u8Counter + 1U);
		
#ifndef WIN32
		vRM4_DELAYS__Delay_uS(10);
#endif

		//read it back.
		u8Temp = u8BQ76_SPI__Read_U8(u8Counter + 1U, BQ76_REG__ADDX_CONTROL);

		//todo, check that the device is avail
		if((u8Temp & 0x80U) != 0x80U)
		{
			//addx bit not set, error
			vSIL3_FAULTTREE__Set_Flag(&sBQ76.sDevice[u8Counter].sFaultFlags, C_LCCM715__DEVICE__FAULT_INDEX__00);
			vSIL3_FAULTTREE__Set_Flag(&sBQ76.sDevice[u8Counter].sFaultFlags, C_LCCM715__DEVICE__FAULT_INDEX__01);
		}
		else
		{
			//todo: check that we have the actual correct addx
		}

		//clear the AR bit of Alert status
		//it requires setting 0x80 and then 0x00 (two writes)
		vBQ76_SPI__Write_U8(u8Counter + 1U, BQ76_REG__ALERT_STATUS, 0x80U);

#ifndef WIN32
		vRM4_DELAYS__Delay_uS(10);
#endif

		//second write
		vBQ76_SPI__Write_U8(u8Counter + 1U, BQ76_REG__ALERT_STATUS, 0x00U);


	}//for(u8Counter = 0U; u8Counter < C_LOCALDEF__LCCM715__NUM_DEVICES; u8Counter++)
		
}


/***************************************************************************//**
 * @brief
 * Write a byte to a register
 * 
 * @param[in]		u8Value					The value to write
 * @param[in]		eReg					The register addx
 * @param[in]		u8DeviceAddx			The BQ76 device address (Must not be zero)
 * @st_funcMD5		E28EEC9D306AB58712AA3FC2286EA0B0
 * @st_funcID		LCCM715R0.FILE.006.FUNC.003
 */
void vBQ76_SPI__Write_U8(Luint8 u8DeviceAddx, TE_BQ76__REG_DEFS eReg, Luint8 u8Value)
{

#ifndef WIN32
	Luint8 u8Test;
	Luint8 u8CRC;
	Luint8 u8Buffer[3];

	
	u8Buffer[0] = u8DeviceAddx;

	//shift device addx over
	u8Buffer[0] <<= 1U;

	//LSB 1 = Write
	u8Buffer[0] |= 0x01U;


	u8Buffer[1] = (Luint8)eReg;
	u8Buffer[2] = u8Value;

	//we have a TCS_CLY of 3us min between consecutive transfers
	//apply here because we don't want to rely at the end
	vRM4_DELAYS__Delay_uS(3);

	//Chip Select
	M_LOCALDEF__LCCM715__LATCH__CS(0U);

	//Device Addx
	u8Test = M_LOCALDEF__LCCM715__SPI_TX_U8(u8Buffer[0]);

	//Register Addx
	u8Test = M_LOCALDEF__LCCM715__SPI_TX_U8(u8Buffer[1]);

	//Write Data
	u8Test = M_LOCALDEF__LCCM715__SPI_TX_U8(u8Buffer[2]);

	//compute the CRC
	u8CRC = u8BQ76_CRC__Compute(&u8Buffer[0], 3U);
	
	//CRC
	u8Test = M_LOCALDEF__LCCM715__SPI_TX_U8(u8CRC);

	//done
	M_LOCALDEF__LCCM715__LATCH__CS(1U);

#else
	//win32
#endif

}


/***************************************************************************//**
 * @brief
 * Read a byte from a register
 * 
 * @param[in]		eReg					The register address
 * @param[in]		u8DeviceAddx			The device addx (never 0)
 * @return			The register value
 * @st_funcMD5		902FC075958D200AFDF2CB0E663AD9A4
 * @st_funcID		LCCM715R0.FILE.006.FUNC.004
 */
Luint8 u8BQ76_SPI__Read_U8(Luint8 u8DeviceAddx, TE_BQ76__REG_DEFS eReg)
{
#ifndef WIN32
	Luint8 u8Test;
	Luint8 u8CRC;
	Luint8 u8Buffer[4];

	//we have a TCS_CLY of 3us min between consecutive transfers
	//apply here because we don't want to rely at the end
	vRM4_DELAYS__Delay_uS(3);

	//Chip Select
	M_LOCALDEF__LCCM715__LATCH__CS(0U);

	//shift device addx over
	u8DeviceAddx <<= 1U;

	//LSB 0 = Read
	u8DeviceAddx &= 0xFEU;

	//Device Addx
	u8Buffer[0] = M_LOCALDEF__LCCM715__SPI_TX_U8(u8DeviceAddx);

	//Register Addx
	u8Buffer[1] = M_LOCALDEF__LCCM715__SPI_TX_U8((Luint8)eReg);

	//Count
	u8Buffer[2] = M_LOCALDEF__LCCM715__SPI_TX_U8(1U);

	//read
	u8Buffer[3] = M_LOCALDEF__LCCM715__SPI_TX_U8(0x00U);

	//CRC
	u8CRC = M_LOCALDEF__LCCM715__SPI_TX_U8(0x00U);

	//done
	M_LOCALDEF__LCCM715__LATCH__CS(1U);

	//check CRC
	u8Test = u8BQ76_CRC__Compute(&u8Buffer[0], 4U);
	if(u8Test != u8CRC)
	{
		//fault
	}
	else
	{
		//ok
	}

	//return with last read
	return u8Buffer[3];
#else
	//win32
	return 0U;
#endif
}


/***************************************************************************//**
 * @brief
 * Read a byte array
 * 
 * @param[in]		u8Length				Total length of data read
 * @param[in]		pu8Data					Pointer to the recive buffer
 * @param[in]		eReg					The starting register adds
 * @param[in]		u8DeviceAddx			Device addx
 * @st_funcMD5		09F9689D7FB58B23324E170182349B0B
 * @st_funcID		LCCM715R0.FILE.006.FUNC.005
 */
void vBQ76_SPI__Read_U8_Array(Luint8 u8DeviceAddx, TE_BQ76__REG_DEFS eReg, Luint8 *pu8Data, Luint8 u8Length)
{
#ifndef WIN32
	Luint8 u8Test;
	Luint8 u8Counter;
	Luint8 u8CRC;

	//we have a TCS_CLY of 3us min between consecutive transfers
	//apply here because we don't want to rely at the end
	vRM4_DELAYS__Delay_uS(3);

	//Chip Select
	M_LOCALDEF__LCCM715__LATCH__CS(0U);

	//shift device addx over
	u8DeviceAddx <<= 1U;

	//LSB 0 = Read
	u8DeviceAddx &= 0xFEU;

	//Device Addx
	u8Test = M_LOCALDEF__LCCM715__SPI_TX_U8(u8DeviceAddx);

	//Register Addx
	u8Test = M_LOCALDEF__LCCM715__SPI_TX_U8((Luint8)eReg);

	//Count
	u8Test = M_LOCALDEF__LCCM715__SPI_TX_U8(u8Length);

	//read
	for(u8Counter = 0U; u8Counter < u8Length; u8Counter++)
	{
		pu8Data[u8Counter] = M_LOCALDEF__LCCM715__SPI_TX_U8(0x00U);
	}

	//read the CRC
	u8CRC = M_LOCALDEF__LCCM715__SPI_TX_U8(0x00U);

	//todo, check CRC

	//done
	M_LOCALDEF__LCCM715__LATCH__CS(1U);

#else
	//win32
#endif
}


#endif //#if C_LOCALDEF__LCCM715__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM715__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */


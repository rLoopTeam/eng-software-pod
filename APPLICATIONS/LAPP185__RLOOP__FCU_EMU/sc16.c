/**
 * @file		SC16.C
 * @brief		Main File
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 *				of companies, including Lockie Innovation Pty. Ltd (ACN 123 529 064) and
 *				Lockie Safety Systems Pty. Ltd (ACN 132 340 571).  This code may be distributed
 *				under a license from the Lockie Group of companies, and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright Lockie Innovation Pty Ltd 2003-2012, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2012, All Rights Reserved.
 * @st_fileID	LCCM487R0.FILE.001
 */

/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup SC16IS
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup SC16IS__CORE
 * @ingroup SC16IS
 * @{ */
 
#include "sc16.h"
#if C_LOCALDEF__LCCM487__ENABLE_THIS_MODULE == 1U

struct _strSC16 sSC16;

//locals
void vSC16__Tx_Start(Luint8 u8DeviceIndex);

/***************************************************************************//**
 * @brief
 * Initiates the module
 * 
 * @param[in]		u8DeviceIndex		Defines the Index Number of the Device you want to configure
 *										DeivceIndex can take on as many values as there are chip 
 *										select lines
 * @st_funcMD5		4590317F16E9A4F8477445442BCD2831
 * @st_funcID		LCCM487R0.FILE.001.FUNC.001
 */
void vSC16__Init(Luint8 u8DeviceIndex)
{
	Luint8 u8Test;

	if(u8DeviceIndex < C_LOCALDEF__LCCM487__NUM_DEVICES)
	{

		//init the low level systems.
		vSC16_LOWLEVEL__Init(u8DeviceIndex);

		//setup the interrupt system
		vSC16_INT__Init(u8DeviceIndex);

		//int the fault flags
		vFAULTTREE__Init(&sSC16.sDevice[u8DeviceIndex].sFaultFlags);

		//init the FIFO with the given depth
		vSOFTFIFO__Init(&sSC16.sDevice[u8DeviceIndex].sRawSPI_FIFO.sSPIFIFO, C_SC16__MAX_RAW_SPI_FIFO_DEPTH);

		//init the TxFIFO with the given depth
		vSOFTFIFO__Init(&sSC16.sDevice[u8DeviceIndex].sSPI_TxFIFO.sSPITXFIFO, C_SC16__MAX_SPI_TXFIFO_DEPTH);

		//init Flags
		sSC16.sDevice[u8DeviceIndex].u8NewDataAvalible = 0U;

		//no interrupt has occurred
		sSC16.sDevice[u8DeviceIndex].u8ISRFlag = 0U;

		sSC16.sDevice[u8DeviceIndex].u8Interrupt = 0U;

		sSC16.sDevice[u8DeviceIndex].u8TxCounter = 0U;

		sSC16.sDevice[u8DeviceIndex].u8TxSwitchCounter = 0U;

		//todo
		//do a quick read of the device to check that we can comm with it.
		u8Test = u8SC16_REGISTERS__Read_Register(u8DeviceIndex, 0x03U, 0x07U, 0x00U, 0x03U);

		//check for the default value
		if(u8Test != 0x1D)
		{
			//fault
		}
		else
		{
			//good to go.
		}

	}
	else
	{
		//error
	}

}


/***************************************************************************//**
 * @brief
 * Main Process loop
 * 
 * @param[in]		u8DeviceIndex		Defines the Index Number of the Device you want to configure
 *										DeivceIndex can take on as many values as there are chip 
 *										select lines
 * @st_funcMD5		4A91E9E513AB3E0EEA6CD59A32A3AFA0
 * @st_funcID		LCCM487R0.FILE.001.FUNC.002
 */
void vSC16__Process(Luint8 u8DeviceIndex)
{

	//process any interrupts that may have occurred.
	vSC16_INT__Process(u8DeviceIndex);

	if(u8DeviceIndex < C_LOCALDEF__LCCM487__NUM_DEVICES)
	{
		//check if we have any new data via the interrupt flag
		if(sSC16.sDevice[u8DeviceIndex].u8Interrupt == 1U)
		{
			// clear interrupt once we have handled it
			sSC16.sDevice[u8DeviceIndex].u8Interrupt = 0U;

			// we have an interrupt so handle it
			vSC16_INT__Handle_ISR(u8DeviceIndex);

		}
		else
		{
			// no new data so no need to do anything
		}
	}
	else
	{
		//error
	}
}


/***************************************************************************//**
 * @brief
 * Returns the value of the New Data Available flag
 * 
 * @st_funcMD5		F2437712FCE1C1887BF0BE175FEBC378
 * @param[in]		u8DeviceIndex		## Desc ##
 * @st_funcMD5		9F1EC58D39F8DF54B80BD64AA9F52FA0
 * @st_funcID		LCCM487R0.FILE.001.FUNC.003
 */
Luint8 u8SC16__Get_NewDataAvalible(Luint8 u8DeviceIndex)
{
	return sSC16.sDevice[u8DeviceIndex].u8NewDataAvalible;
}


/***************************************************************************//**
 * @brief
 * Returns the value of the Error flag
 * 
 * @st_funcMD5		AAB8F6C9F8892C5BA32C723DB31A5F0C
 * @param[in]		u8DeviceIndex		## Desc ##
 * @st_funcMD5		299009ECF772FA0BD641F28507DB8E6C
 * @st_funcID		LCCM487R0.FILE.001.FUNC.004
 */
Luint8 u8SC16__Get_ErrorFlagStatus(Luint8 u8DeviceIndex)
{
	return sSC16.sDevice[u8DeviceIndex].u8ErrorFlag;
}

/***************************************************************************//**
 * @brief
 * Clears the value of the Error flag
 * 
 * @st_funcMD5		0FF0CE050AFF52DC352C80E64B57E943
 * @param[in]		u8DeviceIndex		## Desc ##
 * @st_funcMD5		B73833802D6E9735C617B9289D947E9B
 * @st_funcID		LCCM487R0.FILE.001.FUNC.005
 */
void vSC16__Clear_ErrorFlagStatus(Luint8 u8DeviceIndex)
{
	if(u8DeviceIndex < C_LOCALDEF__LCCM487__NUM_DEVICES)
	{
		sSC16.sDevice[u8DeviceIndex].u8ErrorFlag = 0U;
	}
	else
	{
		//error
	}
}

/***************************************************************************//**
 * @brief
 * Clears the value of the New Data Available flag
 * 
 * @st_funcMD5		AF598DBF0F6B769AFBC1DBD657AE471A
 * @param[in]		u8DeviceIndex		## Desc ##
 * @st_funcMD5		1F7A10F1965CA924ECDD294F38A52855
 * @st_funcID		LCCM487R0.FILE.001.FUNC.006
 */
void vSC16__Clear_NewDataAvalible(Luint8 u8DeviceIndex)
{
	if(u8DeviceIndex < C_LOCALDEF__LCCM487__NUM_DEVICES)
	{
		sSC16.sDevice[u8DeviceIndex].u8NewDataAvalible = 0U;
	}
	else
	{
		//fall on
	}
		
}


/***************************************************************************//**
 * @brief
 * Returns 1 if we can transmit a new byte
 * 
 * @st_funcMD5		4A9CA29245E31DDF129E743CEF9AFE08
 * @param[in]		u8DeviceIndex		## Desc ##
 * @st_funcMD5		2447A70F0E8D0E60182D91E4A7203E7D
 * @st_funcID		LCCM487R0.FILE.001.FUNC.007
 */
Luint8 u8SC16_USER__Is_TxAvail(Luint8 u8DeviceIndex)
{
	//todo, manage the Tx fill level

	return 1;
}

/***************************************************************************//**
 * @brief
 * Transmit a byte of data that in on the FIFO's
 * 
 * @param[in]		u8DeviceIndex			The bus device index
 * @st_funcMD5		357CE555BAB5EC40378DC93BD64232F6
 * @st_funcID		LCCM487R0.FILE.001.FUNC.008
 */
void vSC16__Tx_Start(Luint8 u8DeviceIndex)
{
	// init varibles
	Luint8 u8loopcounter;
	Luint8 u8ByteCounter;
	Luint8 u8TempArray[8];
	Lint16 s16Return;

	if(u8DeviceIndex < C_LOCALDEF__LCCM487__NUM_DEVICES)
	{
	
		// pop data off the Tx SW FIFO and put into an array of four byte to send out
		s16Return = s16SOFTFIFO__Pop(&sSC16.sDevice[u8DeviceIndex].sSPI_TxFIFO.sSPITXFIFO);
		if(s16Return >= 0)
		{

			vSC16_FIFO__Reset_Tx_FIFO(u8DeviceIndex, 1U);

			vSC16_LOWLEVEL__FIFO_Write(u8DeviceIndex,
										(Luint8 *)&sSC16.sDevice[u8DeviceIndex].sSPI_TxFIFO.u8Packet[(Luint16)s16Return][0],
										sSC16.sDevice[u8DeviceIndex].sSPI_TxFIFO.u8PacketLength[(Luint16)s16Return]);

		}
		else
		{

			// no data in FIFO
			// so why was this funtion called
			//TODO: error checking
		}
	}
	else
	{
		//big error
	}
}

/***************************************************************************//**
 * @brief
 * Returns 1 if there is at-least one byte avail
 * 
 * @st_funcMD5		97BFD394BEC327B7B85EA314000E1E78
 * @param[in]		u8DeviceIndex		## Desc ##
 * @st_funcMD5		5E8BA63028001D488A6400E4D861E76B
 * @st_funcID		LCCM487R0.FILE.001.FUNC.009
 */
Luint8 u8SC16_USER__Get_ByteAvail(Luint8 u8DeviceIndex)
{
	Luint8 u8Test;
	Luint8 u8Return;
	
	u8Test = u8SOFTFIFO__Is_Empty(&sSC16.sDevice[u8DeviceIndex].sRawSPI_FIFO.sSPIFIFO);
	if(u8Test == 1U)
	{
		u8Return = 0U;
	}
	else
	{
		u8Return = 1U;
	}

	return u8Return;
}


/***************************************************************************//**
 * @brief
 * Only if a byte is available, return the next byte
 * 
 * @st_funcMD5		CDD67B7C73992163B888D904591CEB45
 * @param[in]		u8DeviceIndex		## Desc ##
 * @st_funcMD5		62C2C2F6F17FF35D48C2CF65DEF56A99
 * @st_funcID		LCCM487R0.FILE.001.FUNC.010
 */
Luint8 u8SC16_USER__Get_Byte(Luint8 u8DeviceIndex)
{
	Lint16 s16Return;
	Luint8 u8Return;

	if(u8DeviceIndex < C_LOCALDEF__LCCM487__NUM_DEVICES)
	{
	
		//the FIFO has some data in it
		s16Return = s16SOFTFIFO__Pop(&sSC16.sDevice[u8DeviceIndex].sRawSPI_FIFO.sSPIFIFO);
		if(s16Return >= 0)
		{
			// pass each byte into the Rx Byte function to process incoming data
			u8Return = sSC16.sDevice[u8DeviceIndex].sRawSPI_FIFO.u8Character[(Luint16)s16Return];

		}//if(s16Return >= 0)
		else
		{
			//there is some issue, but nothing we can do about it
			u8Return = 0U;
		}
	}
	else
	{
		//error
		u8Return = 0U;
	}
	
	return u8Return;
}


/***************************************************************************//**
 * @brief
 * Transmit a byte array of data
 * 
 * @param[in]		u8ArrayLength			Length of array
 * @param[in]		pu8Data*				Pointer to the data
 * @param[in]		u8DeviceIndex			Bus Index
 * @st_funcMD5		95C1E8B225EF0DE81E4803E7B37484C8
 * @st_funcID		LCCM487R0.FILE.001.FUNC.011
 */
void vSC16__Tx_ByteArray(Luint8 u8DeviceIndex, Luint8 *pu8Data, Luint8 u8ArrayLength)
{
	Luint8 u8TxAvail;
	Lint16 s16Return;
	Luint8 u8TempCounter;

	if(u8DeviceIndex < C_LOCALDEF__LCCM487__NUM_DEVICES)
	{
		// check if the Tx FIFO is readdy to send data
		u8TxAvail = u8SC16_USER__Is_TxAvail(u8DeviceIndex);

		// for now make sure that the string length dosnt exceed 64 bytes
		if(u8ArrayLength > 64)
		{
			//todo
			// set the u8TxAvali flag to 0 for now so we cant cause an error in the FIFO
			u8TxAvail = 0U;
		}
		else
		{
			// do nothing and let the data continue onto the FIFO
		}

		if(u8TxAvail == 1U)
		{

			// push data onto a SW FIFO
			s16Return = s16SOFTFIFO__Push(&sSC16.sDevice[u8DeviceIndex].sSPI_TxFIFO.sSPITXFIFO);
			if(s16Return >= 0)
			{
				// save the length of the packet
				sSC16.sDevice[u8DeviceIndex].sSPI_TxFIFO.u8PacketLength[(Luint8)s16Return] = u8ArrayLength;

				// push the packet onto the FIFO
				for(u8TempCounter = 0U; u8TempCounter < u8ArrayLength; u8TempCounter++)
				{
					sSC16.sDevice[u8DeviceIndex].sSPI_TxFIFO.u8Packet[(Luint8)s16Return][u8TempCounter] = pu8Data[u8TempCounter];
				}

				// then call the The Byte fucntion
				vSC16__Tx_Start(u8DeviceIndex);

			}
			else
			{
				//no more space on our FIFO;

			}

		}
		else
		{
			// if the Tx FIFO isnt readdy
			// dont send any more data yet

		}
	}
	else
	{
		//error
	}
}

#endif //#if C_LOCALDEF__LCCM487__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM487__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */


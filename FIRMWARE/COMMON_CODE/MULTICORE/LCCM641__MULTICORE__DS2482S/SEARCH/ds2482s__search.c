/**
 * @file		DS2482S__SEARCH.C
 * @brief		Implements one wire search functions
 * @note		https://www.maximintegrated.com/en/app-notes/index.mvp/id/187#
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM641R0.FILE.008
 */
/**
 * @addtogroup MULTICORE
 * @{ */
/**
 * @addtogroup DS2482S
 * @ingroup MULTICORE
 * @{ */
/**
 * @addtogroup DS2482S__SEARCH
 * @ingroup DS2482S
 * @{ */


#include "../ds2482s.h"
#if C_LOCALDEF__LCCM641__ENABLE_THIS_MODULE == 1U

extern struct _strDS2482S sDS2482S;

//locals
static Lint16 s16DS2482S_SEARCH__Search(Luint8 u8DeviceIndex);


/***************************************************************************//**
 * @brief
 * Search for the first device on the bus
 * 
 * @note
 * The 'FIRST' operation is to search on the 1-Wire for the first device. 
 * This is performed by setting LastDiscrepancy, LastFamilyDiscrepancy, 
 * and LastDeviceFlag to zero and then doing the search. 
 * The resulting ROM number can then be read from the ROM_NO register. 
 * If no devices are present on the 1-Wire the reset sequence does not detect a presence and the search is aborted.
 *
 * Maxim's 1-Wire devices each have a 64-bit unique registration number in read-only memory ROM
 * that is used to address them individually by a 1-Wire master in a 1-Wire network. If the ROM numbers of
 * the slave devices on the 1-Wire network are not known, then they can be discovered by using a search algorithm.
 * This document explains the search algorithm in detail and provides an example implementation for rapid integration.
 * This algorithm is valid for all current and future devices that feature a 1-Wire interface.
 *
 * @param[in]		*pu8Addx				Pointer to hold returned addx
 * @param[in]		u8DeviceIndex			I2C Device index
 * @return			1 = Device Found\n
 * 					0 = No device found and no bus error\n
 * 					-ve = error
 * @st_funcMD5		8F7C8910A44EAB7D120A56C093DBE111
 * @st_funcID		LCCM641R0.FILE.008.FUNC.001
 */
Lint16 s16DS2482S_SEARCH__SearchFirstDevice(Luint8 u8DeviceIndex, Luint8 *pu8Addx)
{
	Lint16 s16Return;

	if(u8DeviceIndex < C_LOCALDEF__LCCM641__NUM_DEVICS)
	{
		//setup intial conditions
		sDS2482S.sSearch[u8DeviceIndex].u8LastDiscrepancy = 0U;
		sDS2482S.sSearch[u8DeviceIndex].u8LastDeviceFlag = 0U;
		sDS2482S.sSearch[u8DeviceIndex].u8LastFamilyDiscrepancy = 0U;

		//do the search
		s16Return = s16DS2482S_SEARCH__Search(u8DeviceIndex);
		if(s16Return > 0)
		{
			//order the address
			pu8Addx[0] = sDS2482S.sSearch[u8DeviceIndex].u8ROM_SerialNumber[0];
			pu8Addx[1] = sDS2482S.sSearch[u8DeviceIndex].u8ROM_SerialNumber[1];
			pu8Addx[2] = sDS2482S.sSearch[u8DeviceIndex].u8ROM_SerialNumber[2];
			pu8Addx[3] = sDS2482S.sSearch[u8DeviceIndex].u8ROM_SerialNumber[3];
			pu8Addx[4] = sDS2482S.sSearch[u8DeviceIndex].u8ROM_SerialNumber[4];
			pu8Addx[5] = sDS2482S.sSearch[u8DeviceIndex].u8ROM_SerialNumber[5];
			pu8Addx[6] = sDS2482S.sSearch[u8DeviceIndex].u8ROM_SerialNumber[6];
			pu8Addx[7] = sDS2482S.sSearch[u8DeviceIndex].u8ROM_SerialNumber[7];

		}
		else
		{
			//fall on with error code
		}
	}
	else
	{
		//log the fault

		s16Return = -1;
	}



	return s16Return;

}

/***************************************************************************//**
 * @brief
 * Search for subsequent devices
 * 
 * @note
 * The 'NEXT' operation is to search on the 1-Wire for the next device. 
 * This search is usually performed after a 'FIRST' operation or another 'NEXT' operation. 
 * It is performed by leaving the state unchanged from the previous search and performing another search. 
 * The resulting ROM number can then be read from the ROM_NO register. 
 * If the previous search was the last device on the 1-Wire then the result is FALSE and the 
 * condition is set to execute a 'FIRST' with the next call of the search algorithm.
 *
 * @param[in]		*pu8Addx				Pointer to hold returned addx
 * @param[in]		u8DeviceIndex			I2C Device index
 * @return			1 = Device Found\n
 * 					0 = No device found and no bus error\n
 * 					-ve = error
 * @st_funcMD5		EB7C0E617DEA9CB709D476449BB1054D
 * @st_funcID		LCCM641R0.FILE.008.FUNC.002
 */
Lint16 s16DS2482S_SEARCH__SearchNextDevice(Luint8 u8DeviceIndex, Luint8 *pu8Addx)
{
	Lint16 s16Return;

	if(u8DeviceIndex < C_LOCALDEF__LCCM641__NUM_DEVICS)
	{
		//do the search
		s16Return = s16DS2482S_SEARCH__Search(u8DeviceIndex);
		if(s16Return > 0)
		{
			//order the address
			pu8Addx[0] = sDS2482S.sSearch[u8DeviceIndex].u8ROM_SerialNumber[0];
			pu8Addx[1] = sDS2482S.sSearch[u8DeviceIndex].u8ROM_SerialNumber[1];
			pu8Addx[2] = sDS2482S.sSearch[u8DeviceIndex].u8ROM_SerialNumber[2];
			pu8Addx[3] = sDS2482S.sSearch[u8DeviceIndex].u8ROM_SerialNumber[3];
			pu8Addx[4] = sDS2482S.sSearch[u8DeviceIndex].u8ROM_SerialNumber[4];
			pu8Addx[5] = sDS2482S.sSearch[u8DeviceIndex].u8ROM_SerialNumber[5];
			pu8Addx[6] = sDS2482S.sSearch[u8DeviceIndex].u8ROM_SerialNumber[6];
			pu8Addx[7] = sDS2482S.sSearch[u8DeviceIndex].u8ROM_SerialNumber[7];

		}
		else
		{
			//fall on with error code
		}
	}
	else
	{
		//log the error
		s16Return = -1;
	}


	return s16Return;

}

/***************************************************************************//**
 * @brief
 * Verify that a search device exists
 * 
 * @param[in]		*pu8Addx				Pointer to address to verify
 * @param[in]		u8DeviceIndex			I2C device index
 * @st_funcMD5		7C80DF04ACBBB568FD976DC6C6BC4E4E
 * @st_funcID		LCCM641R0.FILE.008.FUNC.004
 */
Lint16 s16DS2482S_SEARCH__Verify(Luint8 u8DeviceIndex, const Luint8 *pu8Addx)
{

#if 0
//TODO: Cleanup dallas App Note.
//Note: Public Code.
//dallas app note.
unsigned char rom_backup[8];
   int i,rslt,ld_backup,ldf_backup,lfd_backup;

   // keep a backup copy of the current state
   for (i = 0; i < 8; i++)
      rom_backup[i] = ROM_NO[i];
   ld_backup = LastDiscrepancy;
   ldf_backup = LastDeviceFlag;
   lfd_backup = LastFamilyDiscrepancy;

   // set search to find the same device
   LastDiscrepancy = 64;
   LastDeviceFlag = FALSE;

   if (OWSearch())
   {
      // check if same device found
      rslt = TRUE;
      for (i = 0; i < 8; i++)
      {
         if (rom_backup[i] != ROM_NO[i])
         {
            rslt = FALSE;
            break;
         }
      }
   }
   else
     rslt = FALSE;

   // restore the search state 
   for (i = 0; i < 8; i++)
      ROM_NO[i] = rom_backup[i];
   LastDiscrepancy = ld_backup;
   LastDeviceFlag = ldf_backup;
   LastFamilyDiscrepancy = lfd_backup;

   // return the result of the verify
   return rslt;
#endif 

   return 0;

}


/***************************************************************************//**
 * @brief
 * Search the 1-wire bus and return the first address.
 * 
 * @param[in]		u8DeviceIndex				Device index on the bus
 * @return			1 = Device Found\n
 * 					0 = No device found and no bus error\n
 * 					-ve = error
 * @st_funcMD5		B439FB4C86E8B041082AC6AB968AB9DC
 * @st_funcID		LCCM641R0.FILE.008.FUNC.003
 */
Lint16 s16DS2482S_SEARCH__Search(Luint8 u8DeviceIndex)
{
	/*lint -e934*/
	//Note 934: Taking address of near auto variable [MISRA 2004 Rule 1.2]
	/*lint -e960*/
	//Violates MISRA 2004 Required Rule 10.5, Operators '~' and '<<' require recasting to underlying type for sub-integers

	Lint16 s16Return;
	Luint8 u8Test;
	Luint8 u8Temp;
	Luint8 u8Status;

	//one wire app note specifics

	/** The ROM bit number 1 to 64 currently being searched */
	Luint8 u8ID_BitNumber;


	Luint8 last_zero;

	/** The index into the ROM serial number array that we are currently addressing */
	Luint8 u8ROM_Index;

	/** This is the first bit read in a bit search sequence.
	 * his bit is the AND of all of the id_bit_number bits of the
	 * devices that are still participating in the search
	 */
	Luint8 u8IDBit;

	/** The complement of the ID Bit. This bit is the AND complement of all of the id_bit_number bits of the
	 * devices that are still participating in the search
	 */
	Luint8 u8ComplementIDBit;

	/** Used to mask off the current working bit in the ROM byte */
	Luint8 u8ROM_ByteMask;

	/** Bit value indicating the direction of the search. All devices with this bit stay in the seearch
	 * and the rest go ito a wait state for a 1-wire reset */
	Luint8 u8SearchDirection;


	// initialize for search
	if(u8DeviceIndex < C_LOCALDEF__LCCM641__NUM_DEVICS)
	{
		/* Note that this document refers to the bit position in the ROM number as bit 1 least significant
		 * to bit 64 most significant. This convention was used instead of bit 0 to bit 63 for convenience,
		 * to allow initialization of discrepancy counters to 0 for later comparisons.
		 */
		u8ID_BitNumber = 1U;
		last_zero = 0U;
		u8ROM_Index = 0U;
		u8ROM_ByteMask = 1U;
		sDS2482S.sSearch[u8DeviceIndex].u8CRC8 = 0U;
		s16Return = 0;

		// if the last call was not the last one
		if(sDS2482S.sSearch[u8DeviceIndex].u8LastDeviceFlag == 0U)
		{
			//do a 1-wire reset, there may be devices on the bus, we can check this with the
			//return type.
			u8Temp = u8DS2482S_USER__1Wire_Reset(u8DeviceIndex);
			if(u8Temp == 1U)
			{
				//at least one device on bus

				//must not execute during 1-wire commands
				// 0 = not busy or success
				// 1 = timeout
				u8Test = u8DS2482S_DEVICE__Wait_Busy(u8DeviceIndex, &u8Status);
				if(u8Test == 0U)
				{

					//issue the search command = 0xF0U
					s16Return =  s16DS2482S_1WIRE__WriteByte(u8DeviceIndex, 0xF0U, 0U);
					if(s16Return >= 0)
					{

						//command sent now wait
						u8Test = u8DS2482S_DEVICE__Wait_Busy(u8DeviceIndex, &u8Status);
						if(u8Test == 0U)
						{

							// loop to do the search
							// loop until through all ROM bytes 0-7
							do
							{
								// read a bit and its complement
								/* Table 1. Bit Search Information
								 * Bit true 	Bit complement	 	Information Known
								 * 0 			0 					There are both 0s and 1s in the current bit position
								 * 									of the participating ROM numbers. This is a discrepancy.
								 * 0 			1 					There are only 0s in the bit of the participating ROM numbers.
								 * 1 			0 					There are only 1s in the bit of the participating ROM numbers.
								 * 1 			1 					No devices participating in search.
								 */
								s16Return = s16DS2482S_1WIRE__ReadBit(u8DeviceIndex, &u8IDBit);
								s16Return = s16DS2482S_1WIRE__ReadBit(u8DeviceIndex, &u8ComplementIDBit);

								// check for no devices on 1-wire
								if((u8IDBit == 1U) && (u8ComplementIDBit == 1U))
								{
									//No devices participating in search.
									break;

								}//if((u8IDBit == 1U) && (u8ComplementIDBit == 1U))
								else
								{
									// all devices coupled have 0 or 1
									if(u8IDBit != u8ComplementIDBit)
									{
										// bit write value for search
										u8SearchDirection = u8IDBit;

									}//if(u8IDBit != u8ComplementIDBit)
									else
									{
										// if this discrepancy if before the Last Discrepancy
										// on a previous next then pick the same as last time
										if(u8ID_BitNumber < sDS2482S.sSearch[u8DeviceIndex].u8LastDiscrepancy)
										{
											if((sDS2482S.sSearch[u8DeviceIndex].u8ROM_SerialNumber[u8ROM_Index] & u8ROM_ByteMask) > 0U)
											{
												u8SearchDirection = 1U;
											}
											else
											{
												u8SearchDirection = 0U;
											}

										}//if(u8ID_BitNumber < sDS2482S.sSearch.u8LastDiscrepancy)
										else
										{
											// if equal to last pick 1, if not then pick 0
											if(u8ID_BitNumber == sDS2482S.sSearch[u8DeviceIndex].u8LastDiscrepancy)
											{
												u8SearchDirection = 1U;
											}
											else
											{
												u8SearchDirection = 0U;
											}

										}//else if(u8ID_BitNumber < sDS2482S.sSearch.u8LastDiscrepancy)

										// if 0 was picked then record its position in LastZero
										if(u8SearchDirection == 0U)
										{
											last_zero = u8ID_BitNumber;

											// check for Last discrepancy in family
											if(last_zero < 9U)
											{
												sDS2482S.sSearch[u8DeviceIndex].u8LastFamilyDiscrepancy = last_zero;
											}
											else
											{
												//
											}
										}
										else
										{
											//
										}

									} //if(u8IDBit != u8ComplementIDBit)

									// set or clear the bit in the ROM byte rom_byte_number
									// with mask rom_byte_mask
									if(u8SearchDirection == 1U)
									{
										sDS2482S.sSearch[u8DeviceIndex].u8ROM_SerialNumber[u8ROM_Index] |= u8ROM_ByteMask;
									}
									else
									{
										sDS2482S.sSearch[u8DeviceIndex].u8ROM_SerialNumber[u8ROM_Index] &= ~u8ROM_ByteMask;
									}

									// serial number search direction write bit
									s16Return = s16DS2482S_1WIRE__WriteBit(u8DeviceIndex, u8SearchDirection, 0U);

									// increment the byte counter u8IDBitNumber
									// and shift the mask rom_byte_mask
									u8ID_BitNumber++;

									u8ROM_ByteMask <<= 1U;

									// if the mask is 0 then go to new SerialNum byte rom_byte_number and reset mask
									if(u8ROM_ByteMask == 0U)
									{
										u8ROM_Index++;
										u8ROM_ByteMask = 1U;
									}
									else
									{
										//
									}

								}//if((u8IDBit == 1U) && (u8ComplementIDBit == 1U))

							}while(u8ROM_Index < 8U);

							//perform the CRC.
							sDS2482S.sSearch[u8DeviceIndex].u8CRC8 = u8DS2482S_CRC__CRC8(&sDS2482S.sSearch[u8DeviceIndex].u8ROM_SerialNumber[0], 7U);

							// if the search was successful then
							if((u8ID_BitNumber == 65U) && (sDS2482S.sSearch[u8DeviceIndex].u8CRC8 != 0U))
							{
								// search successful so set LastDiscrepancy,LastDeviceFlag,search_result
								sDS2482S.sSearch[u8DeviceIndex].u8LastDiscrepancy = last_zero;

								// check for last device
								if(sDS2482S.sSearch[u8DeviceIndex].u8LastDiscrepancy == 0U)
								{
									sDS2482S.sSearch[u8DeviceIndex].u8LastDeviceFlag = 1U;
								}
								else
								{
									//
								}

								//success
								s16Return = 1;
							}
							else
							{
								//some error code
								s16Return = -2;
							}


						}
						else
						{
							//timeout has occurred
							s16Return = -1;
						}

					}
					else
					{
						//fall through with error code
					}
				}
				else
				{
					//we were busy, something went wrong
					s16Return = -1;
				}

			}
			else
			{
				sDS2482S.sSearch[u8DeviceIndex].u8LastDiscrepancy = 0U;
				sDS2482S.sSearch[u8DeviceIndex].u8LastDeviceFlag = 0U;
				sDS2482S.sSearch[u8DeviceIndex].u8LastFamilyDiscrepancy = 0U;

				//transaction fault or no devices on bus
				s16Return = -100;
			}

		}//if(sDS2482S.sSearch.LastDeviceFlag == 0U)
		else
		{
			//
			s16Return = -22;

		}//else if(sDS2482S.sSearch.LastDeviceFlag == 0U)

	}
	else
	{
		//log the error and fall on
		s16Return = -1;
	}

	return s16Return;
	/*lint +e934*/
	/*lint +e960*/

}



#endif //#if C_LOCALDEF__LCCM641__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM641__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */


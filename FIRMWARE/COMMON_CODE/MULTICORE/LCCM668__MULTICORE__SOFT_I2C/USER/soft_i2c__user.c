/*
 * soft_i2c__user.c
 *
 *  Created on: 25 Jan 2017
 *      Author: Lachlan
 */

#include "../soft_i2c.h"

void vSOFTI2C_USER__Init(void)
{
	vSOFTI2C__Init();
}

Lint16 s16SOFT_I2C_USER__TxByte(Luint8 u8DeviceAddx, Luint8 u8RegAddx, Luint8 u8Byte)
{
	Lint16 s16Return;
	Luint8 u8Read;
	Luint8 u8Temp;

	s16Return = 0;

	//generate the start conditino
	vSOFTI2C_LOWLEVEL__Generate_Start_Conidition();

	//write the device address
	u8Temp = u8DeviceAddx;
	u8Temp <<= 1U;
	vSOFTI2C_LOWLEVEL__TxByte(u8Temp);

	//check the ack status
	u8Read = u8SOFTI2C_LOWLEVEL__Check_Ack();
	//we don't actually care about slave addressing phase

	//write the register addx
	vSOFTI2C_LOWLEVEL__TxByte(u8RegAddx);

	//check the ack
	u8Read = u8SOFTI2C_LOWLEVEL__Check_Ack();
	if(u8Read != 0U)
	{
		s16Return = -1;
	}
	else
	{
		//keep going

		//send the value
		vSOFTI2C_LOWLEVEL__TxByte(u8Byte);

		//check the ack
		u8Read = u8SOFTI2C_LOWLEVEL__Check_Ack();
		if(u8Read != 0U)
		{
			s16Return = -2;
		}
		else
		{
			s16Return = 0;
		}
	}

	//gen a stop condition
	vSOFTI2C_LOWLEVEL__Generate_Stop_Condition();

	return s16Return;
}



Lint16 s16SOFT_I2C_USER__RxByte(Luint8 u8DeviceAddx, Luint8 u8RegAddx, Luint8 *pu8Byte)
{
	Lint16 s16Return;
	Luint8 u8Read;
	Luint8 u8Temp;

	s16Return = 0;

	//generate the start conditino
	vSOFTI2C_LOWLEVEL__Generate_Start_Conidition();

	//write the device address
	u8Temp = u8DeviceAddx;
	u8Temp <<= 1U;
	vSOFTI2C_LOWLEVEL__TxByte(u8Temp);

	//check the ack status
	u8Read = u8SOFTI2C_LOWLEVEL__Check_Ack();
	//we don't actually care about slave addressing phase

	//write the register addx
	vSOFTI2C_LOWLEVEL__TxByte(u8RegAddx);

	//check the ack
	u8Read = u8SOFTI2C_LOWLEVEL__Check_Ack();
	u8Read = 0U;
	if(u8Read != 0U)
	{
		s16Return = -1;
	}
	else
	{
		//keep going

		//gen a new start addx
		vSOFTI2C_LOWLEVEL__Generate_Start_Conidition();

		//write the device address again, but need to change the RW bit
		u8Temp = u8DeviceAddx;
		u8Temp <<= 1U;
		u8Temp |= 0x01U;
		vSOFTI2C_LOWLEVEL__TxByte(u8Temp);

		//do we want the ACK?
		u8Read = u8SOFTI2C_LOWLEVEL__Check_Ack();

		//do the reception
		*pu8Byte = u8SOFTI2C_LOWLEVEL__RxByte();

		//do a NACK
		u8Read = u8SOFTI2C_LOWLEVEL__Check_Nack();
		if(u8Read != 0U)
		{
			s16Return = -2;
		}
		else
		{
			s16Return = 0;
		}
	}

	//gen a stop condition
	vSOFTI2C_LOWLEVEL__Generate_Stop_Condition();

	return s16Return;
}


Lint16 s16SOFT_I2C_USER__RxByteArray(Luint8 u8DeviceAddx, Luint8 u8RegAddx, Luint8 *pu8Array, Luint16 u16Length)
{
	Lint16 s16Return;
	Luint8 u8Read;
	Luint16 u16Counter;
	Luint8 u8Temp;

	s16Return = 0;

	//generate the start conditino
	vSOFTI2C_LOWLEVEL__Generate_Start_Conidition();

	//write the device address
	u8Temp = u8DeviceAddx;
	u8Temp <<= 1U;
	vSOFTI2C_LOWLEVEL__TxByte(u8Temp);

	//check the ack status
	u8Read = u8SOFTI2C_LOWLEVEL__Check_Ack();
	//we don't actually care about slave addressing phase

	//write the register addx
	vSOFTI2C_LOWLEVEL__TxByte(u8RegAddx);

	//check the ack
	u8Read = u8SOFTI2C_LOWLEVEL__Check_Ack();
	if(u8Read != 0U)
	{
		s16Return = -1;
	}
	else
	{
		//keep going

		//gen a new start addx
		vSOFTI2C_LOWLEVEL__Generate_Start_Conidition();

		//write the device address again, but need to change the RW bit
		u8Temp = u8DeviceAddx;
		u8Temp <<= 1U;
		u8Temp |= 0x01U;
		vSOFTI2C_LOWLEVEL__TxByte(u8Temp);

		//do we want the ACK?
		u8Read = u8SOFTI2C_LOWLEVEL__Check_Ack();

		for(u16Counter = 0U; u16Counter < (u16Length - 1); u16Counter++)
		{

			//do the reception
			pu8Array[u16Counter] = u8SOFTI2C_LOWLEVEL__RxByte();

			//do a ACK
			u8Read = u8SOFTI2C_LOWLEVEL__Check_Ack();

		}//for(u16Counter = 0U; u16Couter < u16Length; u16Counter++)

		//final byte
		//do the reception
		pu8Array[(u16Length - 1)] = u8SOFTI2C_LOWLEVEL__RxByte();

		//do a NACK
		u8Read = u8SOFTI2C_LOWLEVEL__Check_Nack();
		if(u8Read != 0U)
		{
			s16Return = -2;
		}
		else
		{
			s16Return = 0;
		}
	}

	//gen a stop condition
	vSOFTI2C_LOWLEVEL__Generate_Stop_Condition();

	return s16Return;
}



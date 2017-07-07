/*
 * soft_i2c__lowlevel.c
 *
 *  Created on: 25 Jan 2017
 *      Author: Lachlan
 */

#include "../soft_i2c.h"

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

#define C_SDA_PIN	25U
#define C_SCL_PIN	27U

//locals

void vSOFTI2C_LOWLEVEL__Generate_Delay(void);
void vSOFTI2C_LOWLEVEL__Set_SCL_Hi(void);
void vSOFTI2C_LOWLEVEL__Set_SDA_Hi(void);
void vSOFTI2C_LOWLEVEL__Set_SCL_Lo(void);
void vSOFTI2C_LOWLEVEL__Set_SDA_Lo(void);
void vSOFTI2C_LOWLEVEL__Generate_ClockPulse(void);


void vSOFTI2C_LOWLEVEL__Init(void)
{
	vRM4_N2HET_PINS__Set_PinDirection_Input(N2HET_CHANNEL__1, C_SDA_PIN);
	vRM4_N2HET_PINS__Set_PinDirection_Input(N2HET_CHANNEL__1, C_SCL_PIN);
}

//implement the I2C delay for bit timing
void vSOFTI2C_LOWLEVEL__Generate_Delay(void)
{
	vRM4_DELAYS__Delay_uS(200);
}

void vSOFTI2C_LOWLEVEL__Set_SCL_Hi(void)
{
	vRM4_N2HET_PINS__Set_PinDirection_Input(N2HET_CHANNEL__1, C_SCL_PIN);
	vSOFTI2C_LOWLEVEL__Generate_Delay();
}

void vSOFTI2C_LOWLEVEL__Set_SDA_Hi(void)
{
	vRM4_N2HET_PINS__Set_PinDirection_Input(N2HET_CHANNEL__1, C_SDA_PIN);
	vSOFTI2C_LOWLEVEL__Generate_Delay();
}

void vSOFTI2C_LOWLEVEL__Set_SCL_Lo(void)
{
	vRM4_N2HET_PINS__Set_PinLow(N2HET_CHANNEL__1, C_SCL_PIN);
	vRM4_N2HET_PINS__Set_PinDirection_Output(N2HET_CHANNEL__1, C_SCL_PIN);
	vSOFTI2C_LOWLEVEL__Generate_Delay();
}

void vSOFTI2C_LOWLEVEL__Set_SDA_Lo(void)
{
	vRM4_N2HET_PINS__Set_PinLow(N2HET_CHANNEL__1, C_SDA_PIN);
	vRM4_N2HET_PINS__Set_PinDirection_Output(N2HET_CHANNEL__1, C_SDA_PIN);
	vSOFTI2C_LOWLEVEL__Generate_Delay();
}

//generate a start condition
void vSOFTI2C_LOWLEVEL__Generate_Start_Conidition(void)
{
	vSOFTI2C_LOWLEVEL__Set_SDA_Hi();
	vSOFTI2C_LOWLEVEL__Set_SCL_Hi();
	vSOFTI2C_LOWLEVEL__Generate_Delay();
	vSOFTI2C_LOWLEVEL__Set_SDA_Lo();
	vSOFTI2C_LOWLEVEL__Generate_Delay();
	vSOFTI2C_LOWLEVEL__Set_SCL_Lo();
	vSOFTI2C_LOWLEVEL__Generate_Delay();
}

//generate a stop condition
void vSOFTI2C_LOWLEVEL__Generate_Stop_Condition(void)
{
	vSOFTI2C_LOWLEVEL__Set_SDA_Lo();
	vSOFTI2C_LOWLEVEL__Generate_Delay();
	vSOFTI2C_LOWLEVEL__Set_SCL_Hi();
	vSOFTI2C_LOWLEVEL__Generate_Delay();
	vSOFTI2C_LOWLEVEL__Set_SDA_Hi();
	vSOFTI2C_LOWLEVEL__Generate_Delay();
}

//generate a clock pulse
void vSOFTI2C_LOWLEVEL__Generate_ClockPulse(void)
{
	vSOFTI2C_LOWLEVEL__Set_SCL_Hi();
	vSOFTI2C_LOWLEVEL__Generate_Delay();
	vSOFTI2C_LOWLEVEL__Set_SCL_Lo();
}

//write a byte on the bus
void vSOFTI2C_LOWLEVEL__TxByte(Luint8 u8Value)
{
	Luint8 u8Counter;

	//go through each bit
	for(u8Counter = 0U; u8Counter < 8U; u8Counter++)
	{

		if(bitRead(u8Value, (7U - u8Counter)))
		{
			vSOFTI2C_LOWLEVEL__Set_SDA_Hi();
		}
		else
		{
			vSOFTI2C_LOWLEVEL__Set_SDA_Lo();
		}

		//clock the data out.
		vSOFTI2C_LOWLEVEL__Generate_ClockPulse();

	}//for(u8Counter = 0; u8Counter < 8; u8Counter++)
}

Luint8 u8SOFTI2C_LOWLEVEL__Read_Bit(void)
{
	Luint8 u8Read;

	//clock hi
	vSOFTI2C_LOWLEVEL__Set_SCL_Hi();

	//read the value of the data pin
	u8Read = u8RM4_N2HET_PINS__Get_Pin(N2HET_CHANNEL__1, C_SDA_PIN);

	vSOFTI2C_LOWLEVEL__Generate_Delay();

	//clock to low
	vSOFTI2C_LOWLEVEL__Set_SCL_Lo();

	return u8Read;
}

Luint8 u8SOFTI2C_LOWLEVEL__RxByte(void)
{
	Luint8 u8Counter;
	Luint8 out_byte = 0;

	vSOFTI2C_LOWLEVEL__Set_SDA_Hi();


	for(u8Counter = 0; u8Counter < 8; u8Counter++)
	{
		vSOFTI2C_LOWLEVEL__Generate_Delay();
		bitWrite(out_byte, 7 - u8Counter, u8SOFTI2C_LOWLEVEL__Read_Bit());
	}

	return out_byte;
}

/**
 * Return 0 if ACK was received, else 1
 */
Luint8 u8SOFTI2C_LOWLEVEL__Check_Ack(void)
{
	Luint8 u8Read;
	Luint8 u8Return;

	//sda pin to high
	vSOFTI2C_LOWLEVEL__Set_SDA_Hi();

	u8Read = u8SOFTI2C_LOWLEVEL__Read_Bit();
	if(u8Read == 0U)
	{
		u8Return = 0U;
	}
	else
	{
		u8Return = 1U;
	}

	return u8Return;
}

/**
 * Return 0 if NACK was received, else 1
 */
Luint8 u8SOFTI2C_LOWLEVEL__Check_Nack(void)
{
	Luint8 u8Read;
	Luint8 u8Return;

	//set the SDA high
	vSOFTI2C_LOWLEVEL__Set_SDA_Hi();

	u8Read = u8SOFTI2C_LOWLEVEL__Read_Bit();
	if(u8Read == 1U)
	{
		u8Return = 0U;
	}
	else
	{
		u8Return = 1U;
	}

	return u8Return;
}








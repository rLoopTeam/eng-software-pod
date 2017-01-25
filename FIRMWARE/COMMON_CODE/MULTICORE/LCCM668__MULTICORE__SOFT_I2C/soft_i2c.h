#ifndef _SOFT_I2C_H_
#define _SOFT_I2C_H_

#include <localdef.h>


	//function protos
	void vSOFTI2C_USER__Init(void);
	Lint16 s16SOFT_I2C_USER__TxByte(Luint8 DeviceAddx, Luint8 u8RegAddx, Luint8 u8Byte);
	Lint16 s16SOFT_I2C_USER__RxByte(Luint8 u8DeviceIndex, Luint8 u8RegAddx, Luint8 *pu8Byte);
	Lint16 s16SOFT_I2C_USER__RxByteArray(Luint8 u8DeviceIndex, Luint8 u8RegAddx, Luint8 *pu8Array, Luint16 u16Length);


	//lowlevel
	void vSOFTI2C_LOWLEVEL__Init(void);
	void vSOFTI2C_LOWLEVEL__Generate_Start_Conidition(void);
	void vSOFTI2C_LOWLEVEL__Generate_Stop_Condition(void);
	void vSOFTI2C_LOWLEVEL__TxByte(Luint8 u8Value);
	Luint8 u8SOFTI2C_LOWLEVEL__RxByte(void);
	Luint8 u8SOFTI2C_LOWLEVEL__Check_Ack(void);
	Luint8 u8SOFTI2C_LOWLEVEL__Check_Nack(void);

	void vSOFTI2C__Init(void);
	void vSOFTI2C__Process(void);

#endif //_SOFT_I2C_H_

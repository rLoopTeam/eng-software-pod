/**
 * @file		eeprom_params.h
 * @brief		eeprom paramters header
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of the Lockie Group
 *				of companies, including SIL3 Pty. Ltd (ACN 123 529 064) and
 *				Lockie Safety Systems Pty. Ltd (ACN 132 340 571).  This code may be distributed
 *				under a license from the Lockie Group of companies, and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty Ltd 2003-2012, All Rights Reserved.
 * @copyright	This file is copyright Lockie Safety Systems Pty Ltd 2008-2012, All Rights Reserved.
 * @st_fileID	LCCM188R0.FILE.002
 */

 
#ifndef _EEPROM_PARAMETERS_H_
#define _EEPROM_PARAMETERS_H_

	/*******************************************************************************
	Includes
	*******************************************************************************/
	#include <localdef.h>
	
	#ifndef C_LOCALDEF__LCCM188__ENABLE_THIS_MODULE
		#error
	#endif
	
	#if C_LOCALDEF__LCCM188__ENABLE_THIS_MODULE == 1U

		#include <MULTICORE/LCCM118__MULTICORE__NUMERICAL/numerical.h>
		#include <MULTICORE/LCCM118__MULTICORE__NUMERICAL/numerical__structs.h>

		#define C_LOCALDEF__LCCM188_DELAYED_WRITE								1U
		#define C_LOCALDEF__LCCM188_IMMEDIATE_WRITE								0U

		/** Write delay types */
		typedef enum
		{

			/** Write immedate */
			DELAY_T__IMMEDIATE_WRITE = 0U,

			/** Write delayed */
			DELAY_T__DELAYED_WRITE = 1U

		}E_EEPROM_PARAMS__DELAY_T;


		#ifndef C_LOCALDEF__LCCM188__USE_WITH_LCCM013
			#error
		#endif

		#if C_LOCALDEF__LCCM188__USE_WITH_LCCM013 == 1U
				
		
		#else //#if C_LOCALDEF__LCCM188__USE_WITH_LCCM013 == 1U
		
	
			#if C_LOCALDEF__LCCM188__USE_ON_PIC18 == 1U
				//eeprom routines (pic18)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_U8(addx,val,delay)		vPIC18_EEPROM__Write((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx,val)
				#define C_LOCALDEF__LCCM188__EEPROM_READ_U8(addx)			u8PIC18_EEPROM__Read((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx)
				
				#if C_LOCALDEF__LCCM188__DISABLE__U16 != 1U
					#define C_LOCALDEF__LCCM188__EEPROM_WRITE_U16(addx,val,delay)		vPIC18_EEPROM__WriteU16((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx,val)
					#define C_LOCALDEF__LCCM188__EEPROM_READ_U16(addx)			u16PIC18_EEPROM__Read((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx)
				#endif //C_LOCALDEF__LCCM188__DISABLE__U16
				
				#if C_LOCALDEF__LCCM188__DISABLE__S16 != 1U
					#define C_LOCALDEF__LCCM188__EEPROM_WRITE_S16(addx,val,delay)		vPIC18_EEPROM__WriteS16((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx,val)
					#define C_LOCALDEF__LCCM188__EEPROM_READ_S16(addx)			s16PIC18_EEPROM__Read((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx)
				#endif //C_LOCALDEF__LCCM188__DISABLE__S16
				
				#if C_LOCALDEF__LCCM188__DISABLE__U32 != 1U
					#define C_LOCALDEF__LCCM188__EEPROM_WRITE_U32(addx,val,delay)		vPIC18_EEPROM__WriteU32((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx,val)
					#define C_LOCALDEF__LCCM188__EEPROM_READ_U32(addx)			u32PIC18_EEPROM__Read((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx)
				#endif //C_LOCALDEF__LCCM188__DISABLE__U32
				
				#if C_LOCALDEF__LCCM188__DISABLE__S32 != 1U
					#define C_LOCALDEF__LCCM188__EEPROM_WRITE_S32(addx,val,delay)		vPIC18_EEPROM__WriteS32((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx,val)
					#define C_LOCALDEF__LCCM188__EEPROM_READ_S32(addx)			s32PIC18_EEPROM__Read((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx)
				#endif //C_LOCALDEF__LCCM188__DISABLE__S32
				
				#if C_LOCALDEF__LCCM188__DISABLE__F32 != 1U
					#define C_LOCALDEF__LCCM188__EEPROM_WRITE_F32(addx,val,delay)		vPIC18_EEPROM__WriteF32((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx,val)
					#define C_LOCALDEF__LCCM188__EEPROM_READ_F32(addx)			f32PIC18_EEPROM__Read((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx)
				#endif //C_LOCALDEF__LCCM188__DISABLE__F32
			
			#elif C_LOCALDEF__LCCM188__USE_ON_PIC32 == 1U
				//eeprom routines (pic32)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_U8(addx,val,delay)		vPIC32_NVM__WriteU32((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx, (Luint32)val)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_U16(addx,val,delay)		vPIC32_NVM__WriteU32((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx, (Luint32)val)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_S16(addx,val,delay)		vPIC32_NVM__WriteS32((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx, (Lint32)val)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_U32(addx,val,delay)		vPIC32_NVM__WriteU32((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx, val)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_S32(addx,val,delay)		vPIC32_NVM__WriteS32((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx, val)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_F32(addx,val,delay)		vPIC32_NVM__WriteF32((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx, val)
				
				#define C_LOCALDEF__LCCM188__EEPROM_READ_U8(addx)			(Luint8)u32PIC32_NVM__Read((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx)
				#define C_LOCALDEF__LCCM188__EEPROM_READ_U16(addx)			(Luint16)u32PIC32_NVM__Read((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx)
				#define C_LOCALDEF__LCCM188__EEPROM_READ_S16(addx)			(Lint16)s32PIC32_NVM__Read((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx)
				#define C_LOCALDEF__LCCM188__EEPROM_READ_U32(addx)			u32PIC32_NVM__Read((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx)
				#define C_LOCALDEF__LCCM188__EEPROM_READ_S32(addx)			s32PIC32_NVM__Read((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx)
				#define C_LOCALDEF__LCCM188__EEPROM_READ_F32(addx)			f32PIC32_NVM__Read((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx)
	
			#elif C_LOCALDEF__LCCM188__USE_ON_DSPIC == 1U
				//eeprom routines (dsPIC)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_U8(addx,val,delay)		vDSPIC_EFLASH__WriteU16((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx, (Luint16)val)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_U16(addx,val,delay)		vDSPIC_EFLASH__WriteU16((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx, (Luint16)val)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_S16(addx,val,delay)		vDSPIC_EFLASH__WriteS16((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx, (Lint16)val)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_U32(addx,val,delay)		vDSPIC_EFLASH__WriteU32((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx, val)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_S32(addx,val,delay)		vDSPIC_EFLASH__WriteS32((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx, val)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_F32(addx,val,delay)		vDSPIC_EFLASH__WriteF32((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx, val)
				
				#define C_LOCALDEF__LCCM188__EEPROM_READ_U8(addx)			(Luint8)u16DSPIC_EFLASH__Read((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx)
				#define C_LOCALDEF__LCCM188__EEPROM_READ_U16(addx)			(Luint16)u16DSPIC_EFLASH__Read((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx)
				#define C_LOCALDEF__LCCM188__EEPROM_READ_S16(addx)			(Lint16)s16DSPIC_EFLASH__Read((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx)
				#define C_LOCALDEF__LCCM188__EEPROM_READ_U32(addx)			u32DSPIC_EFLASH__Read((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx)
				#define C_LOCALDEF__LCCM188__EEPROM_READ_S32(addx)			s32DSPIC_EFLASH__Read((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx)
				#define C_LOCALDEF__LCCM188__EEPROM_READ_F32(addx)			f32DSPIC_EFLASH__Read((Luint16)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint16)addx)
	
			#elif C_LOCALDEF__LCCM188__USE_ON_RM4 == 1U
				//eeprom routines (RM4)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_U8(addx,val,delay)		vRM4_EEPROM__WriteU32((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx, (Luint32)val, delay)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_U16(addx,val,delay)		vRM4_EEPROM__WriteU32((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx, (Luint32)val, delay)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_S16(addx,val,delay)		vRM4_EEPROM__WriteS32((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx, (Lint32)val, delay)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_U32(addx,val,delay)		vRM4_EEPROM__WriteU32((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx, val, delay)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_S32(addx,val,delay)		vRM4_EEPROM__WriteS32((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx, val, delay)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_F32(addx,val,delay)		vRM4_EEPROM__WriteF32((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx, val, delay)
	
				#define C_LOCALDEF__LCCM188__EEPROM_READ_U8(addx)			(Luint8)u32RM4_EEPROM__Read((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx)
				#define C_LOCALDEF__LCCM188__EEPROM_READ_U16(addx)			(Luint16)u32RM4_EEPROM__Read((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx)
				#define C_LOCALDEF__LCCM188__EEPROM_READ_S16(addx)			(Lint16)s32RM4_EEPROM__Read((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx)
				#define C_LOCALDEF__LCCM188__EEPROM_READ_U32(addx)			u32RM4_EEPROM__Read((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx)
				#define C_LOCALDEF__LCCM188__EEPROM_READ_S32(addx)			s32RM4_EEPROM__Read((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx)
				#define C_LOCALDEF__LCCM188__EEPROM_READ_F32(addx)			f32RM4_EEPROM__Read((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx)
	
			#elif C_LOCALDEF__LCCM188__USE_ON_WIN32 == 1U
				//eeprom routines (WIN32)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_U8(addx,val,delay)		vEEPARAM_WIN32__WriteU32((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx, (Luint32)val)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_U16(addx,val,delay)		vEEPARAM_WIN32__WriteU32((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx, (Luint32)val)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_S16(addx,val,delay)		vEEPARAM_WIN32__WriteS32((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx, (Lint32)val)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_U32(addx,val,delay)		vEEPARAM_WIN32__WriteU32((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx, val)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_S32(addx,val,delay)		vEEPARAM_WIN32__WriteS32((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx, val)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_F32(addx,val,delay)		vEEPARAM_WIN32__WriteF32((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx, val)
	
				#define C_LOCALDEF__LCCM188__EEPROM_READ_U8(addx)			(Luint8)u32EEPARAM_WIN32__Read((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx)
				#define C_LOCALDEF__LCCM188__EEPROM_READ_U16(addx)			(Luint16)u32EEPARAM_WIN32__Read((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx)
				#define C_LOCALDEF__LCCM188__EEPROM_READ_S16(addx)			(Lint16)s32EEPARAM_WIN32__Read((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx)
				#define C_LOCALDEF__LCCM188__EEPROM_READ_U32(addx)			u32EEPARAM_WIN32__Read((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx)
				#define C_LOCALDEF__LCCM188__EEPROM_READ_S32(addx)			s32EEPARAM_WIN32__Read((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx)
				#define C_LOCALDEF__LCCM188__EEPROM_READ_F32(addx)			f32EEPARAM_WIN32__Read((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx)
				
			#elif C_LOCALDEF__LCCM188__USE_ON_MSP430 == 1U
				//eeprom routines (MSP430)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_U8(addx,val,delay)		vMSP430_EEPROM__WriteU32((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx, (Luint32)val, delay)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_U16(addx,val,delay)		vMSP430_EEPROM__WriteU32((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx, (Luint32)val, delay)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_S16(addx,val,delay)		vMSP430_EEPROM__WriteS32((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx, (Lint32)val, delay)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_U32(addx,val,delay)		vMSP430_EEPROM__WriteU32((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx, val, delay)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_S32(addx,val,delay)		vMSP430_EEPROM__WriteS32((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx, val, delay)
				#define C_LOCALDEF__LCCM188__EEPROM_WRITE_F32(addx,val,delay)		vMSP430_EEPROM__WriteF32((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx, val, delay)

				#define C_LOCALDEF__LCCM188__EEPROM_READ_U8(addx)			(Luint8)u32MSP430_EEPROM__Read((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx)
				#define C_LOCALDEF__LCCM188__EEPROM_READ_U16(addx)			(Luint16)u32MSP430_EEPROM__Read((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx)
				#define C_LOCALDEF__LCCM188__EEPROM_READ_S16(addx)			(Lint16)s32MSP430_EEPROM__Read((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx)
				#define C_LOCALDEF__LCCM188__EEPROM_READ_U32(addx)			u32MSP430_EEPROM__Read((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx)
				#define C_LOCALDEF__LCCM188__EEPROM_READ_S32(addx)			s32MSP430_EEPROM__Read((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx)
				#define C_LOCALDEF__LCCM188__EEPROM_READ_F32(addx)			f32MSP430_EEPROM__Read((Luint32)C_LOCALDEF__LCCM188__EEPROM_START_OFFSET + (Luint32)addx)

			#else
				#error
			#endif
		#endif //#if C_LOCALDEF__LCCM188__USE_WITH_LCCM013 == 1U

	//structures
	/*****************************************************************************
	*****************************************************************************/
	struct _strEEPARAM
	{
		//if set to 1 any updated will be delayed
		//until the user so requests.  This can be used
		//to control memory flogging that could occur during
		//large updates (writes) and consequential memory life 
		//shortening.
		Luint8 u8DelayUpdate;	
		
	};

	/*******************************************************************************
	Function Prototypes
	*******************************************************************************/
	void vEEPARAM__Init(void);
	Luint8 u8EEPARAM__Read(Luint16 u16Index);
	Luint16 u16EEPARAM__Read(Luint16 u16Index);
	Lint16 s16EEPARAM__Read(Luint16 u16Index);
	Luint32 u32EEPARAM__Read(Luint16 u16Index);
	Lint32 s32EEPARAM__Read(Luint16 u16Index);
	Lfloat32 f32EEPARAM__Read(Luint16 u16Index);
	
	void vEEPARAM__WriteU8(Luint16 u16Index, Luint8 u8Value, Luint8 u8Delayed);
	void vEEPARAM__WriteU16(Luint16 u16Index, Luint16 u16Value, Luint8 u8Delayed);
	void vEEPARAM__WriteS16(Luint16 u16Index, Lint16 s16Value, Luint8 u8Delayed);
	void vEEPARAM__WriteU32(Luint16 u16Index, Luint32 u32Value, Luint8 u8Delayed);
	void vEEPARAM__WriteS32(Luint16 u16Index, Lint32 s32Value, Luint8 u8Delayed);
	void vEEPARAM__WriteF32(Luint16 u16Index, Lfloat32 f32Value, Luint8 u8Delayed);

	#if C_LOCALDEF__LCCM188__ENABLE_VECTORS == 1U
		void vEEPARAM__Write_VS32(Luint16 u16Index, sNUM_s32Vector_3D *pvs32Value, E_EEPROM_PARAMS__DELAY_T eDelay);
		void vs32EEPARAM__Read(Luint16 u16Index, sNUM_s32Vector_3D *pvs32Value);
		void vEEPARAM__Write_VF32(Luint16 u16Index, sNUM_f32Vector_3D *pvf32Value, E_EEPROM_PARAMS__DELAY_T eDelay);
		void vf32EEPARAM__Read(Luint16 u16Index, sNUM_f32Vector_3D *pvf32Value);
	#endif

	//MAC
	void vEEPARAM__Read_MAC8(Luint16 u16Index, Luint8 * pu8MAC);
	void vEEPARAM__Write_MAC8(Luint16 u16Index, const Luint8 * pu8MAC, Luint8 u8Delayed);

	#if C_LOCALDEF__LCCM188__ENABLE_CRC == 1U
		Luint8 u8EEPARAM_CRC__Is_CRC_OK(Luint16 u16StartIndex, Luint16 u16EndIndex, Luint16 u16CRCIndex);
		Luint16 u16EEPARAM_CRC__CalculateCRC(Luint16 u16StartIndex, Luint16 u16EndIndex);
		void vEEPARAM_CRC__Calculate_And_Store_CRC(Luint16 u16StartIndex, Luint16 u16EndIndex, Luint16 u16CRCIndex);
	#endif //C_LOCALDEF__LCCM188__ENABLE_CRC

	#if C_LOCALDEF__LCCM188__USE_ON_WIN32 == 1U
		void vEEPARAM_WIN32__WriteU32(Luint32 u32Addx, Luint32 u32Val);
		void vEEPARAM_WIN32__WriteS32(Luint32 u32Addx, Lint32 s32Val);
		void vEEPARAM_WIN32__WriteF32(Luint32 u32Addx, Lfloat32 f32Val);
		Luint32 u32EEPARAM_WIN32__Read(Luint32 u32Addx);
		Lint32 s32EEPARAM_WIN32__Read(Luint32 u32Addx);
		Lfloat32 f32EEPARAM_WIN32__Read(Luint32 u32Addx);
	#endif
	
	//testing
	#if C_LOCALDEF__LCCM188__ENABLE_TEST_SPEC == 1U
		DLL_DECLARATION void vLCCM188_TS_001(void);
		DLL_DECLARATION void vLCCM188_TS_002(void);
		DLL_DECLARATION void vLCCM188_TS_003(void);
		DLL_DECLARATION void vLCCM188_TS_004(void);
		DLL_DECLARATION void vLCCM188_TS_005(void);
		DLL_DECLARATION void vLCCM188_TS_006(void);
		DLL_DECLARATION void vLCCM188_TS_007(void);
		DLL_DECLARATION void vLCCM188_TS_008(void);
		DLL_DECLARATION void vLCCM188_TS_009(void);
		DLL_DECLARATION void vLCCM188_TS_010(void);
		DLL_DECLARATION void vLCCM188_TS_011(void);
		DLL_DECLARATION void vLCCM188_TS_012(void);
		DLL_DECLARATION void vLCCM188_TS_013(void);
		DLL_DECLARATION void vLCCM188_TS_017(void);
		DLL_DECLARATION void vLCCM188_TS_018(void);
		DLL_DECLARATION void vLCCM188_TS_019(void);
		DLL_DECLARATION void vLCCM188R0_TS_021(void);
		DLL_DECLARATION void vLCCM188R0_TS_022(void);
		DLL_DECLARATION void vLCCM188R0_TS_024(void);


	#endif //C_LOCALDEF__LCCM188__ENABLE_TEST_SPEC

	//safetys
	#ifndef C_LOCALDEF__LCCM188__USE_ON_PIC18
		#error
	#endif
	#ifndef C_LOCALDEF__LCCM188__USE_ON_PIC32
		#error
	#endif
	#ifndef C_LOCALDEF__LCCM188__USE_ON_DSPIC
		#error
	#endif
	#ifndef C_LOCALDEF__LCCM188__USE_ON_RM4
		#error
	#endif


	#endif
	
#endif //_EEPROM_PARAMETERS_H_

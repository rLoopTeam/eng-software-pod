/**
 * @file		PI_COMMS.H
 * @brief		Main header file for pi comms
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 * @st_fileID	LCCM656R0.FILE.001
 */

#ifndef _PI_COMMS_H_
#define _PI_COMMS_H_
	#include <localdef.h>
	#if C_LOCALDEF__LCCM656__ENABLE_THIS_MODULE == 1U

		/*******************************************************************************
		Defines
		*******************************************************************************/
		#define RPOD_I2C_BUFFER_SIZE 			5000U
		#define RPOD_I2C_CONTROL_CHAR 			0xD5U
		#define RPOD_I2C_FRAME_START 			0xD0U
		#define RPOD_I2C_PARAMETER_START 		0xD3U
		#define RPOD_I2C_FRAME_END 				0xD8U
		

		#define I2C_BUFFER_SIZE 3000
		#define I2C_CONTROL_CHAR 0xD5
		#define I2C_FRAME_START 0xD0
		#define I2C_PARAMETER_START 0xD3
		#define I2C_FRAME_END 0xD8

		struct rI2CRX_decParam
		{
			Luint16 index;
			Luint8 type;
			Luint8 length;
			void *val;
		}rI2CRX_decParam_t;

		extern void (*rI2CRX_frameRXBeginCB) ();
		extern void (*rI2CRX_recvDecParamCB) (struct rI2CRX_decParam decParam);
		extern void (*rI2CRX_frameRXEndCB) ();


		enum rI2C_paramTypes
		{
			rI2C_INT8 = 0x11,
			rI2C_UINT8 = 0x12,
			rI2C_INT16 = 0x21,
			rI2C_UINT16 = 0x22,
			rI2C_INT32 = 0x41,
			rI2C_UINT32 = 0x42,
			rI2C_INT64 = 0x81,
			rI2C_UINT64 = 0x82,
			rI2C_FLOAT = 0x43,
			rI2C_DOUBLE = 0x83
		};

		void rI2CRX_begin();
		void rI2CRX_receiveBytes(Luint8* data, Luint16 length);

		/*******************************************************************************
		Structures
		*******************************************************************************/
		
		/** Main Pi communications structure*/
		struct _strPICOMMS
		{
			/** Upper structure guarding */
			Luint32 u32UpperGuard;
		
			/** Transmit structure
			* Transmission is from RM48 to Pi over Serial */
			struct
			{
			
				/** Support multiple transmit buffers so as we can
				* implement double or tripple buffering */
				Luint8 u8BufferIndex;
			
				Luint8 rI2CTX_buffer[RPOD_I2C_BUFFER_SIZE] __attribute__((aligned(0x04)));
				Luint16 rI2CTX_bufferPos;
				Luint16 rI2CTX_frameLength;
				Luint8 checksum;
				
			}sTx;
			
		

			/** Lower structure guarding */
			Luint32 u32LowerGuard;
		
		};
		

		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		void vPICOMMS__Init(void);

		//tx system
		void vPICOMMS_TX__Init(void);
		void rI2CTX_beginFrame();
		void rI2CTX_calculateChecksum(Luint16 lastByte);
		Luint16 rI2CTX_endFrame();
		Luint8 * pu8I2CTx__Get_BufferPointer(void);
		void rI2CTX_addParameter_int8(Luint16 u16Index, Lint8 data);
		void rI2CTX_addParameter_uint8(Luint16 u16Index, Luint8 data);
		void rI2CTX_addParameter_int16(Luint16 u16Index, Lint16 data);
		void rI2CTX_addParameter_uint16(Luint16 u16Index, Luint16 data);
		void rI2CTX_addParameter_int64(Luint16 u16Index, Lint64 data);
		void rI2CTX_addParameter_uint64(Luint16 u16Index, Luint64 data);
		void rI2CTX_addParameter_int32(Luint16 u16Index, Lint32 data);
		void rI2CTX_addParameter_uint32(Luint16 u16Index, Luint32 data);
		void rI2CTX_addParameter_float(Luint16 u16Index, Lfloat32 data);
		void rI2CTX_addParameter_double(Luint16 u16Index, Lfloat64 data);
		
		//win32 support
		#ifdef WIN32
			//some support
			typedef void(__cdecl * pPICOMMS_WIN32__TxFrame__FuncType)(const Luint8 * pu8Frame, Luint16 u16Length);
			extern "C" __declspec(dllexport) void __cdecl vPICOMMS_WIN32__TxFrame_Set_Callback(pPICOMMS_WIN32__TxFrame__FuncType pFunc);
			void vPICOMMS_WIN32__TxFrame_Callback(const Luint8 * pu8Frame, Luint16 u16Length);

			DLL_DECLARATION void vPICOMMS_WIN32__Test1(void);
		#endif

	#endif //#if C_LOCALDEF__LCCM656__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM656__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_PI_COMMS_H_


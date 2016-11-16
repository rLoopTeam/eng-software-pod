/**
 * @file		PI_COMMS.H
 * @brief		Main header file for pi comms
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 */

#ifndef _PI_COMMS_H_
#define _PI_COMMS_H_
	#include <localdef.h>
	#if C_LOCALDEF__LCCM656__ENABLE_THIS_MODULE == 1U

		//our default packet types.
		#include <LCCM656__RLOOP__PI_COMMS/pi_comms__packet_types.h>

		/*******************************************************************************
		Defines
		*******************************************************************************/
		#define RPOD_PICOMMS_BUFFER_SIZE 			3000U //CAREFUL MAKING THIS LARGER, MAY CRASH AND I DON'T KNOW WHY
		#define RPOD_PICOMMS_CONTROL_CHAR 			0xD5U
		#define RPOD_PICOMMS_FRAME_START 			0xD0U
		#define RPOD_PICOMMS_PARAMETER_START 		0xD3U
		#define RPOD_PICOMMS_FRAME_END 				0xD8U

		extern void (*PICOMMS_RX_frameRXBeginCB) ();

		extern void (*PICOMMS_RX_recvLuint8) (Luint16 index, Luint8 data);
		extern void (*PICOMMS_RX_recvLint8) (Luint16 index, Lint8 data);
		extern void (*PICOMMS_RX_recvLuint16) (Luint16 index, Luint16 data);
		extern void (*PICOMMS_RX_recvLint16) (Luint16 index, Lint16 data);
		extern void (*PICOMMS_RX_recvLuint32) (Luint16 index, Luint32 data);
		extern void (*PICOMMS_RX_recvLint32) (Luint16 index, Lint32 data);
		extern void (*PICOMMS_RX_recvLuint64) (Luint16 index, Luint64 data);
		extern void (*PICOMMS_RX_recvLint64) (Luint16 index, Lint64 data);
		extern void (*PICOMMS_RX_recvLfloat32) (Luint16 index, Lfloat32 data);
		extern void (*PICOMMS_RX_recvLfloat64) (Luint16 index, Lfloat64 data);
		
		extern void (*PICOMMS_RX_frameRXEndCB) ();


		enum PICOMMS_paramTypes
		{
			PICOMMS_INT8 = 0x11,
			PICOMMS_UINT8 = 0x12,
			PICOMMS_INT16 = 0x21,
			PICOMMS_UINT16 = 0x22,
			PICOMMS_INT32 = 0x41,
			PICOMMS_UINT32 = 0x42,
			PICOMMS_INT64 = 0x81,
			PICOMMS_UINT64 = 0x82,
			PICOMMS_FLOAT = 0x43,
			PICOMMS_DOUBLE = 0x83
		};


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
			
				Luint8 PICOMMS_TX_buffer[RPOD_PICOMMS_BUFFER_SIZE] __attribute__((aligned(0x04)));
				Luint16 PICOMMS_TX_bufferPos;
				Luint16 PICOMMS_TX_frameLength;
				Luint8 u8Checksum;
				
			}sTx;

			/** Receive side */
			struct
			{

				Luint8 u8Buffer[RPOD_PICOMMS_BUFFER_SIZE] __attribute__((aligned(0x04)));
				Luint16 bufferBegin;
				Luint16 bufferLength;
				Luint8 u8TempFrameBuffer[RPOD_PICOMMS_BUFFER_SIZE] __attribute__((aligned(0x04)));

				//quick and nasty fault counter
				Luint32 u32Faults;

			}sRx;

			struct
			{
				Luint8 PICOMMS_LOOP_UINT8;
				Lint8 PICOMMS_LOOP_INT8;
				Luint16 PICOMMS_LOOP_UINT16;
				Lint16 PICOMMS_LOOP_INT16;
				Luint32 PICOMMS_LOOP_UINT32;
				Lint32 PICOMMS_LOOP_INT32;
				Luint64 PICOMMS_LOOP_UINT64;
				Lint64 PICOMMS_LOOP_INT64;
				Lfloat32 PICOMMS_LOOP_FLOAT32;
				Lfloat64 PICOMMS_LOOP_FLOAT64;
			}sLp;

			/** Lower structure guarding */
			Luint32 u32LowerGuard;

		};

		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		void vPICOMMS__Init(void);
		void vPICOMMS__Process(void);


		//tx system
		void vPICOMMS_TX__Init(void);
		void PICOMMS_TX_beginFrame();
		void PICOMMS_TX_calculateChecksum(Luint16 lastByte);
		Luint16 PICOMMS_TX_endFrame();
		Luint8 * pu8I2CTx__Get_BufferPointer(void);
		void PICOMMS_TX_addParameter_int8(Luint16 u16Index, Lint8 data);
		void vPICOMMS_TX__Add_U8(Luint16 u16Index, Luint8 data);
		void PICOMMS_TX_addParameter_int16(Luint16 u16Index, Lint16 data);
		void vPICOMMS_TX__Add_U16(Luint16 u16Index, Luint16 data);
		void PICOMMS_TX_addParameter_int64(Luint16 u16Index, Lint64 data);
		void PICOMMS_TX_addParameter_uint64(Luint16 u16Index, Luint64 data);
		void PICOMMS_TX_addParameter_int32(Luint16 u16Index, Lint32 data);
		void vPICOMMS_TX__Add_U32(Luint16 u16Index, Luint32 data);
		void vPICOMMS_TX__Add_F32(Luint16 u16Index, Lfloat32 data);
		void PICOMMS_TX_addParameter_double(Luint16 u16Index, Lfloat64 data);
		

		//Rx system
		void vPICOMMS_RX__Init();
		void vPICOMMS_RX__Receive_Bytes(Luint8* data, Luint16 length);


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


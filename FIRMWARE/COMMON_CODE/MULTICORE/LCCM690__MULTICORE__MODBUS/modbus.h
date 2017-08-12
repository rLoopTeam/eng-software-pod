/**
 * @file		MODBUS.H
 * @brief		Main header file.
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM690R0.FILE.001
 */

#ifndef _MODBUS_H_
#define _MODBUS_H_

	#include <localdef.h>

	#if C_LOCALDEF__LCCM690__ENABLE_THIS_MODULE == 1U

		/*******************************************************************************
		Includes
		*******************************************************************************/
		#include <MULTICORE/LCCM690__MULTICORE__MODBUS/modbus__types.h>
		#include <MULTICORE/LCCM690__MULTICORE__MODBUS/modbus__defines.h>

		#include <MULTICORE/LCCM357__MULTICORE__SOFTWARE_FIFO/software_fifo__public.h>

		/*******************************************************************************
		Defines
		*******************************************************************************/
		
		/** Maximum UART Rx Tx Buffer Length in bytes */
		#define C_MODBUS__MAX_UART_RX_BUFF_LENGTH									(32U)
		
		#if C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__WIN32 == 1U
			typedef void (__cdecl *pSIL3_MODBUS_WIN32__TxPacket_CallbackType)(Luint8 *pu8Array, Luint16 u16Length);
		#endif

		/*******************************************************************************
		Structures
		*******************************************************************************/
		typedef struct
		{
			
			/** Uart Rx Support */
			struct
			{
				/** The Rx buffer to store incomming data */
				Luint8 u8Buffer[C_MODBUS__MAX_UART_RX_BUFF_LENGTH];
			
				/** FIFO to keep track of the buffer position */
				SOFTWARE_FIFO__USER_T sFIFO;
			
			}sUART_Rx;
			
			#if C_LOCALDEF__LCCM690__PERSONALITY_MASTER == 0U
				/** Data for the slave interface*/
				struct
				{

					/** We need to signal is new UART data is available the issue here is that we
					 * will never know the true length of the UART data until the CRC is checked
					 * So we can signal from the UART layer to the SLAVE layer that new UART data is in the
					 * Temp Frame buffer, and if needed co-ordinate the collection of addtional data, or
					 * abort the UART collection and wait for a new packet
					 */
					Luint8 u8NewTempData;

					/** Temp buffer holds data from the UART layer and once we have processed the CRC, we
					 * release the UART and keep processing this buffer
					 */
					Luint8 u8TempBuffer[C_MODBUS__MAX_UART_RX_BUFF_LENGTH];

					/** Keep track of the buffer position */
					Luint8 u8TempBufferPos;

					/** Is a message being handled by the register unit?
					 * This is set once a valid message is passed off to the register unit*/
					Luint8 u8MessageBeingHandled;

					/** The slave address used for networking */
					Luint8 u8SlaveAddx;

				}sSlave;

				/** Slave Register Set */
				struct
				{

					/** The slave handler has a valid message buffer */
					Luint8 u8SlaveBufferValid;


					/** The actual number of registers */
					struct
					{
						/** The actual register value */
						Luint16 u16Value;

						/** The programmed register address */
						Luint16 u16Addx;

					}sRegs[C_LOCALDEF__LCCM690__NUM_SLAVE_REGISTERS];


				}sSlaveRegs;


				/** Slave response to a message */
				struct
				{

					/** Has a new response been created and ready to be sent?*/
					Luint8 u8ResponseValid;

					/** Response buffer */
					Luint8 u8ResponseBuffer[C_MODBUS__MAX_UART_RX_BUFF_LENGTH];

					/** Length of the response */
					Luint8 u8ResponseLength;

				}sSlaveResponse;


			#elif C_LOCALDEF__LCCM690__PERSONALITY_MASTER == 1U

				/** Master mode interface */
				struct
				{

					/** State control */
					struct
					{
						/** Master state machine */
						TE_MODBUS__MASTER_STATES eSate;
						
						/** User has committed a new command and its ready to be processed */
						Luint8 u8NewCommandReady;
						
						/** The state machine wants to transmit something */
						Luint8 u8TxRequired;
						
						/** Count of 10ms ticks for timeout purposes */
						Luint32 u32TimeoutCounter;

						/** Last command error code, check after busy = 0 */
						Lint16 s16LastCommandCode;

					}sState;

					/** Slave Register Set */
					struct
					{

						/** The slave handler has a valid message buffer */
						Luint8 u8SlaveBufferValid;

						/** The set index on the bus */
						Luint8 u8SlaveAddx;

						/** The actual number of registers */
						struct
						{
							/** The actual register value */
							Luint16 u16Value;

							/** The programmed register address */
							Luint16 u16Addx;

						}sRegs[C_LOCALDEF__LCCM690__MASTER_NUM_SLAVE_REGS];


					}sSlaves[C_LOCALDEF__LCCM690__MASTER_NUM_SLAVES];

					/** Message Transmit Buffer */
					struct
					{

						/** Do we need to transmit a message? */
						Luint8 u8TxRequired;

						/** The message buffer */
						Luint8 u8Buffer[C_MODBUS__MAX_UART_RX_BUFF_LENGTH];

						/** The length of the message buffer */
						Luint8 u8BufferLength;

						/** The transmit is in progress */
						Luint8 u8InProgress;


					}sTxBuffer;


					/** Rx handling */
					struct
					{
						/** We need to signal is new UART data is available the issue here is that we
						 * will never know the true length of the UART data until the CRC is checked
						 * So we can signal from the UART layer to the SLAVE layer that new UART data is in the
						 * Temp Frame buffer, and if needed co-ordinate the collection of addtional data, or
						 * abort the UART collection and wait for a new packet
						 */
						Luint8 u8NewTempData;

						/** Temp buffer holds data from the UART layer and once we have processed the CRC, we
						 * release the UART and keep processing this buffer
						 */
						Luint8 u8TempBuffer[C_MODBUS__MAX_UART_RX_BUFF_LENGTH];

						/** Keep track of the buffer position */
						Luint8 u8TempBufferPos;

						/** Is a message being handled by the register unit?
						 * This is set once a valid message is passed off to the register unit*/
						Luint8 u8MessageBeingHandled;

						/** The current frame check is done and the frame is good */
						Luint8 u8FrameCheckComplete;

					}sRxBuffer;


					/** Keep track of what requests were sent to what slaves */
					struct
					{

						/** Flag to indicate if we have a request in progress */
						Luint8 u8InProgress;

						/** Timer for how long the request has been in the queue
						 * this is used to detect dead slaves */
						Luint32 u32Timer;

						/** The addx of the slave that was last sent */
						Luint8 u8SlaveAddx;

						/** The request type */
						TE_MODBUS__FUNCTION_CODE eSlaveRequest;

						/** The amount of registers to read */
						Luint16 u16SlaveNumRegs;

						/** The starting address of the registers */
						Luint16 u16StartingAddx;

					}sSlaveRequest;



				}sMaster;
			#else
				#error
			#endif
			
			#ifdef WIN32
			/** Win32 Emulation Support*/
			struct
			{
				/** The transmit packet callback, should be set by the upper layer*/
				pSIL3_MODBUS_WIN32__TxPacket_CallbackType pTxPacketCallback;
			}sWIN32;
			#endif
			
		}TS_SIL3_MODBUS_MAIN;
		

		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		void vSIL3_MODBUS__Init(void);
		void vSIL3_MODBUS__Process(void);
		void vSIL3_MODBUS__10MS_Timer(void);
		
		void vSIL3_MODBUS_LOWLEVEL__Init(void);
		void vSIL3_MODBUS_LOWLEVEL__Process(void);
		void vSIL3_MODBUS_LOWLEVEL__Tx_Enable(void);
		void vSIL3_MODBUS_LOWLEVEL__Tx_Disable(void);
		
		#if C_LOCALDEF__LCCM690__PERSONALITY_MASTER == 0U
			//slave
			void vSIL3_MODBUS_SLAVE__Init(void);
			void vSIL3_MODBUS_SLAVE__Process(void);
			void vSIL3_MODBUS_SLAVE__Set_SlaveAddx(Luint8 u8Addx);
			void vSIL3_MODBUS_SLAVE__Append_UART_U8(Luint8 u8Value);

			//slave registers
			void vSIL3_MODBUS_SLAVE_REGS__Init(void);
			void vSIL3_MODBUS_SLAVE_REGS__Process(void);
			void vSIL3_MODBUS_SLAVE_REGS__Message_Valid(void);
			void vSIL3_MODBUS_SLAVE_REGS__Set_RegisterAddx(Luint8 u8RegIndex, Luint16 u16Addx);
			void vSIL3_MODBUS_SLAVE_REGS__Set_RegisterValue_U16(Luint8 u8RegIndex, Luint16 u16Value);
			Luint16 u16SIL3_MODBUS_SLAVE_REGS__Get_RegisterValue(Luint8 u8RegIndex);

		#elif C_LOCALDEF__LCCM690__PERSONALITY_MASTER == 1U

			void vSIL3_MODBUS_MASTER__Init(void);
			void vSIL3_MODBUS_MASTER__Process(void);
			Luint8 u8SIL3_MODBUS_MASTER__Get_IsBusy(void);
			Lint16 s16SIL3_MODBUS_MASTER__Get_LastErrorCode(void);
			void vSIL3_MODBUS_MASTER__Append_UART_U8(Luint8 u8Value);
			void vSIL3_MODBUS_MASTER__10MS_Timer(void);

			void vSIL3_MODBUS_MASTER_CMD__Init(void);
			void vSIL3_MODBUS_MASTER_CMD__Process(void);
			Lint16 s16SIL3_MODBUS_MASTER_CMD__Slave_Reqest_Read(Luint8 u8SlaveAddx, TE_MODBUS__FUNCTION_CODE eFunction, Luint16 u16StartAddx, Luint16 u16NumRegs);

			void vSIL3_MODBUS_MASTER_SLAVEREGS__Init(void);
			void vSIL3_MODBUS_MASTER_SLAVEREGS__Process(void);
			void vSIL3_MODBUS_MASTER_SLAVEREGS__Handle_Slave_Message(Luint8 u8SlaveIndex);
			Lint16 s16SIL3_MODBUS_MASTER_SLAVEREGS__DeviceIndex_To_SlaveIndex(Luint8 u8DeviceIndex);
			Luint16 u16SIL_MODBUS_MASTER_SLAVEREGS__RegAddx_To_Index(Luint8 u8SlaveIndex, Luint16 u16RegAddx);
			Luint16 u16SIL_MODBUS_MASTER_SLAVEREGS__RegIndex_To_Addx(Luint8 u8SlaveIndex, Luint16 u16RegIndex);
			Luint16 u16SIL3_MODBUS_MASTER_SLAVEREGS__Get_RegisterValue_Addx(Luint8 u8SlaveIndex, Luint16 u16RegAddx);
			Luint16 u16SIL3_MODBUS_MASTER_SLAVEREGS__Get_RegisterValue(Luint8 u8SlaveIndex, Luint8 u8RegIndex);
			void vSIL3_MODBUS_MASTER_SLAVEREGS__Set_RegisterAddx(Luint8 u8SlaveIndex, Luint8 u8RegIndex, Luint16 u16Addx);
			void vSIL3_MODBUS_MASTER_SLAVEREGS__Set_RegisterValue_Addx(Luint8 u8SlaveIndex, Luint16 u16RegAddx, Luint16 u16Value);
			void vSIL3_MODBUS_MASTER_SLAVEREGS__Set_SlaveAddx(Luint8 u8SlaveIndex, Luint8 u8SlaveAddx);

		#else
			#error
		#endif

		//CRC functions
		Lint16 s16SIL3_MODBUS_CRC__CheckCRC(Luint8 *pu8Data, Luint16 u16DataLen);
		void vSIL3_MODBUS_CRC__AddCRC(Luint8 *pu8Data, Luint16 u16FrameLength);
		Luint16 u16SIL3_MODBUS_CRC__ComputeCRC(Luint8 *pu8Data, Luint16 u16DataLen);
		
		//framing
		Lint16 s16SIL3_MODBUS_FRAME__Check_Complete(void);

		//UART Interface
		void vSIL3_MODBUS_UART__Init(void);
		void vSIL3_MODBUS_UART__Process(void);
		void vSIL3_MODBUS_UART__Rx_U8(Luint8 u8Value);
		
		#if C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__WIN32 == 1U
			void vSIL3_MODBUS_WIN32__Init(void);
			void vSIL3_MODBUS_WIN32__Process(void);
			DLL_DECLARATION void vSIL3_MODBUS_WIN32__Rx_Packet(Luint8 *pBuffer, Luint16 u16Length);
			void vSIL3_MODBUS_WIN32__Set_Callback__Tx_Packet(pSIL3_MODBUS_WIN32__TxPacket_CallbackType pFunc);
			void vSIL3_MODBUS_WIN32__Tx_Packet(Luint8 *pBuffer, Luint16 u16Length);
		#endif


		//testing
		#if C_LOCALDEF__LCCM690__ENABLE_TEST_SPEC == 1U
			DLL_DECLARATION void vLCCM690R0_TS_000(void);
			DLL_DECLARATION void vLCCM690R0_TS_001(void);
			DLL_DECLARATION void vLCCM690R0_TS_002(void);
			DLL_DECLARATION void vLCCM690R0_TS_003(void);
			DLL_DECLARATION void vLCCM690R0_TS_004(void);
			DLL_DECLARATION void vLCCM690R0_TS_005(void);
			DLL_DECLARATION void vLCCM690R0_TS_006(void);
			DLL_DECLARATION void vLCCM690R0_TS_007(void);
			DLL_DECLARATION void vLCCM690R0_TS_008(void);
			DLL_DECLARATION void vLCCM690R0_TS_009(void);
			DLL_DECLARATION void vLCCM690R0_TS_010(void);
			DLL_DECLARATION void vLCCM690R0_TS_011(void);
			DLL_DECLARATION void vLCCM690R0_TS_012(void);
			DLL_DECLARATION void vLCCM690R0_TS_013(void);
			DLL_DECLARATION void vLCCM690R0_TS_014(void);
			DLL_DECLARATION void vLCCM690R0_TS_015(void);
			DLL_DECLARATION void vLCCM690R0_TS_016(void);
			DLL_DECLARATION void vLCCM690R0_TS_017(void);
			DLL_DECLARATION void vLCCM690R0_TS_018(void);
			DLL_DECLARATION void vLCCM690R0_TS_019(void);
#endif //C_LOCALDEF__LCCM690__ENABLE_TEST_SPEC
		
		
		#ifndef C_LOCALDEF__SIL3_GENERIC__CPU_TYPE__WIN32
			#error
		#endif
		
	#endif //#if C_LOCALDEF__LCCM690__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM690__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_MODBUS_H_


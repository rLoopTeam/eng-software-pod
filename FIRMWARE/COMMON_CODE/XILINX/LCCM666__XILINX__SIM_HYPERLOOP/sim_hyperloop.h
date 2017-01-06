/**
 * @file		SIM_HYPERLOOP.H
 * @brief		Main Header
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM666R0.FILE.001
 */

#ifndef _SIM_HYPERLOOP_H_
#define _SIM_HYPERLOOP_H_
	#include <localdef.h>
	#if C_LOCALDEF__LCCM666__ENABLE_THIS_MODULE == 1U

		/*******************************************************************************
		Defines
		*******************************************************************************/

		typedef enum
		{
			TRAKSIM_STATE__IDLE = 0U,
			
			TRAKSIM_STATE__ACCEL,
			
			TRAKSIM_STATE__COAST,
			
			TRAKSIM_STATE__DECEL,
			
			TRAKSIM_STATE__STOP
			
		}E_SIMHL__TRACK_SIM_STATE_T;
		

		/*******************************************************************************
		Structures
		*******************************************************************************/
		struct _strSIMHLOOP
		{
			
			/** Software Track Model */
			struct
			{
				
				E_SIMHL__TRACK_SIM_STATE_T eState;
				
				/** Pod Dynamics */
				struct
				{
					
					/** Mass of Pod */
					Lfloat32 f32PodMass_KG;
					
					/** G-Force during acceleration */
					Lfloat32 f32Accel_G;
					
					/** Cost Transition Velocity */
					Lfloat32 f32CoastVeloc_ms;
					
					/** Braking Decel */
					Lfloat32 f32Decel_G;
					
					
				}sPod;
				
				
				/** Timestep per iteration / Clock Frequency */
				Lfloat32 f32TimeStep;
				
				/** Accel increment per time step */
				Lfloat32 f32AccelIncrement;
				
				
			}sTrack;
			

			/** Control params */
			struct
			{

				/** Running 1 or 0 */
				Luint8 u8RunStatus;

			}sControl;


			/** Ethernet handler */
			struct
			{
				/** loacal specific MAC */
				Luint8 u8MACAddx[6];

				/** local IP */
				Luint8 u8IPAddx[4];

				/** The timer has incremented */
				Luint8 u8TimerFlag;

			}sEthernet;

		};
		

		/*******************************************************************************
		Function Prototypes
		*******************************************************************************/
		void vSIMHLOOP__Init(void);
		void vSIMHLOOP__Process(void);
		void vSIMHLOOP__100MS_Timer(void);

		//ethernet
		void vSIMHLOOP_ETH__Init(void);
		void vSIMHLOOP_ETH__Process(void);

		//lowlevel
		void vSIMHLOOP_LOWLEVEL__Init(void);
		void vSIMHLOOP_LOWLEVEL__Set_Accel_GForce(Lfloat32 f32GForce);
		void vSIMHLOOP_LOWLEVEL__Set_Max_Veloc(Luint32 u32Max);
		void vSIMHLOOP_LOWLEVEL__ManualLaser_Control(Luint32 u32Laser, Luint32 u32Value);
		void vSIMHLOOP_LOWLEVEL__Run_On(void);
		void vSIMHLOOP_LOWLEVEL__Run_Off(void);

	#endif //#if C_LOCALDEF__LCCM666__ENABLE_THIS_MODULE == 1U
	//safetys
	#ifndef C_LOCALDEF__LCCM666__ENABLE_THIS_MODULE
		#error
	#endif
#endif //_SIM_HYPERLOOP_H_


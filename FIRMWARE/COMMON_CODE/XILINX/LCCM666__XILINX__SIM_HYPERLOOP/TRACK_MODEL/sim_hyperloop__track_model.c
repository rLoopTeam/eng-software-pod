/**
 * @file		SIM_HYPERLOOP__TRACK_MODEL.C
 * @brief		Software track model,
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM666R0.FILE.003
 */

/**
 * @addtogroup XILINX
 * @{ */
/**
 * @addtogroup HYPERLOOP
 * @ingroup XILINX
 * @{ */
/**
 * @addtogroup HYPERLOOP__TRACK_MODEL
 * @ingroup HYPERLOOP
 * @{ */

#include "../sim_hyperloop.h"

extern struct _strSIMHLOOP sSH;

//init the track model.
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		7D1FE410B86838B43F9BD31EA4526184
 * @st_funcID		LCCM666R0.FILE.003.FUNC.001
 */
void vSIMHLOOP_TRACK__Init(void)
{
	
	sSH.sTrack.eState = TRAKSIM_STATE__IDLE;
	
	//config the pod model
	sSH.sTrack.sPod.f32PodMass_KG = 320.0F;
	sSH.sTrack.sPod.f32Accel_G = 2.0F;
	sSH.sTrack.sPod.f32CoastVeloc_ms = 100.0F;
	sSH.sTrack.sPod.f32Decel_G = -2.0F;
	
	//Simulation
	//10ns time step
	sSH.sTrack.f32TimeStep = 10E-9;
	
	//compute the veloc increase per time step based on the g-force
	//sSH.sTrack.f32AccelIncrement;
	
	//Need to compute the distance travelled per time step
	//no easy way to do this other than
	//s = ut + 1/2at^2
	
	
}

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		EC34923095FC8D17EEF1551720BD0A34
 * @st_funcID		LCCM666R0.FILE.003.FUNC.002
 */
void vSIMHLOOP_TRACK__Process(void)
{
	
	switch(sSH.sTrack.eState)
	{
		
		case TRAKSIM_STATE__IDLE:
			break;
		case TRAKSIM_STATE__ACCEL:
			break;
			
		case TRAKSIM_STATE__COAST:
			break;
			
		case TRAKSIM_STATE__DECEL:
			break;
			
		case TRAKSIM_STATE__STOP:
			break;
		
	}
	
}

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		AE42C7F8391E98903A4588048F26F286
 * @st_funcID		LCCM666R0.FILE.003.FUNC.003
 */
void vSIMHLOOP_TRACK__Start(void)
{
	
	sSH.sTrack.eState = TRAKSIM_STATE__ACCEL;
}
/** @} */
/** @} */
/** @} */

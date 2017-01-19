/**
 * @file		SIM_HYPERLOOP__LOWLEVEL.C
 * @brief		Lowlevel register IO
 * @author		Lachlan Grogan
 * @copyright	This file contains proprietary and confidential information of
 *				SIL3 Pty. Ltd. (ACN 123 529 064). This code may be distributed
 *				under a license from SIL3 Pty. Ltd., and may be used, copied
 *				and/or disclosed only pursuant to the terms of that license agreement.
 *				This copyright notice must be retained as part of this file at all times.
 * @copyright	This file is copyright SIL3 Pty. Ltd. 2003-2016, All Rights Reserved.
 * @st_fileID	LCCM666R0.FILE.004
 */
/**
 * @addtogroup XILINX
 * @{ */
/**
 * @addtogroup HYPERLOOP
 * @ingroup XILINX
 * @{ */
/**
 * @addtogroup HYPERLOOP__LOWLEVEL
 * @ingroup HYPERLOOP
 * @{ */

#include "../sim_hyperloop.h"
#if C_LOCALDEF__LCCM666__ENABLE_THIS_MODULE == 1U

/***************************************************************************//**
 * @brief
 * Init any lowlevel stuff
 * 
 * @st_funcMD5		30A635200B352BC311E02294DC2A6C88
 * @st_funcID		LCCM666R0.FILE.004.FUNC.001
 */
void vSIMHLOOP_LOWLEVEL__Init(void)
{


}

/***************************************************************************//**
 * @brief
 * Set the accel g force in mm/s^2
 * 
 * @param[in]		f32GForce				The normal G-Force
 * @st_funcMD5		59F6D079737D5551F91C5D98C4DAB030
 * @st_funcID		LCCM666R0.FILE.004.FUNC.002
 */
void vSIMHLOOP_LOWLEVEL__Set_Accel_GForce(Lfloat32 f32GForce)
{
	Lfloat32 f32Temp;
	Luint32 u32Temp;

	//convert to mm/s^2
	f32Temp = f32GForce;

	//convert to accel
	f32Temp *= 9.80665F;

	//convert to mm
	f32Temp *= 1000.0F;

	//convert to U32
	u32Temp = (Luint32)f32Temp;

	//update the accel register
	XIo_Out32((XPAR_LVHD087_SIM_HYPERLOOP_0_BASEADDR + 0x04U), u32Temp);

}

/***************************************************************************//**
 * @brief
 * Set the maximum velocity possible before transition to coast state
 * 
 * @param[in]		u32Max				In meters per second
 * @st_funcMD5		68450253DB4DA4D9C51482118F28DBCF
 * @st_funcID		LCCM666R0.FILE.004.FUNC.003
 */
void vSIMHLOOP_LOWLEVEL__Set_Max_Veloc(Luint32 u32Max)
{
	//convert to mm/sec
	u32Max *= 1000U;

	//update the accel register
	XIo_Out32((XPAR_LVHD087_SIM_HYPERLOOP_0_BASEADDR + 0x08U), u32Max);

}


void vSIMHLOOP_LOWLEVEL__ManualLaser_Control(Luint32 u32Laser, Luint32 u32Value)
{
	Luint32 u32Reg;
	Luint32 u32Mask;

	//read the control register
	u32Reg = XIo_In32(XPAR_LVHD087_SIM_HYPERLOOP_0_BASEADDR + 0x00U);

	//modify
	u32Mask = 0x00000002U;
	//select our laser
	u32Mask <<= u32Laser;

	//switch on
	if(u32Value == 1U)
	{
		u32Reg |= u32Mask;
	}
	else
	{
		//off
		u32Mask ^= 0xFFFFFFFFU;
		u32Reg &= u32Mask;
	}

	//write back
	XIo_Out32(XPAR_LVHD087_SIM_HYPERLOOP_0_BASEADDR + 0x00U, u32Reg);

}

/***************************************************************************//**
 * @brief
 * Sets the run state machine to on
 * 
 * @st_funcMD5		8B7C45CBC192EC4E374461367D5E91D0
 * @st_funcID		LCCM666R0.FILE.004.FUNC.004
 */
void vSIMHLOOP_LOWLEVEL__Run_On(void)
{
	Luint32 u32Reg;
	Luint32 u32Mask;

	//read the control register
	u32Reg = XIo_In32(XPAR_LVHD087_SIM_HYPERLOOP_0_BASEADDR + 0x00U);

	//modify
	u32Mask = 0x00000001U;

	//switch on
	u32Reg |= u32Mask;

	//write back
	XIo_Out32(XPAR_LVHD087_SIM_HYPERLOOP_0_BASEADDR + 0x00U, u32Reg);

}

/***************************************************************************//**
 * @brief
 * Stop the run
 * 
 * @st_funcMD5		A4AE0EB985ECE133B0AB320AC339EEFE
 * @st_funcID		LCCM666R0.FILE.004.FUNC.005
 */
void vSIMHLOOP_LOWLEVEL__Run_Off(void)
{
	Luint32 u32Reg;
	Luint32 u32Mask;

	//read the control register
	u32Reg = XIo_In32(XPAR_LVHD087_SIM_HYPERLOOP_0_BASEADDR + 0x00U);

	//modify
	u32Mask = 0x00000001U;

	//invert
	u32Mask ^= 0xFFFFFFFFU;

	//switch off
	u32Reg &= u32Mask;

	//write back
	XIo_Out32(XPAR_LVHD087_SIM_HYPERLOOP_0_BASEADDR + 0x00U, u32Reg);

}

#endif //#if C_LOCALDEF__LCCM666__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM666__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */



//Blends the position, accel and veloc from lower layers and gives a
//single point of interface to the flight layer with our primary measurements
//also allows the track profile to dictate what sensors are used for what measurements.


#include "../../fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL == 1U
#if 0
//the structure
extern struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		6B43487B4AB4C611614B83DC0EEEBF49
 * @st_funcID		LCCM655R0.FILE.092.FUNC.001
 */
void vFCU_FCTL_BLENDER__Init(void)
{
	//todo: init flight conditions
	sFCU.sFlightControl.sBlender.sWorking.s32Accel_mm_ss = 0;
	sFCU.sFlightControl.sBlender.sWorking.s32Veloc_mm_s = 0;
	sFCU.sFlightControl.sBlender.sWorking.s32Distance_mm = 0;
}


/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		31AE84EF1368AB58CB3EB6C6317023B7
 * @st_funcID		LCCM655R0.FILE.092.FUNC.002
 */
void vFCU_FCTL_BLENDER__Process(void)
{
	//todo
	//determine from the track database what sensors we need
	//add in any geometry offsets
	//check things like laser range as its not a displacement from the start of the track
	//determine 3 current values, A, V, D

}

//return the current values
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		04CC27AC99940E871624E78E33672C83
 * @st_funcID		LCCM655R0.FILE.092.FUNC.003
 */
Lint32 s32FCU_FCTL_BLENDER__Get_Accel_mmss(void)
{
	return sFCU.sFlightControl.sBlender.sWorking.s32Accel_mm_ss;
}

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		7323B04512CB94BB9AE1D2F14756DE75
 * @st_funcID		LCCM655R0.FILE.092.FUNC.004
 */
Lint32 s32FCU_FCTL_BLENDER__Get_Veloc_mms(void)
{
	return sFCU.sFlightControl.sBlender.sWorking.s32Veloc_mm_s;
}

/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @st_funcMD5		EAA5F1CFCA6CE2E031FD233665A309D1
 * @st_funcID		LCCM655R0.FILE.092.FUNC.005
 */
Lint32 s32FCU_FCTL_BLENDER__Get_Displacement_mm(void)
{
	return sFCU.sFlightControl.sBlender.sWorking.s32Distance_mm;
}

//update the velocity from the accelometer subystems
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Veloc_mms		## Desc ##
 * @param[in]		u8Channel		## Desc ##
 * @st_funcMD5		59777C3CBA664752E7B836BBF31863CA
 * @st_funcID		LCCM655R0.FILE.092.FUNC.006
 */
void vFCU_FCTL_BLENDER__Veloc_UpdateFrom_Accel(Luint8 u8Channel, Luint32 u32Veloc_mms)
{

}

//update the velocity from the LRF
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Veloc_mms		## Desc ##
 * @param[in]		u8Channel		## Desc ##
 * @st_funcMD5		1A965AB11BC3801E8CBD37BA6AF48288
 * @st_funcID		LCCM655R0.FILE.092.FUNC.007
 */
void vFCU_FCTL_BLENDER__Veloc_UpdateFrom_LRF(Luint8 u8Channel, Luint32 u32Veloc_mms)
{

}

//Update the velocity from the contrast sensor system
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Veloc_mms		## Desc ##
 * @param[in]		u8Channel		## Desc ##
 * @st_funcMD5		DA62E13F32AAB193E5867676F9F40554
 * @st_funcID		LCCM655R0.FILE.092.FUNC.008
 */
void vFCU_FCTL_BLENDER__Veloc_UpdateFrom_Contrast(Luint8 u8Channel, Luint32 u32Veloc_mms)
{

}


//update the Acceleration from the accelometer subystems
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Accel_mmss		## Desc ##
 * @param[in]		u8Channel		## Desc ##
 * @st_funcMD5		D0DDA1FC5BC49388A1AFD578BAEBF3F1
 * @st_funcID		LCCM655R0.FILE.092.FUNC.009
 */
void vFCU_FCTL_BLENDER__Accel_UpdateFrom_Accel(Luint8 u8Channel, Luint32 u32Accel_mmss)
{

}

//update the Acceleration from the LRF
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Accel_mmss		## Desc ##
 * @param[in]		u8Channel		## Desc ##
 * @st_funcMD5		655026A0D75A99EE8E7EBE3FDBFEFEE3
 * @st_funcID		LCCM655R0.FILE.092.FUNC.010
 */
void vFCU_FCTL_BLENDER__Accel_UpdateFrom_LRF(Luint8 u8Channel, Luint32 u32Accel_mmss)
{

}

//Update the Acceleration from the contrast sensor system
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Accel_mmss		## Desc ##
 * @param[in]		u8Channel		## Desc ##
 * @st_funcMD5		B584AA4C4391361450C62BFDE003C99A
 * @st_funcID		LCCM655R0.FILE.092.FUNC.011
 */
void vFCU_FCTL_BLENDER__Accel_UpdateFrom_Contrast(Luint8 u8Channel, Luint32 u32Accel_mmss)
{

}


//update the Displacement from the accelometer subystems
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Disp_mm		## Desc ##
 * @param[in]		u8Channel		## Desc ##
 * @st_funcMD5		129388323E9D8D7D2541218E26D05374
 * @st_funcID		LCCM655R0.FILE.092.FUNC.012
 */
void vFCU_FCTL_BLENDER__Displacement_UpdateFrom_Accel(Luint8 u8Channel, Luint32 u32Disp_mm)
{

}

//update the Displacement from the LRF
//Note: LRF may be distance remaining, need to blend properly
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Disp_mm		## Desc ##
 * @param[in]		u8Channel		## Desc ##
 * @st_funcMD5		C1359FA82075785458C825BDCA155672
 * @st_funcID		LCCM655R0.FILE.092.FUNC.013
 */
void vFCU_FCTL_BLENDER__Displacement_UpdateFrom_LRF(Luint8 u8Channel, Luint32 u32Disp_mm)
{

}

//Update the Displacement from the contrast sensor system
//Note this may be track elapsed position
/***************************************************************************//**
 * @brief
 * ToDo
 * 
 * @param[in]		u32Disp_mm		## Desc ##
 * @param[in]		u8Channel		## Desc ##
 * @st_funcMD5		EF8AE94096E136C3DE982D043F64045C
 * @st_funcID		LCCM655R0.FILE.092.FUNC.014
 */
void vFCU_FCTL_BLENDER__Displacement_UpdateFrom_Contrast(Luint8 u8Channel, Luint32 u32Disp_mm)
{

}


#endif //0
#endif //C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
#ifndef C_LOCALDEF__LCCM655__ENABLE_FLIGHT_CONTROL
	#error
#endif

#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif



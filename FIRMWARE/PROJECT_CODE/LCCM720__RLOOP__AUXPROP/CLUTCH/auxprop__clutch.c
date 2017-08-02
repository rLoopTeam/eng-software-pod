/**
 * @file		AUXPROP__CLUTCH.C
 * @brief		Clutch controller
 * @author		Lachlan Grogan
 * @st_fileID	LCCM720R0.FILE.010
 */

/**
 * @addtogroup RLOOP
 * @{
*/
/**
 * @addtogroup AUXPROP
 * @ingroup RLOOP
 * @{
*/
/**
 * @addtogroup AUXPROP__CLUTCH
 * @ingroup AUXPROP
 * @{
*/
#include <LCCM720__RLOOP__AUXPROP/auxprop.h>
#if C_LOCALDEF__LCCM720__ENABLE_THIS_MODULE == 1U

//Main structure
extern TS_APU__MAIN sAPU;

/***************************************************************************//**
 * @brief
 * Init the clutch
 * 
 * @st_funcMD5		52843EC10071D7F49FCB9CFF25BBB7EF
 * @st_funcID		LCCM720R0.FILE.010.FUNC.001
 */
void vAPU_CLUTCH__Init(void)
{
	
	sAPU.sClutch.u8State = CLUTCH_STATE__DISENGAGED;
	
#ifndef WIN32

	//clutch is on A2
	vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_A, 2U, GIO_DIRECTION__OUTPUT);

	//disenage clutch
	vAPU_CLUTCH__Disengage();
#endif

}

/***************************************************************************//**
 * @brief
 * Process any clutch functions
 * 
 * @st_funcMD5		F2E937BB6CA0BB2B0D5D39DE84F8FF49
 * @st_funcID		LCCM720R0.FILE.010.FUNC.002
 */
void vAPU_CLUTCH__Process(void)
{
	//do nothing.
	
}

/***************************************************************************//**
 * @brief
 * Engage the clutch
 * 
 * @st_funcMD5		0C31C29DC205143A2C3D76A2FEAA4C14
 * @st_funcID		LCCM720R0.FILE.010.FUNC.003
 */
void vAPU_CLUTCH__Engage(void)
{
#ifndef WIN32
	//set the IO port
	vRM4_GIO__Set_Bit(RM4_GIO__PORT_A, 2U, 1U);
#endif
	//set the state
	sAPU.sClutch.u8State = CLUTCH_STATE__ENGAGED;

	
#ifdef WIN32
	vAPU_WIN32__Send_Generic_Update();
#endif

}

/***************************************************************************//**
 * @brief
 * Disengage the clutch
 * 
 * @st_funcMD5		30C82A1C49A5485CBA5E4385DE0B1955
 * @st_funcID		LCCM720R0.FILE.010.FUNC.004
 */
void vAPU_CLUTCH__Disengage(void)
{
#ifndef WIN32
	//set the IO port
	vRM4_GIO__Set_Bit(RM4_GIO__PORT_A, 2U, 0U);
#endif
	//set the state
	sAPU.sClutch.u8State = CLUTCH_STATE__DISENGAGED;

#ifdef WIN32
	vAPU_WIN32__Send_Generic_Update();
#endif

}



#endif //#if C_LOCALDEF__LCCM720__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM720__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */


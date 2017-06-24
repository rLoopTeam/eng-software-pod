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
 * @st_funcMD5		A9C4EFDFE2796F7B98FCE5E1CAAA5E0D
 * @st_funcID		LCCM720R0.FILE.010.FUNC.001
 */
void vAPU_CLUTCH__Init(void)
{
	
	sAPU.sClutch[AUXPROP_SIDE__LEFT].u8State = CLUTCH_STATE__DISENGAGED;
	sAPU.sClutch[AUXPROP_SIDE__RIGHT].u8State = CLUTCH_STATE__DISENGAGED;
	
#ifndef WIN32
	 //J4:1		N2HET1:2		LEFT_CLUTCH
	 //J4:2		N2HET1:18		RIGHT_CLUTCH
	//setup the outputs
	vRM4_N2HET_PINS__Set_PinDirection_Output(N2HET_CHANNEL__1, 2U);
	vRM4_N2HET_PINS__Set_PinDirection_Output(N2HET_CHANNEL__1, 18U);

	//disenage clutch
	vAPU_CLUTCH__Disengage(AUXPROP_SIDE__LEFT);
	vAPU_CLUTCH__Disengage(AUXPROP_SIDE__RIGHT);
#endif

}

/***************************************************************************//**
 * @brief
 * Process any clutch functions
 * 
 * @st_funcMD5		1A23B184AA88915B649646C5D3D89A84
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
 * @param[in]		eSide				Side of the pod, left or right
 * @st_funcMD5		C27E1A9932AB7414147242E44D0CBEB5
 * @st_funcID		LCCM720R0.FILE.010.FUNC.003
 */
void vAPU_CLUTCH__Engage(TE_RLOOP_AUXPROP__SIDE eSide)
{
	
	switch(eSide)
	{
		case AUXPROP_SIDE__LEFT:
			sAPU.sClutch[AUXPROP_SIDE__LEFT].u8State = CLUTCH_STATE__ENGAGED;

#ifndef WIN32
			vRM4_N2HET_PINS__Set_Pin(N2HET_CHANNEL__1, 2U, 1U);
#endif
			break;
		
		case AUXPROP_SIDE__RIGHT:
			sAPU.sClutch[AUXPROP_SIDE__RIGHT].u8State = CLUTCH_STATE__ENGAGED;
#ifndef WIN32
			vRM4_N2HET_PINS__Set_Pin(N2HET_CHANNEL__1, 18U, 1U);
#endif
			break;
		
		default:
			//do nothing
			break;
	}//switch(eSide)
	
#ifdef WIN32
	vAPU_WIN32__Send_Generic_Update();
#endif

}

/***************************************************************************//**
 * @brief
 * Disengage the clutch
 * 
 * @param[in]		eSide				Side of the pod, left or right
 * @st_funcMD5		4CA54DF38A5A2150A068EF1B6DC0B6F9
 * @st_funcID		LCCM720R0.FILE.010.FUNC.004
 */
void vAPU_CLUTCH__Disengage(TE_RLOOP_AUXPROP__SIDE eSide)
{

	switch(eSide)
	{
		case AUXPROP_SIDE__LEFT:
			sAPU.sClutch[AUXPROP_SIDE__LEFT].u8State = CLUTCH_STATE__DISENGAGED;
#ifndef WIN32
			vRM4_N2HET_PINS__Set_Pin(N2HET_CHANNEL__1, 2U, 0U);
#endif
			break;

		case AUXPROP_SIDE__RIGHT:
			sAPU.sClutch[AUXPROP_SIDE__RIGHT].u8State = CLUTCH_STATE__DISENGAGED;
#ifndef WIN32
			vRM4_N2HET_PINS__Set_Pin(N2HET_CHANNEL__1, 18U, 0U);
#endif
			break;

		default:
			//do nothing
			break;
	}//switch(eSide)

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


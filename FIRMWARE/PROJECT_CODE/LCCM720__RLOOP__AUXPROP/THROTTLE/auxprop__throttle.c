/**
 * @file		AUXPROP__THROTTLE.C
 * @brief		Throttle and direction control
 * @author		Lachlan Grogan
 * @st_fileID	LCCM720R0.FILE.006
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
 * @addtogroup AUXPROP__THROTTLE
 * @ingroup AUXPROP
 * @{
*/
#include <LCCM720__RLOOP__AUXPROP/auxprop.h>
#if C_LOCALDEF__LCCM720__ENABLE_THIS_MODULE == 1U

//Main structure
extern TS_APU__MAIN sAPU;

/***************************************************************************//**
 * @brief
 * Init the throttles
 * 
 * @st_funcMD5		2537A69CD83D3B913E3CDC4D9106085B
 * @st_funcID		LCCM720R0.FILE.006.FUNC.001
 */
void vAPU_THROTTLE__Init(void)
{
	
	sAPU.sThrottle[AUXPROP_SIDE__LEFT].u8Direction = THROTTLE_DIR__FORWARD;
	sAPU.sThrottle[AUXPROP_SIDE__RIGHT].u8Direction = THROTTLE_DIR__FORWARD;

#ifndef WIN32
	//J4:3		N2HET1:16		LEFT_DIR
	//J4:4		N2HET1:30		RIGHT_DIR
	//setup the outputs
	vRM4_N2HET_PINS__Set_PinDirection_Output(N2HET_CHANNEL__1, 16U);
	vRM4_N2HET_PINS__Set_PinDirection_Output(N2HET_CHANNEL__1, 30U);

	//all motors forward
	vAPU_THROTTLE__Forward(AUXPROP_SIDE__LEFT);
	vAPU_THROTTLE__Forward(AUXPROP_SIDE__RIGHT);
#endif

}

/***************************************************************************//**
 * @brief
 * Process any throttle tasks
 * 
 * @st_funcMD5		7AF6CF6FF6DF97CEC3CC9FA8D141DBDD
 * @st_funcID		LCCM720R0.FILE.006.FUNC.002
 */
void vAPU_THROTTLE__Process(void)
{
	
	//do nothing.
}

/***************************************************************************//**
 * @brief
 * Set direction forward
 * 
 * @param[in]		eSide				The side of the pod, left or right
 * @st_funcMD5		D589C2BE85D5D9F37CB603713A5BBE7D
 * @st_funcID		LCCM720R0.FILE.006.FUNC.003
 */
void vAPU_THROTTLE__Forward(TE_RLOOP_AUXPROP__SIDE eSide)
{

	switch(eSide)
	{
		case AUXPROP_SIDE__LEFT:
			sAPU.sThrottle[AUXPROP_SIDE__LEFT].u8Direction = THROTTLE_DIR__FORWARD;
#ifndef WIN32
			vRM4_N2HET_PINS__Set_Pin(N2HET_CHANNEL__1, 16U, 1U);
#endif
			break;

		case AUXPROP_SIDE__RIGHT:
			sAPU.sThrottle[AUXPROP_SIDE__RIGHT].u8Direction = THROTTLE_DIR__FORWARD;
#ifndef WIN32
			vRM4_N2HET_PINS__Set_Pin(N2HET_CHANNEL__1, 30U, 1U);
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
 * Set direction in reverse
 * 
 * @param[in]		eSide				The side of the pod, left or right
 * @st_funcMD5		DD60FFA15828F1917607B54E8132E2B5
 * @st_funcID		LCCM720R0.FILE.006.FUNC.004
 */
void vAPU_THROTTLE__Reverse(TE_RLOOP_AUXPROP__SIDE eSide)
{

	switch(eSide)
	{
		case AUXPROP_SIDE__LEFT:
			sAPU.sThrottle[AUXPROP_SIDE__LEFT].u8Direction = THROTTLE_DIR__REVERSE;
#ifndef WIN32
			vRM4_N2HET_PINS__Set_Pin(N2HET_CHANNEL__1, 16U, 0U);
#endif
			break;

		case AUXPROP_SIDE__RIGHT:
			sAPU.sThrottle[AUXPROP_SIDE__RIGHT].u8Direction = THROTTLE_DIR__REVERSE;
#ifndef WIN32
			vRM4_N2HET_PINS__Set_Pin(N2HET_CHANNEL__1, 30U, 0U);
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


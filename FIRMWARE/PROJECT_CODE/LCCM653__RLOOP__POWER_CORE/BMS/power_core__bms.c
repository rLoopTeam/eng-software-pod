/**
 * @file		POWER_CORE__BMS.C
 * @brief		Battery Management Interface Layer
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 * @st_fileID	LCCM653R0.FILE.008
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup POWER_NODE__BMS
 * @ingroup POWER_NODE
 * @{ */


#include "../power_core.h"
#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
#if C_LOCALDEF__LCCM653__ENABLE_BMS == 1U

extern struct _strPWRNODE sPWRNODE;

/***************************************************************************//**
 * @brief
 * Init the battery management system
 * 
 * @st_funcMD5		270D9FCF297F4E126AB47ABD1EAA4572
 * @st_funcID		LCCM653R0.FILE.008.FUNC.001
 */
void vPWRNODE_BMS__Init(void)
{

#ifndef WIN32
	#if C_LOCALDEF__BMS_REVISION == 1U
		//init the ATA6870 driver
		vATA6870__Init();

	#elif C_LOCALDEF__BMS_REVISION == 2U

		sPWRNODE.sBMS.f32StateOfCharge = 0;

		//configure the IO ports

		//Comms Enable
		vRM4_GIO__Set_BitDirection(RM4_GIO__PORT_A, 7U, GIO_DIRECTION__OUTPUT);
		vRM4_GIO__Set_Bit(RM4_GIO__PORT_A, 7U, 1U);

		//NCS
		vRM4_MIBSPI135_PINS__Set_OutputDirection(MIBSPI135_CHANNEL__3, MIBSPI135_PIN__CS1);

		//convert
		vRM4_N2HET_PINS__Set_PinDirection_Output(N2HET_CHANNEL__1, 2U);

		//Fault
		vRM4_N2HET_PINS__Set_PinDirection_Input(N2HET_CHANNEL__1, 18U);

		//Data Ready
		vRM4_N2HET_PINS__Set_PinDirection_Input(N2HET_CHANNEL__1, 16U);

		//Alert Pin
		vRM4_N2HET_PINS__Set_PinDirection_Input(N2HET_CHANNEL__1, 22U);

		//init the BQ driver
		vBQ76__Init();
	#else
		#error
	#endif
#endif

	vPWRNODE_BMS_FANS__Init();

	//setup any ethernet systems.
	vPWR_BMS_ETH__Init();


}

/***************************************************************************//**
 * @brief
 * Process any battery management system items
 * 
 * @st_funcMD5		15B2FAA1BAD482B0EC323B1CBE361248
 * @st_funcID		LCCM653R0.FILE.008.FUNC.002
 */
void vPWRNODE_BMS__Process(void)
{
    Lfloat32 f32Temp;
    Lfloat32 f32MaxV;
    Lfloat32 f32MinV;

#ifndef WIN32
	#if C_LOCALDEF__BMS_REVISION == 1U
		//process any ATA6870 tasks
		vATA6870__Process();
	#elif C_LOCALDEF__BMS_REVISION == 2U
		vBQ76__Process();
		vPWRNODE_BMS_FANS__Process();

		//Verify all cells are above the minimum voltage spec
		if(f32BQ76_CELLS__Get_LowestVoltage() <= C_PWRCORE__UNDERVOLTAGE_KILL)
		{
            #if C_LOCALDEF__LCCM653__ENABLE_DC_CONVERTER == 1U
		        vPWRNODE_DC__Pod_Safe_Go();
            #endif
		    //TODO: set fault flag
		}else{
		    //Nothing to do
		    //TODO: clear fault flag
		}

		//Verify all cells are below the maximum voltage spec
        if(f32BQ76_CELLS__Get_HighestVoltage() >= C_PWRCORE__OVERVOLTAGE_KILL)
        {
            #if C_LOCALDEF__LCCM653__ENABLE_DC_CONVERTER == 1U
                vPWRNODE_DC__Pod_Safe_Go();
            #endif
            //TODO: set fault flag
        }else{
            //Nothing to do
            //TODO: clear fault flag
        }

        //TODO: Check voltage update count

        //Move to 10 ms ISR?
        f32MaxV = C_PWRCORE__OVERVOLTAGE_KILL-.1;
        f32MinV = C_PWRCORE__UNDERVOLTAGE_KILL+.1;
        f32Temp = ((f32PWRNODE_BMS__Cell_Get_LowestVoltage() - f32MinV)/(f32MaxV - f32MinV))*100.0F;
        if(f32Temp < 0 || f32Temp > 100){
            //TODO: Fault
        }else{
            sPWRNODE.sBMS.f32StateOfCharge = f32Temp;
        }

	#else
		#error
	#endif
#endif
}

Luint32 u32PWRNODE_BMS__Get_DeviceFlags(Luint8 u8DeviceIndex)
{
#if C_LOCALDEF__BMS_REVISION == 1U
	return 0xFFFFFFFFU;
#elif C_LOCALDEF__BMS_REVISION == 2U
	return u32BQ76__Get_FaultFlags(u8DeviceIndex);
#else
	#error
#endif

}


/***************************************************************************//**
 * @brief
 * Get the highest cell voltage
 * 
 * @st_funcMD5		CCDA9D0AA2A185CC2B0AED32C6C65C05
 * @st_funcID		LCCM653R0.FILE.008.FUNC.003
 */
Lfloat32 f32PWRNODE_BMS__Cell_Get_HighestVoltage(void)
{
	#if C_LOCALDEF__BMS_REVISION == 1U
		return f32ATA6870_CELL__Get_HighestVoltage();
	#elif C_LOCALDEF__BMS_REVISION == 2U
		return f32BQ76_CELLS__Get_HighestVoltage();
	#else
		#error
	#endif
}

/***************************************************************************//**
 * @brief
 * Returns the last computed lowest cell voltage.
 * 
 * @st_funcMD5		71C954368FC27625363D95A446DA7B32
 * @st_funcID		LCCM653R0.FILE.008.FUNC.007
 */
Lfloat32 f32PWRNODE_BMS__Cell_Get_LowestVoltage(void)
{
	#if C_LOCALDEF__BMS_REVISION == 1U
		return f32ATA6870_CELL__Get_LowestVoltage();
	#elif C_LOCALDEF__BMS_REVISION == 2U
		return f32BQ76_CELLS__Get_LowestVoltage();
	#else
		#error
	#endif
}

/***************************************************************************//**
 * @brief
 * Returns the entire pack voltage
 * 
 * @st_funcMD5		1FEB2A9DBECB7ED0651F480855A300D6
 * @st_funcID		LCCM653R0.FILE.008.FUNC.004
 */
Lfloat32 f32PWRNODE_BMS__Get_PackVoltage(void)
{

	#if C_LOCALDEF__BMS_REVISION == 1U
		return f32ATA6870_CELL__Get_PackVoltage();
	#elif C_LOCALDEF__BMS_REVISION == 2U
		return f32BQ76_BATTERY__Get_PackVoltage();
	#else
		#error
	#endif
}


/***************************************************************************//**
 * @brief
 * Start the balance process.
 * 
 * @st_funcMD5		A4A94DAE9A680CCCF72DBE546F52ED5F
 * @st_funcID		LCCM653R0.FILE.008.FUNC.005
 */
void vPWRNODE_BMS__Balance_Start(void)
{
	#if C_LOCALDEF__BMS_REVISION == 1U
		vATA6870_BALANCE__Start();
	#elif C_LOCALDEF__BMS_REVISION == 2U
		vBQ76_BALANCE__Start();
	#else
		#error
	#endif

}


/***************************************************************************//**
 * @brief
 * Is the balancer busy?
 * 
 * @st_funcMD5		4B308ED45EA0D643CDA7B851220C95A7
 * @st_funcID		LCCM653R0.FILE.008.FUNC.006
 */
Luint8 u8PWRNODE_BMS__Balance_IsBusy(void)
{
	#if C_LOCALDEF__BMS_REVISION == 1U
		return u8ATA6870_BALANCE__Is_Busy();
	#elif C_LOCALDEF__BMS_REVISION == 2U
		return u8BQ76_BALANCE__Is_Busy();
	#else
		#error
	#endif

}


/***************************************************************************//**
 * @brief
 * Stop balance immediate
 * 
 * @st_funcMD5		94B33EB600AA0ACD3DD21B166CE76587
 * @st_funcID		LCCM653R0.FILE.008.FUNC.008
 */
void vPWRNODE_BMS__Balance_Stop(void)
{
	#if C_LOCALDEF__BMS_REVISION == 1U
		vATA6870_BALANCE__Stop();
	#elif C_LOCALDEF__BMS_REVISION == 2U
		vBQ76_BALANCE__Stop();
	#else
		#error
	#endif

}

/***************************************************************************//**
 * @brief
 * Enable manual balancing on a particular cell
 * 
 * @param[in]		u8Enable				1 = Enable
 * @param[in]		u8CellIndex				Zero based cell index for all cells in the battery
 * @st_funcMD5		62BA84541AA2A37395BF6F24B081ED3D
 * @st_funcID		LCCM653R0.FILE.008.FUNC.009
 */
void vPWRNODE_BMS__Balance_Manual(Luint8 u8CellIndex, Luint8 u8Enable)
{
	#if C_LOCALDEF__BMS_REVISION == 1U
		vATA6870_BALANCE__Manual(u8CellIndex, u8Enable);
	#elif C_LOCALDEF__BMS_REVISION == 2U
		vBQ76_BALANCE__Manual(u8CellIndex, u8Enable);
	#else
		#error
	#endif

}

/***************************************************************************//**
 * @brief
 * Get the count of the number of times the voltage has been resampled.
 * This is useful for checking the speed of things
 * 
 * @st_funcMD5		985C5FB642DFF8E96E0AB41B7CAAB50F
 * @st_funcID		LCCM653R0.FILE.008.FUNC.010
 */
Luint32 u32PWRNODE_BMS__Get_VoltsUpdateCount(void)
{
	#if C_LOCALDEF__BMS_REVISION == 1U
		return u32ATA6870__Get_VoltsUpdateCount();
	#elif C_LOCALDEF__BMS_REVISION == 2U
		return u32BQ76__Get_VoltsUpdateCount();
	#else
		#error
	#endif

}


#endif //C_LOCALDEF__LCCM653__ENABLE_BMS

#endif //#if C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM653__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */


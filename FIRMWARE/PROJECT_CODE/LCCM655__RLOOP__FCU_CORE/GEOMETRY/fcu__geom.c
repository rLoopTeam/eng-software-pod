/**
 * @file		FCU__GEOM.C
 * @brief		Geometry interface, storage, etc.
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup FCU
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup FCU__GEOM
 * @ingroup FCU
 * @{ */

#include "../fcu_core.h"

//http://confluence.rloop.org/display/SD/System+Parameters

//http://confluence.rloop.org/display/SD/2.3.+Determine+Pod+Front+and+Rear+x+Position%2C+Speed+and+Acceleration+in+tube

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U

//the structure
extern struct _strFCU sFCU;


void vFCU_GEOM__Init(void)
{
	Luint8 u8Test;
	Luint8 u8Counter;
	Luint16 u16Index;

	//check the CRC
	u8Test = u8EEPARAM_CRC__Is_CRC_OK(	C_LOCALDEF__LCCM655__FCTL_GEOM___START_INDEX,
										C_LOCALDEF__LCCM655__FCTL_GEOM___END_INDEX,
										C_LOCALDEF__LCCM655__FCTL_GEOM___CRC);
	//load up the X,Y,Z pairs
	if(u8Test == 1U)
	{
		u16Index = C_LOCALDEF__LCCM655__FCTL_GEOM___START_INDEX;
		//valid
		for(u8Counter = 0U; u8Counter < C_FCU__GEOM__NUM_ITEMS_F32; u8Counter++)
		{
			vf32EEPARAM__Read(u16Index, &sFCU.sFlightControl.sGeom.vf32Geom[u8Counter]);
			u16Index += 3U;
		}

		for(u8Counter = 0U; u8Counter < C_FCU__GEOM__NUM_ITEMS_S32; u8Counter++)
		{
			vs32EEPARAM__Read(u16Index, &sFCU.sFlightControl.sGeom.vs32Geom[u8Counter]);
			u16Index += 3U;
		}

	}//if(u8Test == 1U)
	else
	{
		//CRC is invalid

		//set the start
		u16Index = C_LOCALDEF__LCCM655__FCTL_GEOM___START_INDEX;

		for(u8Counter = 0U; u8Counter < C_FCU__GEOM__NUM_ITEMS_F32; u8Counter++)
		{
			sFCU.sFlightControl.sGeom.vf32Geom[u8Counter].f32X = 0.0F;
			sFCU.sFlightControl.sGeom.vf32Geom[u8Counter].f32Y = 0.0F;
			sFCU.sFlightControl.sGeom.vf32Geom[u8Counter].f32Z = 0.0F;
			vEEPARAM__Write_VF32(u16Index, &sFCU.sFlightControl.sGeom.vf32Geom[u8Counter], DELAY_T__DELAYED_WRITE);
			u16Index += 3U;
		}

		for(u8Counter = 0U; u8Counter < C_FCU__GEOM__NUM_ITEMS_S32; u8Counter++)
		{
			sFCU.sFlightControl.sGeom.vs32Geom[u8Counter].s32X = 0;
			sFCU.sFlightControl.sGeom.vs32Geom[u8Counter].s32Y = 0;
			sFCU.sFlightControl.sGeom.vs32Geom[u8Counter].s32Z = 0;
			if(u8Counter == (C_FCU__GEOM__NUM_ITEMS_S32 - 1))
			{
				vEEPARAM__Write_VS32(u16Index, &sFCU.sFlightControl.sGeom.vs32Geom[u8Counter], DELAY_T__IMMEDIATE_WRITE);
			}
			else
			{
				vEEPARAM__Write_VS32(u16Index, &sFCU.sFlightControl.sGeom.vs32Geom[u8Counter], DELAY_T__DELAYED_WRITE);
			}
			u16Index += 3U;
		}

		//redo the CRC;
		vEEPARAM_CRC__Calculate_And_Store_CRC(	C_LOCALDEF__LCCM655__FCTL_GEOM___START_INDEX,
												C_LOCALDEF__LCCM655__FCTL_GEOM___END_INDEX,
												C_LOCALDEF__LCCM655__FCTL_GEOM___CRC);



	}

	//init any eth needs
	vFCU_GEOM_ETH__Init();

}



void vFCU_GEOM__Process(void)
{

}


#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */


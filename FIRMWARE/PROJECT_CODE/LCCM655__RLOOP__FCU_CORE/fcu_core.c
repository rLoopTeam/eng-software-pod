/**
 * @file		FCU_CORE.C
 * @brief		Core of the flight control unit
 * @author		Lachlan Grogan
 * @copyright	rLoop Inc.
 * @st_fileID	LCCM655R0.FILE.000
 */
/**
 * @addtogroup RLOOP
 * @{ */
/**
 * @addtogroup FCU
 * @ingroup RLOOP
 * @{ */
/**
 * @addtogroup FCU__CORE
 * @ingroup FCU
 * @{ */

#include "fcu_core.h"

#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U

struct _strFCU sFCU;

/***************************************************************************//**
 * @brief
 * Init the FCU. Call this first thing.
 * 
 * @st_funcMD5		CC1CE932DF70839CDB882B5F32B8106A
 * @st_funcID		LCCM655R0.FILE.000.FUNC.001
 */
void vFCU__Init(void)
{

	//init any FCU variabes
	sFCU.eInitStates = INIT_STATE__RESET;
}


/***************************************************************************//**
 * @brief
 * Process any FCU tasks.
 * 
 * @st_funcMD5		05CF3F7820A29ABF562E522CC9365071
 * @st_funcID		LCCM655R0.FILE.000.FUNC.002
 */
void vFCU__Process(void)
{

	//process the states
	switch(sFCU.eInitStates)
	{
		case INIT_STATE__RESET:
			//first state after reset, handle some RM4 tasks

			//setup flash memory access
			vRM4_FLASH__Init();

			//GIO
			vRM4_GIO__Init();

			//change state
			sFCU.eInitStates = INIT_STATE__INIT_COMMS;
			break;

		case INIT_STATE__INIT_COMMS:

			//setup UART, SCI2 = Pi Connection
			vRM4_SCI__Init(SCI_CHANNEL__2);
			vRM4_SCI__Set_Baudrate(SCI_CHANNEL__2, 9600U);

			//setup our SPI channels.
			//ASI Interface
			vRM4_MIBSPI135__Init(MIBSPI135_CHANNEL__1);

			//Serial channel's A
			vRM4_MIBSPI135__Init(MIBSPI135_CHANNEL__3);

			//serial subsystem B
			vRM4_SPI24__Init(SPI24_CHANNEL__2);

			//init the I2C
			sFCU.eInitStates = INIT_STATE__INIT_SPI_UARTS;
			break;

		case INIT_STATE__INIT_SPI_UARTS:

			//init all 7 of our uarts
			vSC16__Init(0);
			vSC16__Init(1);
			vSC16__Init(2);
			vSC16__Init(3);
			vSC16__Init(4);
			vSC16__Init(5);
			vSC16__Init(6);
			vSC16__Init(7);

			//move state
			sFCU.eInitStates = INIT_STATE__RUN;
			break;

		case INIT_STATE__RUN:

			break;

	}//switch(sFCU.eInitStates)

}

#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U
//safetys
#ifndef C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE
	#error
#endif
/** @} */
/** @} */
/** @} */


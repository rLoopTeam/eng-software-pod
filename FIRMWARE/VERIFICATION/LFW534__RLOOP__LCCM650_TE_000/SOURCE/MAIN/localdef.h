

#ifndef LOCALDEF_H_
#define LOCALDEF_H_

	/*lint -e950*/

	//Run on RM48 CNCD
	#include <../../../../BOARD_SUPPORT/lpcb234r0__board_support.h>

	//disable I2C module from the main board support file.
	/*lint -e960*/
	#undef C_LOCALDEF__LCCM215__ENABLE_THIS_MODULE
	#define C_LOCALDEF__LCCM215__ENABLE_THIS_MODULE 0
	/*lint +e960*/

/*******************************************************************************
SOFTWARE BASED CRC
*******************************************************************************/
	#define C_LOCALDEF__LCCM012__ENABLE_THIS_MODULE							1U
	#if C_LOCALDEF__LCCM012__ENABLE_THIS_MODULE == 1U

		//types of CRC
		#define C_LOCALDEF__LCCM012__ENABLE_CRC7							0U
		#define C_LOCALDEF__LCCM012__ENABLE_CRC8							1U
		#define C_LOCALDEF__LCCM012__ENABLE_CRC16							1U

		//set to 1 to enable test specification code
		#define C_LOCALDEF__LCCM012__ENABLE_TEST_SPEC						0U

		//set to 1 to enable table based CRC16
		//Note: Not possible on PIC18 due to page sizes
		#define C_LOCALDEF__LCCM012__ENABLE_TABLE_BASED_CRC					1U

		//if using tables, define any alignment issues
		#if C_LOCALDEF__LCCM012__ENABLE_TABLE_BASED_CRC == 1U
			#ifndef WIN32
				#define C_LOCALDEF__LCCM012__TABLE16_DEF const Luint16 u16SWCRC_CRC_TABLE[] __attribute__ ((aligned (128)))
			#else
				//no alignment possible on win32.
				#define C_LOCALDEF__LCCM012__TABLE16_DEF static Luint16 u16SWCRC_CRC_TABLE[]
			#endif
		#endif //C_LOCALDEF__LCCM012__ENABLE_TABLE_BASED_CRC

		#include <MULTICORE/LCCM012__MULTICORE__SOFTWARE_CRC/software_crc.h>

	#endif


/*******************************************************************************
GENERAL PURPOSE
SOFTWARE FIFO
*******************************************************************************/
	#define C_LOCALDEF__LCCM357__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM357__ENABLE_THIS_MODULE == 1U

		//testing options
		#define C_LOCALDEF__LCCM357__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <MULTICORE/LCCM357__MULTICORE__SOFTWARE_FIFO/software_fifo.h>

	#endif //C_LOCALDEF__LCCM357__ENABLE_THIS_MODULE

/*******************************************************************************
ATA6870N - BATTERY MANAGEMENT DEVICE
*******************************************************************************/
	#define C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE == 1U

		//architecture
		#define C_LOCALDEF__LCCM650__USE_ON_RM4								(1U)

		/** number of devices in series */
		#define C_LOCALDEF__LCCM650__NUM_DEVICES							(1U)

		/** Use checksum support on the ATA comms or not? */
		#define C_LOCALDEF__LCCM650__ENABLE_CRC								(0U)

		//setup for functions

		#define M_LOCALDEF__LCCM650__NCS_TRIS(dir)							{if(dir == 0U) vRM4_GIO__Set_BitDirection(gioPORTB, 4U, GIO_DIRECTION__OUTPUT); else vRM4_GIO__Set_BitDirection(gioPORTB, 4U, GIO_DIRECTION__INPUT);}
		#define M_LOCALDEF__LCCM650__NCS_LATCH(val)							{vRM4_GIO__Set_Bit(gioPORTB, 4U, val);}
		#define M_LOCALDEF__LCCM650__SPI_TX_U8(x)							u8RM4_MIBSPI135__Tx_U8(MIBSPI135_CHANNEL__1, MIBSPI135_DATA_FORMAT__0, MIBSPI135_CS__NONE, x)

		#define M_LOCALDEF__LCCM650__POWER_ENABLE_TRIS(x)					{if(x == 0U) vRM4_GIO__Set_BitDirection(gioPORTB, 2U, GIO_DIRECTION__OUTPUT); else vRM4_GIO__Set_BitDirection(gioPORTB, 2U, GIO_DIRECTION__INPUT); }
		#define M_LOCALDEF__LCCM650__POWER_ENABLE_LATCH(x)					{vRM4_GIO__Set_Bit(gioPORTB, 2U, x); }

		#define M_LOCALDEF__LCCM650__POWER_AVAIL_TRIS(x)					{if(x == 0U) vRM4_GIO__Set_BitDirection(gioPORTB, 5U, GIO_DIRECTION__OUTPUT); else vRM4_GIO__Set_BitDirection(gioPORTB, 5U, GIO_DIRECTION__INPUT); }
		#define M_LOCALDEF__LCCM650__POWER_AVAIL_PORT()						u32RM4_GIO__Get_Bit(gioPORTB, 5U)

		/** Testing Options */
		#define C_LOCALDEF__LCCM650__ENABLE_TEST_SPEC						(0U)


		/** Main include file */
		#include <MULTICORE/LCCM650__MULTICORE__ATA6870/ata6870.h>
	#endif //#if C_LOCALDEF__LCCM650__ENABLE_THIS_MODULE == 1U


	/*lint +e950*/
	


#endif /* LOCALDEF_H_ */

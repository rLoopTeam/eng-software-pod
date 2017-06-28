

#ifndef _RM57L843_LAUNCHPAD__BSP_H_
#define _RM57L843_LAUNCHPAD__BSP_H_

/*******************************************************************************
RM4 MAIN SYSTEM SETUP
Place this at the top of your Localdef file
Change the build settings:
1. Enable GCC extensions under advanced options -> language options
2. Enable unaligned loads and stores to on
3. Make sure designate enum type is packed.

*******************************************************************************/
	/*lint -e950 */
	/*lint -e621 */

#ifndef WIN32
	#include "sil3_generic__cpu.h"
#else
	#include "../sil3_generic__cpu_win32.h"
#endif
	
	//data types
	#include <RM4/LCCM105__RM4__BASIC_TYPES/basic_types.h>

	//set this to 1 to disable all common startups as would be used by a bootloader
	#define C_LOCALDEF__SYSTEM__DISABLE_ALL_FOR_BOOTLOADER					(0U)

	//change osc freq to match the osc on your board
	//valid values are 10 and 16MHZ
	#define C_LOCALDEF__SYSTEM__OSCILLATOR_FREQ     						(16000000U)

	//This is the HCLK frequency, it is not defined here, but is a result of the
	//PLL1 setup.  Standard range is 200MHZ to 220MHZ (952 part)
	//Valid Is:
	//220
	//200 (Standard)
	//150 (Low Power) + RM57
	//100 (Low Power)
	#define C_LOCALDEF__SYSTEM__HCLK_FREQ_MHZ								(150U)

	//normal bus division is either 1 or 2
	//In 1x mode, VCLK1 is 100MHZ, in 2x mode VCLK is 50MHZ
	//you may only need 2x mode if you need ultra lo SPI comms, etc.
	#define C_LOCALDEF__SYSTEM__VCLK1_DIVISOR								(1U)


	//just here because of no EMIF
	//if ou are using EMIF, then remove this line
	#define C_LOCALDEF__LCCM107__EMIF_CLOCK_DIVISOR							(1U)

	//we have the ability to use the ECLK pin to generate a high frequency divided
	//clock signal, possibly faster than we can do with PWM
	#define C_LOCALDEF__SYSTEM__ENABLE_ECLK									(1U)

	//150MHZ HCKL = 75MHZ VCLK /=3 = 25MHZ to the PHY
	#define C_LOCALDEF__SYSTEM__ECLK_DIVISOR								(3U)

	//other includes
	#include <RM4/LCCM219__RM4__SYSTEM/rm4_system.h>

	#include <RM4/LCCM364__RM4__FIRMWARE_VERSION/rm4_firmware_version.h>

/*******************************************************************************
RM4 CRC MODULE
*******************************************************************************/
	#define C_LOCALDEF__LCCM226__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM226__ENABLE_THIS_MODULE == 1U

		//testing options
		#define C_LOCALDEF__LCCM226__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <RM4/LCCM226__RM4__CRC/rm4_crc.h>

	#endif //C_LOCALDEF__LCCM226__ENABLE_THIS_MODULE

/*******************************************************************************
RM48 - CPU LOAD MEASUREMENT
*******************************************************************************/
	#define C_LOCALDEF__LCCM663__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM663__ENABLE_THIS_MODULE == 1U

		/** The filtering size for the percentage trend */
		#define C_LOCALDEF__LCCM663__FILTER_WINDOW							(8U)

		/** Testing Options */
		#define C_LOCALDEF__LCCM663__ENABLE_TEST_SPEC						(0U)

		/** Main include file */
		#include <RM4/LCCM663__RM4__CPU_LOAD/rm4_cpuload.h>
	#endif //#if C_LOCALDEF__LCCM663__ENABLE_THIS_MODULE == 1U

/*******************************************************************************
BUILT IN SELF TEST MODULE
*******************************************************************************/
	#define C_LOCALDEF__LCCM227__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM227__ENABLE_THIS_MODULE == 1U

		//testing options
		#define C_LOCALDEF__LCCM227__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <RM4/LCCM227__RM4__BIST/rm4_bist.h>

	#endif //C_LOCALDEF__LCCM227__ENABLE_THIS_MODULE



/*******************************************************************************
FLASH MODULE
Even if you don't want in system programming or firmware update features
include this to get access to the flash registers and setup features
*******************************************************************************/
	#define C_LOCALDEF__LCCM135__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM135__ENABLE_THIS_MODULE == 1U

		//enable F021
		#define C_LOCALDEF__LCCM135__ENABLE_F021							(1U)

		//testing options
		#define C_LOCALDEF__LCCM135__ENABLE_TEST_SPEC						(0U)

		#include <RM4/LCCM135__RM4__FLASH/rm4_flash.h>

	#endif //#if C_LOCALDEF__LCCM135__ENABLE_THIS_MODULE == 1U


/*******************************************************************************
RM4 DELAY ROUTINES
*******************************************************************************/
	#define C_LOCALDEF__LCCM228__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM228__ENABLE_THIS_MODULE == 1U

		//Testing options
		#define C_LOCALDEF__LCCM228__ENABLE_TEST_SPEC						(0U)

		//enable the PMU if needed
		#define C_LOCALDEF__LCCM288__ENABLE_PMU_FOR_DEBUG					(0U)

		//main include file
		#include <RM4/LCCM228__RM4__DELAYS/rm4_delays.h>

	#endif //C_LOCALDEF__LCCM228__ENABLE_THIS_MODULE
	

/*******************************************************************************
ERROR SIGNALLING MODULE
*******************************************************************************/
	#define C_LOCALDEF__LCCM220__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM220__ENABLE_THIS_MODULE == 1U

		//testing options
		#define C_LOCALDEF__LCCM220__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <RM4/LCCM220__RM4__ERROR_SIGNAL_MODULE/rm4_esm.h>

	#endif //C_LOCALDEF__LCCM220__ENABLE_THIS_MODULE

/*******************************************************************************
SELFTEST MODULE
*******************************************************************************/
	#define C_LOCALDEF__LCCM221__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM221__ENABLE_THIS_MODULE == 1U

		//testing options
		#define C_LOCALDEF__LCCM221__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <RM4/LCCM221__RM4__SELFTEST/rm4_selftest.h>

	#endif //C_LOCALDEF__LCCM221__ENABLE_THIS_MODULE

/*******************************************************************************
RM57 - PERIPH CENTRAL RESOURCE
*******************************************************************************/
	#define C_LOCALDEF__LCCM708__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM708__ENABLE_THIS_MODULE == 1U

		/** Testing options */
		#define C_LOCALDEF__LCCM708__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <RM57/LCCM708__RM57__PERIPH_CENTRAL_RESOURCE/rm57_pcr.h>

	#endif //C_LOCALDEF__LCCM708__ENABLE_THIS_MODULE

/*******************************************************************************
RM4 DMA Module
*******************************************************************************/
	#define C_LOCALDEF__LCCM229__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM229__ENABLE_THIS_MODULE == 1U

		//testing options
		#define C_LOCALDEF__LCCM229__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <RM4/LCCM229__RM4__DMA/rm4_dma.h>

	#endif //C_LOCALDEF__LCCM229__ENABLE_THIS_MODULE

/*******************************************************************************
RM57 - PIN MUX SYSTEM
*******************************************************************************/
#ifndef WIN32
	#define C_LOCALDEF__LCCM709__ENABLE_THIS_MODULE							(1U)
#else
	#define C_LOCALDEF__LCCM709__ENABLE_THIS_MODULE							(0U)
#endif
	#if C_LOCALDEF__LCCM709__ENABLE_THIS_MODULE == 1U

		//testing options
		#define C_LOCALDEF__LCCM709__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <RM57/LCCM709__RM57__PIN_MUX/rm57_pinmux.h>

	#endif //C_LOCALDEF__LCCM709__ENABLE_THIS_MODULE
	

/*******************************************************************************
VECTORED INTERRUPT MODULE
*******************************************************************************/
	#define C_LOCALDEF__LCCM225__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM225__ENABLE_THIS_MODULE == 1U

		//testing options
		#define C_LOCALDEF__LCCM225__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <RM4/LCCM225__RM4__VECTORED_ISR_MGR/rm4_vim.h>

	#endif //C_LOCALDEF__LCCM225__ENABLE_THIS_MODULE


/*******************************************************************************
SCI / LIN Module
*******************************************************************************/
	#define C_LOCALDEF__LCCM282__ENABLE_THIS_MODULE							(0U)
	#if C_LOCALDEF__LCCM282__ENABLE_THIS_MODULE == 1U

		//if you have to do debugging
		#define DEBUG_PRINT(x)												vRM4_SCI_HELPERS__DisplayText(SCI_CHANNEL__2, x, 100)

		//enable interrupts, else use polling Mode
		#define C_LOCALDEF__LCCM282__ENABLE_INTERRUPTS						(0U)

		/** Switch on DMA functions */
		#define C_LOCALDEF__LCCM282__ENABLE_DMA								(0U)

		//determine which SCI module to enable
		//SCI1 shares pins with EMAC
		#define C_LOCALDEF__LCCM282__ENABLE_SCI_1							(0U)

		//SCI 2 is also LIN and uses the LIN pins on ZWT Package
		//SCI2 is USB debug on HDK
		#define C_LOCALDEF__LCCM282__ENABLE_SCI_2							(1U)


		//main include file
		#include <RM4/LCCM282__RM4__SCI/rm4_sci.h>

	#else
		#define DEBUG_PRINT(x)
	#endif //C_LOCALDEF__LCCM282__ENABLE_THIS_MODULE


/*******************************************************************************
SafeTool Branch Analysis Support
*******************************************************************************/
#ifdef PCLINT_ENABLED
	#define C_LOCALDEF__LCCM517__ENABLE_THIS_MODULE							(0U)
#else
	#define C_LOCALDEF__LCCM517__ENABLE_THIS_MODULE							(0U)
#endif	
	#if C_LOCALDEF__LCCM517__ENABLE_THIS_MODULE == 1U

		/** The maximum number of branch calls permissible, adjust as necessary
		 * depening on function size and test environment.
		 */
		#define C_LOCALDEF__LCCM517__MAX_BRANCH_CALLS						(16U)


		/** Testing Options */
		#define C_LOCALDEF__LCCM517__ENABLE_TEST_SPEC						(0U)


		/** Main include file */
		#include <MULTICORE/LCCM517__MULTICORE__SAFETOOL_BRANCH/safetool_branch.h>
	#else
		//placeholder
		#define SAFETOOL_BRANCH(stFuncID)
	#endif //#if C_LOCALDEF__LCCM517__ENABLE_THIS_MODULE == 1U

	
/*******************************************************************************
SOFTWARE MULTIPURPOSE FAULT TREE HANDLER
*******************************************************************************/
	#define C_LOCALDEF__LCCM284__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM284__ENABLE_THIS_MODULE == 1U

		//testing options
		#define C_LOCALDEF__LCCM284__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <MULTICORE/LCCM284__MULTICORE__FAULT_TREE/fault_tree.h>

	#endif //C_LOCALDEF__LCCM284__ENABLE_THIS_MODULE

/*******************************************************************************
SIL3 - SOFTWARE BASED CRC
*******************************************************************************/
	#define C_LOCALDEF__LCCM012__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM012__ENABLE_THIS_MODULE == 1U

		//set to 1 to enable test specification code
		#define C_LOCALDEF__LCCM012__ENABLE_TEST_SPEC						(0U)

		//types of CRC
		#define C_LOCALDEF__LCCM012__ENABLE_CRC7							(0U)
		#define C_LOCALDEF__LCCM012__ENABLE_CRC8							(1U)
		#define C_LOCALDEF__LCCM012__ENABLE_CRC16							(1U)

		//set to 1 to enable table based CRC16
		//Note: Not possible on PIC18 due to page sizes
		#define C_LOCALDEF__LCCM012__ENABLE_TABLE_BASED_CRC					(1U)


		#if C_LOCALDEF__LCCM012__ENABLE_CRC16 == 1U

			//if using tables, define any alignment issues
			#if C_LOCALDEF__LCCM012__ENABLE_TABLE_BASED_CRC == 1U
				#ifndef WIN32
					#define C_LOCALDEF__LCCM012__TABLE16_DEF const Luint16 u16SWCRC_CRC_TABLE[] __attribute__ ((aligned (128)))
				#else
					//no alignment possible on win32.
					#define C_LOCALDEF__LCCM012__TABLE16_DEF const Luint16 u16SWCRC_CRC_TABLE[]
				#endif
			#endif //C_LOCALDEF__LCCM012__ENABLE_TABLE_BASED_CRC
		#endif

		#include <MULTICORE/LCCM012__MULTICORE__SOFTWARE_CRC/software_crc.h>

	#endif

/*******************************************************************************
SIL3 - RM4 N2HET DRIVER
General Configuration
HR Clock = 100MHZ
VCLK2 = 100Mhz, Actual HR Clock = 100MHZ
Loop Time = 100ns
LR Time = 160ns
*******************************************************************************/
#ifndef WIN32
	#define C_LOCALDEF__LCCM240__ENABLE_THIS_MODULE							(1U)
#else
	#define C_LOCALDEF__LCCM240__ENABLE_THIS_MODULE							(0U)
#endif
 	 #if C_LOCALDEF__LCCM240__ENABLE_THIS_MODULE == 1U

		//Module Enables
		#define C_LOCALDEF__LCCM240__ENABLE_N2HET1							(1U)
		#define C_LOCALDEF__LCCM240__ENABLE_N2HET2							(0U)

		//enable interrupts or not
		#define C_LOCALDEF__LCCM240__ENABLE_INTERRUPTS						(0U)


		//HET Options
		#define C_LOCALDEF__LCCM240__ENABLE_INPUT_CAPTURE					(0U)
		#define C_LOCALDEF__LCCM240__ENABLE_EDGE_CAPTURE					(0U)
		#define C_LOCALDEF__LCCM240__ENABLE_PWM								(0U)
		#define C_LOCALDEF__LCCM240__ENABLE_TIMESTAMPING					(0U)

		//testing
		#define C_LOCALDEF__LCCM240__ENABLE_TEST_SPEC						(0U)

 	 	//main include
 	 	#include <RM4/LCCM240__RM4__N2HET/rm4_n2het.h>

 	 #endif //C_LOCALDEF__LCCM240__ENABLE_THIS_MODULE

/*******************************************************************************
SIL3 - RM4 EEPROM EMULATION
You'll need the flash access module for this
*******************************************************************************/
	#define C_LOCALDEF__LCCM230__ENABLE_THIS_MODULE							(1U)
 	 #if C_LOCALDEF__LCCM230__ENABLE_THIS_MODULE == 1U

		//testing options
		#define C_LOCALDEF__LCCM230__ENABLE_TEST_SPEC						(0U)

 	 	//main include
 	 	#include <RM4/LCCM230__RM4__EEPROM/rm4_eeprom.h>

 	 #endif //C_LOCALDEF__LCCM230__ENABLE_THIS_MODULE

/*******************************************************************************
SIL3 - NUMERICAL MODULE
Note: Needs to go before eeprom params if any.
*******************************************************************************/
	#define C_LOCALDEF__LCCM118__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM118__ENABLE_THIS_MODULE == 1U

		/** set to 1 to include TRIG */
		#define C_LOCALDEF__LCCM118__ENABLE_TRIG							(0U)

		/** enable x^y */
		#define C_LOCALDEF__LCCM118__ENABLE_POWER							(1U)

		/** enable vector math */
		#define C_LOCALDEF__LCCM118__ENABLE_VECTORS							(0U)

		/** DISABLES */
		#define C_LOCALDEF__LCCM118__DISABLE_FILTERING__S16					(0U)
		#define C_LOCALDEF__LCCM118__DISABLE_FILTERING__U16					(0U)
		#define C_LOCALDEF__LCCM118__DISABLE_FILTERING__U32					(0U)
		#define C_LOCALDEF__LCCM118__DISABLE_FILTERING__S32					(0U)
		#define C_LOCALDEF__LCCM118__DISABLE_FILTERING__F32					(0U)

		#define C_LOCALDEF__LCCM118__DISABLE_NUMERICAL__S16					(0U)
		#define C_LOCALDEF__LCCM118__DISABLE_NUMERICAL__U16					(0U)
		#define C_LOCALDEF__LCCM118__DISABLE_NUMERICAL__S32					(0U)
		#define C_LOCALDEF__LCCM118__DISABLE_NUMERICAL__U32					(0U)
		#define C_LOCALDEF__LCCM118__DISABLE_NUMERICAL__F32					(0U)
		#define C_LOCALDEF__LCCM118__DISABLE_NUMERICAL__F64					(0U)
		#define C_LOCALDEF__LCCM118__DISABLE_NUMERICAL__U64					(0U)

		/** Testing options */
		#define	C_LOCALDEF__LCCM118__ENABLE_TEST_SPEC						(0U)

		//main include
		#include <MULTICORE/LCCM118__MULTICORE__NUMERICAL/numerical.h>
	#endif //C_LOCALDEF__LCCM118__ENABLE_THIS_MODULE

/*******************************************************************************
SIL3 - GENERAL PURPOSE SOFTWARE FIFO
*******************************************************************************/
	#define C_LOCALDEF__LCCM357__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM357__ENABLE_THIS_MODULE == 1U

		/** Software FIFO depth size, U8 = 255 or U16 = 65K, not both */
		#define C_LOCALDEF__LCCM357__FIFO_DEPTH_U8							(0U)
		#define C_LOCALDEF__LCCM357__FIFO_DEPTH_U16							(1U)

		//testing options
		#define C_LOCALDEF__LCCM357__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <MULTICORE/LCCM357__MULTICORE__SOFTWARE_FIFO/software_fifo.h>

	#endif //C_LOCALDEF__LCCM357__ENABLE_THIS_MODULE


/*******************************************************************************
SIL3 - EEPROM BASIC PARAMETERS
*******************************************************************************/
	#define C_LOCALDEF__LCCM188__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM188__ENABLE_THIS_MODULE == 1U

		/** Use the EEPRARAMS module with an external FLASH */
		#define C_LOCALDEF__LCCM188__USE_WITH_LCCM013						(0U)

		/** Define the number of parameters in the system */
		#define C_LOCALDEF__LCCM188__NUM_PARAMETERS							(32U)

		/** set to 1 if you want to enable CRC's across the entire paramter
		range.  If so you will loose one paramter at the end to store theCRC
		*/
		#define C_LOCALDEF__LCCM188__ENABLE_CRC								(1U)

		/** Offset to start in memory */
		#define C_LOCALDEF__LCCM188__EEPROM_START_OFFSET					(0U)

		/** DISABLES */
		#define C_LOCALDEF__LCCM188__DISABLE__U16							(0U)
		#define C_LOCALDEF__LCCM188__DISABLE__S16							(0U)
		#define C_LOCALDEF__LCCM188__DISABLE__U32							(0U)
		#define C_LOCALDEF__LCCM188__DISABLE__S32							(0U)
		#define C_LOCALDEF__LCCM188__DISABLE__F32							(0U)
		#define C_LOCALDEF__LCCM188__DISABLE__MAC							(0U)

		/** Specialised enabled */
		#define C_LOCALDEF__LCCM188__ENABLE_VECTORS							(0U)

		/** Testing options */
		#define C_LOCALDEF__LCCM188__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <MULTICORE/LCCM188__MULTICORE__EEPROM_PARAMS/eeprom_params.h>

	#endif //C_LOCALDEF__LCCM188__ENABLE_THIS_MODULE

/*******************************************************************************
RM4 - EMAC Module
*******************************************************************************/
	#define C_LOCALDEF__LCCM254__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM254__ENABLE_THIS_MODULE == 1U

		//on some dev boards we need to use RMII mode, not MII mode
		#define C_LOCALDEF__LCCM254__ENABLE_RMII_MODE						(0U)

		//set to 1 if you have an external reset pin to the EMAC
		#define C_LOCALDEF__LCCM254__ENABLE_EXTERN_RESET					(1U)

		#if C_LOCALDEF__LCCM254__ENABLE_EXTERN_RESET == 1U
			#define C_LOCALDEF__LCCM254__NRESET_PIN__TRIS()						vRM4_N2HET_PINS__Set_PinDirection_Output(N2HET_CHANNEL__1, 0U)
			#define C_LOCALDEF__LCCM254__NRESET_PIN__LATCH(x)					vRM4_N2HET_PINS__Set_Pin(N2HET_CHANNEL__1, 0U, x)
		#endif

		//use LWIP or not
		#define C_LOCALDEF__LCCM254__USE_WITH_LWIP							(0U)
		#define C_LOCALDEF__LCCM254__USE_WITH_LCCM325						(1U)

		//testing options
		#define C_LOCALDEF__LCCM254__ENABLE_TEST_SPEC						(0U)
		#define C_LOCALDEF__LCCM254__ENABLE_IO_PIN_TESTING					(0U)

		//main include file
		#include <RM4/LCCM254__RM4__EMAC/rm4_emac.h>

	#endif //C_LOCALDEF__LCCM254__ENABLE_THIS_MODULE

/*******************************************************************************
SIL3 - DP83640 Ethernet PHY with IEE1588
*******************************************************************************/
	#define C_LOCALDEF__LCCM515__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM515__ENABLE_THIS_MODULE == 1U

		/** Testing Options */
		#define C_LOCALDEF__LCCM515__ENABLE_TEST_SPEC						(0U)

		/** Main include file */
		#include <MULTICORE/LCCM515__MULTICORE__DP83640/dp83640.h>

	#endif //#if C_LOCALDEF__LCCM515__ENABLE_THIS_MODULE == 1U

#endif //_RM57L843_LAUNCHPAD__BSP_H_


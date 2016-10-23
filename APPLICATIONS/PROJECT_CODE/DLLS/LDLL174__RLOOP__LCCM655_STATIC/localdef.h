#ifndef _LOCALDEF_H_
#define _LOCALDEF_H_

	//our basic defines
	#include <WIN32/BASIC_TYPES/basic_types.h>
	#include <WIN32/DEBUG_PRINTF/debug_printf.h>

	//some placeholders
	#define SAFETOOL_BRANCH(stFuncID)

/*******************************************************************************
SOFTWARE MULTIPURPOSE FAULT TREE HANDLER
*******************************************************************************/
	#define C_LOCALDEF__LCCM284__ENABLE_THIS_MODULE							1U
	#if C_LOCALDEF__LCCM284__ENABLE_THIS_MODULE == 1U

		//testing options
		#define C_LOCALDEF__LCCM284__ENABLE_TEST_SPEC						0U

		//main include file
		#include <multicore/LCCM284__MULTICORE__FAULT_TREE/fault_tree.h>

	#endif //C_LOCALDEF__LCCM284__ENABLE_THIS_MODULE


/*******************************************************************************
NUMERICAL MODULE
*******************************************************************************/
	#define C_LOCALDEF__LCCM118__ENABLE_THIS_MODULE							1U
	#if C_LOCALDEF__LCCM118__ENABLE_THIS_MODULE == 1
	
		//set to 1 to include TRIG
		#define C_LOCALDEF__LCCM118__ENABLE_TRIG							0U
	
		//enable x^y
		#define C_LOCALDEF__LCCM118__ENABLE_POWER							0U

		//enable vector math
		#define C_LOCALDEF__LCCM118__ENABLE_VECTORS							0U

		//main include
		#include <MULTICORE/LCCM118__MULTICORE__NUMERICAL/numerical.h>
	#endif //C_LOCALDEF__LCCM118__ENABLE_THIS_MODULE

/*******************************************************************************
SOFTWARE BASED CRC
*******************************************************************************/
	#define C_LOCALDEF__LCCM012__ENABLE_THIS_MODULE							1U
	#if C_LOCALDEF__LCCM012__ENABLE_THIS_MODULE == 1U
	
		//set to 1 to enable test specification code
		#define C_LOCALDEF__LCCM012__ENABLE_TEST_SPEC						0U
	
		//types of CRC
		#define C_LOCALDEF__LCCM012__ENABLE_CRC7							0U
		#define C_LOCALDEF__LCCM012__ENABLE_CRC8							1U
		#define C_LOCALDEF__LCCM012__ENABLE_CRC16							1U
		#define C_LOCALDEF__LCCM012__ENABLE_CRC32							1U
	
	
		#if C_LOCALDEF__LCCM012__ENABLE_CRC16 == 1U
			//set to 1 to enable table based CRC16
			//Note: Not possible on PIC18 due to page sizes
			#define C_LOCALDEF__LCCM012__ENABLE_TABLE_BASED_CRC				1U
			
			//if using tables, define any alignment issues
			#if C_LOCALDEF__LCCM012__ENABLE_TABLE_BASED_CRC == 1U
				#ifndef WIN32
					#define C_LOCALDEF__LCCM012__TABLE16_DEF static Luint16 u16SWCRC_CRC_TABLE[] __attribute__ ((aligned (128)))
				#else
					//no alignment possible on win32.
					#define C_LOCALDEF__LCCM012__TABLE16_DEF static Luint16 u16SWCRC_CRC_TABLE[]
				#endif
			#endif //C_LOCALDEF__LCCM012__ENABLE_TABLE_BASED_CRC
		#endif
			
		#include <MULTICORE/LCCM012__MULTICORE__SOFTWARE_CRC/software_crc.h>
	
	#endif

/*******************************************************************************
RLOOP - FLIGHT CONTROL UNIT - CORE
*******************************************************************************/
	#define C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U


		/** Testing Options */
		#define C_LOCALDEF__LCCM655__ENABLE_TEST_SPEC						(0U)

		/** Main include file */
		#include <LCCM655__RLOOP__FCU_CORE/fcu_core.h>

	#endif //#if C_LOCALDEF__LCCM655__ENABLE_THIS_MODULE == 1U

#endif //LOCALDEF

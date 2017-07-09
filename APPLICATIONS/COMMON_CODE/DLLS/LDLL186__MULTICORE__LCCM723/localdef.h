#ifndef _LOCALDEF_H_
#define _LOCALDEF_H_

	#include <sil3_generic__cpu.h>

	//our basic defines
	#include <WIN32/BASIC_TYPES/basic_types.h>

	#include <WIN32/DEBUG_PRINTF/debug_printf.h>
	#include <WIN32/DEBUG_CSV/win32__debug_csv.h>



/*******************************************************************************
NUMERICAL MODULE
*******************************************************************************/
	#define C_LOCALDEF__LCCM118__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM118__ENABLE_THIS_MODULE == 1U

		/** set to 1 to include TRIG */
		#define C_LOCALDEF__LCCM118__ENABLE_TRIG							(1U)
	
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
		
		
		/** Testing options */
		#define	C_LOCALDEF__LCCM118__ENABLE_TEST_SPEC						(0U)

		//main include
		#include <MULTICORE/LCCM118__MULTICORE__NUMERICAL/numerical.h>
	#endif //C_LOCALDEF__LCCM118__ENABLE_THIS_MODULE


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
SafeTool Branch Analysis Support
*******************************************************************************/
	#define C_LOCALDEF__LCCM517__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM517__ENABLE_THIS_MODULE == 1U

		/** The maximum number of branch calls permissible, adjust as necessary
		 * depening on function size and test environment.
		 */
		#define C_LOCALDEF__LCCM517__MAX_BRANCH_CALLS						(64U)


		/** Testing Options */
		#define C_LOCALDEF__LCCM517__ENABLE_TEST_SPEC						(0U)


		/** Main include file */
		#include <MULTICORE/LCCM517__MULTICORE__SAFETOOL_BRANCH/safetool_branch.h>
	#else
		//placeholder
		#define SAFETOOL_BRANCH(stFuncID)
	#endif //#if C_LOCALDEF__LCCM517__ENABLE_THIS_MODULE == 1U

/*******************************************************************************
LIPO CELL MODEL
*******************************************************************************/
	#define C_LOCALDEF__LCCM723__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM723__ENABLE_THIS_MODULE == 1U

		/** Define the maximum time size in seconds */
		#define C_LOCALDEF__LCCM723__MAX_TIME_SIZE							(600U)
	
		/** If you want to make a battery out of many cells, specify the
		number of cells, min is 1
		Number of cells * num Packs = total cells */
		#define C_LOCALDEF__LCCM723__NUM_CELLS_PER_PACK						(18U)
	
		/** If you want to make a parallel pack, set this to the number
		of cells in parallel, else 1*/
		#define C_LOCALDEF__LCCM723__NUM_PARALLEL							(6U)

	
		/** Number of individual battery packs */
		#define C_LOCALDEF__LCCM723__NUM_PACKS								(1U)
		
		
		/** Testing Options */
		#define C_LOCALDEF__LCCM723__ENABLE_TEST_SPEC						(0U)
		
		/** Main include file */
		#include <MULTICORE/LCCM723__MULTICORE__LIPO_CELL_MODEL/cell_model.h>
	#endif //#if C_LOCALDEF__LCCM723__ENABLE_THIS_MODULE == 1U
	
	
#endif //LOCALDEF

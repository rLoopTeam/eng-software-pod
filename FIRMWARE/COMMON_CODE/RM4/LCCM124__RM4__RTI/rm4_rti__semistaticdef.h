
#ifndef RM48_RTI_SEMISTATICDEF_H_
#define RM48_RTI_SEMISTATICDEF_H_

#include <RM4/LCCM124__RM4__RTI/rm4_rti__staticdef.h>

	/** Preescaler for each timer
	 * The RTI1CLK feeds into counter 0 and counter 1
	 */
	//The prescaler value takes the RTI1CLK and divides it down to the compare frequency.
	#define RM48L950_RTI_COUNTER0_PRESC 10U



	#define RM48L950_RTI_COMPARE0 RM48L950_RTI_COUNTER_ZERO //All compare registers refer to Counter 0
	#define RM48L950_RTI_COMPARE1 RM48L950_RTI_COUNTER_ZERO //All compare registers refer to Counter 0
	#define RM48L950_RTI_COMPARE2 RM48L950_RTI_COUNTER_ZERO //All compare registers refer to Counter 0
	#define RM48L950_RTI_COMPARE3 RM48L950_RTI_COUNTER_ZERO //All compare registers refer to Counter 0

	#define RM48L950_RTI_FRC0_PRESET 0x00000000U //Preset value for the Free Running Counter 0
	#define RM48L950_RTI_FRC1_PRESET 0x00000000U //Preset value for the Free Running Counter 1
	#define RM48L950_RTI_CU0_PRESET	0x00000000U //Preset value for the Counter Up 0
	#define RM48L950_RTI_CU1_PRESET	0x00000000U //Preset value for the Counter Up 1

	#define RM48L950_RTI_CAPTURE0_TRIG RM48L950_RTI_SOURCE_0 //Capture event of Counter 0 is triggered by source 0
	#define RM48L950_RTI_CAPTURE1_TRIG RM48L950_RTI_SOURCE_0 //Capture event of Counter 0 is triggered by source 1

	#define RM48L950_RTI_FRC0_TIMEBASE RM48L950_RTI_TIMEBASE_RTIUC0 //Setting the time base to be the Up Counter

#endif //RM48_RTI_SEMISTATICDEF_H_


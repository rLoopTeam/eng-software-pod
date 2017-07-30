#if 0

/*******************************************************************************
SIL3 - H-BRIDGE MOTOR CONTROLLER WITH PID
*******************************************************************************/
	#define C_LOCALDEF__LCCM492__ENABLE_THIS_MODULE							(1U)
	#if C_LOCALDEF__LCCM492__ENABLE_THIS_MODULE == 1U

		//num devices (motors)
		#define C_LOCALDEF__LCCM492__NUM_MOTORS								(1U)

		
		/** Motor Direction A control */
		#define C_LOCALDEF__LCCM492__LATCH_DIR_A(index, x)					{}
		
		/** Motor Direction B control */
		#define C_LOCALDEF__LCCM492__LATCH_DIR_B(index, x)					{}
		
		/** Enable / PWM control - Connect to enable pin */
		#define C_LOCALDEF__LCCM492__UPDATE_PWM(channelIndex, programIndex, pwm, dutycycle)					{}
		
		
		
		//Hint at the driver type
		#define C_LOCALDEF__LCCM492__DRIVER_L298N							(1U)

		//testing
		#define C_LOCALDEF__LCCM492__ENABLE_TEST_SPEC						(0U)

		//main include file
		#include <MULTICORE/LCCM492__MULTICORE__HBRIDGE_MOTOR/h_bridge.h>
	#endif //#if C_LOCALDEF__LCCM492__ENABLE_THIS_MODULE == 1U


#endif //0



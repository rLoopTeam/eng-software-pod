
#include <localdef.h>

int main()
{

	//init the FLASH memory
	vRM4_FLASH__Init();

	//int the I2C
	vRM4_I2C_USER__Init();

	//init the Temp Sensor
	vTSYS01__Init();

	while(1)
	{

		//process any tasks
		vTSYS01__Process();

	}
}




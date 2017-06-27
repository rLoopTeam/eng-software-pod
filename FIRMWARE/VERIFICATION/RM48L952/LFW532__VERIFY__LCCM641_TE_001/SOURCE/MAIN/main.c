
#include <localdef.h>

int main()
{

	//init the FLASH memory
	vRM4_FLASH__Init();

	//int the I2C
	vRM4_I2C_USER__Init();

	//init the DS2482
	vDS2482S__Init();

	//init the DS18B20 module
	vDS18B20__Init();


	while(1)
	{

		//process any tasks
		vDS2482S__Process();

		//process any temp sensor tasks.
		vDS18B20__Process();

	}
}




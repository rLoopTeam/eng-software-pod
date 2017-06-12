//Run on flight control hardware

#include <localdef.h>




int main()
{


	//init the FLASH memory
	vRM4_FLASH__Init();

	//init the DMA
	vRM4_DMA__Init();

	//init SCI2
	vRM4_SCI__Init(SCI_CHANNEL__2);
	vRM4_SCI__Set_Baudrate(SCI_CHANNEL__2, 9600);

	//Init the I2C
	vRM4_I2C_USER__Init();

	//init the AMC device
	vAMC7812__Init();

	//main program loop.
	while(1)
	{



	}
}




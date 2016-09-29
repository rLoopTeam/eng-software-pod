/*
 * main.c
 *
 *  Created on: 23/08/2013
 *      Author: Lachlan
 */

#include <localdef.h>

int main()
{

	//setup flash
	vRM4_FLASH__Init();

	//GIO
	vRM4_GIO__Init();

	//init branching
	vSAFETOOL_BRANCH__Init();

	//setup UART
	vRM4_SCI__Init(SCI_CHANNEL__2);
	vRM4_SCI__Set_Baudrate(SCI_CHANNEL__2, 9600U);



	while(1);

}



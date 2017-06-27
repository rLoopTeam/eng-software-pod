/* Test the BMS stack
 *
 * Connections:
 *
 * Power Node:
 * SIGNAL NAME			DIRECTION		RM4 FUNCTION
 * ----------------------------------------------------------------------
 * BMS PWR AVAIL		IN				GIOA:5
 * BMS NCS				OUTPUT			GIOB:4
 * BMS PWR DISABLE		OUTPUT			GIOB:2
 * BMS MISO				INPUT			SPI1MISO
 * BMS MOSI				OUT				SPI1SIMO
 * BMS SCK				OUT				SPI1CLK
 * BMS IRQ				IN				GIOA:4
 *
 * Power Node to BMS Board (Lower Connector)
 * SIGNAL NAME			DIR. (PWRNODE)	CN2 PIN
 * ----------------------------------------------------------------------
 * MISO FROM UPPER		IN				1
 * N/A									2
 * MOSI TO UPPER		OUT				3
 * CLK TO UPPER							4
 * SCK TO UPPER			OUT				5
 * PD IN FROM UPPER		OUT				8
 * IRQ FROM UPPER		IN				9
 * VDD_HV				N/A				10
 * DGND					N/A				11
 * N/A									12
 * PWR DN				N/A				13
 * VDD FROM UPPER		N/A				14
 *
 * POWER TO BMS BOARD:
 * Lab PSU, 10VDC between CELL7-Pos and CELL1-Neg
 *
 */


#include <localdef.h>

int main()
{
	Luint8 u8Test;

	//init the FLASH memory
	vRM4_FLASH__Init();

	//int the GPIO
	vRM4_GIO__Init();

	//setup UART
	//vRM4_SCI__Init(SCI_CHANNEL__2);
	//vRM4_SCI__Set_Baudrate(SCI_CHANNEL__2, 9600U);

	//get the SPI up for the BMS system
	vRM4_MIBSPI135__Init(MIBSPI135_CHANNEL__1);

	//init the BMS device
	vATA6870__Init();

	//do some tests;
#if 0
	//just check the SPI
	M_LOCALDEF__LCCM650__NCS_TRIS(0U);
	M_LOCALDEF__LCCM650__NCS_LATCH(1U);
	M_LOCALDEF__LCCM650__NCS_LATCH(0U);
	M_LOCALDEF__LCCM650__NCS_LATCH(1U);
#endif


	/* Check the ATA device on the top board is powered on/off
	 * Measure at just below C10 (ATA3V) on LPCB225 and check the two following
	 * functions enable and disable the ATA3V line.
	 */
#if 0
	vATA6870_LOWLEVEL__PowerOn();
	vATA6870_LOWLEVEL__PowerOff();
#endif //0


	/* check the power available signal.
	 * with the device off, the power avil signal should be off.
	 * Note: Currently top PCB will need a wire signal on pin 10.
	 */
#if 0
	//switch on
	vATA6870_LOWLEVEL__PowerOn();
	//delay a bit for things to settle
	vRM4_DELAYS__Delay_mS(100U);

	//check the flag
	u8Test = u8ATA6870_LOWLEVEL__Get_PowerAvail();

	while(1)
	{
		//wait here and check the value of u8 test
	}

#endif

#if 1
	//check a resistor
	vATA6870_RES__TurnOn(0, 1);

#endif


	//make sure we are off until ready.
	vATA6870_LOWLEVEL__PowerOff();


	//power up
	vATA6870_LOWLEVEL__PowerOn();


	while(1)
	{

		//process any BMS tasks
		vATA6870__Process();

	}
}




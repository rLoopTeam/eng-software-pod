#include <localdef.h>

int main()
{

	//init the flight control unit
	vFCU__Init();

	while(1)
	{
		//process any FCU tasks
		vFCU__Process();

		//todo:
		//clear the WDT
	}

}



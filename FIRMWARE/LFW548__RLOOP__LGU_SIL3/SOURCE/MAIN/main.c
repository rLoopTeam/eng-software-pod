#include <localdef.h>

int main()
{

	//init the landing gear unit
	vLGU__Init();

	while(1)
	{
		//process any LGU tasks
		vLGU__Process();

		//todo:
		//clear the WDT
	}

}



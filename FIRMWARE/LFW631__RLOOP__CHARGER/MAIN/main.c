#include <localdef.h>

int main()
{

	//init
	vAPU__Init();


	while(1)
	{
		//process any tasks
		vAPU__Process();
	}

}



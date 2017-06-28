#include <localdef.h>

int main()
{

	//init
	vHETHERM__Init();


	while(1)
	{
		//process any tasks
		vHETHERM__Process();
	}

}



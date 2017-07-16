#include <localdef.h>

int main()
{

	//init
	vLGU__Init();


	while(1)
	{
		//process any tasks
		vLGU__Process();
	}

}



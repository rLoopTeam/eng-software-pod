#include <localdef.h>

int main()
{

	//init the power node
	vPWRNODE__Init();


	while(1)
	{
		//process any power node tasks.
		vPWRNODE__Process();
	}

}



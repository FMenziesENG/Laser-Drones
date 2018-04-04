// LaserDrones c++ main Code
// Written by Fraser Menzies

//include Libraries
#include <thread>

//Tasks
#include "TSK_Motors.h"
#include "TSK_Proximity.h"
//#include "TSK_Control.h"
#include "TSK_Stop.h"
#include "TSK_Interface.h"
/*
#include "TSK_IMU.h"
#include "TSK_Camera.h"

*/


int main()
{

	//Initialise Threads
	std::thread ID_Stop(TSK_Stop);    //Initialise Stop Task
	if (Stop_TSKS == 'N')
	{
		std::thread ID_Interface(TSK_Interface);
		std::thread ID_Motors(TSK_Motors);
		//std::thread ID_Control(TSK_Control);
		std::thread ID_Prox(TSK_Proximity);

		//dont return main unless threads end
		ID_Interface.join();
		ID_Motors.join();
		ID_Prox.join();
		ID_Stop.join();
	}

	//Once threads end either shutdown pi or end program
	if(Shutdown == 'Y')
	{
		system("sudo poweroff");	//poweroff pi
	}else
	{
		return 0;
	}
}

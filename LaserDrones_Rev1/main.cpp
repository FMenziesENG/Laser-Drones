// LaserDrones c++ main Code
// Written by Fraser Menzies

//include Libraries
#include <iostream>
#include <thread>

//Tasks
#include "TSK_Motors.h"
#include "TSK_Proximity.h"
#include "TSK_Control.h"
#include "TSK_Stop.h"
/*
#include "TSK_IMU.h"
#include "TSK_Camera.h"

*/


int main()
{

	//Initialise Threads
	std::thread ID_Stop(TSK_Stop);    //Initialise Stop Task
	if (STOP == 'N')
	{
		std::thread ID_Motors(TSK_Motors);
		std::thread ID_Control(TSK_Control);
		std::thread ID_Prox(TSK_Proximity);



		//dont return main unless threads end
		ID_Motors.join();
		ID_Prox.join();
	}

	return 0;
}
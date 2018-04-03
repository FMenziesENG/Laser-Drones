#include <curses.h>
#include "TSK_Interface.h"
#include "TSK_Stop.h"
#include <string>
//This thread prints data to the screen and takes input from the screen for debugging purposes

// Messages to Screen
//------------Setup----------
//TSK_Stop: Initialise, wiringPiSetup, Shutdown, End_prog, Stop Flags
//TSK_Interface: Initialise
//TSK_Proximity: Initialise
//TSK_Motors: Initialise
//TSK_IMU: Initialise
//TSK_Camera: Initialise
//------------Data-----------
//TSK_Proximity: Proximity mm

//------------Inputs----------
// 'E' - Ends Program
//----------External Variables

int = TSK_Stop_Init;
int = TSK_STOP_wiringPiSetup;
int = TSK_Stop_Shutdown;
int = TSK_Stop_End_prog;
int = TSK_Stop_Flags;
int = TSK_Motors_Init;
int = TSK_IMU_Init;
int = TSK_Camera_Init;

void TSK_Interface()
{
	//Setup curses.h
	initscr;
	cbreak;
	noecho;
	scrollok(stdscr, TRUE);
	nodelay(stdscr, TRUE);

	while(Stop_TSKS == 'N')
	{
		//End Program Command
		if(getch() == ' ') //to end program press space bar
		{
			Interface_END = 'Y';
		}
		erase();	//clears screen
		//Print Data to screen, if data changes then change message to write
		printw("------------Setup-------------"
			"------------TSK_Stop----------"
			"TSK_Stop: %s"
			"wiring_PiSetup: %s"
			"Shutdown: %s"
			"End Session: %s"
			"Threads Ended: %s"
			"------------TSK_Proximity----------"
			"TSK_Proximity: %s"
			"Height: %d"
			"------------TSK_Motors----------"
			"TSK_Motors: %s"
			"------------TSK_IMU----------"
			"TSK_IMU: %s"
			"Roll: %f"
			"Pitch: %f"
			"Yaw: %f"
			"------------TSK_Camera----------"
			"TSK_Camera: %s"
			"---------------------------------",
				print_Init(TSK_Stop_Init),
				print_Init(TSK_Stop_wiringPiSetup),
				print_Init(TSK_Stop_Shutdown),
				print_Init(TSK_Stop_End_prog),
				print_Init(TSK_Stop_Flags),
				print_Init(TSK_Proximity_Init),
				Proximity,
				print_Init(TSK_Motors_Init),
				print_Init(TSK_IMU_Init),
				TSK_IMU_Roll,
				TSK_IMU_Pitch,
				TSK_IMU_Yaw,
				Print_Init(TSK_Camera_Init)
		);
	}
	endwin();
	TSK_Interface_Stop_Flag = 1;
}

print_Init(int Flag)
{
	if(Flag == 1)
	{
		return "Initialised";
	}else
	{
		return "OFF";
	}

}

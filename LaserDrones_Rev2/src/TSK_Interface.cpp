#include <curses.h>
#include <string>
#include <unistd.h>

#include "TSK_Interface.h"
#include "TSK_Stop.h"
#include "TSK_Proximity.h"
#include "TSK_Motors.h"

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

int TSK_Stop_Init;
int TSK_Stop_wiringPiSetup;
int TSK_Stop_Shutdown;
int TSK_Stop_End_prog;
int TSK_Stop_Flags;
int TSK_Motors_Init;
int TSK_IMU_Init = 0;
int TSK_Camera_Init = 0;
int TSK_Proximity_Init;
float Roll = 0.0;
float Pitch = 0.0;
float Yaw = 0.0;


const char *print_Init(int Flag);

void TSK_Interface()
{
	//Setup curses.h
	initscr();
	cbreak();
	noecho();
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
		printw("------------Setup-------------\n"
			"------------TSK_Stop----------\n"
			"TSK_Stop: %s\n"
			"wiring_PiSetup: %s\n"
			"Shutdown: %s\n"
			"End Session: %s\n"
			"Threads Ended: %s\n"
			"------------TSK_Proximity----------\n"
			"TSK_Proximity: %s\n"
			"Height: %i\n"
			"------------TSK_Motors----------\n"
			"TSK_Motors: %s\n"
			"------------TSK_IMU----------\n"
			"TSK_IMU: %s\n"
			"Roll: %f\n"
			"Pitch: %f\n"
			"Yaw: %f\n"
			"------------TSK_Camera----------\n"
			"TSK_Camera: %s\n"
			"---------------------------------\n",
				print_Init(TSK_Stop_Init),
				print_Init(TSK_Stop_wiringPiSetup),
				print_Init(TSK_Stop_Shutdown),
				print_Init(TSK_Stop_End_prog),
				print_Init(TSK_Stop_Flags),
				print_Init(TSK_Proximity_Init),
				Proximity,
				print_Init(TSK_Motors_Init),
				print_Init(TSK_IMU_Init),
				Roll,
				Pitch,
				Yaw,
				print_Init(TSK_Camera_Init)
		);
	}
	endwin();
	erase();
	TSK_Interface_Stop_Flag = 1;
}

const char *print_Init(int Flag)
{
	if(Flag == 1)
	{
		return "Initialised";
	}else
	{
		return "OFF";
	}

}

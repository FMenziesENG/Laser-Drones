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

void TSK_Interface()
{	
	//Setup curses.h
	initscr;
	cbreak;
	noecho;
	scrollok(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	
	printw("------Interface UP------\nPress space to end program");
	
	while(Stop_TSKS == 'N')
	{
		//End Program Command
		if(getch() == ' ') //to end program press space bar
		{
			Interface_END = 'Y';
		}
		
		//Print Data to screen, if data changes then change message to write
		printw("//------------Setup-------------"
			   "//------------TSK_Stop----------"
			   "//%s"
			   "//%s"
			   "//%s"
			   "//%s"
			   "//%s"
			   "//------------TSK_Interface----------"
			   "//%s"
			   "//------------TSK_Proximity----------"
			   "//%s"
			   "//------------TSK_Motors----------"
			   "//%s"
			   "//------------TSK_IMU----------"
			   "//%s"
			   "//------------TSK_Camera----------"
			   "//%s"
			   "//------------Data--------------"
			   "//%s",
				
		);
		//clear screen function
	}
	
	//end window
	TSK_Interface_Stop_Flag = 1;
}
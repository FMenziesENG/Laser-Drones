#include <curses.h>
#include <string>
#include <unistd.h>

#include "PCA9685.h"
#include "TSK_Interface.h"
#include "TSK_Stop.h"
#include "TSK_Proximity.h"
#include "TSK_Motors.h"
#include "Motor_Control.h"

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

extern struct Motors No_Motors;
extern struct Motors Up_Motors;
extern struct Motors Down_Motors;
extern struct Motors Clockwise_Motors;
extern struct Motors Anticlockwise_Motors;
extern struct Motors Selected_Motors;
extern struct Motors Old_Motors;

int Sel;
int Cal_Sel;
int Cal_Motors_Flag;
int Cal_Motor = 0;
int Cal_Message = 0;
extern struct Motors Cal_Selected_Motor;

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
int TSK_Interface_Stop_Flag = 1;
//bool Cal_Motors_Flag;

const char *print_Init(int Flag);
const char *print_Cal(int Cal_Motor);
const char *Get_Cal_Message(int Cal_Message);

void TSK_Interface()
{
	TSK_Interface_Stop_Flag = 0; //Tell TSK_Stop that Interface has Initialised
	char input;

	PCA9685 PWMs(1,0x40);

	//Setup curses.h
	initscr();
	cbreak();
	noecho();
	scrollok(stdscr, TRUE);
	nodelay(stdscr, TRUE);

	while(Stop_TSKS == 'N')
	{
		//Inputs
		input = getch();
		Selected_Motors = Get_Motors(input); //Returns Sel
		Get_Motor_Setting(input);			//Sets Selected_Motors.Setting to setting of input motor selection
		Update_Motor_Setting(Selected_Motors.Setting, Sel);
		Get_Calibration_Mode(input);
		//End Program Command
		if(input == ' ') //to end program press space bar
		{
			Interface_END = 'Y';
		}

		erase();	//clears screen

		if(Cal_Motors_Flag == 1)  //Go into Calibration Mode
		{
			Cal_Selected_Motor = Get_Cal_Motor(input);
			Get_Cal_Motor_Mode(input);

			printw(
			"-------Calibration_Mode-------\n"
			"------------------------------\n"
			"%s\n"
			"Selected Channel: %i\n"
			"%s\n"
			"------------------------------\n"
			"------------TSK_Stop----------\n"
			"TSK_Stop: %s\n"
			"wiring_PiSetup: %s\n"
			"Shutdown: %s\n"
			"End Session: %s\n"
			"Threads Ended: %s\n"
			"------------TSK_Proximity-----\n"
			"TSK_Proximity: %s\n"
			"Height: %i\n"
			"------------TSK_Motors--------\n"
			"TSK_Motors: %s\n"
			"Motor Selection: %s\n"
			"Motor Setting(0-1000): %i\n"
			"Motor 1 PWM: %i\n"
			"Motor 2 PWM: %i\n"
			"Motor 3 PWM: %i\n"
			"Motor 4 PWM: %i\n"
			"Motor 5 PWM: %i\n"
			"Motor 6 PWM: %i\n"
			"Motor 7 PWM: %i\n"
			"Motor 8 PWM: %i\n"
			"------------TSK_IMU-----------\n"
			"TSK_IMU: %s\n"
			"Roll: %f\n"
			"Pitch: %f\n"
			"Yaw: %f\n"
			"------------TSK_Camera--------\n"
			"TSK_Camera: %s\n"
			"------------------------------\n",
				Cal_Selected_Motor.Name,
				Cal_Sel,
				Get_Cal_Message(Cal_Message),
				print_Init(TSK_Stop_Init),
				print_Init(TSK_Stop_wiringPiSetup),
				print_Init(TSK_Stop_Shutdown),
				print_Init(TSK_Stop_End_prog),
				print_Init(TSK_Stop_Flags),
				print_Init(TSK_Proximity_Init),
				Proximity,
				print_Init(TSK_Motors_Init),
				Selected_Motors.Name,
				Selected_Motors.Setting,
				PWMs.getPWM(1),
				PWMs.getPWM(2),
				PWMs.getPWM(3),
				PWMs.getPWM(4),
				PWMs.getPWM(9),
				PWMs.getPWM(10),
				PWMs.getPWM(11),
				PWMs.getPWM(12),
				print_Init(TSK_IMU_Init),
				Roll,
				Pitch,
				Yaw,
				print_Init(TSK_Camera_Init)
			);

		}
		else
		{
		//Print Data to screen, if data changes then change message to write
			printw(
			"------------Setup-------------\n"
			"------------TSK_Stop----------\n"
			"TSK_Stop: %s\n"
			"wiring_PiSetup: %s\n"
			"Shutdown: %s\n"
			"End Session: %s\n"
			"Threads Ended: %s\n"
			"------------TSK_Proximity-----\n"
			"TSK_Proximity: %s\n"
			"Height: %i\n"
			"------------TSK_Motors--------\n"
			"TSK_Motors: %s\n"
			"Motor Selection: %s\n"
			"Motor Setting(0-1000): %i\n"
			"Motor 1 PWM: %i\n"
			"Motor 2 PWM: %i\n"
			"Motor 3 PWM: %i\n"
			"Motor 4 PWM: %i\n"
			"Motor 5 PWM: %i\n"
			"Motor 6 PWM: %i\n"
			"Motor 7 PWM: %i\n"
			"Motor 8 PWM: %i\n"
			"------------TSK_IMU-----------\n"
			"TSK_IMU: %s\n"
			"Roll: %f\n"
			"Pitch: %f\n"
			"Yaw: %f\n"
			"------------TSK_Camera--------\n"
			"TSK_Camera: %s\n"
			"------------------------------\n",
				print_Init(TSK_Stop_Init),
				print_Init(TSK_Stop_wiringPiSetup),
				print_Init(TSK_Stop_Shutdown),
				print_Init(TSK_Stop_End_prog),
				print_Init(TSK_Stop_Flags),
				print_Init(TSK_Proximity_Init),
				Proximity,
				print_Init(TSK_Motors_Init),
				Selected_Motors.Name,
				Selected_Motors.Setting,
				PWMs.getPWM(1),
				PWMs.getPWM(2),
				PWMs.getPWM(3),
				PWMs.getPWM(4),
				PWMs.getPWM(9),
				PWMs.getPWM(10),
				PWMs.getPWM(11),
				PWMs.getPWM(12),
				print_Init(TSK_IMU_Init),
				Roll,
				Pitch,
				Yaw,
				print_Init(TSK_Camera_Init)
			);
		}
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

const char *Get_Cal_Message(int Cal_Message)
{

	if(Cal_Message == 1)
	{
		return "Disconnect Battery and press N";
	}else
	if(Cal_Message == 2)
	{
		return "Wiring Pi Failed";
	}else
	if(Cal_Message == 3)
	{
		return "Connect Battery, wait for falling tone and press N";
	}else
	if(Cal_Message == 4)
	{
		return "Waiting for 12 Seconds";
	}else
	if(Cal_Message == 5)
	{
		return "Waiting for 2 seconds";
	}
	else
	if(Cal_Message == 6)
	{
		return "Arming ESC now";
	}else
	if(Cal_Message == 7)
	{
		return "Calibration complete";
	}
}

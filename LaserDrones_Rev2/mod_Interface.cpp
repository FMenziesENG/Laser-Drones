#include <curses.h>
#include <string>
#include <unistd.h>

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

int TSK_Stop_Init=0;
int TSK_Stop_wiringPiSetup=0;
int TSK_Stop_Shutdown=0;
int TSK_Stop_End_prog=0;
int TSK_Stop_Flags=0;
int TSK_Motors_Init=0;
int TSK_IMU_Init = 0;
int TSK_Camera_Init = 0;
int TSK_Proximity_Init=0;
float Roll = 0.0;
float Pitch = 0.0;
float Yaw = 0.0;


struct Motors
{
	const char *Name;
	int Setting;
	uint16_t Driver_Channels;

};

//typedef struct Motors Motors;

#define No_Motors_Channels 0b00000000
#define Up_Motors_Channels 0b11000000
#define Down_Motors_Channels 0b00110000
#define Clockwise_Motors_Channels 0b00001100
#define Anticlockwise_Motors_Channels 0b00000011

int Sel;

const char *print_Init(int Flag);
const char *print_Motor_Selection(uint16_t Motor_Selection);

Motors Get_Motors(char input);
void Get_Motor_Setting(char input);
void Check_Motor_Update(Motors Check_Motors);
void Update_Motor_Setting(int New_Setting, int Old_Setting_Index);

Motors No_Motors = {
	"No Motors Selected",
	0,
	No_Motors_Channels
};

Motors Up_Motors = {
	"Up Motors Selected",
	0,
	Up_Motors_Channels
};


Motors Down_Motors = {
	"Down Motors Selected",
	0,
	Down_Motors_Channels
};


Motors Clockwise_Motors = {
	"Clockwise Motors Selected",
	0,
	Clockwise_Motors_Channels
};


Motors Anticlockwise_Motors = {
	"Anticlockwise Motors Selected",
	0,
	Anticlockwise_Motors_Channels
};

Motors Selected_Motors = No_Motors;
Motors Old_Motors = Selected_Motors;

Motors Motor_Choices[5] = {No_Motors, Up_Motors, Down_Motors, Clockwise_Motors, Anticlockwise_Motors};

int main()
{
	char input;
	char Stop_TSKS = 'N';
	int TSK_Interface_Stop_Flag = 0;

	//Setup curses.h
	initscr();
	cbreak();
	noecho();
	scrollok(stdscr, TRUE);
	nodelay(stdscr, TRUE);

	while(Stop_TSKS == 'N')
	{
		input = getch();
		Selected_Motors = Get_Motors(input);
		Get_Motor_Setting(input);
		Update_Motor_Setting(Selected_Motors.Setting, Sel);
		//End Program Command
		if(input == ' ') //to end program press space bar
		{
			//char Interface_END = 'Y';
			break;
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
			"Motor Selection: %s\n"
			"Motor Setting(0-1000): %i\n"
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
				1092,
				print_Init(TSK_Motors_Init),
				Selected_Motors.Name,
				Selected_Motors.Setting,
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

	return 0;
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


Motors Get_Motors(char input)
{
	switch(input)
	{
		case 'u':
			Sel = 1;
			break;
		case 'd':
			Sel = 2;
			break;
		case 'c':
			Sel = 3;
			break;
		case 'a':
			Sel = 4;
			break;
		case'n':
			Sel = 0;
			break;
		default:
			return Selected_Motors;
	}

	return Motor_Choices[Sel];
}

void Get_Motor_Setting(char input)
{

	if(input == 'i')
	{
		Selected_Motors.Setting += 100;
	}else
	if(input == 'o')
	{
		Selected_Motors.Setting -= 100;
	}
}

void Update_Motor_Setting(int New_Setting, int Motor_Memory_Index)	//Update Motor Structures with Check_Motors Data
{
	Motors Old_Motors = Motor_Choices[Motor_Memory_Index];		//Place last retrieved motor structure from memory into struct variable

	if( Old_Motors.Setting != New_Setting )				//If the PWM Settings have been changed by user
	{
		Old_Motors.Setting = New_Setting;			//Place last selected PWM Setting into temporary variable
		Motor_Choices[Motor_Memory_Index] = Old_Motors;		//Update Memory Struct with Temporary Struct
	}
}


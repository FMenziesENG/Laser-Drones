#include "Motor_Control.h"


//Struct Definitions
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

//Array of Motor Settings Structs
Motors Motor_Choices[5] = {No_Motors, Up_Motors, Down_Motors, Clockwise_Motors, Anticlockwise_Motors};


//Motor Control Function Declarations

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
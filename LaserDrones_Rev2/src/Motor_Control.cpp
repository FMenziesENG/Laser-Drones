#include "Motor_Control.h"
#include "TSK_Motors.h"

//Struct Definitions
Motors No_Motors = {
	"No Motors Selected",
	0,
	No_Motors_Channels
};

Motors Up_Motors = {
	"Up Motors Selected",
	Init_PWM,
	Up_Motors_Channels
};


Motors Down_Motors = {
	"Down Motors Selected",
	Init_PWM,
	Down_Motors_Channels
};


Motors Clockwise_Motors = {
	"Clockwise Motors Selected",
	Init_PWM,
	Clockwise_Motors_Channels
};


Motors Anticlockwise_Motors = {
	"Anticlockwise Motors Selected",
	Init_PWM,
	Anticlockwise_Motors_Channels
};

Motors Channel_1_Motor = {
	"AntiClockwise_1",
	Init_PWM,
	Channel_1
};

Motors Channel_2_Motor = {
	"AntiClockwise_2",
	Init_PWM,
	Channel_2
};

Motors Channel_3_Motor = {
	"Clockwise_1",
	Init_PWM,
	Channel_3
};

Motors Channel_4_Motor = {
	"Clockwise_2",
	Init_PWM,
	Channel_4
};

Motors Channel_9_Motor = {
	"Down_1",
	Init_PWM,
	Channel_9
};

Motors Channel_10_Motor = {
	"Down_2",
	Init_PWM,
	Channel_10
};

Motors Channel_11_Motor = {
	"Up_1",
	Init_PWM,
	Channel_11
};

Motors Channel_12_Motor = {
	"Up_2",
	Init_PWM,
	Channel_12
};

Motors Selected_Motors = No_Motors;
Motors Old_Motors = Selected_Motors;

Motors Cal_Selected_Motor = No_Motors;

//Array of Motor Settings Structs
Motors Motor_Choices[5] = {No_Motors, Up_Motors, Down_Motors, Clockwise_Motors, Anticlockwise_Motors};

//Calibration Motor_Choices
Motors Motor_Cal_Choices[13]= {No_Motors, Channel_1_Motor, Channel_2_Motor, Channel_3_Motor, Channel_4_Motor,
			      No_Motors, No_Motors, No_Motors, No_Motors,
			      Channel_9_Motor, Channel_10_Motor, Channel_11_Motor, Channel_12_Motor};

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
		Selected_Motors.Setting += 30;
	}else
	if(input == 'o')
	{
		Selected_Motors.Setting -= 30;
	}
}

void Update_Motor_Setting(int New_Setting, int Motor_Memory_Index)	//Update Motor Structures with Check_Motors Data
{
	Motors Old_Motors = Motor_Choices[Motor_Memory_Index];		//Place last retrieved motor structure from memory into struct variable

	if( Old_Motors.Setting != New_Setting )				//If the PWM Settings have been changed by user
	{
		Old_Motors.Setting = New_Setting;			//Place last selected PWM Setting into temporary variable
		Motor_Choices[Motor_Memory_Index] = Old_Motors;		//Update Memory Struct with Temporary Struct
		Motor_Update_Flag = 1;
	}else
	{
		Motor_Update_Flag = 0;
	}
}

//-------------------Calibration Mode Functions----------

//Puts Drone Motor Control into Calibration Mode
void Get_Calibration_Mode(char input)
{
	if(input == 'C')	//Changes drone to Calibration Mode
	{
		Cal_Motors_Flag = 1;
	}
	else if (input == 'S')	//Changed drone to Standard Mode
	{
		Cal_Motors_Flag = 0;
	}
}

//Selects the Motor to be Calibrated
Motors Get_Cal_Motor(char input)
{

	switch(input)
	{
		case '1':
			Cal_Sel = 1;
			break;
		case '2':
			Cal_Sel = 2;
			break;
		case '3':
			Cal_Sel = 3;
			break;
		case '4':
			Cal_Sel = 4;
			break;
		case '5':
			Cal_Sel = 9;
			break;
		case '6':
			Cal_Sel = 10;
			break;
		case '7':
			Cal_Sel = 11;
			break;
		case '8':
			Cal_Sel = 12;
			break;
		default:
			return Cal_Selected_Motor;
	}
	return Motor_Cal_Choices[Cal_Sel];
}

//Sets Calibration Motor to Calibrate or Arm

void Get_Cal_Motor_Mode(char input)
{

	if(input == 'A')
	{
		Arm_Motor_Flag = 1;
	}
	else
	if(input == 'K')
	{
		Cal_Motor_Flag = 1;
	}else
	if(input == 'N')
	{
		proceed = 1;
	}
}

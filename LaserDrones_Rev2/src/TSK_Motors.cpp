#include "TSK_Motors.h"
#include "Motor_Control.h"
#include "TSK_Stop.h"
#include "TSK_Interface.h"
#include "Project_Config.h"
#include "PCA9685.h"
#include <string>
#include <unistd.h>
#include "wiringPi.h"
//#include <curses.h>
#include <stdio.h>


//Sets motors to setting as described in Selected_Motors

void Calibrate_Motors();
void Initialise_Motors();
void Update_Motors();
void Arm_Motors();
void Clear_Motors();
void Arm_Motor();
void Calibrate_Motor();

//------------External Variables ---------------
const int MAX_PWM = 500; //12.2% PWM
const int MIN_PWM = 200; //2.4% PWM
const int START_PWM = 230;
int Motor_Update_Flag = 0;
int Arm_Motor_Flag = 0;
int Cal_Motor_Flag = 0;
int proceed = 0;
int TSK_Motors_Stop_Flag = 1;
extern struct Motors Selected_Motors;
PCA9685 motors(1,0x40); //Setup Comms to Motor Driver

void TSK_Motors()
{
	TSK_Motors_Stop_Flag = 0;
	TSK_Motors_Init = 1;

	//Initialise Motor Variables
	motors.setPWMFreq(55);

//	Arm_Motors();
	Initialise_Motors();

	//check does motor PWM need updating?
	//if so then update PWMGUI and reset update request flag to 0
	while (Stop_TSKS == 'N' && Interface_END == 'N')
	{
		if (Motor_Update_Flag != 0)
		{
			Update_Motors();
		}
		if(Arm_Motor_Flag != 0)
		{
			Arm_Motor();
		}
		if(Cal_Motor_Flag!= 0)
		{
			Calibrate_Motor();
		}
	}
	TSK_Motors_Stop_Flag = 1;
	TSK_Motors_Init = 0;
}


void Initialise_Motors()
{
	for (int i = 0; i < 8; i++)
	{
		motors.setPWM(i+1, START_PWM);

	}
	for (int i = 8; i < 12; i++)
	{
		motors.setPWM(i+1, START_PWM);
	}
}

void Update_Motors()
{
	for (int i = 0; i < 4; i++)
	{
		if (Selected_Motors.Driver_Channels & (0b1 << i))
		{
			motors.setPWM(i+1, Selected_Motors.Setting);
		}
	}
	for (int i = 8; i < 12; i++)
	{
		if (Selected_Motors.Driver_Channels & (0b1 << i))
		{
			motors.setPWM(i+1, Selected_Motors.Setting);
		}
	}
}

void Arm_Motors()
{
	for (int i = 0; i < 4; i++)
	{
		motors.setPWM(i+1, 0);
		sleep(1);
		motors.setPWM(i+1, MAX_PWM);
		sleep(1);
		motors.setPWM(i+1, MIN_PWM);
	}

	for (int i = 8; i < 12; i++)
	{
		motors.setPWM(i+1, 0);
		sleep(1);
		motors.setPWM(i+1, MAX_PWM);
		sleep(1);
		motors.setPWM(i+1, MIN_PWM);
	}
}

void Clear_Motors()
{
	for (int i = 0; i < 4; i++)
	{
		motors.setPWM(i+1, 0);
	}

	for (int i = 8; i < 12; i++)
	{
		motors.setPWM(i+1, 0);
	}
}

void Arm_Motor()
{
		Arm_Motor_Flag = 0;
		motors.setPWM(Cal_Sel, 0);
		sleep(1);
		motors.setPWM(Cal_Sel, MAX_PWM);
		sleep(1);
		motors.setPWM(Cal_Sel, MIN_PWM);
}


void Calibrate_Motor()
{
	if (wiringPiSetup() == -1)
	{
		Cal_Message = 2;
	}

	Cal_Message = 1;	//"Disconnect Battery and press N"

	while(proceed != 1){}
	proceed = 0;
	motors.setPWM(Cal_Sel, MAX_PWM);
	Cal_Message = 3;	//"Connect Battery, wait for falling tone and press N"

	while(proceed != 1){}
	proceed = 0;
	motors.setPWM(Cal_Sel, MIN_PWM);
	Cal_Message = 4;	//"Wait for 12 seconds"
	delay(12000);
	motors.setPWM(Cal_Sel, 0);
	Cal_Message = 5;	//"Set to 0 and wait for 2 seconds"
	delay(2000);
	motors.setPWM(Cal_Sel, MIN_PWM);
	Cal_Message = 6;	//"Arming ESC"
	delay(1000);
	Cal_Message = 7;	//"Calibration Complete"
	motors.setPWM(Cal_Sel, START_PWM);
	Cal_Motor_Flag = 0;
}


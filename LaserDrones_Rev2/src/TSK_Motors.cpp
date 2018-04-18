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

//------------External Variables ---------------
const int MAX_PWM = 500; //12.2% PWM
const int MIN_PWM = 200; //2.4% PWM
//int PWM_Table[8] = {0,0,0,0,0,0,0,0};
int Motor_Update_Flag = 0;
int TSK_Motors_Stop_Flag = 1;
extern struct Motors Selected_Motors;
PCA9685 motors(1,0x40); //Setup Comms to Motor Driver
bool Cal_Motors_Flag;

void TSK_Motors()
{
	TSK_Motors_Stop_Flag = 0;
	TSK_Motors_Init = 1;

	//Initialise Motor Variables
	motors.setPWMFreq(55);

	Cal_Motors_Flag = true; //ESC calibration

	if (Cal_Motors_Flag == true)
	{
		Calibrate_Motors();
		Initialise_Motors();
	}
	else
	{
		Arm_Motors();
	}

	//check does motor PWM need updating?
	//if so then update PWMGUI and reset update request flag to 0
	while (Stop_TSKS == 'N' && Interface_END == 'N')
	{
		if (Motor_Update_Flag != 0)
		{
			Update_Motors();
		}
	}
	TSK_Motors_Stop_Flag = 1;
	TSK_Motors_Init = 0;
}



void Calibrate_Motors()
{
/*	initscr();
	cbreak();
	noecho();
	scrollok(stdscr, TRUE);
	nodelay(stdscr, TRUE);
*/
	char input;

	if (wiringPiSetup() == -1)
	{
		printf("Wiring Pi Failed");
	}

	printf("Calibrating Motors\n");
	printf("Disconnect battery and press Enter\n");
		scanf("%c", &input);
		if( input == 'c')
		{
			for (int i = 0; i < 8; i++)
			{
				motors.setPWM(i + 1, MAX_PWM);
			}

			printf("Connect Battery, wait for falling tone and press c\n");
				scanf("%c", &input);
				if (input == 'c')
				{
					for (int i = 0; i < 8; i++)
					{
						motors.setPWM(i + 1, MIN_PWM);
						printf("Wait 12 seconds, Motor: %i\n", i);
						delay(12000);
						printf("Set PWM to 0 and wait 2 seconds, Motor: %i\n", i);
						motors.setPWM(i + 1, 0);
						delay(2000);
						printf("Arming ESC now, Motor: %i\n", i);
						motors.setPWM(i + 1, MIN_PWM);
						delay(1000);
						printf("Calibration Complete, Motor %i\n", i);
					}
				}
		}
}

void Initialise_Motors()
{
	for (int i = 0; i < 8; i++)
	{
		motors.setPWM(i+1, 200);

	}
	for (int i = 8; i < 12; i++)
	{
		motors.setPWM(i+1, 200);

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

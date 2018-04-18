#include "TSK_Motors.h"
#include "Motor_Control.h"
#include "TSK_Stop.h"
#include "TSK_Interface.h"
#include "Project_Config.h"
#include "PCA9685.h"
#include <string>
#include <unistd.h>
#include <curses.h>

//Sets motors to setting as described in Selected_Motors

void Calibrate_Motors();
void Initialise_Motors();
void Update_Motors();
void Arm_Motors();

//------------External Variables ---------------
const int MAX_PWM = 500; //12.2% PWM
const int MIN_PWM = 200; //2.4% PWM
//int PWM_Table[8] = {0,0,0,0,0,0,0,0};
int Motor_Update_Flag = 0;
int TSK_Motors_Stop_Flag = 1;
extern struct Motors Selected_Motors;
PCA9685 motors(1,0x40); //Setup Comms to Motor Driver


void TSK_Motors()
{
	TSK_Motors_Stop_Flag = 0;
	TSK_Motors_Init = 1;

	//Initialise Motor Variables
	motors.setPWMFreq(55);

	const bool Cal_Motors_Flag = false; //ESC calibration

	if (Cal_Motors_Flag == true)
	{
		Calibrate_Motors();
		Initialise_Motors();
		Cal_Motors_Flag = false;
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
	printw("Calibrating Motors\n");
	printw("Disconnect battery and press Enter\n");
	while(1)
	{
		if(getch() == KEY_ENTER)
		{
			for (int i = 0; i < 8; i++)
			{
				motors.setPWM(i + 1, MAX_PWM);
			}

			printw("Connect Battery, wait for falling tone and press Enter\n");
			while(1)
			{
				if (getch() == KEY_ENTER)
				{
					for (int i = 0; i < 8; i++)
					{
						motors.setPWM(i + 1, MIN_PWM);
					}
					printw("Wait 12 seconds\n");
					sleep(12);
					printw("Set PWM to 0 and wait 2 seconds\n");
					for (int i = 0; i < 8; i++)
					{
						motors.setPWM(i + 1, 0);
					}
					sleep(2);
					printw("Arming ESC now\n");
					for (int i = 0; i < 8; i++)
					{
						motors.setPWM(i + 1, MIN_PWM);
					}
					sleep(1);
					printw("Calibration Complete\n");
				}
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

}

void Update_Motors()
{
	for (int i = 0; i < 8; i++)
	{
		if (Selected_Motors.Driver_Channels & (0b1 << i))
		{
			motors.setPWM(i+1, Selected_Motors.Setting);
		}
	}

}

void Arm_Motors()
{
	for (int i = 0; i < 8; i++)
	{
		motors.setPWM(i+1, 0);

	}
	
	sleep(1);
	
	for (int i = 0; i < 8; i++)
	{
		motors.setPWM(i+1, 500);

	}
	
	sleep(1);
	
	for (int i = 0; i < 8; i++)
	{
		motors.setPWM(i+1, 200);

	}
}


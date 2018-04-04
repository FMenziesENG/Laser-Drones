#include "TSK_Motors.h"
#include "TSK_Stop.h"
#include "TSK_Interface.h"
#include "Project_Config.h"
#include "PCA9685.h"
#include <string>
#include <unistd.h>
#include <curses.h>

void Calibrate_Motors();
void Initialise_Motors();
void Update_Motors();

//------------External Variables ---------------
const int MAX_PWM = 3000;
const int MIN_PWM = 1500;
int PWM_Table[8] = {0,0,0,0,0,0,0,0};
char Motor_Update_Flag[8] = {0,0,0,0,0,0,0,0};


PCA9685 motors(1,0x40); //Setup Comms to Motor Driver


void TSK_Motors()
{

	TSK_Motors_Init = 1;

	//Initialise Motor Variables
	motors.setPWMFreq(55);

	const bool Cal_Motors_Flag = false; //ESC calibration

	if (Cal_Motors_Flag == true)
	{
		Calibrate_Motors();
		Initialise_Motors();
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
	printw("Disconnect batter and press Enter\n");
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
		motors.setPWM(i+1, 1000);

	}

}

void Update_Motors()
{
	for (int i = 0; i < 8; i++)
	{
		if ((Motor_Update_Flag && 0x1 << i) == 1)
		{
			motors.setPWM(i+1, PWM_Table[i]);
		}
	}

}


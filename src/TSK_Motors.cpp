#include "TSK_Motors.h"
#include "TSK_Stop.h"
#include "Project_Config.h"
#include "PCA9685.h"
#include <iostream>
#include <string>
#include <unistd.h>


void Calibrate_Motors();
void Initialise_Motors();
void Update_Motors();

//------------External Variables ---------------
const int MAX_PWM = 3000;
const int MIN_PWM = 1500;
int PWM_Table[8] = {0,0,0,0,0,0,0,0};
char Motor_Update_Flag[8] = {0,0,0,0,0,0,0,0};

/*
PCA9685 motors(1,0x40); //Setup Comms to Motor Driver
*/

void TSK_Motors()
{
/*
	std::cout << "Motors Task Up";

	//Initialise Motor Variables
	motors.setPWMFreq(55);

	const bool Cal_Motors_Flag = true; //ESC calibration

	if (Cal_Motors_Flag == true)
	{
		Calibrate_Motors();
		Initialise_Motors();
	}

	//check does motor PWM need updating?
	//if so then update PWMGUI and reset update request flag to 0
	while (Stop_TSKS == 'N' || Interface_END == 'N')
	{
		if (Motor_Update_Flag != 0)
		{
			Update_Motors();
		}
	}
	TSK_Motors_Stop_Flag = 1;
*/
}

void Calibrate_Motors()
{/*
	std::string input;

	std::cout << "Calibrating all channels" << std::endl;
	std::cout << "Disconnect battery and press enter" << std::endl;
	std::getline(std::cin, input);
	if (input.empty())
	{
		for (int i = 0; i < 8; i++)
		{
			motors.setPWM(i + 1, MAX_PWM);
		}

		std::cout << "connect the battery NOW... you will hear tow beeps, then wait for a gradual falling tone and press Enter" << std::endl;
		std::getline(std::cin, input);
		if (input.empty())
		{
			for (int i = 0; i < 8; i++)
			{
				motors.setPWM(i + 1, MIN_PWM);
			}
			std::cout << "Weird eh! Special tone" << std::endl;
			sleep(7);
			std::cout << "Wait for it..." << std::endl;
			sleep(5);
			std::cout << "I'm working on it, Dont worry just wait" << std::endl;
			for (int i = 0; i < 8; i++)
			{
				motors.setPWM(i + 1, 0);
			}
			sleep(2);
			std::cout << "Arming ESC now" << std::endl;
			for (int i = 0; i < 8; i++)
			{
				motors.setPWM(i + 1, MIN_PWM);
			}
			sleep(1);
			std::cout << "Calibration Complete" << std::endl;
		}
	}*/
}

void Initialise_Motors()
{/*
	for (int i = 0; i < 8; i++)
	{
		motors.setPWM(i+1, 1000);

	}
*/
}

void Update_Motors()
{/*
	for (int i = 0; i < 8; i++)
	{
		if ((Motor_Update_Flag && 0x1 << i) == 1)
		{
			motors.setPWM(i+1, PWM_Table[i]);
		}
	}
*/
}


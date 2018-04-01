#include "TSK_Motors.h"
#include "TSK_Stop.h"
#include "Project_Config.h"
#include "PCA9685.h"
#include <iostream>
#include <string>
#include <unistd.h>


void Calibrate_Motors();
void Initialise_Motors();
void Update_Motors()

PCA9625 motors(1, 0x40); //Setup Comms to Motor Driver

void TSK_Motors()
{

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
	//if so then update PWM and reset update request flag to 0
	while (STOP=='N')
	{
		if (Motor_Update_Flag != 0)
		{
			Update_Motors();
		}
	}
	TSK_Motors_Stop_Flag = 1;
}

void Calibrate_Motors()
{
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
	}
}

void Initialise_Motors()
{
	M1_PWM = 1000;
	M2_PWM = 1000;
	M3_PWM = 1000;
	M4_PWM = 1000;
	M5_PWM = 1000;
	M6_PWM = 1000;
	M7_PWM = 1000;
	M8_PWM = 1000;

	M1_Update_Flag = 1;
	M2_Update_Flag = 1;
	M3_Update_Flag = 1;
	M4_Update_Flag = 1;
	M5_Update_Flag = 1;
	M6_Update_Flag = 1;
	M7_Update_Flag = 1;
	M8_Update_Flag = 1;
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
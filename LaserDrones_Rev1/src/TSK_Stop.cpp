#include "TSK_Stop.h"
#include <wiringPi.h>
#include <thread>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>

//----------External Variables

char Stop = 'N';
int StopPin = 10;
int TSK_Motors_Stop_Flag = 0;
int TSK_Control_Stop_Flag = 0;
int TSK_Proximity_Stop_Flag = 0;
int TSK_Camera_Stop_Flag = 0;
int TSK_IMU_Stop_Flag = 0;


void TSK_Stop()
{
	if (wiringPiSetup() == -1)
	{
		std::cout << "Wiring Pi Setup Failed" << std::endl;
	}

	pinMode(StopPin, INPUT);

	while (1)
	{
		if (digitalRead(StopPin) == 0 || getch() == '\b')
		{
			Stop = 'Y';
			int Stop_Count = 0;
			while (1)
			{
				if (TSK_Motors_Stop_Flag == 1 && TSK_Control_Stop_Flag == 1 &&
					TSK_Proximity_Stop_Flag == 1 && TSK_Camera_Stop_Flag == 1 && 
					TSK_IMU_Stop_Flag==1)
				{
					system("nano poweroff");
				}else
					{
						sleep(1);
						Stop_Count++;
						if (Stop_Count == 5)
						{
							system("nano poweroff");
						}
				}
			}
		}
	}

}

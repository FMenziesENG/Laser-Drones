#include "TSK_Stop.h"
#include "TSK_Interface.h"
#include <wiringPi.h>
#include <pthread.h>
#include <iostream>
#include "Project_Config.h"
#include <unistd.h>

//----------External Variables

char Shutdown = 'N';
char Stop_TSKS = 'N';
char END_Prog = 'N';
char Interface_END = 'N';

int ShutdownPin = SWITCHPIN;

int TSK_Motors_Stop_Flag = 0;
int TSK_Control_Stop_Flag = 1;
int TSK_Proximity_Stop_Flag = 0;
int TSK_Camera_Stop_Flag = 1;
int TSK_IMU_Stop_Flag = 1;
int TSK_Interface_Stop_Flag = 0;

//----------Local Functions
void Stop_TSKS_Check();
void Countdown_Shutdown();

void TSK_Stop()
{
	TSK_Stop_Init = 1;
	//Setup Hardware Triggered Shutdown 
	if (wiringPiSetup() == -1)
	{
		TSK_Stop_wiringPiSetup = 0;
	}else
	{
		TSK_Stop_wiringPiSetup = 1;
	}

	pinMode(ShutdownPin, INPUT);
	int Stop_Count = 0;

	while (END_Prog == 'N')
	{
//		Stop_TSKS_Check();

		if ( Stop_TSKS == 'Y' || Interface_END == 'Y')	//shutdown code and power off raspberry pi if button pressed
		{

			while (END_Prog == 'N')
			{
				if (Stop_TSKS == 'Y' && TSK_Motors_Stop_Flag == 1 && TSK_Control_Stop_Flag == 1 &&
					TSK_Proximity_Stop_Flag == 1 && TSK_Camera_Stop_Flag == 1 &&
					TSK_IMU_Stop_Flag==1 && TSK_Interface_Stop_Flag==1)
				{
					TSK_Stop_Flags = 1;
					TSK_Stop_Shutdown = 1;
//					usleep(OFFTIME);
					Shutdown = 'Y'; //Once all threads close return to main and poweroff
				}else
				if (Interface_END == 'Y' && TSK_Motors_Stop_Flag == 1 && TSK_Control_Stop_Flag == 1 &&
					TSK_Proximity_Stop_Flag == 1 && TSK_Camera_Stop_Flag == 1 &&
					TSK_IMU_Stop_Flag==1)
				{
					TSK_Stop_Flags = 1;
					TSK_Stop_End_prog = 1;
					usleep(OFFTIME);
					Stop_TSKS = 'Y';
					END_Prog = 'Y';
					usleep(OFFTIME);
					//END_Prog = 'Y'; //Once all threads close return to main and end
				}else	//if TSKs fail to end then shutdown after 5 seconds
				{

					sleep(1);
					Stop_Count++;
					if (Stop_Count == 5)
					{
						Shutdown = 'Y';
					}
				}
			}
		}
	}

	TSK_Stop_Init = 0;

}

void Stop_TSKS_Check()
{
	if (digitalRead(ShutdownPin) == 0)
	{
		Stop_TSKS ='Y';
	}
}


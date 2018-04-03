#include "TSK_Stop.h"
#include "TSK_Interface.h"
#include <wiringPi.h>
#include <thread>
#include <iostream>

#include <unistd.h>

//----------External Variables

char Shutdown = 'N';
char Stop_TSKs = 'N';
char END_Prog = 'N';
int ShutdownPin = 10;
int TSK_Motors_Stop_Flag = 0;
int TSK_Control_Stop_Flag = 0;
int TSK_Proximity_Stop_Flag = 0;
int TSK_Camera_Stop_Flag = 0;
int TSK_IMU_Stop_Flag = 0;
int TSK_Interface_Stop_Flag = 0;

//----------Local Functions
void Stop_Check()
void Countdown_Shutdown()

void TSK_Stop()
{
	//Setup Hardware Triggered Shutdown 
	if (wiringPiSetup() == -1)
	{
		std::cout << "Wiring Pi Setup Failed" << std::endl;
	}

	pinMode(ShutdownPin, INPUT);
	int Stop_Count = 0;
	
	while (1)
	{
		Stop_TSKS_Check();
		
		if ( Stop_TSKS == 'Y' || Interface_END == 'Y')	//shutdown code and power off raspberry pi if button pressed
		{
			
			while (1)
			{
				if (Stop_TSKS == 'Y' && TSK_Motors_Stop_Flag == 1 && TSK_Control_Stop_Flag == 1 &&
					TSK_Proximity_Stop_Flag == 1 && TSK_Camera_Stop_Flag == 1 && 
					TSK_IMU_Stop_Flag==1 && TSK_Interface_Stop_Flag==1)
				{
					Shutdown = 'Y'; //Once all threads close return to main and poweroff
				}else if (Interface_END == 'Y' && TSK_Motors_Stop_Flag == 1 && TSK_Control_Stop_Flag == 1 &&
					TSK_Proximity_Stop_Flag == 1 && TSK_Camera_Stop_Flag == 1 && 
					TSK_IMU_Stop_Flag==1 && TSK_Interface_Stop_Flag==1)
				{
					END_Prog = 'Y'; //Once all threads close return to main and end
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

}

void Stop_Check()
{
	if (digitalRead(StopPin) == 0)
	{
		Stop ='Y';
	}
}



/*
Filename : TSK_Sensors
Description : Read Sensors and interpret data
Date : 13-Mar-2018
Author : Fraser Menzies
*/
#define TSK_Sensors_C

/*
Modules
*/
//#include "TSK_Sensors.h"
#include <stdio.h>
#include <pthread.h>
/*
Exported Variables
*/
pthread_t tidSensors;
/*
Prototypes of Local Functions
*/

void *TSK_Sensors(void const *argument);

/*
Local Functions
*/


/*
Function TSK_Sensors
@Description Sensor Task to read sensors
*/

void *TSK_Sensors(void const *argument)
{
    char user_input;

    while(1)
    {
        scanf("%c", &user_input);
        printf("%c", user_input);
    }
}

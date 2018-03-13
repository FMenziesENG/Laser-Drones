/*Written by FMenzies*/

/*
Include Dependencies
*/
#include <stdio.h>
#include <pthread.h>
#include "TSK_Sensors.h"
/*Declare Functions*/

/*Declare Variables*/
pthread_t TSK_Motors;
pthread_t TSK_Vertical;
pthread_t TSK_Rotate;
pthread_t TSK_Horizontal;
pthread_t TSK_OpenCV;

/*Declare and start Threads*/
int main(void)
{
    pthread_create(tidSensors, NULL, TSK_Sensors, NULL);//Start Sensors_TSK
    //Start Motors_TSK
    //Start Open_CV_TSK
}

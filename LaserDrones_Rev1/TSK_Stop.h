#ifndef TSK_Stop_H
#define TSK_Stop_H

void TSK_Stop(); //Stop Thread Name

int StopPin = 10;
int Stop_Count;

char STOP;
//StopFlags- 0, Do not stop. 1, TSK has stopped and is ready for shutdown
int TSK_Motors_Stop_Flag;
int TSK_Control_Stop_Flag;
int TSK_Proximity_Stop_Flag;
int TSK_IMU_Stop_Flag;
int TSK_Camera_Stop_Flag;

#endif
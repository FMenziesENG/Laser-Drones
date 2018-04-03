#ifndef TSK_Stop_H
#define TSK_Stop_H

void TSK_Stop(); //Stop Thread Name

extern int Stop_Count;

extern char Stop;
//StopFlags- 0, Do not stop. 1, TSK has stopped and is ready for shutdown
extern int TSK_Motors_Stop_Flag;
extern int TSK_Control_Stop_Flag;
extern int TSK_Proximity_Stop_Flag;
extern int TSK_IMU_Stop_Flag;
extern int TSK_Camera_Stop_Flag;

#endif

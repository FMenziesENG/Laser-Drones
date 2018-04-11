#ifndef TSK_Stop_H
#define TSK_Stop_H

extern void TSK_Stop(); //Stop Thread Name

extern int Stop_Count;

extern char Stop_TSKS;

extern char Shutdown;
extern char Interface_END;
extern char END_Prog;

extern int Tasks_Initialised; //Initialised in main

//StopFlags- 0, Do not stop. 1, TSK has stopped and is ready for shutdown
extern int TSK_Motors_Stop_Flag;
extern int TSK_Control_Stop_Flag;
extern int TSK_Proximity_Stop_Flag;
extern int TSK_IMU_Stop_Flag;
extern int TSK_Camera_Stop_Flag;
extern int TSK_Interface_Stop_Flag;
#endif

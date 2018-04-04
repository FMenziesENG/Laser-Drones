#ifndef TSK_Interface_H
#define TSK_Interface_H

extern void TSK_Interface(); //Interface Thread Name

extern char Interface_END;

extern int TSK_Stop_Init;
extern int TSK_Stop_wiringPiSetup;
extern int TSK_Stop_Shutdown;
extern int TSK_Stop_End_prog;
extern int TSK_Stop_Flags;

extern int TSK_Proximity_Init;
extern int TSK_Motors_Init;
extern int TSK_IMU_Init;
extern int TSK_Camera_Init;

#endif

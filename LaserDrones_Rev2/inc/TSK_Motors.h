#ifndef TSK_Motors_H
#define TSK_Motors_H

//-------------------Exported Functions-----------------------

extern void TSK_Motors(); //Motor Thread Name

//-------------------Exported Variables-----------------------
//Motor PWM Variables 0-4095 per channel
//extern int PWM_Table[8] ;

//Motor update request variable
//extern char Motor_Update_Flag[8]; //binary number that contains motors that need updating

extern int TSK_Motors_Stop_Flag;
extern int Motor_Update_Flag;
extern bool Cal_Motors_Flag;

#endif

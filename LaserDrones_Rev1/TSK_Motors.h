#ifndef TSK_Motors_H
#define TSK_Motors_H

//-------------------Exported Functions-----------------------

void TSK_Motors(); //Motor Thread Name

//-------------------Exported Variables-----------------------
//Motor PWM Variables 0-4095 per channel
int PWM_Table[8] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
};

//Motor update request variable
char Motor_Update_Flag[8]; //binary number that contains motors that need updating

//-------------------Local Variables-----------------------
const int MAX_PWM = 3000;
const int MIN_PWM = 1500;

#endif

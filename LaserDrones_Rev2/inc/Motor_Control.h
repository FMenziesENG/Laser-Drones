#ifndef Motor_Control_H
#define Motor_Control_H

#include <stdint.h>

//---------------Definitions--------------
#define No_Motors_Channels 0b00000000
#define Up_Motors_Channels 0b11000000
#define Down_Motors_Channels 0b00110000
#define Clockwise_Motors_Channels 0b00001100
#define Anticlockwise_Motors_Channels 0b00000011

//---------------Motor Control Variable Definitions--------------

extern int Sel; //Variable used for Motor Indexing

//---------------Motor Control Structures-----

struct Motors
{
	const char *Name;
	int Setting;
	uint16_t Driver_Channels;
};

extern Motors Motor_Choices[5];

//---------------Motor Control Function Definitions--------------

Motors Get_Motors(char input); //
void Get_Motor_Setting(char input);
void Check_Motor_Update(Motors Check_Motors);
void Update_Motor_Setting(int New_Setting, int Old_Setting_Index);

#endif

#ifndef Motor_Control_H
#define Motor_Control_H

#include <stdint.h>

//---------------Definitions--------------
//--------Motor Channel Definitions-------
#define No_Motors_Channels            0b000000000000
#define Up_Motors_Channels            0b110000000000
#define Down_Motors_Channels          0b001100000000
#define Clockwise_Motors_Channels     0b000000001100
#define Anticlockwise_Motors_Channels 0b000000000011
#define Right_Motors_Channels         0b000000001001
#define Left_Motors_Channels          0b000000000110

#define Channel_1  0b000000000001
#define Channel_2  0b000000000010
#define Channel_3  0b000000000100
#define Channel_4  0b000000001000
#define Channel_9  0b000100000000
#define Channel_10 0b001000000000
#define Channel_11 0b010000000000
#define Channel_12 0b100000000000

#define Init_PWM 230


//---------------Motor Control Variable Definitions--------------

extern int Sel; //Variable used for Motor Indexing
extern int Cal_Sel;
extern int Cal_Motors_Flag;
extern int Cal_Motor;
extern int Cal_Message;
extern int Cal_Motor_Flag;
extern int proceed;
//---------------Motor Control Structures-----

struct Motors
{
	const char *Name;
	int Setting;
	uint16_t Driver_Channels;
};

extern Motors Motor_Choices[7];
extern Motors Motor_Cal_Choices[13];
//---------------Motor Control Function Definitions--------------

Motors Get_Motors(char input); //
void Get_Motor_Setting(char input);
void Check_Motor_Update(Motors Check_Motors);
void Update_Motor_Setting(int New_Setting, int Old_Setting_Index);
//---------------Calibrate Motor Function Definitions--------------
void Get_Calibration_Mode(char input);		//turns Calibration mode on and off
Motors Get_Cal_Motor(char input);			//Chooses motor to Calibrate
void Get_Cal_Motor_Mode(char input);	//Chooses Calibration function
//void Calibrate_Motor(int Cal_Sel);		//Calibrates Cal_Motor
//void Arm_Motor(int channel);			//Arms Cal_Motor
const char* Print_Calibration_Message(int Calibration_Message);	//Print Calibration Messages
#endif

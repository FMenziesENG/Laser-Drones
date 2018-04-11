#ifndef Motor_Control_H
#define Motor_Control_H


//---------------Definitions--------------
#define No_Motors_Channels 0b00000000
#define Up_Motors_Channels 0b11000000
#define Down_Motors_Channels 0b00110000
#define Clockwise_Motors_Channels 0b00001100
#define Anticlockwise_Motors_Channels 0b00000011

//---------------Motor Control Function Definitions--------------

Motors Get_Motors(char input); //
void Get_Motor_Setting(char input);
void Check_Motor_Update(Motors Check_Motors);
void Update_Motor_Setting(int New_Setting, int Old_Setting_Index);

//---------------Motor Control Variable Definitions--------------

int Sel; //Variable used for Motor Indexing

//---------------Motor Control Structures-----

struct Motors
{
	const char *Name;
	int Setting;
	uint16_t Driver_Channels;
};

Motors No_Motors = {
	"No Motors Selected",
	0,
	No_Motors_Channels
};

Motors Up_Motors = {
	"Up Motors Selected",
	0,
	Up_Motors_Channels
};


Motors Down_Motors = {
	"Down Motors Selected",
	0,
	Down_Motors_Channels
};


Motors Clockwise_Motors = {
	"Clockwise Motors Selected",
	0,
	Clockwise_Motors_Channels
};


Motors Anticlockwise_Motors = {
	"Anticlockwise Motors Selected",
	0,
	Anticlockwise_Motors_Channels
};

Motors Selected_Motors = No_Motors;
Motors Old_Motors = Selected_Motors;

Motors Motor_Choices[5] = {No_Motors, Up_Motors, Down_Motors, Clockwise_Motors, Anticlockwise_Motors};


#endif
#include "TSK_Control.h"
#include "TSK_Stop.h"
#include "TSK_Motors.h"
#include "pid.h"

void TSK_Control()
{
//Notes- Remember to place limits on control signals to prevent crazy excessive movement in a  particular direction

//-------------Height Control---------------------------
//Requirements:
//             Setpoint is predefined height = 2000mm
//             Process variable given by Proximity Sensor
//             Output Controls Motor 1-UP,2-UP,3-DOWN,4-DOWN


//-------------Roll Control---------------------------
//Requirements:
//             Setpoint is 0deg/s
//             Process variable given by gyroscope x axis
//             Output Controls Motor 1-UP,2-UP,3-DOWN,4-DOWN

//-------------Pitch Control---------------------------
//Requirements:
//             Setpoint is 0deg/s
//             Process variable given by gyroscope y  axis
//             Output Controls Motor 1-UP,2-UP,3-DOWN,4-DOWN

//-------------Yaw Control---------------------------
//Requirements:
//             Setpoint is given by camera
//             Process variable given by compass
//             Output Controls Motor 5-LEFT,6-LEFT,7-RIGHT,8-RIGHT

	

		//Roll, Pitch and Yaw Control
		//Setpoint =0 on for roll and pitch
		//Camera dictates yaw requirements
		PID Roll = PID(0.1, 100, -100, 0.1, 0.01, 0.5);

	while (STOP == 'N')
	{



	}
	TSK_Control_Stop_Flag ==1;

}
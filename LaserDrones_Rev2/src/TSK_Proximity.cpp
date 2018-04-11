#include <stdlib.h>
#include "TSK_Proximity.h"
#include "PCA9685.h"
#include "TSK_Stop.h"
#include "TSK_Interface.h"

//----------External Variables-------
int Proximity;
int TSK_Proximity_Stop_Flag = 1;


void TSK_Proximity()
{
	TSK_Proximity_Stop_Flag = 0;
	int i;
	int Proximity_sub;
	TSK_Proximity_Init = 1;

	VL53L0X_Error Status = VL53L0X_ERROR_NONE;
	VL53L0X_Dev_t MyDevice;
	VL53L0X_Dev_t *pMyDevice = &MyDevice;
	VL53L0X_RangingMeasurementData_t RangingMeasurementData;

	pMyDevice->I2cDevAddr = 0x29;

	pMyDevice->fd = VL53L0X_i2c_init((char*)"/dev/i2c-1", pMyDevice->I2cDevAddr);//choose between i2c-0 and i2c-1; On the raspberry pi zero, i2c-1 are pins 2 and 3

	if (Status == VL53L0X_ERROR_NONE)
	{
		while(Stop_TSKS == 'N' && Interface_END == 'N')
		{
			Proximity_sub = 0;
			for(i=0;i<50;i++)
			{
				Status = VL53L0X_PerformSingleRangingMeasurement(pMyDevice,&RangingMeasurementData);
				if (Status != VL53L0X_ERROR_NONE) break;
				Proximity_sub += RangingMeasurementData.RangeMilliMeter;
			}
			Proximity = Proximity_sub/50;
		}
		TSK_Proximity_Stop_Flag = 1;
		TSK_Proximity_Init = 0;
	}

}

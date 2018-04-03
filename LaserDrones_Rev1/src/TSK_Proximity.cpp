#include <stdlib.h>
#include <stdio.h>
#include "TSK_Proximity.h"
#include "PCA9685.h"
#include "TSK_Stop.h"


//----------External Variables-------
int Proximity;

void TSK_Proximity()
{
	VL53L0X_Error Status = VL53L0X_ERROR_NONE;
	VL53L0X_Dev_t MyDevice;
	VL53L0X_Dev_t *pMyDevice = &MyDevice;
	VL53L0X_RangingMeasurementData_t RangingMeasurementData;

	printf("VL53L0X API Simple Ranging example FMenzies mod\n\n");

	pMyDevice->I2cDevAddr = 0x29;

	pMyDevice->fd = VL53L0X_i2c_init((char*)"/dev/i2c-1", pMyDevice->I2cDevAddr);//choose between i2c-0 and i2c-1; On the raspberry pi zero, i2c-1 are pins 2 and 3

	if (Status == VL53L0X_ERROR_NONE)
	{
		while(Stop = 'N')
		{
			printf("Call of VL53L0X_PerformSingleRangingMeasurement\n");
			Status = VL53L0X_PerformSingleRangingMeasurement(pMyDevice,&RangingMeasurementData);

			if (Status != VL53L0X_ERROR_NONE) break;

			printf("Measured distance: %i \n\n", RangingMeasurementData.RangeMilliMeter);

			Proximity = RangingMeasurementData.RangeMilliMeter;
		}
		TSK_Proximity_Stop_Flag = 1;
	}

}

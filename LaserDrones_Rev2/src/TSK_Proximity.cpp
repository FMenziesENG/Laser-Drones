#include <stdlib.h>
#include "TSK_Proximity.h"
#include "PCA9685.h"
#include "TSK_Stop.h"
#include "TSK_Interface.h"

//----------External Variables-------
int Proximity;
int TSK_Proximity_Stop_Flag = 1;

//Local Functions
void TSK_Proximity();
//Used for Sensor API
VL53L0X_Error WaitMeasurementDataReady(VL53L0X_DEV Dev);
VL53L0X_Error WaitStopCompleted(VL53L0X_DEV Dev);


void TSK_Proximity()
{
	
	///////////////////////////////
	TSK_Proximity_Stop_Flag = 0;
	int i;
	int Proximity_sub;
	TSK_Proximity_Init = 1;
	
/////SETUP DO NOT CHANGE//////////////////////////
	VL53L0X_Error Status = VL53L0X_ERROR_NONE;
	VL53L0X_Dev_t MyDevice;
	VL53L0X_Dev_t *pMyDevice = &MyDevice;
	
	pMyDevice->I2cDevAddr = 0x29;

	pMyDevice->fd = VL53L0X_i2c_init((char*)"/dev/i2c-1", pMyDevice->I2cDevAddr);//choose between i2c-0 and i2c-1; On the raspberry pi zero, i2c-1 are pins 2 and 3

	if(Status == VL53L0X_ERROR_NONE)
    {
        Status = VL53L0X_DataInit(&MyDevice); // Data initialization
    }

	
    VL53L0X_RangingMeasurementData_t    RangingMeasurementData;
    VL53L0X_RangingMeasurementData_t   *pRangingMeasurementData    = &RangingMeasurementData;

    uint32_t refSpadCount;
    uint8_t isApertureSpads;
    uint8_t VhvSettings;
    uint8_t PhaseCal;
	
	if(Status == VL53L0X_ERROR_NONE)
    {
//        printf ("Call of VL53L0X_StaticInit\n");
        Status = VL53L0X_StaticInit(pMyDevice); // Device Initialization
        // StaticInit will set interrupt by default
    }
    if(Status == VL53L0X_ERROR_NONE)
    {
//        printf ("Call of VL53L0X_PerformRefCalibration\n");
        Status = VL53L0X_PerformRefCalibration(pMyDevice,
        		&VhvSettings, &PhaseCal); // Device Initialization
    }

    if(Status == VL53L0X_ERROR_NONE)
    {
//        printf ("Call of VL53L0X_PerformRefSpadManagement\n");
        Status = VL53L0X_PerformRefSpadManagement(pMyDevice,
        		&refSpadCount, &isApertureSpads); // Device Initialization
    }

    if(Status == VL53L0X_ERROR_NONE)
    {

//        printf ("Call of VL53L0X_SetDeviceMode\n");
        Status = VL53L0X_SetDeviceMode(pMyDevice, VL53L0X_DEVICEMODE_CONTINUOUS_RANGING); // Setup in single ranging mode
    }

    if(Status == VL53L0X_ERROR_NONE)
    {
//		printf ("Call of VL53L0X_StartMeasurement\n");
		Status = VL53L0X_StartMeasurement(pMyDevice);
    }

/////END CALIBRATION///////////////////////////////
	
	while(Stop_TSKS == 'N' && Interface_END == 'N')
	{
		if(Status == VL53L0X_ERROR_NONE)
		{
			int Proximity=0, sumProximity=0, subProximity=0;
			uint32_t measurement;
			uint32_t no_of_measurements = 5;

			uint16_t* pResults = (uint16_t*)malloc(sizeof(uint16_t) * no_of_measurements);

			for(measurement=0; measurement<no_of_measurements; measurement++)
			{

				Status = WaitMeasurementDataReady(pMyDevice);

				if(Status == VL53L0X_ERROR_NONE)
				{
					Status = VL53L0X_GetRangingMeasurementData(pMyDevice, pRangingMeasurementData);

					*(pResults + measurement) = pRangingMeasurementData->RangeMilliMeter;
					subProximity = pRangingMeasurementData->RangeMilliMeter;

					// Clear the interrupt
					VL53L0X_ClearInterruptMask(pMyDevice, VL53L0X_REG_SYSTEM_INTERRUPT_GPIO_NEW_SAMPLE_READY);
					VL53L0X_PollingDelay(pMyDevice);
					sumProximity=sumProximity + subProximity;
				} else {
					break;
				}
			}
			Proximity = sumProximity/5;
			return Proximity;
		
		}    

        free(pResults);
    }

    
    if(Status == VL53L0X_ERROR_NONE)
    {
//        printf ("Call of VL53L0X_StopMeasurement\n");
        Status = VL53L0X_StopMeasurement(pMyDevice);
    }

    if(Status == VL53L0X_ERROR_NONE)
    {
//        printf ("Wait Stop to be competed\n");
        Status = WaitStopCompleted(pMyDevice);
    }

    if(Status == VL53L0X_ERROR_NONE)
	Status = VL53L0X_ClearInterruptMask(pMyDevice,
		VL53L0X_REG_SYSTEM_INTERRUPT_GPIO_NEW_SAMPLE_READY);

    TSK_Proximity_Stop_Flag = 1;
	TSK_Proximity_Init = 0;

}

//  Used for Sensor API
VL53L0X_Error WaitStopCompleted(VL53L0X_DEV Dev) {
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    uint32_t StopCompleted=0;
    uint32_t LoopNb;

    // Wait until it finished
    // use timeout to avoid deadlock
    if (Status == VL53L0X_ERROR_NONE) {
        LoopNb = 0;
        do {
            Status = VL53L0X_GetStopCompletedStatus(Dev, &StopCompleted);
            if ((StopCompleted == 0x00) || Status != VL53L0X_ERROR_NONE) {
                break;
            }
            LoopNb = LoopNb + 1;
            VL53L0X_PollingDelay(Dev);
        } while (LoopNb < VL53L0X_DEFAULT_MAX_LOOP);

        if (LoopNb >= VL53L0X_DEFAULT_MAX_LOOP) {
            Status = VL53L0X_ERROR_TIME_OUT;
        }
	
    }

    return Status;
}

// Used for Sensor API
VL53L0X_Error WaitMeasurementDataReady(VL53L0X_DEV Dev) {
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    uint8_t NewDatReady=0;
    uint32_t LoopNb;

    // Wait until it finished
    // use timeout to avoid deadlock
    if (Status == VL53L0X_ERROR_NONE) {
        LoopNb = 0;
        do {
            Status = VL53L0X_GetMeasurementDataReady(Dev, &NewDatReady);
            if ((NewDatReady == 0x01) || Status != VL53L0X_ERROR_NONE) {
                break;
            }
            LoopNb = LoopNb + 1;
            VL53L0X_PollingDelay(Dev);
        } while (LoopNb < VL53L0X_DEFAULT_MAX_LOOP);

        if (LoopNb >= VL53L0X_DEFAULT_MAX_LOOP) {
            Status = VL53L0X_ERROR_TIME_OUT;
        }
    }

    return Status;
}
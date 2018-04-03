CC = g++ -pthread -lncurses
CC2=gcc

TARGET = Drone_Start

INC = -lwiringPi -LTSK_Motors -LTSK_Proximity -LTSK_Stop -LTSK_Interface

Proj_Dir = /home/pi/Laser-Drones/LaserDrones_Rev2

INCLUDES = \
	-I$(Proj_Dir) \
	-I$(Proj_Dir)/inc \
	-I$(Proj_Dir)/Drone_ProximityTSK/platform/inc \
	-I$(Proj_Dir)/Drone_ProximityTSK/VL53L0X_1.0.2/Api/core/inc \

VPATH = \
	$(Proj_Dir) \
	$(Proj_Dir)/src/ \
	$(Proj_Dir)/Drone_ProximityTSK/platform/src \
	$(Proj_Dir)/Drone_ProximityTSK/VL53L0X_1.0.2/Api/core/src \

SRCcpp =\
	main.cpp \
	TSK_Stop.cpp \
	TSK_Motors.cpp \
	TSK_Proximity.cpp \
	TSK_Interface.cpp \
	I2C.cpp \
	PCA9685.cpp \

SRCc = \
	vl53l0x_api_calibration.c \
	vl53l0x_api_core.c \
	vl53l0x_api_ranging.c \
	vl53l0x_api_strings.c \
	vl53l0x_api.c \
	vl53l0x_platform.c\

OBJ = $(SRCcpp:%.cpp=%.o) $(SRCc:%.c=%.o)


all:$(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(INC) $(INCLUDES) $^ -o $@

TSK_Interface.o: TSK_Interface.cpp
	$(CC) -c $(INC) $(INCLUDES) $^ -o $@	
	
TSK_Stop.o: TSK_Stop.cpp
	$(CC) -c $(INC) $(INCLUDES) $^ -o $@

TSK_Proximity.o: TSK_Proximity.cpp
	$(CC) -c $(INC) $(INCLUDES) $^ -o $@

TSK_Motors.o: TSK_Motors.cpp
	$(CC) -c $(INC) $(INCLUDES) $^ -o $@

I2C.o: I2C.cpp
	$(CC) -c $(INC) $(INCLUDES) $^ -o $@

PCA9685.o: PCA9685.cpp
	$(CC) -c $(INC) $(INCLUDES) $^ -o $@

vl53l0x_api_calibration.o: vl53l0x_api_calibration.c
	$(CC) -c $(INC) $(INCLUDES) $^ -o $@

vl53l0x_api_core.o: vl53l0x_api_core.c
	$(CC2) -c $(INC) $(INCLUDES) $^ -o $@

vl53l0x_api_ranging.o: vl53l0x_api_ranging.c
	$(CC) -c $(INC) $(INCLUDES) $^ -o $@

vl53l0x_api_strings.o: vl53l0x_api_strings.c
	$(CC) -c $(INC) $(INCLUDES) $^ -o $@

vl53l0x_api.o: vl53l0x_api.c
	$(CC) -c $(INC) $(INCLUDES) $^ -o $@

vl53l0x_platform.o: vl53l0x_platform.c
	$(CC2) -c $(INC) $(INCLUDES) $^ -o $@

main.o: main.cpp
	$(CC) -c $(INC) $(INCLUDES) $^ -o $@

clean:
	rm $(TARGET) $(OBJ)

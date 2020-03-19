
#pragma once
 
 
struct IMUdata {
	float TimeStamp;
	float gyro[3];
	float mag[3];
	int number;
};
 
IMUdata setIMU( float data[]);


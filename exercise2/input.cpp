#include "imu.h"
//���ļ����������ݴ���IMUdata�ṹ��
IMUdata setIMU(String data[])
{
	IMUdata imudata;
	for (int i = 0; i < 3; i++)
	{
		imudata.acc[i] = data[i + 1];
		imudata.gyro[i] = data[i + 4];
		imudata.mag[i] = data[i + 7];
	}
	return imudata;
}

#ifndef __MPU6050_H__
#define __MPU6050_H__
#include "main.h"
void MPU6050_Init(void);

typedef struct
{
    int16_t Accel_X;
    int16_t Accel_Y;
    int16_t Accel_Z;
    int16_t Gyro_X;
    int16_t Gyro_Y;
    int16_t Gyro_Z;
    int16_t Temperature;
}MPU6050_RawData_t;

typedef struct
{
    float Ax;
    float Ay;
    float Az;
    float Gx;
    float Gy;
    float Gz;
    float T;
}MPU6050_Data_t;

void MPU6050_Update(MPU6050_Data_t *Data);
#endif

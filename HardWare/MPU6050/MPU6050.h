#ifndef __MPU6050_H__
#define __MPU6050_H__
void MPU6050_Init(void);
void MPU6050_Proc(void);

void MPU6050_Update(void);
float MPU6050_Get_Ax(void);
float MPU6050_Get_Ay(void);
float MPU6050_Get_Az(void);

float MPU6050_Get_Temperature(void);

float MPU6050_Get_Gx(void);
float MPU6050_Get_Gy(void);
float MPU6050_Get_Gz(void);


#endif

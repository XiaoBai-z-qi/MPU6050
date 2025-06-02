#include "main.h"
#include "mpu6050.h"
#include "define_conf.h"

#define MPU6050_ADDR 0xD0

static float ax, ay, az, gx, gy, gz, temperature;
static float yaw, pitch, roll;  //欧拉角， 单位°
static void MPU6050_WriteReg(uint8_t RegAddr, uint8_t Data)
{
    HAL_I2C_Mem_Write(MPU6050_I2C, MPU6050_ADDR, RegAddr, I2C_MEMADD_SIZE_8BIT, &Data, 1, 1000);
}

static uint8_t MPU6050_ReadReg(uint8_t RegAddr)
{
    uint8_t Data;
   HAL_I2C_Mem_Read(MPU6050_I2C, MPU6050_ADDR, RegAddr, I2C_MEMADD_SIZE_8BIT, &Data, 1, 1000);
    return Data;
}

void MPU6050_Init(void)
{
    MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x80);    //复位
    HAL_Delay(100);
    MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x00);   //关闭睡眠模式 
    
    MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);    //设置陀螺仪传感器为±2000°/s
    MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x00);   //设置加速度传感器为±2g
}

void MPU6050_Proc(void)
{
    static uint32_t nxt = 0;
    if (HAL_GetTick() < nxt) return;

    MPU6050_Update();   //更新传感器的值

    yaw     = yaw   + gz * 0.005;
    pitch   = pitch + gx * 0.005;
    roll    = roll  + gy * 0.005;

    nxt += 5;
}

void MPU6050_Update(void)
{
    int16_t ax_raw = (int16_t)(MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H) << 8 |   MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L)); //读取X轴加速度
    int16_t ay_raw = (int16_t)(MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H) << 8 |   MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L)); //读取Y轴加速度
    int16_t az_raw = (int16_t)(MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H) << 8 |   MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L)); //读取Z轴加速度
    ax = ax_raw * 6.1035e-5f;
    ay = ay_raw * 6.1035e-5f;
    az = az_raw * 6.1035e-5f;

    int16_t temperature_raw = (int16_t)(MPU6050_ReadReg(MPU6050_TEMP_OUT_H) << 8 | MPU6050_ReadReg(MPU6050_TEMP_OUT_L)); //读取温度
    temperature = (float)((temperature_raw / 340) + 36.53); //温度转换

    int16_t gx_raw = (int16_t)(MPU6050_ReadReg(MPU6050_GYRO_XOUT_H) << 8 |   MPU6050_ReadReg(MPU6050_GYRO_XOUT_L)); //读取X轴加速度
    int16_t gy_raw = (int16_t)(MPU6050_ReadReg(MPU6050_GYRO_YOUT_H) << 8 |   MPU6050_ReadReg(MPU6050_GYRO_YOUT_L)); //读取Y轴加速度
    int16_t gz_raw = (int16_t)(MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H) << 8 |   MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L)); //读取Z轴加速度
    gx = gx_raw * 6.1035e-2f;
    gy = gy_raw * 6.1035e-2f;
    gz = gz_raw * 6.1035e-2f;

}

float MPU6050_Get_Ax(void)
{
    return ax;
}

float MPU6050_Get_Ay(void)
{
    return ay;
}
float MPU6050_Get_Az(void)
{
    return az;
}

float MPU6050_Get_Temperature(void)
{
    return temperature;
}
float MPU6050_Get_Gx(void)
{
    return gx;
}
float MPU6050_Get_Gy(void)
{
    return gy;
}
float MPU6050_Get_Gz(void)
{
    return gz;
}
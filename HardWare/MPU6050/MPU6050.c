#include "main.h"
#include "mpu6050.h"
#include "define_conf.h"

#define MPU6050_ADDR 0xD0
static void MPU6050_WriteReg(uint8_t RegAddr, uint8_t Data)
{
    HAL_I2C_Mem_Write(MPU6050_I2C, MPU6050_ADDR, RegAddr, I2C_MEMADD_SIZE_8BIT, &Data, 1, 1000);
}

uint8_t MPU6050_ReadReg(uint8_t RegAddr)
{
    uint8_t Data;
   HAL_I2C_Mem_Read(MPU6050_I2C, MPU6050_ADDR, RegAddr, I2C_MEMADD_SIZE_8BIT, &Data, 1, 1000);
    return Data;
}

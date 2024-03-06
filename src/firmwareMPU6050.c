#include <libopencm3/stm32/i2c.h>

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "firmwareMPU6050.h"
#include "i2c.h"
#include "uart.h"

#define ALPHA 0.1
#define NUMSAMPLES 2000

void delayMs(uint16_t ms)
{
    for (volatile int i = 0; i < ms * 800; i++)
    {
        __asm__("nop");
    }
}

void mpuReadReg(mpu_t *mpu, uint8_t reg, uint8_t * data) 
{
    *data = i2cReadReg(mpu->i2c, mpu->addr, reg);
}

int16_t mpuReadSeq(mpu_t *mpu, uint8_t reg, uint8_t * data, uint8_t len) 
{
    return i2cReadSeq(mpu->i2c, mpu->addr, reg, data, len);
}

void mpuWriteReg(mpu_t *mpu, uint8_t reg, uint8_t data) 
{
    i2cWriteReg(mpu->i2c, mpu->addr, reg, data);
}

void mpuWriteBits(mpu_t *mpu, uint8_t reg, uint8_t base, uint8_t len, uint8_t data) 
{
    i2cSetBitField(mpu->i2c, mpu->addr, reg, base, len, data);
}


void mpuSetup(mpu_t *mpu)
{
    mpuWriteBits(mpu, MPU6050_REG_PWR_MGMT_1, 0x6,1,0);
    delayMs(10);
    mpuWriteBits(mpu, MPU6050_REG_PWR_MGMT_1, 0x0, 0x3, 0x1);
    mpuWriteBits(mpu, MPU6050_REG_CONFIG, 0x0, 0x3, 0x3);
    mpuWriteReg(mpu, MPU6050_REG_SMPRT_DIV, 4);
    mpuWriteBits(mpu, MPU6050_REG_GYRO_CONFIG, 0x3, 0x2, MPU_GYRO_FS);
    mpuWriteBits(mpu, MPU6050_REG_ACCEL_CONFIG, 0x3, 0x2, MPU_ACCEL_FS);
}

void mpuGetRawData(mpu_t *mpu) 
{

    volatile uint8_t buffer[14];
    mpuReadSeq(mpu, MPU6050_REG_ACCEL_XOUT_H, (uint8_t *) buffer, 14);

    mpu->rawSensorData[0] = (((int16_t) buffer[0]) << 8) | buffer[1];
    mpu->rawSensorData[1] = (((int16_t) buffer[2]) << 8) | buffer[3];
    mpu->rawSensorData[2] = (((int16_t) buffer[4]) << 8) | buffer[5];

    mpu->rawSensorData[3] = (((int16_t) buffer[8]) << 8) | buffer[9];
    mpu->rawSensorData[4] = (((int16_t) buffer[10]) << 8) | buffer[11];
    mpu->rawSensorData[5] = (((int16_t) buffer[12]) << 8) | buffer[13];
}


double emaFilter(double *currentValue, double *previousValue)
{
    return  + 0.1 * (*currentValue + *previousValue - *previousValue); //0.1 chosen at random
}

void lowPassedData(mpu_t *mpu, double *oldData)
{
    for (uint8_t i = 0; i < ARRAY_LENGTH(mpu->sensorData); i++)
    {
        emaFilter(&mpu->sensorData[i], &oldData[i]);
    }
}


void calculateOffset(mpu_t *mpu, int16_t *offset)
{
    int16_t sum[6] = {0};
    for (uint16_t i = 0; i < NUMSAMPLES; i++)
    {
        mpuGetRawData(mpu);
        for (uint8_t j = 0; j < ARRAY_LENGTH(mpu->rawSensorData); j++)
        {
            sum[j] += mpu->rawSensorData[j];
        }

    }

    for (int i = 0; i < 6; i++)
    {
        offset[i] = sum[i] / NUMSAMPLES;
    }
}



void mpuFixData(mpu_t *mpu, int16_t *offset) 
{
    mpuGetRawData(mpu);
    for (uint8_t i = 0; i < ARRAY_LENGTH(mpu->sensorData); i++)
    {
        mpu->sensorData[i] = (mpu->rawSensorData[i] - offset[i]) / ( i < 3 ? MPU_AGAIN : MPU_GGAIN );
    }
    mpu->sensorData[0] *= 9.81;
    mpu->sensorData[1] *= 9.81;
    mpu->sensorData[2] *= 9.81;
}


  
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
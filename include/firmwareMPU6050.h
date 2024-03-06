
#pragma once

#define CHIP_NAME                 "TDK MPU6050"        /**< chip name */
#define MANUFACTURER_NAME         "TDK"                /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.375f               /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        3.46f                /**< chip max supply voltage */
#define MAX_CURRENT               3.9f                 /**< chip max current */
#define TEMPERATURE_MIN           -40.0f               /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                /**< chip max operating temperature */

/**
 * @brief chip register definition
 */
#define MPU6050_REG_SELF_TEST_X         0x0D        /**< self test x register */
#define MPU6050_REG_SELF_TEST_Y         0x0E        /**< self test y register */
#define MPU6050_REG_SELF_TEST_Z         0x0F        /**< self test z register */
#define MPU6050_REG_SELF_TEST_A         0x10        /**< self test a register */
#define MPU6050_REG_SMPRT_DIV           0x19        /**< smprt div register */
#define MPU6050_REG_CONFIG              0x1A        /**< configure register */
#define MPU6050_REG_GYRO_CONFIG         0x1B        /**< gyro configure register */
#define MPU6050_REG_ACCEL_CONFIG        0x1C        /**< accel configure register */
#define MPU6050_REG_MOTION_THRESHOLD    0x1F        /**< motion threshold register */
#define MPU6050_REG_MOTION_DURATION     0x20        /**< motion duration register */
#define MPU6050_REG_FIFO_EN             0x23        /**< fifo enable register */
#define MPU6050_REG_I2C_MST_CTRL        0x24        /**< i2c master ctrl register */
#define MPU6050_REG_I2C_MST_STATUS      0x36        /**< i2c master status register */
#define MPU6050_REG_I2C_MST_DELAY_CTRL  0x67        /**< i2c master delay ctrl register */
#define MPU6050_REG_I2C_SLV0_ADDR       0x25        /**< iic slave0 address register */
#define MPU6050_REG_I2C_SLV0_REG        0x26        /**< iic slave0 reg register */
#define MPU6050_REG_I2C_SLV0_CTRL       0x27        /**< iic slave0 ctrl register */
#define MPU6050_REG_I2C_SLV0_DO         0x63        /**< iic slave0 do register */
#define MPU6050_REG_I2C_SLV1_ADDR       0x28        /**< iic slave1 address register */
#define MPU6050_REG_I2C_SLV1_REG        0x29        /**< iic slave1 reg register */
#define MPU6050_REG_I2C_SLV1_CTRL       0x2A        /**< iic slave1 ctrl register */
#define MPU6050_REG_I2C_SLV1_DO         0x64        /**< iic slave1 do register */
#define MPU6050_REG_I2C_SLV2_ADDR       0x2B        /**< iic slave2 address register */
#define MPU6050_REG_I2C_SLV2_REG        0x2C        /**< iic slave2 reg register */
#define MPU6050_REG_I2C_SLV2_CTRL       0x2D        /**< iic slave2 ctrl register */
#define MPU6050_REG_I2C_SLV2_DO         0x65        /**< iic slave2 do register */
#define MPU6050_REG_I2C_SLV3_ADDR       0x2E        /**< iic slave3 address register */
#define MPU6050_REG_I2C_SLV3_REG        0x2F        /**< iic slave3 reg register */
#define MPU6050_REG_I2C_SLV3_CTRL       0x30        /**< iic slave3 ctrl register */
#define MPU6050_REG_I2C_SLV3_DO         0x66        /**< iic slave3 do register */
#define MPU6050_REG_I2C_SLV4_ADDR       0x31        /**< iic slave4 address register */
#define MPU6050_REG_I2C_SLV4_REG        0x32        /**< iic slave4 reg register */
#define MPU6050_REG_I2C_SLV4_CTRL       0x34        /**< iic slave4 ctrl register */
#define MPU6050_REG_I2C_SLV4_DO         0x33        /**< iic slave4 do register */
#define MPU6050_REG_I2C_SLV4_DI         0x35        /**< iic slave4 di register */
#define MPU6050_REG_EXT_SENS_DATA_00    0x49        /**< extern sensor data 00 register */
#define MPU6050_REG_INT_PIN_CFG         0x37        /**< interrupt pin configure register */
#define MPU6050_REG_INT_ENABLE          0x38        /**< interrupt enable register */
#define MPU6050_REG_INT_STATUS          0x3A        /**< interrupt status register */
#define MPU6050_REG_ACCEL_XOUT_H        0x3B        /**< accel xout high register */
#define MPU6050_REG_ACCEL_XOUT_L        0x3C        /**< accel xout low register */
#define MPU6050_REG_ACCEL_YOUT_H        0x3D        /**< accel yout high register */
#define MPU6050_REG_ACCEL_YOUT_L        0x3E        /**< accel yout low register */
#define MPU6050_REG_ACCEL_ZOUT_H        0x3F        /**< accel zout high register */
#define MPU6050_REG_ACCEL_ZOUT_L        0x40        /**< accel zout low register */
#define MPU6050_REG_TEMP_OUT_H          0x41        /**< temp high register */
#define MPU6050_REG_TEMP_OUT_L          0x42        /**< temp low register */
#define MPU6050_REG_GYRO_XOUT_H         0x43        /**< gyro xout high register */
#define MPU6050_REG_GYRO_XOUT_L         0x44        /**< gyro xout low register */
#define MPU6050_REG_GYRO_YOUT_H         0x45        /**< gyro yout high register */
#define MPU6050_REG_GYRO_YOUT_L         0x46        /**< gyro yout low register */
#define MPU6050_REG_GYRO_ZOUT_H         0x47        /**< gyro zout high register */
#define MPU6050_REG_GYRO_ZOUT_L         0x48        /**< gyro zout low register */
#define MPU6050_REG_SIGNAL_PATH_RESET   0x68        /**< signal path reset register */
#define MPU6050_REG_USER_CTRL           0x6A        /**< user ctrl register */
#define MPU6050_REG_PWR_MGMT_1          0x6B        /**< power management 1 register */
#define MPU6050_REG_PWR_MGMT_2          0x6C        /**< power management 2 register */
#define MPU6050_REG_BANK_SEL            0x6D        /**< bank sel register */
#define MPU6050_REG_MEM                 0x6F        /**< memory register */
#define MPU6050_REG_PROGRAM_START       0x70        /**< program start register */
#define MPU6050_REG_FIFO_COUNTH         0x72        /**< fifo count high threshold register */
#define MPU6050_REG_FIFO_COUNTL         0x73        /**< fifo count low threshold register */
#define MPU6050_REG_R_W                 0x74        /**< fifo read write data register */
#define MPU6050_REG_WHO_AM_I            0x75        /**< who am I register */

/**
 * @brief mpu6050 dmp code definition
 */
#define MPU6050_DMP_SAMPLE_RATE               200                                                 /**< sample rate */
#define MPU6050_DMP_GYRO_SF                   (46850825LL * 200 / MPU6050_DMP_SAMPLE_RATE)        /**< gyro sf */
#define MPU6050_DMP_D_PEDSTD_TIMECTR          964                                                 /**< walk time mem register */
#define MPU6050_DMP_D_PEDSTD_STEPCTR          (768 + 0x60)                                        /**< step counter mem register */
#define MPU6050_DMP_D_1_36                    (256 + 36)                                          /**< 36 register */
#define MPU6050_DMP_D_1_40                    (256 + 40)                                          /**< 40 register */
#define MPU6050_DMP_D_1_44                    (256 + 44)                                          /**< 44 register */
#define MPU6050_DMP_D_1_72                    (256 + 72)                                          /**< 72 register */
#define MPU6050_DMP_D_1_79                    (256 + 79)                                          /**< 79 register */
#define MPU6050_DMP_D_1_88                    (256 + 88)                                          /**< 88 register */
#define MPU6050_DMP_D_1_90                    (256 + 90)                                          /**< 90 register */
#define MPU6050_DMP_D_1_92                    (256 + 92)                                          /**< 92 register */
#define MPU6050_DMP_D_1_218                   (256 + 218)                                         /**< 218 register */
#define MPU6050_DMP_D_0_22                    (512 + 22)                                          /**< 22 register */
#define MPU6050_DMP_D_0_104                   104                                                 /**< 104 register */
#define MPU6050_DMP_TAPW_MIN                  478                                                 /**< tap time min register */
#define MPU6050_DMP_TAP_THX                   468                                                 /**< tap threshold x register */
#define MPU6050_DMP_TAP_THY                   472                                                 /**< tap threshold y register */
#define MPU6050_DMP_TAP_THZ                   476                                                 /**< tap threshold z register */
#define MPU6050_DMP_CFG_6                     2753                                                /**< cfg 6 register */
#define MPU6050_DMP_CFG_8                     2718                                                /**< cfg 8 register */
#define MPU6050_DMP_CFG_MOTION_BIAS           1208                                                /**< motion bias register */
#define MPU6050_DMP_CFG_LP_QUAT               2712                                                /**< lp quat register */
#define MPU6050_DMP_CFG_FIFO_ON_EVENT         2690                                                /**< fifo on event register */
#define MPU6050_DMP_FCFG_1                    1062                                                /**< fcfg 1 register */
#define MPU6050_DMP_FCFG_2                    1066                                                /**< fcfg 2 register */
#define MPU6050_DMP_FCFG_3                    1088                                                /**< fcfg 3 register */
#define MPU6050_DMP_FCFG_7                    1073                                                /**< fcfg 7 register */
#define MPU6050_DMP_D_EXT_GYRO_BIAS_X         (61 * 16)                                           /**< gyro bias x register */
#define MPU6050_DMP_D_EXT_GYRO_BIAS_Y         (61 * 16 + 4)                                       /**< gyro bias y register */
#define MPU6050_DMP_D_EXT_GYRO_BIAS_Z         (61 * 16 + 8)                                       /**< gyro bias z register */
#define MPU6050_DMP_D_ACCEL_BIAS              660                                                 /**< accel bias register */
#define MPU6050_DMP_FEATURE_SEND_ANY_GYRO     (MPU6050_DMP_FEATURE_SEND_RAW_GYRO | \
                                               MPU6050_DMP_FEATURE_SEND_CAL_GYRO)                 /**< send any gyro register */
#define MPU6050_DMP_CFG_15                    2727                                                /**< cfg 15 register */
#define MPU6050_DMP_CFG_27                    2742                                                /**< cfg 27 register */
#define MPU6050_DMP_CFG_GYRO_RAW_DATA         2722                                                /**< cfg gyro raw data register */
#define MPU6050_DMP_CFG_20                    2224                                                /**< cfg 20 register */
#define MPU6050_DMP_CFG_ORIENT_INT            1853                                                /**< cfg orient int register */
#define MPU6050_DMP_QUAT_ERROR_THRESH         (1L << 24)                                          /**< quat error thresh */
#define MPU6050_DMP_QUAT_MAG_SQ_NORMALIZED    (1L << 28)                                          /**< quat mag sq normalized */
#define MPU6050_DMP_QUAT_MAG_SQ_MIN           (MPU6050_DMP_QUAT_MAG_SQ_NORMALIZED - \
                                               MPU6050_DMP_QUAT_ERROR_THRESH)                     /**< quat mag sq min */
#define MPU6050_DMP_QUAT_MAG_SQ_MAX           (MPU6050_DMP_QUAT_MAG_SQ_NORMALIZED + \
                                               MPU6050_DMP_QUAT_ERROR_THRESH)                     /**< quat mag sq max */
#define MPU6050_DMP_INT_SRC_TAP               0x01                                                /**< int src tap */
#define MPU6050_DMP_INT_SRC_ORIENT            0x08                                                /**< int src orient */
#define MPU6050_DMP_TAP_THRESH                250                                                 /**< 250 mg/ms */
#define MPU6050_DMP_TAP_MIN_TAP_COUNT         1                                                   /**< 1 */
#define MPU6050_DMP_TAP_TIME                  100                                                 /**< 100 ms */
#define MPU6050_DMP_TAP_TIME_MULTI            200                                                 /**< 200 ms */
#define MPU6050_DMP_SHAKE_REJECT_THRESH       200                                                 /**< 200 ms */
#define MPU6050_DMP_SHAKE_REJECT_TIME         40                                                  /**< 40 ms */
#define MPU6050_DMP_SHAKE_REJECT_TIMEOUT      10                                                  /**< 10 ms */

#define MPU_GYRO_FS_250         0
#define MPU_GYRO_FS_500         1
#define MPU_GYRO_FS_1000        2
#define MPU_GYRO_FS_2000        3

#define MPU_ACCEL_FS_BASE       3
#define MPU_ACCEL_FS_LEN        2
#define MPU_ACCEL_FS_2          0
#define MPU_ACCEL_FS_4          1
#define MPU_ACCEL_FS_8          2
#define MPU_ACCEL_FS_16         3


#define MPU_GYRO_LSB_250    131.0
#define MPU_GYRO_LSB_500    65.5
#define MPU_GYRO_LSB_1000   32.8
#define MPU_GYRO_LSB_2000   16.4

#define MPU_ACCEL_LSB_2     16384.0
#define MPU_ACCEL_LSB_4      8192.0
#define MPU_ACCEL_LSB_8      4096.0
#define MPU_ACCEL_LSB_16     2048.0

#define MPU_GYRO_FS         MPU_GYRO_FS_2000
#define MPU_ACCEL_FS        MPU_ACCEL_FS_16

#if (MPU_GYRO_FS == MPU_GYRO_FS_250)
    #define MPU_GGAIN   MPU_GYRO_LSB_250
#elif (MPU_GYRO_FS == MPU_GYRO_FS_500)
    #define MPU_GGAIN   MPU_GYRO_LSB_500
#elif (MPU_GYRO_FS == MPU_GYRO_FS_1000)
    #define MPU_GGAIN   MPU_GYRO_LSB_1000
#elif (MPU_GYRO_FS == MPU_GYRO_FS_2000)
    #define MPU_GGAIN   MPU_GYRO_LSB_2000
#endif

#if (MPU_ACCEL_FS == MPU_ACCEL_FS_2)
    #define MPU_AGAIN MPU_ACCEL_LSB_2
#elif (MPU_ACCEL_FS == MPU_ACCEL_FS_4)
    #define MPU_AGAIN MPU_ACCEL_LSB_4
#elif (MPU_ACCEL_FS == MPU_ACCEL_FS_8)
    #define MPU_AGAIN MPU_ACCEL_LSB_8
#elif (MPU_ACCEL_FS == MPU_ACCEL_FS_16)
    #define MPU_AGAIN MPU_ACCEL_LSB_16
#endif


#define MPU_AXOFFSET        0
#define MPU_AYOFFSET        0
#define MPU_AZOFFSET        0

#define MPU_GXOFFSET        0
#define MPU_GYOFFSET        0
#define MPU_GZOFFSET        0
#define ARRAY_LENGTH(array) (sizeof(array) / sizeof((array)[0]))

typedef struct mpu {
    uint32_t i2c;
    uint8_t addr;
    double sensorData[6];
    int16_t rawSensorData[6];

} mpu_t;


void delayMs(uint16_t ms);
void mpuReadReg(mpu_t *mpu, uint8_t reg, uint8_t * data);
int16_t mpuReadSeq(mpu_t *mpu, uint8_t reg, uint8_t * data, uint8_t len); 
void mpuWriteReg(mpu_t *mpu, uint8_t reg, uint8_t data);
void mpuWriteBits(mpu_t *mpu, uint8_t reg, uint8_t base, uint8_t len, uint8_t data);
void mpuSetup(mpu_t *mpu);
void mpuGetRawData(mpu_t *mpu);
void calculateOffset(mpu_t *mpu, int16_t *offset);
void mpuFixData(mpu_t *mpu, int16_t *offset);
double emaFilter(double *currentValue, double *previousValue);
void lowPassedData(mpu_t *mpu, double *oldData);

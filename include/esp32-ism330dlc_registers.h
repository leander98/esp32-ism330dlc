#ifndef ESP32_ISM330DLC_REGISTERS_H
#define ESP32_ISM330DLC_REGISTERS_H

#include <stdint.h>

/** Register addresses according to datasheet ISM330DLC*/

#define FUNC_CFG_ACCESS                 0x01    /*R/W - Embedded functions configuration register*/

#define SENSOR_SYNC_TIME_FRAME          0x04    /*R/W - Sensor synchronization time frame register*/
#define SENSOR_SYNC_RES_RATIO           0x05    /*R/W - Sensor synchronization resolution ratio register*/

#define FIFO_CTRL1                      0x06    /*R/W - FIFO control register 1*/
#define FIFO_CTRL2                      0x07    /*R/W - FIFO control register 2*/
#define FIFO_CTRL3                      0x08    /*R/W - FIFO control register 3*/
#define FIFO_CTRL4                      0x09    /*R/W - FIFO control register 4*/
#define FIFO_CTRL5                      0x0A    /*R/W - FIFO control register 5*/

#define DRDY_PULSE_CFG                  0x0B    /*R/W - Data ready pulse configuration register*/

#define INT1_CTRL                       0x0D    /*R/W - Interrupt signal control register 1*/
#define INT2_CTRL                       0x0E    /*R/W - Interrupt signal control register 2*/

#define WHO_AM_I                        0x0F    /*R/W - WHO_AM_I identifier register*/

#define CTRL1_XL                        0x10    /*R/W - Control register 1 - Accelerometer*/
#define CTRL2_G                         0x11    /*R/W - Control register 2 - Gyroscope*/
#define CTRL3_C                         0x12    /*R/W - Control register 3 - Control*/
#define CTRL4_C                         0x13    /*R/W - Control register 4 - Control*/
#define CTRL5_C                         0x14    /*R/W - Control register 5 - Control*/
#define CTRL6_C                         0x15    /*R/W - Control register 6 - Control*/
#define CTRL7_G                         0x16    /*R/W - Control register 7 - Gyroscope*/
#define CTRL8_XL                        0x17    /*R/W - Control register 8 - Accelerometer*/
#define CTRL9_XL                        0x18    /*R/W - Control register 9 - Accelerometer*/
#define CTRL10_C                        0x19    /*R/W - Control register 10 - Control*/

#define MASTER_CONFIG                   0x1A    /*R/W - Master configuration register*/

#define WAKE_UP_SRC                     0x1B    /*R - Wake-up source register*/

#define TAP_SRC                         0x1C    /*R - Tap source register*/

#define D6D_SRC                         0x1D    /*R - 6D source register*/

#define STATUS_REG                      0x1E    /*R - Status register*/

#define OUT_TEMP_L                      0x20    /*R - Output temperature low register*/
#define OUT_TEMP_H                      0x21    /*R - Output temperature high register*/

#define OUTX_L_G                        0x22    /*R - Output X-axis low register*/
#define OUTX_H_G                        0x23    /*R - Output X-axis high register*/
#define OUTY_L_G                        0x24    /*R - Output Y-axis low register*/
#define OUTY_H_G                        0x25    /*R - Output Y-axis high register*/
#define OUTZ_L_G                        0x26    /*R - Output Z-axis low register*/
#define OUTZ_H_G                        0x27    /*R - Output Z-axis high register*/
#define OUTX_L_XL                       0x28    /*R - Output X-axis low register*/
#define OUTX_H_XL                       0x29    /*R - Output X-axis high register*/
#define OUTY_L_XL                       0x2A    /*R - Output Y-axis low register*/
#define OUTY_H_XL                       0x2B    /*R - Output Y-axis high register*/
#define OUTZ_L_XL                       0x2C    /*R - Output Z-axis low register*/
#define OUTZ_H_XL                       0x2D    /*R - Output Z-axis high register*/

#define SENSORHUB1_REG                  0x2E    /*R - Sensor hub register 1*/
#define SENSORHUB2_REG                  0x2F    /*R - Sensor hub register 2*/
#define SENSORHUB3_REG                  0x30    /*R - Sensor hub register 3*/
#define SENSORHUB4_REG                  0x31    /*R - Sensor hub register 4*/
#define SENSORHUB5_REG                  0x32    /*R - Sensor hub register 5*/
#define SENSORHUB6_REG                  0x33    /*R - Sensor hub register 6*/
#define SENSORHUB7_REG                  0x34    /*R - Sensor hub register 7*/
#define SENSORHUB8_REG                  0x35    /*R - Sensor hub register 8*/
#define SENSORHUB9_REG                  0x36    /*R - Sensor hub register 9*/
#define SENSORHUB10_REG                 0x37    /*R - Sensor hub register 10*/
#define SENSORHUB11_REG                 0x38    /*R - Sensor hub register 11*/
#define SENSORHUB12_REG                 0x39    /*R - Sensor hub register 12*/

#define FIFO_STATUS1                    0x3A    /*R - FIFO status register 1*/
#define FIFO_STATUS2                    0x3B    /*R - FIFO status register 2*/
#define FIFO_STATUS3                    0x3C    /*R - FIFO status register 3*/
#define FIFO_STATUS4                    0x3D    /*R - FIFO status register 4*/

#define FIFO_DATA_OUT_L                 0x3E    /*R - FIFO data output low register*/
#define FIFO_DATA_OUT_H                 0x3F    /*R - FIFO data output high register*/

#define TIMESTAMP0_REG                  0x40    /*R - Timestamp register 0*/
#define TIMESTAMP1_REG                  0x41    /*R - Timestamp register 1*/
#define TIMESTAMP2_REG                  0x42    /*R/W - Timestamp register 2*/

#define SENSORHUB13_REG                 0x4D    /*R - Sensor hub register 13*/
#define SENSORHUB14_REG                 0x4E    /*R - Sensor hub register 14*/
#define SENSORHUB15_REG                 0x4F    /*R - Sensor hub register 15*/
#define SENSORHUB16_REG                 0x50    /*R - Sensor hub register 16*/
#define SENSORHUB17_REG                 0x51    /*R - Sensor hub register 17*/
#define SENSORHUB18_REG                 0x52    /*R - Sensor hub register 18*/

#define FUNC_SRC1                       0x53    /*R - Function source register*/
#define FUNC_SRC2                       0x54    /*R - Function source register*/
#define TAP_CFG                         0x58    /*R/W - Tap configuration register*/
#define TAP_THS_6D                      0x59    /*R/W - Tap threshold register*/
#define INT_DUR2                        0x5A    /*R/W - Interrupt duration register*/
#define WAKE_UP_THS                     0x5B    /*R/W - Wake-up threshold register*/
#define WAKE_UP_DUR                     0x5C    /*R/W - Wake-up duration register*/
#define FREE_FALL                       0x5D    /*R/W - Free-fall configuration register*/
#define MD1_CFG                         0x5E    /*R/W - Interrupt configuration register 1*/
#define MD2_CFG                         0x5F    /*R/W - Interrupt configuration register 2*/

#define MASTER_CMD_CODE                 0x60   /*R/W - Master command code register*/

#define SENS_SYNC_SPI_ERROR_CODE        0x61   /*R - Sensor synchronization SPI error code register*/

#define OUT_MAG_RAW_X_L                 0x66   /*R - Output magnetometer X-axis low register*/
#define OUT_MAG_RAW_X_H                 0x67   /*R - Output magnetometer X-axis high register*/
#define OUT_MAG_RAW_Y_L                 0x68   /*R - Output magnetometer Y-axis low register*/
#define OUT_MAG_RAW_Y_H                 0x69   /*R - Output magnetometer Y-axis high register*/
#define OUT_MAG_RAW_Z_L                 0x6A   /*R - Output magnetometer Z-axis low register*/
#define OUT_MAG_RAW_Z_H                 0x6B   /*R - Output magnetometer Z-axis high register*/

#define INT_OIS                         0x6F   /*R/W - Interrupt OIS configuration register*/

#define CTRL1_OIS                       0x70   /*R/W - Control register 1 - OIS*/
#define CTRL2_OIS                       0x71   /*R/W - Control register 2 - OIS*/
#define CTRL3_OIS                       0x72   /*R/W - Control register 3 - OIS*/
#define X_OFS_USR                       0x73   /*R/W - X-axis offset user register*/
#define Y_OFS_USR                       0x74   /*R/W - Y-axis offset user register*/
#define Z_OFS_USR                       0x75   /*R/W - Z-axis offset user register*/


/** Register bit mapping */

/*FUNC_CFG_ACCESS*/
typedef union {
    struct {
        uint8_t uFunc_Cfg_Gen : 1;              /*Enable access to the embedded functions configuration registers, 0: disabled, 1: enabled*/
        uint8_t uReserved : 7;
    };
    uint8_t byte;
} ism330dlc_FUNC_CFG_ACCESS_t;

/*SENSOR_SYNC_TIME_FRAME*/
typedef union {
    struct {
        uint8_t uReserved : 4;
        uint8_t uSensor_Sync_Time_Frame : 4;    /*Sensor synchronization time frame with a step of 500 ms and full range of 5 s. Unsigned 8-bit. Default value: 0000 0000 (sensor sync disabled)*/
    };
    uint8_t byte;
} ism330dlc_SENSOR_SYNC_TIME_FRAME_t;

/*SENSOR_SYNC_RES_RATIO*/
typedef union {
    struct {
        uint8_t uReserved : 6;
        uint8_t uSensor_Sync_Res_Ratio : 2;     /*Resolution ratio of error code for sensor synchronization.*/
    };
    uint8_t byte;
} ism330dlc_SENSOR_SYNC_RES_RATIO_t;

/*FIFO_CTRL_1*/
typedef union {
    struct {
        uint8_t uFifo_Threshold : 8;            /*FIFO threshold. Unsigned 8-bit. Default value: 0000 0000*/
    };
    uint8_t byte;
} ism330dlc_FIFO_CTRL_1_t;

/*FIFO_CTRL_2*/
typedef union {
    struct {
        uint8_t uFIFO_TIMER_EN : 1;             /*FIFO timer enable. 0: disabled, 1: enabled*/
        uint8_t uReserved: 3;
        uint8_t uFIFO_TEMP_EN : 1;              /*FIFO temperature enable. 0*/
        uint8_t uFifo_Threshold : 3;            /*FIFO threshold. Unsigned 8-bit. Default value: 0000 0000*/
    };
    uint8_t byte;
} ism330dlc_FIFO_CTRL_2_t;



#endif // ESP32_ISM330DLC_REGISTERS_H
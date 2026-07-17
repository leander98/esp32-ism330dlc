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

/*FIFO_CTRL_3*/
typedef union {
    struct {
        uint8_t uDec_FIFO_XL : 3;               /*Accelerometer FIFO data set decimation setting*/
        uint8_t uDec_FIFO_GYRO : 3;             /*Gyroscope FIFO data set decimation setting*/
        uint8_t uReserved : 2;
    };
    uint8_t byte;
} ism330dlc_FIFO_CTRL_3_t;

/*FIFO_CTRL_4*/
typedef union {
    struct {
        uint8_t uDec_DS3_FIFO : 3;              /*Third FIFO data set decimation setting*/
        uint8_t uDec_DS4_FIFO : 3;              /*Fourth FIFO data set decimation setting*/
        uint8_t uONLY_HIGH_DATA : 1;            /*8-bit data storage in FIFO*/
        uint8_t uSTOP_ON_FTH : 1;               /*FIFO threshold level use enable*/
    };
    uint8_t byte;
} ism330dlc_FIFO_CTRL_4_t;

/*FIFO_CTRL_5*/
typedef union {
    struct {
        uint8_t uFIFO_MODE : 3;                 /*FIFO mode selection bits*/
        uint8_t uODR_FIFO : 4;                  /*FIFO ODR selection*/
        uint8_t uReserved : 1;
    };
    uint8_t byte;
} ism330dlc_FIFO_CTRL_5_t;

/*DRDY_PULSE_CFG*/
typedef union {
    struct {
        uint8_t uReserved : 7;
        uint8_t uDRDY_PULSED : 1;               /*Enables pulsed data-ready mode*/
    };
    uint8_t byte;
} ism330dlc_DRDY_PULSE_CFG_t;

/*INT1_CTRL*/
typedef union {
    struct {
        uint8_t uINT1_DRDY_XL : 1;              /*Accelerometer data-ready on INT1*/
        uint8_t uINT1_DRDY_G : 1;               /*Gyroscope data-ready on INT1*/
        uint8_t uINT1_BOOT : 1;                 /*Boot status on INT1*/
        uint8_t uINT1_FTH : 1;                  /*FIFO threshold interrupt on INT1*/
        uint8_t uINT1_FIFO_OVR : 1;             /*FIFO overrun interrupt on INT1*/
        uint8_t uINT1_FULL_FLAG : 1;            /*FIFO full flag interrupt on INT1*/
        uint8_t uReserved : 2;
    };
    uint8_t byte;
} ism330dlc_INT1_CTRL_t;

/*INT2_CTRL*/
typedef union {
    struct {
        uint8_t uINT2_DRDY_XL : 1;              /*Accelerometer data-ready on INT2*/
        uint8_t uINT2_DRDY_G : 1;               /*Gyroscope data-ready on INT2*/
        uint8_t uINT2_DRDY_TEMP : 1;            /*Temperature data-ready on INT2*/
        uint8_t uINT2_FTH : 1;                  /*FIFO threshold interrupt on INT2*/
        uint8_t uINT2_FIFO_OVR : 1;             /*FIFO overrun interrupt on INT2*/
        uint8_t uINT2_FULL_FLAG : 1;            /*FIFO full flag interrupt on INT2*/
        uint8_t uReserved : 2;
    };
    uint8_t byte;
} ism330dlc_INT2_CTRL_t;

/*WHO_AM_I*/
typedef union {
    struct {
        uint8_t uWhoAmI : 8;                    /*Fixed device ID, expected value 0x6A*/
    };
    uint8_t byte;
} ism330dlc_WHO_AM_I_t;

/*CTRL1_XL*/
typedef union {
    struct {
        uint8_t uBW0_XL : 1;                    /*Accelerometer analog chain bandwidth selection*/
        uint8_t uLPF1_BW_SEL : 1;               /*Accelerometer LPF1 bandwidth selection*/
        uint8_t uFS_XL : 2;                     /*Accelerometer full-scale selection*/
        uint8_t uODR_XL : 4;                    /*Accelerometer output data rate selection*/
    };
    uint8_t byte;
} ism330dlc_CTRL1_XL_t;

/*CTRL2_G*/
typedef union {
    struct {
        uint8_t uReserved : 1;
        uint8_t uFS_125 : 1;                    /*Gyroscope full-scale at ±125 dps*/
        uint8_t uFS_G : 2;                      /*Gyroscope full-scale selection*/
        uint8_t uODR_G : 4;                     /*Gyroscope output data rate selection*/
    };
    uint8_t byte;
} ism330dlc_CTRL2_G_t;

/*CTRL3_C*/
typedef union {
    struct {
        uint8_t uSW_RESET : 1;                  /*Software reset*/
        uint8_t uBLE : 1;                       /*Big/little endian selection*/
        uint8_t uIF_INC : 1;                    /*Register address auto increment*/
        uint8_t uSIM : 1;                       /*SPI serial interface mode selection*/
        uint8_t uPP_OD : 1;                     /*Push-pull/open-drain selection*/
        uint8_t uH_LACTIVE : 1;                 /*Interrupt activation level*/
        uint8_t uBDU : 1;                       /*Block data update*/
        uint8_t uBOOT : 1;                      /*Reboot memory content*/
    };
    uint8_t byte;
} ism330dlc_CTRL3_C_t;

/*CTRL4_C*/
typedef union {
    struct {
        uint8_t uReserved : 1;
        uint8_t uLPF1_SEL_G : 1;                /*Enable gyroscope LPF1*/
        uint8_t uI2C_disable : 1;               /*Disable I²C interface*/
        uint8_t uDRDY_MASK : 1;                 /*Data available masking*/
        uint8_t uDEN_DRDY_INT1 : 1;             /*DEN DRDY signal on INT1*/
        uint8_t uINT2_on_INT1 : 1;              /*Enable all INT2 signals on INT1*/
        uint8_t uSLEEP : 1;                     /*Gyroscope sleep mode enable*/
        uint8_t uDEN_XL_EN : 1;                 /*Extend DEN functionality to accelerometer*/
    };
    uint8_t byte;
} ism330dlc_CTRL4_C_t;

/*CTRL5_C*/
typedef union {
    struct {
        uint8_t uST_XL : 2;                     /*Accelerometer self-test enable*/
        uint8_t uST_G : 2;                      /*Gyroscope self-test enable*/
        uint8_t uDEN_LH : 1;                    /*DEN active level configuration*/
        uint8_t uROUNDING : 3;                  /*Output register wraparound pattern*/
    };
    uint8_t byte;
} ism330dlc_CTRL5_C_t;

/*CTRL6_C*/
typedef union {
    struct {
        uint8_t uFTYPE : 2;                     /*Gyroscope LPF1 bandwidth selection*/
        uint8_t uReserved : 1;
        uint8_t uUSR_OFF_W : 1;                 /*Weight of accelerometer user offset bits*/
        uint8_t uXL_HM_MODE : 1;                /*Disable accelerometer high-performance mode*/
        uint8_t uLVL2_EN : 1;                   /*Enable DEN level-sensitive latched*/
        uint8_t uLVL1_EN : 1;                   /*Enable DEN level-sensitive trigger*/
        uint8_t uTRIG_EN : 1;                   /*Enable DEN edge-sensitive trigger*/
    };
    uint8_t byte;
} ism330dlc_CTRL6_C_t;

/*CTRL7_G*/
typedef union {
    struct {
        uint8_t uReserved0 : 1;
        uint8_t uReserved1 : 1;
        uint8_t uROUNDING_STATUS : 1;           /*Source register wraparound function*/
        uint8_t uReserved2 : 1;
        uint8_t uHPM_G : 2;                     /*Gyroscope HP filter cutoff selection*/
        uint8_t uHP_EN_G : 1;                   /*Enable gyroscope digital high-pass filter*/
        uint8_t uG_HM_MODE : 1;                 /*Disable gyroscope high-performance mode*/
    };
    uint8_t byte;
} ism330dlc_CTRL7_G_t;

/*CTRL8_XL*/
typedef union {
    struct {
        uint8_t uLOW_PASS_ON_6D : 1;            /*LPF2 on 6D function selection*/
        uint8_t uReserved : 1;
        uint8_t uHP_SLOPE_XL_EN : 1;            /*Slope/high-pass filter selection*/
        uint8_t uINPUT_COMPOSITE : 1;           /*Composite filter input selection*/
        uint8_t uHP_REF_MODE : 1;               /*Enable HP filter reference mode*/
        uint8_t uHPCF_XL : 2;                   /*Accelerometer LPF2 / HP filter config*/
        uint8_t uLPF2_XL_EN : 1;                /*Accelerometer LPF2 enable*/
    };
    uint8_t byte;
} ism330dlc_CTRL8_XL_t;

/*CTRL9_XL*/
typedef union {
    struct {
        uint8_t uReserved0 : 1;
        uint8_t uReserved1 : 1;
        uint8_t uSOFT_EN : 1;                   /*Enable soft-iron correction algorithm*/
        uint8_t uReserved2 : 1;
        uint8_t uDEN_XL_G : 1;                  /*DEN stamping sensor selection*/
        uint8_t uDEN_Z : 1;                     /*Store DEN in Z-axis LSB*/
        uint8_t uDEN_Y : 1;                     /*Store DEN in Y-axis LSB*/
        uint8_t uDEN_X : 1;                     /*Store DEN in X-axis LSB*/
    };
    uint8_t byte;
} ism330dlc_CTRL9_XL_t;

/*CTRL10_C*/
typedef union {
    struct {
        uint8_t uReserved0 : 1;
        uint8_t uReserved1 : 1;
        uint8_t uFUNC_EN : 1;                   /*Enable embedded functionalities*/
        uint8_t uTILT_EN : 1;                   /*Enable tilt calculation*/
        uint8_t uReserved2 : 1;
        uint8_t uTIMER_EN : 1;                  /*Enable timestamp count*/
        uint8_t uReserved3 : 1;
        uint8_t uReserved4 : 1;
    };
    uint8_t byte;
} ism330dlc_CTRL10_C_t;

/*MASTER_CONFIG*/
typedef union {
    struct {
        uint8_t uMASTER_ON : 1;                 /*Enable sensor hub I²C master*/
        uint8_t uIRON_EN : 1;                   /*Enable hard-iron correction algorithm*/
        uint8_t uPASS_THROUGH_MODE : 1;         /*I²C interface pass-through*/
        uint8_t uPULL_UP_EN : 1;                /*Auxiliary I²C pull-up*/
        uint8_t uSTART_CONFIG : 1;              /*Sensor hub trigger signal selection*/
        uint8_t uReserved : 1;
        uint8_t uDATA_VALID_SEL_FIFO : 1;       /*Selection of FIFO data-valid signal*/
        uint8_t uDRDY_ON_INT1 : 1;              /*Master DRDY signal on INT1*/
    };
    uint8_t byte;
} ism330dlc_MASTER_CONFIG_t;

/*WAKE_UP_SRC*/
typedef union {
    struct {
        uint8_t uZ_WU : 1;                      /*Wake-up event on Z-axis*/
        uint8_t uY_WU : 1;                      /*Wake-up event on Y-axis*/
        uint8_t uX_WU : 1;                      /*Wake-up event on X-axis*/
        uint8_t uWU_IA : 1;                     /*Wake-up event detected*/
        uint8_t uSLEEP_STATE_IA : 1;            /*Sleep event status*/
        uint8_t uFF_IA : 1;                     /*Free-fall event detected*/
        uint8_t uReserved : 2;
    };
    uint8_t byte;
} ism330dlc_WAKE_UP_SRC_t;

/*TAP_SRC*/
typedef union {
    struct {
        uint8_t uZ_TAP : 1;                     /*Tap event on Z-axis*/
        uint8_t uY_TAP : 1;                     /*Tap event on Y-axis*/
        uint8_t uX_TAP : 1;                     /*Tap event on X-axis*/
        uint8_t uTAP_SIGN : 1;                  /*Sign of acceleration detected by tap event*/
        uint8_t uDOUBLE_TAP : 1;                /*Double-tap event status*/
        uint8_t uSINGLE_TAP : 1;                /*Single-tap event status*/
        uint8_t uTAP_IA : 1;                    /*Tap event detected*/
        uint8_t uReserved : 1;
    };
    uint8_t byte;
} ism330dlc_TAP_SRC_t;

/*D6D_SRC*/
typedef union {
    struct {
        uint8_t uXL : 1;                        /*X-axis low event*/
        uint8_t uXH : 1;                        /*X-axis high event*/
        uint8_t uYL : 1;                        /*Y-axis low event*/
        uint8_t uYH : 1;                        /*Y-axis high event*/
        uint8_t uZL : 1;                        /*Z-axis low event*/
        uint8_t uZH : 1;                        /*Z-axis high event*/
        uint8_t uD6D_IA : 1;                    /*6D orientation interrupt active*/
        uint8_t uDEN_DRDY : 1;                  /*DEN data-ready signal*/
    };
    uint8_t byte;
} ism330dlc_D6D_SRC_t;

/*STATUS_REG*/
typedef union {
    struct {
        uint8_t uXLDA : 1;                      /*Accelerometer new data available*/
        uint8_t uGDA : 1;                       /*Gyroscope new data available*/
        uint8_t uTDA : 1;                       /*Temperature new data available*/
        uint8_t uReserved : 5;
    };
    uint8_t byte;
} ism330dlc_STATUS_REG_t;

/*Byte-wide output/status registers*/
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_OUT_TEMP_L_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_OUT_TEMP_H_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_OUTX_L_G_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_OUTX_H_G_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_OUTY_L_G_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_OUTY_H_G_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_OUTZ_L_G_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_OUTZ_H_G_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_OUTX_L_XL_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_OUTX_H_XL_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_OUTY_L_XL_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_OUTY_H_XL_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_OUTZ_L_XL_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_OUTZ_H_XL_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_SENSORHUB1_REG_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_SENSORHUB2_REG_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_SENSORHUB3_REG_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_SENSORHUB4_REG_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_SENSORHUB5_REG_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_SENSORHUB6_REG_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_SENSORHUB7_REG_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_SENSORHUB8_REG_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_SENSORHUB9_REG_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_SENSORHUB10_REG_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_SENSORHUB11_REG_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_SENSORHUB12_REG_t;

/*FIFO_STATUS1*/
typedef union {
    struct {
        uint8_t uDIFF_FIFO : 8;                 /*Unread FIFO words [7:0]*/
    };
    uint8_t byte;
} ism330dlc_FIFO_STATUS1_t;

/*FIFO_STATUS2*/
typedef union {
    struct {
        uint8_t uDIFF_FIFO_H : 3;               /*Unread FIFO words [10:8]*/
        uint8_t uReserved : 1;
        uint8_t uFIFO_EMPTY : 1;                /*FIFO empty status*/
        uint8_t uFIFO_FULL_SMART : 1;           /*Smart FIFO full status*/
        uint8_t uOVER_RUN : 1;                  /*FIFO overrun status*/
        uint8_t uWaterM : 1;                    /*FIFO watermark status*/
    };
    uint8_t byte;
} ism330dlc_FIFO_STATUS2_t;

/*FIFO_STATUS3*/
typedef union {
    struct {
        uint8_t uFIFO_PATTERN : 8;              /*FIFO pattern [7:0]*/
    };
    uint8_t byte;
} ism330dlc_FIFO_STATUS3_t;

/*FIFO_STATUS4*/
typedef union {
    struct {
        uint8_t uFIFO_PATTERN_H : 2;            /*FIFO pattern [9:8]*/
        uint8_t uReserved : 6;
    };
    uint8_t byte;
} ism330dlc_FIFO_STATUS4_t;

typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_FIFO_DATA_OUT_L_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_FIFO_DATA_OUT_H_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_TIMESTAMP0_REG_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_TIMESTAMP1_REG_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_TIMESTAMP2_REG_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_SENSORHUB13_REG_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_SENSORHUB14_REG_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_SENSORHUB15_REG_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_SENSORHUB16_REG_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_SENSORHUB17_REG_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_SENSORHUB18_REG_t;

/*FUNC_SRC1*/
typedef union {
    struct {
        uint8_t uSENSORHUB_END_OP : 1;          /*Sensor hub communication status*/
        uint8_t uSI_END_OP : 1;                 /*Hard/soft-iron calculation status*/
        uint8_t uHI_FAIL : 1;                   /*Hard/soft-iron algorithm fail*/
        uint8_t uReserved : 2;
        uint8_t uTILT_IA : 1;                   /*Tilt event detection status*/
        uint8_t uReserved2 : 2;
    };
    uint8_t byte;
} ism330dlc_FUNC_SRC1_t;

/*FUNC_SRC2*/
typedef union {
    struct {
        uint8_t uReserved : 3;
        uint8_t uSLAVE0_NACK : 1;               /*NACK on slave 0 communication*/
        uint8_t uSLAVE1_NACK : 1;               /*NACK on slave 1 communication*/
        uint8_t uSLAVE2_NACK : 1;               /*NACK on slave 2 communication*/
        uint8_t uSLAVE3_NACK : 1;               /*NACK on slave 3 communication*/
        uint8_t uReserved2 : 1;
    };
    uint8_t byte;
} ism330dlc_FUNC_SRC2_t;

/*TAP_CFG*/
typedef union {
    struct {
        uint8_t uLIR : 1;                       /*Latched interrupt*/
        uint8_t uTAP_Z_EN : 1;                  /*Enable Z direction in tap recognition*/
        uint8_t uTAP_Y_EN : 1;                  /*Enable Y direction in tap recognition*/
        uint8_t uTAP_X_EN : 1;                  /*Enable X direction in tap recognition*/
        uint8_t uSLOPE_FDS : 1;                 /*HPF or SLOPE filter selection*/
        uint8_t uINACT_EN : 2;                  /*Inactivity function enable*/
        uint8_t uINTERRUPTS_ENABLE : 1;         /*Enable basic interrupts*/
    };
    uint8_t byte;
} ism330dlc_TAP_CFG_t;

/*TAP_THS_6D*/
typedef union {
    struct {
        uint8_t uTAP_THS : 5;                   /*Threshold for tap recognition*/
        uint8_t uSIXD_THS : 2;                  /*Threshold for 4D/6D function*/
        uint8_t uD4D_EN : 1;                    /*4D orientation detection enable*/
    };
    uint8_t byte;
} ism330dlc_TAP_THS_6D_t;

/*INT_DUR2*/
typedef union {
    struct {
        uint8_t uSHOCK : 2;                     /*Maximum duration of overthreshold event*/
        uint8_t uQUIET : 2;                     /*Expected quiet time after tap detection*/
        uint8_t uDUR : 4;                       /*Maximum time gap for double-tap recognition*/
    };
    uint8_t byte;
} ism330dlc_INT_DUR2_t;

/*WAKE_UP_THS*/
typedef union {
    struct {
        uint8_t uWK_THS : 6;                    /*Threshold for wakeup*/
        uint8_t uReserved : 1;
        uint8_t uSINGLE_DOUBLE_TAP : 1;         /*Single/double-tap event enable*/
    };
    uint8_t byte;
} ism330dlc_WAKE_UP_THS_t;

/*WAKE_UP_DUR*/
typedef union {
    struct {
        uint8_t uSLEEP_DUR : 4;                 /*Duration to go in sleep mode*/
        uint8_t uTIMER_HR : 1;                  /*Timestamp resolution setting*/
        uint8_t uWAKE_DUR : 2;                  /*Wake up duration event*/
        uint8_t uFF_DUR5 : 1;                   /*Free-fall duration event MSb*/
    };
    uint8_t byte;
} ism330dlc_WAKE_UP_DUR_t;

/*FREE_FALL*/
typedef union {
    struct {
        uint8_t uFF_THS : 3;                    /*Free-fall threshold setting*/
        uint8_t uFF_DUR : 5;                    /*Free-fall duration event [4:0]*/
    };
    uint8_t byte;
} ism330dlc_FREE_FALL_t;

/*MD1_CFG*/
typedef union {
    struct {
        uint8_t uINT1_TIMER : 1;                /*Route timer end counter event to INT1*/
        uint8_t uINT1_TILT : 1;                 /*Route tilt event to INT1*/
        uint8_t uINT1_6D : 1;                   /*Route 6D event to INT1*/
        uint8_t uINT1_DOUBLE_TAP : 1;           /*Route double-tap event to INT1*/
        uint8_t uINT1_FF : 1;                   /*Route free-fall event to INT1*/
        uint8_t uINT1_WU : 1;                   /*Route wake-up event to INT1*/
        uint8_t uINT1_SINGLE_TAP : 1;           /*Route single-tap event to INT1*/
        uint8_t uINT1_INACT_STATE : 1;          /*Route inactivity state to INT1*/
    };
    uint8_t byte;
} ism330dlc_MD1_CFG_t;

/*MD2_CFG*/
typedef union {
    struct {
        uint8_t uINT2_IRON : 1;                 /*Route hard/soft-iron event to INT2*/
        uint8_t uINT2_TILT : 1;                 /*Route tilt event to INT2*/
        uint8_t uINT2_6D : 1;                   /*Route 6D event to INT2*/
        uint8_t uINT2_DOUBLE_TAP : 1;           /*Route double-tap event to INT2*/
        uint8_t uINT2_FF : 1;                   /*Route free-fall event to INT2*/
        uint8_t uINT2_WU : 1;                   /*Route wake-up event to INT2*/
        uint8_t uINT2_SINGLE_TAP : 1;           /*Route single-tap event to INT2*/
        uint8_t uINT2_INACT_STATE : 1;          /*Route inactivity state to INT2*/
    };
    uint8_t byte;
} ism330dlc_MD2_CFG_t;

typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_MASTER_CMD_CODE_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_SENS_SYNC_SPI_ERROR_CODE_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_OUT_MAG_RAW_X_L_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_OUT_MAG_RAW_X_H_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_OUT_MAG_RAW_Y_L_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_OUT_MAG_RAW_Y_H_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_OUT_MAG_RAW_Z_L_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_OUT_MAG_RAW_Z_H_t;

/*INT_OIS*/
typedef union {
    struct {
        uint8_t uReserved : 6;
        uint8_t uLVL2_OIS : 1;                  /*Level-sensitive latched mode on OIS chain*/
        uint8_t uINT2_DRDY_OIS : 1;             /*Enable OIS chain DRDY on INT2*/
    };
    uint8_t byte;
} ism330dlc_INT_OIS_t;

/*CTRL1_OIS*/
typedef union {
    struct {
        uint8_t uOIS_EN_SPI2 : 1;               /*Enable OIS chain data processing*/
        uint8_t uFS_125_OIS : 1;                /*Select OIS gyroscope ±125 dps full scale*/
        uint8_t uFS_G_OIS : 2;                  /*OIS gyroscope full-scale selection*/
        uint8_t uMODE4_EN : 1;                  /*Enable accelerometer OIS chain*/
        uint8_t uSIM_OIS : 1;                   /*SPI2 3- or 4-wire mode*/
        uint8_t uLVL1_OIS : 1;                  /*Level-sensitive trigger mode on OIS chain*/
        uint8_t uBLE_OIS : 1;                   /*OIS endian data selection*/
    };
    uint8_t byte;
} ism330dlc_CTRL1_OIS_t;

/*CTRL2_OIS*/
typedef union {
    struct {
        uint8_t uHP_EN_OIS : 1;                 /*Enable OIS gyroscope HPF*/
        uint8_t uFTYPE_OIS : 2;                 /*OIS gyroscope LPF1 bandwidth selection*/
        uint8_t uReserved0 : 1;
        uint8_t uHPM_OIS : 2;                   /*OIS gyroscope HPF cutoff selection*/
        uint8_t uReserved1 : 2;
    };
    uint8_t byte;
} ism330dlc_CTRL2_OIS_t;

/*CTRL3_OIS*/
typedef union {
    struct {
        uint8_t uST_OIS_CLAMPDIS : 1;           /*Disable OIS gyroscope clamp*/
        uint8_t uST_OIS : 2;                    /*OIS gyroscope self-test selection*/
        uint8_t uFILTER_XL_CONF_OIS : 2;        /*OIS accelerometer bandwidth selection*/
        uint8_t uFS_XL_OIS : 2;                 /*OIS accelerometer full-scale selection*/
        uint8_t uDEN_LH_OIS : 1;                /*DEN polarity on OIS chain*/
    };
    uint8_t byte;
} ism330dlc_CTRL3_OIS_t;

typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_X_OFS_USR_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_Y_OFS_USR_t;
typedef union { struct { uint8_t uData : 8; }; uint8_t byte; } ism330dlc_Z_OFS_USR_t;



#endif // ESP32_ISM330DLC_REGISTERS_H
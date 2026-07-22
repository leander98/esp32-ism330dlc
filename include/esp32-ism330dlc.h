#ifndef ESP32_ISM330DLC_H
#define ESP32_ISM330DLC_H

#include <esp_err.h>
#include <stddef.h>
#include <stdint.h>

#include "esp32-ism330dlc_registers.h"

#define TAG "esp32-ism330dlc"

typedef esp_err_t (*esp32_ism330dlc_read_fn)(void *context, uint8_t reg,
                                             uint8_t *data, size_t length);
typedef esp_err_t (*esp32_ism330dlc_write_fn)(void *context, uint8_t reg,
                                              const uint8_t *data, size_t length);

typedef enum {
    ISM330DLC_ODR_POWER_DOWN = 0x0,
    ISM330DLC_ODR_12_5_HZ = 0x1,
    ISM330DLC_ODR_26_HZ = 0x2,
    ISM330DLC_ODR_52_HZ = 0x3,
    ISM330DLC_ODR_104_HZ = 0x4,
    ISM330DLC_ODR_208_HZ = 0x5,
    ISM330DLC_ODR_416_HZ = 0x6,
    ISM330DLC_ODR_833_HZ = 0x7,
    ISM330DLC_ODR_1660_HZ = 0x8,
    ISM330DLC_ODR_3330_HZ = 0x9,
    ISM330DLC_ODR_6660_HZ = 0xA,
} esp32_ism330dlc_odr_t;

typedef enum {
    ISM330DLC_ACCEL_FS_2G = 0x0,
    ISM330DLC_ACCEL_FS_16G = 0x1,
    ISM330DLC_ACCEL_FS_4G = 0x2,
    ISM330DLC_ACCEL_FS_8G = 0x3,
} esp32_ism330dlc_accel_fs_t;

typedef enum {
    ISM330DLC_GYRO_FS_250_DPS = 0x0,
    ISM330DLC_GYRO_FS_500_DPS = 0x1,
    ISM330DLC_GYRO_FS_1000_DPS = 0x2,
    ISM330DLC_GYRO_FS_2000_DPS = 0x3,
} esp32_ism330dlc_gyro_fs_t;

typedef struct esp32_ism330dlc {
    esp32_ism330dlc_registers registers;    /*Register instance of device*/
    esp32_ism330dlc_read_fn read;
    esp32_ism330dlc_write_fn write;
    void *context;
    esp32_ism330dlc_odr_t accel_odr;
    esp32_ism330dlc_odr_t gyro_odr;
    esp32_ism330dlc_accel_fs_t accel_full_scale;
    esp32_ism330dlc_gyro_fs_t gyro_full_scale;
} esp32_ism330dlc_t;

#define ESP32_ISM330DLC_DEFAULT_CONFIG(read_cb, write_cb, bus_context) \
    { .read = (read_cb), .write = (write_cb), .context = (bus_context), \
      .accel_odr = ISM330DLC_ODR_416_HZ, .gyro_odr = ISM330DLC_ODR_416_HZ, \
      .accel_full_scale = ISM330DLC_ACCEL_FS_4G, \
      .gyro_full_scale = ISM330DLC_GYRO_FS_2000_DPS }

esp_err_t esp32_ism330dlc_init(esp32_ism330dlc_t *dev);

#endif // ESP32_ISM330DLC_H

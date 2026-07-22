#ifndef ESP32_ISM330DLC_H
#define ESP32_ISM330DLC_H

#include <esp_err.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "esp32-ism330dlc_registers.h"

#define TAG "esp32-ism330dlc"

/* Set to 1 at compile time to use vTaskDelay(), or 0 to use the ROM delay. */
#ifndef ESP32_ISM330DLC_USE_FREERTOS_DELAY
#ifdef CONFIG_ESP32_ISM330DLC_USE_FREERTOS_DELAY
#define ESP32_ISM330DLC_USE_FREERTOS_DELAY 1
#else
#define ESP32_ISM330DLC_USE_FREERTOS_DELAY 0
#endif
#endif

/**
 * @brief Read one or more consecutive ISM330DLC registers.
 *
 * @param context User-provided bus context.
 * @param reg First register address to read.
 * @param data Destination buffer.
 * @param length Number of bytes to read.
 * @return ESP_OK on success, otherwise an ESP-IDF error code.
 */
typedef esp_err_t (*esp32_ism330dlc_read_fn)(void *context, uint8_t reg,
                                             uint8_t *data, size_t length);

/**
 * @brief Write one or more consecutive ISM330DLC registers.
 *
 * @param context User-provided bus context.
 * @param reg First register address to write.
 * @param data Source buffer.
 * @param length Number of bytes to write.
 * @return ESP_OK on success, otherwise an ESP-IDF error code.
 */
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

typedef enum {
    ISM330DLC_INTERRUPT_ACTIVE_HIGH = 0,
    ISM330DLC_INTERRUPT_ACTIVE_LOW,
} esp32_ism330dlc_interrupt_polarity_t;

typedef enum {
    ISM330DLC_INTERRUPT_PUSH_PULL = 0,
    ISM330DLC_INTERRUPT_OPEN_DRAIN,
} esp32_ism330dlc_interrupt_output_t;

typedef enum {
    ISM330DLC_DATA_READY_LATCHED = 0,
    ISM330DLC_DATA_READY_PULSED,
} esp32_ism330dlc_data_ready_mode_t;

typedef struct {
    bool accelerometer_data_ready;
    bool gyroscope_data_ready;
    bool boot_complete;
    bool fifo_threshold;
    bool fifo_overrun;
    bool fifo_full;
    bool timer;
    bool tilt;
    bool orientation_6d;
    bool double_tap;
    bool free_fall;
    bool wake_up;
    bool single_tap;
    bool inactivity;
} esp32_ism330dlc_int1_route_t;

typedef struct {
    bool accelerometer_data_ready;
    bool gyroscope_data_ready;
    bool temperature_data_ready;
    bool fifo_threshold;
    bool fifo_overrun;
    bool fifo_full;
    bool iron_correction;
    bool tilt;
    bool orientation_6d;
    bool double_tap;
    bool free_fall;
    bool wake_up;
    bool single_tap;
    bool inactivity;
} esp32_ism330dlc_int2_route_t;

typedef struct {
    esp32_ism330dlc_interrupt_polarity_t polarity;
    esp32_ism330dlc_interrupt_output_t output_type;
    esp32_ism330dlc_data_ready_mode_t data_ready_mode;
    bool mask_data_ready_until_filters_settle;
    bool route_int2_signals_to_int1;
    esp32_ism330dlc_int1_route_t int1;
    esp32_ism330dlc_int2_route_t int2;
} esp32_ism330dlc_interrupt_config_t;

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} esp32_ism330dlc_raw_vector_t;

typedef struct {
    esp32_ism330dlc_raw_vector_t acceleration;
    esp32_ism330dlc_raw_vector_t angular_rate;
    int16_t temperature;
} esp32_ism330dlc_raw_sample_t;

typedef struct {
    float x;
    float y;
    float z;
} esp32_ism330dlc_vector_t;

typedef struct {
    esp32_ism330dlc_vector_t acceleration_g;
    esp32_ism330dlc_vector_t angular_rate_dps;
    float temperature_c;
} esp32_ism330dlc_sample_t;

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

/**
 * @brief Initialize and configure the ISM330DLC accelerometer and gyroscope.
 *
 * Verifies the device identity, performs a software reset, enables block data
 * update and register auto-increment, and applies the configured output data
 * rates and full-scale ranges.
 *
 * @param dev Device instance with transport callbacks and settings populated.
 * @return ESP_OK on success, ESP_ERR_NOT_FOUND for an unexpected device ID,
 *         ESP_ERR_TIMEOUT if reset does not complete, or another ESP-IDF error.
 */
esp_err_t esp32_ism330dlc_init(esp32_ism330dlc_t *dev);

/**
 * @brief Configure the electrical behavior and event routing of INT1 and INT2.
 *
 * Shared control registers are updated without changing unrelated settings.
 * Event generators such as tap, wake-up, and free-fall must be configured
 * separately before their routed interrupts can occur.
 *
 * @param dev Initialized device instance.
 * @param config Interrupt pin and routing configuration.
 * @return ESP_OK on success, ESP_ERR_INVALID_ARG for invalid arguments, or a
 *         transport error returned by the read/write callbacks.
 */
esp_err_t esp32_ism330dlc_configure_interrupts(
    esp32_ism330dlc_t *dev,
    const esp32_ism330dlc_interrupt_config_t *config);

/**
 * @brief Read one raw temperature, gyroscope, and accelerometer sample.
 *
 * The output registers are read in a single transaction. Register
 * auto-increment must be enabled, as it is by esp32_ism330dlc_init().
 *
 * @param dev Initialized device instance.
 * @param sample Destination for the signed raw sensor values.
 * @return ESP_OK on success, ESP_ERR_INVALID_ARG for invalid arguments, or a
 *         transport error returned by the read callback.
 */
esp_err_t esp32_ism330dlc_read_raw(esp32_ism330dlc_t *dev,
                                  esp32_ism330dlc_raw_sample_t *sample);

/**
 * @brief Read and convert one temperature, gyroscope, and accelerometer sample.
 *
 * Acceleration is returned in g, angular rate in degrees per second, and
 * temperature in degrees Celsius.
 *
 * @param dev Initialized device instance.
 * @param sample Destination for the converted sensor values.
 * @return ESP_OK on success, ESP_ERR_INVALID_ARG for invalid arguments, or a
 *         transport error returned by the read callback.
 */
esp_err_t esp32_ism330dlc_read(esp32_ism330dlc_t *dev,
                              esp32_ism330dlc_sample_t *sample);

#endif // ESP32_ISM330DLC_H

/**
 * @file example.c
 * @brief I2C example for initializing and periodically reading an ISM330DLC.
 *
 * Adapt the GPIO assignments and I2C address below to match the board wiring.
 * The address is 0x6A when SDO/SA0 is low and 0x6B when SDO/SA0 is high.
 */

#include <driver/gpio.h>
#include <driver/i2c_master.h>
#include <esp_err.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "esp32-ism330dlc.h"

#define IMU_I2C_PORT       I2C_NUM_0
#define IMU_I2C_SDA_GPIO   GPIO_NUM_8
#define IMU_I2C_SCL_GPIO   GPIO_NUM_9
#define IMU_I2C_FREQUENCY  400000U
#define IMU_I2C_ADDRESS    0x6AU
#define IMU_SAMPLE_PERIOD  pdMS_TO_TICKS(1000U)

static const char *APP_TAG = "flight-controller";

/**
 * @brief Create the I2C bus and initialize an ISM330DLC device.
 *
 * The I2C device handle is stored as the driver's transport context. ESP-IDF
 * owns the bus and device objects after they are created, so their handles
 * remain valid after this function returns.
 *
 * @param[out] imu Destination for the initialized driver instance.
 * @return ESP_OK on success, otherwise an ESP-IDF bus or sensor error.
 */
static esp_err_t initialize_imu(esp32_ism330dlc_t *imu)
{
    i2c_master_bus_handle_t bus;
    i2c_master_dev_handle_t device;

    /* Internal pull-ups are convenient for testing; external pull-ups are
     * recommended for reliable operation, especially at 400 kHz. */
    const i2c_master_bus_config_t bus_config = {
        .i2c_port = IMU_I2C_PORT,
        .sda_io_num = IMU_I2C_SDA_GPIO,
        .scl_io_num = IMU_I2C_SCL_GPIO,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };
    esp_err_t err = i2c_new_master_bus(&bus_config, &bus);
    if (err != ESP_OK) {
        ESP_LOGE(APP_TAG, "Failed to initialize I2C bus: %s",
                 esp_err_to_name(err));
        return err;
    }

    /* Register the sensor on the bus using its unshifted 7-bit address. */
    const i2c_device_config_t device_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = IMU_I2C_ADDRESS,
        .scl_speed_hz = IMU_I2C_FREQUENCY,
    };
    err = i2c_master_bus_add_device(bus, &device_config, &device);
    if (err != ESP_OK) {
        ESP_LOGE(APP_TAG, "Failed to add ISM330DLC to I2C bus: %s",
                 esp_err_to_name(err));
        return err;
    }

    /* Pair the component-provided I2C callbacks with this device handle. */
    *imu = (esp32_ism330dlc_t)ESP32_ISM330DLC_DEFAULT_CONFIG(
        esp32_ism330dlc_i2c_read, esp32_ism330dlc_i2c_write, device);

    /* Verify WHO_AM_I, reset the sensor, and apply the default configuration. */
    return esp32_ism330dlc_init(imu);
}

/**
 * @brief Application entry point.
 *
 * Initializes the sensor once, then reads converted acceleration, angular
 * rate, and temperature values at the configured sample period.
 */
void app_main(void)
{
    esp32_ism330dlc_t imu;
    esp_err_t err = initialize_imu(&imu);
    if (err != ESP_OK) {
        ESP_LOGE(APP_TAG, "ISM330DLC initialization failed: %s",
                 esp_err_to_name(err));
        return;
    }

    while (true) {
        esp32_ism330dlc_sample_t sample;

        /* esp32_ism330dlc_read() returns values in g, dps, and degrees Celsius. */
        err = esp32_ism330dlc_read(&imu, &sample);
        if (err == ESP_OK) {
            ESP_LOGI(APP_TAG,
                     "accel [g]: %.3f, %.3f, %.3f | "
                     "gyro [dps]: %.3f, %.3f, %.3f | temp: %.2f C",
                     sample.acceleration_g.x,
                     sample.acceleration_g.y,
                     sample.acceleration_g.z,
                     sample.angular_rate_dps.x,
                     sample.angular_rate_dps.y,
                     sample.angular_rate_dps.z,
                     sample.temperature_c);
        } else {
            ESP_LOGE(APP_TAG, "Failed to read ISM330DLC: %s",
                     esp_err_to_name(err));
        }

        vTaskDelay(IMU_SAMPLE_PERIOD);
    }
}

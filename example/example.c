/*
 * Typical transport setup for the esp32-ism330dlc component.
 *
 * These examples use the ESP-IDF I2C master and SPI master drivers. Bus and
 * device creation is application-specific; pass the resulting device handle
 * as the driver's context as shown at the bottom of this file. The component
 * provides the I2C and SPI transport callbacks.
 */

#include <driver/i2c_master.h>
#include <driver/spi_master.h>
#include <esp_err.h>

#include "esp32-ism330dlc.h"

#define ISM330DLC_I2C_ADDRESS_SDO_LOW  0x6AU
#define ISM330DLC_I2C_ADDRESS_SDO_HIGH 0x6BU

/**
 * @brief Add the ISM330DLC to an initialized ESP-IDF I2C master bus.
 *
 * The sensor uses 7-bit address 0x6A when SDO/SA0 is low and 0x6B when it is
 * high. The address passed to ESP-IDF is not shifted and does not include the
 * I2C read/write bit.
 *
 * @param bus Initialized I2C master bus.
 * @param sdo_high True when the sensor SDO/SA0 pin is high, false when low.
 * @param device Destination for the created I2C device handle.
 * @return ESP_OK on success, otherwise an ESP-IDF I2C error.
 */
static esp_err_t example_ism330dlc_add_i2c_device(
    i2c_master_bus_handle_t bus,
    bool sdo_high,
    i2c_master_dev_handle_t *device)
{
    if (bus == NULL || device == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    const i2c_device_config_t config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = sdo_high ? ISM330DLC_I2C_ADDRESS_SDO_HIGH
                                   : ISM330DLC_I2C_ADDRESS_SDO_LOW,
        .scl_speed_hz = 400000,
    };

    return i2c_master_bus_add_device(bus, &config, device);
}

/**
 * @brief Construct an ISM330DLC instance backed by an ESP-IDF I2C device.
 *
 * @param i2c_device Initialized ESP-IDF I2C device handle.
 * @return Device instance configured with the component I2C read callback.
 */
static esp32_ism330dlc_t example_ism330dlc_over_i2c(
    i2c_master_dev_handle_t i2c_device)
{
    esp32_ism330dlc_t imu = ESP32_ISM330DLC_DEFAULT_CONFIG(
        esp32_ism330dlc_i2c_read, esp32_ism330dlc_i2c_write, i2c_device);
    return imu;
}

/**
 * @brief Construct an ISM330DLC instance backed by an ESP-IDF SPI device.
 *
 * @param spi_device Initialized ESP-IDF SPI device handle.
 * @return Device instance configured with the component SPI read callback.
 */
static esp32_ism330dlc_t example_ism330dlc_over_spi(
    spi_device_handle_t spi_device)
{
    esp32_ism330dlc_t imu = ESP32_ISM330DLC_DEFAULT_CONFIG(
        esp32_ism330dlc_spi_read, esp32_ism330dlc_spi_write, spi_device);
    return imu;
}

#include <stdio.h>
#include <string.h>

#include <esp_err.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "esp32-ism330dlc.h"
#include "esp32-ism330dlc_registers.h"

/*  @brief:     Zero-initialize the ISM330DLC registers
    @param      registers: Pointer to the registers structure
    @return:    ESP_OK if successful, otherwise an error code
*/
static esp_err_t esp32_ism330dlc_registers_zero_init(esp32_ism330dlc_registers *registers)
{
    if (registers == NULL) {
        ESP_LOGE(TAG, "Registers structure pointer is NULL.");
        return ESP_ERR_INVALID_ARG;
    }

    memset(registers, 0, sizeof(*registers));
    return ESP_OK;
}

static esp_err_t ism330dlc_read_register(esp32_ism330dlc_t *dev, uint8_t reg,
                                        uint8_t *value)
{
    esp_err_t err = dev->read(dev->context, reg, value, 1);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to read register 0x%02x: %s", reg, esp_err_to_name(err));
    }
    return err;
}

static esp_err_t ism330dlc_write_register(esp32_ism330dlc_t *dev, uint8_t reg,
                                         uint8_t value)
{
    esp_err_t err = dev->write(dev->context, reg, &value, 1);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to write register 0x%02x: %s", reg, esp_err_to_name(err));
    }
    return err;
}

/*  @brief:     Initialize the ISM330DLC sensor 
    @param      dev: Pointer to the ISM330DLC device structure
    @return:    ESP_OK if successful, otherwise an error code
*/
esp_err_t esp32_ism330dlc_init(esp32_ism330dlc_t *dev)
{
    esp32_ism330dlc_registers registers;
    esp_err_t err;
    uint8_t value;

    ESP_LOGI(TAG, "Initializing ISM330DLC sensor...");

    if (dev == NULL || dev->read == NULL || dev->write == NULL) {
        ESP_LOGE(TAG, "Device and transport callbacks must be provided.");
        return ESP_ERR_INVALID_ARG;
    }

    if (dev->accel_odr > ISM330DLC_ODR_6660_HZ ||
        dev->gyro_odr > ISM330DLC_ODR_6660_HZ ||
        dev->accel_full_scale > ISM330DLC_ACCEL_FS_8G ||
        dev->gyro_full_scale > ISM330DLC_GYRO_FS_2000_DPS) {
        return ESP_ERR_INVALID_ARG;
    }

    err = esp32_ism330dlc_registers_zero_init(&registers);
    if (err != ESP_OK) {
        return err;
    }
    dev->registers = registers;

    err = ism330dlc_read_register(dev, WHO_AM_I, &value);
    if (err != ESP_OK) {
        return err;
    }
    dev->registers.sDeviceID.uWHO_AM_I.byte = value;
    if (value != ISM330DLC_WHO_AM_I_VALUE) {
        ESP_LOGE(TAG, "Unexpected WHO_AM_I value 0x%02x (expected 0x%02x)",
                 value, ISM330DLC_WHO_AM_I_VALUE);
        return ESP_ERR_NOT_FOUND;
    }

    /* Reset first, then wait for SW_RESET to clear. */
    err = ism330dlc_write_register(dev, CTRL3_C, 0x01);
    if (err != ESP_OK) {
        return err;
    }
    for (unsigned int attempt = 0; attempt < 20; ++attempt) {
        vTaskDelay(pdMS_TO_TICKS(1));
        err = ism330dlc_read_register(dev, CTRL3_C, &value);
        if (err != ESP_OK) {
            return err;
        }
        if ((value & 0x01U) == 0) {
            break;
        }
        if (attempt == 19) {
            ESP_LOGE(TAG, "Timed out waiting for software reset");
            return ESP_ERR_TIMEOUT;
        }
    }

    /* BDU prevents torn samples; IF_INC enables multi-byte output reads. */
    dev->registers.sConfig.uCTRL3_C.byte = 0x44;
    dev->registers.sConfig.uCTRL1_XL.byte =
        ((uint8_t)dev->accel_odr << 4) | ((uint8_t)dev->accel_full_scale << 2);
    dev->registers.sConfig.uCTRL2_G.byte =
        ((uint8_t)dev->gyro_odr << 4) | ((uint8_t)dev->gyro_full_scale << 2);

    err = ism330dlc_write_register(dev, CTRL3_C, dev->registers.sConfig.uCTRL3_C.byte);
    if (err != ESP_OK) {
        return err;
    }
    err = ism330dlc_write_register(dev, CTRL1_XL, dev->registers.sConfig.uCTRL1_XL.byte);
    if (err != ESP_OK) {
        return err;
    }
    err = ism330dlc_write_register(dev, CTRL2_G, dev->registers.sConfig.uCTRL2_G.byte);
    if (err != ESP_OK) {
        return err;
    }



    ESP_LOGI(TAG, "ISM330DLC sensor initialized successfully.");

    return ESP_OK;
}

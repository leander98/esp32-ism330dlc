#include <stdio.h>
#include <string.h>

#include <esp_err.h>
#include <esp_log.h>

#include "esp32-ism330dlc.h"
#include "esp32-ism330dlc_registers.h"

#if ESP32_ISM330DLC_USE_FREERTOS_DELAY == 1
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#elif ESP32_ISM330DLC_USE_FREERTOS_DELAY == 0
#include <esp_rom_sys.h>
#else
#error "ESP32_ISM330DLC_USE_FREERTOS_DELAY must be 0 or 1"
#endif

/**
 * @brief Delay execution using the delay backend selected at compile time.
 *
 * @param milliseconds Delay duration in milliseconds.
 */
static void ism330dlc_delay_ms(uint32_t milliseconds)
{
#if ESP32_ISM330DLC_USE_FREERTOS_DELAY == 1
    vTaskDelay(pdMS_TO_TICKS(milliseconds));
#else
    esp_rom_delay_us(milliseconds * 1000U);
#endif
}

/**
 * @brief Zero-initialize the local ISM330DLC register shadow.
 *
 * @param registers Register shadow to initialize.
 * @return ESP_OK on success or ESP_ERR_INVALID_ARG for a NULL pointer.
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

/**
 * @brief Read a single device register through the configured transport.
 *
 * @param dev Device instance.
 * @param reg Register address.
 * @param value Destination for the register value.
 * @return ESP_OK on success, otherwise the transport error.
 */
static esp_err_t ism330dlc_read_register(esp32_ism330dlc_t *dev, uint8_t reg,
                                        uint8_t *value)
{
    esp_err_t err = dev->read(dev->context, reg, value, 1);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to read register 0x%02x: %s", reg, esp_err_to_name(err));
    }
    return err;
}

/**
 * @brief Write a single device register through the configured transport.
 *
 * @param dev Device instance.
 * @param reg Register address.
 * @param value Register value to write.
 * @return ESP_OK on success, otherwise the transport error.
 */
static esp_err_t ism330dlc_write_register(esp32_ism330dlc_t *dev, uint8_t reg,
                                         uint8_t value)
{
    esp_err_t err = dev->write(dev->context, reg, &value, 1);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to write register 0x%02x: %s", reg, esp_err_to_name(err));
    }
    return err;
}

/**
 * @brief Apply interrupt pin electrical settings and source routing.
 *
 * @param dev Device instance.
 * @param config Interrupt configuration to apply.
 * @return ESP_OK on success, otherwise an argument or transport error.
 */
esp_err_t esp32_ism330dlc_configure_interrupts(
    esp32_ism330dlc_t *dev,
    const esp32_ism330dlc_interrupt_config_t *config)
{
    esp_err_t err;
    uint8_t ctrl3;
    uint8_t ctrl4;
    uint8_t drdy_pulse;
    uint8_t int1_ctrl;
    uint8_t int2_ctrl;
    uint8_t md1_cfg;
    uint8_t md2_cfg;

    if (dev == NULL || config == NULL || dev->read == NULL || dev->write == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    if (config->polarity > ISM330DLC_INTERRUPT_ACTIVE_LOW ||
        config->output_type > ISM330DLC_INTERRUPT_OPEN_DRAIN ||
        config->data_ready_mode > ISM330DLC_DATA_READY_PULSED) {
        return ESP_ERR_INVALID_ARG;
    }

    err = ism330dlc_read_register(dev, CTRL3_C, &ctrl3);
    if (err != ESP_OK) {
        return err;
    }
    err = ism330dlc_read_register(dev, CTRL4_C, &ctrl4);
    if (err != ESP_OK) {
        return err;
    }

    ctrl3 &= (uint8_t)~(0x20U | 0x10U); /* H_LACTIVE and PP_OD. */
    if (config->polarity == ISM330DLC_INTERRUPT_ACTIVE_LOW) {
        ctrl3 |= 0x20U;
    }
    if (config->output_type == ISM330DLC_INTERRUPT_OPEN_DRAIN) {
        ctrl3 |= 0x10U;
    }

    ctrl4 &= (uint8_t)~(0x20U | 0x08U); /* DRDY_MASK and INT2_on_INT1. */
    if (config->mask_data_ready_until_filters_settle) {
        ctrl4 |= 0x08U;
    }
    if (config->route_int2_signals_to_int1) {
        ctrl4 |= 0x20U;
    }

    drdy_pulse = config->data_ready_mode == ISM330DLC_DATA_READY_PULSED ? 0x80U : 0x00U;

    int1_ctrl = (config->int1.accelerometer_data_ready ? 0x01U : 0U) |
                (config->int1.gyroscope_data_ready ? 0x02U : 0U) |
                (config->int1.boot_complete ? 0x04U : 0U) |
                (config->int1.fifo_threshold ? 0x08U : 0U) |
                (config->int1.fifo_overrun ? 0x10U : 0U) |
                (config->int1.fifo_full ? 0x20U : 0U);
    int2_ctrl = (config->int2.accelerometer_data_ready ? 0x01U : 0U) |
                (config->int2.gyroscope_data_ready ? 0x02U : 0U) |
                (config->int2.temperature_data_ready ? 0x04U : 0U) |
                (config->int2.fifo_threshold ? 0x08U : 0U) |
                (config->int2.fifo_overrun ? 0x10U : 0U) |
                (config->int2.fifo_full ? 0x20U : 0U);

    md1_cfg = (config->int1.timer ? 0x01U : 0U) |
              (config->int1.tilt ? 0x02U : 0U) |
              (config->int1.orientation_6d ? 0x04U : 0U) |
              (config->int1.double_tap ? 0x08U : 0U) |
              (config->int1.free_fall ? 0x10U : 0U) |
              (config->int1.wake_up ? 0x20U : 0U) |
              (config->int1.single_tap ? 0x40U : 0U) |
              (config->int1.inactivity ? 0x80U : 0U);
    md2_cfg = (config->int2.iron_correction ? 0x01U : 0U) |
              (config->int2.tilt ? 0x02U : 0U) |
              (config->int2.orientation_6d ? 0x04U : 0U) |
              (config->int2.double_tap ? 0x08U : 0U) |
              (config->int2.free_fall ? 0x10U : 0U) |
              (config->int2.wake_up ? 0x20U : 0U) |
              (config->int2.single_tap ? 0x40U : 0U) |
              (config->int2.inactivity ? 0x80U : 0U);

    const struct {
        uint8_t address;
        uint8_t value;
    } writes[] = {
        { CTRL3_C, ctrl3 }, { CTRL4_C, ctrl4 }, { DRDY_PULSE_CFG, drdy_pulse },
        { INT1_CTRL, int1_ctrl }, { INT2_CTRL, int2_ctrl },
        { MD1_CFG, md1_cfg }, { MD2_CFG, md2_cfg },
    };

    for (size_t i = 0; i < sizeof(writes) / sizeof(writes[0]); ++i) {
        err = ism330dlc_write_register(dev, writes[i].address, writes[i].value);
        if (err != ESP_OK) {
            return err;
        }
    }

    dev->registers.sConfig.uCTRL3_C.byte = ctrl3;
    dev->registers.sConfig.uCTRL4_C.byte = ctrl4;
    dev->registers.sInterruptRouting.uDRDY_PULSE_CFG.byte = drdy_pulse;
    dev->registers.sInterruptRouting.uINT1_CTRL.byte = int1_ctrl;
    dev->registers.sInterruptRouting.uINT2_CTRL.byte = int2_ctrl;
    dev->registers.sInterruptConfig.uMD1_CFG.byte = md1_cfg;
    dev->registers.sInterruptConfig.uMD2_CFG.byte = md2_cfg;

    return ESP_OK;
}

/**
 * @brief Initialize the ISM330DLC sensor.
 *
 * @param dev Device instance with transport callbacks and settings populated.
 * @return ESP_OK on success, otherwise an argument, transport, identity, or
 *         reset-timeout error.
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
        ism330dlc_delay_ms(1);
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

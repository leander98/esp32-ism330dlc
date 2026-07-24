#include <stdio.h>
#include <string.h>

#include <esp_err.h>
#include <esp_log.h>
#include <driver/i2c_master.h>
#include <driver/spi_master.h>

#include "esp32-ism330dlc.h"
#include "esp32-ism330dlc_registers.h"

#define ISM330DLC_SPI_READ_BIT     0x80U
#define ISM330DLC_SPI_ADDRESS_MASK 0x7FU

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
 * @brief Read ISM330DLC registers using an ESP-IDF I2C device handle.
 *
 * @param context Initialized i2c_master_dev_handle_t cast to void *.
 * @param reg First register address to read.
 * @param data Destination buffer.
 * @param length Number of consecutive bytes to read.
 * @return ESP_OK on success, otherwise an ESP-IDF I2C error.
 */
esp_err_t esp32_ism330dlc_i2c_read(void *context, uint8_t reg,
                                   uint8_t *data, size_t length)
{
    i2c_master_dev_handle_t device = (i2c_master_dev_handle_t)context;

    if (device == NULL || data == NULL || length == 0) {
        return ESP_ERR_INVALID_ARG;
    }

    return i2c_master_transmit_receive(device, &reg, sizeof(reg), data, length,
                                       -1);
}

/**
 * @brief Read ISM330DLC registers using an ESP-IDF SPI device handle.
 *
 * The first received byte overlaps the transmitted register address and is
 * discarded. The remaining bytes contain the requested register values.
 *
 * @param context Initialized spi_device_handle_t cast to void *.
 * @param reg First register address to read.
 * @param data Destination buffer.
 * @param length Number of consecutive bytes to read.
 * @return ESP_OK on success, otherwise an ESP-IDF SPI error.
 */
esp_err_t esp32_ism330dlc_spi_read(void *context, uint8_t reg,
                                   uint8_t *data, size_t length)
{
    spi_device_handle_t device = (spi_device_handle_t)context;

    if (device == NULL || data == NULL || length == 0) {
        return ESP_ERR_INVALID_ARG;
    }

    uint8_t tx_buffer[length + 1];
    uint8_t rx_buffer[length + 1];
    memset(tx_buffer, 0, sizeof(tx_buffer));
    tx_buffer[0] = (reg & ISM330DLC_SPI_ADDRESS_MASK) |
                   ISM330DLC_SPI_READ_BIT;

    spi_transaction_t transaction = {
        .length = sizeof(tx_buffer) * 8U,
        .tx_buffer = tx_buffer,
        .rx_buffer = rx_buffer,
    };

    esp_err_t err = spi_device_transmit(device, &transaction);
    if (err == ESP_OK) {
        memcpy(data, &rx_buffer[1], length);
    }
    return err;
}

/**
 * @brief Write ISM330DLC registers using an ESP-IDF I2C device handle.
 *
 * @param context Initialized i2c_master_dev_handle_t cast to void *.
 * @param reg First register address to write.
 * @param data Source buffer.
 * @param length Number of consecutive bytes to write.
 * @return ESP_OK on success, otherwise an ESP-IDF I2C error.
 */
esp_err_t esp32_ism330dlc_i2c_write(void *context, uint8_t reg,
                                    const uint8_t *data, size_t length)
{
    i2c_master_dev_handle_t device = (i2c_master_dev_handle_t)context;

    if (device == NULL || data == NULL || length == 0) {
        return ESP_ERR_INVALID_ARG;
    }

    uint8_t transaction[length + 1];
    transaction[0] = reg;
    memcpy(&transaction[1], data, length);

    return i2c_master_transmit(device, transaction, sizeof(transaction), -1);
}

/**
 * @brief Write ISM330DLC registers using an ESP-IDF SPI device handle.
 *
 * @param context Initialized spi_device_handle_t cast to void *.
 * @param reg First register address to write.
 * @param data Source buffer.
 * @param length Number of consecutive bytes to write.
 * @return ESP_OK on success, otherwise an ESP-IDF SPI error.
 */
esp_err_t esp32_ism330dlc_spi_write(void *context, uint8_t reg,
                                    const uint8_t *data, size_t length)
{
    spi_device_handle_t device = (spi_device_handle_t)context;

    if (device == NULL || data == NULL || length == 0) {
        return ESP_ERR_INVALID_ARG;
    }

    uint8_t tx_buffer[length + 1];
    tx_buffer[0] = reg & ISM330DLC_SPI_ADDRESS_MASK;
    memcpy(&tx_buffer[1], data, length);

    spi_transaction_t transaction = {
        .length = sizeof(tx_buffer) * 8U,
        .tx_buffer = tx_buffer,
    };

    return spi_device_transmit(device, &transaction);
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

static int16_t ism330dlc_decode_int16(const uint8_t *data)
{
    return (int16_t)((uint16_t)data[0] | ((uint16_t)data[1] << 8));
}

/**
 * @brief Read and convert only the accelerometer output registers.
 *
 * @param dev Device instance.
 * @param acceleration_g Destination vector in g.
 * @return ESP_OK on success, otherwise an argument or transport error.
 */
esp_err_t esp32_ism330dlc_read_acceleration(
    esp32_ism330dlc_t *dev,
    esp32_ism330dlc_vector_t *acceleration_g)
{
    static const float scale_g_per_lsb[] = {
        0.000061f, 0.000488f, 0.000122f, 0.000244f
    };
    uint8_t data[6];
    float scale;
    esp_err_t err;

    if (dev == NULL || acceleration_g == NULL || dev->read == NULL ||
        dev->accel_full_scale > ISM330DLC_ACCEL_FS_8G) {
        return ESP_ERR_INVALID_ARG;
    }

    err = dev->read(dev->context, OUTX_L_XL, data, sizeof(data));
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to read accelerometer output: %s", esp_err_to_name(err));
        return err;
    }

    scale = scale_g_per_lsb[dev->accel_full_scale];
    acceleration_g->x = ism330dlc_decode_int16(&data[0]) * scale;
    acceleration_g->y = ism330dlc_decode_int16(&data[2]) * scale;
    acceleration_g->z = ism330dlc_decode_int16(&data[4]) * scale;

    dev->registers.sOutput.uOUTX_L_XL.byte = data[0];
    dev->registers.sOutput.uOUTX_H_XL.byte = data[1];
    dev->registers.sOutput.uOUTY_L_XL.byte = data[2];
    dev->registers.sOutput.uOUTY_H_XL.byte = data[3];
    dev->registers.sOutput.uOUTZ_L_XL.byte = data[4];
    dev->registers.sOutput.uOUTZ_H_XL.byte = data[5];

    return ESP_OK;
}

/**
 * @brief Read and convert only the gyroscope output registers.
 *
 * @param dev Device instance.
 * @param angular_rate_dps Destination vector in degrees per second.
 * @return ESP_OK on success, otherwise an argument or transport error.
 */
esp_err_t esp32_ism330dlc_read_angular_rate(
    esp32_ism330dlc_t *dev,
    esp32_ism330dlc_vector_t *angular_rate_dps)
{
    static const float scale_dps_per_lsb[] = {
        0.00875f, 0.01750f, 0.035f, 0.070f
    };
    uint8_t data[6];
    float scale;
    esp_err_t err;

    if (dev == NULL || angular_rate_dps == NULL || dev->read == NULL ||
        dev->gyro_full_scale > ISM330DLC_GYRO_FS_2000_DPS) {
        return ESP_ERR_INVALID_ARG;
    }

    err = dev->read(dev->context, OUTX_L_G, data, sizeof(data));
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to read gyroscope output: %s", esp_err_to_name(err));
        return err;
    }

    scale = scale_dps_per_lsb[dev->gyro_full_scale];
    angular_rate_dps->x = ism330dlc_decode_int16(&data[0]) * scale;
    angular_rate_dps->y = ism330dlc_decode_int16(&data[2]) * scale;
    angular_rate_dps->z = ism330dlc_decode_int16(&data[4]) * scale;

    dev->registers.sOutput.uOUTX_L_G.byte = data[0];
    dev->registers.sOutput.uOUTX_H_G.byte = data[1];
    dev->registers.sOutput.uOUTY_L_G.byte = data[2];
    dev->registers.sOutput.uOUTY_H_G.byte = data[3];
    dev->registers.sOutput.uOUTZ_L_G.byte = data[4];
    dev->registers.sOutput.uOUTZ_H_G.byte = data[5];

    return ESP_OK;
}

/**
 * @brief Read the complete temperature, gyroscope, and accelerometer output.
 *
 * @param dev Device instance.
 * @param sample Destination for decoded raw values.
 * @return ESP_OK on success, otherwise an argument or transport error.
 */
esp_err_t esp32_ism330dlc_read_raw(esp32_ism330dlc_t *dev,
                                  esp32_ism330dlc_raw_sample_t *sample)
{
    uint8_t data[14];
    esp_err_t err;

    if (dev == NULL || sample == NULL || dev->read == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    err = dev->read(dev->context, OUT_TEMP_L, data, sizeof(data));
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to read IMU output registers: %s", esp_err_to_name(err));
        return err;
    }

    sample->temperature = ism330dlc_decode_int16(&data[0]);
    sample->angular_rate.x = ism330dlc_decode_int16(&data[2]);
    sample->angular_rate.y = ism330dlc_decode_int16(&data[4]);
    sample->angular_rate.z = ism330dlc_decode_int16(&data[6]);
    sample->acceleration.x = ism330dlc_decode_int16(&data[8]);
    sample->acceleration.y = ism330dlc_decode_int16(&data[10]);
    sample->acceleration.z = ism330dlc_decode_int16(&data[12]);

    dev->registers.sOutput.uOUT_TEMP_L.byte = data[0];
    dev->registers.sOutput.uOUT_TEMP_H.byte = data[1];
    dev->registers.sOutput.uOUTX_L_G.byte = data[2];
    dev->registers.sOutput.uOUTX_H_G.byte = data[3];
    dev->registers.sOutput.uOUTY_L_G.byte = data[4];
    dev->registers.sOutput.uOUTY_H_G.byte = data[5];
    dev->registers.sOutput.uOUTZ_L_G.byte = data[6];
    dev->registers.sOutput.uOUTZ_H_G.byte = data[7];
    dev->registers.sOutput.uOUTX_L_XL.byte = data[8];
    dev->registers.sOutput.uOUTX_H_XL.byte = data[9];
    dev->registers.sOutput.uOUTY_L_XL.byte = data[10];
    dev->registers.sOutput.uOUTY_H_XL.byte = data[11];
    dev->registers.sOutput.uOUTZ_L_XL.byte = data[12];
    dev->registers.sOutput.uOUTZ_H_XL.byte = data[13];

    return ESP_OK;
}

/**
 * @brief Read sensor output and convert it to engineering units.
 *
 * @param dev Device instance.
 * @param sample Destination for converted values.
 * @return ESP_OK on success, otherwise an argument or transport error.
 */
esp_err_t esp32_ism330dlc_read(esp32_ism330dlc_t *dev,
                              esp32_ism330dlc_sample_t *sample)
{
    static const float accel_mg_per_lsb[] = { 0.061f, 0.488f, 0.122f, 0.244f };
    static const float gyro_mdps_per_lsb[] = { 8.75f, 17.50f, 35.0f, 70.0f };
    esp32_ism330dlc_raw_sample_t raw;
    esp_err_t err;
    float accel_scale;
    float gyro_scale;

    if (dev == NULL || sample == NULL ||
        dev->accel_full_scale > ISM330DLC_ACCEL_FS_8G ||
        dev->gyro_full_scale > ISM330DLC_GYRO_FS_2000_DPS) {
        return ESP_ERR_INVALID_ARG;
    }

    err = esp32_ism330dlc_read_raw(dev, &raw);
    if (err != ESP_OK) {
        return err;
    }

    accel_scale = accel_mg_per_lsb[dev->accel_full_scale] / 1000.0f;
    gyro_scale = gyro_mdps_per_lsb[dev->gyro_full_scale] / 1000.0f;

    sample->acceleration_g.x = raw.acceleration.x * accel_scale;
    sample->acceleration_g.y = raw.acceleration.y * accel_scale;
    sample->acceleration_g.z = raw.acceleration.z * accel_scale;
    sample->angular_rate_dps.x = raw.angular_rate.x * gyro_scale;
    sample->angular_rate_dps.y = raw.angular_rate.y * gyro_scale;
    sample->angular_rate_dps.z = raw.angular_rate.z * gyro_scale;
    sample->temperature_c = 25.0f + ((float)raw.temperature / 16.0f);

    return ESP_OK;
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

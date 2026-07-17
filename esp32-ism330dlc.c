#include <stdio.h>
#include <string.h>

#include <esp_err.h>
#include <esp_log.h>

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

/*  @brief:     Initialize the ISM330DLC sensor 
    @param      dev: Pointer to the ISM330DLC device structure
    @return:    ESP_OK if successful, otherwise an error code
*/
esp_err_t esp32_ism330dlc_init(esp32_ism330dlc_t *dev)
{
    esp32_ism330dlc_registers registers;

    ESP_LOGI(TAG, "Initializing ISM330DLC sensor...");

    if (dev == NULL) {
        ESP_LOGE(TAG, "Device structure pointer is NULL.");
        return ESP_ERR_INVALID_ARG;
    }

    ESP_ERROR_CHECK(esp32_ism330dlc_registers_zero_init(&registers));
    dev->registers = registers;

    /*Translate settings of main struct into register config and update tge ISM330 accordingly*/



    ESP_LOGI(TAG, "ISM330DLC sensor initialized successfully.");

    return ESP_OK;
}

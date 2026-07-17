#ifndef ESP32_ISM330DLC_H
#define ESP32_ISM330DLC_H

#include <esp_err.h>

#include "esp32-ism330dlc_registers.h"

#define TAG "esp32-ism330dlc"

typedef struct esp32_ism330dlc{
    esp32_ism330dlc_registers registers;    /*Register instance of device*/
    
} esp32_ism330dlc_t;

esp_err_t esp32_ism330dlc_init(esp32_ism330dlc_t *dev);

#endif // ESP32_ISM330DLC_H

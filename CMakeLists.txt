idf_component_register(SRCS "esp32-ism330dlc.c"
                    INCLUDE_DIRS "include"
                    PRIV_REQUIRES esp_driver_i2c esp_driver_spi)

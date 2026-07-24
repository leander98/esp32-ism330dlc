# ESP32 ISM330DLC component

ESP-IDF driver for the ST ISM330DLC 3-axis accelerometer and 3-axis
gyroscope. The component supports I2C and SPI transports, sensor
initialization, converted or raw sample reads, and interrupt routing.

## Requirements

- ESP-IDF with the `driver/i2c_master.h` API
- An ISM330DLC connected over I2C or SPI
- External I2C pull-up resistors are recommended, especially at 400 kHz

## Adding the component

Place `esp32-ism330dlc` in the project's `components` directory and declare it
from the consuming component:

```cmake
idf_component_register(
    SRCS "main.c"
    INCLUDE_DIRS "."
    PRIV_REQUIRES esp32-ism330dlc esp_driver_gpio esp_driver_i2c
)
```

Use `esp_driver_spi` instead of `esp_driver_i2c` when the application creates
an SPI device.

## I2C wiring

The sensor uses the following unshifted 7-bit address:

| SDO/SA0 level | Address |
| --- | --- |
| Low | `0x6A` |
| High | `0x6B` |

Create an ESP-IDF I2C device, then use its handle as the driver context:

```c
const i2c_master_bus_config_t bus_config = {
    .i2c_port = I2C_NUM_0,
    .sda_io_num = GPIO_NUM_8,
    .scl_io_num = GPIO_NUM_9,
    .clk_source = I2C_CLK_SRC_DEFAULT,
    .glitch_ignore_cnt = 7,
    .flags.enable_internal_pullup = true,
};

i2c_master_bus_handle_t bus;
ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, &bus));

const i2c_device_config_t device_config = {
    .dev_addr_length = I2C_ADDR_BIT_LEN_7,
    .device_address = 0x6A,
    .scl_speed_hz = 400000,
};

i2c_master_dev_handle_t device;
ESP_ERROR_CHECK(i2c_master_bus_add_device(bus, &device_config, &device));

esp32_ism330dlc_t imu = ESP32_ISM330DLC_DEFAULT_CONFIG(
    esp32_ism330dlc_i2c_read,
    esp32_ism330dlc_i2c_write,
    device);

ESP_ERROR_CHECK(esp32_ism330dlc_init(&imu));
```

Change the GPIOs and address to match the board wiring. The bus and device
must remain valid for as long as the IMU instance is used.

## SPI setup

After the application creates an ESP-IDF `spi_device_handle_t`, construct the
driver with the component-provided SPI callbacks:

```c
esp32_ism330dlc_t imu = ESP32_ISM330DLC_DEFAULT_CONFIG(
    esp32_ism330dlc_spi_read,
    esp32_ism330dlc_spi_write,
    spi_device);

ESP_ERROR_CHECK(esp32_ism330dlc_init(&imu));
```

Bus pins, host, clock speed, mode, and chip-select setup remain the
application's responsibility. Configure the SPI device without separate
command or address phases; the callbacks transmit the register address as the
first data byte.

## Reading measurements

Read all converted outputs in one transaction:

```c
esp32_ism330dlc_sample_t sample;

if (esp32_ism330dlc_read(&imu, &sample) == ESP_OK) {
    printf("accel: %.3f %.3f %.3f g\n",
           sample.acceleration_g.x,
           sample.acceleration_g.y,
           sample.acceleration_g.z);
    printf("gyro: %.3f %.3f %.3f dps\n",
           sample.angular_rate_dps.x,
           sample.angular_rate_dps.y,
           sample.angular_rate_dps.z);
    printf("temperature: %.2f C\n", sample.temperature_c);
}
```

Available read functions:

| Function | Result |
| --- | --- |
| `esp32_ism330dlc_read()` | Acceleration in g, angular rate in dps, and temperature in °C |
| `esp32_ism330dlc_read_raw()` | Raw signed temperature, gyroscope, and accelerometer values |
| `esp32_ism330dlc_read_acceleration()` | Converted acceleration vector in g |
| `esp32_ism330dlc_read_angular_rate()` | Converted angular-rate vector in dps |

## Configuration

`ESP32_ISM330DLC_DEFAULT_CONFIG()` selects:

- Accelerometer output data rate: 416 Hz
- Gyroscope output data rate: 416 Hz
- Accelerometer full scale: ±4 g
- Gyroscope full scale: ±2000 dps

Override fields before initialization when different settings are required:

```c
imu.accel_odr = ISM330DLC_ODR_104_HZ;
imu.gyro_odr = ISM330DLC_ODR_104_HZ;
imu.accel_full_scale = ISM330DLC_ACCEL_FS_8G;
imu.gyro_full_scale = ISM330DLC_GYRO_FS_500_DPS;

ESP_ERROR_CHECK(esp32_ism330dlc_init(&imu));
```

The `ESP32_ISM330DLC_USE_FREERTOS_DELAY` option under
`Component config > ISM330DLC driver configuration` selects whether reset
delays use `vTaskDelay()` or the ROM microsecond delay. The ROM delay is the
default.

## Interrupts

Use `esp32_ism330dlc_configure_interrupts()` to configure INT1/INT2 polarity,
output type, data-ready behavior, and source routing. Event generators such as
tap, wake-up, and free-fall require their own sensor-register configuration
before routed interrupts can occur.

## Custom transports

Applications may replace the supplied ESP-IDF callbacks with custom functions
matching `esp32_ism330dlc_read_fn` and `esp32_ism330dlc_write_fn`. The context
pointer is passed unchanged to every transport operation.

See [`example/example.c`](example/example.c) for a complete I2C initialization
and periodic sampling example.

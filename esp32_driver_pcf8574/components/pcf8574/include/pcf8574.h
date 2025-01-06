#ifndef __PCF8574_H__
#define __PCF8574_H__

#include "driver/i2c_master.h"
#include "esp_err.h"
#include "driver/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    i2c_port_t port;  /*!< I2C port number */
    uint8_t addr;     /*!< I2C address of the device */
} pcf8574_dev_t;


//   Initialize PCF8574 device
 
//   dev Pointer to PCF8574 device descriptor
//   addr I2C address (default: 0x20)
//   port I2C port number (e.g., I2C_NUM_0 or I2C_NUM_1)
//   sda_gpio SDA GPIO pin number
//   scl_gpio SCL GPIO pin number
//   ESP_OK on success, or an error code
 
esp_err_t pcf8574_init(pcf8574_dev_t *dev, uint8_t addr, i2c_port_t port, gpio_num_t sda_gpio, gpio_num_t scl_gpio);


//    Free the I2C resources for PCF8574
//    dev Pointer to PCF8574 device descriptor
//    return ESP_OK on success, or an error code
 
esp_err_t pcf8574_deinit(pcf8574_dev_t *dev);


//   Read the GPIO port value of the PCF8574
 
//   dev Pointer to PCF8574 device descriptor
//   val Pointer to store the GPIO port value
//   ESP_OK on success, or an error code
 
esp_err_t pcf8574_port_read(pcf8574_dev_t *dev, uint8_t *val);


//   Write value to the GPIO port of the PCF8574
//   Pointer to PCF8574 device descriptor
//   GPIO port value to write
//   ESP_OK on success, or an error code
 
esp_err_t pcf8574_port_write(pcf8574_dev_t *dev, uint8_t val);

#ifdef __cplusplus
}
#endif

#endif 

#include "pcf8574.h"
#include "esp_log.h"
#include "driver/i2c.h"

#define TAG "PCF8574"

// I2C command handling macros
#define I2C_TIMEOUT_MS    1000  // Timeout for I2C operations

esp_err_t pcf8574_init(pcf8574_dev_t *dev, uint8_t addr, i2c_port_t port, gpio_num_t sda_gpio, gpio_num_t scl_gpio)
{
    esp_err_t ret;
    
    // Configure I2C master interface
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = sda_gpio,
        .scl_io_num = scl_gpio,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000,  // 100kHz clock speed
    };
    
    // Initialize I2C driver
    ret = i2c_param_config(port, &conf);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to configure I2C");
        return ret;
    }
    
    ret = i2c_driver_install(port, I2C_MODE_MASTER, 0, 0, 0);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to install I2C driver");
        return ret;
    }

    dev->port = port;
    dev->addr = addr;

    return ESP_OK;
}

esp_err_t pcf8574_deinit(pcf8574_dev_t *dev)
{
    esp_err_t ret = i2c_driver_delete(dev->port);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to uninstall I2C driver");
    }
    return ret;
}

esp_err_t pcf8574_port_read(pcf8574_dev_t *dev, uint8_t *val)
{
    esp_err_t ret;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    
    // Start I2C communication
    i2c_master_start(cmd);
    
    // Write the I2C address with a read bit (last bit = 1)
    i2c_master_write_byte(cmd, (dev->addr << 1) | I2C_MASTER_READ, true);

    // Read the value from the port
    i2c_master_read_byte(cmd, val, I2C_MASTER_ACK);

    // Stop communication
    i2c_master_stop(cmd);

    // Execute the command
    ret = i2c_master_cmd_begin(dev->port, cmd, pdMS_TO_TICKS(I2C_TIMEOUT_MS));
    i2c_cmd_link_delete(cmd);

    return ret;
}

esp_err_t pcf8574_port_write(pcf8574_dev_t *dev, uint8_t val)
{
    esp_err_t ret;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    
    // Start I2C communication
    i2c_master_start(cmd);

    // Write the I2C address with a write bit (last bit = 0)
    i2c_master_write_byte(cmd, (dev->addr << 1) | I2C_MASTER_WRITE, true);

    // Write the value to the port
    i2c_master_write(cmd, &val, 1, true);

    // Stop communication
    i2c_master_stop(cmd);

    // Execute the command
    ret = i2c_master_cmd_begin(dev->port, cmd, pdMS_TO_TICKS(I2C_TIMEOUT_MS));
    i2c_cmd_link_delete(cmd);

    return ret;
}

#include "pcf8574.h"
#include "esp_log.h"

#define SDA_PIN GPIO_NUM_21
#define SCL_PIN GPIO_NUM_22
#define PCF8574_ADDR 0x27  // Default address for PCF8574

void app_main()
{
    esp_err_t ret;
    pcf8574_dev_t pcf_dev;

    // Initialize the PCF8574 device
    ret = pcf8574_init(&pcf_dev, PCF8574_ADDR, I2C_NUM_0, SDA_PIN, SCL_PIN);
    if (ret != ESP_OK) {
        ESP_LOGE("PCF8574", "PCF8574 initialization failed");
        return;
    }

    //uint8_t read_val;
    // Read the GPIO port value
    // ret = pcf8574_port_read(&pcf_dev, &read_val);
    // if (ret == ESP_OK) {
    //     ESP_LOGI("PCF8574", "Read GPIO value: 0x%02X", read_val);
    // } else {
    //     ESP_LOGE("PCF8574", "Failed to read GPIO value");
    // }

    // Write value to the GPIO port
    // P0		0x01	
    // P1		0x02	
    // P2		0x04	
    // P3		0x08	
    // P4		0x10	
    // P5		0x20	
    // P6		0x40	
    // P7		0x80	
    ret = pcf8574_port_write(&pcf_dev, 0x10);  // Set all pins high
    if (ret != ESP_OK) {
        ESP_LOGE("PCF8574", "Failed to write GPIO value");
    } else {
        ESP_LOGI("PCF8574", "GPIO pins set to high ");
    }

    // Deinitialize the PCF8574 device
    pcf8574_deinit(&pcf_dev);
}

#include "pcf8574.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


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
    //pcf8574_pullup(&pcf_dev, P5);
    pcf8574_pulldown(&pcf_dev);

    
    
    ret = gpio_high(&pcf_dev, P4);  // Set all pins high
    if (ret != ESP_OK) {
        ESP_LOGE("PCF8574", "Failed to write GPIO value");
    } else {
        ESP_LOGI("PCF8574", "GPIO pins set to high ");
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
    //Read the GPIO port value
    uint8_t read_val;
    ret = gpio_read(&pcf_dev, &read_val);
    if (ret == ESP_OK) {
        ESP_LOGI("PCF8574", "Read High GPIO value: 0x%02X", read_val);
        // if (read_val & 0x10) 
        // {  
        //     // Check P4 (0x10 corresponds to P4)
        //     ESP_LOGI("PCF8574", "Pin P4 is HIGH");
        // } 
        // else 
        // {
        //     ESP_LOGI("PCF8574", "Pin P4 is LOW");
        // }
    } 
    else 
    {
        ESP_LOGE("PCF8574", "Failed to read GPIO value");
    }


    // Deinitialize the PCF8574 device
    pcf8574_deinit(&pcf_dev);
}

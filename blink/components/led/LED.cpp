#include "LED.h"

LED::LED(gpio_num_t ledPin) : 
ledPin(ledPin) 
{
    if(this->ledPin != GPIO_NUM_NC){
        // Multi ledPin configuration
        gpio_config_t gpioOutputConfigure = {
            .pin_bit_mask = (1ULL << ledPin),
            .mode = GPIO_MODE_INPUT_OUTPUT,
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
            .intr_type = GPIO_INTR_DISABLE
        };
        ESP_ERROR_CHECK(gpio_config(&gpioOutputConfigure));
    } else {
        ESP_LOGI("LED Setup", "Led pin set to GPIO_NUM_NC");
    }

    xBlinkHandle = NULL;
}

void LED::begin(const BaseType_t app_cpu) {

        if (xBlinkHandle == NULL) {
            BaseType_t result = xTaskCreatePinnedToCore(
                blinkTask,          //Task
                "BlinkTask",        //Task name
                2048,               //Size of the task
                this,               //This instance, or this particular object
                1,                  //Priority
                &xBlinkHandle,      //Task handle
                app_cpu             //Core
            );

            if (result == pdPASS){
                ESP_LOGI("SETUP", "Created the BlinkTask successfully");
            } else {
                ESP_LOGI("SETUP", "Failed to create the task");
            }
        } else {
            ESP_LOGI("SETUP", "BlinkTask already created");
        }
}

void LED::turnOn() {
    gpio_set_level(ledPin, 1);
    ESP_LOGI("turnOn", "Led is On");
}

void LED::turnOff() {
    gpio_set_level(ledPin, 0);
    ESP_LOGI("turnOff", "Led is Off");
}

void LED::toggle() {
    gpio_set_level(ledPin, !gpio_get_level(ledPin));
    ESP_LOGI("toggle", "Led state: %d", gpio_get_level(ledPin));
}

// Definition of blinkTask
void LED::blinkTask(void *pvParameters) {
    while (1) {
        static_cast<LED*>(pvParameters)->toggle();
        vTaskDelay(1000 / portTICK_PERIOD_MS);  // Wait for 1000 milliseconds
    }
}

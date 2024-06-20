#include "gpio.h"

namespace NamespaceGpio
{
    gpio::gpio(const gpio_config_t& cfg, const gpio_num_t pin = GPIO_NUM_NC, const bool invertedLogic = false) :
    cfg(cfg),
    pin(pin),
    invertedLogic(invertedLogic)
    // xBlinkHandle(nullptr)
    {}

    [[nodiscard]] esp_err_t gpio::init(void) {
        esp_err_t status{ESP_OK};
        status |= gpio_config(&cfg);
        return status;
    }


    gpioOutput::gpioOutput(const gpio_num_t pin = GPIO_NUM_NC, const bool invertedLogic = false) :
    gpio(gpio_config_t{
        .pin_bit_mask   = static_cast<uint64_t>(1),
        .mode           = GPIO_MODE_OUTPUT,
        .pull_up_en     = GPIO_PULLUP_DISABLE,
        .pull_down_en   = GPIO_PULLDOWN_ENABLE,
        .intr_type      = GPIO_INTR_DISABLE
    },
    pin,
    invertedLogic) {}
    }

    [[nodiscard]] esp_err_t gpioOutput::init(void) {
        esp_err_t status = gpio::init();
        if(ESP_OK == status)
            status =| set(invertedLogic);
        return status;
    }

    esp_err_t gpioOutput::set(const bool state) {
        this->state = state;
        return gpio_set_level(this->pin, invertedLogic ? !state : state);
    }
} // namespace NamespaceGpio

    // void gpioOutput::begin(const BaseType_t app_cpu) {

    //     if (xBlinkHandle == nullptr) {
    //         BaseType_t result = xTaskCreatePinnedToCore(
    //             blinkTask,          //Task
    //             "BlinkTask",        //Task name
    //             2048,               //Size of the task
    //             this,               //This instance, or this particular object
    //             1,                  //Priority
    //             &xBlinkHandle,      //Task handle
    //             app_cpu             //Core
    //         );

    //         if (result == pdPASS){
    //             ESP_LOGI("SETUP", "Created the BlinkTask successfully");
    //         } else {
    //             ESP_LOGI("SETUP", "Failed to create the task");
    //         }
    //     } else {
    //         ESP_LOGI("SETUP", "BlinkTask already created");
    //     }
    // }


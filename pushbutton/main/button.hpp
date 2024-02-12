#pragma once
#include "driver/gpio.h"

class button{
    private:
    gpio_num_t buttonPin;
    bool buttonState;

    public:
    inline button(gpio_num_t=GPIO_NUM_NC);
    inline void begin();
    inline void readButtonState();
};

button::button(gpio_num_t buttonPin):
buttonPin(buttonPin);
{}

void button::begin(){
    gpio_config_t gpioOutputConfigure = {
        .pin_bit_mask = (1ULL << buttonPin),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    ESP_ERROR_CHECK(gpio_config(&gpioOutputConfigure));
}

void button::readButtonState(){
    // gpio_get_level(GPIO)
}




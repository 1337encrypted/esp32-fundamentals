#pragma once

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"

class LED {
private:
    gpio_num_t ledPin;

public:
    LED(gpio_num_t = GPIO_NUM_NC);
    void begin(const BaseType_t = 1);
    inline void turnOn();
    inline void turnOff();
    inline void toggle();

    static inline void blinkTask(void *);

    //Task handles
    TaskHandle_t xBlinkHandle;
};


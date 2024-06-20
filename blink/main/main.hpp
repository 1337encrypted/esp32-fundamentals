#include <stdio.h>
#include "main.hpp"
#include "gpio.hpp"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// #if CONFIG_FREERTOS_UNICORE
//   static const BaseType_t app_cpu = 0;
// #else
//   static const BaseType_t app_cpu = 1;
// #endif


class Main {
    public:
    esp_err_t setup();
    void loop(void);

    gpio::gpioOutput blueLed(ledPin, true)
}

extern "C" void app_main(void)
{
  
}
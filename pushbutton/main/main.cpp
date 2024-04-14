#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "button.hpp"

constexpr gpio_num_t pushButtonPin = GPIO_NUM_23;

Button pushButton(pushButtonPin);

extern "C" {
    void app_main(void)
    {
        pushButton.begin();
    }
}

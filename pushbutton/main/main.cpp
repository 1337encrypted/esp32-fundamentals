#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "button.hpp"

constexpr gpio_num_t pushButtonPin = GPIO_NUM_23;
constexpr gpio_num_t ledPin = GPIO_NUM_2;

button btn1(pushButtonPin);

extern "C" {
    void app_main(void)
    {
        btn.begin();
        while(true){
            // btn1.readButtonState();
        }
    }
}

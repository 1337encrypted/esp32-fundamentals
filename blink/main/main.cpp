#include <stdio.h>

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"

#include "LED.h"

#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

constexpr gpio_num_t ledPin = GPIO_NUM_2;

LED blueLed(ledPin);

extern "C"
{
  void app_main(void)
  {
    blueLed.begin(app_cpu);
  }
}
#include <stdio.h>
#include "driver/gpio.h"
#include "esp_log.h"
#include "iot_button.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define TAG "BUTTON_EXAMPLE"
constexpr gpio_num_t PUSHBUTTON_PIN = GPIO_NUM_4;

static void button_press_down_cb(void *arg, void *data)
{
    ESP_LOGI(TAG, "BTN%d: BUTTON_PRESS_DOWN", (int)arg);
}

static void button_press_up_cb(void *arg, void *data)
{
    ESP_LOGI(TAG, "BTN: BUTTON_PRESS_UP[%d]", iot_button_get_ticks_time((button_handle_t)arg));
}

static void button_single_click_cb(void *arg, void *data)
{
    ESP_LOGI(TAG, "BTN: BUTTON_SINGLE_CLICK");
}

static void button_double_click_cb(void *arg, void *data)
{
    ESP_LOGI(TAG, "BTN: BUTTON_DOUBLE_CLICK");
}

static void button_long_press_start_cb(void *arg, void *data)
{
    ESP_LOGI(TAG, "BTN: BUTTON_LONG_PRESS_START");
}

static void button_long_press_hold_cb(void *arg, void *data)
{
    ESP_LOGI(TAG, "BTN: BUTTON_LONG_PRESS_HOLD");
}

static void button_long_press_up_cb(void *arg, void *data)
{
    ESP_LOGI(TAG, "BTN: BUTTON_LONG_PRESS_UP");
}

#include <stdio.h>
#include "driver/gpio.h"
#include "esp_log.h"
#include "iot_button.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define TAG "BUTTON_EXAMPLE"

const gpio_num_t pushbuttonPin = GPIO_NUM_2;

extern "C" {
    static void button_press_down_cb(void *arg, void *data)
    {
        ESP_LOGI(TAG, "BTN: BUTTON_PRESS_DOWN");
    }

    static void button_press_up_cb(void *arg, void *data)
    {
        ESP_LOGI(TAG, "BTN: BUTTON_PRESS_UP[%d]", iot_button_get_ticks_time((button_handle_t)arg));
    }

    static void button_press_repeat_cb(void *arg, void *data)
    {
        ESP_LOGI(TAG, "BTN: BUTTON_PRESS_REPEAT[%d]", iot_button_get_repeat((button_handle_t)arg));
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
        ESP_LOGI(TAG, "BTN: BUTTON_LONG_PRESS_HOLD[%d],count is [%d]", 
                 iot_button_get_ticks_time((button_handle_t)arg), 
                 iot_button_get_long_press_hold_cnt((button_handle_t)arg));
    }

    static void button_press_repeat_done_cb(void *arg, void *data)
    {
        ESP_LOGI(TAG, "BTN: BUTTON_PRESS_REPEAT_DONE[%d]", iot_button_get_repeat((button_handle_t)arg));
    }

    void app_main(void)
    {
        // Button configuration
        button_config_t pushbutton_config = {
            .type = BUTTON_TYPE_GPIO,
            .long_press_time = 1000,
            .short_press_time = 200,
            .gpio_button_config = {
                .gpio_num = pushbuttonPin,
                .active_level = 1,
            },
        };

        // Create button
        button_handle_t pushbutton = iot_button_create(&pushbutton_config);
        if (pushbutton == NULL) {
            ESP_LOGE(TAG, "Button creation failed");
            return;
        }

        // Register callbacks
        iot_button_register_cb(pushbutton, BUTTON_PRESS_DOWN, button_press_down_cb, NULL);
        iot_button_register_cb(pushbutton, BUTTON_PRESS_UP, button_press_up_cb, NULL);
        iot_button_register_cb(pushbutton, BUTTON_PRESS_REPEAT, button_press_repeat_cb, NULL);
        iot_button_register_cb(pushbutton, BUTTON_SINGLE_CLICK, button_single_click_cb, NULL);
        iot_button_register_cb(pushbutton, BUTTON_DOUBLE_CLICK, button_double_click_cb, NULL);
        iot_button_register_cb(pushbutton, BUTTON_LONG_PRESS_START, button_long_press_start_cb, NULL);
        iot_button_register_cb(pushbutton, BUTTON_LONG_PRESS_HOLD, button_long_press_hold_cb, NULL);
        iot_button_register_cb(pushbutton, BUTTON_PRESS_REPEAT_DONE, button_press_repeat_done_cb, NULL);

        // Get initial button level
        uint8_t level = iot_button_get_key_level(pushbutton);
        ESP_LOGI(TAG, "Initial button level is %d", level);

        // Main loop
        while (1) {
            vTaskDelay(pdMS_TO_TICKS(1000));
        }

        // This part will never be reached in this example
        iot_button_delete(pushbutton);
    }
}
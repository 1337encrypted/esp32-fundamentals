#include "main.hpp"

extern "C" void app_main(void)
{
    button_config_t pushbutton = {
        .type = BUTTON_TYPE_GPIO,
        .long_press_time = 1000,
        .short_press_time = 200,
        .gpio_button_config = {
            .gpio_num = PUSHBUTTON_PIN,
            .active_level = 0,
        },
    };

    button_handle_t btn_handle = iot_button_create(&pushbutton);
    if (btn_handle == NULL) {
        ESP_LOGE(TAG, "Button creation failed");
        return;
    }

    iot_button_register_cb(btn_handle, BUTTON_PRESS_DOWN, button_press_down_cb, (void*)PUSHBUTTON_PIN);
    iot_button_register_cb(btn_handle, BUTTON_PRESS_UP, button_press_up_cb, NULL);
    iot_button_register_cb(btn_handle, BUTTON_SINGLE_CLICK, button_single_click_cb, NULL);
    iot_button_register_cb(btn_handle, BUTTON_DOUBLE_CLICK, button_double_click_cb, NULL);
    iot_button_register_cb(btn_handle, BUTTON_LONG_PRESS_START, button_long_press_start_cb, NULL);
    iot_button_register_cb(btn_handle, BUTTON_LONG_PRESS_HOLD, button_long_press_hold_cb, NULL);
    iot_button_register_cb(btn_handle, BUTTON_LONG_PRESS_UP, button_long_press_up_cb, NULL);

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    // This part will never be reached in this example
    iot_button_delete(btn_handle);
}
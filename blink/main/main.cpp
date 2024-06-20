#include "main.hpp"

esp_err_t Main::setup(void) {
  blueLed.init();
}

void Main::loop {
  ESP_LOGI(LOG_TAG, "blueLed is on");
  blueLed.set(true);
  vTaskDelay(pdSecond);
  ESP_LOGI(LOG_TAG, "blueLed is off");
  blueLed.set(false);
  vTaskDelay(pdSecond);
}
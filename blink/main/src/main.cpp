#include "main.hpp"

static Main myMain;

extern "C" void app_main(void) {
  ESP_ERROR_CHECK(myMain.setup());

  while(true) {
    myMain.loop();
  }
}

esp_err_t Main::setup(void) {
  esp_err_t status = ESP_OK;
  status = blueLed.init();
  return status;
}

void Main::loop {
  ESP_LOGI(LOG_TAG, "blueLed is on");
  blueLed.set(true);
  vTaskDelay(pdSecond);
  ESP_LOGI(LOG_TAG, "blueLed is off");
  blueLed.set(false);
  vTaskDelay(pdSecond);
}
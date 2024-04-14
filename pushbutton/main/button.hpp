#include <iostream>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_log.h"

QueueHandle_t interruptQueue;

class Button {
private:
    gpio_num_t buttonPin;

public:
    Button(gpio_num_t pin = GPIO_NUM_NC);
    void begin(BaseType_t app_cpu = 1);

    static void buttonPushedTask(void* pvParams);
    static void buttonPressedISR(void* arg);
};

Button::Button(gpio_num_t buttonPin) : buttonPin(buttonPin) {}

void Button::begin(BaseType_t app_cpu) {
    interruptQueue = xQueueCreate(10, sizeof(uint32_t));

    // Configure GPIO pin
    gpio_config_t gpioConfig = {
        .pin_bit_mask = (1ULL << buttonPin),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .intr_type = GPIO_INTR_POSEDGE // Trigger on positive edge (button press)
    };
    ESP_ERROR_CHECK(gpio_config(&gpioConfig));

    // Install ISR service to handle GPIO interrupts
    ESP_ERROR_CHECK(gpio_install_isr_service(0));
    ESP_ERROR_CHECK(gpio_isr_handler_add(this->buttonPin, buttonPressedISR, reinterpret_cast<void*>(this->buttonPin)));

    xTaskCreatePinnedToCore(buttonPushedTask, "buttonPushedTask", configMINIMAL_STACK_SIZE, nullptr, 1, nullptr, app_cpu);

    std::cout << "Minimum free heap size: " << esp_get_minimum_free_heap_size() << " bytes" << std::endl;
}

void IRAM_ATTR Button::buttonPressedISR(void* args) {

    gpio_num_t buttonPin = static_cast<gpio_num_t>(reinterpret_cast<uintptr_t>(args));

    xQueueSendFromISR(interruptQueue, &buttonPin, nullptr);
}

void Button::buttonPushedTask(void *pvParams) {
    int count = 0;
    gpio_num_t buttonPin;
    while (true) {
        if (xQueueReceive(interruptQueue, &buttonPin, portMAX_DELAY)) {

            gpio_isr_handler_remove(buttonPin);     // Disable the interrupt.

            
            // wait some time while we check for the button to be released
            do {
                vTaskDelay(20 / portTICK_PERIOD_MS) ;
            } while(gpio_get_level(buttonPin) == 1);

            std::cout << "Button GPIO " << buttonPin << " was pressed " << count++ << " times" << std::endl;

            
            gpio_isr_handler_add(buttonPin, buttonPressedISR, (void *)buttonPin);       // re-enable the interrupt
        }
    }
}

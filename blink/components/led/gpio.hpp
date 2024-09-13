#pragma once

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"

namespace NamespaceGpio {
    
    class gpio {
    protected:
        const gpio_config_t cfg;
        const gpio_num_t pin;
        const bool invertedLogic;
        // BaseType_t xBlinkHandle;

    public:
        constexpr gpio(const gpio_config_t& cfg, const gpio_num_t pin = GPIO_NUM_NC, const bool invertedLogic = false);
        [[nodiscard]] inline esp_err_t init(void);
        virtual bool state(void) = 0;
        virtual esp_err_t set(const bool state) = 0;
    }; 

    class gpioOutput : public gpio {
    private:
        bool state;
    public: 
        constexpr gpioOutput(const gpio_num_t pin = GPIO_NUM_NC, const bool invertedLogic = false);
        [[nodiscard]] inline esp_err_t init(void);
        inline esp_err_t set(const bool state);
        inline esp_err_t toggle(void);
        inline bool state(return state);

        // static inline void blinkTask(void *);

        //Task handles
        // TaskHandle_t xBlinkHandle;
    };

    class gpioInput : public gpio {
    private:

    public:
        [[nodiscard]] inline esp_err_t init(void);
    }
}   // namespece GPIO


extern "C" void app_main(void)
{
  
}
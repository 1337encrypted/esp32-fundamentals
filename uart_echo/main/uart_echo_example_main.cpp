#include "uart.hpp"

#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

HardwareUart serial;

extern "C" {
    void app_main(void) {
        serial.begin(app_cpu);
    }
}

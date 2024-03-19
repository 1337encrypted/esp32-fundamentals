#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include <string.h>

#define TXD 4
#define RXD 5
#define RTS (UART_PIN_NO_CHANGE)
#define CTS (UART_PIN_NO_CHANGE)

constexpr uart_port_t PORT_NUM = UART_NUM_2;
#define STACK_SIZE 2048

static const char *TAG = "UART TEST";

class HardwareUart {
private:
    const int uart_buffer_size;
    QueueHandle_t uart_queue;
    int length;
    const char* test_str;

public:
    HardwareUart(int buffer_size = 1024, const char* str = "S\n")
        : uart_buffer_size(buffer_size), length(0), test_str(str) {

        uart_config_t uart_config = {
            .baud_rate = 115200,
            .data_bits = UART_DATA_8_BITS,
            .parity    = UART_PARITY_DISABLE,
            .stop_bits = UART_STOP_BITS_1,
            .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
            .rx_flow_ctrl_thresh = UART_SCLK_APB,
            .source_clk = UART_SCLK_DEFAULT
        };

        ESP_ERROR_CHECK(uart_param_config(PORT_NUM, &uart_config));
        ESP_ERROR_CHECK(uart_set_pin(PORT_NUM, TXD, RXD, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
        ESP_ERROR_CHECK(uart_driver_install(PORT_NUM, uart_buffer_size, uart_buffer_size, 10, &uart_queue, 0));
    }

    void begin() {
        xTaskCreate(echo_task, "uart_echo_task", STACK_SIZE, this, 10, NULL);
    }

    void sendData() {
        uart_write_bytes(PORT_NUM, test_str, strlen(test_str));
    }

    void receiveData() {
        uint8_t data[128];
        ESP_ERROR_CHECK(uart_get_buffered_data_len(UART_NUM_2, (size_t*)&length));
        length = uart_read_bytes(PORT_NUM, data, length-1, 1000 / portTICK_PERIOD_MS);

        if (length) {
            data[length] = '\0';
            ESP_LOGI(TAG, "Recv str: %s", (char *) data);
            uart_flush(PORT_NUM);
        }
    }

    static void echo_task(void *arg) {
        HardwareUart *serial = (HardwareUart*)arg;

        while (1) {
            serial->sendData();
            serial->receiveData();
        }
    }
};

extern "C" {
    void app_main(void) {
        HardwareUart serial;
        serial.begin();
    }
}

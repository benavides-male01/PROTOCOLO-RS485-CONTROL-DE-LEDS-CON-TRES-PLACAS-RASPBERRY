#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"

#define UART_ID uart1
#define RX_PIN 5
#define LED1 15


bool led_on = false;
char instruccion;
char direccion;

int main() {
    stdio_init_all();
    uart_init(UART_ID, 9600);
    gpio_set_function(RX_PIN, GPIO_FUNC_UART);

    gpio_init(LED1);
    gpio_set_dir(LED1, GPIO_OUT);

    while (1) {
        if (uart_is_readable(UART_ID)) {
             direccion = uart_getc(UART_ID);
            if (direccion == 0x01) {
                while(!uart_is_readable(UART_ID));
                instruccion = uart_getc(UART_ID);
                if(instruccion == 0x10){
                    led_on = !led_on;
                    gpio_put(LED1, led_on);
                }
            }
        }
    }
}
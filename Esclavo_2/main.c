#include <stdio.h>
#include "pico/stdlib.h"
#include "stdlib.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include "systick.h"

#define UART_ID uart1
#define RX_PIN 5
#define LED2 15

bool parpadeo = false;
bool led_on = false;
bool led_on2 = false;
uint32_t ultimo_cambio = 0;
char instruccion;
char direccion;
char dato;

int main() {
    stdio_init_all();
    init_systick();

    uart_init(UART_ID, 9600);
    gpio_set_function(RX_PIN, GPIO_FUNC_UART);

    gpio_init(LED2);
    gpio_set_dir(LED2, GPIO_OUT);

    while (1) {
        if (uart_is_readable(UART_ID)) {
            direccion = uart_getc(UART_ID);
            if(direccion  == 0x02 ){
                while(!uart_is_readable(UART_ID));
              instruccion = uart_getc(UART_ID);
              if (instruccion == 0x10) {
                parpadeo = false;
                led_on = !led_on;
                gpio_put(LED2, led_on);
            } else if (instruccion == 0x20) {
                parpadeo = true;
            }
         }
     }

        if ((parpadeo) && (get_systick() - ultimo_cambio > 500)) {
            ultimo_cambio = get_systick();
            led_on2 = !led_on2;
            gpio_put(LED2, led_on2);
        }
    }
}
#include "hardware.h"
#include "pico/stdlib.h"
#include "stdio.h"
#include "hardware/uart.h"
#include "funciones.h"
#include "systick.h"

uint16_t delay1 = 0, delay2 = 0;
const uint PINS[] = {P1_PIN, P2_PIN};

// Callback de interrupción para los pulsadores
void gpio_callback(uint gpio, uint32_t event_mask) {
    if ((gpio == P1_PIN) && (event_mask == GPIO_IRQ_EDGE_FALL)) {
        delay1 = get_systick() + DEBOUNCE;
    }
    if ((gpio == P2_PIN) && (event_mask == GPIO_IRQ_EDGE_FALL)) {
        delay2 = get_systick() + DEBOUNCE;
    }
}
// Configura los pines de entrada, salida y RS485
void setup_gpio(void) {

    // Configurar pulsadores
    
    for (int i = 0; i < 2; i++) {
        gpio_init(PINS[i]);
        gpio_set_dir(PINS[i], GPIO_IN);
        gpio_set_pulls(PINS[i],true,false);
        gpio_pull_up(PINS[i]); // Activar pull-up interno
        gpio_set_input_hysteresis_enabled(PINS[i], true);
        gpio_set_irq_enabled_with_callback(PINS[i], GPIO_IRQ_EDGE_FALL, true, gpio_callback);
    }
    stdio_init_all();
    init_systick();
}

// Configura UART0 para comunicación RS485
void setup_rs485(void) {
    uart_init(UART_ID_1, 9600); // Velocidad 9600 baudios
    gpio_set_function(RS485_TX_PIN, GPIO_FUNC_UART);
}

// Función para enviar un comando a un esclavo
void enviar_comando(uint8_t id, uint8_t comando) {
    sleep_ms(5);               // Pequeña espera para estabilizar
    
    uart_putc(UART_ID_1, id);      // Enviar ID del destinatario
    uart_putc(UART_ID_1, comando); // Enviar el comando

    sleep_ms(5);
    printf("Enviado ID: %02X, CMD: %02X\n", id, comando);
}


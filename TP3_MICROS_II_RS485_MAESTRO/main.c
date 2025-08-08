#include "pico/stdlib.h"
#include "funciones.h"
#include "systick.h"

uint8_t pulsador1, pulsador2, id, comando;

int main() {
    setup_gpio();   // Inicializar GPIOs
    setup_rs485();  // Inicializar RS485

    while (1) {
        pulsador1 = gpio_get(P1_PIN);
        pulsador2 = gpio_get(P2_PIN);
    
        if ((delay1) && (delay1 <= get_systick())) {
            delay1 = 0;
            if (pulsador1 == 0) {
                enviar_comando(ID_ESCLAVO_1, CAMBIO_ESTADO_LED);
                enviar_comando(ID_ESCLAVO_2, CAMBIO_ESTADO_LED);
            }
        }
    
        if ((delay2) && (delay2 <= get_systick())) {
            delay2 = 0;
            if (pulsador2 == 0) {
                enviar_comando(ID_ESCLAVO_2, PARPADEO_LED);
            }
        }
    }
}
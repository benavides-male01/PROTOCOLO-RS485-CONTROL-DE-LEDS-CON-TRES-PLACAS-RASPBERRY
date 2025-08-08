#ifndef _FUNCIONES_H_
#define _FUNCIONES_H_

#include <stdint.h>
#include <stdbool.h>
#include "hardware.h"

extern const uint PINS[];

extern uint16_t delay1, delay2;

// Identificadores de placas (IDs)
#define ID_ESCLAVO_1   0x01
#define ID_ESCLAVO_2   0x02
#define ID_BROADCAST   0xFF    // Enviar a todos

#define DEBOUNCE 25

void gpio_callback(uint gpio, uint32_t event_mask);

// Comandos que se pueden enviar
#define CAMBIO_ESTADO_LED 0x10    // Cambiar estado del LED
#define PARPADEO_LED  0x20    // Hacer parpadear el LED

// Prototipos de funciones
void setup_gpio(void);                  // Configura todos los pines
void setup_rs485(void);                  // Configura RS485 
void enviar_comando(uint8_t id, uint8_t comando);   // Enviar un comando

#endif

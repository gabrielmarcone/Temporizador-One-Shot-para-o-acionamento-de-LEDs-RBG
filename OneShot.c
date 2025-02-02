#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Definição dos LEDs
#define LED_GREEN 11
#define LED_BLUE 12
#define LED_RED 13

// Definição do botão A
#define BUTTON_A 5

// Função para inicializar as GPIOs
void init_gpio() {
    // Leds
    gpio_init(LED_GREEN);
    gpio_init(LED_BLUE);
    gpio_init(LED_RED);
    // Botão
    gpio_init(BUTTON_A);

    // Direção dos pinos dos LEDs
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_set_dir(LED_RED, GPIO_OUT);
    // Direção do pino do botão
    gpio_set_dir(BUTTON_A, GPIO_IN);

    // Configura o resistor de pull-up para o botão
    gpio_pull_up(BUTTON_A);
}

int64_t alarm_callback(alarm_id_t id, void *user_data) {
    return 0;
}

int main() {
    stdio_init_all();
    init_gpio();

    add_alarm_in_ms(2000, alarm_callback, NULL, false);

    while (true) {
    }
}
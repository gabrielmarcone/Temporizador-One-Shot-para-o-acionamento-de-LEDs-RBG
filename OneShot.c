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
    gpio_init(LED_GREEN);
    gpio_init(LED_BLUE);
    gpio_init(LED_RED);
    gpio_init(BUTTON_A);

    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(BUTTON_A, GPIO_IN);

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
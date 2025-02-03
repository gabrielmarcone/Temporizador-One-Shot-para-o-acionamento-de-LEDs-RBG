#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/gpio.h"

// Definição dos LEDs
#define LED_GREEN 11
#define LED_BLUE 12
#define LED_RED 13

// Definição do botão A
#define BUTTON_A 5

// Variável para controle da sequência
volatile bool sequence_running = false;

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

// Função de debounce
bool debounce_button() {
    static uint32_t last_time = 0;
    uint32_t current_time = to_ms_since_boot(get_absolute_time());
    if (current_time - last_time < 50) {
        return false;
    }
    last_time = current_time;
    return true;
}

int main() {
    stdio_init_all();
    init_gpio();

    // Configuração da interrupção do botão
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &button_callback);

    while (true) {
        tight_loop_contents();
    }
}
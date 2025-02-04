#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"
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

// Callback para desligar o último LED
int64_t turn_off_last_led(alarm_id_t id, void *user_data) {
    gpio_put(LED_GREEN, 0);
    sequence_running = false; // Permite novo acionamento do botão
    return 0;
}

// Callback para desligar o segundo LED
int64_t turn_off_second_led(alarm_id_t id, void *user_data) {
    gpio_put(LED_RED, 0);
    add_alarm_in_ms(3000, turn_off_last_led, NULL, false);
    return 0;
}

// Callback para desligar o primeiro LED
int64_t turn_off_first_led(alarm_id_t id, void *user_data) {
    gpio_put(LED_BLUE, 0);
    add_alarm_in_ms(3000, turn_off_second_led, NULL, false);
    return 0;
}

// Callback de temporização inicial
int64_t start_sequence(alarm_id_t id, void *user_data) {
    gpio_put(LED_RED, 1);
    gpio_put(LED_BLUE, 1);
    gpio_put(LED_GREEN, 1);
    add_alarm_in_ms(3000, turn_off_first_led, NULL, false);
    return 0;
}

// Função para interrupção do botão
void button_callback(uint gpio, uint32_t events) {
    if (!sequence_running && debounce_button()) {
        sequence_running = true;
        add_alarm_in_ms(10, start_sequence, NULL, false);
    }
}

int main() {
    stdio_init_all();
    init_gpio();

    // Configuração da interrupção do botão
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &button_callback);

    // Configura o clock do sistema para operar em 100MHz
    set_sys_clock_khz(100000, false);

    while (true) {
        tight_loop_contents();
    }
}
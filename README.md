# Temporizador de um Disparo (One Shot) - Raspberry Pi Pico W

## 📌 Descrição do Projeto
Este projeto implementa um **sistema de temporização** para acionar e desligar três LEDs (azul, vermelho e verde) utilizando um **botão de pressão (pushbutton)** conectado ao **Raspberry Pi Pico W**. O código foi desenvolvido utilizando o **Pico SDK** e trabalha com **interrupções, debounce de software e timers assíncronos** para controlar o fluxo de acionamento e desligamento dos LEDs.

## 🎯 Objetivo
Criar um temporizador baseado na função `add_alarm_in_ms()` para **controlar o acionamento dos LEDs** de forma sequencial a partir do clique em um botão.

## 🛠 Componentes Utilizados
- **Microcontrolador**: Raspberry Pi Pico W
- **03 LEDs**: Verde (GPIO 11), Azul (GPIO 12), Vermelho (GPIO 13)
- **03 Resistores**: 330Ω (um para cada LED)
- **Botão Pushbutton**: Conectado ao GPIO 5

## 🏗 Estrutura do Código

### 🔹 1. Inicialização das GPIOs
A função `init_gpio()` configura os pinos dos LEDs como **saída** e do botão como **entrada**, ativando um **resistor pull-up** interno;

### 🔹 2. Debounce do Botão
A função `debounce_button()` evita leituras errôneas causadas pela vibração mecânica do botão.
Se o botão for pressionado antes de **50ms**, a leitura é ignorada;

### 🔹 3. Controle dos LEDs com Temporizadores
Os LEDs são acesos e desligados em sequência usando `add_alarm_in_ms()`, que chama funções **assíncronas** para desligá-los após um intervalo de tempo:

1️⃣ **Acende todos os LEDs** → `start_sequence()`;

2️⃣ **Desliga LED Azul após 3s** → `turn_off_first_led()`;

3️⃣ **Desliga LED Vermelho após mais 3s** → `turn_off_second_led()`;

4️⃣ **Desliga LED Verde após mais 3s e libera o botão** → `turn_off_last_led()`;

### 🔹 4. Interrupção do Botão
A função `button_callback()` inicia a sequência ao pressionar o botão:
```c
void button_callback(uint gpio, uint32_t events) {
    if (!sequence_running && debounce_button()) {
        sequence_running = true;
        add_alarm_in_ms(10, start_sequence, NULL, false);
    }
}
```

### 🔹 5. Configuração da Interrupção
No `main()`, a interrupção do botão é configurada para **detectar o pressionamento** e iniciar a sequência de LEDs:
```c
int main() {
    stdio_init_all();
    init_gpio();
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &button_callback);
    while (true) {
        tight_loop_contents();
    }
}
```

## 🔄 Fluxo Completo do Código
1️⃣ **Botão pressionado** → `button_callback()` é chamado.
2️⃣ **Verifica debounce** e inicia `start_sequence()`.
3️⃣ **Acende todos os LEDs**.
4️⃣ **Após 3s**, `turn_off_first_led()` desliga o **LED Azul**.
5️⃣ **Após 3s**, `turn_off_second_led()` desliga o **LED Vermelho**.
6️⃣ **Após 3s**, `turn_off_last_led()` desliga o **LED Verde** e libera o botão.
7️⃣ **Agora, o botão pode ser pressionado novamente para repetir a sequência.**

## 🎥 Vídeo explicativo
Aqui segue o link de um vídeo que ilustra o funcionamento do código na placa e explica brevemente a estrutura do código:

- **[Link para acessar o vídeo](https://drive.google.com/file/d/1UFzD7G1h8zX7dzQXiKYzgtq9-8yzOVQW)**

## 📌 Conclusão
✔ **O projeto implementa um temporizador assíncrono** para controlar LEDs com interrupções e debounce de software.
✔ **O botão só pode acionar o sistema quando o último LED for desligado**, garantindo uma execução correta.
✔ **Uso eficiente de timers (`add_alarm_in_ms()`) para uma execução não bloqueante.**

Este projeto é ideal para entender conceitos de **interrupções, debounce de botões e controle de temporizadores no Raspberry Pi Pico W**. 🚀
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "matriz_leds.h"
#include <stdio.h>

#define LED_PIN 13  // Led vermelho
#define BUTTON_A 6  // Botão A
#define BUTTON_B 5  // Botão B

volatile bool button_a_pressed = false;
volatile bool button_b_pressed = false;

const Matriz_leds_config zero = {
    // Verde médio 
    {{0.0, 0.5, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.0, 0.0}},
    {{0.0, 0.5, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.0, 0.0}},
    {{0.0, 0.5, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.0, 0.0}},
    {{0.0, 0.5, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.0, 0.0}},
    {{0.0, 0.5, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.0, 0.0}}
};
const Matriz_leds_config one = {
    // Azul médio com formato tradicional do número 1
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.5}, {0.0, 0.0, 0.5}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0 - parte superior do 1
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.5}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.5}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.5}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.5}, {0.0, 0.0, 0.5}, {0.0, 0.0, 0.5}, {0.0, 0.0, 0.0}}  // Linha 4 - base do 1
};
const Matriz_leds_config two = {
    // Amarelo médio 
    {{0.5, 0.5, 0.0}, {0.5, 0.5, 0.0}, {0.5, 0.5, 0.0}, {0.5, 0.5, 0.0}, {0.0, 0.0, 0.0}},
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.5, 0.0}, {0.0, 0.0, 0.0}},
    {{0.5, 0.5, 0.0}, {0.5, 0.5, 0.0}, {0.5, 0.5, 0.0}, {0.5, 0.5, 0.0}, {0.0, 0.0, 0.0}},
    {{0.5, 0.5, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},
    {{0.5, 0.5, 0.0}, {0.5, 0.5, 0.0}, {0.5, 0.5, 0.0}, {0.5, 0.5, 0.0}, {0.0, 0.0, 0.0}}
};

const Matriz_leds_config three = {
    // Magenta médio 
    {{0.5, 0.0, 0.5}, {0.5, 0.0, 0.5}, {0.5, 0.0, 0.5}, {0.5, 0.0, 0.5}, {0.0, 0.0, 0.0}},
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.0, 0.5}, {0.0, 0.0, 0.0}},
    {{0.5, 0.0, 0.5}, {0.5, 0.0, 0.5}, {0.5, 0.0, 0.5}, {0.5, 0.0, 0.5}, {0.0, 0.0, 0.0}},
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.0, 0.5}, {0.0, 0.0, 0.0}},
    {{0.5, 0.0, 0.5}, {0.5, 0.0, 0.5}, {0.5, 0.0, 0.5}, {0.5, 0.0, 0.5}, {0.0, 0.0, 0.0}}
};

const Matriz_leds_config four = {
    // Ciano médio 
    {{0.0, 0.5, 0.5}, {0.0, 0.5, 0.5}, {0.0, 0.0, 0.0}, {0.0, 0.5, 0.5}, {0.0, 0.0, 0.0}},
    {{0.0, 0.5, 0.5}, {0.0, 0.5, 0.5}, {0.0, 0.0, 0.0}, {0.0, 0.5, 0.5}, {0.0, 0.0, 0.0}},
    {{0.0, 0.5, 0.5}, {0.0, 0.5, 0.5}, {0.0, 0.5, 0.5}, {0.0, 0.5, 0.5}, {0.0, 0.0, 0.0}},
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.5, 0.5}, {0.0, 0.0, 0.0}},
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.5, 0.5}, {0.0, 0.0, 0.0}}
};

const Matriz_leds_config five = {
    // Branco médio 
    {{0.5, 0.5, 0.5}, {0.5, 0.5, 0.5}, {0.5, 0.5, 0.5}, {0.5, 0.5, 0.5}, {0.0, 0.0, 0.0}},
    {{0.5, 0.5, 0.5}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},
    {{0.5, 0.5, 0.5}, {0.5, 0.5, 0.5}, {0.5, 0.5, 0.5}, {0.5, 0.5, 0.5}, {0.0, 0.0, 0.0}},
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.5, 0.5}, {0.0, 0.0, 0.0}},
    {{0.5, 0.5, 0.5}, {0.5, 0.5, 0.5}, {0.5, 0.5, 0.5}, {0.5, 0.5, 0.5}, {0.0, 0.0, 0.0}}
};

const Matriz_leds_config six = {
    // Vermelho médio
    {{0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}},
    {{0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},
    {{0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}},
    {{0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}},
    {{0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.0, 0.0}}
};

const Matriz_leds_config seven = {
    // Verde médio
    {{0.0, 0.5, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.0, 0.0}},
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}},
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}
};

const Matriz_leds_config eight = {
    // Azul médio
    {{0.0, 0.0, 0.5}, {0.0, 0.0, 0.5}, {0.0, 0.0, 0.5}, {0.0, 0.0, 0.5}, {0.0, 0.0, 0.0}},
    {{0.0, 0.0, 0.5}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.5}, {0.0, 0.0, 0.0}},
    {{0.0, 0.0, 0.5}, {0.0, 0.0, 0.5}, {0.0, 0.0, 0.5}, {0.0, 0.0, 0.5}, {0.0, 0.0, 0.0}},
    {{0.0, 0.0, 0.5}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.5}, {0.0, 0.0, 0.0}},
    {{0.0, 0.0, 0.5}, {0.0, 0.0, 0.5}, {0.0, 0.0, 0.5}, {0.0, 0.0, 0.5}, {0.0, 0.0, 0.0}}
};

const Matriz_leds_config nine = {
    // Amarelo médio
    {{0.5, 0.5, 0.0}, {0.5, 0.5, 0.0}, {0.5, 0.5, 0.0}, {0.5, 0.5, 0.0}, {0.0, 0.0, 0.0}}, // Linha 0
    {{0.5, 0.5, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.5, 0.0}, {0.0, 0.0, 0.0}}, // Linha 1
    {{0.5, 0.5, 0.0}, {0.5, 0.5, 0.0}, {0.5, 0.5, 0.0}, {0.5, 0.5, 0.0}, {0.0, 0.0, 0.0}}, // Linha 2
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.5, 0.0}, {0.0, 0.0, 0.0}}, // Linha 3
    {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.5, 0.5, 0.0}, {0.0, 0.0, 0.0}}  // Linha 4
};
const Matriz_leds_config *nums[] = {&zero, &one, &two, &three, &four, &five, &six, &seven, &eight, &nine};

// Função para inicializar os pinos
void init_gpios() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A); // pull-up resistor

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B); // pull-up resistor
}

// Função para fazer o LED piscar
void blink_red_led() {
    gpio_put(LED_PIN, 1);
    sleep_ms(100);
    gpio_put(LED_PIN, 0);
    sleep_ms(100);
}

// Função de callback para os botões
void button_press_handler(uint gpio, uint32_t events) {
    if (gpio == BUTTON_A) {
        button_a_pressed = true;
    } else if (gpio == BUTTON_B) {
        button_b_pressed = true;
    }
}

// Função de debounce
void debounce(int delay_ms) {
    sleep_ms(delay_ms);
}

// Função para atualizar o índice do número
void update_index(bool increment, int *i) {
    if (increment && *i < 9) {
        (*i)++;
    } else if (!increment && *i > 0) {
        (*i)--;
    }
}

// Função principal
int main() {
    stdio_init_all();
    init_gpios();

    int i = 0;  // Inicializa o índice do número
    PIO pio = pio0;
    uint sm = configurar_matriz(pio);

    imprimir_desenho(nums[i], pio, sm);  // Exibe o número 0 inicialmente

    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &button_press_handler);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &button_press_handler);

    while (true) {
        blink_red_led();

        if (button_a_pressed) {
            button_a_pressed = false;
            update_index(true, &i);  // Incrementa o número
            debounce(75);  // Debounce
            imprimir_desenho(nums[i], pio, sm);
        } else if (button_b_pressed) {
            button_b_pressed = false;
            update_index(false, &i);  // Decrementa o número
            debounce(50);  // Debounce
            imprimir_desenho(nums[i], pio, sm);
        }
    }

    return 0;
}
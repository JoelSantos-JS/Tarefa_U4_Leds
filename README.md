# Projeto de Controle de LEDs e Botões com RP2040 e BitDogLab

Este projeto foi desenvolvido para a placa de desenvolvimento **BitDogLab** utilizando o microcontrolador **RP2040**. O objetivo é implementar a manipulação de LEDs e botões, demonstrando o uso de interrupções, controle de LEDs WS2812, debouncing via software e o uso de resistores de pull-up internos.

## Objetivos

- **Compreender o funcionamento das interrupções** em microcontroladores.
- **Tratar o fenômeno de bouncing** de botões utilizando debouncing via software.
- **Controlar LEDs comuns e LEDs endereçáveis WS2812**.
- **Trabalhar com resistores de pull-up internos** em botões de acionamento.
- **Desenvolver um projeto funcional** integrando hardware e software.

## Componentes Utilizados

- **Matriz 5x5 de LEDs (WS2812)**: Conectada à GPIO 7.
- **LED RGB**: Conectado às GPIOs 11, 12 e 13.
- **Botão A**: Conectado à GPIO 5.
- **Botão B**: Conectado à GPIO 6.

## Funcionalidades

1. **LED vermelho piscando**: O LED vermelho do LED RGB pisca continuamente 5 vezes por segundo.
2. **Botão A (Incremento)**: Cada vez que o Botão A for pressionado, o número exibido na matriz de LEDs aumenta em 1.
3. **Botão B (Decremento)**: Cada vez que o Botão B for pressionado, o número exibido na matriz de LEDs diminui em 1.
4. **Exibição de números na matriz WS2812**: A matriz de LEDs exibe os números de 0 a 9, um por vez, com a exibição alterada a cada pressão de um dos botões.

## Requisitos

- **Uso de interrupções (IRQ)**: Todas as funcionalidades relacionadas aos botões devem ser implementadas utilizando interrupções.
- **Debouncing via software**: O tratamento de bouncing dos botões deve ser feito no software.
- **Controle de LEDs**: Deve ser demonstrado o uso de LEDs comuns e LEDs WS2812, com controle adequado.
- **Estrutura e organização do código**: O código deve ser bem estruturado e comentado para facilitar o entendimento.

## Como Funciona

### LEDs

- O LED vermelho do RGB piscando é controlado com um temporizador para acionar interrupções a cada 200ms, garantindo o piscar a uma taxa de 5 vezes por segundo.
- A matriz 5x5 de LEDs é usada para exibir números de 0 a 9. Cada número é gerado com base no controle de segmentos de LEDs e exibido conforme o valor da variável de incremento/decremento.

### Botões

- Os botões A e B utilizam interrupções para detectar pressões. Para evitar problemas de bouncing, o código implementa o **debouncing via software**, garantindo que cada pressionamento de botão seja detectado corretamente.
- O Botão A incrementa o número mostrado na matriz e o Botão B decrementa esse número.

### Debouncing

- A técnica de **debouncing via software** foi utilizada para garantir que o estado do botão seja estabilizado antes de ser processado, evitando múltiplas leituras do mesmo pressionamento.

## Como Rodar o Projeto

1. **Clone o repositório**:
   ```bash
   git clone <URL-do-repositório>
   cd <diretório-do-projeto>

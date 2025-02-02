# Projeto de Controle de LEDs e Botões com RP2040 e BitDogLab

Este projeto foi desenvolvido para a placa de desenvolvimento **BitDogLab** utilizando o microcontrolador **RP2040**. O objetivo é implementar a manipulação de LEDs e botões, demonstrando o uso de interrupções, controle de LEDs WS2812, debouncing via software e o uso de resistores de pull-up internos.

![Esquema do Projeto](https://i.ibb.co/n8V0yChd/photo-2025-02-02-07-53-00.jpg)

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

### 🔴 LEDs

- O **LED vermelho do RGB** pisca continuamente com uma frequência de **5 vezes por segundo**.
- A **matriz de LEDs 5x5 WS2812** exibe os números de **0 a 9**. Cada número possui um formato pré-definido e cores associadas.

### 🎮 Botões

- O **Botão A** avança para o próximo número na matriz.
- O **Botão B** retorna para o número anterior.
- As interrupções garantem que os botões sejam detectados instantaneamente.

### ⏳ Debouncing

- O efeito de bouncing dos botões é tratado via **software**, garantindo que cada pressionamento seja processado apenas uma vez.

- 📌 Conclusão
Este projeto demonstrou como controlar LEDs e botões usando um RP2040 na placa BitDogLab, aplicando técnicas avançadas como:

Interrupções para botões
Debouncing via software
Controle de LEDs WS2812
Uso de GPIOs com resistores de pull-up internos


🎥 Vídeo Explicativo
Para uma explicação mais detalhada, assista ao vídeo abaixo:



🔗 Assistir no YouTube: https://www.youtube.com/watch?v=CrZgHFkFbEg&ab_channel=GoldenBoy


## Como Rodar o Projeto

### 📥 1. Clone o repositório
```bash
git clone <URL-do-repositório>
cd <diretório-do-projeto>



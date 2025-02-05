# Programa de Controle de LEDs com Botão e Alarmes no Raspberry Pi Pico

Este programa controla LEDs conectados aos pinos GPIO 11, 12 e 13 do Raspberry Pi Pico. Quando um botão é pressionado, os LEDs acendem sequencialmente. Após 3 segundos, o programa desliga os LEDs de forma sequencial, com a repetição desse ciclo.

## Requisitos

- **Raspberry Pi Pico** ou outro microcontrolador compatível com a biblioteca `pico/stdlib.h`.
- Um **botão** conectado ao pino GPIO 5.
- **LEDs** conectados aos pinos GPIO 11, 12 e 13 (ou modifique os pinos conforme necessário).
- **Resistor Pull-Up** para o pino do botão (ou use o resistor interno do Raspberry Pi Pico).

## Descrição do Funcionamento

### Comportamento do programa:

1. **Pressionar o Botão**: Quando o botão conectado ao pino GPIO 5 é pressionado, o programa liga os LEDs conectados aos pinos GPIO 11, 12 e 13.
   
2. **Sequência de Desligamento dos LEDs**: Após 3 segundos, o programa desliga os LEDs de forma sequencial, começando pelo pino GPIO 11, depois GPIO 12 e, finalmente, GPIO 13.

3. **Repetição do Ciclo**: O ciclo de desligamento dos LEDs será repetido mais duas vezes, totalizando 3 execuções (uma inicial e mais duas repetições após 3 segundos).

4. **Reset do Estado**: Após 3 ciclos de desligamento, todos os LEDs são apagados, e o estado do programa é resetado.

## Configuração do Circuito

- **Botão**: Conecte o botão ao pino GPIO 5 e ao GND. O pino será lido como `LOW` quando pressionado, e como `HIGH` quando não pressionado.
- **LEDs**: Conecte os LEDs aos pinos GPIO 11, 12 e 13. Use resistores limitadores de corrente (por exemplo, 220Ω ou 330Ω) para proteger os LEDs.
  

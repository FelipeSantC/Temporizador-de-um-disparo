#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

int Leds = 11;// Variaveel da pinagem dos leds
const uint BUTTON_PIN = 5; // Define o pino GPIO 5 para ler o estado do botão.
bool led_on = false; // Define o estado dos leds
int repeat_count = 0; // Variável para controlar quantas vezes o alarme foi disparado

int64_t turn_off_callback(alarm_id_t id, void *user_data)
{
    printf("Leds apagando.\n");
    // Desliga o LED configurando o pino LED_PIN para nível baixo.
    // Apaga o led anterior que foi acionado
    if (Leds < 14)
    {
        printf("Pino: %d , desativado.\n", Leds);
        gpio_put(Leds, !led_on);
        Leds++;
    }

    // Incrementa o contador de repetições
    repeat_count++;

    // Verifica se o alarme deve se repetir mais 2 vezes (já foi disparado uma vez, então queremos mais 2)
    if (repeat_count < 3)
    {
        // Reagende o alarme para ser disparado novamente em 3 segundos
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);
    }
    else
    {
        // Após 3 execuções, não repete mais
        printf("Alarme não será mais repetido, Todos os Leds foram desativados.\n");
        led_on = false; // Estado dos leds retorna ao original
        Leds = 11;// Pinagem retorna a inicial
        repeat_count = 0;//Contador zera
        return 0; // Retorna 0 para indicar que o alarme não deve se repetir
    }

    // Retorna 0 para indicar que o alarme não deve se repetir.
    return 0;
}

int main()
{
    stdio_init_all();

    
    gpio_init(BUTTON_PIN); //Habilita o pino
    gpio_set_dir(BUTTON_PIN, GPIO_IN);//Seta o botão como entrada

    // Habilita o resistor pull-up interno para o pino do botão.
    // Isso garante que o pino seja lido como alto (3,3 V) quando o botão não está pressionado.
    gpio_pull_up(BUTTON_PIN);

    for (Leds; Leds < 14; Leds++)
    {
        gpio_init(Leds);              // Inicializa o pino LED
        gpio_set_dir(Leds, GPIO_OUT); // Define o pino como saída
    }
    
    while (true)
    {
        // Verifica se o botão foi pressionado (nível baixo no pino) e se o LED não está ativo.
        if (gpio_get(BUTTON_PIN) == 0 && led_on == false)
        {
            // Adiciona um pequeno atraso para debounce, evitando leituras errôneas.
            sleep_ms(50);

            // Verifica novamente o estado do botão após o debounce.
            if (gpio_get(BUTTON_PIN) == 0)
            {
                // Liga o LED configurando o pino LED_PIN para nível alto.
                // Inicializa todos os pinos dos leds como saida e aciona os mesmos
                printf("Inicialização.\n");
                led_on = true;
                for (Leds = 11; Leds < 14; Leds++)
                {
                    gpio_put(Leds, true);         // Liga o LED no pino correspondente
                }
                Leds = 11;
                // Agenda um alarme para desligar o LED após 3 segundos (3000 ms).
                // A função 'turn_off_callback' será chamada após esse tempo.
                add_alarm_in_ms(3000, turn_off_callback, NULL, false);
            }
        }
        // Introduz uma pequena pausa de 10 ms para reduzir o uso da CPU.
        // Isso evita que o loop seja executado muito rapidamente e consuma recursos desnecessários.
        sleep_ms(10);
    }

    return 0;
}

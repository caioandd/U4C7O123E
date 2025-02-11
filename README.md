# U4C7O123E - PWM

Este projeto tem como objetivo a implementação de um sistema de controle de angulação de um servomotor utilizando o módulo PWM do microcontrolador RP2040, presente na placa Raspberry Pi Pico W. A simulação será realizada no ambiente online Wokwi.

O controle do servo será feito por meio de um sinal PWM configurado para uma frequência de aproximadamente 50Hz (período de 20ms). Variando o ciclo de trabalho do PWM, o servo será posicionado em diferentes ângulos, incluindo 0º, 90º e 180º. Após, se iniciará um movimento períodico suave cíclico entre 0º e 180º.

Para testes físicos, podemos atribuir o programa PWM em um LED para que seja possível visualizá-lo na placa BitDogLab.

## Componentes necessários

1) Microcontrolador Raspberry Pi Pico W;

2) Servomotor padrão (Wokwi) ou LED;

4) Resistor de 330 Ohms.

## Modelagem

A frequência do PWM na Raspberry Pi Pico é determinada pela seguinte equação:
```math
$$
f_{\text{PWM}} = \frac{f_{\text{clock}}}{\text{divisor} \times (\text{WRAP} + 1)}
$$

Rearranjando a equação, temos:

$$
\text{divisor} \times (\text{WRAP} + 1) =  \frac{f_{\text{clock}}}{f_{\text{PWM}}}
$$

Substituindo os valores:

$$
\text{divisor} \times (\text{WRAP} + 1) =  \frac{125000000}{50}
$$

Considerando o divisor inteiro como 100, teremos:

$$
100 \times (\text{WRAP} + 1) = \frac{125000000}{50}
$$

Isolando WRAP:

$$
(\text{WRAP} + 1) = \frac{25000000}{100}
$$

$$
\text{WRAP} = 250000 - 1
$$

$$
\text{WRAP} = 24999
$$
```
## Intruções de uso

1) Como a placa BitDogLab já tem um LED azul, deve-se utilizar:
```ruby
 #define PIN_SERVO 12
```
Caso queira utilizar o PWM no servomotor, como na simulação, deve-se utilizar:
```ruby
 #define PIN_SERVO 22
```
Em que 12 respresenta a GPIO do LED azul e 22 respresenta a GPIO escolhida para o servomotor.

2) Para mudança de posição, fazemos uma modificação no tamanho do duty cicle utilizando, sendo:

* 2.400µs (0,12%): Posiciona o servo em 180º (aguarda 5s).

* 1.470µs (0,0735%): Posiciona o servo em 90º (aguarda 5s).

* 500µs (0,025%): Posiciona o servo em 0º (aguarda 5s).

Após, inicia-se um movimento infinito que varia entre:

* 500µs (0,025%): Posiciona o servo em 0º (aguarda 0.5s).

* 2.400µs (0,12%): Posiciona o servo em 180º (aguarda 0.5s).
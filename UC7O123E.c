#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define PIN_SERVO 22 // LED AZUL = 12, SERVO = 22
#define WRAP_PERIOD 24999 // Valor do WRAP
#define PWM_DIVISER 100.0 // Valor do divisor de clock do PWM

uint16_t ANGULO_180 = 3000; // Valor correspondente a 0,12% do Duty Cicle (180 graus)
uint16_t ANGULO_90 = 1837; // Valor correspondente a 0,0725% do Duty Cicle (90 graus)
uint16_t ANGULO_0 = 624; // Valor correspondente a 0,025% do Duty Cicle (0 graus)
uint16_t POS_SERVO = 624; // Valor inicial de DC
uint8_t estado = 0; //Etapa do ciclo

// Chamada primária
void pwm_setup();
void mov_servo();
void loop_servo();

int main(){

    stdio_init_all();
    pwm_setup(); 

    mov_servo();
    loop_servo();
}

void pwm_setup(){
    gpio_set_function(PIN_SERVO, GPIO_FUNC_PWM); // GPIO como PWM
    uint slice = pwm_gpio_to_slice_num(PIN_SERVO); // Slice da GPIO
    pwm_set_clkdiv(slice, PWM_DIVISER); // Divisor de clock do PWM
    pwm_set_wrap(slice, WRAP_PERIOD); // WRAP
    pwm_set_enabled(slice, true); // Liga o PWM
}

void loop_servo(){
    while (true) {
        uint16_t SERVO_STEP = 5;
        uint POS_SERVO;
        // Movimento de 0° para 180°
        for (POS_SERVO = ANGULO_0; POS_SERVO <= ANGULO_180; POS_SERVO += SERVO_STEP) {
            pwm_set_gpio_level(PIN_SERVO, POS_SERVO); //Nivel do PWN (% de Duty)
            sleep_ms(10);
        }
        sleep_ms(500); // Pausa de 0,5s no topo

        // Movimento de 180° para 0°
        for (POS_SERVO = ANGULO_180; POS_SERVO >= ANGULO_0; POS_SERVO -= SERVO_STEP) {
            pwm_set_gpio_level(PIN_SERVO, POS_SERVO); //Nivel do PWN (% de Duty)
            sleep_ms(10);
        }
        sleep_ms(500); // Pausa no topo
    }
}

void mov_servo(){
    uint16_t SERVO_STEP = 500;
    while (estado != 3)
    {
        if (estado == 0){
        POS_SERVO += SERVO_STEP; // Incrementa posição do servo até o angulo de 180
        if (POS_SERVO >= ANGULO_180){
            POS_SERVO=ANGULO_180; 
            pwm_set_gpio_level(PIN_SERVO, POS_SERVO); // Nivel do PWN (% de Duty)
            estado = 1; // Alterna para posição seguinte
            sleep_ms(5000); // Pausa no topo
        }
        }else if (estado == 1){
            POS_SERVO -= SERVO_STEP; // Decrementa a posição do servo até o angulo de 90
            if (POS_SERVO <= ANGULO_90){
                POS_SERVO=ANGULO_90;
                pwm_set_gpio_level(PIN_SERVO, POS_SERVO); // Nivel do PWN (% de Duty)
                estado = 2; // Alterna para posição seguinte
                sleep_ms(5000); // Pausa no topo
            }
        }else if (estado == 2){
            POS_SERVO -= SERVO_STEP; // Decrementa a posição do servo até o angulo de 0
            if (POS_SERVO <= ANGULO_0){
                POS_SERVO=ANGULO_0;
                pwm_set_gpio_level(PIN_SERVO, POS_SERVO); //Seta  o duty para a posição do angulo
                sleep_ms(5000); // Pausa no topo
                estado=3;
            }
        }
    }
}
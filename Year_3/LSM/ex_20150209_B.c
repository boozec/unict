#include "stm32_unict_lib.h"
#include <stdio.h>
#define X_VAL 11400

/*
 * RA3    = PB10
 * RA2    = PB4
 * RB0    = PB0
 * RB1    = PC2
 * RA0    = ADC1_IN11
 * -      = PB5
 * +      = PB6
 *
 * ====================
 *
 * Not included POINT B
 */

typedef enum {
    IDLE,
    TURNING_ON,
    TURN_ON
} status_t;

status_t status = IDLE;

int X_ms = X_VAL; /* 'r'*100 */
int Z_ms = 495; /* 'c'*5 */

int high_temperature = 0;
int low_potence = 0;

void
init()
{
    DISPLAY_init();
    GPIO_init(GPIOB);
    GPIO_init(GPIOC);
    GPIO_config_input(GPIOB, 10);
    GPIO_config_EXTI(GPIOB, EXTI10);
    EXTI_enable(EXTI10, FALLING_EDGE);

    GPIO_config_input(GPIOB, 4);
    GPIO_config_EXTI(GPIOB, EXTI4);
    EXTI_enable(EXTI4, FALLING_EDGE);

    GPIO_config_input(GPIOB, 5);
    GPIO_config_EXTI(GPIOB, EXTI5);
    EXTI_enable(EXTI5, FALLING_EDGE);

    GPIO_config_input(GPIOB, 6);
    GPIO_config_EXTI(GPIOB, EXTI6);
    EXTI_enable(EXTI6, FALLING_EDGE);

    GPIO_config_output(GPIOB, 0);
    GPIO_config_output(GPIOC, 2);

    TIM_init(TIM2);
    TIM_set(TIM2, 0);
    TIM_config_timebase(TIM2, 8400, X_VAL * 10);
    TIM_enable_irq(TIM2, IRQ_UPDATE);
    TIM_on(TIM2);

    TIM_init(TIM3);
    TIM_set(TIM3, 0);
    TIM_config_timebase(TIM3, 8400, Z_ms * 10);
    TIM_enable_irq(TIM3, IRQ_UPDATE);
    TIM_on(TIM3);

    ADC_init(ADC1, ADC_RES_8, ADC_ALIGN_RIGHT);
    ADC_channel_config(ADC1, GPIOC, 1, 11);
    ADC_on(ADC1);
    ADC_sample_channel(ADC1, 11);

    CONSOLE_init();
}

int
main()
{
    init();

    int value;
    int adc_read;
    int min = X_VAL - 3000;
    int max = X_VAL + 3000;
    char s[5];

    for (;;) {
        ADC_start(ADC1);
        while (!ADC_completed(ADC1))
            ;

        adc_read = ADC_read(ADC1);
        value = ((adc_read * (max - min)) / 255.0) + min;
        TIM2->ARR = value * 10;

        sprintf(s, "%f", value / 1000.0);
        DISPLAY_puts(0, s);
    }
    return 0;
}

void
EXTI15_10_IRQHandler(void)
{
    if (EXTI_isset(EXTI10)) {
        if (status == IDLE) {
            status = TURNING_ON;
            high_temperature = 0;
        } else if (status == TURN_ON || high_temperature) {
            GPIO_write(GPIOB, 0, 0);
            GPIO_write(GPIOC, 2, 0);
            status = IDLE;
            TIM3->CNT = 0;
            TIM2->CNT = 0;
        }

        EXTI_clear(EXTI10);
    }
}

void
EXTI9_5_IRQHandler(void)
{
    if (EXTI_isset(EXTI5)) {
        if (status == IDLE) {
            Z_ms -= 50;
            TIM3->ARR = Z_ms;
            printf("%.2f ms\n", TIM3->ARR / 10.0);
        }

        EXTI_clear(EXTI5);
    }

    if (EXTI_isset(EXTI6)) {
        if (status == IDLE) {
            Z_ms += 50;
            TIM3->ARR = Z_ms;
            printf("%.2f ms\n", TIM3->ARR / 10.0);
        }

        EXTI_clear(EXTI6);
    }
}

void
EXTI4_IRQHandler(void)
{
    if (EXTI_isset(EXTI4)) {
        if (status == TURNING_ON) {
            high_temperature = 1;
        }
        EXTI_clear(EXTI4);
    }
}

void
TIM2_IRQHandler(void)
{
    if (TIM_update_check(TIM2)) {
        if (status == TURNING_ON && !high_temperature) {
            status = TURN_ON;
            GPIO_write(GPIOB, 0, 1);
            GPIO_write(GPIOC, 2, 0);
        }
        TIM_update_clear(TIM2);
    }
}

void
TIM3_IRQHandler(void)
{
    if (TIM_update_check(TIM3)) {
        if (status == TURNING_ON) {
            GPIO_toggle(GPIOC, 2);
        }
        TIM_update_clear(TIM3);
    }
}

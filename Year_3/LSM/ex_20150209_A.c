#include "stm32_unict_lib.h"
#include <stdio.h>
#define SECS_3 3000
#define X_VAL 11400

/*
 * RA3    = PB10
 * RA2    = PB4
 * RB0    = PB0
 * RB1    = PC2
 * RA0    = ADC1_IN11
 * -      = PB5
 * +      = PB6
 */

typedef enum {
    IDLE,
    TURN_ON
} status_t;

status_t status = IDLE;

int X_ms = X_VAL; /* 'r'*100 */
int Y_ms = 3800; /* X_ms / 3 */
int Z_ms = 495; /* 'c'*5 */
int time_turn_on = 0;
int can_blind = 0;

int y_incr = 0;

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
    TIM_config_timebase(TIM2, 8400, 10);
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
    char s[5];
    int min = X_VAL - SECS_3;
    int max = X_VAL + SECS_3;
    int value;
    int adc_read;

    for (;;) {
        ADC_start(ADC1);
        while (!ADC_completed(ADC1))
            ;
        adc_read = ADC_read(ADC1);

        value = ((ADC_read(ADC1) * (max - min)) / 255.0) + min;
        X_ms = value;
        Y_ms = value / 3;

        sprintf(s, "%f", value / 1000.0);
        DISPLAY_puts(0, s);
    }
    return 0;
}

void
turn_off(void)
{
    status = IDLE;
    GPIO_write(GPIOB, 0, 0);
    GPIO_write(GPIOC, 2, 0);
    time_turn_on = 0;
    can_blind = 0;
}

void
EXTI15_10_IRQHandler(void)
{
    if (EXTI_isset(EXTI10)) {
        if (status == IDLE) {
            status = TURN_ON;
            GPIO_write(GPIOB, 0, 1);
            TIM2->CNT = 0;
        } else {
            turn_off();
        }
        EXTI_clear(EXTI10);
    }
}

void
EXTI9_5_IRQHandler(void)
{
    if (EXTI_isset(EXTI5)) {
        y_incr -= 100;
        printf("%d\n", y_incr);
        EXTI_clear(EXTI5);
    }

    if (EXTI_isset(EXTI6)) {
        y_incr += 100;
        printf("%d\n", y_incr);
        EXTI_clear(EXTI6);
    }
}

void
EXTI4_IRQHandler(void)
{
    if (EXTI_isset(EXTI4)) {
        if (status == TURN_ON) {
            time_turn_on = 0;
        }
        EXTI_clear(EXTI4);
    }
}

void
TIM2_IRQHandler(void)
{
    if (TIM_update_check(TIM2)) {
        if (status == TURN_ON) {
            if (time_turn_on >= X_ms) {
                can_blind = 1;
            } else {
                can_blind = 0;
            }

            if (time_turn_on >= X_ms + Y_ms + y_incr) {
                turn_off();
            }

            time_turn_on++;
        }
        TIM_update_clear(TIM2);
    }
}

void
TIM3_IRQHandler(void)
{
    if (TIM_update_check(TIM3)) {
        if (can_blind) {
            GPIO_toggle(GPIOC, 2);
        } else {
            GPIO_write(GPIOC, 2, 0);
        }
        TIM_update_clear(TIM3);
    }
}

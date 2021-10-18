#include "stm32_unict_lib.h"
#include <stdio.h>

#define X_INCR 20
#define Y_INCR 5

#define GET_MONEY 0
#define EROGATING 1
#define EROGATED 2

#define PRICE_L 1.5

/*
 * X = PB10
 * Y = PB4
 * Z = PB5
 * T = PB6
 * output:
 * red = PB0
 * yellow = PC2
 */

int money_tot = 0;
int status = GET_MONEY;
float erogated = 0;
char s[5];
int flashing = 0;

int
main()
{
    GPIO_init(GPIOB);
    GPIO_init(GPIOC);

    GPIO_config_output(GPIOC, 2);
    GPIO_config_output(GPIOB, 0);
    TIM_init(TIM2);
    TIM_set(TIM2, 0);
    TIM_on(TIM2);
    TIM_enable_irq(TIM2, IRQ_UPDATE);
    TIM_config_timebase(TIM2, 8400, 5000);

    GPIO_config_input(GPIOB, 10); /* X */
    GPIO_config_input(GPIOB, 4); /* Y */
    GPIO_config_input(GPIOB, 5); /* Z */
    GPIO_config_input(GPIOB, 6); /* T */

    DISPLAY_init();

    GPIO_config_EXTI(GPIOB, EXTI10);
    EXTI_enable(EXTI10, FALLING_EDGE);
    GPIO_config_EXTI(GPIOB, EXTI4);
    EXTI_enable(EXTI4, FALLING_EDGE);
    GPIO_config_EXTI(GPIOB, EXTI5);
    EXTI_enable(EXTI5, FALLING_EDGE);
    GPIO_config_EXTI(GPIOB, EXTI6);
    EXTI_enable(EXTI6, FALLING_EDGE);

    for (;;) {
        if (status == GET_MONEY) {
            sprintf(s, "%4d", money_tot);
            DISPLAY_puts(0, s);
        } else if (status == EROGATING) {
            sprintf(s, "%g", erogated);
            DISPLAY_puts(0, s);
        }
    }

    return 0;
}

void
EXTI15_10_IRQHandler(void)
{
    if (EXTI_isset(EXTI10)) {
        if (status == GET_MONEY) {
            money_tot += X_INCR;
        }
        EXTI_clear(EXTI10);
    }
}

void
EXTI4_IRQHandler(void)
{
    if (EXTI_isset(EXTI4)) {
        if (status == GET_MONEY) {
            money_tot += Y_INCR;
        }
        EXTI_clear(EXTI4);
    }
}

void
EXTI9_5_IRQHandler(void)
{
    if (EXTI_isset(EXTI5)) {
        if (status == GET_MONEY) {
            money_tot = 0;
        }
        EXTI_clear(EXTI5);
    }

    if (EXTI_isset(EXTI6)) {
        if (status == GET_MONEY) {
            status = EROGATING;
        } else if (status == EROGATED) {
            GPIO_write(GPIOB, 0, 0);
            status = GET_MONEY;
            erogated = 0;
            money_tot = 0;
        }
        EXTI_clear(EXTI6);
    }
}

void
TIM2_IRQHandler(void)
{
    if (erogated >= (money_tot / PRICE_L)) {
        if (status == EROGATING) {
            status = EROGATED;
            GPIO_write(GPIOB, 0, 1);
            GPIO_write(GPIOC, 2, 0);
        }
    } else {
        if (status == EROGATING) {
            GPIO_toggle(GPIOC, 2);
            erogated += 0.375;
        }
    }
    TIM_update_clear(TIM2);
}

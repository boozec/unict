#include "stm32_unict_lib.h"
#include <stdio.h>
#include <string.h>

int queue = 0;
int current_ticket = 0;
int average_s = 0;

int incr_s = -1;

int ms500 = 0;
int sum = 0;
int n = 0;

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

    GPIO_config_output(GPIOB, 0);

    TIM_init(TIM3);
    TIM_set(TIM3, 0);
    TIM_config_timebase(TIM3, 8400, 5000);
    TIM_config_IC(TIM3, 1, IC_FALLING_EDGE);
    TIM_enable_irq(TIM3, IRQ_UPDATE | IRQ_CC_1);
    TIM_on(TIM3);

    CONSOLE_init();
}

int
main()
{
    init();

    char s[2];

    for (;;) {
        if (incr_s >= 0) {
            if ((incr_s % 2) == 1) {
                sprintf(s, "%02d", queue);
            } else {
                sprintf(s, "  ");
            }
        } else {
            sprintf(s, "%02d", current_ticket);
        }

        DISPLAY_puts(0, s);

        sprintf(s, "%02d", average_s);
        DISPLAY_puts(2, s);
    }
    return 0;
}

void
EXTI15_10_IRQHandler(void)
{
    if (EXTI_isset(EXTI10)) {
        queue++;
        incr_s = 0;
        GPIO_write(GPIOB, 0, 1);
        TIM3->CNT = 0;

        EXTI_clear(EXTI10);
    }
}

void
EXTI4_IRQHandler(void)
{
    if (EXTI_isset(EXTI4)) {
        int seconds = ms500 / 2;
        sum += seconds;
        n++;

        average_s = sum / n;
        current_ticket++;
        ms500 = 0;

        EXTI_clear(EXTI4);
    }
}

void
TIM3_IRQHandler(void)
{
    char s[2];
    if (TIM_update_check(TIM3)) {
        ms500++;

        if (incr_s >= 0) {
            incr_s++;

            if (incr_s == 4) {
                incr_s = -1;
                GPIO_write(GPIOB, 0, 0);
            }
        }

        TIM_update_clear(TIM3);
    }
}

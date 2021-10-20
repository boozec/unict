#include "stm32_unict_lib.h"
#include <stdio.h>
#include <string.h>

#define OPEN_T 20
#define CLOSE_T 8

typedef enum {
    CLOSED,
    OPENING,
    OPENED,
    CLOSING
} status_t;

status_t status = CLOSED;

/*
 * X = PB10
 * Y = PB4
 * Z = PB5
 * output:
 * red = PB0
 */

char str[5] = "----\0";
int ms_to_open = OPEN_T; /* 500ms x 10s */
int ms_to_close = CLOSE_T; /* 500ms x 4s */

int level = 4;

void
print_dash(int n, int opt)
{
    int i;

    if (opt && level < n)
        return;
    else if (!opt && level > n)
        return;

    memset(str, ' ', 5);
    for (i = 0; i < n; ++i)
        *(str + i) = '-';

    for (; i < 5; ++i)
        *(str + i) = ' ';

    level = n;
}

int
main()
{
    GPIO_init(GPIOB);
    GPIO_init(GPIOC);

    GPIO_config_input(GPIOB, 10); /* X, change status to OPENING */
    GPIO_config_input(GPIOB, 4); /* Y */
    GPIO_config_input(GPIOB, 5); /* Z */

    GPIO_config_output(GPIOB, 0); /* led */

    DISPLAY_init();

    GPIO_config_EXTI(GPIOB, EXTI10);
    EXTI_enable(EXTI10, FALLING_EDGE);
    GPIO_config_EXTI(GPIOB, EXTI4);
    EXTI_enable(EXTI4, FALLING_EDGE);
    GPIO_config_EXTI(GPIOB, EXTI5);
    EXTI_enable(EXTI5, FALLING_EDGE);

    /* Timer for red LED */
    TIM_init(TIM2);
    TIM_set(TIM2, 0);
    TIM_on(TIM2);
    TIM_enable_irq(TIM2, IRQ_UPDATE);
    TIM_config_timebase(TIM2, 8400, 5000);

    for (;;) {
        DISPLAY_puts(0, str);
    }

    return 0;
}

void
EXTI9_5_IRQHandler(void)
{
    if (EXTI_isset(EXTI5)) {
        int mul;
        if (status == OPENED) {
            switch (level) {
            case 1:
                mul = 25;
                break;
            case 2:
                mul = 50;
                break;
            default:
                mul = 70;
            }
            ms_to_close = CLOSE_T - (CLOSE_T * mul / 100);
        } else if (status == CLOSING) {
            switch (level) {
            case 1:
                mul = 25;
                break;
            case 2:
                mul = 50;
                break;
            default:
                mul = 70;
            }
            ms_to_open = OPEN_T - (OPEN_T * mul / 100);
            status = OPENING;
        }
        EXTI_clear(EXTI5);
    }
}

void
EXTI15_10_IRQHandler(void)
{
    if (EXTI_isset(EXTI10)) {
        status = OPENING;
        int mul;
        switch (level) {
        case 1:
            mul = 70;
            break;
        case 2:
            mul = 50;
            break;
        default:
            mul = 25;
        }
        ms_to_open = OPEN_T - (OPEN_T * mul / 100);
        EXTI_clear(EXTI10);
    }
}

void
EXTI4_IRQHandler(void)
{
    if (EXTI_isset(EXTI4)) {
        if (status == OPENED) {
            status = CLOSING;
            ms_to_close = OPEN_T;
        } else if (status == OPENING) {
            status = CLOSING;
            ms_to_close = OPEN_T - ms_to_close;
        }
        EXTI_clear(EXTI4);
    }
}

void
TIM2_IRQHandler(void)
{
    if (status == OPENING) {
        GPIO_toggle(GPIOB, 0);
        ms_to_open--;

        if (ms_to_open <= OPEN_T - (OPEN_T * 70 / 100)) {
            print_dash(1, 1);
        } else if (ms_to_open <= OPEN_T - (OPEN_T * 50 / 100)) {
            print_dash(2, 1);
        } else if (ms_to_open <= OPEN_T - (OPEN_T * 25 / 100)) {
            print_dash(3, 1);
        }

        if (ms_to_open == 0) {
            status = OPENED;
            print_dash(0, 1);
            GPIO_write(GPIOB, 0, 0);
            ms_to_open = OPEN_T; /* Reset timer of 10s */
        }
    } else if (status == OPENED) {
        ms_to_close--;
        if (ms_to_close == 0) {
            status = CLOSING;
            ms_to_close = OPEN_T; /* During the closing, ms_to_close has the same value of OPENING time */
        }
    } else if (status == CLOSING) {
        GPIO_toggle(GPIOB, 0);
        ms_to_close--;
        if (ms_to_close <= OPEN_T - (OPEN_T * 70 / 100)) {
            print_dash(3, 0);
        } else if (ms_to_close <= OPEN_T - (OPEN_T * 50 / 100)) {
            print_dash(2, 0);
        } else if (ms_to_close <= OPEN_T - (OPEN_T * 25 / 100)) {
            print_dash(1, 0);
        }

        if (ms_to_close == 0) {
            status = CLOSED;
            print_dash(4, 0);
            GPIO_write(GPIOB, 0, 0);
            ms_to_close = CLOSE_T;
        }
    }

    TIM_update_clear(TIM2);
}

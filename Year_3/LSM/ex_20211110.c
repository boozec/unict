#include "stm32_unict_lib.h"
#include <stdio.h>
#include <string.h>

/* LED RED = PB0,
 * LED YELLOW = PC2,
 * LED GREEN = PC3,
 * X = PB10,
 * Y = PB4,
 * Z = PB5,
 * T = PB6
 */

#define TA_MIN 10
#define TA_MAX 30
#define CYCLE_50MS 12

int config_state = 0;
int config_ta = 0;
int ta_time = TA_MIN;

typedef enum {
    AUTO,
    HAND
} modes_t;

typedef enum {
    CLOSED,
    OPENING,
    OPEN,
    CLOSING
} status_t;

modes_t mode = AUTO;
status_t status = CLOSED;

char gate[4] = "----";

int counter_open = 0;
int counter_ta = 0;

void
dash(int n)
{
    int i;
    for (i = 0; i < n; ++i)
        *(gate + i) = '-';

    for (i = n; i < 4; ++i)
        *(gate + i) = ' ';
}

int
main()
{
    GPIO_init(GPIOB);
    GPIO_init(GPIOC);

    GPIO_config_output(GPIOB, 0);
    GPIO_config_output(GPIOC, 2);
    GPIO_config_output(GPIOC, 3);

    GPIO_config_input(GPIOB, 6);
    GPIO_config_input(GPIOB, 10);
    GPIO_config_input(GPIOB, 4);
    GPIO_config_input(GPIOB, 5);

    GPIO_config_EXTI(GPIOB, EXTI6);
    EXTI_enable(EXTI6, FALLING_EDGE);

    GPIO_config_EXTI(GPIOB, EXTI10);
    EXTI_enable(EXTI10, FALLING_EDGE);

    GPIO_config_EXTI(GPIOB, EXTI4);
    EXTI_enable(EXTI4, FALLING_EDGE);

    GPIO_config_EXTI(GPIOB, EXTI5);
    EXTI_enable(EXTI5, FALLING_EDGE);

    DISPLAY_init();
    ADC_init(ADC1, ADC_RES_8, ADC_ALIGN_RIGHT);
    ADC_channel_config(ADC1, GPIOC, 1, 11);
    ADC_on(ADC1);
    ADC_sample_channel(ADC1, 11);

    /* Use one timer for:
	 * OPENING time: 50 * 12 = 600ms
	 *
	 */
    TIM_init(TIM2);
    TIM_set(TIM2, 0);
    TIM_on(TIM2);
    TIM_enable_irq(TIM2, IRQ_UPDATE);
    TIM_config_timebase(TIM2, 8400, 500); /* 50 ms */

    int adc_read;
    char buffer[4];

    if (mode == HAND) {
        GPIO_write(GPIOC, 2, 1);
    }

    for (;;) {
        ADC_start(ADC1);
        if (config_state) {
            if (config_ta) {
                while (!ADC_completed(ADC1)) { }
                adc_read = ADC_read(ADC1);
                ta_time = adc_read * (TA_MAX - TA_MIN) / 255 + TA_MIN;
                sprintf(buffer, "  %2d", ta_time);
            } else {
                if (mode == AUTO) {
                    sprintf(buffer, "AUTO");
                } else {
                    sprintf(buffer, "HAND");
                }
            }
        } else {
            strcpy(buffer, gate);
        }
        DISPLAY_puts(0, buffer);
    }

    return 0;
}

void
EXTI9_5_IRQHandler(void)
{
    if (EXTI_isset(EXTI6)) {
        config_state = !config_state;
        if (!config_state) {

            config_ta = 0;
        }

        GPIO_toggle(GPIOB, 0);
        EXTI_clear(EXTI6);
    }

    if (EXTI_isset(EXTI5)) {
        if (mode == HAND) {
            if (status == CLOSED) {
                status = OPENING;
            } else if (status == OPEN) {
                status = CLOSING;
            }
        }
        EXTI_clear(EXTI5);
    }
}

void
EXTI15_10_IRQHandler(void)
{
    if (EXTI_isset(EXTI10)) {
        if (config_state) {
            config_ta = 1;
        } else {
            if (status == CLOSED) {
                status = OPENING;
            }
        }
        EXTI_clear(EXTI10);
    }
}

void
EXTI4_IRQHandler(void)
{
    if (EXTI_isset(EXTI4)) {
        if (config_state) {
            config_ta = 0;

            if (mode == AUTO) {
                mode = HAND;
            } else {
                mode = AUTO;
            }

            GPIO_toggle(GPIOC, 2);
        }
        EXTI_clear(EXTI4);
    }
}

void
TIM2_IRQHandler(void)
{
    if (status == CLOSED) {
        GPIO_write(GPIOC, 3, 0);
    } else if (status == OPEN) {
        GPIO_write(GPIOC, 3, 1);
    } else {
        GPIO_toggle(GPIOC, 3);
    }

    if (status == OPEN) {
        counter_ta++;
        if (counter_ta >= ta_time * 20) {
            if (mode == AUTO) {
                counter_ta = 0;
                status = CLOSING;
            }
        }
    }

    if (status == OPENING || status == CLOSING) {
        counter_open++;
        if (counter_open == CYCLE_50MS) {
            if (status == OPENING) {
                status = OPEN;
            } else if (status == CLOSING) {
                status = CLOSED;
            }
            counter_open = 0;
        }

        if (status == OPENING) {
            if (counter_open <= CYCLE_50MS / 4) {
                dash(3);
            } else if (counter_open <= CYCLE_50MS / 3) {
                dash(2);
            } else if (counter_open <= CYCLE_50MS / 2) {
                dash(1);
            } else {
                dash(0);
            }
        } else if (status == CLOSING) {
            if (counter_open <= CYCLE_50MS / 4) {
                dash(1);
            } else if (counter_open <= CYCLE_50MS / 3) {
                dash(2);
            } else if (counter_open <= CYCLE_50MS / 2) {
                dash(3);
            } else {
                dash(4);
            }
        }
    }

    TIM_update_clear(TIM2);
}

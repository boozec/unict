#include "stm32_unict_lib.h"
#include <ctype.h> /* For isdigit() */
#include <stdio.h>
#include <stdlib.h> /* For atoi() */
#include <string.h>

typedef int electr_users_t;

typedef enum {
    IDLE, /* Init state */
    CONSUME_ALL, /* Press X */
    CONSUME_PER_SECOND, /* Press Y */
    CONFIG, /* Press T */
} status_t;

electr_users_t electr_user[2];
status_t status = IDLE;
short switch_on = 0; /* Press Z */
int consumption = 0;
float consumption_per_second = 0.0;
int threshold = 3000; /* Start value */
short counter_over_threshold = 0;
short alarm_on = 0;

float
calculate_consume_per_second()
{
    /* E = P * t
     * where E is kW/h, P is kW and t is hours
     * `energy_hours` is kWh
     */
    float energy_hours = ((electr_user[0] + electr_user[1]) / 1000.0) * ((1 / 60.0) / 60.0);

    return energy_hours * 3600;
}

int
get_new_threshold()
{
    char string[4];
    char ch;
    int i;
    int error;
    int num;

    memset(string, 0, 4);

    do {
        printf("\nAdd a threshold in [0, 3000]: ");
        fflush(stdout);

        error = 0;
        for (i = 0; i < 4; ++i) {
            ch = readchar();

            if (ch == 13) {
                if (i == 0) {
                    error = 1;
                } else {
                    string[i] = '\0';
                }

                break;
            } else if (!isdigit(ch)) {
                error = 1;
                break;
            }

            __io_putchar(ch);
            string[i] = ch;
        }

        if (error) {
            printf("\nEnter a number.");
            num = 3001;
        } else {
            /* `num` can't be < 0 because '-' is not a valid character */
            num = atoi(string);
        }
    } while (num > 3000);

    return num;
}

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
    GPIO_config_output(GPIOC, 3);

    TIM_init(TIM2);
    TIM_set(TIM2, 0);
    /* TIM2 is 32-bits */
    /* (42000/84e3) * 2000 = 1000 ms */
    TIM_config_timebase(TIM2, 42000, 2000);
    TIM_enable_irq(TIM2, IRQ_UPDATE);
    TIM_on(TIM2);

    ADC_init(ADC1, ADC_RES_8, ADC_ALIGN_RIGHT);
    ADC_channel_config(ADC1, GPIOC, 0, 10);
    ADC_channel_config(ADC1, GPIOC, 1, 11);
    ADC_on(ADC1);

    CONSOLE_init();
}

int
main()
{
    int adc_read;
    char s[5];

    init();

    for (;;) {
        ADC_sample_channel(ADC1, 11);
        ADC_start(ADC1);
        while (!ADC_completed(ADC1))
            ;
        adc_read = ADC_read(ADC1);
        electr_user[0] = (adc_read * 500 / 255);

        ADC_sample_channel(ADC1, 10);
        ADC_start(ADC1);
        while (!ADC_completed(ADC1))
            ;
        adc_read = ADC_read(ADC1);
        electr_user[1] = (adc_read * 1000 / 255);

        switch (status) {
        case CONSUME_ALL:
            /* Handle the case if the integer value is greater
             * than the maximum length of the screen.
             * In that case use KWatt
             */

            if (consumption <= 9999) {
                sprintf(s, "%4d", consumption);
            } else {
                sprintf(s, "%4f", consumption / 1000.0);
            }
            break;
        case CONSUME_PER_SECOND:
            sprintf(s, "%4f", consumption_per_second);
            break;
        case CONFIG:
            threshold = get_new_threshold();
            status = IDLE;
            counter_over_threshold = 0;
            break;
        default:
            memset(s, ' ', 4);
        }

        DISPLAY_puts(0, s);
    }

    return 0;
}

void
EXTI15_10_IRQHandler(void)
{
    if (EXTI_isset(EXTI10)) {
        /* X */

        if (status != CONFIG) {
            status = CONSUME_ALL;
        }

        EXTI_clear(EXTI10);
    }
}

void
EXTI9_5_IRQHandler(void)
{
    if (EXTI_isset(EXTI6)) {
        /* T */

        status = CONFIG;

        EXTI_clear(EXTI6);
    }

    if (EXTI_isset(EXTI5)) {
        /* Z */

        if (status != CONFIG) {
            switch_on = !switch_on;

            /* GPIO_toggle() does not assure 1 for ON and 0 for OFF */
            if (switch_on) {
                alarm_on = 0;
                counter_over_threshold = 0;
                GPIO_write(GPIOB, 0, 0); /* Turn off red led */
                GPIO_write(GPIOC, 3, 1);
            } else {
                status = IDLE;
                GPIO_write(GPIOC, 3, 0);
            }

            consumption = 0;
            consumption_per_second = 0;
        }

        EXTI_clear(EXTI5);
    }
}

void
EXTI4_IRQHandler(void)
{
    if (EXTI_isset(EXTI4)) {
        /* Y */

        if (status != CONFIG) {
            status = CONSUME_PER_SECOND;
        }

        EXTI_clear(EXTI4);
    }
}

void
TIM2_IRQHandler(void)
{
    if (TIM_update_check(TIM2)) {
        if (!alarm_on && status != CONFIG) {
            if (switch_on) {
                int current_watts = (electr_user[0] + electr_user[1]);
                consumption += current_watts;

                if (current_watts > threshold) {
                    counter_over_threshold++;

                    if (counter_over_threshold > 10) {
                        alarm_on = 1;
                        GPIO_write(GPIOB, 0, 1); /* Turn on red led */
                        GPIO_write(GPIOC, 3, 0); /* Turn off green led */
                        switch_on = 0;
                    }
                }

                consumption_per_second = calculate_consume_per_second();
            }
        }

        TIM_update_clear(TIM2);
    }
}

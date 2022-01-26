#include "stm32_unict_lib.h"
#include <stdlib.h>
#include <string.h>

typedef enum {
    FIRST = 2,
    F_S,
    SECOND,
    S_T,
    THIRD
} floor_t;

typedef enum {
    CONFIG,
    IDLE,
    CLOSING,
    RUNNING,
    OPENING,
} status_t;

floor_t curr_floor = FIRST;
floor_t next_floor = FIRST;
short direction = 1;

unsigned q_index = 0;
floor_t* queue;

status_t status = IDLE;

short circular_200ms = 0; /* alternates 0 and 1 thanks to `0 ^ 1` */
short handle_1500ms = 0; /* until 15, then restart */

int time = 10; /* 10 * `time` = 1s */
int lift_time;
int time_i = 0;

void
init()
{
    int i;
    queue = malloc(sizeof(floor_t) * 10);
    for (i = 0; i < 10; ++i)
        queue[i] = 0;

    GPIO_init(GPIOB);
    GPIO_init(GPIOC);

    GPIO_config_input(GPIOB, 10); /* X */
    GPIO_config_EXTI(GPIOB, EXTI10);
    EXTI_enable(EXTI10, FALLING_EDGE);

    GPIO_config_input(GPIOB, 4); /* Y */
    GPIO_config_EXTI(GPIOB, EXTI4);
    EXTI_enable(EXTI4, FALLING_EDGE);

    GPIO_config_input(GPIOB, 5); /* Z */
    GPIO_config_EXTI(GPIOB, EXTI5);
    EXTI_enable(EXTI5, FALLING_EDGE);

    GPIO_config_input(GPIOB, 6); /* T */
    GPIO_config_EXTI(GPIOB, EXTI6);
    EXTI_enable(EXTI6, FALLING_EDGE);

    GPIO_config_output(GPIOC, 2); /* YELLOW */
    GPIO_config_output(GPIOC, 3); /* GREEN */
    GPIO_config_output(GPIOB, 0); /* RED */

    DISPLAY_init();

    CONSOLE_init();

    TIM_init(TIM2);
    TIM_set(TIM2, 0);
    TIM_on(TIM2);
    TIM_config_timebase(TIM2, 8400, 840);
    TIM_enable_irq(TIM2, IRQ_UPDATE);

    ADC_init(ADC1, ADC_RES_8, ADC_ALIGN_RIGHT);
    ADC_channel_config(ADC1, GPIOC, 1, 11);
    ADC_on(ADC1);
    ADC_sample_channel(ADC1, 11);

    ADC_start(ADC1);
    while (!ADC_completed(ADC1))
        ;
    int adc_read = ADC_read(ADC1);
    time = ((adc_read * (10 - 4) / 255.0) + 4);
}

int
main()
{
    init();

    char s[4];
    int i;
    int adc_read;

    sprintf(s, "%3d ", curr_floor);

    for (;;) {
        ADC_start(ADC1);
        if (status == CONFIG) {
            while (!ADC_completed(ADC1))
                ;
            adc_read = ADC_read(ADC1);
            time = ((adc_read * (10 - 4) / 255.0) + 4);
            sprintf(s, "%f", time / 10.0);
            DISPLAY_puts(0, s);
        } else {
            sprintf(s, "%3d%c", curr_floor / 2, ((curr_floor % 2) ? '-' : ' '));
            DISPLAY_puts(0, s);
            lift_time = (time / 10 / 2.0) / 0.1;
        }
    }

    free(queue);
    return 0;
}

void
check_queue()
{
    int i;

    for (i = q_index; i != (q_index - 1) % 10; i = (i + 1) % 10) {
        if (queue[i] != 0) {
            goto_floor(queue[i]);
            queue[i] = 0;
            return;
        }
    }

    if (queue[i] != 0) {
        goto_floor(queue[i]);
        queue[i] = 0;
    }
}

void
    goto_floor(floor)
{
    status = CLOSING;
    switch (floor) {
    case 1:
        next_floor = FIRST;
        break;
    case 2:
        next_floor = SECOND;
        break;
    case 3:
        next_floor = THIRD;
        break;
    }

    if (curr_floor < next_floor) {
        direction = 1;
    } else if (curr_floor > next_floor) {
        direction = -1;
    } else {
        direction = 0;
    }
}

void
    call_floor(floor)
{
    if (queue[(q_index - 1) % 10] == floor)
        return;

    if (status == IDLE) {
        goto_floor(floor);
    } else {
        queue[q_index] = floor;
        q_index = (q_index + 1) % 10;
    }
}

void
EXTI15_10_IRQHandler(void)
{
    if (EXTI_isset(EXTI10)) {
        call_floor(1);
        EXTI_clear(10);
    }
}

void
EXTI9_5_IRQHandler(void)
{
    if (EXTI_isset(EXTI5)) {
        call_floor(2);
        EXTI_clear(EXTI5);
    }

    if (EXTI_isset(EXTI6)) {
        if (status == IDLE) {
            status = CONFIG;
        } else if (status == CONFIG) {
            status = IDLE;
        }
        EXTI_clear(EXTI6);
    }
}

void
EXTI4_IRQHandler(void)
{
    if (EXTI_isset(EXTI4)) {
        call_floor(3);
        EXTI_clear(EXTI4);
    }
}

void
TIM2_IRQHandler(void)
{
    if (TIM_update_check(TIM2)) {
        if (status == RUNNING) {
            if (circular_200ms) {
                GPIO_toggle(GPIOC, 2);
            }

            time_i++;

            if (time_i >= lift_time) {
                time_i = 0;
                if (curr_floor == next_floor) {
                    GPIO_write(GPIOC, 2, 0);
                    status = OPENING;
                    time_i = 0;
                } else {
                    curr_floor += direction;
                }
            }
        } else if (status == CLOSING || status == OPENING) {
            if (circular_200ms) {
                if (status == CLOSING)
                    GPIO_toggle(GPIOB, 0);
                else
                    GPIO_toggle(GPIOC, 3);
            }

            handle_1500ms++;
            if (handle_1500ms == 15) {
                if (status == CLOSING) {
                    status = RUNNING;
                } else {
                    status = IDLE;
                }

                handle_1500ms = 0;
                GPIO_write(GPIOB, 0, 0);
                GPIO_write(GPIOC, 3, 0);

                if (status == IDLE)
                    check_queue();
            }
        }

        circular_200ms ^= 1;
        TIM_update_clear(TIM2);
    }
}

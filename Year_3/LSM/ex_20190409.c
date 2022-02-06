#include "stm32_unict_lib.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char name[10];
    float price;
    char display[2];
    short s_range;
    short e_range;
} drinks_t;

typedef enum {
    SELECTING,
    EROGATING,
    RESTING,
} status_t;

typedef struct {
    int five_c;
    int ten_c;
    int twenty_c;
} rest_t;

drinks_t drinks[3];
float total = 0.0;

int flag_add = 0;
status_t status = SELECTING;
int inc_erogating = 0;
int value;

rest_t rest;

int q_rest[30] = { 0 };
int q_index = 0;
int q_jndex = 0;
int total_to_return;

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
    GPIO_config_output(GPIOC, 3);

    TIM_init(TIM2);
    TIM_set(TIM2, 0);
    TIM_config_timebase(TIM2, 8400, 5000);
    TIM_enable_irq(TIM2, IRQ_UPDATE);
    TIM_on(TIM2);

    ADC_init(ADC1, ADC_RES_6, ADC_ALIGN_RIGHT);
    ADC_channel_config(ADC1, GPIOC, 1, 11);
    ADC_on(ADC1);
    ADC_sample_channel(ADC1, 11);

    CONSOLE_init();
}

int
search_index_range(int value)
{
    int i;

    for (i = 0; i < 3; ++i) {
        if (drinks[i].s_range <= value && drinks[i].e_range >= value)
            break;
    }

    return i;
}

void
get_rest(int drink_index)
{
    total_to_return = floor((total - drinks[drink_index].price) * 100);

    while (rest.twenty_c > 0) {
        if ((total_to_return - 20) >= 0) {
            total_to_return -= 20;
            rest.twenty_c--;
            q_rest[q_index++] = 20;
        } else {
            break;
        }
    }

    while (rest.ten_c > 0) {
        if ((total_to_return - 10) >= 0) {
            total_to_return -= 10;
            rest.ten_c--;
            q_rest[q_index++] = 10;
        } else {
            break;
        }
    }

    while (rest.five_c > 0) {
        if ((total_to_return - 5) >= 0) {
            total_to_return -= 5;
            rest.five_c--;
            q_rest[q_index++] = 5;
        } else {
            break;
        }
    }
}

int
main()
{
    init();

    strcpy(drinks[0].name, "Coffee");
    strcpy(drinks[0].display, "Ca");
    drinks[0].price = 0.35;
    drinks[0].s_range = 0;
    drinks[0].e_range = 28;

    strcpy(drinks[1].name, "The");
    strcpy(drinks[1].display, "te");
    drinks[1].price = 0.40;
    drinks[1].s_range = 29;
    drinks[1].e_range = 38;

    strcpy(drinks[2].name, "Choco");
    strcpy(drinks[2].display, "Ci");
    drinks[2].price = 0.45;
    drinks[2].s_range = 39;
    drinks[2].e_range = 64;

    rest.five_c = 10;
    rest.ten_c = 10;
    rest.twenty_c = 10;

    char s[5];
    char s2[2];

    for (;;) {
        ADC_start(ADC1);
        while (!ADC_completed(ADC1))
            ;
        value = ADC_read(ADC1);
        int index = search_index_range(value);

        sprintf(s, "%s", drinks[index].display);
        DISPLAY_puts(0, s);

        if (status == RESTING) {
            if (inc_erogating) {
                printf("%d %d %d\n", inc_erogating, q_rest[q_jndex], q_jndex);
                sprintf(s2, "%02d", q_rest[q_jndex++]);
            } else {
                sprintf(s2, "  ");
            }
            DISPLAY_puts(2, s2);
            delay_ms(500);
        } else {
            sprintf(s, "%.1f", total);
            DISPLAY_puts(2, s);

            sprintf(s, "%.1f", total - floor(total));
            memcpy(s, &s[2], 1);
            s[1] = '\0';
            DISPLAY_puts(3, s);
        }
    }
    return 0;
}

void
EXTI15_10_IRQHandler(void)
{
    if (EXTI_isset(EXTI10)) {
        if (status == SELECTING) {
            total += 0.5;
            flag_add = 1;
        }

        EXTI_clear(EXTI10);
    }
}

void
EXTI9_5_IRQHandler(void)
{
    if (EXTI_isset(EXTI5)) {
        if (status == SELECTING) {
            total += 0.1;
            flag_add = 1;
        }

        EXTI_clear(EXTI5);
    }

    if (EXTI_isset(EXTI6)) {
        if (status == SELECTING) {
            status = EROGATING;
            GPIO_write(GPIOC, 3, 1);
        }

        EXTI_clear(EXTI6);
    }
}

void
EXTI4_IRQHandler(void)
{
    if (EXTI_isset(EXTI4)) {
        if (status == SELECTING) {
            total += 0.2;
            flag_add = 1;
        }

        EXTI_clear(EXTI4);
    }
}

void
TIM2_IRQHandler(void)
{
    if (TIM_update_check(TIM2)) {
        if (status == SELECTING) {
            if (flag_add == 1) {
                GPIO_write(GPIOB, 0, 1);
                flag_add = 0;
            } else {
                GPIO_write(GPIOB, 0, 0);
            }
        } else if (status == EROGATING) {
            if (inc_erogating == 1) {
                GPIO_write(GPIOC, 3, 0);
                status = RESTING;
                inc_erogating = 0;
                get_rest(search_index_range(value));
                total = 0.0;
                GPIO_write(GPIOA, 7, 0);
            }
            inc_erogating ^= 1;
        } else {
            GPIO_write(GPIOC, 2, 1);
            inc_erogating ^= 1;

            if (q_index == q_jndex) {
                GPIO_write(GPIOC, 2, 0);
                q_index = q_jndex = 0;
                status = SELECTING;
            }
        }

        TIM_update_clear(TIM2);
    }
}

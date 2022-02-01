#include "stm32_unict_lib.h"
#include <string.h>

typedef enum {
    IDLE,
    RAIN
} status_t;

status_t status = IDLE;
int freq = 100;
float dim;
float tank = 0;

void
init()
{
    DISPLAY_init();
    GPIO_init(GPIOB);
    GPIO_config_input(GPIOB, 10);
    GPIO_config_EXTI(GPIOB, EXTI10);
    EXTI_enable(EXTI10, FALLING_EDGE);

    GPIO_config_output(GPIOB, 0);

    ADC_init(ADC1, ADC_RES_8, ADC_ALIGN_RIGHT);
    ADC_channel_config(ADC1, GPIOC, 1, 11);
    ADC_channel_config(ADC1, GPIOC, 0, 10);
    ADC_on(ADC1);

    TIM_init(TIM2);
    TIM_set(TIM2, 0);
    TIM_on(TIM2);
    TIM_config_timebase(TIM2, 8400, 1000);
    TIM_enable_irq(TIM2, IRQ_UPDATE);

    CONSOLE_init();
}

int
main()
{
    init();
    char s[4];
    int value;

    for (;;) {
        if (status == RAIN) {
            if (tank > 30)
                tank = 0;
            ADC_sample_channel(ADC1, 11);
            ADC_start(ADC1);
            while (!ADC_completed(ADC1)) { }
            value = ADC_read(ADC1);
            freq = (value * 70 / 255 + 10) * 100;

            ADC_sample_channel(ADC1, 10);
            ADC_start(ADC1);
            while (!ADC_completed(ADC1)) { }
            value = ADC_read(ADC1);
            dim = (value * 48 / 255.0 + 2) / 10;

            sprintf(s, "%f", tank);
        } else {
            sprintf(s, "SUN ");
        }
        DISPLAY_puts(0, s);
    }
    return 0;
}

void
EXTI15_10_IRQHandler(void)
{
    if (EXTI_isset(EXTI10)) {
        if (status == IDLE) {
            GPIO_write(GPIOB, 0, 1);
            status = RAIN;
        } else {
            GPIO_write(GPIOB, 0, 0);
            status = IDLE;
        }

        EXTI_clear(EXTI10);
    }
}

void
TIM2_IRQHandler(void)
{
    if (TIM_update_check(TIM2)) {
        TIM2->ARR = freq;

        if (status == RAIN) {
            tank += dim;
        }
        TIM_update_clear(TIM2);
    }
}

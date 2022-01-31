#include "stm32_unict_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int tmax;
typedef enum {
    SETUP,
    RUN
} status_t;

status_t status = RUN;
float real_root = 0;
float new_want_root = 0;
float want_root = 180;

double rotation = 1;

void
init()
{
    GPIO_init(GPIOB);
    GPIO_init(GPIOC);

    GPIO_config_input(GPIOB, 10); /* X */
    GPIO_config_EXTI(GPIOB, EXTI10);
    EXTI_enable(EXTI10, FALLING_EDGE);

    GPIO_config_input(GPIOB, 4); /* Y */
    GPIO_config_EXTI(GPIOB, EXTI4);
    EXTI_enable(EXTI4, FALLING_EDGE);

    GPIO_config_output(GPIOB, 0); /* LED RED */
    GPIO_config_output(GPIOC, 3); /* LED GREEN */

    TIM_init(TIM2);
    TIM_set(TIM2, 0);
    TIM_on(TIM2);
    TIM_config_timebase(TIM2, 8400, 100);
    TIM_enable_irq(TIM2, IRQ_UPDATE);

    ADC_init(ADC1, ADC_RES_12, ADC_ALIGN_RIGHT);
    ADC_channel_config(ADC1, GPIOC, 1, 11);
    ADC_channel_config(ADC1, GPIOC, 0, 10);
    ADC_on(ADC1);

    DISPLAY_init();
    CONSOLE_init();
}

int
main()
{
    init();
    char s[5];
    srand(time(NULL));

    for (;;) {
        if (status == RUN) {
            ADC_sample_channel(ADC1, 10);
            ADC_start(ADC1);
            while (!ADC_completed(ADC1))
                ;
            float adc_read = ADC_read(ADC1);

            adc_read = (2 * adc_read) / 4095;
            real_root -= ((adc_read * 2) * (1.0 * rand()) / RAND_MAX - adc_read);
            if (real_root > 180)
                real_root = 180;
            else if (real_root < -180)
                real_root = -180;

            printf("%f %f %f\n", rotation, real_root, want_root);
            sprintf(s, "%f", real_root);

            DISPLAY_puts(0, s);
            delay_ms(500);
        } else {
            ADC_sample_channel(ADC1, 11);
            ADC_start(ADC1);
            while (!ADC_completed(ADC1))
                ;
            float adc_read = ADC_read(ADC1);
            new_want_root = (((180 + 180) * adc_read) / 4095) - 180;
            sprintf(s, "%f", new_want_root);

            DISPLAY_puts(0, s);
            delay_ms(500);
        }
    }
    return 0;
}

void
EXTI4_IRQHandler(void)
{
    if (EXTI_isset(EXTI4)) {
        if (status == SETUP) {
            status = RUN;
            want_root = new_want_root;
            GPIO_write(GPIOB, 0, 0);
        }
        EXTI_clear(EXTI4);
    }
}

void
EXTI15_10_IRQHandler(void)
{
    if (EXTI_isset(EXTI10)) {
        if (status == RUN) {
            status = SETUP;
            GPIO_write(GPIOB, 0, 1);
        } else {
            status = RUN;
            GPIO_write(GPIOB, 0, 0);
        }

        EXTI_clear(EXTI10);
    }
}

void
TIM2_IRQHandler(void)
{
    if (TIM_update_check(TIM2)) {
        rotation = (want_root - real_root) * 0.08;

        if (rotation < -10) {
            rotation = -10;
        } else if (rotation > 10) {
            rotation = 10;
        }

        real_root = real_root + rotation * 0.04;
        if (real_root < -180) {
            real_root = -180;
        } else {
            real_root = 180;
        }

        if (abs(want_root - real_root) <= 2) {
            GPIO_write(GPIOC, 3, 1);
        } else {
            GPIO_write(GPIOC, 3, 0);
        }

        TIM_update_clear(TIM2);
    }
}

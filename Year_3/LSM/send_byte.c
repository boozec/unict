/* Run minicom -D /dev/ttyACM0 -b 9600 */

#include "stm32_unict_lib.h"
#include <stdio.h>

/* Slide 3/13 */

struct t_tx_state {
    uint8_t data;
    int bit_count;
    int start;
} tx_state;

/*
 * 9600 interruputs per seconds
 * 84e6/9600 = 8750
 */

void
init_periph()
{
    GPIO_init(GPIOA);
    GPIO_config_output(GPIOA, 2);
    GPIO_write(GPIOA, 2, 1);

    TIM_init(TIM2);

    TIM_config_timebase(TIM2, 1, 8750);

    TIM_set(TIM2, 0);
    TIM_on(TIM2);

    TIM_enable_irq(TIM2, IRQ_UPDATE);

    tx_state.start = 0;
    tx_state.bit_count = 0;
}

void
send_byte(uint8_t c)
{
    /* First wait the end of the trasmission */
    while (tx_state.start == 1) { }

    tx_state.data = c;
    tx_state.start = 1;
    tx_state.bit_count = 0;
}

/*int
__io_putchar(int ch)
{
	send_byte(ch);
	return 0;
}*/

int
main()
{
    init_periph();

    for (;;) {
        /* Using a `printf()` here means you must overwrite the `__io_putchar()` in `console.c`. */
        // printf("Hello world\n\r");

        send_byte('A');
        delay_ms(100);
    }

    return 0;
}

void
TIM2_IRQHandler(void)
{
    if (TIM_update_check(TIM2)) {
        if (tx_state.start) {
            switch (tx_state.bit_count) {
            case 0:
                GPIO_write(GPIOA, 2, 0);
                break;
            case 9:
            case 10:
                GPIO_write(GPIOA, 2, 1);
                break;
            default:
                /* Data bit */
                GPIO_write(GPIOA, 2, tx_state.data & 1); // TX B0
                tx_state.data >>= 1;
            }
            tx_state.bit_count++;

            if (tx_state.bit_count == 11) {
                tx_state.start = 0;
            }
        }

        TIM_update_clear(TIM2);
    }
}

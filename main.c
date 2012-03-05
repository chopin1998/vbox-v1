#include "common.h"

#include "uart.h"
#include "clock.h"
#include "uart_process.h"
#include "io.h"

#include "disp.h"

void init_io(void)
{
    
    LED_PORT.DIRSET = LED1 | LED2;
    LED_PORT.OUTSET = LED1 | LED2;
    
    // PORTC.DIRSET = PIN7_bm;
    // PORTCFG.CLKEVOUT |= PORTCFG_CLKOUT_PC7_gc;
}


void _uart_sendc(unsigned char c)
{
    uart_sendc(&UART_BT, c);
}

void init_uart(void)
{
    uart_init(&UART_BT);
    uart_queue_init(&Q_BT);

    uart_process_init_linebuf(&LB_BT);
    LB_BT.packet_status = OUT_PACKET;

    fdevopen(_uart_sendc, NULL);
}

int main(void)
{
    unsigned char buf[32];
    
    clock_pll_init();
    clock_rtc_init();
    
    init_io();
    init_uart();
    
    disp_init();
    
    PMIC.CTRL |= PMIC_MEDLVLEX_bm | PMIC_LOLVLEX_bm | PMIC_RREN_bm;
    sei();

    clock_interval_clear();

    for (unsigned char i=0;i<100;i++)
    {
        disp_pixel(i, 10, 0x0770);
    }

    for (;;)
    {
        uart_process_tick(&Q_BT, &LB_BT, uart_process_lb_bt, STX, ETX);

        if (1)
        {
            // SLEEP.CTRL = SLEEP_SEN_bm | SLEEP_SMODE_PSAVE_gc;
            SLEEP.CTRL = SLEEP_SEN_bm | SLEEP_SMODE_IDLE_gc;
            __asm__ __volatile__ ("sleep");
        }
    }
}

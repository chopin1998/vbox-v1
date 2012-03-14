#include "common.h"

#include "uart.h"
#include "clock.h"
#include "uart_process.h"
#include "io.h"

#include "disp.h"
#include "bitchar.h"

#include "gps.h"
#include "task.h"

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

    uart_init(&UART_GPS);
    uart_queue_init(&Q_GPS);

    uart_process_init_linebuf(&LB_BT);
    LB_BT.packet_status = OUT_PACKET;
    uart_process_init_linebuf(&LB_GPS);
    LB_GPS.packet_status = OUT_PACKET;

    fdevopen(_uart_sendc, NULL);
}

/*
void disp_show(void)
{
    unsigned short img[] = 
        {
            disp_16color(255,0,0),disp_16color(255,0,0),disp_16color(0,255,0),disp_16color(0,255,0),disp_16color(0,0,255),disp_16color(0,0,255),
            disp_16color(255,0,0),disp_16color(255,0,0),disp_16color(0,255,0),disp_16color(0,255,0),disp_16color(0,0,255),disp_16color(0,0,255),
            disp_16color(255,0,0),disp_16color(255,0,0),disp_16color(0,255,0),disp_16color(0,255,0),disp_16color(0,0,255),disp_16color(0,0,255),
            disp_16color(255,0,0),disp_16color(255,0,0),disp_16color(0,255,0),disp_16color(0,255,0),disp_16color(0,0,255),disp_16color(0,0,255),
            disp_16color(255,0,0),disp_16color(255,0,0),disp_16color(0,255,0),disp_16color(0,255,0),disp_16color(0,0,255),disp_16color(0,0,255),
            disp_16color(255,0,0),disp_16color(255,0,0),disp_16color(0,255,0),disp_16color(0,255,0),disp_16color(0,0,255),disp_16color(0,0,255),
        };

    disp_line(10, 10, 40, 20, disp_16color(0, 255, 0));
    disp_box(1, 50, 25, 30, disp_16color(0, 255, 255), 1);
    disp_box(0, 100, 50, 45, disp_16color(255, 100, 255), 0);
    disp_circle(70, 20, 10, disp_16color(0, 200, 100));
    disp_circle(70, 20, 20, disp_16color(100, 200, 10));

    st7735_img(50, 50, 6, 6, img);
    
    disp_string(10, 85, &BM_FONT_7x8, disp_16color(120, 20, 20), 0xffff, "ABCD+-/*xyzjpP_");    
}
*/

int main(void)
{
    
    clock_pll_init();
    clock_rtc_init();
    
    init_io();
    init_uart();
    
    st7735_init();
    st7735_fill_16(disp_16color(128, 64, 160));
    
    PMIC.CTRL |= PMIC_MEDLVLEX_bm | PMIC_LOLVLEX_bm | PMIC_RREN_bm;
    sei();

    clock_interval_clear();

    for (;;)
    {
        /*
         * uart task
         */
        uart_process_tick(&Q_BT, &LB_BT, uart_process_lb_bt, STX, ETX);
        /* uart task */

        
        /*
         * gps task
         */
        uart_process_tick(&Q_GPS, &LB_GPS, gps_process, GPS_STX, GPS_ETX);
        /* gps task */

        
        /*
         * global display func
         */
        task_screen();
        /* global display func */

        
        /*
         * sleep, irq drive device back
         */
        if (1)
        {
            SLEEP.CTRL = SLEEP_SEN_bm | SLEEP_SMODE_IDLE_gc;
            __asm__ __volatile__ ("sleep");
        }
        /* sleep */
    }
}

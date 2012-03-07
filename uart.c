#include "uart.h"

signed char uart_dequeue(RAW_QUEUE_t *q)
{
    char rev;

    if (q->rx_count == 0)
    {                           /* no data */
        rev = -1;
    }
    else
    {                           /* dequeue normally */
        rev = q->queue[q->rx_out];
        q->rx_out = (q->rx_out + 1) % UART_RAW_RXBUF_MAX;
        q->rx_count--;
    }

    return rev;
}

inline void uart_join(RAW_QUEUE_t *q, unsigned char data)
{
    if (q->rx_count >= UART_RAW_RXBUF_MAX)
    {                           /* buffer full, reset */
        q->queue[0] = data;
        q->rx_in = 1;
        q->rx_out = 0;
        q->rx_count = 1;
    }
    else
    {
        q->queue[q->rx_in] = data;
        q->rx_in = (q->rx_in + 1) % UART_RAW_RXBUF_MAX;
        q->rx_count++;
    }
}
    

ISR (UART_BT_RXC_vect)
{
    unsigned char data;
    data = UART_BT.DATA;

    // uart_sendc(&UART_USB, data);
    uart_join(&Q_BT, data);
}

ISR (UART_GPS_RXC_vect)
{
    unsigned char data;
    data = UART_BT.DATA;

    uart_join(&Q_GPS, data);
}

void uart_init(USART_t *dev)
{
    UART_BT_PORT.DIRSET = UART_BT_TX;
    UART_BT_PORT.DIRCLR = UART_BT_RX;

    UART_GPS_PORT.DIRSET = UART_GPS_TX;
    UART_GPS_PORT.DIRCLR = UART_GPS_RX;
    
    int bsel;
    unsigned char bscale;

    if (dev == &UART_BT)
    {
        bsel = 186;
        bscale = 10;            /* 576000 @ 36M */
    }
    else // if (dev == &UART_GPS)
    {
        bsel = 3734;
        bscale = 12;            /* 9600 @ 36M */
    }
    
    dev->CTRLC = USART_CHSIZE_8BIT_gc | USART_PMODE_DISABLED_gc;

    dev->BAUDCTRLA = (unsigned char)bsel;
    dev->BAUDCTRLB = (bscale << 4) | (bsel >> 8);

    dev->CTRLB |= USART_RXEN_bm | USART_TXEN_bm;

    dev->CTRLA |= USART_RXCINTLVL_LO_gc; /* enable rx interrupt */
}

void uart_queue_init(RAW_QUEUE_t *q)
{
    memset(q->queue, 0x00, UART_RAW_RXBUF_MAX);
    q->rx_in = 0;
    q->rx_out = 0;
    q->rx_count = 0;
}

inline void uart_sendc(USART_t *dev, unsigned char data)
{
    loop_until_bit_is_set(dev->STATUS, USART_DREIF_bp);
    dev->DATA = data;
}

void uart_sends(USART_t *dev, const char *data)
{
    unsigned int len = strlen(data);
    for (unsigned int i=0; i<len; i++)
    {
        uart_sendc(dev, data[i]);
    }
}

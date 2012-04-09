#ifndef _DS1302_H
#define _DS1302_h


#define DS1302_PORT   PORTD
#define DS1302_CE_bm   PIN4_bm
#define DS1302_CLK_bm  PIN1_bm
#define DS1302_SDA_bm  PIN0_bm
#define DS1302_SDA_PINCTRL PIN0CTRL

#define DS1302_CE_HI   (DS1302_PORT.OUTSET = DS1302_CE_bm)
#define DS1302_CE_LO   (DS1302_PORT.OUTCLR = DS1302_CE_bm)
#define DS1302_CLK_HI  (DS1302_PORT.OUTSET = DS1302_CLK_bm)
#define DS1302_CLK_LO  (DS1302_PORT.OUTCLR = DS1302_CLK_bm)

#define DS1302_SDA_INPUT  (DS1302_PORT.DIRCLR = DS1302_SDA_bm)
#define DS1302_SDA_OUTPUT (DS1302_PORT.DIRSET = DS1302_SDA_bm)
#define DS1302_SDA_HI  (DS1302_PORT.OUTSET = DS1302_SDA_bm)
#define DS1302_SDA_LO  (DS1302_PORT.OUTCLR = DS1302_SDA_bm)
#define DS1302_SDA_IN  (DS1302_PORT.IN & DS1302_SDA_bm)

#define DS1302_WR_OP   0x80
#define DS1302_RD_OP   0x81
#define DS1302_SEC     0x00
#define DS1302_MIN     0x01
#define DS1302_HOUR    0x02
#define DS1302_DATE    0x03
#define DS1302_MON     0x04
#define DS1302_DAY     0x05
#define DS1302_YEAR    0x06
#define DS1302_WP      
#define DS1302_TCR     0x08
#define DS1302_RAM     0x20


typedef struct
{
    unsigned char tm_sec;
    unsigned char tm_min;
    unsigned char tm_hour;
    unsigned char tm_mday;
    unsigned char tm_mon;
    unsigned char tm_year;
    unsigned char tm_wday;
    unsigned char tm_yday;
    unsigned char tm_isdst;
} RTC_TIME_t;

void ds1302_init(void);
unsigned char ds1302_read(unsigned char addr);
void ds1302_write(unsigned char addr, unsigned char val);

unsigned char ds1302_read_time(RTC_TIME_t *tm);
void ds1302_set_time(RTC_TIME_t *tm);


#endif

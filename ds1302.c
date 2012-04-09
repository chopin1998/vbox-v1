#include "ds1302.h"
#include "common.h"
#include "io.h"
#include "util.h"

static void _ds1302_writebits(unsigned char val);
static unsigned char _ds1302_readbits(void);


void ds1302_init(void)
{
    DS1302_PORT.DIRSET = DS1302_CE_bm | DS1302_CLK_bm;
    DS1302_PORT.DIRCLR = DS1302_SDA_bm;

    DS1302_CE_LO;               /* disable */

    DS1302_CLK_LO;
    DS1302_SDA_LO;
    DS1302_SDA_INPUT;
}


static void _ds1302_writebits(unsigned char val)
{
    DS1302_SDA_OUTPUT;
    
    for (unsigned char i=8; (i); i--, val >>=1)
    {
        (val & 0x01) ? DS1302_SDA_HI : DS1302_SDA_LO;
         
        DS1302_CLK_HI;
        _delay_us(1);
        DS1302_CLK_LO;
        _delay_us(1);
    }
}

static unsigned char _ds1302_readbits(void)
{
    unsigned char rev=0;
    
    DS1302_SDA_INPUT;
    
    for (unsigned char i=0; i<8; i++)
    {
        rev |= DS1302_SDA_IN << i;

        DS1302_CLK_HI;
        _delay_us(1);
        DS1302_CLK_LO;
        _delay_us(1);
    }

    return rev;
}

void ds1302_write(unsigned char addr, unsigned char val)
{
    DS1302_CE_HI;

    _ds1302_writebits(((addr & 0x3f) << 1) | DS1302_WR_OP);
    _ds1302_writebits(val);
    
    DS1302_CE_LO;
}

unsigned char ds1302_read(unsigned char addr)
{
    unsigned char rev;
    
    DS1302_CE_HI;
    
    _ds1302_writebits(((addr & 0x3f) << 1) | DS1302_RD_OP);
    rev = _ds1302_readbits();
    
    DS1302_CE_LO;
    return rev;
}

static unsigned char rtc_valid_tm(RTC_TIME_t *tm)
{
    return 1;
}

unsigned char ds1302_read_time(RTC_TIME_t *tm)
{
    tm->tm_sec  = bcd2bin(ds1302_read(DS1302_SEC));
    tm->tm_min  = bcd2bin(ds1302_read(DS1302_MIN));
    tm->tm_hour = bcd2bin(ds1302_read(DS1302_HOUR));
    tm->tm_wday = bcd2bin(ds1302_read(DS1302_DAY));
    tm->tm_mday = bcd2bin(ds1302_read(DS1302_DATE));
    tm->tm_mon  = bcd2bin(ds1302_read(DS1302_MON)) - 1;
    tm->tm_year = bcd2bin(ds1302_read(DS1302_YEAR));

    /*
    if (tm->tm_year < 70)
        tm->tm_year += 100;
    */

    printf("tm is secs=%d, mins=%d, hours=%d, "
           "mday=%d, mon=%d, year=%d, wday=%d\n",
           tm->tm_sec, tm->tm_min, tm->tm_hour,
           tm->tm_mday, tm->tm_mon + 1, tm->tm_year, tm->tm_wday);

    return rtc_valid_tm(tm);
}

void ds1302_set_time(RTC_TIME_t *tm)
{
    /* Stop RTC */
    ds1302_write(DS1302_SEC, ds1302_read(DS1302_SEC) | 0x80);

    ds1302_write(DS1302_SEC,  bin2bcd(tm->tm_sec));
    ds1302_write(DS1302_MIN,  bin2bcd(tm->tm_min));
    ds1302_write(DS1302_HOUR, bin2bcd(tm->tm_hour));
    ds1302_write(DS1302_DAY,  bin2bcd(tm->tm_wday));
    ds1302_write(DS1302_DATE, bin2bcd(tm->tm_mday));
    ds1302_write(DS1302_MON,  bin2bcd(tm->tm_mon + 1));
    ds1302_write(DS1302_YEAR, bin2bcd(tm->tm_year % 100));

    /* Start RTC */
    ds1302_write(DS1302_SEC, ds1302_read(DS1302_SEC) & ~0x80);
}

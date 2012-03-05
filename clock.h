#ifndef _CLOCK_H
#define _CLOCK_H 1


#define RTC_INTERVAL (8192 - 1)


void clock_pll_init(void);
void clock_rtc_init(void);

unsigned int clock_interval_get_r(void);
unsigned int clock_interval_get(void);
void clock_interval_clear(void);

#endif

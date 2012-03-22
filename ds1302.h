#ifndef _DS1302_H
#define _DS1302_h


#define DS1302_PORT   PORTD
#define DS1302_RST_bm  PIN4_bm
#define DS1302_CLK_bm  PIN1_bm
#define DS1302_SDA_bm  PIN0_bm
#define DS1302_SDA_PINCTRL PIN0CTRL


void ds1302_init(void);



#endif

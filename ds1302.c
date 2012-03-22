#include "ds1302.h"
#include "common.h"
#include "io.h"


void ds1302_init(void)
{
    DS1302_PORT.DIRSET = DS1302_RST_bm | DS1302_CLK_bm;
    DS1302_PORT.DIRCLR = DS1302_SDA_bm;
    // DS1302_PORT.DS1302_SDA_PINCTRL = PORT_OPC_PULLUP_gc;
    DS1302_PORT.DS1302_SDA_PINCTRL = PORT_OPC_PULLDOWN_gc;
}

#include "common.h"
#include "st7735.h"
#include "io.h"
#include "spi.h"


inline unsigned char spi_writeread(SPI_t *dev, unsigned char data)
{
    dev->DATA = data;
    loop_until_bit_is_set(dev->STATUS, SPI_IF_bp);
    return dev->DATA;
}

void spi_init(SPI_t *dev)
{
    dev->CTRL = SPI_ENABLE_bm | SPI_MASTER_bm;   
}

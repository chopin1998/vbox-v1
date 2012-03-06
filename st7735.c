#include "common.h"
#include "st7735.h"
#include "io.h"

static unsigned char spi_writeread(unsigned char data);

static unsigned char spi_writeread(unsigned char data)
{
    ST7735_SPI.DATA = data;
    loop_until_bit_is_set(ST7735_SPI.STATUS, SPI_IF_bp);
    return ST7735_SPI.DATA;
}

void st7735_writecmd(unsigned char cmd)
{
    ST7735_CS_ON;
    ST7735_CMD;

    spi_writeread(cmd);

    ST7735_CS_OFF;
}

void st7735_writedat(unsigned char dat)
{
    ST7735_CS_ON;
    ST7735_DAT;

    spi_writeread(dat);

    ST7735_CS_OFF;
}


void st7735_init(void)
{
    TFT_SD_PORT.DIRSET = TFT_BL_bm | TFT_RST_bm | TFT_RS_bm |
        TFT_CS_bm | SD_CS_bm | TFT_SPI_MOSI_bm |
        TFT_SPI_CLK_bm;
    
    ST7735_BL_OFF;

    ST7735_RST_OFF;
    _delay_ms(1);
    ST7735_RST_ON;
    _delay_ms(1);
    ST7735_RST_OFF;
    _delay_ms(1);
    
    ST7735_BL_ON;
    
    ST7735_CMD;
    ST7735_CS_OFF;
    ST7735_SD_CS_OFF;

    /* init spi */
    ST7735_SPI.CTRL = SPI_ENABLE_bm | SPI_MASTER_bm;
    /* init spi */

    /* init lcd */
    st7735_writecmd(ST7735_SWRST);  /* software reset */
    _delay_ms(1);
    
    st7735_writecmd(ST7735_SLPOUT); /* out of sleep mode */
    _delay_us(1);

    st7735_writecmd(ST7735_COLMOD); /* set color mode */
    st7735_writedat(0x05);         /* 16-bit */
    // st7735_writedat(0x06);         /* 18-bit */
    _delay_us(1);

    st7735_writecmd(ST7735_FRMCTR1); /* frame rate control */
    st7735_writedat(0x00);        /* fastest refresh */
    st7735_writedat(0x06);        /* 6 lines front porch */
    st7735_writedat(0x03);        /* 3 lines back porch */
    _delay_us(1);

    st7735_writecmd(ST7735_MADCTL); /* memory access control (directions) */
    st7735_writedat(0xC8);  /* row address/col address, bottom to top refresh */


    st7735_writecmd(ST7735_NORON);  /* normal display on */
    _delay_us(1);

    st7735_writecmd(ST7735_DISPON);
    _delay_ms(1);
    
    st7735_fill_16(0xf800);
}

void st7735_set_addrwindow(unsigned char x0, unsigned char y0,
                           unsigned char x1, unsigned char y1)
{
    st7735_writecmd(ST7735_CASET);  // column addr set
    st7735_writedat(0x00);
    st7735_writedat(x0+2);        // xstart
    st7735_writedat(0x00);
    st7735_writedat(x1+2);        // xend

    st7735_writecmd(ST7735_RASET);  // row addr set
    st7735_writedat(0x00);
    st7735_writedat(y0+1);        // ystart
    st7735_writedat(0x00);
    st7735_writedat(y1+1);        // yend
}

void st7735_fill_16(unsigned short color)
{
    unsigned char x, y;

    st7735_set_addrwindow(0, 0, ST7735_WIDTH - 1, ST7735_HEIGHT - 1);
    
    st7735_writecmd(ST7735_RAMWR); // write to RAM
    for (x=0; x <ST7735_WIDTH; x++)
    {
        for (y=0; y <ST7735_HEIGHT; y++)
        {
            st7735_writedat(color >> 8);
            st7735_writedat(color);
        }
    }

    st7735_writecmd(ST7735_NOP);
}

void st7735_pixel(unsigned char x, unsigned char y, unsigned short color)
{
    st7735_set_addrwindow(x, y, x+1, y+1);

    st7735_writecmd(ST7735_RAMWR); // write to RAM
    
    st7735_writedat(color >> 8);
    st7735_writedat(color);
}

#include "common.h"
#include "disp.h"


static unsigned char spi_writeread(unsigned char data);

static unsigned char spi_writeread(unsigned char data)
{
    TFT_SPI.DATA = data;
    loop_until_bit_is_set(TFT_SPI.STATUS, SPI_IF_bp);
    return TFT_SPI.DATA;
}

void disp_writecmd(unsigned char cmd)
{
    TFT_CS_ON;
    TFT_CMD;

    spi_writeread(cmd);

    TFT_CS_OFF;
}

void disp_writedat(unsigned char dat)
{
    TFT_CS_ON;
    TFT_DAT;

    spi_writeread(dat);

    TFT_CS_OFF;
}


void disp_set_addrwindow(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1)
{
    disp_writecmd(DISP_CASET);  // column addr set
    disp_writedat(0x00);
    disp_writedat(x0+2);        // xstart
    disp_writedat(0x00);
    disp_writedat(x1+2);        // xend

    disp_writecmd(DISP_RASET);  // row addr set
    disp_writedat(0x00);
    disp_writedat(y0+1);        // ystart
    disp_writedat(0x00);
    disp_writedat(y1+1);        // yend
}

void disp_fill(unsigned short color)
{
    unsigned char x, y;

    disp_set_addrwindow(0, 0, 128 - 1, 160 - 1);
    
    disp_writecmd(DISP_RAMWR); // write to RAM
    for (x=0; x <128; x++)
    {
        for (y=0; y <160; y++)
        {
            disp_writedat(color >> 8);
            disp_writedat(color);
        }
    }

    disp_writecmd(DISP_NOP);
}

void disp_init()
{
    TFT_SD_PORT.DIRSET = TFT_BL_bm | TFT_RST_bm | TFT_RS_bm | TFT_CS_bm | SD_CS_bm |
        TFT_SPI_MOSI_bm | TFT_SPI_CLK_bm;;
    
    TFT_BL_OFF;

    TFT_RST_OFF;
    _delay_ms(1);
    TFT_RST_ON;
    _delay_ms(1);
    TFT_RST_OFF;
    _delay_ms(1);
    
    TFT_BL_ON;
    
    TFT_CMD;
    TFT_CS_OFF;
    SD_CS_OFF;

    /* init spi */
    TFT_SPI.CTRL = SPI_ENABLE_bm | SPI_MASTER_bm;
    /* init spi */

    /* init lcd */
    disp_writecmd(DISP_SWRST);  /* software reset */
    _delay_ms(1);
    
    disp_writecmd(DISP_SLPOUT); /* out of sleep mode */
    _delay_us(1);

    disp_writecmd(DISP_COLMOD); /* set color mode */
    disp_writedat(0x05);         /* 16-bit */
    // disp_writedat(0x06);         /* 18-bit */
    _delay_us(1);

    disp_writecmd(DISP_FRMCTR1); /* frame rate control */
    disp_writedat(0x00);        /* fastest refresh */
    disp_writedat(0x06);        /* 6 lines front porch */
    disp_writedat(0x03);        /* 3 lines back porch */
    _delay_us(1);

    disp_writecmd(DISP_MADCTL); /* memory access control (directions) */
    disp_writedat(0xC8);  /* row address/col address, bottom to top refresh */


    disp_writecmd(DISP_NORON);  /* normal display on */
    _delay_us(1);

    disp_writecmd(DISP_DISPON);
    _delay_ms(1);
    
    disp_fill(0xf800);
}


void disp_pixel(unsigned char x, unsigned char y, unsigned short color)
{
    disp_set_addrwindow(x, y, x+1, y+1);

    disp_writecmd(DISP_RAMWR); // write to RAM
    disp_writedat(color >> 8);

    disp_writedat(color);
}

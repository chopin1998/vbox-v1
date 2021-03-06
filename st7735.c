#include "common.h"
#include "st7735.h"
#include "io.h"
#include "spi.h"

void st7735_writecmd(unsigned char cmd)
{
    ST7735_CS_ON;
    ST7735_CMD;

    spi_writeread(&ST7735_SPI, cmd);

    ST7735_CS_OFF;
}

void st7735_writedat(unsigned char dat)
{
    ST7735_CS_ON;
    ST7735_DAT;

    spi_writeread(&ST7735_SPI, dat);

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
    spi_init(&ST7735_SPI);
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
    
    st7735_fill_16(0x0000);
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

void st7735_img(unsigned char x, unsigned char y,
                unsigned char width, unsigned char height, unsigned short *bm)
{
    for (unsigned char i=0; i<height; i++)
    {
        st7735_set_addrwindow(x, y+i, x+width, y+i);
        st7735_writecmd(ST7735_RAMWR);
        for (unsigned char j=0; j<width; j++)
        {
            st7735_writedat((*bm)>>8);
            st7735_writedat(*bm);

            bm++;
        }
    }

    st7735_writecmd(ST7735_NOP);
}

void st7735_bitmap(unsigned char x, unsigned char y,
                   BM_t *bm, unsigned char index,
                   unsigned short color, unsigned short bg)
{
    unsigned char c;
    
    for (unsigned char i=0; i<bm->width; i++)
    {
        st7735_set_addrwindow(x+i, y, x+i, y+bm->height);
        st7735_writecmd(ST7735_RAMWR);

        c = *(bm->bitmap+index*bm->width+i);
        // printf("c-> 0x%02x\n", c);
        for (unsigned char j=0; j<bm->height; j++)
        {   
            if (c & 0x01)
            {
                st7735_writedat(color>>8);
                st7735_writedat(color);
            }
            else
            {
                st7735_writedat(bg>>8);
                st7735_writedat(bg);
            }
            c>>=1;
        }
    }

    st7735_writecmd(ST7735_NOP);
}

#ifndef _ST7735_H
#define _ST7735_H

#include "io.h"

#define ST7735_WIDTH    128
#define ST7735_HEIGHT   160


#define ST7735_BL_ON    (TFT_SD_PORT.OUTCLR = TFT_BL_bm)
#define ST7735_BL_OFF   (TFT_SD_PORT.OUTSET = TFT_BL_bm)

#define ST7735_RST_ON   (TFT_SD_PORT.OUTCLR = TFT_RST_bm)
#define ST7735_RST_OFF  (TFT_SD_PORT.OUTSET = TFT_RST_bm)

#define ST7735_DAT      (TFT_SD_PORT.OUTSET = TFT_RS_bm)
#define ST7735_CMD      (TFT_SD_PORT.OUTCLR = TFT_RS_bm)

#define ST7735_CS_ON    (TFT_SD_PORT.OUTCLR = TFT_CS_bm)
#define ST7735_CS_OFF   (TFT_SD_PORT.OUTSET = TFT_CS_bm)

#define ST7735_SD_CS_ON     (TFT_SD_PORT.OUTCLR = SD_CS_bm)
#define ST7735_SD_CS_OFF    (TFT_SD_PORT.OUTSET = SD_CS_bm)


#define ST7735_SPI      SPIE
#define ST7735_SD_SPI   SPIE
#define ST7735_SPI_vect SPIE_INT_vect


#define ST7735_NOP    0x00
#define ST7735_SWRST  0x01
#define ST7735_ID     0x04
#define ST7735_STATUS 0x09
#define ST7735_RDDPM  0x0a
#define ST7735_RDMADCTL 0x0b
#define ST7735_RDCOLMOD 0x0c
#define ST7735_RDDIM  0x0d
#define ST7735_RDDSM  0x0e
#define ST7735_SLPIN  0x10
#define ST7735_SLPOUT 0x11
#define ST7735_PTLON  0x12
#define ST7735_NORON  0x13
#define ST7735_INVOFF 0x20
#define ST7735_INVON  0x21
#define ST7735_GAMSET 0x26
#define ST7735_DISPOFF 0x28
#define ST7735_DISPON 0x29
#define ST7735_CASET  0x2a
#define ST7735_RASET  0x2b
#define ST7735_RAMWR  0x2c
#define ST7735_RGBSET 0x2d
#define ST7735_RAMRD  0x2e
#define ST7735_PTLAR  0x30
#define ST7735_TEOFF  0x34
#define ST7735_TEON   0x35
#define ST7735_MADCTL 0x36
#define ST7735_IDMOFF 0x38
#define ST7735_IDMON  0x39
#define ST7735_COLMOD 0x3a
#define ST7735_RDID1  0xda
#define ST7735_RDID2  0xdb
#define ST7735_RDID3  0xdc
#define ST7735_FRMCTR1 0xb1
#define ST7735_FRMCTR2 0xb2
#define ST7735_FRMCTR3 0xb3
#define ST7735_INVCTR  0xb4
#define ST7735_PWCTR1  0xc0
#define ST7735_PWCTR2  0xc1
#define ST7735_PWCTR3  0xc2
#define ST7735_PWCTR4  0xc3
#define ST7735_PWCTR5  0xc4
#define ST7735_VMCTR1  0xc5
#define ST7735_VMOFCTR 0xc7
#define ST7735_WRID2   0xd1
#define ST7735_WRID3   0xd2
#define ST7735_NVCTR1  0xd9
#define ST7735_NVCTR2  0xde
#define ST7735_NVCTR3  0xdf
#define ST7735_GAMCTRP1 0xe0
#define ST7735_GAMCTRN1 0xe1


typedef struct 
{
    unsigned char width;
    unsigned char height;
    const unsigned char *bitmap;
} BM_t;

void st7735_writecmd(unsigned char cmd);
void st7735_writedat(unsigned char dat);

void st7735_init(void);

void st7735_set_addrwindow(unsigned char x0, unsigned char y0,
                         unsigned char x1, unsigned char y1);
void st7735_fill_16(unsigned short color);
void st7735_pixel(unsigned char x, unsigned char y, unsigned short color);

void st7735_img(unsigned char x, unsigned char y,
                   unsigned char width, unsigned char height,
                   unsigned short *bm);

void st7735_bitmap(unsigned char x, unsigned char y,
                   BM_t *bm, unsigned char index,
                   unsigned short color, unsigned short bg);

#endif

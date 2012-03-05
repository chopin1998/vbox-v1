#ifndef _DISP_H
#define _DISP_H

#include "io.h"


#define TFT_BL_ON    (TFT_SD_PORT.OUTCLR = TFT_BL_bm)
#define TFT_BL_OFF   (TFT_SD_PORT.OUTSET = TFT_BL_bm)

#define TFT_RST_ON   (TFT_SD_PORT.OUTCLR = TFT_RST_bm)
#define TFT_RST_OFF  (TFT_SD_PORT.OUTSET = TFT_RST_bm)

#define TFT_DAT      (TFT_SD_PORT.OUTSET = TFT_RS_bm)
#define TFT_CMD      (TFT_SD_PORT.OUTCLR = TFT_RS_bm)

#define TFT_CS_ON    (TFT_SD_PORT.OUTCLR = TFT_CS_bm)
#define TFT_CS_OFF   (TFT_SD_PORT.OUTSET = TFT_CS_bm)

#define SD_CS_ON     (TFT_SD_PORT.OUTCLR = SD_CS_bm)
#define SD_CS_OFF    (TFT_SD_PORT.OUTSET = SD_CS_bm)


#define TFT_SPI      SPIE
#define SD_SPI       SPIE
#define TFT_SPI_vect  SPIE_INT_vect



#define DISP_NOP    0x00
#define DISP_SWRST  0x01
#define DISP_ID     0x04
#define DISP_STATUS 0x09
#define DISP_RDDPM  0x0a
#define DISP_RDMADCTL 0x0b
#define DISP_RDCOLMOD 0x0c
#define DISP_RDDIM  0x0d
#define DISP_RDDSM  0x0e
#define DISP_SLPIN  0x10
#define DISP_SLPOUT 0x11
#define DISP_PTLON  0x12
#define DISP_NORON  0x13
#define DISP_INVOFF 0x20
#define DISP_INVON  0x21
#define DISP_GAMSET 0x26
#define DISP_DISPOFF 0x28
#define DISP_DISPON 0x29
#define DISP_CASET  0x2a
#define DISP_RASET  0x2b
#define DISP_RAMWR  0x2c
#define DISP_RGBSET 0x2d
#define DISP_RAMRD  0x2e
#define DISP_PTLAR  0x30
#define DISP_TEOFF  0x34
#define DISP_TEON   0x35
#define DISP_MADCTL 0x36
#define DISP_IDMOFF 0x38
#define DISP_IDMON  0x39
#define DISP_COLMOD 0x3a
#define DISP_RDID1  0xda
#define DISP_RDID2  0xdb
#define DISP_RDID3  0xdc
#define DISP_FRMCTR1 0xb1
#define DISP_FRMCTR2 0xb2
#define DISP_FRMCTR3 0xb3
#define DISP_INVCTR  0xb4
#define DISP_PWCTR1  0xc0
#define DISP_PWCTR2  0xc1
#define DISP_PWCTR3  0xc2
#define DISP_PWCTR4  0xc3
#define DISP_PWCTR5  0xc4
#define DISP_VMCTR1  0xc5
#define DISP_VMOFCTR 0xc7
#define DISP_WRID2   0xd1
#define DISP_WRID3   0xd2
#define DISP_NVCTR1  0xd9
#define DISP_NVCTR2  0xde
#define DISP_NVCTR3  0xdf
#define DISP_GAMCTRP1 0xe0
#define DISP_GAMCTRN1 0xe1


void disp_writecmd(unsigned char cmd);
void disp_writedat(unsigned char dat);
void disp_init(void);

void disp_set_addrwindow(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1);
void disp_fill(unsigned short color);
void disp_pixel(unsigned char x, unsigned char y, unsigned short color);




#endif

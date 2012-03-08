#ifndef _DISP_H
#define _DISP_H

#include "st7735.h"

void disp_line(unsigned char x1, unsigned char y1,
               unsigned char x2, unsigned char y2, unsigned short color);

void disp_box(unsigned char x, unsigned short y,
              unsigned char b, unsigned short a,
              unsigned short color, unsigned char solid);

void disp_circle(unsigned char cx, unsigned char cy,
                 unsigned char radius, unsigned short color);

void disp_string(unsigned char x, unsigned char y,
                 BM_t *bm, unsigned short color, unsigned short bg,
                 unsigned char *buf);

unsigned short disp_16color(unsigned char r, unsigned char g, unsigned char b);




#endif

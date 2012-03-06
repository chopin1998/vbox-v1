#ifndef _DISP_H
#define _DISP_H

void disp_line(unsigned char x1, unsigned char y1,
               unsigned char x2, unsigned char y2, unsigned short color);

void disp_box(unsigned char x, unsigned short y,
              unsigned char b, unsigned short a,
              unsigned short color, unsigned char solid);

void disp_circle(unsigned char cx, unsigned char cy,
                 unsigned char radius, unsigned short color);

unsigned short disp_16color(unsigned char r, unsigned char g, unsigned char b);




#endif

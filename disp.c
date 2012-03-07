#include "common.h"
#include "disp.h"

#include "st7735.h"


void disp_line(unsigned char x1, unsigned char y1,
               unsigned char x2, unsigned char y2, unsigned short color)
{

    int CurrentX, CurrentY, Xinc, Yinc, Dx, Dy,
        TwoDx, TwoDy, TwoDxAccumulatedError, TwoDyAccumulatedError;

    Dx = (x2-x1);
    Dy = (y2-y1);

    TwoDx = Dx + Dx;
    TwoDy = Dy + Dy;

    CurrentX = x1;
    CurrentY = y1;

    Xinc = 1;
    Yinc = 1;

    if (Dx < 0) 
    {
        Xinc = -1;
        Dx = -Dx;
        TwoDx = -TwoDx;
    }

    if (Dy < 0) 
    {
        Yinc = -1;
        Dy = -Dy;
        TwoDy = -TwoDy;
    }

    st7735_pixel(x1, y1, color);
    if ((Dx != 0) || (Dy != 0)) 
    {
        if (Dy <= Dx) 
        {
            TwoDxAccumulatedError = 0;

            do 
            {
                CurrentX += Xinc;
                TwoDxAccumulatedError += TwoDy;

                if(TwoDxAccumulatedError > Dx) 
                {
                    CurrentY += Yinc;
                    TwoDxAccumulatedError -= TwoDx;
                }
                st7735_pixel(CurrentX, CurrentY, color);
            }
            while (CurrentX != x2);
        }
        else 
        {
            TwoDyAccumulatedError = 0;
            
            do 
            {
                CurrentY += Yinc;
                TwoDyAccumulatedError += TwoDx;

                if(TwoDyAccumulatedError>Dy) 
                {
                    CurrentX += Xinc;
                    TwoDyAccumulatedError -= TwoDy;
                }
                st7735_pixel(CurrentX,CurrentY, color);
            }
            while (CurrentY != y2);
        }
    }
}


void disp_box(unsigned char x, unsigned short y,
              unsigned char b, unsigned short a,
              unsigned short color, unsigned char solid)
{
    unsigned int i, j;

    if (!solid)
    {
        for (j=0; j<a; j++)
        {
            st7735_pixel(x, y+j, color);
            st7735_pixel(x+b-1, y+j, color);
        }
        for (j = 0; j < b; j++)
        {
            st7735_pixel(x+j, y, color);
            st7735_pixel(x+j, y+a-1, color);
        }
    }
    else
    {
        for (j=0; j<a; j++)
        {
            for (i=0; i<b; i++)
            {
                st7735_pixel(x+i, y+j, color);
            }
        }
    }
}

void disp_circle(unsigned char cx, unsigned char cy,
                 unsigned char radius, unsigned short color)
{
    int x, y, xchange, ychange, radiusError;

    x = radius;
    y = 0;

    xchange = 1 - 2 * radius;
    ychange = 1;

    radiusError = 0;

    while(x >= y)
    {
        st7735_pixel(cx+x, cy+y, color);
        st7735_pixel(cx-x, cy+y, color);
        st7735_pixel(cx-x, cy-y, color);
        st7735_pixel(cx+x, cy-y, color);
        st7735_pixel(cx+y, cy+x, color);
        st7735_pixel(cx-y, cy+x, color);
        st7735_pixel(cx-y, cy-x, color);
        st7735_pixel(cx+y, cy-x, color);

        y++;

        radiusError += ychange;
        ychange += 2;

        if ( 2*radiusError + xchange > 0 ) 
        {
            x--;
            radiusError += xchange;
            xchange += 2;
        }
    }
}

unsigned short disp_16color(unsigned char r, unsigned char g, unsigned char b)
{
    return  (r & 0xf8) << 8 | (g & 0xfc) << 3 | b >> 3;
}


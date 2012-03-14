#include "common.h"
#include "uart.h"
#include "uart_process.h"
#include "util.h"
#include "gps.h"

GPS_t gps;


void gps_process(void)
{
    char para[24][16];
    unsigned char p_count=0, p_sub_count=0;
    unsigned char i, rev;
    unsigned char *p_buf = LB_GPS.buf;

    /* init */
    for (i=0; i<24; i++)
    {
        para[i][0] = 0x0;
    }

    /* spliting */
    while (*p_buf)
    {
        rev = *p_buf;
        
        switch (rev)
        {
        case ',':
            if (p_sub_count == 0)
            {
                para[p_count][p_sub_count] = ' ';
                p_sub_count++;
            }
            
            para[p_count][p_sub_count] = 0x0;            
            p_count++;
            p_sub_count = 0;
            
            if (p_count >= 23) 
            {
                p_count = 0;
                p_sub_count = 0;
            }
            break;

        case '\r':
            para[p_count][p_sub_count] = 0x0;
            break;
            
        default:
            para[p_count][p_sub_count] = rev;
            p_sub_count++;
            if (p_sub_count >= 15)
            {
                p_sub_count = 0;
            }
            break;
        }

        p_buf++;
    }

    /* processing */
    /*
    for (i=0; i<24; i++)
    {
        if (!para[i][0])
        {
            break;
        }

        printf("%s|", para[i]);
    }
    printf("\n");
    */

    if (!strcmp(para[0], "GPGGA"))
    { // provides the current Fix data
        gps.gga_updated = 1;
        
        strncpy(gps.utc, para[1], 10);
        strncpy(gps.latitude, para[2], 9);
        strncpy(gps.ns_indicator, para[3], 1);
        strncpy(gps.longitude, para[4], 10);
        strncpy(gps.ew_indicator, para[5], 1);
        strncpy(gps.pos_fix_indicator, para[6], 1);
        strncpy(gps.satellites_used, para[7], 2);

        printf("%s, %s, %s, %s, %s, %s, %s\n",
               gps.utc, gps.latitude, gps.ns_indicator,
               gps.longitude, gps.ew_indicator, gps.pos_fix_indicator,
               gps.satellites_used);
    }
    else if (!strcmp(para[0], "GPGSA"))
    { // provides the satellite status data
    }
    else if (!strcmp(para[0], "GPRMC"))
    { // provides the minimum gps sentences info.
    }
    else if (!strcmp(para[0], "GPGSV"))
    {
    }
    else if (!strcmp(para[0], "GPGLL"))
    {
    }
    else if (!strcmp(para[0], "GPVTG"))
    {
    }
    else
    {
    }
}

unsigned char gps_gga_updated(void)
{
    unsigned char rev;
    
    if (gps.gga_updated)
    {
        rev = 1;
        gps.gga_updated = 0;
    }
    else
    {
        rev = 0;
    }

    return rev;
}

#ifndef _GPS_H
#define _GPS_H


#define GPS_STX '$'
#define GPS_ETX '\n'

typedef struct
{
    /* GGA */
    unsigned char gga_updated;
    unsigned char utc[11];
    unsigned char latitude[10];
    unsigned char latitude_polar[2];
    unsigned char longitude[11];
    unsigned char longitude_polar[2];
    unsigned char quality[2];
    unsigned char satellity_number[3];
    
} GPS_t;

extern GPS_t gps;



void uart_process_lb_gps(void);



#endif

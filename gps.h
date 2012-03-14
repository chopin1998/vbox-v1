#ifndef _GPS_H
#define _GPS_H

#define GPS_STX '$'
#define GPS_ETX '\n'

typedef struct
{
    /* GGA */
    unsigned char gga_updated;
    
    unsigned char utc[11];      /* time in utc, hhmmss.sss */
    unsigned char latitude[10]; /* ddmm.mmmm */
    unsigned char ns_indicator[2]; /* North or South */
    unsigned char longitude[11];   /* dddmm.mmmm */
    unsigned char ew_indicator[2]; /* East or West */
    unsigned char pos_fix_indicator[2]; /* 0: invalid, 1: SPS, 2: diff GPS, 3-5:not support, 6: dead reckoning */
    unsigned char satellites_used[3];  /* number of satellites, 0 ~ 12 */
    unsigned char hdop[4];      /* Horizontal Dilution of Precision */
    unsigned char altitude[4];  /* MSL altitude */
    unsigned char altitude_units[2];      /*  */
    unsigned char geoid_separation[10];   /*  */
    unsigned char geoid_units[2];         /*  */
    unsigned char age_of_diff_corr[10];   /*  */
    unsigned char diff_ref_station_id[5]; /*  */
    
    
} GPS_t;

extern GPS_t gps;



void gps_process(void);
unsigned char gps_gga_updated(void);


#endif

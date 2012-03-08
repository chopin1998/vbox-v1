#include "common.h"
#include "uart.h"
#include "uart_process.h"
#include "util.h"
#include "gps.h"

GPS_t gps;


void uart_process_lb_gps(void)
{
    P_LIST_t *para_head, *curr;
    char *p = NULL;
    unsigned char p_count = 0;

    para_head = (P_LIST_t *)malloc(sizeof(P_LIST_t));

    p = strtok(&LB_GPS.buf[0], ",");
    curr = para_head;

    while (p)
    {
        p_count++;

        curr->para = p;
        curr->next = (P_LIST_t *)malloc(sizeof(P_LIST_t));
        curr = curr->next;

        p = strtok(NULL, "|");
    }
    curr->next = NULL;

    if ( !strcmp(para_head->para, "GPGGA") )
    {
        gps.gga_updated = 1;

        /*
        strncpy(gps.utc, para[1], 10);
        strncpy(gps.latitude, para[2], 9);
        strncpy(gps.latitude_polar, para[3], 1);
        strncpy(gps.longitude, para[4], 10);
        strncpy(gps.longitude_polar, para[5], 1);
        strncpy(gps.quality, para[6], 1);
        strncpy(gps.satellity_number, para[7], 2);
        */
    }
    else
    {
        printf("got a %s\n", para_head->para);
    }

    
    p_list_clear(para_head);
}

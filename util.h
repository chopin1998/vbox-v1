#ifndef _UTIL_H
#define _UTIL_H


typedef struct _p_list
{
    char *para;
    struct _p_list *next;
} P_LIST_t;
void p_list_clear(P_LIST_t *head);

char* p_list_para(P_LIST_t *head, unsigned char index);


void limit_i(int *val, int bottom, int top);
void limit_f(float *val, float bottom, float top);

unsigned bcd2bin(unsigned char val);
unsigned char bin2bcd(unsigned val);

unsigned char week_of_day(unsigned int year, unsigned char mon, unsigned char day);

#endif

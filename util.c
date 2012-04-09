#include "common.h"
#include "util.h"


void p_list_clear(P_LIST_t *head)
{
    P_LIST_t *curr, *tmp;

    curr = head;
    while (curr)
    {
        tmp = curr->next;
        free(curr);
        curr = tmp;
    }
}

char * p_list_para(P_LIST_t *head, unsigned char index)
{
    P_LIST_t *curr;

    curr = head;
    for (unsigned char i=0; i<index; i++)
    {
        if (curr->para == NULL)
        {
            return NULL;
        }
        curr = curr->next;
    }

    return curr->para;
}

void limit_i(int *val, int bottom, int top)
{
    if (*val < bottom)
    {
        *val = bottom;
    }
    else if (*val > top)
    {
        *val = top;
    }
}

void limit_f(float *val, float bottom, float top)
{
    if (*val < bottom)
    {
        *val = bottom;
    }
    else if (*val > top)
    {
        *val = top;
    }
}


unsigned bcd2bin(unsigned char val)
{
    return (val & 0x0f) + (val >> 4) * 10;
}

unsigned char bin2bcd(unsigned val)
{
    return ((val / 10) << 4) + val % 10;
}

unsigned char week_of_day(unsigned int year, unsigned char mon, unsigned char day)
{
    /*
      Zeller's congruence
          assert after Oct 4, 1582
    */
    signed char rev;
    
    unsigned char c = year / 100;
    unsigned char y = year % 100;

    rev = y + y/4 + c/4 - 2*c + (26*(mon+1)/10) + day - 1;
    rev %= 7;
    if (rev < 0)
    {
        rev += 7;
        rev %= 7;
    }
    
    return rev;
}

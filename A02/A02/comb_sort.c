#include "sorting_methods.h"
//not working well
void comb_sort(T *data,int first,int one_after_last)
{
    int gap = one_after_last-first;
    int swap = 1;
    while(gap != 1 || swap ==1)
    {
        int a = (gap*10)/13;
        gap = (a>1) ? gap*10/13:1;
        swap = 0;
        for(int i=0; i<one_after_last-first-gap;i++)
        {
            if(data[i] > data[i+gap])
            {
                T tmp = data[i];
                data[i] = data[i+gap];
                data[i+gap] = tmp;
                swap = 1;
            }
        }
    }
}

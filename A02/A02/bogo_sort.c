#include "sorting_methods.h"
#include <stdlib.h>
#include <stdio.h>

int sorted(T *data, int first, int one_after_last)
{
    for(int i = first; i < one_after_last-1;i++)
    {
        if(data[i] > data[i+1])
            return -1;
    }
    return 1;
}

void shuffle(T *data, int first, int one_after_last)
{
    for(int i=first; i<one_after_last; i++)
    {
        int idx = rand()%(one_after_last-first) + first;
        int tmp = data[i];
        data[i] = data[idx];
        data[idx] = tmp;
    }
}
void bogo_sort(T *data, int first, int one_after_last)
{
    while(sorted(data,first,one_after_last) == -1)
    {
        shuffle(data,first,one_after_last);
    }
}

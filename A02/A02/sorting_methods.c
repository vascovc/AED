//
// Tomás Oliveira e Silva, AED, December 2020
//
// sorting algorithms
//
// Things to do:
//   1. (mandatory)
//      Compile and run this program and redirect its output to a file
//      This can be done by running the following commands
//      > make sorting_methods
//      > ./sorting_methods -measure | tee output.txt
//      The program will take some time to finish (somewhere between 1 hour and 4 hours)
//   2. (highly recommended)
//      Read and understand the code of the main function.
//   2. (mandatory)
//      Write the report
//   2a.  In the report draw graphs of the average execution time for each sorting algorithm
//        and try to approximate the data points by a known function, such as A*n^2+B*B+C or A*n*log(n)+B*n+C
//   2b.  For each algorithm, what can you say about the *observed* best and worst execution times (comment!)
//   2c.  Which algorithm would you choose? Consider the execution time and the effort to write and verify the actual code.
//

#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorting_methods.h"
#include "../P02/elapsed_time.h"

void show(T *data,int first,int one_after_last)
{
  int i;

  printf("[%2d,%2d]",first,one_after_last - 1);
  for(i = first;i < one_after_last;i++)
    printf(" %5d",data[i]);
  printf("\n");
}

int main(int argc,char *argv[argc])
{
  static struct
  {
    sort_function_t function;
    char *name;
  }
  functions[] =
  {
#define EXPAND(name)  { name,# name }
    
    EXPAND(bubble_sort),
    EXPAND(shaker_sort),
    EXPAND(insertion_sort),
    EXPAND(Shell_sort),
    EXPAND(quick_sort),
    EXPAND(merge_sort),
    EXPAND(heap_sort),
    EXPAND(rank_sort),
    EXPAND(selection_sort),
  
    EXPAND(tree_sort),
    EXPAND(bogo_sort)
#undef EXPAND
  };
#define N_FUNCTIONS (int)(sizeof(functions) / sizeof(functions[0]))

  //
  // test the functions
  //
  if(argc == 2 && strcmp(argv[1],"-test") == 0)
  {
# define MAX_N   1000  // test array sizes up to this limit
# define N_TESTS  100  // number of tests to perform for each array size
    int i,j,k,n,first,one_after_last;
    T master[MAX_N],data[MAX_N];

    srand((unsigned int)time(NULL));
    for(n = 1;n <= MAX_N;n++)
    {
      for(i = 0;i < n;i++)
        master[i] = (T)((int)rand() % MAX_N);
      first = 0;
      one_after_last = n;
      for(j = 0;j < N_TESTS;j++)
      {
        fprintf(stderr,"%4d[%4d,%4d] \r",n,first,one_after_last);
        for(k = 0;k < N_FUNCTIONS;k++)
        {
          for(i = 0;i < first;i++)
            data[i] = (T)(-1);
          for(;i < one_after_last;i++)
            data[i] = master[i];
          for(;i < n;i++)
            data[i] = (T)(-1);
          (*functions[k].function)(data,first,one_after_last);
          if(data[first] < (T)(0) || (first > 0 && data[first - 1] != (T)(-1)) || (one_after_last < n && data[one_after_last] != (T)(-1)))
          {
            fprintf(stderr,"%s() failed for n=%d, first=%d, and one_after_last=%d (access error) --- 😒\n",functions[k].name,n,first,one_after_last);
            exit(1);
          }
          for(i = first + 1;i < one_after_last;i++)
            if(data[i] < data[i - 1])
            {
              show(data,first,one_after_last);
              fprintf(stderr,"%s() failed for n=%d, first=%d, and one_after_last=%d (sort error for i=%d) --- 😒\n",functions[k].name,n,first,one_after_last,i);
              exit(1);
            }
        }
        first = (int)rand() % (1 + (3 * n) / 4);
        do
          one_after_last = (int)rand() % (1 + n);
        while(one_after_last <= first);
      }
    }
    //
    // done
    //
    printf("No errors found --- 😀\n");
    return 0;
# undef MAX_N
# undef N_TESTS
  }
  //
  // measure the cpu time of all sorting routines
  //
  if(argc == 2 && strcmp(argv[1],"-measure") == 0)
  {
# define MAX_N          10000000  // largest array size
# define N_MEASUREMENTS     1000  // number of measurements to perform for each value of n
# define N_EXTRA              50  // half the number of extra measurements (to discard N_EXTRA possible outliers on each side)
# define MAX_TIME           500.0  // maximum amount of time, in seconds, spent in a value of n
    double v,w,t[N_MEASUREMENTS + 2 * N_EXTRA];
    int f_idx,n_idx,n,i,j;
    T *data;

    data = (T *)malloc((size_t)MAX_N * sizeof(T));
    if(data == NULL)
    {
      fprintf(stderr,"unable to allocate memory for the data array --- 😒\n");
      exit(1);
    }
    for(f_idx = 0;f_idx < N_FUNCTIONS;f_idx++)
    {
      printf("# %s\n",functions[f_idx].name);
      printf("#      n  min time  max time  avg time   std dev\n");
      printf("#------- --------- --------- --------- ---------\n");
      for(n_idx = 10;n_idx <= 80;n_idx++)
      {
        n = (int)round(pow(10.0,0.1 * (double)n_idx));
        //n = n_idx;
        
        if(n <= MAX_N)
        {
          srand((unsigned int)n_idx); // make sure are sorting routines receive the same data
          for(i = 0;i < N_MEASUREMENTS + 2 * N_EXTRA;i++)
          {
            for(j = 0;j < n;j++)
              data[j] = (T)rand();
            v = cpu_time();
            (*functions[f_idx].function)(data,0,n);
            v = cpu_time() - v;
            // insertion sort!
            for(j = i;j > 0 && t[j - 1] > v;j--)
              t[j] = t[j - 1];
            t[j] = v;
          }
          v = 0.0;
          for(i = N_EXTRA;i < N_EXTRA + N_MEASUREMENTS;i++)
            v += t[i];
          v /= (double)N_MEASUREMENTS;
          w = 0.0;
          for(i = N_EXTRA;i < N_EXTRA + N_MEASUREMENTS;i++)
            w += (t[i] - v) * (t[i] - v);
          w /= (double)N_MEASUREMENTS;
          printf("%8d %.3e %.3e %.3e %.3e\n",n,t[N_EXTRA],t[N_EXTRA + N_MEASUREMENTS - 1],v,sqrt(w));
          fflush(stdout);
          if((double)N_MEASUREMENTS * v >= MAX_TIME)
            break; // too much time spent on this value of n; skip the remining ones
        }
      }
      printf("#------- --------- --------- --------- ---------\n");
      printf("\n\n");
      fflush(stdout);
    }
    free(data);
    return 0;
# undef MAX_N
# undef N_MEASUREMENTS
# undef N_EXTRA
# undef MAX_TIME
  }
  //
  // usage message
  //
  fprintf(stderr,"usage: %s -test     # test all sorting routines\n",argv[0]);
  fprintf(stderr,"       %s -measure  # measure the cpu time of all sorting routines\n",argv[0]);
  return 1;
}

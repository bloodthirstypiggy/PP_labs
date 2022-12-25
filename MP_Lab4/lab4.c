#include <stdio.h>
#include <omp.h>
#include <stdlib.h>


#ifndef _OPENMP
   #define MESSAGE "no omp"
#endif

int main()
{
    printf("%d", _OPENMP);
}

#include <stdio.h>
#include <omp.h>

int main(){
int a=0, b=0, c=0;
#pragma omp parallel num_threads(4)
{
    #pragma omp atomic
    a;
    #pragma omp critical
    printf("hello fro am thread number: %d \n", omp_get_thread_num());
    c = c + 1;
}
printf("single: %d -- critical: %d\n, just c:%d \n", a, b, c);
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
    const int count = 1000000;     ///< Number of array elements
    const int threads = 8;         ///< Number of parallel threads to use
    const int random_seed = 920215; ///< RNG seed
    int column = 10;

    int** array = 0;                 ///< The array we need to find the max in
    int  max   = -1;                ///< The maximal element
    int t = 0;                   ///  Used time
    int t_end=0;
    double time_taken = 0;
    /* Initialize the RNG */
    srand(random_seed);
    double delta;
    struct timespec tstart = {0,0}, tend = {0,0};

    double time_spec_seconds(struct timespec* ts) {
    
    return (double) ts->tv_sec + (double) ts->tv_nsec * 1.0e-9;
    }

    /* Determine the OpenMP support */
    printf("OpenMP: %d;\n======\n", _OPENMP);
    printf("time -> %ld", time(NULL));

    /* Generate the random array */
    array = (int**)malloc(column * sizeof(int*)); //line * column
    for(int i=0; i<column;i++)
    {
        array[i] = (int*)malloc(count * sizeof(int));
    }
    for(int i=0; i<column; i++)
    {
        for(int j=0; j<count;j++)
        {
            array[i][j] = rand();
        }
    }

    for(int j=1; j<threads + 1; j++)
    {

    for(int i=0; i<column; i++){
        int t = clock_gettime(CLOCK_THREAD_CPUTIME_ID, &tstart);
        max = -1;
    /* Find the maximal element */
    #pragma omp parallel num_threads(j) shared(array, count, column, i) reduction(max: max) default(none)
    {
  //      #pragma omp for
        
            #pragma omp for
            for(int j=0; j<count; j++){
            if(array[i][j] > max) {
                max = array[i][j]; 
            }
            }
        
        //}
    
      //  }
    }
    printf("\nArray number : %d Max is: %d;\n",i, max);
    t = clock_gettime(CLOCK_THREAD_CPUTIME_ID, &tend);
    delta = time_spec_seconds(&tend) - time_spec_seconds(&tstart);
    printf("Array number: %d with threads number: %d time spent is %f \n",i,j, delta);
    printf(" END\n \n \n");
}} //dopisal }}
return 0;
}

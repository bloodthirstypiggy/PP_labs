#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main(int argc, char** argv)
{
    const int count = 1000000;     ///< Number of array elements
    const int threads = 8;         ///< Number of parallel threads to use
    const int random_seed = 920215; ///< RNG seed
    int column = 10;

    double time;
    int** array = 0;                 ///< The array we need to find the max in
    int  max   = -1;                ///< The maximal element
    FILE* fd;
    fd = fopen ("test.txt","w");
    struct timeval start, end;

    /* Initialize the RNG */
    srand(random_seed);
    double delta;
    struct timespec tstart = {0,0}, tend = {0,0};

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
        printf("threads number: %d \n", j);
    gettimeofday(&start, NULL);
    time = omp_get_wtime();
    for(int i=0; i<column; i++){
        max = -1;
    /* Find the maximal element */
    #pragma omp parallel num_threads(j) shared(array, count, column, i) reduction(max: max) default(none)
    {
        
            #pragma omp for
            for(int j=0; j<count; j++){
            if(array[i][j] > max) {
                max = array[i][j]; 
            }
            }
    
    }
}
    gettimeofday(&end, NULL);
    time =omp_get_wtime() - time;
    delta = ((end.tv_sec  - start.tv_sec) * 1000000u + 
         end.tv_usec - start.tv_usec);
    fprintf(fd, "%f\n", time);
    printf("time is: %f \n", time);



}
  fclose(fd);
return 0;
}

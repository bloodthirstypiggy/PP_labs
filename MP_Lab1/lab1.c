#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
    const int count = 1000;     ///< Number of array elements
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

    /* Determine the OpenMP support */
    printf("OpenMP: %d;\n======\n", _OPENMP);

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
        t = clock();
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
        
        printf(" My lmax is: %d;\n", max);
        //}
    
      //  }
    }
    printf("\nMax is: %d;\n", max);
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("time spent is %f \n", time_taken);
    printf(" END\n \n \n");
}} //dopisal }}
return 0;
}

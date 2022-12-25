#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main(int argc, char** argv)
{
    int count = 10000000;     ///< Number of array elements
    const int random_seed = 920214; ///< RNG seed
    const int max_threads = 8;      ///< Number of parallel threads to use

    int* array = 0;                 ///< The array we need to find the max in
    int  index = count;                ///< The index of the element we need

    /* Initialize the RNG */
    srand(random_seed);


    /* Generate the random array */
    array = (int*)malloc(count*sizeof(int));
    for(int i=0; i<count; i++) { array[i] = rand(); }
    srand(time(NULL));
    const int target = array[rand() % count];          ///< Number to look for
//    const int target = -1;          ///< Number to look for
    // 1 THREAD:
    double t = omp_get_wtime();
    for(int i=0; i<count; i++)
    {
        if(array[i] == target)
        {
            index = i;
            break;
        }
    }
    if(index == count)
        printf("NOTHING WAS FOUND;\n");
    else
        printf("1THREAD: Found occurence of %d at index %d;\n", target, index);
    printf("TIME: %f\n", omp_get_wtime() - t);

    /* Find the index of the element */
    for (int threads = 1; threads <= max_threads; threads++) {
    t = omp_get_wtime();
    printf("\n");
    #pragma omp parallel num_threads(threads) shared(array, count, target) reduction(max: index) default(none)
        {
            index = count;
            #pragma omp for
            for (int i = 0; i < count; i++) {
                if (array[i] == target) {
                    index = i;
                    count = 0;
                }
            }
        }
        if(index == count)
            printf("NOTHING WAS FOUND;\n");
        else
            printf("MP; %d THREADS: Found occurence of %d at index %d;\n", threads, target, index);
        printf("TIME: %f\n", omp_get_wtime() - t);
    }
    return(0);
}

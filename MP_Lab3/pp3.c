#include <stdio.h>
#include <omp.h>
#include <sys/time.h>
#include <stdlib.h>


void InsertSort(int arr[], int i, int length,  int half){
	int temp = 0;
	int j = 0;

	for (int f = half + i; f < length; f = f + half)
	{
		j = f;
		while(j > i && arr[j - half] > arr[j])
		{
			temp = arr[j];
			arr[j] = arr[j - half];
			arr[j - half] = temp;
			j = j - half;
		}
	}
}


void Shell(int A[], int n, int k){
	int h;
	int j = 0;
	int temp = 0;
	for(h = n / 2; h > 0; h = h / 2)
	{
		#pragma omp parallel for num_threads(k) shared(A, n, h)
		for(int i = 0; i < h; i++)
		{
			InsertSort(A, i, n, h);
		}
	}
}


int main(){
	int i, n = 10000000;
	int *A = (int*)malloc(n * sizeof(int));
	int *B = (int*)malloc(n * sizeof(int));
	for (i = 0; i < n; i++){
		A[i] = rand();
		B[i] = A[i];
		//cout << A[i] << ' ';
	}
	//cout << endl;
	for (int k = 1; k < 9; ++k){
		double start = omp_get_wtime();
		Shell(A, n, k);
		double end = omp_get_wtime();
        FILE* fd;
        fd = fopen("result.txt", "a");
		fprintf(fd,"%f\n", end - start);
        fclose(fd);
		for (int j = 0; j < 10000000; ++j){
			A[j] = B[j];
		}
		//std::cout << std::endl << "========Time for " << k << " threads is " << end - start << std::endl;
	}
	printf("\n");
	free(A);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define SIZE 1024

int a[SIZE][SIZE];
int b[SIZE][SIZE];

int c[SIZE][SIZE];

void init_matrix() {
	int i = 0;
	int j = 0;

	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			a[i][j] = rand() % 10;
			b[i][j] = rand() % 10;			
		}
	}

}


int min(int a, int b) {
	if (b < a) {
		return b;
	}

	return a;
}

void multiply_tiling(int block) {

	int n = SIZE;
	int p = SIZE;
	int m = SIZE;

	for (int i = 0; i < n; i+=block) {
		for (int j = 0; j < p; j+=block) {
			for (int k = 0; k < m; k+=block) {
				for (int ii = i; ii < min(i + block, n); ii++) {
					for (int jj = j; jj < min(j+block, p); jj++) {
						int sum = 0;
						for (int kk = k; kk < min(k+block, m); kk++) {
							int temp = a[ii][kk] * b[kk][jj];
							sum+=temp;
						}
						c[ii][jj]+=sum;
					}
				}
			}
		}
	}
}

void multiply_regular() {
	
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {       
			int sum = 0;
 			for (int k = 0; k < SIZE; k++) {
				sum = sum + a[i][k]*b[k][j];        
			}       
			c[i][j] = sum;      
		}    
	}
}

void print_matrix(int matrix[SIZE][SIZE]) {
	int i = 0;
	int j = 0;

	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			printf("%d\t", matrix[i][j]);
		} 
		printf("\n");
	}
}

int main(int argc, char *argv[]) {
	
	if (argc < 2) {
		printf("Please enter a tiling size\n");
		return 0;
	}

	int tiling_size = atoi(argv[1]);

	srand(time(NULL));	
	init_matrix();

	struct timeval start_time;
	struct timeval end_time;
	
	gettimeofday(&start_time, NULL);
	multiply_tiling(tiling_size);
	gettimeofday(&end_time, NULL);
	
	long elapsed = ((end_time.tv_sec * 1000000 + end_time.tv_usec) - (start_time.tv_sec * 1000000 + start_time.tv_usec));


//	print_matrix(a);
	printf("\n");
//	print_matrix(b);
	printf("\n");
	//print_matrix(c);
	printf("\n The amount of time it takes for a tiling size of %d is %ld\n", tiling_size, elapsed);
	return 1;
}

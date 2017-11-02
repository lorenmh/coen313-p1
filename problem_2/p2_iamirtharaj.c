#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define SIZE 4

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
	
	srand(time(NULL));	
	init_matrix();

	struct timespec start_time;
	struct timespec end_time;
	
//	gettimeofday(&start_time, NULL);
//	multiply_regular();
	multiply_tiling(2);
//	gettimeofday(&end_time, NULL);
	print_matrix(a);
	printf("\n");
	print_matrix(b);
	printf("\n");
	print_matrix(c);

	multiply_regular();
	printf("\n");
	print_matrix(c);
	return 1;
}

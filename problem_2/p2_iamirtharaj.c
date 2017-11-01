#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 3

int matrix1[SIZE][SIZE];
int matrix2[SIZE][SIZE];

int matrix3[SIZE][SIZE];

void init_matrix() {
	int i = 0;
	int j = 0;

	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			matrix1[i][j] = rand() % 10;
			matrix2[i][j] = rand() % 10;			
		}
	}

}

void multiply_regular() {
	
	int i;
	int j;
	int k;

	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {       
			int sum = 0;
 			for (k = 0; k < SIZE; k++) {
				sum = sum + matrix1[i][k]*matrix2[k][j];        
			}       
			matrix3[i][j] = sum;      
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
//	print_matrix(matrix1);
//	print_matrix(matrix2);
//	print_matrix(matrix3);
	// time
	multiply_regular();
	// end time		
	
	print_matrix(matrix3);

	return 1;
}

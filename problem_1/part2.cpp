// Immanuel Amirtharaj

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <unistd.h>



using namespace std;

#define SIZE 10000

uint8_t *large_array;

void init_array() {
	// srand(time(NULL));

	// for (int i = 0; i < SIZE; i++) {
	// 	large_array[i] = (char) (rand() % 256);
	// }

	uint8_t *temp_array = (uint8_t *) malloc(SIZE * sizeof(uint8_t));

	uint8_t offset = (uint64_t) temp_array % (32 * 1024);

	large_array = &temp_array[(32 * 1024) - offset]; // alligned to cache size


	for (int i = 0; i < SIZE; i++) {
		large_array[i] = temp_array[i * (32 * 1024)];
	}

	cout << "Finished initializing array" << endl;
}

// Takes in an integer of size in bytes
void run_experiment(int guess_size) {

	// because indexed from 0 to n-1
	int first_pos = guess_size - 1;
	int second_pos = guess_size;

	struct timeval start_time, end_time;

	// Brings the cache line into memory
	int first_element = large_array[first_pos];

	// Calculate the time it takes to access the next element
	gettimeofday(&start_time, NULL);
	int next_element = large_array[second_pos];
	gettimeofday(&end_time, NULL);

	double time_for_last = (end_time.tv_usec) - (start_time.tv_usec);
	cout << start_time.tv_sec << " and " << start_time.tv_usec << endl;
	cout << end_time.tv_sec << " and " << start_time.tv_usec << endl;
	cout << "time for last is 	" << time_for_last << endl;

}

int main(int argc, char* argv[]) {

	init_array();

	for (int i = 4; i < 11; i++) {
		int guess_size = pow(2, i);
	//	run_experiment(guess_size);
	}


	return 0;
}

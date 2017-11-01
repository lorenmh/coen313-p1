#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>

// 256k
#define BUF_SIZE 1024 * 1024
#define NUM_RUNS 3000

// buf for clearing
uint8_t cbuf[BUF_SIZE];

// buf for test
uint8_t tbuf[BUF_SIZE];

void clear() {
	uint8_t v;
	for (int i = 0; i < BUF_SIZE; i++) v = cbuf[i];
}

uint32_t utime() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return 1000000 * tv.tv_sec + tv.tv_usec;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("first arg should be cache size in KB\n");
		exit(1);
	}

	int cache_sz_kb = atoi(argv[1]);

	printf("Using cache size of %d KB\n", cache_sz_kb);


	for (int assoc = 2; assoc < 16; assoc++) {
		double sum_nonassoc = 0;
		double sum_assoc = 0;

		for (int run = 0; run < NUM_RUNS; run++) {
			clear();

			for (int i = 0; i <= assoc; i++) {
				uint32_t start = utime();
				uint8_t byte = tbuf[i * cache_sz_kb * 1024];
				uint32_t end = utime();

				if (i == assoc) sum_assoc += end - start;
				else if (i == assoc-1) sum_nonassoc += end - start;
			}
		}

		double avg_nonassoc = sum_nonassoc / NUM_RUNS;
		double avg_assoc = sum_assoc / NUM_RUNS;

		printf("==============================\n");
		printf("Results for Associativity %d\n", assoc);
		printf("Time for miss which maps to same set: %f\n", avg_nonassoc);
		printf(
			"Time for miss which *would* require the set to remove an item: "
			"%f\n\n",
			avg_assoc
		);
	}
}

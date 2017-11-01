#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>

// 256k
#define BUF_SIZE 1024 * 256
#define NUM_RUNS 20000

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


	for (int assoc = 2; assoc <= 8; assoc++) {
		double sum_evict = 0;
		double sum_base = 0;

		for (int run = 0; run < NUM_RUNS; run++) {
			clear();

			for (int i = 0; i <= assoc; i++) {
				uint8_t byte = tbuf[i * cache_sz_kb * 1024];
			}

			uint8_t byte;
			uint32_t start;
			uint32_t end;

			// baseline
			int base = assoc*cache_sz_kb*1024;
			start = utime();
			byte = tbuf[base];
			end = utime();

			sum_base += end - start;

			// evict
			start = utime();
			byte = tbuf[0];
			end = utime();

			sum_evict += end - start;
		}

		double avg_evict = sum_evict / NUM_RUNS;
		double avg_base = sum_base / NUM_RUNS;

		printf("==============================\n");
		printf("Results for Associativity %d\n", assoc);
		printf("eviction time: %f\n", avg_evict);
		printf("baseline for comparison: %f\n\n", avg_base);
	}
}

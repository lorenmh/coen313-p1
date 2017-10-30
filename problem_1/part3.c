#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// 1 meg
#define BUF_SIZE 1024 * 1024

// buf for clearing
uint8_t cbuf[BUF_SIZE];

// buf for test
uint8_t tbuf[BUF_SIZE];

void clear() {
    uint8_t v;
    for (int i = 0; i < BUF_SIZE; i++) v = cbuf[i];
}

int test_assoc(int sz_kb, int assoc) {
    clear();

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("first arg should be cache size in KB\n");
        exit(1);
    }
    uint8_t cache_sz_kb = atoi(argv[1]);
    printf("Using cache size of %d KB\n", cache_sz_kb);
}

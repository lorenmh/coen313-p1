#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#define NUM_OF_NBYTES   64              // number of megabytes or kilobytes used
#define KILOBYTE        1024            // number of bytes in a kilobyte
#define MEGABYTE        1024 * 1024     // number of bytes in a megabyte

int arrayLength = NUM_OF_NBYTES * KILOBYTE;
uint8_t* mallocArray;

void setupArray() {

    mallocArray = malloc(sizeof(uint8_t) * NUM_OF_NBYTES * KILOBYTE);

}

void firstTraversal() {

    int i;
    uint8_t buffer;

    for (i = 0; i < arrayLength ; i++) {
        mallocArray[i] = i % 100;
    }

}

void secondTraversal() {

    int i;
    uint8_t buffer;
    struct timeval start, end;
    
    gettimeofday(&start, NULL);
    
    for (i = 0; i < arrayLength ; i++) {
        mallocArray[i] = i % 100;
    }

    gettimeofday(&end, NULL);

    printf("%ld microseconds\n", 
            ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));

}


int main() {

    setupArray();
    firstTraversal();
    secondTraversal();

}

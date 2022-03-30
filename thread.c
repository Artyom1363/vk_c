// compile in docker with: gcc -g -lm -pthread thread.c
#include <stdlib.h> // EXIT_SUCCESS
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "structures.h"
#include "timeThreads.h"
#include "calculating.h"

#define MAX_COORD 10

#define THREADS_QUANTITY 20

int main() {

    // vectorsForThreads* vectorsThreadsStart = generateData(VECTORS_QUANTITY, THREADS_QUANTITY);
    // return 0;
    // vectorsForThreads* vectorsThreadsPtr = vectorsThreadsStart;
    // vector* start = vectorsThreadsStart->start;
    // printf("Quantity of vectors: %d\n", calculateVectorsQuantity(start));
    // return 0;
    // showData(start);
    vector* array = createArrayOfVectors(VECTORS_QUANTITY, DIMENTIONS);

    timeMethods(3, 0, array, VECTORS_QUANTITY, THREADS_QUANTITY);
    
    return 0;
}


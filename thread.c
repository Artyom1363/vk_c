// compile in docker with: gcc -g -lm -pthread thread.c
#include <stdlib.h> // EXIT_SUCCESS
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "logic_lib/structures.h"
#include "logic_lib/timeThreads.h"
#include "logic_lib/calculating.h"



int main() {

    vector* array = createArrayOfVectors(VECTORS_QUANTITY, DIMENTIONS);
    // printf("Vectors:\n");
    // for (int i = 0; i < VECTORS_QUANTITY; ++i) {
        // showVector((array + i), DIMENTIONS);
    // }
    timeMethods(3, 3, array, VECTORS_QUANTITY, THREADS_QUANTITY);

    deleteArrayOfVectors(array, VECTORS_QUANTITY);
    
    return 0;
}


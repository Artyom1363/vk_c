// compile in docker with: gcc -g -lm -pthread thread.c
#include <stdlib.h> // EXIT_SUCCESS
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "logic_lib/structures.h"
#include "logic_lib/timeThreads.h"
#include "logic_lib/calculating.h"



int main(int argc, char *argv[]) {
    int opt, threads = 0;
    char *opts = "p:", c;

    while ((opt = getopt(argc, argv, opts)) != -1) {
        printf("optopt=%c, opt=%c, optarg=%s\n", optopt, opt, optarg);
        switch (opt) {
            case 'p': threads = optarg ? atoi(optarg) : 0; break;
            default: break;
        }
    }
    if (threads == 0) {
        printf("You have not set threads quantity, we will use default value: 4\n");
        printf("If you want to set threads quantity set -p5 (for example)\n");
    } else {
        printf("You set number of threads: %d\n", threads);
    }
    // printf("optimal quantity of processors: %d\n", get_nprocs());
    printf("Number of threads: %d\n", threads);
    vector* array = createArrayOfVectors(VECTORS_QUANTITY, DIMENTIONS);
    // printf("Vectors:\n");
    // for (int i = 0; i < VECTORS_QUANTITY; ++i) {
        // showVector((array + i), DIMENTIONS);
    // }
    timeMethods(3, 1, array, VECTORS_QUANTITY, THREADS_QUANTITY);

    deleteArrayOfVectors(array, VECTORS_QUANTITY);
    
    return 0;
}


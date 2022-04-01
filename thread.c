#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "structures.h"
#include "timeThreads.h"
#include "calculating.h"



void showVector(vector* vect, int dimension) {
    for (int i = 0; i < dimension; ++i) {
        printf("%lf ", (vect->coords)[i]);
    }
    printf("\n");
}

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
        printf("You have not set threads quantity, so the launch will be with the default value: 4\n");
        printf("If you want to set threads quantity set -p5 (for example)\n");
        threads = 4;
    } else {
        printf("You set number of threads: %d\n", threads);
    }
    // printf("optimal quantity of processors: %d\n", get_nprocs());
    printf("Number of threads: %d\n", threads);

    vector* array = createArrayOfVectors(VECTORS_QUANTITY, DIMENTIONS);

    // THIS IS ONLY ONE TIME!
    /*dataVectors* arrData = malloc(sizeof(dataVectors));
    arrData->array = array;
    arrData->size = VECTORS_QUANTITY;
    arrData->dimension = DIMENTIONS;
    char name[30] = "data/vectors.txt";
    writeArrayOfVectors(arrData, name);
    return 0;
    */
    // printf("Vectors:\n");
    // for (int i = 0; i < VECTORS_QUANTITY; ++i) {
        // showVector((array + i), DIMENTIONS);
    // }
    timeMethods(1, 1, array, VECTORS_QUANTITY, threads);

    deleteArrayOfVectors(array, VECTORS_QUANTITY);
    
    return 0;
}


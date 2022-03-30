#include <stdio.h>
#include "structures.h"

vector createVector(int dimentions) {
    vector res;
    res.coords = malloc(sizeof(double) * dimentions);
    for (int i = 0; i < dimentions; ++i) {
        (res.coords)[i] = (rand() % MAX_COORD) / ZNAM;
    }
    return res;
}

vector* createArrayOfVectors(int vectorsQuan, int threadsQuan) {
    if (threadsQuan < 1) {
        return NULL;
    }

    vector* startVector = malloc(sizeof(vector) * vectorsQuan);
    for (int i = 0; i < vectorsQuan; ++i) {
        (startVector[i]) = createVector(DIMENTIONS);
    }
    return startVector;
}

void showVector(vector vect, int dim) {
    for (int i = 0; i < dim; ++i) {
        printf("%lf ", (vect.coords)[i]);
    }
    printf("\n");
}



// returns list, with pointers to array of vector for each tread
vectorsForThreads* separateByThreads(vector* arrayOfVectors, int vectorsQuan, int threadsQuan) {
    if (threadsQuan < 1) {
        return NULL;
    }
    // printf("DEBUG IN structures/separate... vectorsQuan: %d \n", vectorsQuan);
    // printf("threads quan: %d \n", threadsQuan);
    vectorsForThreads* ptrForThreads = malloc(sizeof(vectorsForThreads) * threadsQuan);
    int dataForThread = vectorsQuan / threadsQuan;
    for (int i = 0; i < threadsQuan; ++i) {
        (ptrForThreads[i]).start = arrayOfVectors + i * dataForThread;
        (ptrForThreads[i]).quantity = dataForThread;
        // printf("DEBUG in structures/separate... ptr is %x\n", (ptrForThreads[i]).start);
    }

    (ptrForThreads[threadsQuan - 1]).quantity += vectorsQuan - threadsQuan * dataForThread;

    return ptrForThreads;
}


// считает количество векторов в списке
int calculateVectorsQuantity(vectorsForThreads* ptrForThreads, int threadsQuan) {
    int count = 0;
    for (int i = 0; i < threadsQuan; ++i) {
        count += (ptrForThreads[i]).quantity;
    }
    return count;
}

vector* copyVector(vector* vect, int dim) {
    vector* res = malloc(sizeof(vector));
    res->coords = malloc(sizeof(int) * dim);
    for (int i = 0; i < dim; ++i) {
        (res->coords)[i] = (vect->coords)[i];
    }
    return res;
}
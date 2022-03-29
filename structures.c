#include "structures.h"

vector* createVector(int dimentions) {
    vector* res = NULL;
    res = malloc(sizeof(vector));
    res->coords = malloc(sizeof(double) * dimentions);
    for (int i = 0; i < dimentions; ++i) {
        (res->coords)[i] = 1 + rand();
    }
    res->next = NULL;
    return res;
}



// returns list, with pointers to array of vector for each tread
vectorsForThreads* generateData(int vectorsQuan, int threadsQuan) {
    if (threadsQuan < 1) {
        return NULL;
    }
    int dataForThread = vectorsQuan / threadsQuan;

    vector* startVector = NULL;
    vector* endVector = NULL;

    vectorsForThreads* partitionStart = NULL;
    vectorsForThreads* partitionEnd = NULL;

    for (int threadNum = 1; threadNum <= threadsQuan; ++threadNum) {
        if (threadNum == threadsQuan) dataForThread += vectorsQuan - threadsQuan * dataForThread;
        for (int i = 0; i < dataForThread; ++i) {
            if (startVector == NULL) {
                startVector = createVector(DIMENTIONS);
                endVector = startVector;
            } else {
                endVector->next = createVector(DIMENTIONS);
                endVector = endVector->next;
            }
        }
        if (partitionStart == NULL) {
            partitionStart = malloc(sizeof(vectorsForThreads));
            partitionEnd = partitionStart;
        } else {
            partitionEnd->next = malloc(sizeof(vectorsForThreads));
            partitionEnd = partitionEnd->next;
        }
        partitionEnd->start = startVector;
        partitionEnd->end = endVector;
        partitionEnd->next = NULL;

        startVector = endVector;

    }
    
    return partitionStart;
}


int calculateVectorsQuantity(vector* start) {
    int count = 0;
    while (start != NULL) {
        ++count;
        start = start->next;
    }
    return count;
}
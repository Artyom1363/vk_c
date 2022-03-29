#ifndef STRUCTURES
#define STRUCTURES

#include <stdlib.h>

#define VECTORS_QUANTITY 1e8
#define DIMENTIONS 15

// this is struct with vectors
typedef struct vector {
    double* coords;
    struct vector* next;
} vector;


// this struct uses to transfer data for threads
typedef struct data {
    //vector for which we want to calculate min dist
    vector* initial;
    vector* start;
    vector* end;
} data;


// this is struct contains pointers (to vectors) for threads
typedef struct vectorsForThread {
    vector* start;
    vector* end;
    struct vectorsForThread* next;
} vectorsForThreads;

vector* createVector(int dimentions);

vectorsForThreads* generateData(int vectorsQuan, int threadsQuan);

int calculateVectorsQuantity(vector* start);

#endif
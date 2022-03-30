#ifndef STRUCTURES
#define STRUCTURES

#include <stdlib.h>

#define VECTORS_QUANTITY 1e8
#define DIMENTIONS 15

// this is struct with vectors
typedef struct vector {
    double* coords;
    // struct vector* next;
} vector;


// this struct uses to transfer data for threads
typedef struct data {
    //vector for which we want to calculate min dist
    vector* initial;
    vector* start;
    int quantity;
} data;


// this is struct contains pointers (to vectors) for threads
typedef struct vectorsForThread {
    vector* start;
    int quantity;
    // struct vectorsForThread* next;
} vectorsForThreads;

vector createVector(int dimentions);

vector* createArrayOfVectors(int vectorsQuan, int threadsQuan);

vectorsForThreads* separateByThreads(vector* arrayOfVectors, int vectorsQuan, int threadsQuan);

int calculateVectorsQuantity(vectorsForThreads* ptrForThreads, int threadsQuan);

#endif
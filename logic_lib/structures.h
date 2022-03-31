#ifndef STRUCTURES
#define STRUCTURES

#include <stdlib.h>

#define VECTORS_QUANTITY 10
#define DIMENTIONS 5
#define MAX_COORD 500
#define ZNAM 400.0
#define THREADS_QUANTITY 1

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
    vector* answer;
    int quantity;
} data;

// this struct uses to return value from scaned file
typedef struct dataVectors {
    vector* array;
    int size;
    int dimension;
} dataVectors;

// this is struct contains pointers (to vectors) for threads
typedef struct vectorsForThread {
    vector* start;
    int quantity;
    // struct vectorsForThread* next;
} vectorsForThreads;

vector createVector(int dimentions);

vector* createArrayOfVectors(int vectorsQuan, int dimension);

void scanVector(FILE* file, vector* vect, int dimension);

dataVectors* scanArrayOfVectors(char* fileName);

void writeVector(FILE* file, vector* vect, int dimension);

void writeArrayOfVectors(dataVectors* dataArr, char* fileName);

vectorsForThreads* separateByThreads(vector* arrayOfVectors, int vectorsQuan, int threadsQuan);

void showVector(vector vect, int dim);

vector* copyVector(vector* vect, int dim);

#endif
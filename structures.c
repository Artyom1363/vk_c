#include "structures.h"

vector createVector(int dimentions) {
    vector res;
    res.coords = malloc(sizeof(double) * dimentions);
    for (int i = 0; i < dimentions; ++i) {
        (res.coords)[i] = 1 + rand();
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



// returns list, with pointers to array of vector for each tread
vectorsForThreads* separateByThreads(vector* arrayOfVectors, int vectorsQuan, int threadsQuan) {
    if (threadsQuan < 1) {
        return NULL;
    }
    vectorsForThreads* ptrForThreads = malloc(sizeof(vectorsForThreads) * threadsQuan);
    int dataForThread = vectorsQuan / threadsQuan;
    for (int i = 0; i < threadsQuan; ++i) {
        (ptrForThreads[i]).start = arrayOfVectors + i * dataForThread;
        (ptrForThreads[i]).quantity = dataForThread;
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
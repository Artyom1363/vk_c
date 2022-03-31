#ifndef CALCULATING
#define CALCULATING

#include <stdlib.h> 
#include <pthread.h>
#include <stdio.h>
#include <math.h>

#include "structures.h"


double calculateCosineDist(vector* v1, vector* v2, int dimentions);

vector* getMinVector(dataVectors* dataArr, vector* initialVect);

void *thread_routine(void *arg);

void buildThreads(vector* arrayOfVectors, int sizeOfArray, vector* initialVect, int threadsQuantity);

void buildOneThread(vector* arrayOfVectors, int sizeOfArray, vector* initialVect);

#endif
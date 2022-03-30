#ifndef CALCULATING
#define CALCULATING

#include <stdlib.h> 
#include <pthread.h>
#include <stdio.h>
#include <math.h>

#include "structures.h"


double calculateCosineDist(vector v1, vector v2, int dimentions);

void *thread_routine(void *arg);

void buildTreads(vector* arrayOfVectors, int sizeOfArray, vector* initialVect, int threadsQuantity);

void buildOneTread(vector* arrayOfVectors, int sizeOfArray, vector* initialVect);

#endif
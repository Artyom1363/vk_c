#include "calculating.h"


double calculateCosineDist(vector v1, vector v2, int dimentions) {
    double cosMultiplication = 0;
    double lenOfVectorV1 = 0, sqOfLenOfVectorV1 = 0;
    double lenOfVectorV2 = 0, sqOfLenOfVectorV2 = 0;
    double cosDist = 0;
    for (int i = 0; i < dimentions; ++i) {
        cosMultiplication += (v1.coords)[i] * (v2.coords)[i];
        sqOfLenOfVectorV1 += (v1.coords)[i] * (v1.coords)[i];
        sqOfLenOfVectorV2 += (v2.coords)[i] * (v2.coords)[i];
    }
    lenOfVectorV1 = sqrt(sqOfLenOfVectorV1);
    lenOfVectorV2 = sqrt(sqOfLenOfVectorV2);
    cosDist = cosMultiplication / (lenOfVectorV1 * lenOfVectorV2);
    return cosDist;
}

vector* getMinVector(vector* array, vector* initialVect, int sizeOfArray, int dim) {
    double minDist = -2.0;
    int numOfBestVect;
    for (int i = 0; i < sizeOfArray; ++i) {
        double dist = calculateCosineDist(array[i], *initialVect, dim);
        if (dist > minDist) {   
            minDist = dist;
            numOfBestVect = i;
        }
    }
    // printf("Best vect: %d", numOfBestVect);
    return copyVector(&array[numOfBestVect], dim);
}

void *thread_routine(void *arg) {
    
    data* threadData = (data*)arg;
    vector* initialVect = threadData->initial;
    vector* startCalc = threadData->start;
    int quantity = threadData->quantity;
    // printf("DEBUG in calc/thread_routine... ptr is %x\n", startCalc);
    vector* bestVect = getMinVector(startCalc, initialVect, 
                                    threadData->quantity, DIMENTIONS);

    // put vector for transfered pointer
    *(threadData->answer) = *(bestVect);
    return NULL;
}


void buildThreads(vector* arrayOfVectors, int sizeOfArray, vector* initialVect, int threadsQuantity) {
    
    vectorsForThreads* vectorsThreads = separateByThreads(arrayOfVectors, sizeOfArray, threadsQuantity);
    // printf("initial vector: \n");
    // showVector(*initialVect, DIMENTIONS);
    // for (int i = 0; i < threadsQuantity; ++i) {
        // printf("DEBUG in calc/buildThreads ptr is %x\n", vectorsThreads[i].start);
    // }
    // showVector(*(vectorsThreads->start), DIMENTIONS);
    // printf("DEBUG: quantity of vectors:%d\n", calculateVectorsQuantity(vectorsThreads, threadsQuantity));

    data* threadData = malloc(sizeof(data) * threadsQuantity);

    vector* minVectors = malloc(sizeof(vector) * threadsQuantity);

    // array this threads
    pthread_t *threads = malloc(sizeof(pthread_t) * threadsQuantity);

    // creating threads
    for (int i = 0; i < threadsQuantity; ++i) {
        threadData[i].initial = initialVect;
        threadData[i].start = vectorsThreads[i].start;
        threadData[i].answer = (minVectors + i);
        threadData[i].quantity = vectorsThreads[i].quantity;
        int errflag = 0;
        errflag = pthread_create(&(threads[i]), NULL, thread_routine, &(threadData[i]));

        // check error
        if (errflag != 0) {
            printf("Caught error in create thread in cycle: %d\n", errflag);
        }
    }

    // waiting for all threads
    for (int i = 0; i < threadsQuantity; ++i) {
        pthread_join(threads[i], NULL);
        // showVector(minVectors[i], DIMENTIONS);
    }
    vector* bestVect = getMinVector(minVectors, initialVect, threadsQuantity, DIMENTIONS);
    printf("Best vector is:\n");
    showVector(*bestVect, DIMENTIONS);
    printf("DIST: %f\n", calculateCosineDist(*bestVect, *initialVect, DIMENTIONS));
}

void buildOneThread(vector* arrayOfVectors, int sizeOfArray, vector* initialVect) {
    // printf("initial vector: \n");
    // showVector(*initialVect, DIMENTIONS);
    // malloc(sizeof(int));
    // data* threadData = malloc(sizeof(data));
    // threadData->initial = initialVect;
    // threadData->start = arrayOfVectors;
    // threadData->quantity = sizeOfArray;
    vector* bestVect = malloc(sizeof(vector));
    // threadData->answer = bestVect;
    bestVect = getMinVector(arrayOfVectors, initialVect, sizeOfArray, DIMENTIONS);
    // printf("sizeOfArray: %d\n", sizeOfArray);
    // thread_routine(threadData);
    showVector(*bestVect, DIMENTIONS);
    printf("DIST: %f\n", calculateCosineDist(*bestVect, *initialVect, DIMENTIONS));
}
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
}


void *thread_routine(void *arg) {
    
    data* threadData = (data*)arg;
    vector* initialVect = threadData->initial;
    vector* startCalc = threadData->start;
    int quantity = threadData->quantity;
    int count = 0;
    double minDist = 1000.0;
    for (int i = 0; i < threadData->quantity; ++i) {
        double dist = calculateCosineDist(startCalc[i], *initialVect, DIMENTIONS);
        if (dist < minDist) { minDist = dist; }
    }
    // printf("Min dist is:%f\n", minDist);
    // printf("Done!\nProcessed %d vectors\n", count);
    return NULL;
}


void buildTreads(vector* arrayOfVectors, int sizeOfArray, vector* initialVect, int threadsQuantity) {
    
    vectorsForThreads* vectorsThreads = separateByThreads(arrayOfVectors, sizeOfArray, threadsQuantity);

    printf("DEBUG: quantity of vectors:%d\n", calculateVectorsQuantity(vectorsThreads, threadsQuantity));

    data* threadData = malloc(sizeof(data) * threadsQuantity);

    // array this threads
    pthread_t *threads = malloc(sizeof(pthread_t) * threadsQuantity);

    // creating threads
    for (int i = 0; i < threadsQuantity; ++i) {
        threadData[i].initial = initialVect;
        threadData[i].start = vectorsThreads[i].start;
        threadData[i].quantity = vectorsThreads[i].quantity;
        int errflag = 0;
        errflag = pthread_create(&threads[i], NULL, thread_routine, &threadData[i]);

        // check error
        if (errflag != 0) {
            printf("Caught error in create thread in cycle: %d\n", errflag);
        }
    }

    // waiting for all threads
    for (int i = 0; i < threadsQuantity; ++i) {
        pthread_join(threads[i], NULL);
    }
    
}

void buildOneTread(vector* start, int sizeOfArray, vector* initialVect) {

    data* threadData = malloc(sizeof(data));
    threadData->initial = initialVect;
    threadData->start = start;
    threadData->quantity = sizeOfArray;
    int errflag = 0;
    pthread_t thread;

    // create and tun POSIX thread
    errflag = pthread_create(&thread, NULL, thread_routine, threadData);
    // check if thread_create call was successful
    if (errflag != 0) {
        printf("Caught error: %d\n", errflag);
    }
    // printf("Thread id: %ld\n", thread);
    pthread_join(thread, NULL);

    
}
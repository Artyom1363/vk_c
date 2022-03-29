#include "calculating.h"


double calculateCosineDist(vector* v1, vector* v2, int dimentions) {
    double cosMultiplication = 0;
    double lenOfVectorV1 = 0, sqOfLenOfVectorV1 = 0;
    double lenOfVectorV2 = 0, sqOfLenOfVectorV2 = 0;
    double cosDist = 0;
    for (int i = 0; i < dimentions; ++i) {
        cosMultiplication += (v1->coords)[i] * (v2->coords)[i];
        sqOfLenOfVectorV1 += (v1->coords)[i] * (v1->coords)[i];
        sqOfLenOfVectorV2 += (v2->coords)[i] * (v2->coords)[i];
    }
    lenOfVectorV1 = sqrt(sqOfLenOfVectorV1);
    lenOfVectorV2 = sqrt(sqOfLenOfVectorV2);
    cosDist = cosMultiplication / (lenOfVectorV1 * lenOfVectorV2);
}


void *thread_routine(void *arg) {
    
    data* dat = (data*)arg;
    vector* initialVect = dat->initial;
    vector* startCalc = dat->start;
    vector* endCalc = dat->end;
    int count = 0;
    double minDist = 1000.0;
    while (startCalc != endCalc) {
        double dist = calculateCosineDist(startCalc, initialVect, DIMENTIONS);
        if (dist < minDist) { minDist = dist; }
        ++count;
        startCalc = startCalc->next;
    }
    // printf("Min dist is:%f\n", minDist);
    // printf("Done!\nProcessed %d vectors\n", count);
    return NULL;
}


void buildTreads(vectorsForThreads* vectorsThreadsStart, int threadsQuantity) {
    vectorsForThreads* vectorsThreadsPtr = vectorsThreadsStart;
    data* dat = malloc(sizeof(data) * threadsQuantity);
    vector* initialVector = vectorsThreadsStart->start;
    pthread_t *threads = malloc(sizeof(pthread_t) * threadsQuantity);

    // creating threads
    for (int i = 0; i < threadsQuantity; ++i) {
        dat[i].initial = initialVector;
        dat[i].start = vectorsThreadsPtr->start;
        dat[i].end = vectorsThreadsPtr->end;
        vectorsThreadsPtr = vectorsThreadsPtr->next;
        int errflag = 0;
        errflag = pthread_create(&threads[i], NULL, thread_routine, &dat[i]);

        // check if thread_create call was successful
        if (errflag != 0) {
            printf("Main: caught error in create thread in cycle: %d\n", errflag);
        }
        // printf("Thread id: %ld\n", threads[i]);
    }

    // waiting for all threads
    for (int i = 0; i < threadsQuantity; ++i) {
        pthread_join(threads[i], NULL);
    }
    
}

void buildOneTread(vector* start) {

    data* dat = malloc(sizeof(data));
    dat->initial = start;
    dat->start = start;
    dat->end = NULL;
    int errflag = 0;
    pthread_t thread;

    // create and tun POSIX thread
    errflag = pthread_create(&thread, NULL, thread_routine, dat);
    // check if thread_create call was successful
    if (errflag != 0) {
        printf("Main: caught error: %d\n", errflag);
    }
    // printf("Thread id: %ld\n", thread);
    pthread_join(thread, NULL);

    
}
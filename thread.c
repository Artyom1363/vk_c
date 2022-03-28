#include <stdlib.h> // EXIT_SUCCESS
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define MAX_COORD 10

#define THREADS_QUANTITY 20
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



vector* createVector(int dimentions) {
    vector* res = NULL;
    res = malloc(sizeof(vector));
    res->coords = malloc(sizeof(double) * dimentions);
    for (int i = 0; i < dimentions; ++i) {
        (res->coords)[i] = 1 + rand() % MAX_COORD;
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

/*
void showData(vector* start) {
    while (start != NULL) {
        printf("Vector:\n");
        printf("x1: %d\n", start->x1);
        printf("x1: %d\n", start->x2);
        start = start->next;
    }
}
*/


int calculateVectorsQuantity(vector* start) {
    int count = 0;
    while (start != NULL) {
        ++count;
        start = start->next;
    }
    return count;
}

double calculateCosineDist(vector* v1, vector *v2, int dimentions) {
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
    time_t startTime, endTime;
    startTime =  time(NULL);
    
    // buildTreads(vectorsThreadsStart, THREADS_QUANTITY);
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
    printf("Min dist is:%f\n", minDist);
    printf("Done!\nProcessed %d vectors\n", count);
    endTime = time(NULL);
    printf("Time of working:%f\n", difftime(endTime, startTime));
    return NULL;
}


void buildTreads(vectorsForThreads* vectorsThreadsStart, int treadsQuantity) {
    vectorsForThreads* vectorsThreadsPtr = vectorsThreadsStart;
    data* dat = malloc(sizeof(data) * treadsQuantity);
    for (int i = 0; i < treadsQuantity; ++i) {
        dat[i].initial = NULL;
        dat[i].start = vectorsThreadsPtr->start;
        dat[i].end = vectorsThreadsPtr->end;
        vectorsThreadsPtr = vectorsThreadsPtr->next;
        int errflag = 0;
        pthread_t thread;
        errflag = pthread_create(&thread, NULL, thread_routine, &dat[i]);
        // check if thread_create call was successful
        if (errflag != 0) {
            printf("Main: caught error in create thread in cycle: %d\n", errflag);
        }
        printf("Main: thread id: %ld\n", thread);
    }
    pthread_exit(0);
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
    printf("Main: thread id: %ld\n", thread);
    pthread_exit(0);
}

int main() {
    vectorsForThreads* vectorsThreadsStart = generateData(VECTORS_QUANTITY, THREADS_QUANTITY);
    // return 0;
    vectorsForThreads* vectorsThreadsPtr = vectorsThreadsStart;
    vector* start = vectorsThreadsStart->start;
    printf("Quantity of vectors: %d\n", calculateVectorsQuantity(start));
    // return 0;
    // showData(start);
    time_t startTime, endTime;
    startTime =  time(NULL);
    // buildTreads(vectorsThreadsStart, THREADS_QUANTITY);

    buildOneTread(start);
    endTime = time(NULL);
    printf("Time of working:%f\n", difftime(endTime, startTime));
    
    
    return 0;
}

// compile in docker with: gcc -g -lm -pthread thread.c
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

void timeMethods(int quanWithMultiThreads, int quanWithOneTread, 
                 vector* start, vectorsForThreads* vectorsThreadsStart);


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


int calculateVectorsQuantity(vector* start) {
    int count = 0;
    while (start != NULL) {
        ++count;
        start = start->next;
    }
    return count;
}

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

int main() {


    vectorsForThreads* vectorsThreadsStart = generateData(VECTORS_QUANTITY, THREADS_QUANTITY);
    // return 0;
    vectorsForThreads* vectorsThreadsPtr = vectorsThreadsStart;
    vector* start = vectorsThreadsStart->start;
    printf("Quantity of vectors: %d\n", calculateVectorsQuantity(start));
    // return 0;
    // showData(start);

    timeMethods(1, 1, start, vectorsThreadsStart);
    
    return 0;
}

void timeMethods(int quanWithMultiThreads, int quanWithOneTread, 
                 vector* start, vectorsForThreads* vectorsThreadsStart) {

    int threadsQuan = THREADS_QUANTITY;
    for (int i = 0; i < quanWithMultiThreads; ++i) {
        struct timespec begin, end;
        double elapsed;
        clock_gettime(CLOCK_MONOTONIC, &begin);

        buildTreads(vectorsThreadsStart, THREADS_QUANTITY);

        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed = end.tv_sec - begin.tv_sec;
        elapsed += (end.tv_nsec - begin.tv_nsec) / 1000000000.0;
        printf("Time by %d threads:%f\n", threadsQuan, elapsed);
    }

    for (int i = 0; i < quanWithOneTread; ++i) {
        struct timespec begin, end;
        double elapsed;
        clock_gettime(CLOCK_MONOTONIC, &begin);

        buildOneTread(start);

        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed = end.tv_sec - begin.tv_sec;
        elapsed += (end.tv_nsec - begin.tv_nsec) / 1000000000.0;
        printf("Time by one thread:%f\n", elapsed);
    }
}
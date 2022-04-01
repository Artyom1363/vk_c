#include "calculating.h"


double calculateCosineDist(vector* v1, vector* v2, int dimentions) {
    if (v1 == NULL || v2 == NULL) {
        printf("ERROR: CALLED calculateCosineDist WITH NULL VECTOR\n");
        return 2.0;
    }
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
    return cosDist;
}

vector* getMinVector(dataVectors* dataArr, vector* initialVect) {
    if (dataArr == NULL) {
        printf("ERROR getMinVector: GOT NULL VALUE in first parameter\n");
        return NULL;
    }
    if (initialVect == NULL) {
        printf("ERROR getMinVector: GOT NULL VALUE in second parameter\n");
        return NULL;
    }
    int sizeOfArray = dataArr->size;
    int dimension = dataArr->dimension;
    vector* array = dataArr->array;


    double minDist = -2.0;
    int numOfBestVect = 0;

    for (int i = 0; i < sizeOfArray; ++i) {
        double dist = calculateCosineDist((dataArr->array + i), initialVect, dimension);
        if (dist > 1.1) {
            printf("ERROR getMinVector: GET ERROR FROM calculateCosineDist\n");
            return NULL;
        }
        if (dist > minDist) {   
            minDist = dist;
            numOfBestVect = i;
        }
    }
    // printf("Best vect: %d", numOfBestVect);
    return copyVector((dataArr->array + numOfBestVect), dimension);
}

void *thread_routine(void *arg) {
    if (arg == NULL) {
        printf("ERROR thread_routine: GOT NULL VALUE as parameter\n");
        return NULL;
    }
    data* threadData = (data*)arg;
    vector* initialVect = threadData->initial;
    vector* startCalc = threadData->start;
    int quantity = threadData->quantity;
    // printf("DEBUG in calc/thread_routine... ptr is %x\n", startCalc);

    dataVectors* dataArr = malloc(sizeof(dataVectors));
    dataArr->array = startCalc;
    dataArr->size = threadData->quantity;
    dataArr->dimension = DIMENTIONS;
    vector* bestVect = getMinVector(dataArr, initialVect);
    free(dataArr);

    // put vector for transfered pointer
    *(threadData->answer) = *(bestVect);
    free(bestVect);
    return NULL;
}


vector* buildThreads(vector* arrayOfVectors, int sizeOfArray, vector* initialVect, int threadsQuantity) {
    
    if (arrayOfVectors == NULL) {
        printf("ERROR buildThreads: first parameter is NULL\n");
        return NULL;
    }
    if (initialVect == NULL) {
        printf("ERROR buildThreads: third parameter is NULL\n");
        return NULL;
    }
    vectorsForThreads* vectorsThreads = separateByThreads(arrayOfVectors, sizeOfArray, threadsQuantity);
    // printf("initial vector: \n");
    // showVector(*initialVect, DIMENTIONS);
    // for (int i = 0; i < threadsQuantity; ++i) {
        // printf("DEBUG in calc/buildThreads ptr is %x\n", vectorsThreads[i].start);
    // }
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
    free(threads);
    free(threadData);
    free(vectorsThreads);

    dataVectors* dataArr = malloc(sizeof(dataVectors));
    dataArr->array = minVectors;
    dataArr->size = threadsQuantity;
    dataArr->dimension = DIMENTIONS;
    vector* bestVect = getMinVector(dataArr, initialVect);
    free(dataArr);

    // printf("Best vector is:\n");
    // showVector(bestVect, DIMENTIONS);
    // printf("DIST: %f\n", calculateCosineDist(bestVect, initialVect, DIMENTIONS));

    deleteArrayOfVectors(minVectors, threadsQuantity);
    return bestVect;
}

vector* buildOneThread(vector* arrayOfVectors, int sizeOfArray, vector* initialVect) {

    if (arrayOfVectors == NULL) {
        printf("ERROR buildOneThread: first parameter is NULL\n");
        return NULL;
    }
    if (initialVect == NULL) {
        printf("ERROR buildOneThread: third parameter is NULL\n");
        return NULL;
    }

    dataVectors* dataArr = malloc(sizeof(dataVectors));
    dataArr->array = arrayOfVectors;
    dataArr->size = sizeOfArray;
    dataArr->dimension = DIMENTIONS;
    vector* bestVect = getMinVector(dataArr, initialVect);
    free(dataArr);

    // showVector(bestVect, DIMENTIONS);

    // printf("DIST: %f\n", calculateCosineDist(bestVect, initialVect, DIMENTIONS));
    return bestVect;
}
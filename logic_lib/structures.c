#include <stdio.h>
#include "structures.h"


vector createVector(int dimension) {
    vector res;
    res.coords = malloc(sizeof(double) * dimension);
    for (int i = 0; i < dimension; ++i) {
        (res.coords)[i] = (rand() % MAX_COORD) / ZNAM;
    }
    return res;
}

vector* createArrayOfVectors(int vectorsQuan, int dimension) {
    if (vectorsQuan == 0) {
        return NULL;
    }

    vector* startVector = malloc(sizeof(vector) * vectorsQuan);
    for (int i = 0; i < vectorsQuan; ++i) {
        (startVector[i]) = createVector(dimension);
    }
    return startVector;
}

// this func needs a pointer to empty vector
void scanVector(FILE* file, vector* vect, int dimension) {
    if (vect == NULL) return;
    if (file == NULL) return;
    vect->coords = malloc(sizeof(double) * dimension);
    for (int i = 0; i < dimension; ++i) {
        fscanf(file, "%lf", &(vect->coords[i]));
    }
}

dataVectors* scanArrayOfVectors(char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        return NULL;
    }
    int vectorsQuan = 0;
    int dimension = 0;
    dataVectors* dataFromFile = malloc(sizeof(dataVectors));
    fscanf(file, "%d %d", &vectorsQuan, &dimension);

    vector* arrayOfVectors = malloc(sizeof(vector) * vectorsQuan);
    for (int i = 0; i < vectorsQuan; ++i) {
        arrayOfVectors[i].coords = malloc(sizeof(double) * dimension);
        scanVector(file, arrayOfVectors + i, dimension);
    }
    fclose(file);
    dataFromFile->array = arrayOfVectors;
    dataFromFile->size = vectorsQuan;
    dataFromFile->dimension = dimension;
    return dataFromFile;
}

void writeVector(FILE* file, vector* vect, int dimension) {
    if (vect == NULL) return;
    if (file == NULL) return;
    for (int i = 0; i < dimension; ++i) {
        fprintf(file, "%lf ", vect->coords[i]);
    }
    fprintf(file, "\n");
}

void writeArrayOfVectors(dataVectors* dataArr, char* fileName) {
    FILE* file = fopen(fileName, "w");
    fprintf(file, "%d %d\n", dataArr->size, dataArr->dimension);
    for (int i = 0; i < dataArr->size; ++i) {
        writeVector(file, dataArr->array, dataArr->dimension);
    }
} 

void showVector(vector vect, int dim) {
    for (int i = 0; i < dim; ++i) {
        printf("%lf ", (vect.coords)[i]);
    }
    printf("\n");
}



// returns list, with pointers to array of vector for each thread
vectorsForThreads* separateByThreads(vector* arrayOfVectors, int vectorsQuan, int threadsQuan) {
    if (threadsQuan < 1) {
        return NULL;
    }
    // printf("DEBUG IN structures/separate... vectorsQuan: %d \n", vectorsQuan);
    // printf("threads quan: %d \n", threadsQuan);
    vectorsForThreads* ptrForThreads = malloc(sizeof(vectorsForThreads) * threadsQuan);
    int dataForThread = vectorsQuan / threadsQuan;
    for (int i = 0; i < threadsQuan; ++i) {
        (ptrForThreads[i]).start = arrayOfVectors + i * dataForThread;
        (ptrForThreads[i]).quantity = dataForThread;
        // printf("DEBUG in structures/separate... ptr is %x\n", (ptrForThreads[i]).start);
    }

    (ptrForThreads[threadsQuan - 1]).quantity += vectorsQuan - threadsQuan * dataForThread;

    return ptrForThreads;
}


vector* copyVector(vector* vect, int dim) {
    vector* res = malloc(sizeof(vector));
    res->coords = malloc(sizeof(int) * dim);
    for (int i = 0; i < dim; ++i) {
        (res->coords)[i] = (vect->coords)[i];
    }
    return res;
}
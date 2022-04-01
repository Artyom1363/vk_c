#include <gtest/gtest.h>
#include <cmath>

extern "C" {
    #include "structures.h"
    #include "calculating.h"
}

#define EPS 0.00001


dataVectors* getTestVectors() {
    char nameRead[30] = "tests/data/vectors.txt";
    dataVectors* dataFromFile = scanArrayOfVectors(nameRead);
    return dataFromFile;
}

vector* getTestInitVect(int dimension) {
    vector* initialVect = (vector*)malloc(sizeof(vector));
    FILE* file = fopen("tests/data/initVect.txt", "r");
    scanVector(file, initialVect, dimension);
    fclose(file);
    return initialVect;
}


TEST(WorkWithFile, scanVector) {
    dataVectors* dataFromFile = getTestVectors();
    EXPECT_EQ(dataFromFile->size, 10);
    EXPECT_EQ(dataFromFile->dimension, 3);
    EXPECT_EQ((dataFromFile->array->coords)[0], 1.0);
    EXPECT_EQ((dataFromFile->array->coords)[1], 2.0);
    EXPECT_EQ((dataFromFile->array->coords)[2], 3.0);

    vector* initialVect = getTestInitVect(dataFromFile->dimension);
    EXPECT_EQ(initialVect->coords[0], 1.0);
    EXPECT_EQ(initialVect->coords[1], 1.0);
    EXPECT_EQ(initialVect->coords[2], 1.0);

    char name[30] = "tests/data/test_data.txt";
    writeArrayOfVectors(dataFromFile, name);
    deleteArrayOfVectors(dataFromFile->array, dataFromFile->size);
    free(dataFromFile);

    char nameRead[30] = "tests/data/vectors.txt";
    dataVectors* dataFromWroteFile = scanArrayOfVectors(nameRead);


    EXPECT_EQ(dataFromWroteFile->size, 10);
    EXPECT_EQ(dataFromWroteFile->dimension, 3);
    EXPECT_EQ((dataFromWroteFile->array->coords)[0], 1.0);
    EXPECT_EQ((dataFromWroteFile->array->coords)[1], 2.0);
    EXPECT_EQ((dataFromWroteFile->array->coords)[2], 3.0);

    deleteArrayOfVectors(dataFromWroteFile->array, dataFromWroteFile->size);
    free(dataFromWroteFile);


}


TEST(Structures, separateByThreads) {
    vector* testVector = createVector(3);
    deleteVector(testVector);

    int threadsQuan = 3;
    int vectorsQuan = 10;
    vector* arrayOfVectors = createArrayOfVectors(vectorsQuan, threadsQuan);
    vectorsForThreads* vectThreads = separateByThreads(arrayOfVectors, vectorsQuan, threadsQuan);
    EXPECT_EQ(vectThreads[0].quantity, 3);
    EXPECT_EQ(vectThreads[1].quantity, 3);
    EXPECT_EQ(vectThreads[2].quantity, 4);

    EXPECT_EQ(vectThreads[0].start, arrayOfVectors);
    EXPECT_EQ(vectThreads[1].start, (arrayOfVectors + 3));
    EXPECT_EQ(vectThreads[2].start, (arrayOfVectors + 6));

    int count = 0;
    for (int i = 0; i < threadsQuan; ++i) {
        count += (vectThreads[i]).quantity;
    }
    EXPECT_EQ(count, 10);

    deleteArrayOfVectors(arrayOfVectors, vectorsQuan);
    free(vectThreads);

}

TEST(Calculating, calculateCosineDist) {

    EXPECT_EQ(calculateCosineDist(NULL, NULL, 10), 2.0);

    dataVectors* dataFromFile = getTestVectors();
    int dimension = dataFromFile->dimension;
    vector* initialVect = getTestInitVect(dimension);
    vector* vectors = dataFromFile->array;

    double dist;

    dist = calculateCosineDist(vectors, initialVect, dimension);
    EXPECT_TRUE(abs(dist - 0.92582009) < EPS);

    dist = calculateCosineDist(vectors + 1, initialVect, dimension);
    EXPECT_TRUE(abs(dist - 0.98019605) < EPS);

    dist = calculateCosineDist(vectors + 2, initialVect, dimension);
    EXPECT_TRUE(abs(dist - 0.98473192) < EPS);
    
    deleteVector(initialVect);
    deleteArrayOfVectors(dataFromFile->array, dataFromFile->size);
    free(dataFromFile);
}

TEST(Calculating, getMinVector) {
    dataVectors* dataFromFile = getTestVectors();
    vector* initialVect = getTestInitVect(dataFromFile->dimension);
    

    EXPECT_TRUE(getMinVector(dataFromFile, NULL) == NULL);
    EXPECT_TRUE(getMinVector(NULL, initialVect) == NULL);
    vector* bestVector = getMinVector(dataFromFile, initialVect);

    EXPECT_EQ(bestVector->coords[0], 3.0);
    EXPECT_EQ(bestVector->coords[1], 2.0);
    EXPECT_EQ(bestVector->coords[2], 3.0);

    deleteVector(initialVect);
    deleteVector(bestVector);
    deleteArrayOfVectors(dataFromFile->array, dataFromFile->size);
    free(dataFromFile);
}

TEST(Calculating, testParallel) {
    EXPECT_TRUE(thread_routine(NULL) == NULL);
    dataVectors* dataFromFile = getTestVectors();
    vector* initialVect = getTestInitVect(dataFromFile->dimension);
    
    vector* bestVector;

    bestVector = buildThreads(dataFromFile->array, dataFromFile->size, initialVect, 4);
    EXPECT_EQ(bestVector->coords[0], 3.0);
    EXPECT_EQ(bestVector->coords[1], 2.0);
    EXPECT_EQ(bestVector->coords[2], 3.0);
    deleteVector(bestVector);
    EXPECT_TRUE(buildThreads(NULL, 1, initialVect, 1) == NULL);
    EXPECT_TRUE(buildThreads(dataFromFile->array, 1, NULL, 1) == NULL);

    bestVector = buildOneThread(dataFromFile->array, dataFromFile->size, initialVect);
    EXPECT_EQ(bestVector->coords[0], 3.0);
    EXPECT_EQ(bestVector->coords[1], 2.0);
    EXPECT_EQ(bestVector->coords[2], 3.0);
    deleteVector(bestVector);
    EXPECT_TRUE(buildOneThread(NULL, 1, initialVect) == NULL);
    EXPECT_TRUE(buildOneThread(dataFromFile->array, 1, NULL) == NULL);

    deleteArrayOfVectors(dataFromFile->array, dataFromFile->size);
    free(dataFromFile);
    deleteVector(initialVect);
}


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




TEST(Structures, separateByThreads) {
    // separateByThreads(vector* arrayOfVectors, int vectorsQuan, int threadsQuan)
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

}

TEST(Calculating, calculateCosineDist) {

    dataVectors* dataFromFile = getTestVectors();
    int dimension = dataFromFile->dimension;
    vector* initialVect = getTestInitVect(dimension);
    vector* vect = dataFromFile->array;

    double dist;

    dist = calculateCosineDist(vect, initialVect, dimension);
    EXPECT_TRUE(abs(dist - 0.92582009) < EPS);

    dist = calculateCosineDist(vect + 1, initialVect, dimension);
    EXPECT_TRUE(abs(dist - 0.98019605) < EPS);

    dist = calculateCosineDist(vect + 2, initialVect, dimension);
    EXPECT_TRUE(abs(dist - 0.98473192) < EPS);
    
}

TEST(Grouping, scanVector) {
    char nameRead[30] = "tests/data/vectors.txt";
    dataVectors* dataFromFile = scanArrayOfVectors(nameRead);
    EXPECT_EQ(dataFromFile->size, 10);
    EXPECT_EQ(dataFromFile->dimension, 3);
    EXPECT_EQ((dataFromFile->array->coords)[0], 1.0);
    EXPECT_EQ((dataFromFile->array->coords)[1], 2.0);
    EXPECT_EQ((dataFromFile->array->coords)[2], 3.0);
}

TEST(Calculating, getMinVector) {
    dataVectors* dataFromFile = getTestVectors();
    vector* initialVect = getTestInitVect(dataFromFile->dimension);
    
    vector* bestVector = getMinVector(dataFromFile, initialVect);

    EXPECT_EQ(bestVector->coords[0], 3.0);
    EXPECT_EQ(bestVector->coords[1], 2.0);
    EXPECT_EQ(bestVector->coords[2], 3.0);

}

TEST(Calculating, testParallel) {
    dataVectors* dataFromFile = getTestVectors();
    vector* initialVect = getTestInitVect(dataFromFile->dimension);
    
    vector* bestVector;

    bestVector = buildThreads(dataFromFile->array, dataFromFile->size, initialVect, 4);
    EXPECT_EQ(bestVector->coords[0], 3.0);
    EXPECT_EQ(bestVector->coords[1], 2.0);
    EXPECT_EQ(bestVector->coords[2], 3.0);

    bestVector = buildOneThread(dataFromFile->array, dataFromFile->size, initialVect);
    EXPECT_EQ(bestVector->coords[0], 3.0);
    EXPECT_EQ(bestVector->coords[1], 2.0);
    EXPECT_EQ(bestVector->coords[2], 3.0);

}

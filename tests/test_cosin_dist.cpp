#include <gtest/gtest.h>
#include <cmath>

extern "C" {
    #include "structures.h"
    #include "calculating.h"
}

#define EPS 0.00001


void setCoordsToVect(vector* v1, int dim) {
    for (int i = 0; i < dim; ++i) {
        v1->coords[i] = i;
    }
}

TEST(TestGrouping, insertToUserList) {
    int dim = 5;
    vector* vect = createVector(dim);
    setCoordsToVect(vect, dim);
    EXPECT_EQ(vect->coords[0], 0);
    EXPECT_EQ(vect->coords[1], 1);
    EXPECT_EQ(vect->coords[2], 2);
    EXPECT_EQ(vect->coords[3], 3);
}


TEST(TestStructures, separateByThreads) {
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

TEST(TestCalculating, calculateCosineDist) {

    int dim = 3;
    vector* vect = createVector(dim);
    vector* initVect = createVector(dim);
    vect->coords[0] = 1.0;
    vect->coords[1] = 1.0;
    vect->coords[2] = 1.0;
    initVect->coords[0] = 1.0;
    initVect->coords[1] = 1.0;
    initVect->coords[2] = 1.0;
    double dist = calculateCosineDist(vect, initVect, dim);
    ASSERT_TRUE(abs(dist - 1.0) < EPS);

    vect->coords[0] = 1.5;
    vect->coords[1] = 1.3;
    vect->coords[2] = 0.0;
    initVect->coords[0] = 0;
    initVect->coords[1] = 0;
    initVect->coords[2] = 15.0;
    dist = calculateCosineDist(vect, initVect, dim);
    ASSERT_TRUE(abs(dist) < EPS);

    vect->coords[0] = 1.0;
    vect->coords[1] = 1.5;
    vect->coords[2] = 2.1;
    initVect->coords[0] = 2.1;
    initVect->coords[1] = 3.3;
    initVect->coords[2] = 1.0;
    dist = calculateCosineDist(vect, initVect, dim);
    ASSERT_TRUE(abs(dist - 0.818866) < EPS);
}

TEST(TestGrouping, scanVector) {
    char nameRead[30] = "tests/data/test_data.txt";
    dataVectors* dataFromFile = scanArrayOfVectors(nameRead);
    EXPECT_EQ(dataFromFile->size, 1);
    EXPECT_EQ(dataFromFile->dimension, 3);
    EXPECT_EQ((dataFromFile->array->coords)[0], 1.0);
    EXPECT_EQ((dataFromFile->array->coords)[1], 2.0);
    EXPECT_EQ((dataFromFile->array->coords)[2], 3.0);
    char nameWrite[30] = "tests/data/wrote_data.txt";
    writeArrayOfVectors(dataFromFile, nameWrite);
    // showVector(*(dataFromFile->array), dataFromFile->dimension);
}

TEST(TestCalculating, getMinVector) {
    char nameRead[30] = "tests/data/vectors.txt";
    dataVectors* dataFromFile = scanArrayOfVectors(nameRead);
    vector* initialVect = (vector*)malloc(sizeof(vector));
    FILE* file = fopen("tests/data/initVect.txt", "r");
    scanVector(file, initialVect, dataFromFile->dimension);
    fclose(file);
    
    vector* bestVector = getMinVector(dataFromFile, initialVect);


    EXPECT_EQ(bestVector->coords[0], 3.0);
    EXPECT_EQ(bestVector->coords[1], 2.0);
    EXPECT_EQ(bestVector->coords[2], 3.0);

}
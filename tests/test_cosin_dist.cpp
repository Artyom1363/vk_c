#include <gtest/gtest.h>


extern "C" {
    #include "structures.h"
}


void setCoordsToVect(vector v1, int dim) {
    for (int i = 0; i < dim; ++i) {
        v1.coords[i] = i;
    }
}

TEST(TestGrouping, insertToUserList) {
    int dim = 5;
    vector vect = createVector(dim);
    setCoordsToVect(vect, dim);
    EXPECT_EQ(vect.coords[0], 0);
    EXPECT_EQ(vect.coords[1], 1);
    EXPECT_EQ(vect.coords[2], 2);
    EXPECT_EQ(vect.coords[3], 3);
}


TEST(TestGrouping, groupByCode) {
    
}
#include <gtest/gtest.h>

extern "C" {
    #include "groupByCode.h"
}


TEST(Func, TestBasics) {
    struct user* checkValue = NULL;
    struct user* start = NULL;
    checkValue = groupByCode(start);
    EXPECT_EQ(1, checkValue -> netCode);
    EXPECT_EQ(1111111, checkValue -> number);
    EXPECT_EQ(1111110, checkValue -> number);
}

TEST(Func, Test10) {
    EXPECT_EQ(1234, 1234);
}

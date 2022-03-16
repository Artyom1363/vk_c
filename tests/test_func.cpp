#include <gtest/gtest.h>

extern "C" {
    #include "func.h"
}

TEST(Func, TestBasics) {
    EXPECT_EQ(1234, inputInt(123));
    EXPECT_EQ(123, inputInt(123));
}

TEST(Func, Test10) {
    EXPECT_EQ(1234, inputInt(123));
}

#include <gtest/gtest.h>

extern "C" {
    #include "groupByCode.h"
}

struct user* fillTestList() {
    struct user* user1 = (struct user*)malloc(sizeof(struct user));
    struct user* user2 = (struct user*)malloc(sizeof(struct user));
    struct user* user3 = (struct user*)malloc(sizeof(struct user));
    struct user* user4 = (struct user*)malloc(sizeof(struct user));

    user1 -> netCode = 123;
    user1 -> number = 1000001;
    user1 -> next = user2;

    user2 -> netCode = 111;
    user2 -> number = 1000002;
    user2 -> next = user3;

    user3 -> netCode = 222;
    user3 -> number = 1000003;
    user3 -> next = user4;

    user4 -> netCode = 123;
    user4 -> number = 1000004;
    user4 -> next = NULL;

    return user1;
}

TEST(TestGrouping, checkInAlreadyUsed) {
}

TEST(TestGrouping, insertToUserList) {
    struct user* startValue = fillTestList();
    struct user* expectedData = startValue -> next;
    struct user* dataToInsert = (startValue -> next) -> next;
    struct user* insertedData = insertToUserList(startValue, dataToInsert);
    EXPECT_EQ(1000001, startValue -> number);
    EXPECT_EQ(insertedData, startValue -> next);
    EXPECT_EQ(insertedData -> next, expectedData);
    EXPECT_EQ(startValue -> number, (insertToUserList(NULL, startValue) -> number));
}


TEST(TestGrouping, groupByCode) {
    
    struct user* start = fillTestList();
    struct user* checkValue = groupByCode(start);

    EXPECT_EQ(123, checkValue -> netCode);
    EXPECT_EQ(1000001, checkValue -> number);
    // showUsers(checkValue);
}

TEST(Func, Test10) {
    EXPECT_EQ(1234, 1234);
}

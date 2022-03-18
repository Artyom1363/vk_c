#include <gtest/gtest.h>


extern "C" {
    #include "groupByCode.h"
}

user* fillTestList() {
    user* user1 = (user*)malloc(sizeof(user));
    user* user2 = (user*)malloc(sizeof(user));
    user* user3 = (user*)malloc(sizeof(user));
    user* user4 = (user*)malloc(sizeof(user));

    user1->netCode = 123;
    user1->number = 1000001;
    user1->bufLen = (strlen("bob") + 1);
    user1->name = (char*)malloc((user1->bufLen) * sizeof(char));
    strcpy(user1->name, "bob");
    user1->next = user2;

    user2->netCode = 111;
    user2->number = 1000002;
    user2->bufLen = (strlen("rax") + 1);
    user2->name = (char*)malloc((user2->bufLen) * sizeof(char));
    strcpy(user2->name, "rax");
    user2->next = user3;

    user3->netCode = 222;
    user3->number = 1000003;
    user3->bufLen = (strlen("vasya") + 1);
    user3->name = (char*)malloc((user3->bufLen) * sizeof(char));
    strcpy(user3->name, "vasya");
    user3->next = user4;

    user4->netCode = 123;
    user4->number = 1000004;
    user4->bufLen = (strlen("pety") + 1);
    user4->name = (char*)malloc((user4->bufLen) * sizeof(char));
    strcpy(user4->name, "pety");
    user4->next = NULL;

    return user1;
}

TEST(TestGrouping, insertToUserList) {
    user* startValue = fillTestList();
    user* expectedData = startValue->next;
    user* dataToInsert = (startValue->next)->next;
    user* insertedData = insertToUserList(startValue, dataToInsert);
    EXPECT_EQ(1000001, startValue->number);
    EXPECT_EQ(insertedData, startValue->next);
    EXPECT_EQ(insertedData->next, expectedData);
    EXPECT_EQ(startValue->number, (insertToUserList(NULL, startValue)->number));
}


TEST(TestGrouping, groupByCode) {
    
    user* start = fillTestList();
    user* check1 = groupByCode(start);

    user* check2 = check1->next;
    user* check3 = check2->next;
    user* check4 = check3->next;

    EXPECT_EQ(123, check1->netCode);
    EXPECT_EQ(1000001, check1->number);

    EXPECT_EQ(123, check2->netCode);
    EXPECT_EQ(1000004, check2->number);

    EXPECT_EQ(111, check3->netCode);
    EXPECT_EQ(1000002, check3->number);

    EXPECT_EQ(222, check4->netCode);
    EXPECT_EQ(1000003, check4->number);

}

TEST(Func, testCi) {
    EXPECT_EQ(1234, 1234);
}

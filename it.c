#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user_lib/groupByCode.h"
#include "user_lib/user.h"
// #include <gtest/gtest.h>


user* fillTestList() {
    user* user1 = (user*)malloc(sizeof(user));
    user* user2 = (user*)malloc(sizeof(user));
    user* user3 = ( user*)malloc(sizeof(user));
    user* user4 = ( user*)malloc(sizeof(user));
    user* user5 = ( user*)malloc(sizeof(user));
    user* user6 = ( user*)malloc(sizeof(user));

    user1->netCode = 123;
    user1->number = 1000001;
    strcpy(user1->name, "bob");
    user1->next = user2;

    user2->netCode = 111;
    user2->number = 1000002;
    strcpy(user2->name, "alice");
    user2->next = user3;

    user3->netCode = 222;
    user3->number = 1000003;
    strcpy(user3->name, "vasya");
    user3->next = user4;

    user4->netCode = 123;
    user4->number = 1000004;
    strcpy(user4->name, "pety");
    user4->next = user5;

    user5->netCode = 123;
    user5->number = 1000005;
    strcpy(user5->name, "timofey");
    user5->next = user6;

    user6->netCode = 222;
    user6->number = 1000006;
    strcpy(user6->name, "valentin");
    user6->next = NULL;

    return user1;
}

int main() {
    user* first = fillTestList();
    user* second = groupByCode(first);
    printf("THIS IS FIRST LIST:\n");
    showUsers(first);
    printf("\n\n\n\nTHIS IS GROUPED LIST:\n");
    showUsers(second);
    cleanUsersList(first);
    cleanUsersList(second);
    return 0;
}


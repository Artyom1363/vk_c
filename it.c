#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user_lib/groupByCode.h"
#include "user_lib/user.h"
// #include <gtest/gtest.h>


struct user* fillTestList() {
    struct user* user1 = (struct user*)malloc(sizeof(struct user));
    struct user* user2 = (struct user*)malloc(sizeof(struct user));
    struct user* user3 = (struct user*)malloc(sizeof(struct user));
    struct user* user4 = (struct user*)malloc(sizeof(struct user));
    struct user* user5 = (struct user*)malloc(sizeof(struct user));
    struct user* user6 = (struct user*)malloc(sizeof(struct user));

    user1 -> netCode = 123;
    user1 -> number = 1000001;
    strcpy(user1 -> name, "bob");
    user1 -> next = user2;

    user2 -> netCode = 111;
    user2 -> number = 1000002;
    strcpy(user2 -> name, "alice");
    user2 -> next = user3;

    user3 -> netCode = 222;
    user3 -> number = 1000003;
    strcpy(user3 -> name, "vasya");
    user3 -> next = user4;

    user4 -> netCode = 123;
    user4 -> number = 1000004;
    strcpy(user4 -> name, "pety");
    user4 -> next = user5;

    user5 -> netCode = 123;
    user5 -> number = 1000005;
    strcpy(user5 -> name, "timofey");
    user5 -> next = user6;

    user6 -> netCode = 222;
    user6 -> number = 1000006;
    strcpy(user6 -> name, "valentin");
    user6 -> next = NULL;

    return user1;
}

int main() {
    struct user* first = fillTestList();
    struct user* second = groupByCode(first);
    printf("THIS IS FIRST LIST:\n");
    showUsers(first);
    printf("\n\n\n\nTHIS IS GROUPED LIST:\n");
    showUsers(second);
    cleanUsersList(first);
    cleanUsersList(second);
    return 0;
}


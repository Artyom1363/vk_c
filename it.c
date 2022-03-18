#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "user_lib/groupByCode.h"
#include "user_lib/user.h"


user* fillTestList() {
    user* user1 = malloc(sizeof(user));
    user* user2 = malloc(sizeof(user));
    user* user3 = malloc(sizeof(user));
    user* user4 = malloc(sizeof(user));
    user* user5 = malloc(sizeof(user));
    user* user6 = malloc(sizeof(user));

    user1->netCode = 123;
    user1->number = 1000001;
    user1->bufLen = (strlen("bob") + 1);
    user1->name = malloc((user1->bufLen) * sizeof(char));
    strcpy(user1->name, "bob");
    user1->next = user2;

    user2->netCode = 111;
    user2->number = 1000002;
    user2->bufLen = (strlen("rax") + 1);
    user2->name = malloc((user2->bufLen) * sizeof(char));
    strcpy(user2->name, "rax");
    user2->next = user3;

    user3->netCode = 222;
    user3->number = 1000003;
    user3->bufLen = (strlen("vasya") + 1);
    user3->name = malloc((user3->bufLen) * sizeof(char));
    strcpy(user3->name, "vasya");
    user3->next = user4;

    user4->netCode = 123;
    user4->number = 1000004;
    user4->bufLen = (strlen("pety") + 1);
    user4->name = malloc((user4->bufLen) * sizeof(char));
    strcpy(user4->name, "pety");
    user4->next = user5;

    user5->netCode = 123;
    user5->number = 1000005;
    user5->bufLen = (strlen("timofey") + 1);
    user5->name = malloc((user5->bufLen) * sizeof(char));
    strcpy(user5->name, "timofey");
    user5->next = user6;

    user6->netCode = 222;
    user6->number = 1000006;
    user6->bufLen = (strlen("valentin") + 1);
    user6->name = malloc((user6->bufLen) * sizeof(char));
    strcpy(user6->name, "valentin");
    user6->next = NULL;

    return user1;
}

int main() {
    user* data = fillTestList();
    
    user* groupedData = groupByCode(data);
    
    printf("THIS IS FIRST LIST:\n");
    showUsers(data);
    printf("\n\n\n\nTHIS IS GROUPED LIST:\n");
    showUsers(groupedData);
    cleanUsersList(data);
    cleanUsersList(groupedData);
    return 0;
}


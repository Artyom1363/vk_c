#include <stdlib.h>
#include <stdio.h>

#include "user.h"


void showUser(user *val) {
    if (val == NULL) {
        return;
    }
    printf("Network code: %d\n", val->netCode);
    printf("Phone number: %d\n", val->number);
    printf("Username: %s\n", val->name);
}

void showUsers(user *start) {
    printf("SHOWING USERS:\n");
    while (start != NULL) {
        showUser(start);
        start = start->next;
    }
    return;
}

void cleanUsersList(user *start) {
    while (start != NULL) {
        user* tmp = start;
        start = start->next;
        free(tmp->name);
        free(tmp);
    }
}
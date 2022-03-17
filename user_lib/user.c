#include <stdlib.h>
#include "user.h"


void showUser(struct user *val) {
    printf("Network code: %d\n", val -> netCode);
    printf("Phone number: %d\n", val -> number);
    printf("Username: %s\n", val -> name);
}

void showUsers(struct user *start) {
    while (start != NULL) {
        showUser(start);
        start = start -> next;
    }
    return;
}

void cleanUsersList(struct user *start) {
    while (start != NULL) {
        struct user* tmp = start;
        start = start -> next;
        free(tmp);
    }
}
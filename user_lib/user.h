#ifndef USER_H
#define USER_H

typedef struct user {
    int netCode;
    int number;
    char name[20];
    struct user *next;
} user;

void cleanUsersList(user *start);
void showUser(user *val);
void showUsers(user *start);


#endif

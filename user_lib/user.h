#ifndef USER_H
#define USER_H

typedef struct user {
    int netCode;
    int number;
    int bufLen;
    char* name;
    struct user *next;
} user;

void cleanUsersList(user *start);
void showUser(user *val);
void showUsers(user *start);


#endif

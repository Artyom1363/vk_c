#ifndef USER_H
#define USER_H

struct user {
    int netCode;
    int number;
    char *name;
    struct user *next;
};

void cleanUsersList(struct user *start);
void showUser(struct user *val);
void showUsers(struct user *start);


#endif

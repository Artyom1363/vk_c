#include <stdio.h>
#include <stdlib.h>
#include "user.h"
#include "groupByCode.h"


struct user* checkInAlreadyUsed(int code, struct netCodeNode* uniqueValues) {
    while (uniqueValues != NULL) {
        if (uniqueValues -> netCode == code) {
            return uniqueValues -> latestWithThisCode;
        }
        uniqueValues = uniqueValues -> next;
    }
    return NULL;
}

struct user* createCopyUser(struct user* from) {
    if (from == NULL) {
        return NULL;
    }
    struct user* newUser = (struct user*)malloc(sizeof(struct user));
    newUser -> netCode = from -> netCode;
    newUser -> number = from -> number;

    // TODO UPDATE THIS TO DINAMIC DATA
    newUser -> name = from -> name;

    // made to satisfy function name
    newUser -> next = from -> next;
    return newUser;
}


/*
* create new user and insert him after first argument
* if first argument is NULL insert instead of NULL
*/
struct user* insertToUserList(struct user* insertAfter, struct user* dataToInsert) {
    /*if (insertAfter == NULL) {
        printf("ERROR: could not create a UserNode after NULL ptr\n");
        exit(0);
    }*/
    if (dataToInsert == NULL) {
        printf("ERROR: could not copy NULL user\n");
        exit(0);
    }

    struct user* newUser = createCopyUser(dataToInsert);
    if (insertAfter == NULL) {
        return newUser;
    }

    newUser -> next = insertAfter -> next;
    insertAfter -> next = newUser;
    return newUser;
}

struct user* groupByCode(struct user *start) {
    struct user* userPtr = start;
    struct user* groupedStart = NULL;
    struct user* groupedLast = NULL;
    struct netCodeNode* uniqueValues = NULL; // (struct user*)malloc(sizeof(struct user));
    while (userPtr != NULL) {
        struct user* ptrToInsertNewUser = checkInAlreadyUsed(userPtr -> netCode, uniqueValues);
        struct user* insertedUser = insertToUserList(ptrToInsertNewUser, userPtr);
        if (ptrToInsertNewUser == NULL) {
            struct netCodeNode* tmp = (struct netCodeNode*)malloc(sizeof(struct netCodeNode));
            tmp -> netCode = userPtr -> netCode;
            tmp -> next = uniqueValues;
            tmp -> latestWithThisCode = insertedUser;

            uniqueValues = tmp;
            groupedLast -> next = insertedUser;
            groupedLast = groupedLast -> next;
        }
        if (groupedStart == NULL) {
            groupedStart = insertedUser;
        }
        userPtr = userPtr -> next;
    }
    return groupedStart;
}
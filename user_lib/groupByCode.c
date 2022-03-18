#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"
#include "groupByCode.h"


user* checkInAlreadyUsed(int code, netCodeNode* uniqueValues) {
    while (uniqueValues != NULL) {
        if (uniqueValues->netCode == code) {
            return uniqueValues->latestWithThisCode;
        }
        uniqueValues = uniqueValues->next;
    }
    return NULL;
}

user* createCopyUser(user* from) {
    if (from == NULL) {
        return NULL;
    }
    user* newUser = malloc(sizeof(user));
    newUser->netCode = from->netCode;
    newUser->number = from->number;
    newUser->bufLen = from->bufLen;

    newUser->name = malloc((newUser->bufLen) * sizeof(char));
    memcpy(newUser->name, from->name, newUser->bufLen);

    // made to satisfy function name
    newUser->next = from->next;
    return newUser;
}


/*
* create new user and insert him after first argument
* if first argument is NULL insert instead of NULL
*/
user* insertToUserList(user* insertAfter, user* dataToInsert) {
    /*if (insertAfter == NULL) {
        printf("ERROR: could not create a UserNode after NULL ptr\n");
        exit(0);
    }*/
    if (dataToInsert == NULL) {
        printf("ERROR: could not copy NULL user\n");
        exit(0);
    }

    user* newUser = createCopyUser(dataToInsert);
    if (insertAfter == NULL) {
        newUser->next = NULL;
        return newUser;
    }

    newUser->next = insertAfter->next;
    insertAfter->next = newUser;
    return newUser;
}

void cleanNetCodeList(netCodeNode* first) {
    while (first != NULL) {
        netCodeNode* tmp = first;
        first = first->next;
        free(tmp);
    }
}

user* groupByCode(user *start) {
    user* userPtr = start;
    user* groupedStart = NULL;
    user* groupedLast = NULL;
    netCodeNode* uniqueValues = NULL;
    while (userPtr != NULL) {
        user* ptrToInsertNewUser = checkInAlreadyUsed(userPtr->netCode, uniqueValues);
        user* insertedUser = insertToUserList(ptrToInsertNewUser, userPtr);
        if (ptrToInsertNewUser == NULL) {
            netCodeNode* tmp = malloc(sizeof(netCodeNode));
            tmp->netCode = userPtr->netCode;
            tmp->next = uniqueValues;
            tmp->latestWithThisCode = insertedUser;

            uniqueValues = tmp;
            if (groupedLast == NULL) {
                groupedLast = insertedUser;
            } else {
                groupedLast->next = insertedUser;
                groupedLast = groupedLast->next;
            }
        }
        if (groupedStart == NULL) {
            groupedStart = insertedUser;
        }
        userPtr = userPtr->next;
    }
    cleanNetCodeList(uniqueValues);
    return groupedStart;
}
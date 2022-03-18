#ifndef GROUPBYCODE_H
#define GROUPBYCODE_H

#include "user.h"

struct netCodeNode {
    int netCode;
    struct netCodeNode* next;
    struct user* latestWithThisCode;
};
struct user* checkInAlreadyUsed(int code, struct netCodeNode* uniqueValues);

struct user* createCopyUser(struct user* from);

struct user* insertToUserList(struct user* insertAfter, struct user* dataToInsert);

void cleanNetCodeList(struct netCodeNode* first);

struct user* groupByCode(struct user *start);

#endif
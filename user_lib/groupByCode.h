#ifndef GROUPBYCODE_H
#define GROUPBYCODE_H

#include "user.h"

typedef struct netCodeNode {
    int netCode;
    struct netCodeNode* next;
    user* latestWithThisCode;
} netCodeNode;

user* checkInAlreadyUsed(int code, netCodeNode* uniqueValues);

user* createCopyUser(user* from);

user* insertToUserList(user* insertAfter, user* dataToInsert);

void cleanNetCodeList(netCodeNode* first);

user* groupByCode(user* start);

#endif
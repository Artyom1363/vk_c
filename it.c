#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user_lib/groupByCode.h"
#include "user_lib/user.h"
// #include <gtest/gtest.h>


struct user* fillTestList() {
    struct user* user1 = (struct user*)malloc(sizeof(struct user));
    struct user* user2 = (struct user*)malloc(sizeof(struct user));
    struct user* user3 = (struct user*)malloc(sizeof(struct user));
    struct user* user4 = (struct user*)malloc(sizeof(struct user));

    user1 -> netCode = 123;
    user1 -> number = 1000001;
    user1 -> next = user2;

    user2 -> netCode = 111;
    user2 -> number = 1000002;
    user2 -> next = user3;

    user3 -> netCode = 222;
    user3 -> number = 1000003;
    user3 -> next = user4;

    user4 -> netCode = 123;
    user4 -> number = 1000004;
    user4 -> next = NULL;

    return user1;
}

char input_char() {
    char c = '\0';
    int result = 0;
    do {
        result = scanf("%c", &c);
    } while (result != 1);
    return c;
}

char *input_string() {
    struct buffer {
        char *string;
        size_t size;
        size_t capacity;
    } buf = {NULL, 0, 0};
    char c = '\0';
    while (c = input_char(), c != EOF && c != '\n') {
        if (buf.size + 1 >= buf.capacity) {
            size_t new_capacity = !buf.capacity ? 1 : buf.capacity * 2;
            char *tmp = (char *)malloc((new_capacity + 1) * sizeof(char));
            if (!tmp) {
                if (buf.string) {
                    free(buf.string);
                }
                return NULL;
            }
            if (buf.string) {
                tmp = strcpy(tmp, buf.string);
                free(buf.string);
            }
            buf.string = tmp;
            buf.capacity = new_capacity;
        }
        buf.string[buf.size] = c;
        buf.string[buf.size + 1] = '\0';
        ++buf.size;
    }
    return buf.string;
}

int input_int() {
    char c = '\0';
    int result = 0;
    while (c = input_char(), c != EOF && c != '\n') {
        if (!(c >= '0' && c <= '9')) {
            char *buf = input_string(); /* Read to the end of the string */
            if (buf) {
                free(buf);
            }
            return 0;
        }
        result = result * 10 + c - '0';
    }
    return result;
}

int getPhoneNumber() {
    int value = input_int();
    while (!(value <= 9999999 && value >= 1000000)) {
        printf("Your data is incorrect, please try again:\n");
        value = input_int();
    }
    return value;
}

struct user *getUserData() {
    struct user *data = (struct user *)malloc(sizeof(struct user));
    data -> next = NULL;
    printf("Enter your network code:\n");
    int getNetCode = 0;
    getNetCode = input_int();
    data -> netCode = getNetCode;
    printf("Enter your phone number code (7 signs, without leading zeros):\n");
    int phoneNumber = getPhoneNumber();
    data -> number = phoneNumber;
    printf("Enter your name:\n");
    char *getName = input_string();
    data -> name = getName;
    return data;
}


void printMenu() {
    printf("Press:\n");
    printf("1 to enter new user data\n");
    printf("2 to show users data\n");
}


void startProgramm(struct user* first) {
    struct user *latest = NULL;
    while (1) {
        printMenu();
        char type = input_char();
        if (type == '1') {
            if (first == NULL) {
                first = getUserData();
                latest = first;
            } else {
                latest -> next = getUserData();
                latest = latest -> next;
            }
        } else if (type == '2') {
            showUsers(first);
        }
    }
}


int main() {
    struct user* first = fillTestList();
    printf("test print\n");
    struct user* second = groupByCode(first);
    // startProgramm(first);
    return 0;
}


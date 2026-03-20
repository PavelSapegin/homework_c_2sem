#pragma once
#include <stdio.h>

typedef struct ListNode {
    char* code;
    char* name;
    struct ListNode* next;
} ListNode;

typedef struct List {
    ListNode* head;
} List;

List* createList(void);
List* add(List* list, char str[]);
List* delete(List* list, char code[]);
ListNode* find(List* list, char code[]);
void freeList(List* list);
List* load(char filepath[]);
void saveListNode(ListNode* node, FILE* fp);
void save(List* list, char filepath[]);

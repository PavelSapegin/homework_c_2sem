#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

List* createList(void)
{
    List* list = malloc(sizeof(List));
    if (list)
        list->head = NULL;

    return list;
}

List* add(List* list, char str[])
{
    char code[10];
    char name[900];
    if (sscanf(str, "%[^:]:%[^\n]", code, name) != 2)
        return list;

    if ((strlen(name) == 0) || (strlen(code) == 0))
        return list;

    ListNode* newNode = malloc(sizeof(ListNode));
    if (newNode == NULL)
        return list;

    size_t codeSize = strlen(code) + 1;
    size_t nameSize = strlen(name) + 1;
    newNode->code = malloc(codeSize);
    newNode->name = malloc(nameSize);
    newNode->next = NULL;
    if ((newNode->code == NULL) || (newNode->name == NULL)) {
        if (newNode->code)
            free(newNode->code);
        if (newNode->name)
            free(newNode->name);
        free(newNode);
        return list;
    }
    strlcpy(newNode->code, code, codeSize);
    strlcpy(newNode->name, name, nameSize);

    ListNode* curr = list->head;
    list->head = newNode;
    newNode->next = curr;

    return list;
}

List* delete(List* list, char code[])
{
    if ((list == NULL) || (list->head == NULL))
        return list;
    ListNode* curr = list->head;
    ListNode* prev = NULL;
    while (curr && (strcmp(curr->code, code) != 0)) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL)
        return list;

    if (prev == NULL) {
        list->head = curr->next;
    } else {
        prev->next = curr->next;
    }

    free(curr->code);
    free(curr->name);
    free(curr);

    return list;
}

ListNode* find(List* list, char code[])
{
    ListNode* curr = list->head;
    while (curr && (strcmp(curr->code, code) != 0)) {
        curr = curr->next;
    }

    return curr;
}

void freeList(List* list)
{
    ListNode* curr = list->head;
    while (curr != NULL) {
        ListNode* temp = curr->next;
        free(curr->name);
        free(curr->code);
        free(curr);
        curr = temp;
    }

    free(list);
}

List* load(char filepath[])
{
    FILE* fp = fopen(filepath, "r");
    if (fp == NULL)
        return NULL;

    List* list = createList();

    char buff[1024];
    while (fgets(buff, sizeof(buff), fp)) {
        if (strlen(buff) > 1)
            add(list, buff);
    }
    fclose(fp);

    return list;
}

void saveListNode(ListNode* node, FILE* fp)
{
    if (node == NULL)
        return;
    fprintf(fp, "%s:%s\n", node->code, node->name);
}

void save(List* list, char filepath[])
{
    FILE* fp = fopen(filepath, "w");
    if (fp == NULL) {
        return;
    }
    ListNode* curr = list->head;
    while (curr) {
        saveListNode(curr, fp);
        curr = curr->next;
    }
    fclose(fp);
}

#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AVL* load(char filepath[])
{
    FILE* fp = fopen(filepath, "r");
    if (fp == NULL)
        return NULL;

    AVL* tree = malloc(sizeof(AVL));
    if (tree == NULL)
        return NULL;
    tree->root = NULL;

    char buff[1024];
    while (fgets(buff, sizeof(buff), fp)) {
        if (strlen(buff) > 1)
            add(tree, buff);
    }
    fclose(fp);

    return tree;
}

char* find(AVL* tree, char code[])
{
    Node* result = avlFindNode(tree, code);
    if (result == NULL) {
        return NULL;
    }
    return result->name;
}

AVL* add(AVL* tree, char str[])
{
    char iata[10];
    char name[900];
    if (sscanf(str, "%[^:]:%[^\n]", iata, name) != 2)
        return tree;
    
    if ((strlen(name) == 0) || (strlen(iata) == 0))
        return tree;

    tree = avlInsert(tree, iata, name);
    return tree;
}

AVL* delete(AVL* tree, char code[])
{
    tree = avlDeleteNode(tree, code);
    return tree;
}

void saveNode(Node* node, FILE* fp)
{
    if (node == NULL) {
        return;
    }

    saveNode(node->left, fp);
    saveNode(node->right, fp);
    fprintf(fp, "%s:%s\n", node->code, node->name);
}

void save(AVL* tree, char filepath[])
{
    FILE* fp = fopen(filepath, "w");
    if (fp == NULL) {
        return;
    }

    saveNode(tree->root, fp);
    fclose(fp);
}

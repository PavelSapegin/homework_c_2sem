#include "avl.h"
#include <stdio.h>
#include <stdlib.h>

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
        add(tree, buff);
    }
    fclose(fp);

    return tree;
}

char* find(AVL* tree, char code[])
{
    Node* result = avlFindNode(tree, code);
    if (result == NULL) {
        return "Airport don't found.\n";
    }
    return result->name;
}

AVL* add(AVL* tree, char str[])
{
    char iata[10];
    char name[900];
    sscanf(str, "%[^:]:%[^\n]", iata, name);
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

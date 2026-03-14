#pragma once
#include <stdio.h>
typedef struct Node {
    char* code;
    char* name;
    int height;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct AVLtree {
    Node* root;
} AVL;

Node* createNode(char code[], char name[]);
int getHeight(Node* node);
void updateHeight(Node* node);
Node* rotateLeft(Node* node);
Node* rotateRight(Node* node);
Node* balance(Node* node);
Node* insertNode(Node* node, char code[], char name[]);
AVL* avlInsert(AVL* tree,char code[], char name[]);
Node *avlFindNode(AVL *tree, char code[]);
AVL* avlDeleteNode(AVL *tree, char code[]);
Node *findNode(Node *node, char code[]);
void freeNode(Node *node);
AVL* add(AVL* tree, char str[]);
void freeAVL(AVL *tree);
AVL* load(char filepath[]);
char *find(AVL* tree, char code[]);
AVL* delete(AVL *tree, char code[]);
void saveNode(Node *node, FILE* fp);
void save(AVL* tree, char filepath[]);

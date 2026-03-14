#include "avl.h"
#include <stdlib.h>
#include <string.h>

Node* createNode(char code[], char name[])
{
    Node* newNode = malloc(sizeof(Node));

    if (newNode == NULL)
        return NULL;

    newNode->code = malloc(strlen(code) + 1);
    newNode->name = malloc(strlen(name) + 1);
    if (newNode->code == NULL) {
        free(newNode);
        return NULL;
    }
    if (newNode->name == NULL) {
        free(newNode);
        return NULL;
    }

    strlcpy(newNode->code, code,sizeof(newNode->code));
    strlcpy(newNode->name, name,sizeof(newNode->name));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 0;

    return newNode;
}

int getHeight(Node* node)
{
    return node ? node->height : 0;
}

void updateHeight(Node* node)
{
    if (node) {
        int heightLeft = getHeight(node->left);
        int heightRight = getHeight(node->right);
        node->height = 1 + ((heightLeft > heightRight) ? heightLeft : heightRight);
    }
}

Node* rotateLeft(Node* node)
{
    Node* a = node;
    Node* b = a->right;
    a->right = b->left;
    b->left = a;

    updateHeight(a);
    updateHeight(b);

    return b;
}

Node* rotateRight(Node* node)
{
    Node* a = node;
    Node* b = a->left;
    a->left = b->right;
    b->right = a;

    updateHeight(a);
    updateHeight(b);

    return b;
}

Node* balance(Node* node)
{
    if (node == NULL)
        return node;

    int diff = getHeight(node->right) - getHeight(node->left);

    if ((diff > 1) && (node->right)) {
        int childDiff = getHeight(node->right->right) - getHeight(node->right->left);
        if (childDiff < 0)
            node->right = rotateRight(node->right);
        node = rotateLeft(node);

    }

    else if ((diff < -1) && (node->left)) {
        int childDiff = getHeight(node->left->right) - getHeight(node->left->left);
        if (childDiff > 0)
            node->left = rotateLeft(node->left);
        node = rotateRight(node);
    }

    return node;
}

Node* insertNode(Node* node, char code[], char name[])
{
    if (node == NULL) {
        return createNode(code, name);
    }

    else if (strcmp(node->code, code) < 0) {

        node->right = insertNode(node->right, code, name);
    }

    else {

        node->left = insertNode(node->left, code, name);
    }

    updateHeight(node);
    node = balance(node);
    return node;
}

Node* findMin(Node* node)
{
    if (node == NULL)
        return NULL;
    while (node->left != NULL) {
        node = node->left;
    }

    return node;
}

void freeNode(Node* node)
{
    if (node) {
        free(node->code);
        free(node->name);
    }

    free(node);
}

Node* deleteNode(Node* node, char code[])
{
    if (node == NULL)
        return NULL;

    int result = strcmp(node->code, code);
    if (result == 0) {
        if ((node->left == NULL) && (node->right != NULL)) {
            Node* result = node->right;
            freeNode(node);
            return result;
        } else if ((node->left != NULL) && (node->right) == NULL) {
            Node* result = node->left;
            freeNode(node);
            return result;
        } else if ((node->left == NULL) && (node->right == NULL)) {
            freeNode(node);
            return NULL;
        } else {
            Node* minRightNode = findMin(node->right);
            strlcpy(node->code, minRightNode->code,sizeof(node->code));
            strlcpy(node->name, minRightNode->name,sizeof(node->name));
            node->right = deleteNode(node->right, minRightNode->code);
            updateHeight(node);
            node = balance(node);
            return node;
        }
    } else if (result < 0) {
        node->right = deleteNode(node->right, code);
        updateHeight(node);
        node = balance(node);
        return node;
    } else {
        node->left = deleteNode(node->left, code);
        updateHeight(node);
        node = balance(node);
        return node;
    }
}

Node* findNode(Node* node, char code[])
{
    if (node == NULL) {
        return NULL;
    }

    int result = strcmp(node->code, code);
    if (result == 0) {
        return node;
    } else if (result < 0) {
        return findNode(node->right, code);
    } else {
        return findNode(node->left, code);
    }
}

AVL* avlInsert(AVL* tree, char code[], char name[])
{
    if (tree == NULL)
        return NULL;

    tree->root = insertNode(tree->root, code, name);
    return tree;
}

Node* avlFindNode(AVL* tree, char code[])
{
    return findNode(tree->root, code);
}

AVL* avlDeleteNode(AVL* tree, char code[])
{
    if (tree == NULL)
        return NULL;
    tree->root = deleteNode(tree->root, code);
    return tree;
}

void freeAllNodes(Node* node)
{
    if (node != NULL) {
        freeAllNodes(node->left);
        freeAllNodes(node->right);
    }
    freeNode(node);
}

void freeAVL(AVL* tree)
{
    if (tree != NULL) {
        freeAllNodes(tree->root);
    }
    free(tree);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* code;
    int height;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct AVLtree {
    Node* root;
} AVL;

Node* createNode(char* code)
{
    Node* newNode = malloc(sizeof(Node));

    if (newNode == NULL)
        return NULL;

    newNode->code = malloc(strlen(code) + 1);
    if (newNode->code == NULL) {
        free(newNode);
        return NULL;
    }
    strcpy(newNode->code, code);
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

Node* rotate_left(Node* node)
{
    Node* a = node;
    Node* b = a->right;
    a->right = b->left;
    b->left = a;

    updateHeight(a);
    updateHeight(b);

    return b;
}

Node* rotate_right(Node* node)
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
        int child_diff = getHeight(node->right->right) - getHeight(node->right->left);
        if (child_diff < 0)
            node->right = rotate_right(node->right);
        node = rotate_left(node);

    }

    else if ((diff < -1) && (node->left)) {
        int child_diff = getHeight(node->left->right) - getHeight(node->left->left);
        if (child_diff > 0)
            node->left = rotate_left(node->left);
        node = rotate_right(node);
    }

    return node;
}

Node* insertNode(Node* node, char* code)
{
    if (node == NULL) {
        return createNode(code);
    }

    else if (strcmp(node->code, code) <= 0) {

        node->right = insertNode(node->right, code);
    }

    else {

        node->left = insertNode(node->left, code);
    }

    updateHeight(node);
    node = balance(node);
    return node;
}

void avlInsert(AVL* tree, char* code)
{
    if (tree == NULL)
        return;

    tree->root = insertNode(tree->root, code);
}

int main(void)
{
    return 0;
}

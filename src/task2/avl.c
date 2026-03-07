#include "avl.h"
#include <stdio.h>

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

Node* findMin(Node *node)
{
    while (node->left != NULL)
    {
        node = node->left;
    }

    return node;
}

void freeNode(Node *node)
{
    if (node)
        free(node->code);
    free(node);
}

Node *deleteNode(Node *node, char code[])
{
    if (node == NULL)
        return NULL;

    int result = strcmp(node->code,code);
    if (result == 0)
    {
        if ((node->left == NULL) && (node->right != NULL))
        {
            Node *result = node->right;
            freeNode(node);
            return result;
        }
        else if ((node->left != NULL) && (node->right) == NULL)
        {
            Node *result = node->left;
            freeNode(node);
            return result;
        }
        else if ((node->left == NULL) && (node->right == NULL))
        {
            freeNode(node);
            return NULL;
        }
        else
        {
            Node *min_right_node = findMin(node->right);
            strcpy(node->code,min_right_node->code);
            node->right = deleteNode(node->right,min_right_node->code);
            updateHeight(node);
            node = balance(node);
            return node;
        }
    }
    else if (result < 0)
    {
        node->right = deleteNode(node->right,code);
        updateHeight(node);
        node = balance(node);
        return node;
    }
    else
    {
        node->left = deleteNode(node->left,code);
        updateHeight(node);
        node = balance(node);
        return node;
    }

}

void avlInsert(AVL* tree, char code[])
{
    if (tree == NULL)
        return;

    tree->root = insertNode(tree->root, code);
}

void avlDelete(AVL *tree, char code[])
{
    if (tree == NULL)
        return;
    
    tree->root = deleteNode(tree->root,code);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

AVL* load(char filepath[])
{
    FILE* fp = fopen(filepath,"r");
    if (fp == NULL)
        return NULL;

    AVL *tree = malloc(sizeof(AVL));
    if (tree == NULL)
        return NULL;
    tree->root = NULL;

    char buff[1024];
    while (fgets(buff,sizeof(buff),fp))
    {
        add(tree,buff);
        
    }
    fclose(fp);

    return tree;
}

char *find(AVL* tree, char code[])
{
    Node *result = avlFindNode(tree,code);
    if (result == NULL)
    {
        return "Airport don't found.\n";
    }
    return result->name;
}

AVL* add(AVL* tree, char str[])
{
    char iata[10];
    char name[900];
    sscanf(str,"%[^:]:%[^\n]",iata,name);
    tree = avlInsert(tree,iata,name);
    return tree;
}

AVL* delete(AVL *tree, char code[])
{
    tree = avlDeleteNode(tree,code);
    return tree;
}

void saveNode(Node *node, FILE* fp)
{
    if (node == NULL)
    {
        return;
    }

    saveNode(node->left,fp);
    saveNode(node->right,fp);
    fprintf(fp,"%s:%s\n",node->code,node->name);
}

void save(AVL* tree, char filepath[])
{
    FILE *fp = fopen(filepath,"w");
    if (fp == NULL)
    {
        return;
    }

    saveNode(tree->root,fp);
}

int main(int argc,char *argv[])
{
    if (argc < 2)
    {
        printf("Please, write a path to file\n");
        return -1;
    }

    AVL *tree = load(argv[1]);
    if (tree == NULL)
    {
        printf("Error of opening file\n");
        return -1;
    }
    printf("File was opened sucsessfull\n");

    while (1)
    {
        char buff[900];
        char command[10];
        char parametr[860];
        fgets(buff, sizeof(buff), stdin);
        sscanf(buff, "%s %[^\n]", command, parametr);
        if (!strcmp(command,"find"))
        {
            printf("%s\n",find(tree,parametr));
        }
        else if (!strcmp(command,"add"))
        {
            tree = add(tree,parametr);
            printf("Airport %s was added\n",parametr);
        }
        else if (!strcmp(command,"delete"))
        {
            tree = delete(tree,parametr);
            printf("Airport %s was deleted\n",parametr);
        }
        else if (!strcmp(command,"save"))
        {
            printf("Base was saved.\n");
            save(tree,argv[1]);
        }
        else if (!strcmp(command,"quit"))
        {
            printf("Goodbye!\n");
            freeAVL(tree);
            break;
        }
        else
        {
            printf("Unknown command\n");

        }
    }
    return 0;
}

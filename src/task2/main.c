#include "avl.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Please, write a path to file\n");
        return -1;
    }

    if (strcmp(argv[1],"--test") == 0)
    {
        runTests();
        return 0;
    }

    AVL* tree = load(argv[1]);
    if (tree == NULL) {
        printf("Error of opening file\n");
        return -1;
    }
    printf("File was opened successfull\n");

    while (1) {
        char buff[900];
        char command[10];
        char parametr[860];
        fgets(buff, sizeof(buff), stdin);
        sscanf(buff, "%s %[^\n]", command, parametr);
        if (!strcmp(command, "find")) {
            char *result = find(tree, parametr);
            if (result != NULL)
            {
                printf("%s\n", result);
            }
            else
            {
                printf("Airport with code %s didn't found",parametr);
            }
            
        } else if (!strcmp(command, "add")) {
            tree = add(tree, parametr);
            printf("Airport %s was added\n", parametr);
        } else if (!strcmp(command, "delete")) {
            tree = delete (tree, parametr);
            printf("Airport %s was deleted\n", parametr);
        } else if (!strcmp(command, "save")) {
            printf("Base was saved.\n");
            save(tree, argv[1]);
        } else if (!strcmp(command, "quit")) {
            printf("Goodbye!\n");
            freeAVL(tree);
            break;
        } else {
            printf("Unknown command\n");
        }
    }
    return 0;
}

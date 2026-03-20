#include <stdio.h>
#include <stdlib.h>

#ifndef USE_LIST
#include "list.h"
#define TYPE List
#else
#include "avl.h"
#define TYPE AVL
#endif
#define MAX_AIRPORTS 10000
#define MAX_BUFF 1024
int main(int argc, char* argv[])
{
    if (argc < 3)
        return 1;

    char* filename = argv[1];
    int scenario = atoi(argv[2]);

    char codes[MAX_AIRPORTS][10];
    char buff[MAX_BUFF];
    int count = 0;
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        return 1;
    }
    while ((fgets(buff, sizeof(buff), fp)) && (count < MAX_AIRPORTS)) {
        sscanf(buff, "%[^:]", codes[count++]);
    }
    fclose(fp);

    TYPE* container = load(filename);

    srandom(42);

    if (scenario == 1) {
        for (int i = 0; i < 50000; ++i) {
            find(container, codes[random() % count]);
        }
    } else if (scenario == 2) {
        char lastAdded[64];
        for (int i = 0; i < 10000; ++i) {
            sprintf(lastAdded, "X%d:New Airport %d", i, i);
            add(container, lastAdded);

            char codeToFind[10];
            sprintf(codeToFind, "X%d", (int)(random() % i));
            find(container, codeToFind);
        }
    }

    free(container);
    return 0;
}

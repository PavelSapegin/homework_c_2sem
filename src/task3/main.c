#include "expansion.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
    if ((argc > 1) && (strcmp(argv[1], "--test") == 0)) {
        runTests();
        return 0;
    }
    int n, m, k;

    FILE* fp = fopen("../src/task3/test.txt", "r");
    if (fp == NULL) {
        return 1;
    }

    fscanf(fp, "%d %d", &n, &m);

    int* owner = malloc(n * sizeof(int));
    if (owner == NULL) {
        return -1;
    }
    for (int i = 0; i < n; ++i) {
        owner[i] = -1;
    }

    Graph* graph = createGraph(n);
    readEdges(fp, graph, m);
    fscanf(fp, "%d", &k);
    MinHeap** minHeapArr = malloc(k * sizeof(MinHeap*));
    if (minHeapArr == NULL) {
        free(owner);
        return -3;
    }

    initCapitals(fp, graph, owner, minHeapArr, k);
    runExpansion(graph, minHeapArr, owner, k, n);
    print(owner, k, n);
    freeAll(minHeapArr, graph, owner, k, n);
    fclose(fp);

    return 0;
}

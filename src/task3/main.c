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

    if (argc < 2) {
        printf("Please provide input file path as an argument\n");
        return 1;
    }
    int n, m, k;

    FILE* fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Failed to open file: %s\n", argv[1]);
        return 1;
    }

    if (fscanf(fp, "%d %d", &n, &m) != 2) {
        fclose(fp);
        return 1;
    }

    int* owner = malloc(n * sizeof(int));
    if (owner == NULL) {
        fclose(fp);
        return -1;
    }
    for (int i = 0; i < n; ++i) {
        owner[i] = -1;
    }

    Graph* graph = createGraph(n);
    if (!readEdges(fp, graph, m)) {
        free(owner);
        deleteGraph(graph);
        fclose(fp);
        return -2;
    }

    if (fscanf(fp, "%d", &k) != 1) {
        fclose(fp);
        free(owner);
        deleteGraph(graph);
        return 1;
    }
    MinHeap** minHeapArr = malloc(k * sizeof(MinHeap*));
    if (minHeapArr == NULL) {
        free(owner);
        deleteGraph(graph);
        fclose(fp);
        return -3;
    }

    initCapitals(fp, graph, owner, minHeapArr, k);
    runExpansion(graph, minHeapArr, owner, k, n);
    print(owner, k, n);
    freeAll(minHeapArr, graph, owner, k);
    fclose(fp);

    return 0;
}

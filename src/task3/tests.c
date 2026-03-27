#include "expansion.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void testGraphCreation(void)
{
    printf("Running testGraphCreation... ");
    int n = 3;
    Graph* graph = createGraph(n);

    // Check allocation
    assert(graph != NULL);
    assert(graph->graph != NULL);

    // Check initialization with NULL
    for (int i = 0; i < n; ++i) {
        assert(graph->graph[i] == NULL);
    }

    // Test pushEdge
    Edge* e = createEdge(1, 10);
    assert(e->to_city == 1);
    assert(e->len == 10);
    assert(e->next == NULL);

    graph->graph[0] = pushEdge(graph->graph[0], e);
    assert(graph->graph[0] != NULL);
    assert(graph->graph[0]->to_city == 1);

    deleteGraph(graph, n);
    printf("PASSED!\n");
}

void testMinheapPushPop(void)
{
    printf("Running testMinheapPushPop... ");
    MinHeap* heap = createMinHeap();
    assert(heap != NULL);
    assert(heap->size == 0);

    // push elements in random order
    push(heap, 1, 30);
    push(heap, 2, 10);
    push(heap, 3, 20); 

    assert(heap->size == 3);

    assert(heap->nodes[0].len == 10);
    assert(heap->nodes[0].city == 2);

    MinHeapNode result;

    // Check pop
    pop(heap, &result);
    assert(result.city == 2 && result.len == 10);
    assert(heap->size == 2);

    pop(heap, &result);
    assert(result.city == 3 && result.len == 20);
    assert(heap->size == 1);


    pop(heap, &result);
    assert(result.city == 1 && result.len == 30);
    assert(heap->size == 0); // Heap must be a empty

    deleteMinHeap(heap);
    printf("PASSED!\n");
}

void testExpansionLogic(void)
{
    printf("Running testExpansionLogic... ");

    // Test situation
    // 3 cities; roads: 0 - 1 (len 5), 1 - 2 (len 5)
    // Country 0 with capital 0
    // Country 1 with capital 2
    // City 1 must be in Country 0

    int n = 3, k = 2;
    Graph* graph = createGraph(n);


    graph->graph[0] = pushEdge(graph->graph[0], createEdge(1, 5));
    graph->graph[1] = pushEdge(graph->graph[1], createEdge(0, 5));

    graph->graph[1] = pushEdge(graph->graph[1], createEdge(2, 5));
    graph->graph[2] = pushEdge(graph->graph[2], createEdge(1, 5));

    int* owner = malloc(n * sizeof(int));
    assert(owner != NULL);

    owner[0] = -1;
    owner[1] = -1;
    owner[2] = -1;

    MinHeap** heaps = malloc(k * sizeof(MinHeap*));
    assert(heaps != NULL);
    heaps[0] = createMinHeap();
    heaps[1] = createMinHeap();

    owner[0] = 0;
    push(heaps[0], 1, 5);

    owner[2] = 1;
    push(heaps[1], 1, 5);

    // Run expasion test
    runExpansion(graph, heaps, owner, k, n);

    assert(owner[0] == 0); 
    assert(owner[2] == 1); 
    assert(owner[1] == 0);

    freeAll(heaps, graph, owner, k, n);
    printf("PASSED!\n");
}

void runTests(void)
{
    printf("--- Starting Unit Tests ---\n");

    testGraphCreation();
    testMinheapPushPop();
    testExpansionLogic();

    printf("--- All tests completed successfully! ---\n");
}

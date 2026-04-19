#include "expansion.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Edge* createEdge(int city, size_t len)
{
    Edge* newEdge = malloc(sizeof(Edge));
    if (newEdge == NULL) {
        return NULL;
    }
    newEdge->to_city = city;
    newEdge->len = len;
    newEdge->next = NULL;

    return newEdge;
}

Edge* pushEdge(Edge* head, Edge* newEdge)
{
    newEdge->next = head;
    head = newEdge;
    return head;
}

Graph* createGraph(int n)
{
    Graph* newGraph = malloc(sizeof(Graph));
    Edge** newGraphArr = calloc(n, sizeof(Edge*));
    if ((newGraph == NULL) || (newGraphArr == NULL)) {
        if (newGraph) {
            free(newGraph);
        }
        if (newGraphArr) {
            free(newGraphArr);
        }

        return NULL;
    }

    newGraph->graph = newGraphArr;
    newGraph->n = n;
    return newGraph;
}

void deleteGraph(Graph* graph)
{
    for (int i = 0; i < graph->n; ++i) {
        Edge* curr = graph->graph[i];
        while (curr != NULL) {
            Edge* next = curr->next;
            free(curr);
            curr = next;
        }
    }
    free(graph->graph);
    free(graph);
}

MinHeap* createMinHeap(void)
{
    MinHeap* heap = malloc(sizeof(MinHeap));
    if (heap == NULL)
        return NULL;

    heap->size = 0;
    heap->capacity = 10;

    MinHeapNode* newNodes = malloc(sizeof(MinHeapNode) * heap->capacity);
    if (newNodes == NULL) {
        free(heap);
        return NULL;
    }

    heap->nodes = newNodes;
    return heap;
}

void swap(MinHeapNode* node1, MinHeapNode* node2)
{
    MinHeapNode temp = *node1;
    *node1 = *node2;
    *node2 = temp;
}

bool push(MinHeap* heap, int newCity, size_t newLen)
{

    if (heap == NULL) {
        return false;
    }
    if (heap->size == heap->capacity) {
        // Safe for cap == 0
        size_t newCapacity = (heap->capacity == 0) ? 10 : heap->capacity * 2;
        MinHeapNode* newNodes = realloc(heap->nodes, newCapacity * sizeof(MinHeapNode));
        if (newNodes == NULL) {
            return false; // Return false if realloc fails
        }

        heap->capacity = newCapacity;
        heap->nodes = newNodes;
    }
    MinHeapNode* curr = &(heap->nodes[heap->size]);
    curr->city = newCity;
    curr->len = newLen;
    heap->size++;

    size_t i = heap->size - 1;
    while ((i > 0) && (heap->nodes[i].len < heap->nodes[(i - 1) / 2].len)) {
        swap(&heap->nodes[i], &heap->nodes[(i - 1) / 2]);
        i = (i - 1) / 2;
    }

    return true;
}

bool pop(MinHeap* heap, MinHeapNode* result)
{
    if (heap->size == 0) {
        return false;
    }
    *result = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->size - 1];
    heap->size--;

    size_t i = 0;
    while (2 * i + 1 < heap->size) {
        size_t minChildIndex = 2 * i + 1; // Left child
        if ((2 * i + 2 < heap->size) && (heap->nodes[minChildIndex].len > heap->nodes[2 * i + 2].len)) {
            minChildIndex = 2 * i + 2; // Right child
        }

        if (heap->nodes[i].len > heap->nodes[minChildIndex].len) {
            swap(&heap->nodes[i], &heap->nodes[minChildIndex]);
            i = minChildIndex;
        } else {
            break;
        }
    }

    return true;
}

void deleteMinHeap(MinHeap* heap)
{
    free(heap->nodes);
    free(heap);
}

bool readEdges(FILE* fp, Graph* graph, int m)
{

    for (int i = 0; i < m; ++i) {
        int u, v, len;
        if (fscanf(fp, "%d %d %d", &u, &v, &len) != 3) {
            return false;
        }
        u--;
        v--;

        Edge* newEdge1 = createEdge(u, len);
        Edge* newEdge2 = createEdge(v, len);
        graph->graph[u] = pushEdge(graph->graph[u], newEdge2);
        graph->graph[v] = pushEdge(graph->graph[v], newEdge1);
    }

    return true;
}

void initCapitals(FILE* fp, Graph* graph, int* owner, MinHeap** minHeapArr, int k)
{
    int capCity;
    for (int i = 0; i < k; ++i) {
        minHeapArr[i] = createMinHeap();
        fscanf(fp, "%d", &capCity);
        owner[--capCity] = i;
        Edge* currEdge = graph->graph[capCity];
        while (currEdge != NULL) {
            if (owner[currEdge->to_city] == -1) {
                push(minHeapArr[i], currEdge->to_city, currEdge->len);
            }
            currEdge = currEdge->next;
        }
    }
}

void runExpansion(Graph* graph, MinHeap** minHeapArr, int* owner, int k, int n)
{
    int occupiedCities = k;

    while (occupiedCities < n) {
        for (int i = 0; i < k; ++i) {
            MinHeapNode targetNode;
            bool found = false;
            while (minHeapArr[i]->size > 0) {
                pop(minHeapArr[i], &targetNode);
                if (owner[targetNode.city] == -1) {
                    found = true;
                    break;
                }
            }
            if (found) {
                owner[targetNode.city] = i;
                occupiedCities++;
                if (occupiedCities >= n) {
                    break;
                }
                Edge* curr = graph->graph[targetNode.city];
                while (curr != NULL) {
                    if (owner[curr->to_city] == -1) {
                        push(minHeapArr[i], curr->to_city, curr->len);
                    }
                    curr = curr->next;
                }
            }
        }
    }
}

void print(const int* owner, int k, int n)
{
    for (int i = 0; i < k; ++i) {
        printf("Country: %d\n", i + 1);
        for (int city = 0; city < n; ++city) {
            if (owner[city] == i) {
                printf("City: %d ", city + 1);
            }
        }
        printf("\n");
    }
}

void freeAll(MinHeap** minHeapArr, Graph* graph, int* owner, int k)
{
    for (int i = 0; i < k; ++i) {
        deleteMinHeap(minHeapArr[i]);
    }

    free(minHeapArr);
    deleteGraph(graph);
    free(owner);
}

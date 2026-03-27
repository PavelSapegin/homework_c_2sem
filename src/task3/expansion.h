#pragma once
#include <stdio.h>

// Связный список из ребер
typedef struct Edge {
    int to_city;
    size_t len;
    struct Edge* next;
} Edge;

typedef struct Graph {
    Edge** graph;
} Graph;

typedef struct MinHeapNode {
    int city;
    size_t len;
} MinHeapNode;

typedef struct MinHeap {
    MinHeapNode* nodes;
    size_t size;
    size_t capacity;
} MinHeap;

Edge* createEdge(int city, size_t len);
Edge* pushEdge(Edge* head, Edge* newEdge);
Graph* createGraph(int n);
void deleteGraph(Graph* graph, int n);
MinHeap* createMinHeap(void);
void swap(MinHeapNode* node1, MinHeapNode* node2);
MinHeap* push(MinHeap* heap, int newCity, size_t newLen);
MinHeap* pop(MinHeap* heap, MinHeapNode* result);
void deleteMinHeap(MinHeap* heap);
void readEdges(FILE* fp, Graph* graph, int m);
void initCapitals(FILE* fp, Graph* graph, int* owner, MinHeap** minHeapArr, int k);
void runExpansion(Graph* graph, MinHeap** minHeapArr, int* owner, int k, int n);
void print(const int* owner, int k, int n);
void freeAll(MinHeap** minHeapArr, Graph* graph, int* owner, int k, int n);
void testGraphCreation(void);
void testMinheapPushPop(void);
void testExpansionLogic(void);
void runTests(void);

#pragma once
#include <stdbool.h>
#include <stdio.h>

// Связный список из ребер
typedef struct Edge {
    int to_city;
    size_t len;
    struct Edge* next;
} Edge;

typedef struct Graph {
    Edge** graph;
    int n; // Кол-во городов
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
void deleteGraph(Graph* graph);
MinHeap* createMinHeap(void);
void swap(MinHeapNode* node1, MinHeapNode* node2);
bool push(MinHeap* heap, int newCity, size_t newLen);
bool pop(MinHeap* heap, MinHeapNode* result);
void deleteMinHeap(MinHeap* heap);
bool readEdges(FILE* fp, Graph* graph, int m);
void initCapitals(FILE* fp, Graph* graph, int* owner, MinHeap** minHeapArr, int k);
void runExpansion(Graph* graph, MinHeap** minHeapArr, int* owner, int k, int n);
void print(const int* owner, int k, int n);
void freeAll(MinHeap** minHeapArr, Graph* graph, int* owner, int k);
void testGraphCreation(void);
void testMinheapPushPop(void);
void testExpansionLogic(void);
void runTests(void);

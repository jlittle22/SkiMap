#ifndef MINHEAP_H
#define MINHEAP_H

#include "Vertex.h"
#include "math.h"

#define INIT_CAPACITY 10

struct MinHeap{
	Vertex* dataArray;
	unsigned numElems;
	unsigned capacity;
};

#define HEAP_STRUCT_SIZE sizeof(struct MinHeap)

typedef struct MinHeap* MinHeap;

// Member Functions

MinHeap MinHeap_new();
void MinHeap_free(MinHeap);
void MinHeap_insert(MinHeap, Vertex);
void MinHeap_upHeapify(Vertex* arr, unsigned index);
void MinHeap_downHeapify(Vertex* arr, unsigned size, unsigned index);
Vertex MinHeap_extractTop(MinHeap);

#endif

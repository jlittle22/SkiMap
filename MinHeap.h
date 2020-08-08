#ifndef MINHEAP_H
#define MINHEAP_H

#include "Vertex.h"
#include "math.h"

#define INIT_CAPACITY 10

struct MinHeap {
	Vertex* dataArray;
	unsigned numElems;
	unsigned capacity;
};

#define HEAP_STRUCT_SIZE sizeof(struct MinHeap)

typedef struct MinHeap* MinHeap;

/* Initialize a new MinHeap object */
MinHeap MinHeap_new();

/* Free a MinHeap object */
void MinHeap_free(MinHeap);

/* Insert a Vertex object into a MinHeap Object */
void MinHeap_insert(MinHeap, Vertex);

/* Extract the top element from the MinHeap Object */ 
Vertex MinHeap_extractTop(MinHeap);

#endif

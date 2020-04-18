//     What is this module?     //
//------------------------------//
// This is our Vertex interface //
// for a graph.                 //
////////////////////////////////// 

#ifndef VERTEX_H
#define VERTEX_H

#include<inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Edge.h"
#include "LinkedList.h"

#define VERT_NAME_CHAR_COUNT 7

////////////////////////////////
//   Vertex Classifications   //
////////////////////////////////
#define OFFLOAD 0
#define ONLOAD 1 
#define INTERSECTION 2

///////////////////////////
//        BITPACK        //
///////////////////////////

/*    Vertex    */
#define VERT_CLASS_MSB 2
#define DISC_FLAG (VERT_CLASS_MSB+1)

struct Vertex{
	char vertexName[VERT_NAME_CHAR_COUNT];
	uint8_t data; 
	List edges;   
}; 

#define VERTEX_SIZE sizeof(struct Vertex)
typedef struct Vertex* Vertex; 

Vertex Vertex_new(char name[], uint8_t classValue);
void Vertex_free(Vertex);
void Vertex_addEdge(Vertex, void *);
Edge Vertex_getEdge(Vertex obj, int index);
int Vertex_numEdges(Vertex obj);
uint8_t Vertex_getClass(Vertex obj);
bool Vertex_isDiscovered(Vertex obj);
void Vertex_setDiscovered(Vertex obj, bool value);






#endif

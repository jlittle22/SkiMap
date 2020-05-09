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
#include "SmallFloat.h"

#define VERT_NAME_CHAR_COUNT 11

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
#define VERT_CLASS_MSB 1 
#define DISC_FLAG (VERT_CLASS_MSB+1) 
#define DISTANCE_LSB (DISC_FLAG+1) 
#define INFINITE_DIST 16.0F//((uint32_t)((0x0-1)>>(DISTANCE_LSB)))

struct Vertex{
	char vertexName[VERT_NAME_CHAR_COUNT]; // 11
	uint8_t edgesInPath; // 1
	uint32_t data; // 4 
	List edges;   // 8 
	Edge toParent; // 8 	
}; 

#define VERTEX_SIZE sizeof(struct Vertex)
typedef struct Vertex* Vertex; 

Vertex Vertex_new(char name[], uint32_t classValue);
void Vertex_free(Vertex);
void Vertex_addEdge(Vertex, void *);
Edge Vertex_getEdge(Vertex obj, int index);
int Vertex_numEdges(Vertex obj);
uint32_t Vertex_getClass(Vertex obj);
bool Vertex_isDiscovered(Vertex obj);
void Vertex_setDiscovered(Vertex obj, bool value);
void Vertex_setDistance(Vertex obj, float distance);
float Vertex_getDistance(Vertex obj);
bool Vertex_isInfinite(Vertex obj);
uint8_t Vertex_getNumEdgesInPath(Vertex obj);
float Vertex_getNewAvg(Vertex obj, float newNumber);
void Vertex_updateAverage(Vertex obj, float newPathWeight, uint8_t numEdgesInPath);

#endif

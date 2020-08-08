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

/*    Vertex  */
#define VERT_CLASS_MSB 1 
#define DISC_FLAG (VERT_CLASS_MSB + 1) 
#define DISTANCE_LSB (DISC_FLAG + 1)  // presently, this leaves 1 unused bit on the far left of word. Alternative: DISC_FLAG + 2 
#define INFINITE_DIST 16.0F  // ((uint32_t)((0x0-1)>>(DISTANCE_LSB)))

struct Vertex {
	char vertexName[VERT_NAME_CHAR_COUNT]; // 11
	uint8_t edgesInPath; // 1
	uint32_t data; // 4 
	List edges;   // 8 
	Edge toParent; // 8
}; 

// NOTE: 4 most significant bits of a SmallFloat object are unused!! Use them for 

#define VERTEX_SIZE sizeof(struct Vertex)
typedef struct Vertex* Vertex; 

/* Initialize a new Vertex object */
Vertex Vertex_new(char name[], uint32_t classValue);

/* Free a Vertex object. */
void Vertex_free(Vertex);

/* Add an Edge object to a Vertex object's adjacency list */
void Vertex_addEdge(Vertex, void *);

/* Get an indexed Edge from a Vertex's adjacency list */
Edge Vertex_getEdge(Vertex obj, int index);

/* Get the number of Edges originating from a Vertex */
int Vertex_numEdges(Vertex obj);

/* Get a Vertex's classification */
uint32_t Vertex_getClass(Vertex obj);

/* Check if a Vertex is discovered */
bool Vertex_isDiscovered(Vertex obj);

/* Set a Vertex's discovered value */
void Vertex_setDiscovered(Vertex obj, bool value);

/* Set a Vertex's distance value */
void Vertex_setDistance(Vertex obj, float distance);

/* Get a Vertex's distance value */
float Vertex_getDistance(Vertex obj);

/* Get the number of Edges in the current best path to a Vertex from a source */ 
uint8_t Vertex_getNumEdgesInPath(Vertex obj);

/* Calculates the average weight (distance) of a path if newNumber were to be a new edge added. */
float Vertex_getNewAvg(Vertex obj, float newNumber);

/* Updates the average weight (distance) of a Vertex's best path */
void Vertex_updateAverage(Vertex obj, float newPathWeight, uint8_t numEdgesInPath);

#endif

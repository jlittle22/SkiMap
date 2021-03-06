//     What is this module?     //
//------------------------------//
// This is the Edge interface   //
// for a graph. This is NOT     //
// polymorphic (sad.) so it's   //
// really just for this project.//
//////////////////////////////////
#ifndef EDGE_H
#define EDGE_H

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "Errors.h"

#define EDGE_NAME_CHAR_COUNT 15
#define ONE_BIT_AT(n) ((uint32_t)0x1 << n)
#define EDGE_SIZE sizeof(struct Edge)
typedef struct Edge* Edge;


//////////////////////
//   Diff Ratings   //
//////////////////////
#define GREEN 0 
#define BLUE 1
#define BLACK 2
#define DOUBLE 3
#define PARK 4
#define GLADES 5
#define MOGULS 6
#define LIFT_UP 7

typedef struct Vertex* Vertex;

struct Edge {
	char edgeName[EDGE_NAME_CHAR_COUNT];
    uint8_t diffRating;
    Vertex destination;
    Vertex source;  
};

/* Initializes an new Edge object */
Edge Edge_new(char name[], uint8_t array[], int numFlags, Vertex dest, Vertex src);

/* Retrieve the destination Vertex of an Edge object */
Vertex Edge_getDest(Edge obj);

/* Returns TRUE if an Edge object is rated as type (see Diff Ratings above) */
bool Edge_is(Edge obj, int type);

/* NOTE: Edge's are automatically freed in List_free(List obj). */

#endif

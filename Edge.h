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
#define ONE_BIT_AT(n) ((uint8_t)0x1 << n)
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

struct Edge{
	char edgeName[EDGE_NAME_CHAR_COUNT];
    uint8_t diffRating;
    Vertex destination;  
};

Edge Edge_new(char name[], uint8_t array[], int numFlags, Vertex dest);
Vertex Edge_getDest(Edge obj);
///////////////
// Edge Bits //
///////////////
bool Edge_is(Edge obj, int type);


#endif

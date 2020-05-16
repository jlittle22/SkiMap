//     What is this module?     //
//------------------------------//
// This is basically a custom   //
// graph interface. It's        //
// explicitly for this project  //
// and where we need to do most //
// of the buildig... path       //
// finding.                     //
//////////////////////////////////
#ifndef SKIMAP_H
#define SKIMAP_H

#include <time.h>
#include "Vertex.h"

#define MTN_NAME_SIZE 14
#define MAX_EDGE_LINE_SIZE 100
#define SIZE_OF_WORD 8
#define SIZE_OF_WORD_F 8.0F
#define BELLMAN_ERROR 0.0F

struct SkiMap{
	char mtnName[MTN_NAME_SIZE];
	List allVertices; 
	List startPoints;
};

#define SKI_MAP_SIZE sizeof(struct SkiMap)

typedef struct SkiMap* SkiMap;

/* Initialize a new SkiMap object */
SkiMap SkiMap_new(char name[], char* vdata, char* edata);

/* Free a SkiMap object */
void SkiMap_free(SkiMap obj);

char* SkiMap_processInput(SkiMap obj, uint8_t userPreferences);

/* Search for a Vertex object in the SkiMap object */
Vertex SkiMap_searchVertex(SkiMap obj, char name[]);

/* Find a random path in a SkiMap object */
char* SkiMap_randomPathDown(SkiMap obj);

/* MARK FOR STATIC  */
float SkiMap_evaluateEdge(Edge target, uint8_t userPreferences);

/* Relaxes the Edge target. */
void SkiMap_relaxEdge(Vertex source, Edge target, uint8_t userPreferences);

/* Run a modified Bellman Ford Single Source Shortest Path search on a SkiMap object. */
void SkiMap_bellmanFord(SkiMap obj, Vertex source, uint8_t userPreferences);

/* Collected and report the result of a Bellman Ford search in a List of Edges */
List SkiMap_checkBFResults(SkiMap obj);

/* Converts a List of Edges representing a path into a string */
char* SkiMap_stringifyPath(List path);
#endif

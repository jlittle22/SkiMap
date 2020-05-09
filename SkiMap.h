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

struct SkiMap{
	char mtnName[MTN_NAME_SIZE];
	List allVertices; 
	List startPoints;
};

#define SKI_MAP_SIZE sizeof(struct SkiMap)

typedef struct SkiMap* SkiMap;

SkiMap SkiMap_new(char name[], char vertFile[], char trailFile[]);
void SkiMap_free(SkiMap obj);
void SkiMap_loadVertices(SkiMap obj, char vertFile[]);
void SkiMap_loadTrails(SkiMap obj, char trailFile[]);
Vertex SkiMap_searchVertex(SkiMap obj, char name[]);
void SkiMap_randomPathDown(SkiMap obj);
float SkiMap_evaluateEdge(Edge target, uint8_t userPreferences);
void SkiMap_relaxEdge(Vertex source, Edge target, uint8_t userPreferences);
void SkiMap_bellmanFord(SkiMap obj, Vertex source, uint8_t userPreferences);
void SkiMap_checkBFResults(SkiMap obj);
void SkiMap_driver();

#endif

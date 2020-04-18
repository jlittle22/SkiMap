#ifndef SKIMAP_H
#define SKIMAP_H

#include <time.h>
#include "Vertex.h"

#define MTN_NAME_SIZE 14
#define MAX_EDGE_LINE_SIZE 100

struct SkiMap{
	char mtnName[MTN_NAME_SIZE];
	List allVertices; 
	List startPoints;
};

#define SKI_MAP_SIZE sizeof(struct SkiMap)

typedef struct SkiMap* SkiMap;

SkiMap SkiMap_new(char name[], char vertFile[], char trailFile[]);
void SkiMap_loadVertices(SkiMap obj, char vertFile[]);
void SkiMap_loadTrails(SkiMap obj, char trailFile[]);
Vertex SkiMap_searchVertex(SkiMap obj, char name[]);
void SkiMap_randomPathDown(SkiMap obj);

void SkiMap_driver();

#endif

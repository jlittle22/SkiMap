#ifndef PATH_H
#define PATH_H

#include "Vertex.h"

#define INIT_SIZE 100

struct Path{
	char* string; 
	int capacity;
	int numElems;
	float score;
};

#define PATH_STRUCT sizeof(struct Path)

typedef struct Path* Path;

Path Path_new();
void Path_free(Path);
void Path_insert(Path, char*, char);

#endif

#include "SkiMap.h"

static void assignMtnName(SkiMap obj, char array[]);
static unsigned randomNum(unsigned upperBound);
static void randomPathDown_Helper(Vertex current, bool first);
static bool visitedAll(int arr[], int size);

void SkiMap_loadVertices(SkiMap obj, char vertFile[]){
	FILE* verts = fopen(vertFile, "r");	
	char stringName[VERT_NAME_CHAR_COUNT];
	uint8_t class; 
	while(!feof(verts)){
		fscanf(verts, "%s %hhu\n", stringName, &class);
		Vertex new = Vertex_new(stringName, class);
    	List_insert(obj->allVertices, new);
    	if (class == ONLOAD){
    		List_insert(obj->startPoints, new);
    	}
	}
}

static void loadTrail(SkiMap obj, char* line){
	char* token = strtok(line, " ");
	char* originVert; 
	char* destinVert; 
	char* edgeName; 
	uint8_t flags[8]; 
	int count = 0;
	int numFlags = 0;
	while(token != NULL){
		if (count == 0){
			originVert = token;
		}
		else if(count == 1){
			destinVert = token;
		}
		else if(count == 2){
			edgeName = token;
		}
		else if(count > 2){
			flags[numFlags] = (uint8_t)atoi(token);
			numFlags++;
		}
		token = strtok(NULL, " ");
		count++;
	}
	Vertex source = SkiMap_searchVertex(obj, originVert);
	Vertex dest = SkiMap_searchVertex(obj, destinVert);
	Edge new = Edge_new(edgeName, flags, numFlags, dest);
	Vertex_addEdge(source, new);
}

void SkiMap_loadTrails(SkiMap obj, char trailFile[]){
	assert(obj);
	FILE* trails = fopen(trailFile, "r");
	assert(trails);
	while (!feof(trails)){
		char line[MAX_EDGE_LINE_SIZE];
		fgets(line, MAX_EDGE_LINE_SIZE, trails);
		loadTrail(obj, line);
	}
}

SkiMap SkiMap_new(char name[], char vertFile[], char trailFile[]){
	SkiMap obj = malloc(SKI_MAP_SIZE);
	obj->allVertices = List_new();
	obj->startPoints = List_new();
	assignMtnName(obj, name);
    SkiMap_loadVertices(obj, vertFile);
    SkiMap_loadTrails(obj, trailFile);
    return obj;
}

Vertex SkiMap_searchVertex(SkiMap obj, char name[]){
	assert(obj);
	int size = List_numItems(obj->allVertices);
	Vertex curr;
	for (int i = 0; i < size; i++){
		curr = (Vertex)List_getItem(obj->allVertices, i)->data;
		if (strcmp(curr->vertexName, name) == 0){
			return curr;
		}
	}
	nullCheck("ERROR: in SkiMap_searchVertex. Vertex not found.", NULL);
	return NULL;
}

void SkiMap_randomPath(SkiMap obj){
	(void)obj;
	fprintf(stderr, "%u\n", randomNum(10));
}

void SkiMap_randomPathDown(SkiMap obj){
	unsigned numStarts = (unsigned)List_numItems(obj->startPoints);
	Vertex start = (Vertex)List_getItem(obj->startPoints, randomNum(numStarts))->data;
	randomPathDown_Helper(start, true);
}

static void randomPathDown_Helper(Vertex current, bool first){
	if (!first){
		Vertex_setDiscovered(current, true);
	}
	int numEdges = Vertex_numEdges(current);
	int checkCounter[numEdges];
	memset(checkCounter, 0, sizeof(numEdges));
	while(!visitedAll(checkCounter, numEdges)){
		int checkIndex = randomNum(numEdges);
		checkCounter[checkIndex] = 1;
		Edge checkEdge = Vertex_getEdge(current, checkIndex);
		Vertex checkVert = Edge_getDest(checkEdge);
		if (!Vertex_isDiscovered(checkVert)){
			printf("%s -> ", checkEdge->edgeName);
			if(Vertex_getClass(checkVert) == ONLOAD && first == false){
				printf("%s\n", checkVert->vertexName);
				break; 
			}
			randomPathDown_Helper(checkVert, false);
			break;
		}
	}
	Vertex_setDiscovered(current, false);
}

static bool visitedAll(int arr[], int size){
	for(int i = 0; i < size; i++){
		if(arr[i] == 0){
			return false;
		}
	}
	return true;
} 

static void assignMtnName(SkiMap obj, char array[]){
	assert(obj);
	int i;
	int arraySize = strlen(array);
	int size = (arraySize > MTN_NAME_SIZE-1) ? MTN_NAME_SIZE-1 : arraySize;
	for(i = 0; i < size; i++){
		if(i == MTN_NAME_SIZE-1){
			break;
		}
		obj->mtnName[i] = array[i];
	}
	obj->mtnName[i] = '\0';
}

static unsigned randomNum(unsigned upperBound){
	return (rand() % upperBound); 
}

// Bellman-Ford Best Path:
//  * build relax edge function:
//    - check if source.dist + edge.weight < destination.distance 
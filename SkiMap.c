#include "SkiMap.h"

static void assignMtnName(SkiMap obj, char array[]);
static unsigned randomNum(unsigned upperBound);
static void randomPathDown_Helper(Vertex current, bool first);
static bool visitedAll(int arr[], int size);
static void freeAllVertices(List remove);
static bool checkFlag(uint8_t word, unsigned bitLocation);
static bool matchingFlags(int i, uint8_t field1, uint8_t field2);
static uint8_t defineNegationZone(uint8_t userPreferences);

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
	fclose(verts);
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
	Edge new = Edge_new(edgeName, flags, numFlags, dest, source);
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
	fclose(trails);
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

void SkiMap_free(SkiMap obj){
	assert(obj);
	freeAllVertices(obj->allVertices);
	List_partialFree(obj->startPoints);
	free(obj);
}
static void freeAllVertices(List remove){
	Node* current = remove->list->front; 
	Node* temp = NULL;
	while (current != NULL){
		temp = current->next; 
		Vertex_free((Vertex)current->data);
		free(current);
		current = temp; 
	}
	free(remove->list);
	free(remove);
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

char* SkiMap_stringifyPath(List pathList){
	int numItems = List_numItems(pathList);
	char* path = (char*)malloc(VERT_NAME_CHAR_COUNT * numItems);
	*path = '\0';
	nullCheck("ERROR:: at SkiMap_stringifyPath. Malloc failed.", path);
	for (int i = 0; i < numItems; i++){
		Vertex curr = (Vertex)(List_getItem(pathList, i)->data);
		char* currName = curr->vertexName;
		strcat(path, currName);
		strcat(path, " ");
	}
	List_partialFree(pathList);
	return path;
}

List SkiMap_checkBFResults(SkiMap obj){
	unsigned numVerts = List_numItems(obj->startPoints);
	float min = 16.0;
	int minIndex = -1;
	for (unsigned i = 0; i < numVerts; i++){
		Vertex curr = (Vertex)(List_getItem(obj->startPoints, i)->data);
		if(Vertex_getDistance(curr) < min){
			min = Vertex_getDistance(curr);
			minIndex = (int)i;
		}
	}
	if(minIndex == -1 || min == 16.0){
		fprintf(stderr, "BIG FAT ERROR IN SkiMap_checkBFResults!! No path reported!!\n");
		return NULL;
	}

	int j = 0;
	Vertex bestEnd = (Vertex)(List_getItem(obj->startPoints, minIndex)->data);
	float bestDistance = Vertex_getDistance(bestEnd);
	List bestPath = List_new();
	while(bestEnd != NULL){
		if(Vertex_getClass(bestEnd) == ONLOAD && j > 0){
			break;
		}
		Edge currEdge = bestEnd->toParent;
		List_insert(bestPath, currEdge);
		bestEnd = currEdge->source;
		j++;
	}
	fprintf(stderr, "VERTEX: %s Weight: %f\n", bestEnd->vertexName, bestDistance);
	List_print(bestPath->list);
	return bestPath;
	/*for(unsigned i = 0; i < numVerts; i++){
		Vertex curr = (Vertex)(List_getItem(obj->startPoints, i)->data);
		Vertex temp = curr;
		List path = List_new();
		int j = 0; 
		while(curr != NULL){
			if(Vertex_getClass(curr) == ONLOAD && j > 0){
				break;
			}
			Edge currEdge = curr->toParent;
			List_insert(path, currEdge);
			curr = currEdge->source;
			j++;
		}
		fprintf(stderr, "--Path %u--\n", i);
		fprintf(stderr, "VERTEX: %s Weight: %f\n",temp->vertexName, Vertex_getDistance(temp));
		List_print(path->list);
		List_partialFree(path);
	}*/
}

void SkiMap_bellmanFord(SkiMap obj, Vertex source, uint8_t userPreferences){
	Vertex_setDistance(source, 0);
	source->toParent = (void*)0x0;
	unsigned numVerts = (unsigned)List_numItems(obj->allVertices);
	for(unsigned k = 0; k < numVerts; k++){
		if (k == 1){
			Vertex_setDistance(source, INFINITE_DIST);
		}
		for (unsigned i = 0; i < numVerts; i++){
			Vertex test = (Vertex)(List_getItem(obj->allVertices, i)->data);
			unsigned numEdges = (unsigned)List_numItems(test->edges);
			for(unsigned j = 0; j < numEdges; j++){
				Edge currEdge = (Edge)(List_getItem(test->edges, j)->data);
				SkiMap_relaxEdge(test, currEdge, userPreferences);
			}
		}
	}
}

void SkiMap_relaxEdge(Vertex source, Edge target, uint8_t userPreferences){
	if(Vertex_getDistance(source) == INFINITE_DIST){
		return;
	}
	Vertex dest = target->destination;
	float newPathWeight = Vertex_getNewAvg(source, SkiMap_evaluateEdge(target, userPreferences)); 
	uint8_t newPathNumEdges = Vertex_getNumEdgesInPath(source) + 1;
	if(newPathWeight < Vertex_getDistance(dest)){
		dest->toParent = target;
		Vertex_updateAverage(dest, newPathWeight, newPathNumEdges);
	}
}

float SkiMap_evaluateEdge(Edge target, uint8_t userPreferences){
	assert(target);
	float score = SIZE_OF_WORD_F;
	for (unsigned i = 0; i < SIZE_OF_WORD; i++){
		if(matchingFlags(i, userPreferences, target->diffRating) == true){
			score = score - 1.0;
		}
		else if(matchingFlags(i, target->diffRating, defineNegationZone(userPreferences))){
			score = score + 0.5;
		}
	}
	return score;
}

static uint8_t defineNegationZone(uint8_t userPreferences){
	uint8_t diffMask = ONE_BIT_AT((DOUBLE+1))-1;
	int max = -1;
	for (int i = 0; i < DOUBLE; i++){
		if (checkFlag(userPreferences, i) == true){
			max = i;
		}
	}
	diffMask >>= (max+1);
	diffMask <<= (max+1);
	return diffMask;
}

static bool matchingFlags(int i, uint8_t field1, uint8_t field2){
	return (checkFlag(field1, i) == true && checkFlag(field2, i) == true); 
}

static bool checkFlag(uint8_t word, unsigned bitLocation){
	checkRange("ERROR: at CheckFlag.. bitLocation out of range.", bitLocation, (unsigned)(SIZE_OF_WORD-1));
	word = word >> bitLocation;
	uint8_t mask = ONE_BIT_AT(0);
	return (mask & word);
}


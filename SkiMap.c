#include "SkiMap.h"

static void assignMtnName(SkiMap obj, char array[]);
static unsigned randomNum(unsigned upperBound);
static void randomPathDown_Helper(Vertex current, bool first, List path);
static bool visitedAll(int arr[], int size);
static void freeAllVertices(List remove);
static bool checkFlag(uint8_t word, unsigned bitLocation);
static bool matchingFlags(int i, uint8_t field1, uint8_t field2);
static uint8_t defineNegationZone(uint8_t userPreferences);
static void readStringFile(SkiMap obj, char* data, void (*processLine)(SkiMap, char*));
static void loadVertices(SkiMap obj, char* vdata);
static void loadTrails(SkiMap obj, char* edata);
static float randomFloat(float magnitude);

static void loadVertex(SkiMap obj, char* line){
	char* token = strtok(line, " ");
	char* vertexName;
	char* vertClass;
	int count = 0;
	while(token != NULL){
		if(count == 0){
			vertexName = token;
		}
		else if(count == 1){
			vertClass = token;
		}
		token = strtok(NULL, " ");
		count++;
	}
	uint32_t class = (uint32_t)atoi(vertClass);
	Vertex newGuy = Vertex_new(vertexName, class);
	if(class == ONLOAD){
		List_insert(obj->startPoints, newGuy);
	}
	List_insert(obj->allVertices, newGuy);

}

static void readStringFile(SkiMap obj, char* data, void (*processLine)(SkiMap, char*)){
	nullCheck("ERROR:: at SkiMap_readStringFile. Obj is NULL.", obj);
	nullCheck("ERROR:: at SkiMap_readStringFile. Data is NULL.", data);
	char line[MAX_EDGE_LINE_SIZE];
	memset(line, 0, MAX_EDGE_LINE_SIZE);
	char curr= 'A';
	int index = 0;
	while (curr != '\0'){
		curr = (*data);
		if(curr == '\n'){
			processLine(obj, line);
			index = 0;
			memset(line, 0, MAX_EDGE_LINE_SIZE);
		}
		else {
			line[index] = curr;
			index++;
		}
		data++;
	}
}

static void loadVertices(SkiMap obj, char* vdata){
	nullCheck("ERROR:: at loadVertices. Obj is NULL.", obj);
	readStringFile(obj, vdata, loadVertex);
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

static void loadTrails(SkiMap obj, char* edata){
	nullCheck("ERROR:: at loadTrails. Obj is NULL.", obj);
	readStringFile(obj, edata, loadTrail);
}

SkiMap SkiMap_new(char name[], char* vdata, char* edata){
	SkiMap obj = malloc(SKI_MAP_SIZE);
	obj->allVertices = List_new();
	obj->startPoints = List_new();
	assignMtnName(obj, name);
    loadVertices(obj, vdata);
    loadTrails(obj, edata);
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

char* SkiMap_processInput(SkiMap obj, uint8_t userPreferences){
	char* path;
	if (userPreferences == 128 || userPreferences == 255){
		path = SkiMap_randomPathDown(obj);
	}
	else{
		Vertex src = (Vertex)(List_getItem(obj->startPoints, 0)->data);
		SkiMap_bellmanFord(obj, src, userPreferences);
		path = SkiMap_stringifyPath(SkiMap_checkBFResults(obj));
	}
	return path;
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

char* SkiMap_randomPathDown(SkiMap obj){
	unsigned numStarts = (unsigned)List_numItems(obj->startPoints);
	Vertex start = (Vertex)List_getItem(obj->startPoints, randomNum(numStarts))->data;
	List path = List_new();
	randomPathDown_Helper(start, true, path);
	path = List_reverseList(path);
	char* pathString = SkiMap_stringifyPath(path);
	return pathString;
}


static void randomPathDown_Helper(Vertex current, bool first, List path){
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
			List_insert(path, checkEdge);
			if(Vertex_getClass(checkVert) == ONLOAD && first == false){
				break; 
			}
			randomPathDown_Helper(checkVert, false, path);
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

static float randomFloat(float magnitude){
	bool negative = (rand()%2);
	float num = ((float)rand()/(float)RAND_MAX)*magnitude;
	if(negative){
		num *= -1.0;
	}
	return num;
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
	fprintf(stderr, "Score: %f ", min);
	return bestPath;
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
		Vertex_updateAverage(dest, newPathWeight+randomFloat(0.3), newPathNumEdges);
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
			score = score + 0.8;
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


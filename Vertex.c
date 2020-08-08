#include "Vertex.h"

static void assignVertName(Vertex obj, char array[]);

/* Bitpacking Mini-Module */ 
static void setFDistance(Vertex obj, float input);
static float getFDistance(Vertex obj);
static uint32_t flag(uint32_t word, int bitLocation);
static uint32_t unflag(uint32_t word, int bitLocation);
static void checkRatingRange(uint32_t givenVal);
static uint32_t setDiffRate(uint32_t word, uint32_t rating);
static bool checkFlag(uint32_t word, int bitLocation);
static uint32_t getDiffRate(uint32_t word);

Vertex Vertex_new(char name[], uint32_t classValue){
	Vertex new = malloc(VERTEX_SIZE);
	nullCheck("ERROR: at Malloc in Vertex_new.", new);
	assignVertName(new, name);
	new->data = setDiffRate(new->data, classValue);
	Vertex_setDistance(new, INFINITE_DIST);
	Vertex_setDiscovered(new, false);
	new->edges = List_new();
	new->toParent = NULL;
	new->edgesInPath = 0;
	return new;
}

void Vertex_free(Vertex delete){
	nullCheck("ERROR:: at Vertex_free. Obj is NULL.", delete);
	List_free(delete->edges);
	free(delete);
}

static void assignVertName(Vertex obj, char array[]){
	nullCheck("ERROR:: at assignVertName. Obj is NULL.", obj);
	nullCheck("ERROR:: at assignVertName. Name string is NULL.", array);
	int i;
	int arraySize = strlen(array);
	int size = (arraySize > VERT_NAME_CHAR_COUNT-1) ? VERT_NAME_CHAR_COUNT-1 : arraySize;
	for(i = 0; i < size; i++){
		if(i == VERT_NAME_CHAR_COUNT-1){
			break;
		}
		obj->vertexName[i] = array[i];
	}
	obj->vertexName[i] = '\0';
}

void Vertex_addEdge(Vertex obj, void * newEdge){
	nullCheck("ERROR:: at Vertex_addEdge. Obj is NULL.", obj);
	nullCheck("ERROR:: at Vertex_addEdge. newEdge is NULL.", newEdge);
	assert(newEdge);
	List_insert(obj->edges, newEdge);
}

Edge Vertex_getEdge(Vertex obj, int index){
	nullCheck("ERROR:: at Vertex_getEdge. Obj is NULL.", obj);
	Node* resultNode = List_getItem(obj->edges, index); 
	if (resultNode == NULL){
		return NULL;
	}	
	return (Edge)resultNode->data;
}

int Vertex_numEdges(Vertex obj){
	nullCheck("ERROR:: at Vertex_numEdges. Obj is NULL.", obj);
	return List_numItems(obj->edges);
}

uint32_t Vertex_getClass(Vertex obj){
	nullCheck("ERROR:: at Vertex_getClass. Obj is NULL.", obj);
	return getDiffRate(obj->data);
}

bool Vertex_isDiscovered(Vertex obj){
	nullCheck("ERROR:: at Vertex_isDiscovered. Obj is NULL.", obj);
	return checkFlag(obj->data, DISC_FLAG);
}

void Vertex_setDiscovered(Vertex obj, bool value){
	nullCheck("ERROR:: at Vertex_setDiscovered. Obj is NULL.", obj);
	if(value == true){
		obj->data = flag(obj->data, DISC_FLAG);
	}
	else {
		obj->data = unflag(obj->data, DISC_FLAG);
	}
}
void Vertex_setDistance(Vertex obj, float distance){
	nullCheck("ERROR:: at Vertex_setDistance. Obj is NULL.", obj);
	setFDistance(obj, distance);
}

float Vertex_getDistance(Vertex obj){
	nullCheck("ERROR:: at Vertex_getDistance. Obj is NULL.", obj);
	return getFDistance(obj);
}

uint8_t Vertex_getNumEdgesInPath(Vertex obj){
	nullCheck("ERROR:: at Vertex_getNumEdgesInPath. Obj is NULL.", obj);
	return obj->edgesInPath;
}

void Vertex_updateAverage(Vertex obj, float newPathWeight, uint8_t numEdgesInPath){
	nullCheck("ERROR:: at Vertex_updateAverage. Obj is NULL.", obj);
	Vertex_setDistance(obj, newPathWeight);
	obj->edgesInPath = numEdgesInPath;
}

float Vertex_getNewAvg(Vertex obj, float newNumber){
	nullCheck("ERROR:: at Vertex_getNewAvg. Obj is NULL.", obj);
	float currAvg = Vertex_getDistance(obj);
	float numberOfValues = (float)Vertex_getNumEdgesInPath(obj);
	float newAvg = currAvg*(numberOfValues/(numberOfValues+1)) + (newNumber/(numberOfValues+1));
	return newAvg;
}

///////////////////////////
//        BITPACK        //
///////////////////////////
static void setFDistance(Vertex obj, float input){
	nullCheck("ERROR:: at setDistance. Obj is NULL.", obj);
	SmallFloat compressor = SmallFloat_FtoSF(input);
	uint32_t compressed = SmallFloat_getData(compressor);
	SmallFloat_free(compressor);
	fprintf(stderr, "compressed: %x\n", compressed);
	compressed = compressed << DISTANCE_LSB;
	fprintf(stderr, "compressed shifted: %x\n", compressed);
	uint32_t clearMask = ONE_BIT_AT(DISTANCE_LSB)-1;
	clearMask = clearMask & obj->data;
	compressed = compressed | clearMask;
	obj->data = compressed;
}

static float getFDistance(Vertex obj){
	uint32_t mask = ONE_BIT_AT(SF_BITS) - 1;
	mask = mask << DISTANCE_LSB;
	mask = mask & obj->data;
	mask = mask >> DISTANCE_LSB;
	float decompressed = SmallFloat_SFDatatoF(mask);
	return decompressed;
}

static uint32_t flag(uint32_t word, int bitLocation){
	uint32_t mask = ONE_BIT_AT(bitLocation);
	return mask | word;
}

static uint32_t unflag(uint32_t word, int bitLocation){
	uint32_t mask = ONE_BIT_AT(bitLocation);
	mask = ~mask;
	return mask & word;
}

static void checkRatingRange(uint32_t givenVal){
	uint32_t max = ONE_BIT_AT((VERT_CLASS_MSB+1)) - 1;
	if (givenVal > max){
		fprintf(stderr, "ERROR: difficulty rating {%u} is out of range.\n", givenVal);
		exit(1);
	}
}

static uint32_t setDiffRate(uint32_t word, uint32_t rating){
	checkRatingRange(rating);
	uint32_t mask = ~(ONE_BIT_AT((VERT_CLASS_MSB+1)) - 1); 
	uint32_t result = (mask & word) | rating; 
	return result;
}

static bool checkFlag(uint32_t word, int bitLocation){
	word = word & ONE_BIT_AT(bitLocation);
	return word;
}

static uint32_t getDiffRate(uint32_t word){
	uint32_t mask = ONE_BIT_AT((VERT_CLASS_MSB+1))-1;
	return (word & mask);
}

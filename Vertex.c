#include "Vertex.h"


static void assignVertName(Vertex obj, char array[]);

/* Bitpacking Mini-Module */ 
static uint8_t flag(uint8_t word, int bitLocation);
static uint8_t unflag(uint8_t word, int bitLocation);
static void checkRatingRange(uint8_t givenVal);
static uint8_t setDiffRate(uint8_t word, uint8_t rating);
static bool checkFlag(uint8_t word, int bitLocation);
static uint8_t getDiffRate(uint8_t word);
/*                        */


Vertex Vertex_new(char name[], uint8_t classValue){
	Vertex new = malloc(VERTEX_SIZE);
	nullCheck("ERROR: at Malloc in Vertex_new.", new);
	assignVertName(new, name);
	new->data = setDiffRate(new->data, classValue);
	new->edges = List_new();
	return new;
}

void Vertex_free(Vertex delete){
	assert(delete);
	List_free(delete->edges);
	free(delete);
}

static void assignVertName(Vertex obj, char array[]){
	assert(obj);
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
	assert(obj);
	assert(newEdge);
	List_insert(obj->edges, newEdge);
}

Edge Vertex_getEdge(Vertex obj, int index){
	assert(obj);
	Node* resultNode = List_getItem(obj->edges, index); 
	if (resultNode == NULL){
		return NULL;
	}	
	return (Edge)resultNode->data;
}

int Vertex_numEdges(Vertex obj){
	assert(obj);
	return List_numItems(obj->edges);
}

uint8_t Vertex_getClass(Vertex obj){
	assert(obj);
	return getDiffRate(obj->data);
}

bool Vertex_isDiscovered(Vertex obj){
	assert(obj);
	return checkFlag(obj->data, DISC_FLAG);
}

void Vertex_setDiscovered(Vertex obj, bool value){
	assert(obj);
	if(value == true){
		obj->data = flag(obj->data, DISC_FLAG);
	}
	else {
		obj->data = unflag(obj->data, DISC_FLAG);
	}
}




///////////////////////////
//        BITPACK        //
///////////////////////////

static uint8_t flag(uint8_t word, int bitLocation){
	uint8_t mask = ONE_BIT_AT(bitLocation);
	return mask | word;
}

static uint8_t unflag(uint8_t word, int bitLocation){
	uint8_t mask = (0x1 << (bitLocation + 1)) -1;
	return mask & word;
}

static void checkRatingRange(uint8_t givenVal){
	uint8_t max = ONE_BIT_AT((VERT_CLASS_MSB+1)) - 1;
	if (givenVal > max){
		fprintf(stderr, "ERROR: difficulty rating {%u} is out of range.\n", givenVal);
		exit(1);
	}
}

static uint8_t setDiffRate(uint8_t word, uint8_t rating){
	checkRatingRange(rating);
	uint8_t mask = ~(ONE_BIT_AT((VERT_CLASS_MSB+1)) - 1); 
	uint8_t result = (mask & word) | rating; 
	return result;
}

static bool checkFlag(uint8_t word, int bitLocation){
	return (word >> bitLocation);
}

static uint8_t getDiffRate(uint8_t word){
	uint8_t mask = ONE_BIT_AT((VERT_CLASS_MSB+1))-1;
	return (word & mask);
}



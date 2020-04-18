#include "Edge.h"

static uint8_t flag(uint8_t word, int bitLocation);
static bool checkFlag(uint8_t word, int bitLocation);
static void assignEdgeName(Edge obj, char array[]);
static uint8_t initDiffRatings(uint8_t flags[], int length);

Edge Edge_new(char name[], uint8_t flags[], int numFlags, Vertex dest){
	nullCheck("ERROR: Vertex passed to Edge_new is NULL", dest);
	Edge new = malloc(EDGE_SIZE); 
	nullCheck("ERROR: at Malloc in Edge_new", new);
	assignEdgeName(new, name);
	new->destination = dest;
	new->diffRating = initDiffRatings(flags, numFlags);
	return new;
}

Vertex Edge_getDest(Edge obj){
	assert(obj);
	return obj->destination;
}

static uint8_t initDiffRatings(uint8_t flags[], int numFlags){
	assert(flags);
	uint8_t result = 0x0;
	for (uint32_t i = 0; i < (uint32_t)numFlags; i++){
		result = flag(result, flags[i]);
	}
	return result;
}

bool Edge_is(Edge obj, int type){
	assert(obj);
	return checkFlag(obj->diffRating, type);
}

static uint8_t flag(uint8_t word, int bitLocation){
	uint8_t mask = ONE_BIT_AT(bitLocation);
	return mask | word;
}

static bool checkFlag(uint8_t word, int bitLocation){
	uint8_t mask = ONE_BIT_AT(0);
	word = word >> bitLocation;

	return (word & mask);
}


//////////////////
//     EDGE     //
//////////////////

static void assignEdgeName(Edge obj, char array[]){
	assert(obj);
	int i;
	int arraySize = strlen(array);
	int size = (arraySize > EDGE_NAME_CHAR_COUNT-1) ? EDGE_NAME_CHAR_COUNT-1 : arraySize;
	for(i = 0; i < size; i++){
		if(i == EDGE_NAME_CHAR_COUNT-1){
			break;
		}
		obj->edgeName[i] = array[i];
	}
	obj->edgeName[i] = '\0';
}



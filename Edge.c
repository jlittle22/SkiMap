#include "Edge.h"

/* Flag the bit at bitlocation in the word */
static uint8_t flag(uint8_t word, int bitLocation);

/* Check if the bit at bitlocation is flagged */
static bool checkFlag(uint8_t word, int bitLocation);

/* Assign a name to an edge struct */
static void assignEdgeName(Edge obj, char array[]);

/* Flag the proper bits in a word */
static uint8_t initDiffRatings(uint8_t flags[], int length);

/* Allocate memory and initialize a new Edge object */
Edge Edge_new(char name[], uint8_t flags[], int numFlags, Vertex dest, Vertex src){
	nullCheck("ERROR: Vertex passed to Edge_new is NULL", dest);
	Edge new = malloc(EDGE_SIZE); 
	nullCheck("ERROR: at Malloc in Edge_new", new);
	assignEdgeName(new, name);
	new->destination = dest;
	new->diffRating = initDiffRatings(flags, numFlags);
	new->source = src;
	return new;
}

/* Return the a pointer to the Edge's destination Vertex */
Vertex Edge_getDest(Edge obj){
	assert(obj);
	return obj->destination;
}

/* Flag the proper bits for an Edge's diffRating attribute */
static uint8_t initDiffRatings(uint8_t flags[], int numFlags){
	assert(flags);
	uint8_t result = 0x0;
	for (uint32_t i = 0; i < (uint32_t)numFlags; i++){
		result = flag(result, flags[i]);
	}
	return result;
}

/* Check if an Edge is flagged with a certain characteristic */
bool Edge_is(Edge obj, int type){
	assert(obj);
	return checkFlag(obj->diffRating, type);
}

/* Flagged the bit at bitlocation in the word and return it */
static uint8_t flag(uint8_t word, int bitLocation){
	uint8_t mask = ONE_BIT_AT(bitLocation);
	return mask | word;
}

/* Check if the bit at bitlocation is flagged in word */
static bool checkFlag(uint8_t word, int bitLocation){
	uint8_t mask = ONE_BIT_AT(0);
	word = word >> bitLocation;

	return (word & mask);
}

/* Assigned a name to an Edge object and ensure it fits inside the pre-designated size */
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



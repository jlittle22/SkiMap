#include "SkiMap.h"
#include "MinHeap.h"
#include "SmallFloat.h"

int main(){//////////////
	uint8_t userP = 1; // <- Edit me! User preferences are a byte. 
///////////////////////// Example: 00000101 is GREEN and BLACKS (0th and 2nd bits are flagged.)

	srand(time(NULL));
	SkiMap test = SkiMap_new("TEstMtn", "basic.vdata", "basic.edata");
	Vertex src = (Vertex)(List_getItem(test->startPoints, 0)->data);
	SkiMap_bellmanFord(test, src, userP);
	SkiMap_checkBFResults(test);
	SkiMap_free(test);
	return 0;
}

void run(uint8_t userP){//////////////
	userP = 1; // <- Edit me! User preferences are a byte. 
///////////////////////// Example: 00000101 is GREEN and BLACKS (0th and 2nd bits are flagged.)

	srand(time(NULL));
	SkiMap test = SkiMap_new("TEstMtn", "basic.vdata", "basic.edata");
	Vertex src = (Vertex)(List_getItem(test->startPoints, 0)->data);
	SkiMap_bellmanFord(test, src, userP);
	SkiMap_checkBFResults(test);
	SkiMap_free(test);
	return;
}

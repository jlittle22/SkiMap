#include "SkiMap.h"
#include "MinHeap.h"
#include "SmallFloat.h"

char* run(uint8_t userP, char* edata, char* vdata);

int main(){//////////////
	uint8_t userP = 5; // <- Edit me! User preferences are a byte. 
///////////////////////// Example: 00000101 is GREEN and BLACKS (0th and 2nd bits are flagged.)

	srand(time(NULL));
	SkiMap test = SkiMap_new("TEstMtn", "basic.vdata", "basic.edata");
	Vertex src = (Vertex)(List_getItem(test->startPoints, 0)->data);
	SkiMap_bellmanFord(test, src, userP);
	char* path = SkiMap_stringifyPath(SkiMap_checkBFResults(test));
	fprintf(stderr, "FINAL: %s\n", path);
	free(path);
	SkiMap_free(test);
	return 0;
}

char* run(uint8_t userP, char* edata, char* vdata){//////////////
	//uint8_t userP = 5; // <- Edit me! User preferences are a byte. 
///////////////////////// Example: 00000101 is GREEN and BLACKS (0th and 2nd bits are flagged.)
	srand(time(NULL));
	SkiMap test = SkiMap_new("TEstMtn", "basic.vdata", "basic.edata");
	Vertex src = (Vertex)(List_getItem(test->startPoints, 0)->data);
	SkiMap_bellmanFord(test, src, userP);
	char* path = SkiMap_stringifyPath(SkiMap_checkBFResults(test));
	char* ptr = path;
	char c = (*ptr);
	int count = 0;
	while (c != '\0'){
		count++;
		ptr++;
		fprintf(stderr, "Char: %c\n", c);
		c = (*ptr);
	}
	char local[count+1];
	for(int i = 0; i < count; i++){
		local[i] = path[i];
	}
	local[count] = '\0';
	fprintf(stderr, "LOCAL: %s\n", local);
	SkiMap_free(test);
	return path;
}

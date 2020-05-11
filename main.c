#include "SkiMap.h"
#include "MinHeap.h"
#include "SmallFloat.h"

char* run(uint8_t userP, char* edata, char* vdata);

int main(){//////////////
	uint8_t userP = 5; // <- Edit me! User preferences are a byte. 
///////////////////////// Example: 00000101 is GREEN and BLACKS (0th and 2nd bits are flagged.)

	//srand(time(NULL));
	//SkiMap test = SkiMap_new("TEstMtn", "basic.vdata", "basic.edata");
	//Vertex src = (Vertex)(List_getItem(test->startPoints, 0)->data);
	//SkiMap_bellmanFord(test, src, userP);
	//char* path = SkiMap_stringifyPath(SkiMap_checkBFResults(test));
	//fprintf(stderr, "FINAL: %s\n", path);
	//free(path);
	//SkiMap_free(test);
	run(userP, "Lift top1 CharLift 7\nlift2 top1 TheQuad 7\ntop1 inter1 TrueGrit 3 6\ninter1 Lift ValleyRun 0 5\ninter1 Lift Stillness 1\ntop1 inter2 WhiteCaps 1\ninter2 lift2 TheChute 2\ninter2 inter3 Tecumseh 1\ninter2 inter3 Sels 2\ninter3 inter4 JakesTrail 0\ninter4 lift2 Periphery 1, 3, 5\n\0", "Lift 1\nlift2 1\ntop1 0\ninter1 2\ninter2 2\ninter3 2\ninter4 2\n\0");
	return 0;
}

char* run(uint8_t userP, char* edata, char* vdata){//////////////
	//uint8_t userP = 5; // <- Edit me! User preferences are a byte. 
///////////////////////// Example: 00000101 is GREEN and BLACKS (0th and 2nd bits are flagged.)
	srand(time(NULL));
	SkiMap test = SkiMap_new("TEstMtn", vdata, edata);
	Vertex src = (Vertex)(List_getItem(test->startPoints, 0)->data);
	SkiMap_bellmanFord(test, src, userP);
	char* path = SkiMap_stringifyPath(SkiMap_checkBFResults(test));
	char* ptr = path;
	char c = (*ptr);
	int count = 0;
	while (c != '\0'){
		count++;
		ptr++;
		c = (*ptr);
	}
	char local[count+1];
	for(int i = 0; i < count; i++){
		local[i] = path[i];
	}
	local[count] = '\0';
	(void)local;
	SkiMap_free(test);
	return path;
}

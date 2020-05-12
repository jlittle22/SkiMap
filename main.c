#include "SkiMap.h"
#include "MinHeap.h"
#include "SmallFloat.h"

char* run(uint8_t userP, char* edata, char* vdata);

int main(){//////////////
	uint8_t userP; // <- Edit me! User preferences are a byte. 
///////////////////////// Example: 00000101 is GREEN and BLACKS (0th and 2nd bits are flagged.)
	for (unsigned i = 0; i < 256; i++){
		userP = i;
		fprintf(stderr, "Path %u: ", i);
		char * path = run(userP, "V9 B1 Abort 2\nT1 V1 Dogs 1\nT1 V2 Cats 2\nT1 V3 Mice 0\nV1 V6 The_Bird 1\nV1 V7 Big_Rock 0\nV2 V7 Lil_Rock 2\nV2 V3 Braden 0\nV3 V8 Bumpy 0 6\nV6 B1 Park_Me 1 4\nV6 V9 Juice 0\nV7 V8 One_Way 1\nV8 V9 Too_Bumpy 2 6\nV8 B2 Park_Town 0 4\nV8 V10 Homeward 1\nV9 B1 Big_Yikes 3\nV10 B2 Bumpy_Tree 1 5\nT2 V3 Easy_Drop 0\nT2 V4 Sunday_Blue 1\nT2 V5 Tree_Slam 3 5\nV4 V8 Ehhhh 2\nV4 V5 Skurrt 1\nV5 V10 Tree_City 2 5\nB2 T2 Right_Side 7\nB1 T1 Left_Side 7\n", "T1 0\nT2 0\nB1 1\nB2 1\nV1 2\nV2 2\nV3 2\nV4 2\nV5 2 \nV6 2\nV7 2 \nV8 2\nV9 2\nV10 2\n\0");
		free(path);
	};
	return 0;
}

char* run(uint8_t userP, char* edata, char* vdata){
	char* path;
	srand(time(NULL));
	SkiMap test = SkiMap_new("Waterville", vdata, edata);
	if (userP == 128 || userP == 255){
		path = SkiMap_randomPathDown(test);
	}
	else{
		Vertex src = (Vertex)(List_getItem(test->startPoints, 0)->data);
		SkiMap_bellmanFord(test, src, userP);
		path = SkiMap_stringifyPath(SkiMap_checkBFResults(test));
	}
	SkiMap_free(test);
	fprintf(stderr, "%s\n", path);
	return path;
}

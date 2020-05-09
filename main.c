#include "SkiMap.h"
#include "MinHeap.h"
#include "SmallFloat.h"

void path(Vertex start){
	if (start == NULL){
		return;
	}
	Vertex_setDiscovered(start, true);
	printf("Vertex: %s\n", start->vertexName);
	bool gotOne = false;
	Vertex recurseHere;
	int i = 0;
	int numEdges = Vertex_numEdges(start);
	while (!gotOne && i < numEdges){
		Edge curr = Vertex_getEdge(start,i);
		if(!Vertex_isDiscovered(curr->destination)){
			gotOne = true;
			recurseHere = curr->destination;
			char string[] = "Yes";
			char string2[] = "No";
			if (Edge_is(curr, PARK)){
				printf("Trail: %s Is PARK? %s\n", curr->edgeName, string);
			}
			else {
				printf("Trail: %s Is PARK? %s\n", curr->edgeName, string2);
			}
			break;
		}
		i++;
	}
	if(i != numEdges){
		path(recurseHere);
	}
	Vertex_setDiscovered(start,false);
}


int main(){
	Convert input;
	float ttest3 = 1.0;
	fprintf(stderr, "Weird Hex: %x\n", (uint32_t)ttest3);
	input.value = 1.0;

	fprintf(stderr, "Original Hex  : %x\n", input.bits);
	fprintf(stderr, "Original Float: %f\n", input.value);
	SmallFloat floa = SmallFloat_FtoSF(input.value);
	float result = SmallFloat_SFtoF(floa);
	fprintf(stderr, "Result Float  : %f\n", result);
	srand(time(NULL));
	SkiMap test = SkiMap_new("TEstMtn", "basic.vdata", "basic.edata");

	List_print(test->allVertices->list);
	uint8_t userP = 1;
	Vertex src = (Vertex)(List_getItem(test->startPoints, 0)->data);
/////////////////
	Vertex_testFloats(src);
/////////////////

	SkiMap_bellmanFord(test, src, userP);
	SkiMap_checkBFResults(test);
	/*MinHeap heap = MinHeap_new();
	int count = 0;
	while (count < 100){
		Vertex test1 = Vertex_new("Top", 0);
		Vertex_setDistance(test1, (100 - count));
		MinHeap_insert(heap, test1);
		count++;
	}
	fprintf(stderr, "Cap: %u NumElems: %u\n", heap->capacity, heap->numElems);
	for(int i = 0; i < 100; i++){
		fprintf(stderr, "TOP Val: %u\n", Vertex_getDistance(MinHeap_extractTop(heap)));
	}
    MinHeap_free(heap);*/
	SkiMap_free(test);

	// int size = List_numItems(test->allVertices);
	// for(int i = 0; i < size; i++){
	// 	SkiMap_randomPathDown(test);
	// 	Vertex curr = (Vertex)(List_getItem(test->allVertices, i)->data);
	// 	fprintf(stderr, "%s\n", curr->vertexName);
	// 	int size1 = List_numItems(curr->edges);
	// 	for (int j = 0; j < size1; j++){
	// 		Edge curr1 = (Edge)(List_getItem(curr->edges, j)->data);
	// 		fprintf(stderr, "		%s\n		", curr1->edgeName);
	// 		for (int k = 0; k < 8; k++){
	// 			if(Edge_is(curr1, k)){
	// 				fprintf(stderr, "%d ", k);
	// 			}
	// 		}
	// 		fprintf(stderr, "\n");
	// 	}
	// }

	return 0;
}

/*
int main(){
	Vertex test1 = Vertex_new("Top", 0);
	Vertex test2 = Vertex_new("InterA", 2);
	Vertex test3 = Vertex_new("InterB", 2);
	Vertex test4 = Vertex_new("InterC", 2);
	Vertex test5 = Vertex_new("InterD", 2);
	Vertex test6 = Vertex_new("InterE", 2);
	Vertex test7 = Vertex_new("InterF", 2);
	Vertex test8 = Vertex_new("Bottom", 1);

	uint8_t flags[] = {0, 4};
	uint8_t flags2[] = {1};
	int size = sizeof(flags)/sizeof(uint8_t);
	fprintf(stderr, "SIZE: %d\n", size);
	Edge testA = Edge_new("Trail1", flags, size,  test2);
	Edge testB = Edge_new("Trail2", flags2, 1, test3);
	Edge testC = Edge_new("Trail3", flags2, 1, test4);
	Edge testE = Edge_new("Trail4", flags2, 1, test6);
	Edge testD = Edge_new("Trail5", flags2, 1, test5);
	Edge testF = Edge_new("Trail6", flags, size, test7);
	Edge testG = Edge_new("LiftUp", flags, size, test1);
	Edge testH = Edge_new("Trail7", flags2, 1, test8);
	Edge testI = Edge_new("Trail8", flags, size, test8);
	Edge testJ = Edge_new("Trail9", flags2, 1, test8);
	
    Vertex_addEdge(test1, testA);
    Vertex_addEdge(test1, testB);
    Vertex_addEdge(test1, testC);

    Vertex_addEdge(test2, testE);
    Vertex_addEdge(test3, testD);
    Vertex_addEdge(test4, testF);

    Vertex_addEdge(test5, testH);
    Vertex_addEdge(test6, testI);
    Vertex_addEdge(test7, testJ);

    Vertex_addEdge(test8, testG);
    
    path(test1);

	Vertex_free(test1);
	Vertex_free(test2);
	Vertex_free(test3);
	Vertex_free(test4);
	Vertex_free(test5);
	Vertex_free(test6);
	Vertex_free(test7);
	Vertex_free(test8);

	return 0;
}
*/



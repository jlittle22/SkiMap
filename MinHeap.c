#include "MinHeap.h"

static void expand(MinHeap obj);
static void swap(Vertex* arr, unsigned i, unsigned j);
static void upHeapify(Vertex* arr, unsigned index);
static void downHeapify(Vertex* arr, unsigned size, unsigned index);

MinHeap MinHeap_new(){
	MinHeap new = (MinHeap)malloc(HEAP_STRUCT_SIZE);
	nullCheck("ERROR:: at MinHeap_new. Malloc failed for MinHeap ptr.", new);
	new->dataArray = (Vertex*)malloc(sizeof(Vertex) * INIT_CAPACITY);
	nullCheck("ERROR:: at MinHeap_new. Malloc failed for dataArray ptr.", new->dataArray);
	new->numElems = 0;
	new->capacity = INIT_CAPACITY;
	return new;
}

void MinHeap_free(MinHeap obj){
	nullCheck("ERROR:: at MinHeap_free. Object is NULL.", obj);
	nullCheck("ERROR:: at MinHeap_insert. Object array is NULL.", obj->dataArray);
	free(obj->dataArray);
	free(obj);
}

void MinHeap_insert(MinHeap obj, Vertex insertMe){
	nullCheck("ERROR:: at MinHeap_insert. Object is NULL.", obj);
	nullCheck("ERROR:: at MinHeap_insert. Attempting to insert NULL element.", insertMe);
	if(obj->numElems == obj->capacity){
		expand(obj);
	}
	obj->dataArray[obj->numElems] = insertMe;
	obj->numElems = obj->numElems + 1;
	upHeapify(obj->dataArray, obj->numElems-1);
}

static void expand(MinHeap obj){
	nullCheck("ERROR:: at expand. Obj is NULL.", obj);
	unsigned newCap = 2 * obj->capacity;
	Vertex* newArr = (Vertex*)malloc(sizeof(Vertex) * newCap);
	nullCheck("ERROR:: at expand. Malloc failed.", newArr);
	for (unsigned i = 0; i < obj->capacity; i++){
		newArr[i] = obj->dataArray[i];
	}
	obj->capacity = newCap;
	Vertex* temp = obj->dataArray;
	obj->dataArray = newArr;
	free(temp);
}

static void upHeapify(Vertex* arr, unsigned index){
	nullCheck("ERROR:: at upHeapify. Array is NULL.", arr);
	int parent = ((int)index - 1)/2;
	if (parent >= 0){
		if (Vertex_getDistance(arr[parent]) > Vertex_getDistance(arr[index])){
			swap(arr, parent, index);
			upHeapify(arr, parent);
		}
	}
}

static void downHeapify(Vertex* arr, unsigned size, unsigned index){
	nullCheck("ERROR:: at downHeapify. Arr is NULL.", arr);	
	unsigned root = index;
	unsigned leftChild = (2*index)+1;
	unsigned rightChild = (2*index)+2;
	if (leftChild < size && Vertex_getDistance(arr[leftChild]) < Vertex_getDistance(arr[root])){
		root = leftChild;		
	}

	if(rightChild < size && Vertex_getDistance(arr[rightChild]) < Vertex_getDistance(arr[root])){
		root = rightChild;
	}

	if(root != index){
		swap(arr, index, root);
		downHeapify(arr, size, root);
	}
}


static void swap(Vertex* arr, unsigned i, unsigned j){
	nullCheck("ERROR:: at swap. Array is NULL", arr);
	Vertex temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

Vertex MinHeap_extractTop(MinHeap obj){
	nullCheck("ERROR:: at MinHeap_extractTop. Object is NULL.", obj);
	swap(obj->dataArray, 0, obj->numElems-1);
	Vertex item = obj->dataArray[obj->numElems-1];
	obj->numElems = obj->numElems-1;
	downHeapify(obj->dataArray, obj->numElems, 0);
	return item;
}


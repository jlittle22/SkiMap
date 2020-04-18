#include "LinkedList.h"
#include "Vertex.h"

//ERROR HANDLING
static void indexRange(char error[], List obj, int index);

LinkedList LinkedList_new(){
	LinkedList new = (LinkedList)malloc(LINKED_SIZE);
	nullCheck("ERROR: at Malloc in LinkedList_new()", new);
	new->front = NULL;
	return new;
}

void LinkedList_free(LinkedList list){
	assert(list);
	Node* current = list->front; 
	Node* temp = NULL;
	while (current != NULL){
		temp = current->next; 
		free(current);
		current = temp; 
	}
}

void List_insert(List obj, void* newData){
	assert(newData);
	assert(obj);
	Node* afterInserted = obj->list->front;
	Node * new = (Node*)malloc(sizeof(Node));
	nullCheck("ERROR: at Malloc in List_insert()", new);
	new->data = newData;
	new->next = afterInserted;
	obj->list->front = new;
	obj->numElems++;
}

void List_print(LinkedList list){
	assert(list);
	Node * current = list->front;
	while(current != NULL){
		Vertex toBePrint = (Vertex)current->data;
		printf("List Element: %s\n", toBePrint->vertexName);
		current = current->next;
	}
}

List List_new(){
	List new = (List)malloc(LIST_SIZE);
	nullCheck("ERROR: at Malloc in List_new()", new);	
	new->list = (LinkedList)LinkedList_new();
	return new;
}

void List_free(List removeMe){
	assert(removeMe);
	LinkedList_free(removeMe->list);
	free(removeMe->list);
	free(removeMe);
}

Node* List_getItem(List obj, int index){
	indexRange("ERROR: at List_getItem :: index out of range",obj, index);
	Node* curr = obj->list->front; 
	int count = 0;
	while (count < index && curr != NULL){
    	curr = curr->next; 
    	count++;
	}
	nullCheck("ERROR: at List_getItem :: result is NULL.", curr);
	return curr;

}

int List_numItems(List obj){
	return obj->numElems;
}


static void indexRange(char error[], List obj, int index){
	if (index >= obj->numElems || index < 0){
		fprintf(stderr, "%s: %d.\n", error, index);
		exit(1);
	}
}


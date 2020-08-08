#include "LinkedList.h"
#include "Vertex.h"

static void indexRange(char error[], List obj, int index);
static void LinkedList_free(LinkedList list);
static LinkedList LinkedList_new();

/* Create a new LinkedList object */
static LinkedList LinkedList_new(){
	LinkedList new = (LinkedList)malloc(LINKED_SIZE);
	nullCheck("ERROR: at Malloc in LinkedList_new()", new);
	new->front = NULL;
	return new;
}

/* Free a LinkedList object */
static void LinkedList_free(LinkedList list){
	assert(list);
	Node* current = list->front; 
	Node* temp = NULL;
	while (current != NULL){
		temp = current->next; 
		if(current->data != NULL){
			free(current->data);
		}
		free(current);
		current = temp; 
	}
}

/* Free the List obj, but not the contents of the LinkedList */
void List_partialFree(List obj){
	assert(obj);
	LinkedList objList = obj->list;
	assert(objList);
	Node* current = objList->front; 
	Node* temp = NULL;
	while (current != NULL){
		temp = current->next; 
		free(current);
		current = temp; 
	}
	free(objList);
	free(obj);
}

/* Insert an object into a List object */
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

/* TESTING PURPOSES ONLY: Print the contents of a List (assume it stores vertices) */
void List_print(LinkedList list){
	assert(list);
	Node * current = list->front;
	while(current != NULL){
		Vertex toBePrint = (Vertex)current->data;
		printf("List Element: %s\n", toBePrint->vertexName);
		current = current->next;
	}
}

/* Create a new List object */
List List_new(){
	List new = (List)malloc(LIST_SIZE);
	nullCheck("ERROR: at Malloc in List_new()", new);	
	new->list = (LinkedList)LinkedList_new();
	new->numElems = 0;
	return new;
}

/* Free a List object */
void List_free(List removeMe){
	assert(removeMe);
	assert(removeMe);
	LinkedList_free(removeMe->list);
	free(removeMe->list);
	free(removeMe);
}

/* Retrieve the index'th Node from a List object */
Node* List_getItem(List obj, int index){
	assert(obj);
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

/* Retrieves the number of items in a List obj */
int List_numItems(List obj){
	assert(obj);
	return obj->numElems;
}

/* Ensure the given index less than the number of elems in the List obj */
static void indexRange(char error[], List obj, int index){
	assert(obj);
	if (index >= obj->numElems || index < 0){
		fprintf(stderr, "%s: %d.\n", error, index);
		exit(1);
	}
}

/* Reverse the nodes of a List obj by inserting them into another List obj and returning it */
List List_reverseList(List obj){
	int numItems = List_numItems(obj);
	List reversed = List_new();
	for (int i = 0; i < numItems; i++){
		List_insert(reversed, List_getItem(obj,i)->data);
	}
	List_partialFree(obj);
	return reversed;
}

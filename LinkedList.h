//     What is this module?     //
//------------------------------//
// This a List interface.       //
// It's polymorphic so you can  //
// store whatever you want!     //  
// Cool.                        //
//////////////////////////////////

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>
#include "Errors.h"


typedef struct Node Node; 

typedef struct Node {
	void * data; 
	Node * next; 
} Node;

struct LinkedList {
    Node * front;
};

typedef struct LinkedList* LinkedList; 

struct LinkedListClass {
	LinkedList list;
	int numElems; 
};

typedef struct LinkedListClass* List; 

#define LINKED_SIZE sizeof(struct LinkedList)
#define LIST_SIZE sizeof(struct LinkedListClass)

/* Frees a List objected but NOT its contents */
void List_partialFree(List list);

/* Frees a List object */
List List_new();

/* Insert an element into a List */
void List_insert(List list, void* data);

/* Print a List - FOR TESTING PURPOSES ONLY */
void List_print(LinkedList);

/* Completely frees a List object*/
void List_free(List removeMe);

/* Retrieves an indexed Node of a List */
Node* List_getItem(List, int);

/* Gets the number of items in a List */
int List_numItems(List);

/* Returns a new List with elements in reverse orders. Frees memory from old list */
List List_reverseList(List obj);

#endif




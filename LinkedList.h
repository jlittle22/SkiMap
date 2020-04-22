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

typedef struct Node{
	void * data; 
	Node * next; 
} Node;

struct LinkedList{
    Node * front;
};

typedef struct LinkedList* LinkedList; 

struct LinkedListClass{
	LinkedList list;
	int numElems; 
};

typedef struct LinkedListClass* List; 

#define LINKED_SIZE sizeof(struct LinkedList)
#define LIST_SIZE sizeof(struct LinkedListClass)


LinkedList LinkedList_new();
void LinkedList_free(LinkedList list);
void List_partialFree(List list);
List List_new();
void List_insert(List list, void* data);
void List_print(LinkedList);
void List_free(List removeMe);
Node* List_getItem(List, int);
int List_numItems(List);


#endif




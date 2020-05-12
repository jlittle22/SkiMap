#include "Path.h"

Path Path_new(){
	Path new = (Path)malloc(PATH_STRUCT);
	nullCheck("ERROR:: at Path_new. Failed to malloc new Path.", new);
	new->string = (char*)malloc(INIT_SIZE * sizeof(char));
	nullCheck("ERROR:: at Path_new. Failed to malloc String.", new->string);
	new->string[0] = '\0';
	new->capacity = INIT_SIZE;
	new->numElems = 1;
	new->score = 16.0;
	return new;
}

void Path_free(Path obj){
	nullCheck("ERROR:: at Path_free. Obj is NULL.", obj);
	nullCheck("ERROR:: at Path_free. Obj String is NULL.", obj->string);
	free(obj->string);
	free(obj);
}

static void expand(Path obj){
	char* newString = malloc(sizeof(char) * obj->capacity * 2);
	for (int i = 0; i < obj->numElems; i++){
		newString[i] = obj->string[i];
	}
	obj->capacity *= 2;
	free(obj->string);
	obj->string = newString;
}

static void insertChar(Path obj, char new){
	if (obj->numElems == obj->capacity){
		expand(obj);
	}
	obj->string[obj->numElems] = new;
	obj->numElems += 1;
}

void Path_insert(Path obj, char* newPart, char delim){
	nullCheck("ERROR:: at Path_insert. Obj is NULL.", obj);
	nullCheck("ERROR:: at Path_insert. newPart is NULL.", newPart);
	char curr = newPart[0];
	char* ptr = newPart;
	obj->string[obj->numElems-1] = delim;
	while(curr!= '\0'){
		insertChar(obj, curr);
		ptr++;
		curr = (*ptr);
	}
	insertChar(obj, '\0');
}
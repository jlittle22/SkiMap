#include "Errors.h"

void nullCheck(char error[], void* ptr){
	if (ptr == NULL){
		fprintf(stderr, "%s\n", error);
		exit(1);
	}
}

void checkRange(char error[], unsigned index, unsigned max){
	if (index > max){
		fprintf(stderr, "%s\n", error);
		exit(1);
	}
}
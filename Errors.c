#include "Errors.h"

void nullCheck(char error[], void* ptr){
	if (ptr == NULL){
		fprintf(stderr, "%s\n", error);
		exit(1);
	}
}



#include "Errors.h"

void nullCheck(char error[], void* ptr){
	if (ptr == NULL){
		fprintf(stderr, "%s\a\n", error);
		exit(1);
	}
}

void checkRange(char error[], unsigned index, unsigned max){
	if (index > max){
		fprintf(stderr, "%s\a\n", error);
		exit(1);
	}
}

void checkSignedRange(char error[], int index, int max, int min){
	if ((index > max) || (index < min)){
		fprintf(stderr, "%s\a\n", error);
		exit(1);
	}
}
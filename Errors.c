#include "Errors.h"

/* Check if ptr is NULL. If so, print the error message and exit the program. */
void nullCheck(char error[], void* ptr){
	if (ptr == NULL){
		fprintf(stderr, "%s\a\n", error);
		exit(1);
	}
}

/* Check if index is outside the range [0, max]. If true, print the error and exit the program */
void checkRange(char error[], unsigned index, unsigned max){
	if (index > max){
		fprintf(stderr, "%s\a\n", error);
		exit(1);
	}
}

/* Check if index is in the range [min, max]. If not, print the error and exit the program. */
void checkSignedRange(char error[], int index, int max, int min){
	if ((index > max) || (index < min)){
		fprintf(stderr, "%s\a\n", error);
		exit(1);
	}
}

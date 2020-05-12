#ifndef ERRORS_H
#define ERRORS_H

#include <stdlib.h>
#include <stdio.h>

/* Reports an error to stderr and quits the program if ptr is NULL. */
void nullCheck(char error[], void* ptr);

/* Reports an error to stderr and quits the program if index is larger than max */
void checkRange(char error[], unsigned index, unsigned max);

/* Reports and error to stderr and quits the program if index is out of range [min, max] */
void checkSignedRange(char error[], int index, int max, int min);

#endif

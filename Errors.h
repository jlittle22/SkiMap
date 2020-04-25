//     What is this module?     //
//------------------------------//
// Basically nothing. Just here //
// in case we wanna make some   //
// custom error handling stuff  //
//////////////////////////////////
#ifndef ERRORS_H
#define ERRORS_H

#include <stdlib.h>
#include <stdio.h>

void nullCheck(char error[], void* ptr);
void checkRange(char error[], unsigned index, unsigned max);

#endif

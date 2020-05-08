#ifndef SMALLFLOAT_H
#define SMALLFLOAT_H

#include <math.h>
#include <stdbool.h>
#include <inttypes.h>

#include "Errors.h"
// _ _ _ | _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
//29 bit number
//score will be a value from zero to 8 (in this case number of edge characteristics)
//score can NEVER be negative 
//3 is highest possible exponent. 
//3 is bias. 
//Exponent has 3 bits
//
#define EXP_BITS 3 
#define BIAS ((2<<(EXP_BITS-1))-1)
#define EXP_LSB 26
#define MANTISSA_BITS 26

/* Bitpacking Definitions */
#define STD_EXP_LSB 23
#define STD_SIGN 32
#define STD_BIAS 127
#define ONE_AT(n) (((uint32_t)0x1) << n)

struct SmallFloat{
	uint32_t data; 
};
#define FLOAT_SIZE sizeof(struct SmallFloat)

union Convert{
	uint32_t bits;
	float value;
};

typedef union Convert Convert;
typedef struct SmallFloat* SmallFloat; 

SmallFloat SmallFloat_new();
void SmallFloat_free(SmallFloat obj);

//Here for testing purposes
uint8_t getExp(float input);



#endif

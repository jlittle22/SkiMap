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
#define SF_BITS 28
#define EXP_BITS 3 
#define BIAS ((1<<(EXP_BITS-1))-1)
#define EXP_LSB (SF_BITS - EXP_BITS)
#define MANTISSA_MSB (EXP_LSB - 1)
#define MANTISSA_WIDTH (MANTISSA_MSB+1)
/* Bitpacking Definitions */
//0 1------1 101--------------------   11.101  0.0008654  9.3453453453454
#define STD_SIZE 32
#define STD_EXP_LSB 23
#define STD_MANT_WIDTH 23
#define STD_SIGN 32
#define STD_BIAS 127
#define ONE_AT(n) (((uint32_t)0x1) << n)

struct SmallFloat{
	uint32_t data; 
};

#define FLOAT_SIZE sizeof(struct SmallFloat)
typedef struct SmallFloat* SmallFloat; 

union Convert{
	uint32_t bits;
	float value;
};

typedef union Convert Convert;

//Member functions
void SmallFloat_free(SmallFloat obj);
float SmallFloat_SFDatatoF(uint32_t SFData);
SmallFloat SmallFloat_FtoSF(float input);
float SmallFloat_SFtoF(SmallFloat obj);
uint32_t SmallFloat_getData(SmallFloat obj);




#endif

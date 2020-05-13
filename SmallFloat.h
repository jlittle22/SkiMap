#ifndef SMALLFLOAT_H
#define SMALLFLOAT_H

#include "Errors.h"
#include <math.h>
#include <stdbool.h>
#include <inttypes.h>

#define SF_BITS 28
#define EXP_BITS 3 
#define BIAS ((1<<(EXP_BITS-1))-1)
#define EXP_LSB (SF_BITS - EXP_BITS)
#define MANTISSA_MSB (EXP_LSB - 1)
#define MANTISSA_WIDTH (MANTISSA_MSB+1)

/* Bitpacking Definitions */
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

/* Converts a std::float to a SmallFloat */
SmallFloat SmallFloat_FtoSF(float input);

/* Converts a SmallFloat to a std::float */
float SmallFloat_SFtoF(SmallFloat obj);

/* Gets the bit field from a SmallFloat object */
uint32_t SmallFloat_getData(SmallFloat obj);

/* Converts a bit field to a std::float */
float SmallFloat_SFDatatoF(uint32_t SFData);

/* Frees a SmallFloat object */
void SmallFloat_free(SmallFloat obj);


#endif

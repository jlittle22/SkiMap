#include "SmallFloat.h"

SmallFloat SmallFloat_new(){
	SmallFloat new = (SmallFloat) malloc(FLOAT_SIZE);
	nullCheck("ERROR:: at SmallFloat_new. Malloc failed.", new);
	return new;
}

void SmallFloat_free(SmallFloat obj){
	nullCheck("ERROR:: at SmallFloat_free. Object is NULL.", obj);
	free(obj);
}

uint8_t getExp(float in){

	Convert input;
	input.value = in;
	//shift 23
	//clear 9th bit
	//done!
	fprintf(stderr, "OG: %f\n", input.value);
	uint32_t temp = (input.bits >> STD_EXP_LSB);
	fprintf(stderr, "Temp: %u\n", temp);
	uint32_t mask = (ONE_AT((STD_SIGN - STD_EXP_LSB)) - 1);
	fprintf(stderr, "Mask: %u\n", mask);
	temp = temp & mask;
	fprintf(stderr, "Added: %u\n", temp);
	return ((uint8_t)temp - STD_BIAS);
}
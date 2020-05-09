#include "SmallFloat.h"

static int8_t getFloatExp(uint32_t input);
static uint32_t getFloatMantissa(uint32_t input); 
static uint32_t getSFMantissa(uint32_t input);
static int8_t getSFExp(uint32_t input); 
static void setSmallMant(SmallFloat obj, uint32_t mant);
static void setSmallExp(SmallFloat obj, int8_t exp); 
static float setFloatExp(uint32_t input, int8_t exp); 
static float setFloatMantissa(uint32_t input, uint32_t mantissa);
static SmallFloat SmallFloat_new();

static SmallFloat SmallFloat_new(){
	SmallFloat new = (SmallFloat) malloc(FLOAT_SIZE);
	nullCheck("ERROR:: at SmallFloat_new. Malloc failed.", new);
	new->data = (uint32_t)0x0;
	return new;
}

void SmallFloat_free(SmallFloat obj){
	nullCheck("ERROR:: at SmallFloat_free. Object is NULL.", obj);
	free(obj);
}

float SmallFloat_SFDatatoF(uint32_t SFData){
	SmallFloat decompress = SmallFloat_new();
	decompress->data = SFData;
	float value = SmallFloat_SFtoF(decompress);
	return value;
}

SmallFloat SmallFloat_FtoSF(float input){
	SmallFloat new = SmallFloat_new();
	Convert out;
	out.value = input;
	uint8_t exponent = getFloatExp(out.bits);
	uint32_t mant = getFloatMantissa(out.bits);
	setSmallExp(new, exponent);
	setSmallMant(new, mant);
	return new;
}

float SmallFloat_SFtoF(SmallFloat obj){
	nullCheck("ERROR:: at SmallFloat_SFtoF. Obj is NULL.", obj);
	uint32_t mant = getSFMantissa(obj->data);
	int8_t exp = getSFExp(obj->data);
	float value = 0;
	value = setFloatExp(value, exp);
	value = setFloatMantissa(value, mant);
	Convert toFloat;
	toFloat.bits = value;
	SmallFloat_free(obj);
	return toFloat.value;
}

uint32_t SmallFloat_getData(SmallFloat obj){
	nullCheck("ERROR:: at SmallFloat_getData. Obj is NULL.", obj);
	return obj->data;
}

static void setSmallExp(SmallFloat obj, int8_t exp){
	nullCheck("ERROR:: at setSmallExp. Obj is NULL.", obj);
	if (exp != 4){
		checkSignedRange("ERROR:: at setSmallExp. Exp is out of range.", exp, BIAS, (-1*BIAS));
	}
	exp = exp + BIAS;
	uint32_t mask = (uint32_t)exp; 
	mask = mask << EXP_LSB;
	obj->data = obj->data | mask;
}

static void setSmallMant(SmallFloat obj, uint32_t mant){
	uint8_t shift = MANTISSA_MSB - STD_EXP_LSB + 1;
	uint32_t mask = mant << shift;
	obj->data = obj->data | mask;
}

static int8_t getFloatExp(uint32_t input){
	if ((int32_t)input == 0){
		return 0;
	}
	uint32_t temp = (input >> STD_EXP_LSB);
	uint32_t mask = (ONE_AT((STD_SIGN - STD_EXP_LSB)) - 1);
	temp = temp & mask;
	return ((int8_t)temp - STD_BIAS);
}

static uint32_t getFloatMantissa(uint32_t input){
	uint32_t shift = (STD_SIZE - STD_MANT_WIDTH);
	uint32_t temp = input << shift;
	temp = temp >> shift;
	return temp;
}

static uint32_t getSFMantissa(uint32_t input){
	uint32_t mask = (ONE_AT((MANTISSA_MSB+1)) - 1);
	mask = mask & input;
	mask = mask >> ((MANTISSA_WIDTH)-(STD_MANT_WIDTH));
	return mask;
}

static int8_t getSFExp(uint32_t input){
	uint32_t mask = (ONE_AT(EXP_BITS)-1);
	mask = mask << EXP_LSB;
	mask = mask & input;
	mask = mask >> EXP_LSB;
	int8_t done = (int8_t)mask;
	done -= BIAS;
	return done;
}

static float setFloatExp(uint32_t input, int8_t exp){
	checkSignedRange("ERROR:: at setFloatExp. Exp is outside range.", exp, STD_BIAS, (-1*STD_BIAS));
   	uint32_t newExp = (uint32_t)exp;
	newExp = newExp + STD_BIAS;
	uint32_t mask = newExp << STD_EXP_LSB;
	input = mask | input;
	return input;
}

static float setFloatMantissa(uint32_t input, uint32_t mantissa){
	input = input | mantissa;
	return input;
}
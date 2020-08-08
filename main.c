#include "SkiMap.h"

char* run(uint8_t userP, char* edata, char* vdata);

/* main() for is TESTING only! */
int main() {//////////////
	uint8_t userP = 32; // <- Edit me! User preferences are a byte. 
///////////////////////// Example: 00000101 is GREEN and BLACKS (0th and 2nd bits are flagged.)
	//for (unsigned i = 0; i < 256; i++) {
		//userP = i;
		char * path = run(userP, "V9 B1 Abort 2\nT1 V1 Dogs 1\nT1 V2 Cats 2\nT1 V3 Mice 0\nV1 V6 The_Bird 1\nV1 V7 Big_Rock 0\nV2 V7 Lil_Rock 2\nV2 V3 Braden 0\nV3 V8 Bumpy 0 6\nV6 B1 Park_Me 1 4\nV6 V9 Juice 0\nV7 V8 One_Way 1\nV8 V9 Too_Bumpy 2 6\nV8 B2 Park_Town 0 4\nV8 V10 Homeward 1\nV9 B1 Big_Yikes 3\nV10 B2 Bumpy_Tree 1 5\nT2 V3 Easy_Drop 0\nT2 V4 Sunday_Blue 1\nT2 V5 Tree_Slam 3 5\nV4 V8 Ehhhh 2\nV4 V5 Skurrt 1\nV5 V10 Tree_City 2 5\nB2 T2 Right_Side 7\nB1 T1 Left_Side 7\n", "T1 0\nT2 0\nB1 1\nB2 1\nV1 2\nV2 2\nV3 2\nV4 2\nV5 2 \nV6 2\nV7 2 \nV8 2\nV9 2\nV10 2\n\0");
		fprintf(stderr, "%s\n", path);
		for (int i = -30; i < 200; i++) {
		SmallFloat test = SmallFloat_FtoSF((float)i);
		float out = SmallFloat_SFtoF(test);
		union {
			float in;
			uint32_t bits;
		} convert = { .in = out }; 
		fprintf(stderr, "Output: %x\n", convert.bits);
		}
		free(path);
}

/* run() is the actual driver that the JNI entry point calls.
   run() takes a bit-packed byte of user preferences as well as
   two strings representing the edge data and vertex data 
   following the format specified in the README file. */
char* run(uint8_t userP, char* edata, char* vdata) {
	char* path;
	srand(time(NULL));
	SkiMap mtn = SkiMap_new("JakesMtn", vdata, edata); // make new SkiMap and init.
    path = SkiMap_processInput(mtn, userP); // compute path 
	SkiMap_free(mtn); // free memory 
	return path; // (!) NOTE: path points to heap memory that must be freed in the JNI entry.
}

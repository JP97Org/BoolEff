/*
 ============================================================================
 Name        : EffBool.c
 Author      : Jonathan Schenkenberger
 Version     : 1.0
 Copyright   : MIT License (see LICENSE)
 Description : EffBool
 ============================================================================
 */

#include "BoolEff.h"

#define SOME_IMPORTANT_BOOL (15)

int main(void) {
	//puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */

	sizeBoolEffArr_t size = 32;
	boolEff_t *boolEff = getBoolEff(size);

	for(indexBoolEffArr_t i = 0 ; i < size ; i++) {
		setBool(boolEff, i, i % 2);
		printf("%d , ", getBool(boolEff, i));
	}
	printf("\n\n");

	boolEffIter_t iter = iterator(boolEff);
	while(hasNext(&iter)) {
		int _next = next(&iter);
		printf("%d , ", _next);
	}

	printf("\n\n%d\n", getBool(boolEff,SOME_IMPORTANT_BOOL));

	deleteBoolEff(boolEff);
	return EXIT_SUCCESS;
}

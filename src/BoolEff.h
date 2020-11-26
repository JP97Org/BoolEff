#ifndef BOOL_EFF_H
#define BOOL_EFF_H

/*
 ============================================================================
 Name        : BoolEff.h
 Author      : Jonathan Schenkenberger
 Version     : 1.0
 Copyright   : MIT License (see LICENSE)
 Description : EffBool
 ============================================================================

 Header defining space-efficient booleans
 (only use when you want to use more than 28 booleans!)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
 * DEBUG output toggle
 */
int DEBUG = 1;

typedef struct ___bools {
	uint8_t b0 : 1;
	uint8_t b1 : 1;
	uint8_t b2 : 1;
	uint8_t b3 : 1;
	uint8_t b4 : 1;
	uint8_t b5 : 1;
	uint8_t b6 : 1;
	uint8_t b7 : 1;
} __bools;

/*
 * size-type for the bool-eff-array (uint32_t). Use it for size-values.
 */
typedef uint32_t sizeBoolEffArr_t;

/*
 * size-type for the bool-eff-array (uint32_t). Use it for index-values.
 */
typedef sizeBoolEffArr_t indexBoolEffArr_t;

/*should be space-efficient when size > 28 and for normal bools 1byte is used!*/
/*
 * the boolEff_t struct which can be gotten with the getBoolEff function.
 */
typedef struct __boolEff {
	__bools *bools;
	sizeBoolEffArr_t size;
} boolEff_t;

/*
 * Allocates a new boolEff array with the given size (in bool-bits) on the heap.
 * All elements of the array are undefined.
 * After all usages of the array, it should be freed using the delteBoolEff method.
 */
boolEff_t* getBoolEff(sizeBoolEffArr_t size) {
	boolEff_t* ret = (boolEff_t*) (malloc(sizeof(boolEff_t)));

	if(ret != NULL) {
		ret->size = size;
		sizeBoolEffArr_t arrMod = size % 8;
		sizeBoolEffArr_t arrDiv = size / 8;
		sizeBoolEffArr_t arrSize = arrMod == 0 ? (arrDiv) : (arrDiv + 1);
		ret->bools = (__bools*) ( malloc ( arrSize * sizeof(__bools) ) );
	}

	if(DEBUG) {
		printf("SIZE_OF_8BOOLS_BLOCK:%lu\n", sizeof(__bools));
		printf("SIZE_OF_boolEff_t_struct:%lu\n", sizeof(boolEff_t));
		printf("SIZE_OF_returned_ptr:%lu\n", sizeof(boolEff_t*));
		uint32_t sizeAll = ((size / 8) + 1)*sizeof(__bools)
				+ sizeof(boolEff_t)
				+ sizeof(boolEff_t*);
		double sizeAllDivided = ((double)sizeAll) / (double)(size);
		printf("SIZE_per_BOOL_overall_ca.:%lf\n", sizeAllDivided);
	}

	return ret;
}

/*
 * frees the given boolEff struct and all allocated resources associated with it.
 */
int deleteBoolEff(boolEff_t* boolEff) {
	free(boolEff->bools);
	free(boolEff);
	return 0;
}

/*
 * Gets the bool at the given index. Returns -1 on any error.
 */
int getBool(boolEff_t* boolEff, indexBoolEffArr_t index) {
	if(boolEff == NULL) return -1;
	int ret = -1;

	sizeBoolEffArr_t size = boolEff->size;

	if(index < size) {
		indexBoolEffArr_t indexMod = index % 8;
		indexBoolEffArr_t indexDiv = index / 8;

		__bools bools = boolEff->bools[indexDiv];
		switch(indexMod) {
		case 0 : ret = bools.b0; break;
		case 1 : ret = bools.b1; break;
		case 2 : ret = bools.b2; break;
		case 3 : ret = bools.b3; break;
		case 4 : ret = bools.b4; break;
		case 5 : ret = bools.b5; break;
		case 6 : ret = bools.b6; break;
		case 7 : ret = bools.b7; break;
		default : ret = -1; break;
		}
	}

	return ret;
}

int _toBool(int bool) {
	return bool == 0 ? 0 : 1;
}

/*
 * Sets the bool at the given index to the given value. Returns -1 on any error.
 */
int setBool(boolEff_t* boolEff, indexBoolEffArr_t index, int bool) {
	if(boolEff == NULL) return -1;
	int ret = -1;

	sizeBoolEffArr_t size = boolEff->size;

	if(index < size) {
		indexBoolEffArr_t indexMod = index % 8;
		indexBoolEffArr_t indexDiv = index / 8;

		__bools* bools = boolEff->bools + indexDiv;
		int boolNormalized = _toBool(bool);
		switch(indexMod) {
		case 0 : bools->b0 = boolNormalized; break;
		case 1 : bools->b1 = boolNormalized; break;
		case 2 : bools->b2 = boolNormalized; break;
		case 3 : bools->b3 = boolNormalized; break;
		case 4 : bools->b4 = boolNormalized; break;
		case 5 : bools->b5 = boolNormalized; break;
		case 6 : bools->b6 = boolNormalized; break;
		case 7 : bools->b7 = boolNormalized; break;
		default : ret = -1; break;
		}

		ret = 0;
	}

	return ret;
}

//only const iterator!!!!
typedef struct __iterator {
	boolEff_t *boolEff;
	indexBoolEffArr_t index;
} boolEffIter_t;

/*
 * Gets a fresh const iterator over the given boolEff array.
 */
boolEffIter_t iterator(boolEff_t *boolEff) {
	boolEffIter_t ret;

	ret.boolEff = boolEff;
	ret.index = 0;

	return ret;
}

/*
 * iterator's hasNext function. Returns -1 on any error.
 */
int hasNext(boolEffIter_t* iter) {
	if(iter == NULL) return -1;
	if(iter->boolEff == NULL) return -1;

	return iter->index < iter->boolEff->size;
}

/*
 * iterator's next function. Returns -1 on any error.
 */
int next(boolEffIter_t* iter) {
	if(iter == NULL) return -1;
	if(iter->boolEff == NULL) return -1;

	int index = iter->index;
	int ret = getBool(iter->boolEff, index);
	iter->index = index + 1;

	return ret;
}


#endif

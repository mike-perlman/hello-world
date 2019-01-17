/*
 * permMissingElem.c
 *
 *  Created on: Oct 27, 2018
 *      Author: foobar
 */
#include <stdlib.h>
#include <string.h>
#include "permMissingElem.h"

/**
 * Find the missing element.
 * A[] - array of distinct ints.
 * range - max of [1..range] found in A[]. 1..100,000.
 * A[] is of size range-1.
 */
int findMissingElement(int A[], int range) {
	if (range > MAX_RANGE || range < 0) return -1;
	int len = range-1;
    int out = 0;

    char *buf = malloc(sizeof(char)*range);
    strncpy(buf,"",range);

    for (int x = 0; x < len; x++){
    	if (A[x] > range) continue;
    	buf[A[x]-1] = '.';
    }
    out = strlen(buf)+1;
    printf("contents=[%s]\n",buf);

    return out;

}

/*
 * distinctInts.c
 *
 *  Created on: Nov 7, 2018
 *      Author: foobar
 */
#include <stdlib.h>
#include <string.h>
#include "../util/myUtil.h"
int compareInts(const void *x, const void *y) {
	if (*((int *)x) < *((int*)y))
		return -1;
	else if (*((int *)x) > *((int*)y))
		return 1;
	return 0;
}

int distinctInts(int A[], int N){
	if (N <= 0) return -1;
	int buf[N];
	int x;
	for (x = 1; x < N; x++) { buf[x] = A[x];}
	qsort(buf, N, sizeof(int), compareInts );

	printf("Interim sorted array: [");
	print_array(buf,sizeof(buf)/sizeof(int),',');
	printf("]\n");

	int out = 1;
    for (x = 1; x < N; x++){
    	if (buf[x] != buf[x-1]) out++;
    }
    return out;
}



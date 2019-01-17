/*
 * tapeEquilibrium.c
 *
 *  Created on: Oct 27, 2018
 *      Author: foobar
 */
#include "tapeEquilibrium.h"
#include <math.h>

/**
 * Find the first balance point, where sum of A[0..(x-1)] is closest to sum of A[x..n-1]
 * A[] - a non-empty array, elements in range (-1000..1000)  -> muliple balance points may exist.
 * N - number of elements in A[]
 */
int findEquilibrium(int A[], int N) {
	if (N < MIN_ARR_LEN || N > MAX_ARR_LEN) return -1;
	int running_total = 0;
	int *totals = malloc(sizeof(int) * N);
    printf("Array: ");
	for (int i = 0; i < N; i++) {
		running_total += A[i];
		totals[i] = running_total;
		printf("%d ",A[i]);
	}
	int target = running_total / 2;
	printf("\nTotal: %d,  Equilibrium: %d\n",running_total, target);

	int out = 0;
	int least_diff = ABS(target);

	for (int i = 0; i< N; i++) {
		int diff = ABS(totals[i] - target);
		printf("running tot: %d, diff: %d\n",totals[i], diff);
		if ( diff < least_diff) {
			out = i;
			least_diff = diff;
		}
	}
	printf("Found least difference at element %d. diff=%d\n", out, least_diff);
}

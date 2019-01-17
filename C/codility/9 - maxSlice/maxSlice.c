/*
 * maxSlice.c
 *
 *  Created on: Nov 12, 2018
 *      Author: foobar
 */
#include "maxSlice.h"

int findMaximumSliceSum(int A[], int N) {
	int max_ending = 0;
	int max_slice = 0;
	for (int i = 0; i < N; i++) {
		max_ending = MAX(0, max_ending + A[i]);
		max_slice = MAX(max_slice, max_ending);
	}
	return max_slice;
}

int findMaximumSliceProfit(int A[], int N) {
	int max_ending = A[0];
	int max_slice = 0;
	for (int i = 0; i < N; i++) {
		max_ending = MAX(0, A[i] - max_ending);
		max_slice = MAX(max_slice, max_ending);
	}
	return max_slice;
}

/*
 * maxDoubleSliceSum.c
 *
 *  Created on: Nov 12, 2018
 *      Author: foobar
 */

#include "maxDoubleSliceSum.h"
#include "../util/myUtil.h"

static int doubleSlice(int A[], int N, int x, int y, int z);

/**
 * Test a slice, sum of A[X+1], a[y-1], A[Y+1], a[y+2], A[Z-1]
 */
static int doubleSlice(int A[], int N, int x, int y, int z) {
  if (x < 0 || x >= y  || y >= z || z >= N) return 0;

  return (A[x+1] + A[x+2] + A[y-1] + A[y+1] + A[y+2] + A[z-1]);
}

int findMaxDoubleSlice_1(int A[], int N) {
	int out = 0;
	int current = 0;
	for(int i = 0; i < N-2; i++) {
		for (int j = i+1; j < N-1; j++) {
			for (int k = j+1; k < N; k++) {
				current = doubleSlice(A,N,i,j,k);
				if (current > out) {
					int targets[] = {i+1,i+2, j-1,j+1,j+2,k-1};
					printf("New high: %d:  (%d,%d,%d) -> ",current,i,j,k);
					print_elements(A,',',targets,INTSIZE(targets));
					out = current;
				}
			}
		}
	}
	return out;
}

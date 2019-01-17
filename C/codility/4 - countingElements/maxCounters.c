/*
 * maxCounters.c
 *
 *  Created on: Oct 28, 2018
 *      Author: foobar
 */
#include <stdlib.h>
#include <string.h>
#include "maxCounters.h"
/**
 * For each element in A[], increment that counter.  If the element is N+1, set all counters
 * to the highest value.
 * N - number of counters.
 * A[] - array of counter commands. [1..N+1]
 * M - length of A[].
 */
_COUNTER_RESULTS incrementCounters(int N, int A[], int M){
    if (N <=0 || N >MAX_COUNTERS) {
    	N = 1;
    	M = 0;
    }
    int max_counter_val = N+1;
    int high_counter = 0;
	int target = 0;

	_COUNTER_RESULTS out;
	out.C = malloc(sizeof(int)*N);
	out.L = N;
	set_all(out.C,N,0);
	for (int x = 0; x <M; x++) {
		if(A[x]>max_counter_val || A[x]<=0) continue;		//validate element
		if(A[x] == max_counter_val) {                       //set all
			printf("****setting all counters to %d\n",high_counter);
			set_all(out.C,N,high_counter);
		}
		else {                                              //increment counter, test for new highval.
			target = A[x]-1;
			printf("++counter %d\n",target);
			out.C[target] += 1;
			if (out.C[target] > high_counter) high_counter = out.C[target];
		}
	}
	return out;
}

/**
 * set all ints in [target] to [val], up to [len].
 */
void set_all(int *target, int len, int val) {
	for (int y = 0; y<len; y++) target[y] = val;
}

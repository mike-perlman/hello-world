/*
 * prefixSum.c
 *
 *  Created on: Nov 7, 2018
 *      Author: foobar
 */
/**
 * return a * to int array, size N, containing running totals L->R.
 */
int * prefixes(int A[], int N){
	int * out = malloc(sizeof(int)*N);
	out[0] = A[0];
	for (int x = 1; x < N; x++) {
		out[x] = out[x-1]+A[x];
	}
	return out;
}

/**
 * return a * to int array, size N, containing running totals R->L.
 */
int * suffixes(int A[], int N){
	int * out = malloc(sizeof(int)*N);
	out[N-1] = A[N-1];
	for (int x = N-2; x >= 0; x--) {
		out[x] = out[x+1]+A[x];
	}
	return out;

}

float * moving_average(int A[], int N, int window) {
	float * out = malloc(sizeof(float)*N);

	if (window >N) {
		return out;
	}
	float running_total = 0.0;
	for (int x = 0; x < window-1; x++ ){
		out[x] = 0;
		running_total+= A[x];
	}
	out[window-1] = running_total / window;

	for (int x = window; x<N; x++) {
		running_total -= A[x-window];
		running_total += A[x];
		out[x] = running_total / window;
	}

	return out;
}

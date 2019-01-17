#include <stdlib.h>
#include "missingInt.h"

/**
 * traverse array, find lowest positive int not in array.
 * return 1 if no positives found.
 */
int findMissingPositive(int A[], int N) {
	int out = -1;
	int lowest = MAX_INT;

	if (N <= 1 || N > MAX_INT) return out;

	char * foo = malloc(sizeof(char)*MAX_INT);
	strncpy(foo,"",MAX_INT);

	for (int x = 0; x<N; x++) {
		if (A[x] > 0 && A[x]<=MAX_INT) {
			foo[A[x]-1]='.';
		}
	}
	return strlen(foo)+1;
}

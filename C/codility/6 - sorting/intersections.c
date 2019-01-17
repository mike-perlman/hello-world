/*
 * intersections.c
 *
 *  Created on: Nov 8, 2018
 *      Author: foobar
 */
#include "intersections.h"

#define MIN(x,y)  (x <= y? x : y)
#define MAX(x,y)  (x >= y? x : y)
#define FROM(c,r) (c-r)
#define TO(c,r)   (c+r)

int compareDiscs(const void * a, const void * b) {
  if ((*(_DISC *)a).radius < (*(_DISC *)b).radius)
	  return -1;
  if ((*(_DISC *)a).radius > (*(_DISC *)b).radius)
	  return 1;
  return 0;
}

/**
 * min/max test of window overlap. return 1 if 2 discs overlap.
 */
static int hasOverlap(int A[], int source, int target) {
	//printf("testing[%d-%d] vs [%d-%d]\n",FROM(source,A[source]),TO(source,A[source]), FROM(target,A[target]), TO(target,A[target]));
	if (FROM(source,A[source]) < TO(target, A[target]) && TO(source,A[source]) > FROM(target,A[target]))
		return 1;
	return 0;
}



int countOverlaps(int A[], int N) {
	_DISC discs[N];
	int out = 0;
	for (int x = 0; x < N; x++) {
		discs[x].center = x;
		discs[x].radius = A[x] > 0? A[x] : 0;					//guard vs. negative radius
		discs[x].from = discs[x].center - discs[x].radius;
		discs[x].to = discs[x].center + discs[x].radius;
	}
	qsort(discs,N,sizeof(_DISC),compareDiscs);

	_DISC current;
	for (int i = N-1; i >= 0; i--) {
		current = discs[i];
		int left_coverage = current.center - MAX(current.center - current.radius,0);
		int right_coverage  = MIN(current.center + current.radius, N-1) - current.center;
		int disc_intersections = left_coverage + right_coverage;
        printf("disc %d: radius=%d, span=[%d,%d], left = [%d], right = [%d], intersections =s [%d]\n", current.center, current.radius, current.from,current.to, left_coverage, right_coverage, disc_intersections);
        out += disc_intersections;
        if (out > MAX_DISC_INTERSECTIONS) return -1;
	}
	return out/2;
}

int countOverlapsWithoutSort(int A[], int N) {
	int out = 0;
	for (int i = 0; i < N; i ++) {
		if (A[i] == 0) {
			printf("disc %d: zero-radius\n",i);
			continue;
		}
		int left_coverage = i -  MAX(i - A[i],0);
		int right_coverage = MIN(i + A[i],N-1) - i;
		int disc_intersections = left_coverage + right_coverage;
        printf("disc %d: radius=%d, span=[%d,%d], left = [%d], right = [%d], intersections =s [%d]\n", i, A[i], i-A[i],i+A[i], left_coverage, right_coverage, disc_intersections);
        out += disc_intersections;
        if (out > MAX_DISC_INTERSECTIONS) return -1;
	}
    return out/2;
}

/**
 * for each element, look forward (min radius|N) to test for overlaps.
 */
int countOverlapsByTest(int A[], int N) {
	int out = 0;
	for (int i = 0; i < N; i ++) {
		if (A[i] == 0) {
			printf("disc %d: zero-radius\n",i);
			continue;
		}
		for (int j =i+1; j < N; j++) {
			if (j == i) continue;
			if (hasOverlap(A,i,j)){
				printf("overlap found:%d(%d)..%d(%d)\n", i, A[i], j, A[j]);
				out++;
			}
		}
	}
	return out;
}

/*
 * intersections.h
 *
 *  Created on: Nov 8, 2018
 *      Author: foobar
 */

#ifndef SORTING_INTERSECTIONS_H_
#define SORTING_INTERSECTIONS_H_

#define MAX_DISC_ARRAY_LEN  				100000
#define MAX_DISC_RADIUS 				0xFFFFFFFF
#define MAX_DISC_INTERSECTIONS      	  10000000

typedef struct DISC {
	int center;
	int radius;
	int from;
	int to;
} _DISC;

int countOverlaps (int A[], int N);
int countOverlapsWithoutSort(int A[], int N);
int countOverlapsByTest(int A[], int N) ;

#endif /* SORTING_INTERSECTIONS_H_ */

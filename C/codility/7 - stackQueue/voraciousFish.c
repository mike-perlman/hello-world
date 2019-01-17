/*
 * voraciousFish.c
 *
 *  Created on: Nov 14, 2018
 *      Author: salience
 */
#include <stdlib.h>
#include <stdio.h>
#include "../util/myUtil.h"
#include "voraciousFish.h"

/**
 * Determine which fish will survive given :
 *  sizes[] contains distinct values.  Larger numbers will "eat" smaller ones.
 *  directions[] contains UPSTREAM or DOWNSTREAM values.  Invalid values will be eaten!
 *  overlapping (bidirectional) queues.
 *
 */
int survivingFish(int sizes[], int directions[], int N) {
	int out = 0;
	int upstreamFishQty = 0;
	int downstreamFishQty = 0;
	int upstreamers[MAX_FISH];
	int downstreamers[MAX_FISH];
	int eaten = 0;
	int survived = 0;
	_FISH river[N];

	for (int i = 0; i < N; i++) {
		river[i].dir = directions[i];
		river[i].size = sizes[i];
	}

	if (downstreamFishQty == 0 || upstreamFishQty == 0) return N;		//check unidirectional

	for (int i = 0; i < downstreamFishQty; i++ ){
		int chomped = 0;
		int j = 0;
	  for (; j < upstreamFishQty && sizes[upstreamers[j]] < sizes[downstreamers[i]];j++) {
		  chomped++;
	  }
	  if (j < upstreamFishQty) {		//downstreamFish got eaten
		  chomped ++;
	  }
	}

}

_FISHTURN * takeTurn(_FISH *remaining, int len) {
	int safeLow = 0;
	int safeHigh = len-1;
	_FISHTURN out;
	out.qtyRemaining = len;
	out.survived = 0;
	out.remaining = malloc(sizeof(_FISH) * len);

	for (int i = 0; i < len; i++) {
		if (remaining[i].dir == UPSTREAM) {
			if (i == safeLow) {
				out.survived++;
				safeLow++;
				continue;
			}
		}
		else {			//DOWNSTREAM
			if (i == safeHigh) {
				out.survived++;
				continue;
			}
		}
	}

}

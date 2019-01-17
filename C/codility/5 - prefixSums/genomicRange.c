/*
 * genomicRange.c
 *
 *  Created on: Oct 29, 2018
 *      Author: foobar
 */

/**
 * find minimal impact, from sequence[start..end], by translation: A=1, C=2, G=3, T=4
 * returns -1 if start >= end
 *
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../util/myUtil.h"
#include "genomicRange.h"

static int findMinImpact(char *sequence, int start, int end) {
	if (start > end) return ERR_BAD_SEQUENCE;

	char min = 'Z';
	for (int x = start; x <= end; x++) {
		switch (sequence[x]) {
		case 'A':
			return 1;
		case 'C':
			min = sequence[x];
			continue;
		case 'G': case 'T':
			if (sequence[x] < min) min = sequence[x];
			continue;
		default:
			continue;
		}
	}

	switch (min) {
	case 'C': return 2;
	case 'G': return 3;
	case 'T': return 4;
	}

	 return ERR_BAD_SEQUENCE;
}


_GENOMIC_RANGE_RESULTS findMinImpactFactor(char *sequence, int startOffsets[], int endOffsets[], int qtySequences) {
	_GENOMIC_RANGE_RESULTS out;
	out.A = malloc(sizeof(int)*qtySequences);
	out.M = qtySequences;
    printf("testing sequence [%s]\n",sequence);
    char * subseq;
	for (int x = 0; x<qtySequences; x++) {
	   out.A[x] = findMinImpact(sequence,startOffsets[x],endOffsets[x]);
	   subseq = substr(sequence,startOffsets[x],endOffsets[x]);
	   printf("min impact:[%d-%d],[%s]=%d\n",startOffsets[x],endOffsets[x], subseq, out.A[x]);
	   free(subseq);
	}
	return out;
}



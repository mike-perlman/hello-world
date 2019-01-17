/*
 * genomicRange.h
 *
 *  Created on: Oct 29, 2018
 *      Author: foobar
 */

#ifndef PREFIXSUMS_GENOMICRANGE_H_
#define PREFIXSUMS_GENOMICRANGE_H_

#define MAX_NUCLEOTIDES 100000
#define MAX_SEQUENCES 50000

#define ERR_BAD_SEQUENCE 99999

typedef struct genomeResults {
  int * A;
  int M; // Length of the array
} _GENOMIC_RANGE_RESULTS;

_GENOMIC_RANGE_RESULTS findMinImpactFactor(char *sequence, int startOffsets[], int endOffsets[], int qtySequences);

#endif /* PREFIXSUMS_GENOMICRANGE_H_ */

/*
 * maxCounters.h
 *
 *  Created on: Oct 28, 2018
 *      Author: foobar
 */

#ifndef COUNTINGELEMENTS_MAXCOUNTERS_H_
#define COUNTINGELEMENTS_MAXCOUNTERS_H_
#define MAX_COUNTERS 100000

typedef struct Counter_Results {
  int * C;
  int L; // Length of the array
} _COUNTER_RESULTS;

_COUNTER_RESULTS incrementCounters(int N, int A[], int M);

#endif /* COUNTINGELEMENTS_MAXCOUNTERS_H_ */

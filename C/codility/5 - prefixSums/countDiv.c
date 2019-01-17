/*
 * countDiv.c
 *
 *  Created on: Nov 7, 2018
 *      Author: foobar
 */
#include "countDiv.h"

int countDivisors(int A, int B, int K) {
	if (A>B) return -1;
	if(A < MIN_COUNTDIV_RANGE || A > MAX_COUNTDIV_RANGE) return -2;
	if(B < MIN_COUNTDIV_RANGE || A > MAX_COUNTDIV_RANGE) return -3;
	if(K < MIN_COUNTDIV_DIVISOR || A > MAX_COUNTDIV_DIVISOR) return -4;

	int lowMod = A % K;
	int hiMod = B % K;
	int firstMultiple = (A + lowMod);
	int lastMultiple = (B - lowMod);
	if (firstMultiple > lastMultiple) return 0;
	return ((lastMultiple - firstMultiple) / K)+1;
}

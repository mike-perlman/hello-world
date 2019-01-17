/*
 * driver.c
 *
 *  Created on: Oct 26, 2018
 *      Author: foobar
 */
#include "util/myUtil.h"
#include "iterations/iterations.h"
#include "arrays/cyclicRotation.h"
#include "timeComplexity/frogJump.h"
#include "timeComplexity/permMissingElem.h"
#include "timeComplexity/tapeEquilibrium.h"
#include "countingElements/missingInt.h"
#include "countingElements/maxCounters.h"
#include "prefixSums/genomicRange.h"
#include "prefixSums/countDiv.h"
#include "sorting/distinctInts.h"
#include "sorting/intersections.h"
#include "stackQueue/brackets.h"
#include "maxSlice/maxSlice.h"
#include "maxSlice/maxDoubleSliceSum.h"
#include "maxSlice/profit.h"

void driveCountDiv(int A, int B, int K) {
    printf("%d multiples of %d between [%d..%d]\n", countDivisors(A,B,K),K,A,B);
}

int main (int argc, char *argv[]) {
    printf("*****Iterations/binaryGap*****\n");
	printf("argc:[%d].\targv[0]:[%s]\n",argc,argv[0]);
	int x = argc > 1 ? atol(argv[1]) : 9;
	int gap = binaryGap(x);
	printf("input: %d. MaxGap: %d\n", x,gap);

    printf("\n*****Arrays/cyclicRotation*****\n");
    int ex2[] = {4,5,2,3,6,7};
    _Results r = rotateArray(ex2,sizeof(ex2)/sizeof(int),23);
     printf("Before: %d %d %d %d %d %d\n", ex2[0], ex2[1], ex2[2], ex2[3], ex2[4], ex2[5]);
     printf("After: %d %d %d %d %d %d\n", r.A[0], r.A[1], r.A[2], r.A[3], r.A[4], r.A[5]);

     printf("\n*****timeComplex/frogJump*****\n");
     num_jumps(13450,4958203,200);

     printf("\n*****timeComplex/missingElement*****\n");
     int ex3[] = {12,4,9,7,1,10,8,11,3,2,6};
     int len = sizeof(ex3)/sizeof(int);
     printf("input length=%d\n",len);
     int missing = findMissingElement(ex3,len+1);
     printf("missing number=%d\n",5);

     printf("\n*****timeComplex/tapeEquilibrium*****\n");
     int ex4[] = {12,43,903,-75,124,10,812,-110, 3,-3, -1, 2,6};
     int balance_point = findEquilibrium(ex4,sizeof(ex4)/sizeof(int));

     printf("\n*****countingElements/MissingInteger*****\n");
     printf("lowest pos int missing from ex4=[%d]",findMissingPositive(ex4,sizeof(ex4)/sizeof(int)));
     int ex5[] = {12,43,1,903,-75,124,4,10,812,7,-110, 3,8,-3, -1, 2,6};
     printf("lowest pos int missing from ex4=[%d]",findMissingPositive(ex5,sizeof(ex5)/sizeof(int)));

     printf("\n*****countingElements/maxCounters*****\n");
     int ex6[] = {1,2,3,4,5,1,1,6,3};   //should result in [3,3,4,3,3]
     int counters = 5;
     _COUNTER_RESULTS ctr_res = incrementCounters(counters, ex6, sizeof(ex6)/sizeof(int));
     printf("Results: [");
     print_array(ctr_res.C, ctr_res.L, ' ');
     printf("]");

     printf("\n*****prefixSums/genomicRange*****\n");
     char *seq = "GTTCGTCGCTCGTGTCGTCTTAC";   //23-len
     int P[] = {0,2,3,4,5,6, 7, 7, 8,2,14};
     int Q[] = {1,5,6,7,8,9, 9, 7,11,6,22};

    _GENOMIC_RANGE_RESULTS gen_res = findMinImpactFactor(seq,P,Q,sizeof(P)/sizeof(int));
    printf("min Impact: [%d]\n", gen_res.M);

     printf("\n*****prefixSums/countDiv*****\n");
     driveCountDiv(10,100,5);
     driveCountDiv(45,1300000,8);
     driveCountDiv(4,40,1);
     driveCountDiv(7,15,2);

     printf("\n*****sorting/distinctInt*****\n");
     int unsorted[] = {91,5,-20,100000,49185,820491,2,594,-3,10000,-2,1,5,91,594};
     int distinct = distinctInts(unsorted, sizeof(unsorted)/sizeof(int));
     printf("[%d] distinct ints in array:", distinct);
     print_array(unsorted,sizeof(unsorted)/sizeof(int),',');
     printf("\n");

     printf("\n*****sorting/discIntersections*****\n");
     int discs[] = {1,5,2,1,4,0};
     int overlaps = 0;
/*     int overlaps = countOverlaps(discs, sizeof(discs)/sizeof(int));
     printf("%d discs, %d overlaps counted in total.\n", sizeof(discs)/sizeof(int), overlaps);
     printf("\n*****sorting/discIntersections (noSort)*****\n");
*/
     overlaps = countOverlapsByTest(discs, sizeof(discs)/sizeof(int));
     printf("%d discs, %d overlaps counted in total.\n", sizeof(discs)/sizeof(int), overlaps);

     printf("\n*****stacks/brackets*****\n");
     _BRACKET bracketPairs[] = {{'(',')'}, {'[',']'}, {'{','}'}};
     _BRACKET parenPairs[] = {{'(',')'}};

     char *testBrackets[] = { "[](){}[({})]", "[](){}[({{)]"};
     for (int i = 0; i < sizeof(testBrackets)/sizeof(char *); i++) {
    	 if (validateBracketsExtensible(testBrackets[i], bracketPairs, sizeof(bracketPairs)/sizeof(_BRACKET)))
    		 printf("\t- Valid bracket\n");
    	 else
    		 printf("\t- INVALID bracket\n");
     }

     char *testParens[] = {"()()((()))(()()()())","()()()(()()"};
     for (int i = 0; i < sizeof(testParens)/sizeof(char *); i++) {
    	 if (validateBracketsExtensible(testParens[i], parenPairs, sizeof(parenPairs)/sizeof(_BRACKET)))
    		 printf("\t- Valid Parens\n");
    	 else
    		 printf("\t- INVALID Parens\n");
     }

     printf("************maxSlice/baseTest**********\n");
     int sliceTest [] = {5,-7,3,5,-2,4,-1};
     int maxSlice = findMaximumSliceSum(sliceTest, sizeof(sliceTest)/sizeof(int));
     printf("slicetest: max-slice = [%d]\n", maxSlice);

     printf("************maxSlice/maxDoubleSlice**********\n");
     int doubleSliceTest [] = {3,2,6,-1,4,5,-1,2};
     printf("Testing: "); print_array(doubleSliceTest, INTSIZE(doubleSliceTest), ',');
     int max2xSlice = findMaxDoubleSlice_1(doubleSliceTest,INTSIZE(doubleSliceTest));
     printf("slicetest: max-double-slice = [%d]\n", max2xSlice);

     printf("************maxSlice/profit**********\n");
     int prices[] = {23171,21011,21123,21366,21013,21367};
     int maxProfit = findMaxProfit(prices, INTSIZE(prices));
     printf("profit: max profit = [%d]\n",maxProfit);

}

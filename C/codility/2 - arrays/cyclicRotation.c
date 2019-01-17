#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cyclicRotation.h"

/**
 * Note: arrays degrade to pointers when passed as f-params.  length is required.
 */
struct Results rotateArray(int A[], int len, int K) {
	_Results out;
	 out.N = len > 0 ? len : 0;
	 out.A = len > 0 ? malloc(len * sizeof(int)) : malloc(sizeof(int));   //failover to 1-len array

	 //////////////////////////////////////
	 if (K <= 0 || K > MAX_ROTATION || len <= 0)
    	 return out;
	 int rotations = 0;
	 int net_shift = 0;
	 int rel_shift = 0;

	 if (K < len) {
		rotations = 0;
		net_shift = K;
		rel_shift = len - K;
	 }
	 else if (K > len){
		 rotations = len / K;
		 net_shift = K % len;
		 rel_shift = len - (net_shift);
	 }
	 else {
		 rotations = net_shift = rel_shift = 0;
	 }

	 printf("size=%d, k=%d, shift = %d, relative shift =%d\n",out.N, K, net_shift, rel_shift);

	 if (rel_shift > 0) {
    	 int s = 0;
    	 int *buf = malloc(sizeof(int) * rel_shift);
    	 while(s < rel_shift) {       //read into buffer
    		 buf[s] = A[s];
    		 s++;
    	 }

    	 int t = 0;
    	 while(s < out.N) {     //copy remaining input to new offsets
    		 out.A[t] = A[s];
    		 t++;s++;
    	 }

    	 s=0;
    	 while (s < rel_shift)    //copy buffer to output
    	 {
            out.A[t++] = buf[s++];
    	 }
     }
	 else {
        for (int x = 0; x < len; x++)
        	out.A[x] = A[x];
	 }
     return out;
}

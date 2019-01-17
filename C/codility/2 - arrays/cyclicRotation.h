/*
 * cyclicRotation.h
 *
 *  Created on: Oct 26, 2018
 *      Author: foobar
 */

#ifndef ARRAYS_CYCLICROTATION_H_
#define ARRAYS_CYCLICROTATION_H_

#define MAX_ROTATION 100

typedef struct Results {
  int *A;
  int N; // Length of the array
} _Results;

struct Results rotateArray(int A[], int len, int K);



#endif /* ARRAYS_CYCLICROTATION_H_ */


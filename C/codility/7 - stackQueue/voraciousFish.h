/*
 * voraciousFish.h
 *
 *  Created on: Nov 14, 2018
 *      Author: salience
 */

#ifndef STACKQUEUE_VORACIOUSFISH_H_
#define STACKQUEUE_VORACIOUSFISH_H_

#define MAX_FISH		100000
#define MAX_FISH_SIZE 1000000000
enum FishDirection {UPSTREAM = 0,DOWNSTREAM = 1 };
int survivingFish(int sizes[], int directions[], int N);

typedef struct FISH {
	int size;
	enum FishDirection dir;
} _FISH;

typedef struct FISHTURN {
	int survived;
	_FISH *remaining;
	int qtyRemaining;
} _FISHTURN;

#endif /* STACKQUEUE_VORACIOUSFISH_H_ */

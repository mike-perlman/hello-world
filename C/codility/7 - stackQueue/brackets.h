/*
 * brackets.h
 *
 *  Created on: Nov 9, 2018
 *      Author: foobar
 */

#ifndef STACKQUEUE_BRACKETS_H_
#define STACKQUEUE_BRACKETS_H_

#define MAX_BRACKETS_LEN 		200000
#define DEFAULT_STACK_VAL 		'x'

typedef struct BRACKET {
	char open;
	char close;
} _BRACKET;

#define VALID_PAIRS 3

int validateBrackets(char *S);
int validateBracketsExtensible(char *S, _BRACKET *validPairs, int len);
#endif /* STACKQUEUE_BRACKETS_H_ */

/*
 * brackets.c
 *
 *  Created on: Nov 9, 2018
 *      Author: foobar
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "brackets.h"

_BRACKET validBrackets[] = {{'(',')'}, {'[',']'}, {'{','}'}};
int len = sizeof(validBrackets)/sizeof(_BRACKET);

int debugMatches = 0;
int debugMismatches= 1;

static char lookupClose(_BRACKET brackets[], int size, char c) {
	int i;
	for (i = 0; i < size; i++) {
		if (brackets[i].open == c)
			return brackets[i].close;
	}
	return 0;
}

static char lookupOpen(_BRACKET brackets[], int size, char c) {
	int i;
	for (i = 0; i < size; i++) {
		if (brackets[i].close == c)
			return brackets[i].open;
	}
	return 0;
}

int validateBrackets(char *S){

	char * b = malloc(sizeof(char)*MAX_BRACKETS_LEN/2);
	memset(b,DEFAULT_STACK_VAL,MAX_BRACKETS_LEN/2);

	char * ptr = b;						//leave [0] blank.
	printf("...Evaluating [%s]\n",S);
	int i;
	for (i = 0; i < strlen(S); i++) {
		//printf("buf=%s\n",b);
		switch (S[i]) {
		case '(':
		case '[':
		case '{':
			*(++ptr) = S[i];			//push + advance ptr
			break;
		case ')':
		case ']':
		case '}':
			if (*ptr == lookupOpen(validBrackets,len,S[i])) {
				*ptr-- = DEFAULT_STACK_VAL;//pop if matching open, fail otherwise
				if (debugMatches) printf("matching open found for %c at position [%d]\n", S[i], i);
			}
			else {
				if (debugMismatches) printf("mismatch found at position [%d]\n", i);
				return 0;
			}
			break;
		default:
			printf("invalid character [%c] found at %d - \n",S[i],i);
			return 0;
		}
	}
	return 1;
}

/**
 * validate string vs pairs defined in [validPairs].
 * len - length of validPairs Array.
 *
 */
int validateBracketsExtensible(char *S, _BRACKET *validPairs, int len) {
	char * b = malloc(sizeof(char)*MAX_BRACKETS_LEN/2);
	memset(b,DEFAULT_STACK_VAL,MAX_BRACKETS_LEN/2);

	char * ptr = b;						//leave [0] blank.
	printf("...Evaluating [%s]\n",S);
	int i;
	for (i = 0; i < strlen(S); i++) {
		if (lookupClose(validPairs, len, S[i])) {		//push if char has matching close.
			*(++ptr) = S[i];
		}
		else if (*ptr == lookupOpen(validPairs,len, S[i])) {				//pop if matching open is found.
			*ptr-- = DEFAULT_STACK_VAL;
			if (debugMatches) printf("matching open found for %c at position [%d]\n", S[i], i);
		}
		else {
			if (debugMismatches) printf("mismatch found at position [%d]\n", i);
			return 0;
		}
	}
	// pointer should be at home after all that...
	if(ptr == b)
		return 1;
	return 0;
}

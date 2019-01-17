/*
 * myUtil.c
 *
 *  Created on: Oct 29, 2018
 *      Author: foobar
 */
#include <string.h>

char * substr(char * str, int start, int end) {
	if (strlen(str) < end) end = strlen(str);
	if (start > end) return "";
	int len = end-start +2;
	char * out = malloc(sizeof(char)*len);
	for (int s = start, t = 0; s <= end; s++,t++){
		out[t] = str[s];
	}
	out[len-1] = '\0';
	return out;
}

void print_array(int *target, int len, char sep) {
	for (int y = 0; y<len; y++) printf("%d%c",target[y],sep);
	printf("\n");
}

void print_elements(int *target, char sep, int *indexes, int ind_len) {
	for (int y = 0; y<ind_len; y++) printf("%d%c",target[indexes[y]],sep);
	printf("\n");
}

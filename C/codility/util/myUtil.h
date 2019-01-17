/*
 * myUtil.h
 *
 *  Created on: Oct 29, 2018
 *      Author: foobar
 */

#ifndef UTIL_MYUTIL_H_
#define UTIL_MYUTIL_H_
#define MIN(x,y)  (x <= y? x : y)
#define MAX(x,y)  (x >= y? x : y)
#define INTSIZE(x)  (sizeof(x)/sizeof(int))

char * substr(char * str, int start, int end);
void print_array(int *target, int len, char sep);
print_elements(int *target, char sep, int *indexes, int ind_len);

#endif /* UTIL_MYUTIL_H_ */

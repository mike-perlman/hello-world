/*
 * frogjump.c
 *
 *  Created on: Oct 27, 2018
 *      Author: foobar
 */


int num_jumps(int x, int y, int D) {
	if (x > y) return 0;
	if (D <= 0) return 0;
    printf("start: %d, end: %d, hop-length: %d\n", x,y,D);
	int net_distance = y - x;
	if (D > net_distance) return 1;
	int out = net_distance / D;
	if (net_distance %D > 0) out++;
	printf("net_distance: %d, hops: %d\n", net_distance, out);
	return out;
}

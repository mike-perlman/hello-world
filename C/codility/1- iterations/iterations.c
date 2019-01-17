#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int binaryGap(int N) {
	int largest = 0;
	int current = 0;
	unsigned short bits = sizeof(int) * 8;
	printf("Scanning %d bits.\n", bits);

	for (int x = 0, t = 0; x < bits && (t = N >>x) > 0; x++) {
       t &= 1;
       printf("%d",t);
		if (t == 0)
			current+= 1;
		else {
			if (current > largest)
				largest = current;
			current = 0;
		}
	}
	printf("\n");
	return largest;
}


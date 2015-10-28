#include "setmatrix.h"
#include <stdlib.h>

void processSetMatrix(int ***ptr) {
	int f = 0;
	for (int i = 0; ptr[i]; i++) {
		printf("-- %p %p\n", ptr+i, ptr[i]);
		for (int j = 0; ptr[i][j]; j++) {
			printf("%p, %p\n", ptr[i][j], ptr[i]+j);
			for (int k = 0; ptr[i][j][k]; k++) {
				printf(" %p", ptr[i][j]+k);
				int v = ptr[i][j][k];
				continue;
				if (f)	putchar(' ');
				printf("%d", v);
				f = 1;
			}
			puts("");
		}
	}
	puts("");
}

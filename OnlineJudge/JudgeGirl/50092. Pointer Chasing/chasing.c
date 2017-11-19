#include "chasing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXS (1<<16)
void chasing(int **A[], int a, int *B[], int b, int C[], int c) {
	static char s[MAXS], s1[MAXS], s2[MAXS], s3[MAXS];
	int x, y;
	memset(A, 0, sizeof(A[0])*a);
	memset(B, 0, sizeof(B[0])*a);
	while (fgets(s, MAXS, stdin)) {
		int ret = sscanf(s, "%s%d%s%d%s", s1, &x, s2, &y, s3);
		if (ret != 4 || x < 0 || y < 0)
			ret = 0;
		if (ret) {
			if (!strcmp("A", s1) && !strcmp("B", s2) && x < a && y < b)
				A[x] = &B[y];
			else if (!strcmp("B", s1) && !strcmp("C", s2) && x < b && y < c)
				B[x] = &C[y];
			else
				ret = 0;
		}
		puts(ret ? "1" : "0");
	}
}

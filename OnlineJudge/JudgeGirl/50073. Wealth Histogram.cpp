#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
typedef struct R {
	char s[12];
 	unsigned int W;
} R;
#define MAXINT 2147483647
#define MOD 1000

static int cmp(const void *a, const void *b) {
	int x = ((R *) a)->W;
	int y = ((R *) b)->W;
	if (x == y)	return strcmp(((R *)a)->s, ((R *) b)->s);
	if (x < y)	return -1;
	return 1;
}
static int cmp_int(const void *a, const void *b) {
	int x = *(int *) a;
	int y = *(int *) b;
	if (x == y)	return 0;
	if (x < y)	return -1;
	return 1;
}
int main(int argc, char *argv[]) {
	assert(argc > 1);
	FILE *fin = fopen(argv[1], "rb");
	static R A[1024];
	int n = fread(A, sizeof(R), 1024, fin);
	fclose(fin);
	
	int B[1024];
	for (int i = 0; i < n; i++)
		B[i] = A[i].W/MOD;
	qsort(B, n, sizeof(int), cmp_int);
	for (int i = 0; i < n; ) {
		int cnt = 0, v = B[i];
		while (i < n && v == B[i])
			cnt++, i++;
		printf("%d\n", cnt);
	}

	qsort(A, n, sizeof(R), cmp);
	
	int last = n-1;
	while (last-1 >= 0 && A[last-1].W == A[last].W)
		last--;

	int avg = n%2 == 0 ? (A[n/2-1].W+A[n/2].W)/2 : A[n/2].W;
	printf("%s\n%s\n%d\n", A[0].s, A[last].s, avg);
	return 0;
}



